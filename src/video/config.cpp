#include "config.h"

QHash<QString, std::pair<QString, uint64_t>> Universe1::Video::Config::speechDB = {};
QHash<uint64_t, QString> Universe1::Video::Config::silenceDB = {};
Universe1::Video::Config Universe1::Video::Config::m_cfg(QDir::homePath() + QDir::separator() + "Universe1",
                                                         "Universe1");

Universe1::Video::Config::Config(const QString &_outPath,
                                 const QString &_outFileName,
                                 const uint _level,
                                 const uint _threads)
    : level(_level)
    , threads(_threads == 0U ? std::thread::hardware_concurrency() : _threads)
    , outPath(_outPath)
    , outFileName(_outFileName)
{
    if (!outPath.endsWith(QDir::separator()))
        outPath += QDir::separator();

    switch (level)
    {
    case 1U:
        widthScreen = 1920;
        heightScreen = 1080;

        glAccuracy = 0.1f;
        glSamples = 4U;

        textSubsFontHeight = 20U;
        text2DFontHeight = 20U;
        text3DFontHeight = 40U;
        text3DPixelSize = 0.0025f;
        text2DOffsetBorder = 40.0;
        text2DOffsetSubs = 150.0;

        qualityLine = 1U;
        qualitySphere = 7U;

        break;

    case 2U:
        widthScreen = 3840;
        heightScreen = 2160;

        glAccuracy = 0.01f;
        glSamples = 8U;

        textSubsFontHeight = 36U;
        text2DFontHeight = 36U;
        text3DFontHeight = 50U;
        text3DPixelSize = 0.002f;
        text2DOffsetBorder = 60.0;
        text2DOffsetSubs = 200.0;

        qualityLine = 3U;
        qualitySphere = 15U;

        break;

    case 3U:
        widthScreen = 3840;
        heightScreen = 2160;

        glAccuracy = 0.001f;
        glSamples = 16U;

        textSubsFontHeight = 36U;
        text2DFontHeight = 36U;
        text3DFontHeight = 100;
        text3DPixelSize = 0.001f;
        text2DOffsetBorder = 60.0;
        text2DOffsetSubs = 200.0;

        qualityLine = 7U;
        qualitySphere = 31U;

        break;
    }
}

void Universe1::Video::Config::showInfo() const
{
    if (!verbose)
        return;

    std::cout << "*****************  Configuration  *****************" << std::endl;
    std::cout << "Output path:       " << outPath.toStdString() << std::endl;
    std::cout << "Output video:      " << outFileName.toStdString() << "." << suffixVideo.toStdString() << std::endl;
    std::cout << "Thread count:      " << threads << std::endl;
    std::cout << "Quality level:     " << level << std::endl;
    std::cout << "Screen resolution: " << widthScreen << " x " << heightScreen << std::endl;
    std::cout << "Open GL accuracy:  " << glAccuracy << std::endl;
    std::cout << "Open GL samples:   " << glSamples << std::endl;
    std::cout << "2D text:           " << text2DFontHeight << ", subs: " << textSubsFontHeight << std::endl;
    std::cout << "3D text:           " << text3DFontHeight << ", pixel: " << text3DPixelSize << std::endl;
    std::cout << "Quality:           " << qualityLine << ", " << qualitySphere << std::endl;
    std::cout << "Frame duration:    " << frameDuration << "ms" << std::endl;
    std::cout << "Frames per second: " << (1000.0f / static_cast<float>(frameDuration)) << std::endl;
    std::cout << "Audio database:    " << Config::speechDB.size() << ", silence: " << Config::silenceDB.size()
              << std::endl;
}

bool Universe1::Video::Config::clearSpeechDB()
{
    const QString speechPath = m_cfg.outPath + m_cfg.dirSpeech;
    return QDir(speechPath).removeRecursively() && QDir().mkpath(speechPath);
}

