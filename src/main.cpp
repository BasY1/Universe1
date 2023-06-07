#include "gui/mainwindow.h"

#include "video/footagefactory.h"
#include "video/tutorial/tutorial.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    using namespace Universe1::Video;

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("BasY");
    QCoreApplication::setApplicationName("VideoUniverse1");
    QCoreApplication::setApplicationVersion("0.0.1");

    QSettings settings;
    const QString lastPath = settings.value("lastPath", QDir::homePath() + QDir::separator() + "Universe1").toString();
    const QString lastFile = settings.value("lastFile", "Universe1").toString();

    const Config &cfg = Config::init(lastPath, lastFile, 3, true, 2);
    // const Config &cfg = Config::init(lastPath, lastFile, 2, true);
    // const Config &cfg = Config::init(lastPath, lastFile, 1, true);

    Footages::add<Tutorial::Demo3DText>();

    uint64_t removedImg = 0UL, removedAudio = 0UL;
    if (!cfg.clearDirectory(removedImg, removedAudio))
        return EXIT_FAILURE;

    if (cfg.verbose && (removedImg > 0UL || removedAudio > 0UL))
        std::cout << "*****************  Clear image directory, removed " << removedImg << " images and "
                  << removedAudio << " audio files" << std::endl;

    if (cfg.verbose)
        std::cout << "*****************  Creating footages [" << Footages::sequence.size() << "]" << std::endl;

    std::list<Footage *> footages;
    const uint64_t totalDuration = Footages::init(footages);
    cfg.showInfo2(footages.size(), totalDuration);
    if (footages.empty())
    {
        std::cerr << "Empty footage list !" << std::endl;
        return EXIT_FAILURE;
    }

    bool ok = true;
    uint64_t totalFrames = 0UL;
    for (Footage *f : footages)
    {
        if (!f->initialize())
            ok = false;
        else
            totalFrames += f->framesCount;
    }

    if (!ok)
        return EXIT_FAILURE;

    if (cfg.showGui)
    {
        MainWindow mw(footages, totalDuration, totalFrames);
        mw.showMaximized();
        const int e = a.exec();
        if (!mw.createVideo())
            return e;
    }

    if (!cfg.fileSubsHtml.isEmpty() && !Footages::saveSubsHtml(footages, cfg.outPath + cfg.fileSubsHtml))
        return EXIT_FAILURE;

    if (!Footages::saveIndexes(footages, cfg.outPath + cfg.dirImages + cfg.fileIndex))
        return EXIT_FAILURE;

    const QString fa1 = cfg.outPath + cfg.dirAudio + "audio_mix." + cfg.suffixAudio;
    const QString fa2 = cfg.outPath + cfg.dirAudio + "audio." + cfg.suffixAudio;

    QStringList opts;
    for (const Footage *f : footages)
        opts << f->subs.pathAudioFile;

    if (!cfg.connectAudio(fa1, opts) || !cfg.normalizeAudio(fa2, fa1))
        return EXIT_FAILURE;

    if (!cfg.createVideo())
        return EXIT_FAILURE;

    while (!footages.empty())
    {
        delete footages.front();
        footages.pop_front();
    }

    Config::saveSpeechDB();
    settings.setValue("lastPath", cfg.outPath);
    settings.setValue("lastFile", cfg.outFileName);

    return EXIT_SUCCESS;
}
