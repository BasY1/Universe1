/*!
 * \file src/Audio/footageaudio.cpp
 * \brief Footage audio tools
 */

#include "footageaudio.h"

#include <QFile>
#include <QDir>

#include <iostream>

namespace U1 {
namespace Audio {

FootageAudio::~FootageAudio()
{
    for (ScenarioAudio *a : m_audio)
        delete a;
}

QString FootageAudio::subs(const size_t _timeStep) const
{
    QStringList result;
    for (const ScenarioAudio *const &as : std::as_const(m_audio))
    {
        const QString tmp = as->subs(_timeStep);
        if (!tmp.isEmpty())
            result.push_back(tmp);
    }
    return result.join("<BR/>");
}

bool FootageAudio::createAudio(const SettingsAudio &_settings,
                               const QString &_workDir,
                               const QString &_fileName,
                               const size_t _latestTimeStep) const
{
    if (QFile::exists(_fileName))
    {
        if (!QFile::remove(_fileName))
        {
            std::cerr << "AudioError: Can't remove old audio file:" << qPrintable(_fileName) << "!\n";
            return false;
        }
    }

    if (m_audio.empty())
    {
        if (_latestTimeStep == 0UL)
        {
            std::cerr << "AudioError: No audio track in this footage!\n";
            return false;
        }

        return _settings.createSilenceAudio(_fileName, _latestTimeStep);
    }

    if (QDir(_workDir).exists())
    {
        if (!QDir(_workDir).removeRecursively())
        {
            std::cerr << "AudioError: Can't remove workDir:" << qPrintable(_workDir) << "!\n";
            return false;
        }
    }

    if (!QDir().mkpath(_workDir))
    {
        std::cerr << "AudioError: Can't create workDir:" << qPrintable(_workDir) << "!\n";
        return false;
    }

    QStringList trackFiles;
    uint idx = 1U;
    for (const ScenarioAudio *const &as : std::as_const(m_audio))
    {
        const QString trackFileName = _workDir + "track_" + QString::number(idx) + "_." + _settings.fileSuffix;
        const QString trackDir = _workDir + "data_" + QString::number(idx) + "_" + QDir::separator();
        if (!QDir().mkpath(trackDir))
        {
            std::cerr << "AudioError: Can't create working directory:" << qPrintable(trackDir) << "!\n";
            return false;
        }

        if (!as->createAudio(_settings, trackDir, trackFileName, _latestTimeStep))
            return false;

        trackFiles << trackFileName;
        idx++;
    }

    if (trackFiles.size() == 1UL)
    {
        if (!_settings.normalizeAudio(_fileName, trackFiles[0]))
        {
            std::cerr << "AudioError: Can't normalize audio!\n";
            return false;
        }
        return true;
    }

    const QString fnBase = _workDir + "audio_base." + _settings.fileSuffix;
    if (!_settings.mixAudioFiles(fnBase, trackFiles))
    {
        std::cerr << "AudioError: Can't mix audio files!\n";
        return false;
    }

    if (!_settings.normalizeAudio(_fileName, fnBase))
    {
        std::cerr << "AudioError: Can't normalize audio!\n";
        return false;
    }

    return true;
}

}  // namespace Audio
}  // namespace U1

