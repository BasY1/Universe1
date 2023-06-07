#include "footagefactory.h"

std::list<Universe1::Video::FootageFactoryInterface *> Universe1::Video::Footages::sequence = {};

uint64_t Universe1::Video::Footages::init(std::list<Footage *> &_footages)
{
    std::pair<QVector3D, QVector3D> camera = {QVector3D(1, -8, 3), QVector3D(0, 0, 0)};

    uint64_t id = 1UL, tt = 0UL;
    for (const FootageFactoryInterface *fi : sequence)
    {
        Footage *next = fi->create(id, tt, camera);
        camera = next->camera.getLastState();
        id++;
        tt += next->duration;
        _footages.push_back(next);
    }
    return tt;
}

bool Universe1::Video::Footages::saveSubsHtml(const std::list<Footage *> &_footages, const QString &_fileName)
{
    QFile subsFile(_fileName);
    if (!subsFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Error: Can't create file: " << _fileName.toStdString() << std::endl;
        return false;
    }

    QTextStream ss(&subsFile);
    ss << "<!DOCTYPE html><html lang=\"en\"><head><title>Subs</title></head><body style=\"background-color:black; "
          "color:white; \">";
    for (const Footage *f : _footages)
        ss << f->subs.toHtml();
    ss << "</body></html>";

    subsFile.flush();
    subsFile.close();

    return true;
}

bool Universe1::Video::Footages::saveIndexes(const std::list<Footage *> &_footages, const QString &_fileName)
{
    const Config &cfg = Config::cfg();
    QFile iFile(_fileName);
    if (!iFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Error: Can't create file: " << _fileName.toStdString() << std::endl;
        return false;
    }
    QTextStream ts(&iFile);

    const float iDur = static_cast<float>(cfg.frameDuration) / 1000.0f;
    for (const Footage *f : _footages)
    {
        for (uint64_t frId = 0UL; frId < f->framesCount; ++frId)
            ts << "file '" << cfg.pathImage(f->footageId, frId) << "'\nduration " << iDur << "\n";
    }
    ts << "file '" << cfg.pathImage(_footages.back()->footageId, _footages.back()->framesCount - 1UL) << "'\n";
    iFile.flush();
    iFile.close();

    return true;
}
