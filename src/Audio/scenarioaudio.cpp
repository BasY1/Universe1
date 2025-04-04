/*!
 * \file src/Audio/scenarioaudio.cpp
 * \brief Scenario for audio layer
 */

#include "scenarioaudio.h"

#include "../Math/type.h"

#include <iostream>

#include <QDir>
#include <QFileInfo>

namespace U1 {
namespace Audio {

size_t ScenarioAudio::latestTimeStep() const
{
    return m_items.empty() ? 0UL : (*m_items.crbegin()).second.latestTimeStep();
}

bool ScenarioAudio::isVisible(const size_t _timeStep) const
{
    if (m_items.empty())
        return false;

    typename std::map<size_t, ItemAudio>::const_iterator it = m_items.lower_bound(_timeStep);
    if (it == m_items.cend())
    {
        const ItemAudio &last = (*m_items.crbegin()).second;
        if (last.isActive(_timeStep))
            return !last.subs.isEmpty();
        return false;
    }

    if ((*it).second.isActive(_timeStep))
        return !(*it).second.subs.isEmpty();

    if (it == m_items.cbegin())
        return false;

    it--;

    if ((*it).second.isActive(_timeStep))
        return !(*it).second.subs.isEmpty();

    return false;
}

QString ScenarioAudio::subs(const size_t _timeStep) const
{
    if (m_items.empty())
        return "";

    typename std::map<size_t, ItemAudio>::const_iterator it = m_items.lower_bound(_timeStep);
    if (it == m_items.cend())
    {
        const ItemAudio &last = (*m_items.crbegin()).second;
        if (last.isActive(_timeStep))
            return last.subs;
        return "";
    }

    if ((*it).second.isActive(_timeStep))
        return (*it).second.subs;

    if (it == m_items.cbegin())
        return "";

    it--;

    if ((*it).second.isActive(_timeStep))
        return (*it).second.subs;

    return "";
}

bool ScenarioAudio::insertAudio(const size_t _timeStart,
                                const QString &_fileName,
                                const QString &_subs,
                                const size_t _offsetSubs)
{
    if (!m_items.empty())
    {
        if ((*m_items.crbegin()).second.latestTimeStep() > _timeStart)
        {
            std::cerr << "ScenarioAudio[" << name << "]::insertAudio(" << _timeStart << "," << qPrintable(_fileName)
                      << "): Can't insert, minimal start time=" << (*m_items.crbegin()).second.latestTimeStep()
                      << "!\n";
            return false;
        }
    }

    if (!QFile::exists(_fileName))
    {
        std::cerr << "ScenarioAudio[" << name << "]::insertAudio(" << _timeStart << "," << qPrintable(_fileName)
                  << "): Audio file not exist!\n";
        return false;
    }

    const size_t audioDuration = SettingsAudio::readAudioFileDuration(_fileName);
    if (audioDuration == 0UL)
    {
        std::cerr << "ScenarioAudio[" << name << "]::insertAudio(" << _timeStart << "," << qPrintable(_fileName)
                  << "): Invalid audio file!\n";
        return false;
    }

    m_items.insert({_timeStart, {_fileName, _subs, _timeStart, _offsetSubs, audioDuration}});
    return true;
}

bool ScenarioAudio::createAudio(const SettingsAudio &_settings,
                                const QString &_workDir,
                                const QString &_fileName,
                                const size_t _latestTimeStep) const
{
    QStringList files;
    QString fn;
    size_t tt = 0UL;
    for (const std::pair<const size_t, ItemAudio> &ai : std::as_const(m_items))
    {
        if (ai.second.timeStart > tt)
        {
            fn = _workDir + "audio_" + QString::number(files.size() + 1) + "_s." + _settings.fileSuffix;
            if (!_settings.createSilenceAudio(fn, ai.second.timeStart - tt))
            {
                std::cerr << "ScenarioAudio[" << name << "]: Can't create silence audio!\n";
                return false;
            }
            files.push_back(fn);
        }

        fn = _workDir + "audio_" + QString::number(files.size() + 1) + "_." + _settings.fileSuffix;
        if (!_settings.convertAudio(fn, ai.second.fileName))
        {
            std::cerr << "ScenarioAudio[" << name << "]: Can't convert audio:" << qPrintable(ai.second.fileName)
                      << "!\n";
            return false;
        }
        files.push_back(fn);

        tt = ai.second.timeStart + ai.second.audioDuration;
    }

    if (tt < _latestTimeStep)
    {
        fn = _workDir + "audio_" + QString::number(files.size() + 1) + "_s." + _settings.fileSuffix;
        if (!_settings.createSilenceAudio(fn, _latestTimeStep - tt))
        {
            std::cerr << "ScenarioAudio[" << name << "]: Can't create silence audio!\n";
            return false;
        }

        files.push_back(fn);
    }

    if (!_settings.joinAudioFiles(_fileName, files))
    {
        std::cerr << "ScenarioAudio[" << name << "]: Can't join audio files!\n";
        return false;
    }
    return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Tool function calculate hash value for TTS setup
 * \param _ttsBin Text-to-speech external program
 * \param _ttsArgFile Argument name for output file
 * \param _fileSuffix Default audio file suffix for generated speech
 * \param _ttsArgs Additional arguments for text-to-speech program
 * \param _addSpace Keep single space character at the end of speech text
 * \param _doubleQuotes Flag that defines if text-to-speech program uses double quotes for speech text
 * \return Text-to-speech hash
 */
inline static size_t mixHashTTS(const QString &_ttsBin,
                                const QString &_ttsArgFile,
                                const QString &_fileSuffix,
                                const QStringList &_ttsArgs,
                                const bool _addSpace,
                                const bool _doubleQuotes)
{
    size_t o = 1UL,
           result = Math::mixHash(Math::mixTextHash(_ttsBin),
                                  Math::mixTextHash(_fileSuffix),
                                  std::hash<bool>{}(_addSpace),
                                  std::hash<bool>{}(_doubleQuotes));
    if (!_ttsArgFile.isEmpty())
        Math::updateHash(result, o, Math::mixTextHash(_ttsArgFile));

    if (!_ttsArgs.isEmpty())
        Math::updateHash(result, o, Math::mixTextHash(_ttsArgs));

    return result;
}

ScenarioAudioTTS::ScenarioAudioTTS(const std::string &_name,
                                   const QString &_workDir,
                                   const QString &_ttsBin,
                                   const QString &_ttsArgFile,
                                   const QString &_fileSuffix,
                                   const QStringList &_ttsArgs,
                                   const bool _addSpace,
                                   const bool _doubleQuotes)
    : ScenarioAudio(_name)
    , workDir(_workDir)
    , ttsBin(_ttsBin)
    , ttsArgFile(_ttsArgFile)
    , fileSuffix(_fileSuffix)
    , ttsArgs(_ttsArgs)
    , addSpace(_addSpace)
    , doubleQuotes(_doubleQuotes)
    , ttsHash(mixHashTTS(_ttsBin, _ttsArgFile, _fileSuffix, _ttsArgs, _addSpace, _doubleQuotes))
{
}

bool ScenarioAudioTTS::insertSpeech(const size_t _timeStart,
                                    const QString &_speechText,
                                    const QString &_subs,
                                    const size_t _offsetSubs)
{
    const QChar quote = doubleQuotes ? '"' : '\'';
    const QString speechText =
        (addSpace && (_speechText.endsWith('.') || _speechText.endsWith('?') || _speechText.endsWith('!')))
        ? ((quote + _speechText + ' ' + quote))
        : (quote + _speechText + quote);

    const size_t h = Math::mixHash(ttsHash, Math::mixTextHash(speechText));
    const QString fn = workDir + "tts_" + QString::number(h) + "." + fileSuffix;

    if (QFile::exists(fn))
        return insertAudio(_timeStart, fn, _subs, _offsetSubs);

    QStringList args = ttsArgs;
    if (!ttsArgFile.isEmpty())
        args << ttsArgFile;
    args << fn;

    args << speechText;

    SettingsAudio::runProcess(ttsBin, args);

    if (!QFile::exists(fn))
    {
        std::cerr << "ScenarioAudioTTS[" << name << "]::insertSpeech(" << _timeStart << "," << qPrintable(_speechText)
                  << "): Audio file not exist!\n";
        return false;
    }

    return insertAudio(_timeStart, fn, _subs, _offsetSubs);
}

}  // namespace Audio
}  // namespace U1
