/*!
 * \file src/Audio/scenarioaudio.h
 * \brief Scenario for audio layer
 */

#ifndef AUDIO_SCENARIOAUDIO_H
#define AUDIO_SCENARIOAUDIO_H

#include "settingsaudio.h"
#include "itemaudio.h"

#include <map>

namespace U1 {
namespace Audio {

/*! \brief Scenario for audio layer */
class ScenarioAudio
{
 public:
    const std::string name;  //!< Scenario name

 protected:
    std::map<size_t, ItemAudio> m_items = {};  //!< Audio items

 public:
    /*!
     * \brief Constructor
     * \param _name Scenario name
     */
    inline ScenarioAudio(const std::string &_name)
        : name(_name)
    {
    }

    /*!
     * \brief Audio items getter
     * \return Audio items
     */
    inline const std::map<size_t, ItemAudio> &items() const
    {
        return m_items;
    }

    /*!
     * \brief Return latest active time-step
     * \return Latest active time-step
     */
    size_t latestTimeStep() const;

    /*!
     * \brief Test if subtitles are displayed at given time-step
     * \param _timeStep Time step
     * \return \c true if subtitles are displayed at given time-step
     */
    bool isVisible(const size_t _timeStep) const;

    /*!
     * \brief Return subtitles at given time-step
     * \param _timeStep Time step
     * \return Subtitles at given time-step
     */
    QString subs(const size_t _timeStep) const;

    /*!
     * \brief Append audio to this scenario
     * \param _timeStart Start time step
     * \param _fileName Audio file name
     * \param _subs Subtitles
     * \param _offsetSubs Subtitles overlay duration
     * \return Success flag
     */
    bool
    insertAudio(const size_t _timeStart, const QString &_fileName, const QString &_subs, const size_t _offsetSubs = 0U);

    /*!
     * \brief Append audio to the end of this scenario
     * \param _timeWait Time wait after latest active time-step
     * \param _fileName Audio file name
     * \param _subs Subtitles
     * \param _offsetSubs Subtitles overlay duration
     * \return Success flag
     */
    inline bool
    addAudio(const size_t _timeWait, const QString &_fileName, const QString &_subs, const size_t _offsetSubs = 0U)
    {
        return insertAudio(latestTimeStep() + _timeWait, _fileName, _subs, _offsetSubs);
    }

    /*!
     * \brief Create audio file from audio samples
     * \param _settings Audio settings
     * \param _workDir Working directory
     * \param _fileName Output file name
     * \param _latestTimeStep Latest time step (total length of generated audio file)
     * \return Success flag
     */
    virtual bool createAudio(const SettingsAudio &_settings,
                             const QString &_workDir,
                             const QString &_fileName,
                             const size_t _latestTimeStep) const;
};

/*! \brief Audio scenario with text-to-speech engine*/
class ScenarioAudioTTS : public ScenarioAudio
{
 public:
    const QString workDir;      //!< Working directory for generated speech audio files
    const QString ttsBin;       //!< Text-to-speech external program
    const QString ttsArgFile;   //!< Argument name for output file
    const QString fileSuffix;   //!< Default audio file suffix for generated speech
    const QStringList ttsArgs;  //!< Additional arguments for text-to-speech program
    const bool addSpace;        //!< Keep single space character at the end of speech text
    const bool doubleQuotes;    //!< Flag that defines if text-to-speech program uses double quotes for speech text
    const size_t ttsHash;       //!< Text-to-speech setting hash value

    /*!
     * \brief Constructor
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _ttsBin Text-to-speech external program
     * \param _ttsArgFile Argument name for output file
     * \param _fileSuffix Default audio file suffix for generated speech
     * \param _ttsArgs Additional arguments for text-to-speech program
     * \param _addSpace Keep single space character at the end of speech text
     * \param _doubleQuotes Flag that defines if text-to-speech program uses double quotes for speech text
     */
    ScenarioAudioTTS(const std::string &_name,
                     const QString &_workDir,
                     const QString &_ttsBin,
                     const QString &_ttsArgFile,
                     const QString &_fileSuffix,
                     const QStringList &_ttsArgs,
                     const bool _addSpace = false,
                     const bool _doubleQuotes = false);

    /*!
     * \brief Append speech audio to this scenario
     * \param _timeStart Start time step
     * \param _speechText Speech text
     * \param _subs Subtitles
     * \param _offsetSubs Subtitles overlay duration
     * \return Success flag
     */
    bool insertSpeech(const size_t _timeStart,
                      const QString &_speechText,
                      const QString &_subs,
                      const size_t _offsetSubs = 0U);

    /*!
     * \brief Append speech audio to the end of this scenario
     * \param _timeWait Time wait after latest active time-step
     * \param _speechText Speech text
     * \param _subs Subtitles
     * \param _offsetSubs Subtitles overlay duration
     * \return Success flag
     */
    inline bool
    addSpeech(const size_t _timeWait, const QString &_speechText, const QString &_subs, const size_t _offsetSubs = 0U)
    {
        return insertSpeech(latestTimeStep() + _timeWait, _speechText, _subs, _offsetSubs);
    }

    /*!
     * \brief Create default \b espeak audio scenario
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _voice \b espeak voice (mb-us1, mb-us2, mb-us3)
     * \param _bin \b espeak binary
     * \return \b espeak audio scenario
     */
    inline static ScenarioAudioTTS *espeak(const std::string &_name,
                                           const QString &_workDir,
                                           const QString &_voice = "mb-us3",
                                           const QString &_bin = "/usr/bin/espeak")
    {
        return new ScenarioAudioTTS(_name, _workDir, _bin, "-w", "wav", {"-v", _voice}, true, false);
    }

    /*!
     * \brief Create default \b pico2wave audio scenario
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _lang \b pico2wave language (en-US)
     * \param _bin \b pico2wave binary
     * \return \b pico2wave audio scenario
     */
    inline static ScenarioAudioTTS *pico2wave(const std::string &_name,
                                              const QString &_workDir,
                                              const QString &_lang = "en-US",
                                              const QString &_bin = "/usr/bin/pico2wave")
    {
        return new ScenarioAudioTTS(_name, _workDir, _bin, "-w", "wav", {"-l", _lang}, false, false);
    }

    /*!
     * \brief Create default \b google_speech audio scenario
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _lang \b google_speech language (en-US)
     * \param _bin \b google_speech binary
     * \return \b google_speech audio scenario
     */
    inline static ScenarioAudioTTS *google_speech(const std::string &_name,
                                                  const QString &_workDir,
                                                  const QString &_lang = "en-US",
                                                  const QString &_bin = "~/.local/bin/google_speech")
    {
        return new ScenarioAudioTTS(_name, _workDir, _bin, "-o", "mp3", {"-l", _lang}, false, true);
    }
};

}  // namespace Audio
}  // namespace U1

#endif  // AUDIO_SCENARIOAUDIO_H
