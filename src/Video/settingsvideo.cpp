/*!
 * \file src/Video/settingsvideo.cpp
 * \brief General video settings
 */

#include "settingsvideo.h"

#include <iostream>

#include <QFontDatabase>
#include <QFile>

namespace U1 {
namespace Video {

QString SettingsVideo::ffmpegBin = "/usr/bin/ffmpeg";

bool SettingsOpenGL::isValid() const
{
    const bool result =         //
        useGlSamples == 0U ||   //
        useGlSamples == 1U ||   //
        useGlSamples == 2U ||   //
        useGlSamples == 4U ||   //
        useGlSamples == 8U ||   //
        useGlSamples == 16U ||  //
        useGlSamples == 32U;
    if (!result)
        std::cerr << "Invalid Open GL samples[" << useGlSamples << "], use [0|1|2|4|8|16|32]!\n";
    return result;
}

bool SettingsSubtitles::isValid() const
{
    if (!useSubtitles)
        return true;

    if (!QFontDatabase::families().contains(fontFamily))
    {
        std::cerr << "Invalid subs font[" << qPrintable(fontFamily) << "]!\n";
        return false;
    }

    const QList<int> tmpSizes = QFontDatabase::pointSizes(fontFamily);
    if (!tmpSizes.contains(int(fontHeight)))
    {
        if (tmpSizes.isEmpty())
        {
            std::cerr << "Invalid subs font[" << qPrintable(fontFamily) << "] sizes!\n";
            return false;
        }

        std::cerr << "Invalid subs font[" << qPrintable(fontFamily) << "] height[" << fontHeight << "], use["
                  << tmpSizes.front();
        for (qsizetype i = 1; i < tmpSizes.size(); ++i)
            std::cerr << '|' << tmpSizes.at(i);
        std::cerr << "]!\n";

        return false;
    }

    if (!fontColor.isValid())
    {
        std::cerr << "Invalid subs color!\n";
        return false;
    }

    return true;
}

bool SettingsSubtitles::setupFont(const QString &_fontFamily, const int _fontHeight, const uint _bottomOffset)
{
    if (!QFontDatabase::families().contains(_fontFamily))
    {
        std::cerr << "Error: Unknown font family: " << qPrintable(_fontFamily) << "!\n";
        return false;
    }

    const QList<int> validSizes = QFontDatabase::pointSizes(_fontFamily);
    if (validSizes.empty())
    {
        std::cerr << "Error: Invalid font family: " << qPrintable(_fontFamily) << "!\n";
        return false;
    }

    if (validSizes.contains(_fontHeight))
    {
        fontFamily = _fontFamily;
        fontHeight = uint(_fontHeight);
        bottomOffset = _bottomOffset;
        return true;
    }

    int fh = validSizes.front();
    int diff = std::abs(_fontHeight - fh);

    for (const int tmp : std::as_const(validSizes))
    {
        const int diff2 = std::abs(_fontHeight - tmp);
        if (diff > diff2)
        {
            diff = diff2;
            fh = tmp;
        }
    }

    fontFamily = _fontFamily;
    fontHeight = uint(fh);
    bottomOffset = _bottomOffset;

    std::cerr << "Warning: Invalid height(" << _fontHeight << ") for font " << qPrintable(_fontFamily)
              << "using: " << fh << "!\nSupported values: ";
    for (const int tmp : std::as_const(validSizes))
        std::cerr << tmp << ", ";
    std::cerr << '\n';

    return true;
}

bool SettingsVideo::isValid() const
{
    QString tmp;
    if (!Math::isAligned(resolution.width(), 640, 7680) || !Math::isAligned(resolution.height(), 480, 4320))
    {
        std::cerr << "Invalid video resolution!\n";
        return false;
    }

    if (!Math::isAligned(frameDuration, (100.0f / 6.0f), 40.0f))
    {
        std::cerr << "Invalid video frame duration[" << frameDuration << "]!\n";
        return false;
    }

    Audio::SettingsAudio::runProcess(ffmpegBin, {"-encoders"}, &tmp);
    if (!tmp.contains(' ' + videoCodec + ' '))
    {
        std::cerr << "Invalid video codec[" << qPrintable(videoCodec) << "]!\n";
        return false;
    }

    tmp.clear();
    Audio::SettingsAudio::runProcess(ffmpegBin, {"-pix_fmts"}, &tmp);
    if (!tmp.contains(' ' + videoPixelFormat + ' '))
    {
        std::cerr << "Invalid video pixel format[" << qPrintable(videoPixelFormat) << "]!\n";
        return false;
    }

    return true;
}

bool SettingsVideo::createVideo(const QString &_outFileName,
                                const Audio::SettingsAudio &_audioSettings,
                                const QString &_audioFileName,
                                const QStringList &_images,
                                const size_t _hash) const
{
    if (QFile::exists(_outFileName))
    {
        if (!QFile::remove(_outFileName))
        {
            std::cerr << "File already exists, can't remove: " << qPrintable(_outFileName) << "!\n";
            return false;
        }
    }

    const QString tmpFN = _outFileName + ".txt";
    QFile iFile(tmpFN);
    if (!iFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        std::cerr << "Can't create image index file!\n";
        return false;
    }

    QTextStream ts(&iFile);
    qsizetype i = 1;

    const float iDur = frameDuration / 1000.0f;
    for (const QString &f : std::as_const(_images))
    {
        ts << "file '" << f << "'\n";
        if (i != _images.size())
            ts << "duration " << iDur << "\n";
        ++i;
    }

    iFile.flush();
    iFile.close();

    QStringList args = {"-y", "-f", "concat", "-safe", "0", "-threads", "0", "-i", tmpFN};
    if (!_audioFileName.isEmpty())
        args << "-i" << _audioFileName;
    args << "-c:v" << videoCodec;
    args << "-vsync";
    args << "vfr";
    args << "-pix_fmt" << videoPixelFormat;

    if (!_audioFileName.isEmpty())
    {
        args << "-c:a";
        args << "aac";
        args << "-ac" << QString::number(_audioSettings.channels);
        args << "-ar" << QString::number(_audioSettings.sampleRate);
    }

    if (_hash > 0UL)
    {
        args << "-metadata";
        args << "comment=\"" + QString::number(_hash) + "\"";
    }

    args << _outFileName;

    Audio::SettingsAudio::runProcess(ffmpegBin, args);

    QFile::remove(tmpFN);

    return QFile::exists(_outFileName);
}

}  // namespace Video
}  // namespace U1