bool Universe1::Video::Config::initSpeechDB()
{
    speechDB.clear();
    silenceDB.clear();

    const QString speechPath = m_cfg.outPath + m_cfg.dirSpeech;
    const QString speechFile = speechPath + "speech.txt";
    const QString silenceFile = speechPath + "silence.txt";

    QFile f1(speechFile);
    QFile f2(silenceFile);
    if (!f1.open(QIODevice::ReadOnly))
        return false;

    if (!f2.open(QIODevice::ReadOnly))
    {
        f1.close();
        return false;
    }

    {
        QDataStream s1(&f1);
        quint32 cnt;
        s1 >> cnt;
        for (quint32 i = 0U; i < cnt; ++i)
        {
            QString txt, file;
            quint64 dur;
            s1 >> txt;
            s1 >> file;
            s1 >> dur;
            speechDB.insert(txt, {file, dur});
        }
        f1.close();
    }

    {
        QDataStream s2(&f2);
        quint32 cnt;
        s2 >> cnt;
        for (quint32 i = 0U; i < cnt; ++i)
        {
            QString file;
            quint64 dur;
            s2 >> file;
            s2 >> dur;
            silenceDB.insert(dur, file);
        }
        f2.close();
    }

    return true;
}

bool Universe1::Video::Config::saveSpeechDB()
{
    const QString speechPath = m_cfg.outPath + m_cfg.dirSpeech;
    const QString speechFile = speechPath + "speech.txt";
    const QString silenceFile = speechPath + "silence.txt";

    QFile f1(speechFile);
    QFile f2(silenceFile);
    if (!f1.open(QIODevice::WriteOnly))
    {
        std::cerr << "Error: Can't write into file: " << speechFile.toStdString() << std::endl;
        return false;
    }

    if (!f2.open(QIODevice::WriteOnly))
    {
        std::cerr << "Error: Can't write into file: " << silenceFile.toStdString() << std::endl;
        f1.close();
        return false;
    }

    {
        QDataStream s1(&f1);
        s1.setVersion(QDataStream::Qt_5_0);
        s1 << quint32(speechDB.size());
        QHash<QString, std::pair<QString, uint64_t>>::const_iterator i = speechDB.constBegin();
        while (i != speechDB.constEnd())
        {
            s1 << i.key();
            s1 << i.value().first;
            s1 << quint64(i.value().second);
            ++i;
        }
        f1.flush();
        f1.close();
    }

    {
        QDataStream s2(&f2);
        s2.setVersion(QDataStream::Qt_5_0);
        s2 << quint32(silenceDB.size());
        QHash<uint64_t, QString>::const_iterator i = silenceDB.constBegin();
        while (i != silenceDB.constEnd())
        {
            s2 << quint64(i.key());
            s2 << i.value();
            ++i;
        }
        f2.flush();
        f2.close();
    }
    return true;
}

static bool removeDirFiles(uint64_t &_out, const QString &_path, const QStringList &_filter)
{
    QDir dir1(_path);
    dir1.setNameFilters(_filter);
    dir1.setFilter(QDir::Files);
    bool result = true;
    foreach (const QString &dirFile, dir1.entryList())
    {
        if (dir1.remove(dirFile))
        {
            _out++;
        }
        else
        {
            std::cerr << "Error: Can't remove file: " + dirFile.toStdString() << std::endl;
            result = false;
        }
    }
    return result;
}

bool Universe1::Video::Config::clearDirectory(uint64_t &_removedImages, uint64_t &_removedAudio) const
{
    return removeDirFiles(_removedAudio, outPath + dirAudio, (QStringList() << ("*." + suffixAudio))) &&
        removeDirFiles(_removedImages, outPath + dirImages, (QStringList() << ("*." + suffixImages) << fileIndex));
}

#define LENGTH_footageId 4
#define LENGTH_frameId 5

QString Universe1::Video::Config::pathImage(const uint64_t _footageId, const uint64_t _frameId) const
{
    const QString foId = QString::number(_footageId);
    const QString frId = QString::number(_frameId);
    return outPath + dirImages + "f" + QString(LENGTH_footageId - foId.length(), '0') + foId + "_" +
        QString(LENGTH_frameId - frId.length(), '0') + frId + "." + suffixImages;
}

QString Universe1::Video::Config::pathFootageAudio(const uint64_t _footageId) const
{
    const QString foId = QString::number(_footageId);
    return outPath + dirAudio + "f" + QString(LENGTH_footageId - foId.length(), '0') + foId + "." + suffixAudio;
}

#undef LENGTH_footageId
#undef LENGTH_frameId

