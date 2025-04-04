/*!
 * \file src/Audio/settingsaudio.cpp
 * \brief General audio settings
 */

#include "settingsaudio.h"

#include <iostream>

#include <QFile>
#include <QProcess>

namespace U1 {
namespace Audio {

bool SettingsAudio::isValid() const
{
    if (channels != 1 && channels != 2)
    {
        std::cerr << "Invalid audio channels[" << channels << "], use [1|2]!\n";
        return false;
    }

    if (sampleRate != 8000U &&    //
        sampleRate != 11025U &&   //
        sampleRate != 16000U &&   //
        sampleRate != 22050U &&   //
        sampleRate != 44100U &&   //
        sampleRate != 48000U &&   //
        sampleRate != 88200U &&   //
        sampleRate != 176400U &&  //
        sampleRate != 192000U &&  //
        sampleRate != 352800U &&  //
        sampleRate != 384000U)
    {
        std::cerr << "Invalid audio sample rate[" << sampleRate
                  << "], use [8000|11025|16000|22050|44100|48000|88200|176400|192000|352800|384000]!\n";
        return false;
    }

    if (sampleFormat == QAudioFormat::Unknown || sampleFormat == QAudioFormat::NSampleFormats)
    {
        std::cerr << "Invalid audio sample format!\n";
        return false;
    }

    return true;
}

bool SettingsAudio::createSilenceAudio(const QString &_audioFileName, const size_t _duration) const
{
    QStringList args;
    args << "-n";
    args << soxArgs();
    args << _audioFileName;
    args << "trim";
    args << "0.0";
    args << QString::number(static_cast<float>(_duration) / 1000.0f, 'f', 3);
    runProcess("usr/bin/sox", args);
    return QFile::exists(_audioFileName);
}

bool SettingsAudio::convertAudio(const QString &_toFileName, const QString &_fromFileName) const
{
    QStringList args = {_fromFileName};
    args << soxArgs();
    args << _toFileName;
    runProcess("usr/bin/sox", args);
    return QFile::exists(_toFileName);
}

bool SettingsAudio::normalizeAudio(const QString &_toFileName, const QString &_fromFileName) const
{
    runProcess("usr/bin/sox", {"--norm", _fromFileName, _toFileName});
    return QFile::exists(_toFileName);
}

bool SettingsAudio::joinAudioFiles(const QString &_toFileName, const QStringList &_fromFileName) const
{
    QStringList args = {_fromFileName};
    args << _toFileName;
    runProcess("usr/bin/sox", args);
    return QFile::exists(_toFileName);
}

bool SettingsAudio::mixAudioFiles(const QString &_toFileName, const QStringList &_fromFileName) const
{
    QStringList args = {"-m"};
    args << _fromFileName;
    args << _toFileName;
    runProcess("usr/bin/sox", args);
    return QFile::exists(_toFileName);
}

size_t SettingsAudio::readAudioFileDuration(const QString &_audioFileName)
{
    QString scriptText;

    const QStringList args = {"-DT", _audioFileName};
    const QString scriptError = runProcess("usr/bin/soxi", args, &scriptText);
    if (!scriptText.isEmpty())
    {
        bool ok;
        const double value = scriptText.toDouble(&ok);
        if (!ok)
            return 0UL;

        return static_cast<size_t>(value * 1000.0);
    }

    if (scriptError.isEmpty())
        std::cerr << "Error soxi " << qPrintable(_audioFileName) << '\n';
    else
        std::cerr << "soxi " << qPrintable(_audioFileName) << "\nError: " << qPrintable(scriptError) << '\n';

    return 0UL;
}

QString SettingsAudio::runProcess(const QString &_bin, const QStringList &_args, QString *_outData)
{
    QProcess process;
    process.start(_bin, _args, QIODevice::ReadOnly);
    if (!process.waitForFinished(-1))
        return QObject::tr("Error exec: %1 %2").arg(_bin, _args.join(" "));

    const QString stdError = process.readAllStandardError();

    if (_outData != nullptr)
        *_outData = process.readAll();

    return stdError;
}

}  // namespace Audio
}  // namespace U1
