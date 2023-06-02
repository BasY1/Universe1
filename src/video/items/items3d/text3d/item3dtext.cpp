#include "item3dtext.h"

Universe1::Video::Item3DText::Item3DText(const QString &_textHtml,
                                         const float _textSize,
                                         const Qt::Alignment _textAlign,
                                         const QVector3D &_position,
                                         const QVector3D &_normalRow,
                                         const QVector3D &_normalUp,
                                         const bool _followCamera,
                                         const bool _visible,
                                         const Material &_material,
                                         const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , text(_textHtml, _textSize, _textAlign, _name, props)
    , position(_position, _name + ".position")
    , normalRow(_normalRow, _name + ".normalRow")
    , normalUp(_normalUp, _name + ".normalUp")
    , followCamera(_followCamera, _name + ".followCamera")
{
    props.push_back(&position);
    props.push_back(&normalRow);
    props.push_back(&normalUp);
    props.push_back(&followCamera);
}

void Universe1::Video::Item3DText::addData3D(std::list<Data3D> &_out,
                                             const Shader *_shader,
                                             const uint64_t _timeStep) const
{
    const QString txt = text.text.getValue(_timeStep);
    const float tps = text.sizeMult.getValue(_timeStep);
    const Qt::Alignment al = text.align.getValue(_timeStep);
    const QVector3D p = position.getValue(_timeStep);
    const Material m = material.getValue(_timeStep);
    if (followCamera.getValue(_timeStep))
        buildData(_out, _shader, txt, tps, al, p, m);
    else
        buildData(_out, txt, tps, al, p, normalRow.getValue(_timeStep), normalUp.getValue(_timeStep), m);
}

void Universe1::Video::Item3DText::buildData(std::list<Data3D> &_out,
                                             const QString &_textHtml,
                                             const float _textSize,
                                             const Qt::Alignment _textAlign,
                                             const QVector3D &_position,
                                             const QVector3D &_normalRow,
                                             const QVector3D &_normalUp,
                                             const Material &_material)

{
    const Config &cfg = Config::cfg();

    QTextOption opts;
    opts.setAlignment(Qt::AlignCenter);
    opts.setWrapMode(QTextOption::NoWrap);
    QTextDocument *doc = new QTextDocument();
    doc->setDefaultTextOption(opts);
    doc->setUndoRedoEnabled(false);

    const QString &ff = cfg.text3DFontFamily;
    QString tmp = "<span style=\"";
    if (!ff.isEmpty())
        tmp += "font-family:" + ff + "; ";
    tmp += "font-size:" + QString::number(cfg.text3DFontHeight) + "px; color:#FFFFFF; \">";
    tmp += _textHtml;
    tmp += "</span>";
    doc->setHtml(tmp);

    const float mult = _textSize * cfg.text3DPixelSize;

    const QSize imgSize = doc->size().toSize();
    int imgMinX = imgSize.width() + 1, imgMaxX = -1;
    int imgMinY = imgSize.height() + 1, imgMaxY = -1;
    std::vector<uint8_t> imgData(imgSize.width() * imgSize.height(), 0U);
    {
        QImage img(imgSize.width(), imgSize.height(), QImage::Format_Mono);
        img.fill(0);

        {
            QPainter painter(&img);
            painter.setPen(Qt::white);
            doc->drawContents(&painter);
        }

        for (int x = 0; x < img.width(); ++x)
            for (int y = 0; y < img.height(); ++y)
                if (img.pixelColor(x, y) == Qt::white)
                {
                    const int yy = img.height() - y - 1;
                    imgData[x * img.height() + yy] = 1U;
                    if (imgMinX > imgMaxX)
                    {
                        imgMinX = x;
                        imgMaxX = x;
                        imgMinY = yy;
                        imgMaxY = yy;
                    }
                    else
                    {
                        imgMinX = std::min(imgMinX, x);
                        imgMaxX = std::max(imgMaxX, x);
                        imgMinY = std::min(imgMinY, yy);
                        imgMaxY = std::max(imgMaxY, yy);
                    }
                }
    }

    delete doc;

    if (imgMinX > imgMaxX)
        return;

    QVector3D cc = _position;
    if (_textAlign.testFlag(Qt::AlignLeft))
        cc += -_normalRow * (mult * static_cast<float>(imgMaxX - imgMinX + 1));
    else if (_textAlign.testFlag(Qt::AlignHCenter))
        cc += -_normalRow * (0.5f * mult * static_cast<float>(imgMaxX - imgMinX + 1));

    if (_textAlign.testFlag(Qt::AlignBottom))
        cc += -_normalUp * (mult * static_cast<float>(imgMaxY - imgMinY + 1));
    else if (_textAlign.testFlag(Qt::AlignVCenter))
        cc += -_normalUp * (0.5f * mult * static_cast<float>(imgMaxY - imgMinY + 1));

    const QVector3D nf = QVector3D::crossProduct(_normalRow, _normalUp).normalized();
    const QVector3D sr = _normalRow * mult;
    const QVector3D su = _normalUp * mult;

    std::list<std::array<QVector3D, 4U>> pnts;
    for (int xx = imgMinX; xx <= imgMaxX; ++xx)
    {
        const int uxx = xx * imgSize.height();
        const QVector3D cxx = cc + sr * static_cast<float>(xx - imgMinX);

        for (int yy = imgMinY; yy <= imgMaxY; ++yy)
        {
            if (imgData[uxx + yy] != 1U)
                continue;
            int add = 0;
            for (int yyy = yy + 1; yyy <= imgMaxY; ++yyy)
            {
                if (imgData[uxx + yyy] != 1U)
                    break;
                add++;
            }
            const QVector3D p = cxx + su * static_cast<float>(yy - imgMinY);
            const QVector3D u = su * static_cast<float>(add + 1);
            pnts.push_back({p, p + sr, p + sr + u, p + u});
            yy += add;
        }
    }

    _out.push_back({_material, pnts.size() * 4UL, pnts.size() * 6UL, nf});
    Data3D &out = _out.back();

    uint idx = 0U;
    for (const std::array<QVector3D, 4U> &pnt : pnts)
    {
        for (uint8_t i = 0U; i < 4U; ++i)
            out.points.push_back(pnt[i]);
        out.indexes.push_back(idx);
        out.indexes.push_back(idx + 2U);
        out.indexes.push_back(idx + 1U);
        out.indexes.push_back(idx);
        out.indexes.push_back(idx + 3U);
        out.indexes.push_back(idx + 2U);
        idx += 4U;
    }
}

Universe1::Video::DBItem3DText::DBItem3DText(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("text3D", _footageName, _items)
{
}

Universe1::Video::Item3DText *Universe1::Video::DBItem3DText::add(const QString &_textHtml,
                                                                  const float _textSize,
                                                                  const Qt::Alignment _textAlign,
                                                                  const QVector3D &_position,
                                                                  const QVector3D &_normalRow,
                                                                  const QVector3D &_normalUp,
                                                                  const bool _followCamera,
                                                                  const bool _visible,
                                                                  const Material &_material)
{
    Item3DText *result = new Item3DText(_textHtml,
                                        _textSize,
                                        _textAlign,
                                        _position,
                                        _normalRow,
                                        _normalUp,
                                        _followCamera,
                                        _visible,
                                        _material,
                                        nextName());
    items->push_back(result);
    return result;
}