QString Universe1::Video::Config::getSilence(const uint64_t _duration) const
{
    QHash<uint64_t, QString>::iterator it = silenceDB.find(_duration);
    if (it != silenceDB.end())
        return it.value();

    const QString file = m_cfg.outPath + m_cfg.dirSpeech + "void_" + QString::number(_duration) + "." + suffixAudio;
    if (createSilence(file, _duration))
    {
        silenceDB.insert(_duration, file);
        return file;
    }
    return QString();
}

bool Universe1::Video::Config::createSilence(const QString &_fileNameOut, const uint64_t _duration) const
{
    const QStringList opts = {"-n",
                              "-r",
                              m_cfg.audioKhz,
                              _fileNameOut,
                              "trim",
                              "0.0",
                              QString::number(static_cast<float>(_duration) / 1000.0f, 'f', 3)};
    QProcess process;
    process.start("/usr/bin/sox", opts, QIODevice::ReadOnly);
    if (!process.waitForFinished(-1))
    {
        std::cerr << "Error: sox " << opts.join(" ").toStdString() << std::endl;
        return false;
    }

    const QString e = process.readAllStandardError();
    if (!e.isEmpty())
    {
        std::cerr << "Error: sox silence: " << e.toStdString() << std::endl;
        return false;
    }

    return true;
}

std::pair<QString, uint64_t> Universe1::Video::Config::getSpeech(const QString &_speech) const
{
    QHash<QString, std::pair<QString, uint64_t>>::iterator it = speechDB.find(_speech);
    if (it != speechDB.end())
        return it.value();

    const QString file =
        m_cfg.outPath + m_cfg.dirSpeech + "s_" + QString::number(speechDB.size() + 1) + "." + suffixAudio;

    if (createSpeech(file, _speech))
    {
        const uint64_t dur = getAudioDuration(file);
        if (dur > 0UL)
        {
            speechDB.insert(_speech, {file, dur});
            return {file, dur};
        }
    }

    return {"", 0UL};
}

bool Universe1::Video::Config::createSpeech(const QString &_fileNameOut, const QString &_speech) const
{
    QStringList opts = m_cfg.ttsOpts;
    if (m_cfg.ttsAddSpace && _speech.endsWith('.'))
        opts.append({"-w", _fileNameOut, ("'" + _speech + " '")});
    else
        opts.append({"-w", _fileNameOut, ("'" + _speech + "'")});

    QProcess process;
    process.start(m_cfg.ttsBin, opts, QIODevice::ReadOnly);
    if (!process.waitForFinished(-1))
    {
        std::cerr << "Error: " << m_cfg.ttsBin.toStdString() << " " << opts.join(" ").toStdString() << std::endl;
        return false;
    }

    const QString e = process.readAllStandardError();
    if (!e.isEmpty())
    {
        std::cerr << "Error: " << m_cfg.ttsBin.toStdString() << " " << e.toStdString() << std::endl;
        return false;
    }

    return true;
}

uint64_t Universe1::Video::Config::getAudioDuration(const QString &_fileName) const
{
    const QStringList opts = {
        "-v", "error", "-show_entries", "format=duration", "-of", "default=noprint_wrappers=1:nokey=1", _fileName};
    QProcess process;
    process.start("/usr/bin/ffprobe", opts, QIODevice::ReadOnly);
    if (!process.waitForFinished(-1))
    {
        std::cerr << "Error: ffprobe " << opts.join(" ").toStdString() << std::endl;
        return 0UL;
    }

    const QString e = process.readAllStandardError();
    if (!e.isEmpty())
    {
        std::cerr << "Error: ffprobe: " << e.toStdString() << std::endl;
        return 0UL;
    }

    return static_cast<uint64_t>(process.readAll().toDouble() * 1000.0);
}

bool Universe1::Video::Config::connectAudio(const QString &_fileNameOut, const QStringList &_files) const
{
    QStringList allFiles = _files;
    allFiles.push_back(_fileNameOut);

    QProcess process;
    process.start("/usr/bin/sox", allFiles, QIODevice::ReadOnly);
    if (!process.waitForFinished(-1))
    {
        std::cerr << "Error: sox " << allFiles.join(" ").toStdString() << std::endl;
        return false;
    }

    const QString e = process.readAllStandardError();
    if (!e.isEmpty())
    {
        std::cerr << "Error: sox connect: " << e.toStdString() << std::endl;
        return false;
    }

    return true;
}

