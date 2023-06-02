#include "subs.h"

Universe1::Video::Subs::Subs(const QString &_textHtml,
                             const QString &_textRead,
                             const std::string &_name,
                             const uint64_t _showTime,
                             const uint64_t _hideTime)
    : Item(_name)
    , showTime(_showTime)
    , hideTime(_hideTime)
    , textHtml(_textHtml)
    , textRead(_textRead)
{
    const std::pair<QString, uint64_t> tmp = Config::cfg().getSpeech(textRead);
    pathAudio = tmp.first;
    audioDuration = tmp.second;
}

QTextDocument *Universe1::Video::Subs::createDocument() const
{
    const Config &cfg = Config::cfg();
    QTextOption opts;
    opts.setAlignment(Qt::AlignCenter);
    opts.setWrapMode(QTextOption::NoWrap);
    QTextDocument *doc = new QTextDocument();
    doc->setDefaultTextOption(opts);
    doc->setUndoRedoEnabled(false);

    QString tmp = "<span style=\"";
    if (!cfg.textSubsFontFamily.isEmpty())
        tmp += "font-family:" + cfg.textSubsFontFamily + "; ";
    tmp += "font-size:" + QString::number(cfg.textSubsFontHeight) + "pt; ";
    tmp += "color:" + cfg.colorSubs.name() + "; \">";
    tmp += "<table><tr><td align=\"center\">";
    tmp += textHtml;
    tmp += "</td></tr></table></span>";
    doc->setHtml(tmp);
    return doc;
}

bool Universe1::Video::Subs::initialize(const uint64_t _duration)
{
    if (!Item::initialize(_duration))
        return false;

    const Config &cfg = Config::cfg();
    QTextDocument *doc = createDocument();
    if (qreal(cfg.widthScreen) < doc->size().width())
    {
        std::cerr << "Warning[" << name << "]: Subtitle width overflow [" << doc->size().width() << "], screen width ["
                  << cfg.widthScreen << "]" << std::endl;
    }

    if (qreal(cfg.heightScreen) - cfg.text2DOffsetSubs < doc->size().height())
    {
        std::cerr << "Warning[" << name << "]: Subtitle height overflow [" << doc->size().height()
                  << "], screen height [" << cfg.heightScreen << "], bottom offset [" << cfg.text2DOffsetSubs << "]"
                  << std::endl;
    }
    delete doc;

    return true;
}

void Universe1::Video::Subs::paint(QPainter *_painter) const
{
    const Config &cfg = Config::cfg();
    QTextDocument *doc = createDocument();
    const int xx = static_cast<int>((qreal(cfg.widthScreen) - doc->size().width()) * 0.5);
    const int yy = static_cast<int>(qreal(cfg.heightScreen) - cfg.text2DOffsetSubs - doc->size().height());
    const int add = static_cast<int>(cfg.textSubsFontHeight / 8U);
    _painter->fillRect(xx - add,
                       yy - add,
                       doc->size().width() + 2 * add,
                       doc->size().height() + 2 * add,
                       QColor::fromRgbF(cfg.colorBG.redF(), cfg.colorBG.greenF(), cfg.colorBG.blueF(), cfg.alphaSubs));
    _painter->save();
    _painter->setTransform(QTransform::fromTranslate(xx, yy));
    doc->drawContents(_painter);
    _painter->restore();
    delete doc;
}

Universe1::Video::FootageSubs::FootageSubs(const std::string &_footageName, const uint64_t &_footageId)
    : footageName(_footageName)
    , footageId(_footageId)
{
}

Universe1::Video::FootageSubs::~FootageSubs()
{
    while (!subs.empty())
    {
        delete subs.front();
        subs.pop_front();
    }
}

