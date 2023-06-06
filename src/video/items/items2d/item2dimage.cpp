#include "item2dimage.h"

Universe1::Video::Item2DImage::Item2DImage(const bool _visible,
                                           const bool _visibleText,
                                           const QImage &_image,
                                           const QString &_textHtml,
                                           const float _textSize,
                                           const Qt::Alignment _textAlign,
                                           const QColor _textColor,
                                           const std::string &_name)
    : Item2D(_visible, _textHtml, _textSize, _textAlign, _textColor, _name)
    , image(_image)
    , visibleText(_visibleText, _name + ".visibleText")
    , positionX(0U, _name + ".positionX")
    , positionY(0U, _name + ".positionY")
    , sizeX(0U, _name + ".sizeX")
    , sizeY(0U, _name + ".sizeY")
{
    props.push_back(&visibleText);
    props.push_back(&positionX);
    props.push_back(&positionY);
    props.push_back(&sizeX);
    props.push_back(&sizeY);
    addMaximized(0UL);
}

bool Universe1::Video::Item2DImage::initialize(const uint64_t _duration)
{
    return Item2D::initialize(_duration);
}

void Universe1::Video::Item2DImage::paint(QPainter *_painter, const uint64_t _timeStep) const
{
    const Config &cfg = Config::cfg();
    const bool isText = visibleText.getValue(_timeStep);
    const uint px = positionX.getValue(_timeStep);
    const uint py = positionY.getValue(_timeStep);
    const uint sx = sizeX.getValue(_timeStep);
    const uint sy = sizeY.getValue(_timeStep);
    _painter->drawImage(QRect(px, py, sx, sy), image, image.rect());

    if (isText)
    {
        QTextDocument *doc = createDocument(_timeStep);
        qreal x, y;

        const Qt::Alignment al = text.align.getValue(_timeStep);
        if (al.testFlag(Qt::AlignLeft))
            x = px;
        else if (al.testFlag(Qt::AlignRight))
            x = px + sx - doc->size().width();
        else
            x = px + (sx / 2U) - (doc->size().width() / qreal(2));

        if (al.testFlag(Qt::AlignTop))
            y = py - qreal(cfg.text2DFontHeight / 2U);
        else
            y = py + sy + qreal(cfg.text2DFontHeight / 2U);

        _painter->save();
        _painter->setTransform(QTransform::fromTranslate(x, y));
        doc->drawContents(_painter);
        _painter->restore();
        delete doc;
    }
}

void Universe1::Video::Item2DImage::addMaximized(const uint64_t _timeStep)
{
    const Config &cfg = Config::cfg();
    const qreal ix = image.width();
    const qreal iy = image.height();
    const qreal sx = cfg.widthScreen - cfg.text2DOffsetBorder * 2.0;
    const qreal sy = cfg.heightScreen - cfg.text2DOffsetBorder - cfg.text2DOffsetSubs - 3 * cfg.text2DFontHeight;
    const qreal rx = sx / ix;
    const qreal ry = sy / iy;
    uint px = 0U, py = 0U, ax = 0U, ay = 0U;
    if (rx > ry)
    {
        py = cfg.text2DOffsetBorder;
        ay = sy;
        ax = ry * ix;
        px = (cfg.widthScreen - ax) / 2U;
    }
    else
    {
        px = cfg.text2DOffsetBorder;
        ax = sx;
        ay = rx * iy;
        py = cfg.text2DOffsetBorder + (sy - ay) / 2U;
    }

    if (_timeStep == 0UL)
    {
        positionX = px;
        positionY = py;
        sizeX = ax;
        sizeY = ay;
    }
    else
    {
        positionX.add(_timeStep, px);
        positionY.add(_timeStep, py);
        sizeX.add(_timeStep, ax);
        sizeY.add(_timeStep, ay);
    }
}

//

Universe1::Video::DBItem2DImage::DBItem2DImage(const std::string &_footageName)
    : footageName(_footageName)
{
}

Universe1::Video::DBItem2DImage::~DBItem2DImage()
{
    for (Item2DImage *i : images)
        delete i;
}

Universe1::Video::Item2DImage *Universe1::Video::DBItem2DImage::add(const bool _visible,
                                                                    const bool _visibleText,
                                                                    const QImage &_image,
                                                                    const QString &_textHtml,
                                                                    const float _textSize,
                                                                    const Qt::Alignment _textAlign,
                                                                    const QColor _textColor)
{
    Item2DImage *result = new Item2DImage(_visible,
                                          _visibleText,
                                          _image,
                                          _textHtml,
                                          _textSize,
                                          _textAlign,
                                          _textColor,
                                          footageName + ".image[" + std::to_string(images.size() + 1UL) + "]");
    images.push_back(result);
    return result;
}

bool Universe1::Video::DBItem2DImage::initialize(const uint64_t _duration)
{
    bool result = true;
    for (Item2DImage *p : images)
        if (!p->initialize(_duration))
            result = false;
    return result;
}

void Universe1::Video::DBItem2DImage::paint(QPainter *_painter, const uint64_t _timeStep) const
{
    for (const Item2DImage *p : images)
        if (p->visible.getValue(_timeStep))
            p->paint(_painter, _timeStep);
}