bool Universe1::Video::Config::normalizeAudio(const QString &_fileNameOut, const QString &_fileNameIn) const
{
    if (m_cfg.audioNormalize < 0.001)
        return true;

    const QStringList opts = {"-v", QString::number(m_cfg.audioNormalize), _fileNameIn, _fileNameOut};
    QProcess process;
    process.start("/usr/bin/sox", opts, QIODevice::ReadOnly);
    if (!process.waitForFinished(-1))
    {
        std::cerr << "Error: sox normalize: " << opts.join(" ").toStdString() << std::endl;
        return false;
    }

    const QString e = process.readAllStandardError();
    if (!e.isEmpty())
    {
        std::cerr << "Error: sox normalize: " << e.toStdString() << std::endl;
        return false;
    }

    return true;
}

bool Universe1::Video::Config::createIndex(const QStringList &_imageFiles) const
{
    const QString file = m_cfg.outPath + m_cfg.dirImages + fileIndex;
    QFile iFile(file);
    if (!iFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Error: Can't create index file: " << file.toStdString() << std::endl;
        return EXIT_FAILURE;
    }
    QTextStream ts(&iFile);
    const float iDur = static_cast<float>(m_cfg.frameDuration) / 1000.0f;
    for (const QString &_fn : _imageFiles)
        ts << "file '" << _fn << "'\nduration " << iDur << "\n";
    ts << "file '" << _imageFiles.back() << "'\n";
    iFile.flush();
    iFile.close();
    return true;
}

bool Universe1::Video::Config::createVideo() const
{
    QStringList opts;
    opts << "-y"
         << "-f"
         << "concat"
         << "-safe"
         << "0";

    if (m_cfg.threads != 1U)
        opts << "-threads"
             << "0";

    opts << "-i" << (m_cfg.outPath + m_cfg.dirImages + m_cfg.fileIndex);
    opts << "-i" << (m_cfg.outPath + m_cfg.outFileName + "." + m_cfg.suffixAudio);

    opts << "-c:v"
         << "libx264";

    opts << "-vsync"
         << "vfr";

    opts << "-pix_fmt"
         << "yuv420p";

    opts << "-c:a"
         << "aac"
         << "-b:a" << audioKhzShorcut;

    opts << "-i" << (m_cfg.outPath + m_cfg.outFileName + "." + m_cfg.suffixVideo);

    const QDateTime bt = QDateTime::currentDateTime();
    QProcess process;
    process.start("/usr/bin/ffmpeg", opts, QIODevice::ReadOnly);

    if (m_cfg.verbose)
        std::cout << "*****************  ffmpeg ... " << std::endl;

    if (!process.waitForFinished(-1))
    {
        std::cerr << "Error: ffmpeg " << opts.join(" ").toStdString() << std::endl;
        return false;
    }

    const QString result = process.readAll();
    if (m_cfg.verbose)
    {
        const QTime tt = QTime::fromMSecsSinceStartOfDay(bt.msecsTo(QDateTime::currentDateTime()));
        std::cout << "*****************  ffmpeg " << tt.toString("h:m:ss.zzz").toStdString() << ": "
                  << result.toStdString() << std::endl;
    }

    return true;
}

std::vector<std::pair<uint64_t, uint64_t>> Universe1::Video::Config::createPool(const uint64_t _count) const
{
    uint poolSize = (threads == 0 ? std::thread::hardware_concurrency() : threads);

    if (poolSize <= 1UL || _count <= 1UL)
        return {};

    std::vector<std::pair<uint64_t, uint64_t>> result;
    if (_count <= poolSize)
    {
        result.reserve(_count);
        for (uint64_t i = 0UL; i < _count; ++i)
            result.push_back({i, 1UL});
    }
    else
    {
        result.reserve(poolSize);
        uint64_t i = 0UL, vc2 = _count, tc2 = poolSize;
        while (tc2 != 0U)
        {
            const uint64_t io = ((vc2 % tc2) == 0UL ? 0UL : 1UL) + vc2 / tc2;
            result.push_back({i, io});
            i += io;
            vc2 -= io;
            --tc2;
        }
    }
    return result;
}