Universe1::Video::Subs *Universe1::Video::FootageSubs::add(const uint64_t _showTime,
                                                           const uint64_t _hideTime,
                                                           const QString &_textHtml,
                                                           const QString &_textRead)
{
    const uint64_t fd = Config::cfg().frameDuration;
    const uint64_t tmodShow = _showTime % fd;
    const uint64_t tmodHide = _hideTime % fd;
    const uint64_t usedShowTime = _showTime + (tmodShow == 0UL ? 0UL : (fd - tmodShow));
    const uint64_t usedHideTime = _hideTime + (tmodHide == 0UL ? 0UL : (fd - tmodHide));
    const uint64_t sid = subs.size() + 1UL;

    const std::string name = footageName + ".subs[" + std::to_string(sid) + "]";

    if (usedShowTime != _showTime)
        std::cerr << "Warning[" << name << "]: Using aligned show time " << usedShowTime << "ms !" << std::endl;

    if (usedHideTime != _hideTime)
        std::cerr << "Warning[" << name << "]: Using aligned hide time " << usedHideTime << "ms !" << std::endl;

    Subs *result = new Subs(_textHtml, _textRead, name, usedShowTime, usedHideTime);
    subs.push_back(result);

    return result;
}

bool Universe1::Video::FootageSubs::initialize(const uint64_t _duration)
{
    const Config &cfg = Config::cfg();
    if (!cfg.addSubs || subs.empty())
    {
        pathAudioFile = cfg.getSilence(_duration);
        return true;
    }

    subs.sort([](const Subs *_1, const Subs *_2) { return _1->showTime < _2->showTime; });

    bool result = true;

    if (subs.size() == 1UL)
    {
        result = subs.front()->initialize(_duration);
    }
    else
    {
        std::list<Subs *>::iterator itPrev = subs.begin();
        std::list<Subs *>::iterator itNext = itPrev;
        ++itNext;

        for (; itNext != subs.end(); ++itPrev, ++itNext)
            if (!(*itPrev)->initialize((*itNext)->showTime))
                result = false;

        if (!(*itPrev)->initialize(_duration))
            result = false;
    }

    if (!result)
        return false;

    QStringList allAudioFiles;

    std::list<Subs *>::iterator it = subs.begin();
    uint64_t t = 0UL;
    uint64_t s = 0UL;

    if ((*it)->showTime > 0U)
    {
        allAudioFiles.push_back(cfg.getSilence((*it)->showTime));
        t = (*it)->showTime;
        s++;
    }

    allAudioFiles.push_back((*it)->pathAudio);
    t += (*it)->audioDuration;
    ++it;

    for (; it != subs.end(); ++it)
    {
        const uint64_t nextSilence = (*it)->showTime - t;
        if (nextSilence != 0UL)
        {
            allAudioFiles.push_back(cfg.getSilence(nextSilence));
            t = (*it)->showTime;
            s++;
        }
        allAudioFiles.push_back((*it)->pathAudio);
        t += (*it)->audioDuration;
    }

    if (t > _duration)
    {
        std::cerr << "Error[" << footageName << "]: Audio duration overflow !" << std::endl;
        return false;
    }

    const uint64_t lastSilence = _duration - t;
    if (lastSilence != 0UL)
        allAudioFiles.push_back(cfg.getSilence(lastSilence));

    pathAudioFile = cfg.pathFootageAudio(footageId);
    return cfg.connectAudio(pathAudioFile, allAudioFiles);
}

void Universe1::Video::FootageSubs::paint(QPainter *_painter, const uint64_t _timeStep) const
{
    const Config &cfg = Config::cfg();
    if (!cfg.addSubs)
        return;

    for (const Subs *s : subs)
    {
        if (s->showTime > _timeStep)
            return;

        if (s->isCurrent(_timeStep))
        {
            s->paint(_painter);
            return;
        }
    }
}

QString Universe1::Video::FootageSubs::toHtml() const
{
    QString result = "<h2>" + QString::fromStdString(footageName) + "</h2><br/><table>";
    for (const Subs *s : subs)
        result += "<tr><td>" + QTime::fromMSecsSinceStartOfDay(s->showTime).toString("m:ss.z") + "</td><td>" +
            QTime::fromMSecsSinceStartOfDay(s->hideTime).toString("m:ss.z") + "</td><td>" +
            QTime::fromMSecsSinceStartOfDay(s->hideTime - s->showTime).toString("m:ss.z") +
            "</td><td style=\"text-align:left; font-size:200%; padding:5px; border: 1px solid grey; "
            "border-radius:5px;\">" +
            s->textHtml + "</td></tr>";
    result += "</table>";
    return result;
}
