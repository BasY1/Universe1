#include "item2d.h"

const std::set<Qt::Alignment> Universe1::Video::Item2D::supportedAlignments = {
    (Qt::AlignLeft | Qt::AlignTop),
    (Qt::AlignLeft | Qt::AlignBottom),
    (Qt::AlignLeft | Qt::AlignVCenter),
    (Qt::AlignRight | Qt::AlignTop),
    (Qt::AlignRight | Qt::AlignBottom),
    (Qt::AlignRight | Qt::AlignVCenter),
    (Qt::AlignHCenter | Qt::AlignTop),
    (Qt::AlignHCenter | Qt::AlignBottom),
    (Qt::AlignHCenter | Qt::AlignVCenter),
};

Universe1::Video::Item2D::Item2D(const bool _visible,
                                 const QString &_textHtml,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const QColor _textColor,
                                 const std::string &_name)
    : Item(_name)
    , visible(_visible, _name + ".visible")
    , text(_textHtml, _textSize, _textAlign, _name, props)
    , textColor(_textColor, _name + ".textColor")
{
    props.push_back(&visible);
    props.push_back(&textColor);
}

QTextDocument *Universe1::Video::Item2D::createDocument(const uint64_t _timeStep) const
{
    const Config &cfg = Config::cfg();
    QTextOption opts;
    opts.setAlignment(Qt::AlignCenter);
    opts.setWrapMode(QTextOption::NoWrap);
    QTextDocument *doc = new QTextDocument();
    doc->setDefaultTextOption(opts);
    doc->setUndoRedoEnabled(false);

    const QColor cText = textColor.getValue(_timeStep);
    const uint hText =
        std::max(10U, static_cast<uint>(static_cast<float>(cfg.text2DFontHeight) * text.sizeMult.getValue(_timeStep)));

    QString tmp = "<span style=\"";
    if (!cfg.text2DFontFamily.isEmpty())
        tmp += "font-family:" + cfg.text2DFontFamily + "; ";
    tmp += "font-size:" + QString::number(hText) + "pt; ";
    tmp += "color:" + cText.name() + "; \">";
    tmp += text.text.getValue(_timeStep);
    tmp += "</span>";
    doc->setHtml(tmp);
    return doc;
}

bool Universe1::Video::Item2D::initialize(const uint64_t _duration)
{
    return Item::initialize(_duration);
}

void Universe1::Video::Item2D::paint(QPainter *_painter, const uint64_t _timeStep) const
{
    const Config &cfg = Config::cfg();
    QTextDocument *doc = createDocument(_timeStep);
    qreal x = 0, y = 0;

    const Qt::Alignment textAlign = text.align.getValue(_timeStep);

    if (textAlign.testFlag(Qt::AlignBaseline))
    {
        x = qreal(cfg.widthScreen) - doc->size().width();
    }
    else
    {
        x = cfg.text2DOffsetBorder;
        y = cfg.text2DOffsetBorder;
        if (textAlign.testFlag(Qt::AlignRight))
            x = qreal(cfg.widthScreen) - doc->size().width() - cfg.text2DOffsetBorder;
        else if (textAlign.testFlag(Qt::AlignHCenter))
            x = (qreal(cfg.widthScreen) - doc->size().width()) / qreal(2);

        if (textAlign.testFlag(Qt::AlignBottom))
            y = qreal(cfg.heightScreen) - doc->size().height() - cfg.text2DOffsetSubs;
        else if (textAlign.testFlag(Qt::AlignVCenter))
            y = cfg.text2DOffsetBorder +
                (qreal(cfg.heightScreen) - doc->size().height() - cfg.text2DOffsetBorder - cfg.text2DOffsetSubs) /
                    qreal(2);
    }
    _painter->save();
    _painter->setTransform(QTransform::fromTranslate(x, y));
    doc->drawContents(_painter);
    _painter->restore();
    delete doc;
}

//

Universe1::Video::FootageItems2D::FootageItems2D(const std::string &_footageName)
    : footageName(_footageName)
{
}

Universe1::Video::FootageItems2D::~FootageItems2D()
{
    for (std::pair<const Qt::Alignment, std::list<Item2D *>> &i : items)
        for (Item2D *ii : i.second)
            delete ii;
}

Universe1::Video::Item2D *Universe1::Video::FootageItems2D::add(const bool _visible,
                                                                const QString &_textHtml,
                                                                const float _textSize,
                                                                const Qt::Alignment _textAlign,
                                                                const QColor _textColor)
{
    std::map<Qt::Alignment, std::list<Item2D *>>::iterator it = items.find(_textAlign);
    if (it == items.end())
    {
        Item2D *result = new Item2D(_visible,
                                    _textHtml,
                                    _textSize,
                                    _textAlign,
                                    _textColor,
                                    footageName + ".2D[" + std::to_string(_textAlign) + "]");
        items.insert({_textAlign, {result}});
        return result;
    }
    std::cerr << "Error[" << footageName << "]: Can't add secondary item 2D, align[" << _textAlign << "] !"
              << std::endl;
    return nullptr;
}

bool Universe1::Video::FootageItems2D::initialize(const uint64_t _duration)
{
    if (items.empty())
        return true;

    bool result = true;
    for (std::pair<const Qt::Alignment, std::list<Item2D *>> &i : items)
        for (Item2D *ii : i.second)
            if (!ii->initialize(_duration))
                result = false;

    return result;
}

void Universe1::Video::FootageItems2D::paint(QPainter *_painter, const uint64_t _timeStep) const
{
    for (const std::pair<const Qt::Alignment, std::list<Item2D *>> &i : items)
        for (const Item2D *s : i.second)
            if (s->visible.getValue(_timeStep))
                s->paint(_painter, _timeStep);
}
