/*!
 * \file src/Audio/footageaudio.h
 * \brief Footage audio tools
 */

#ifndef AUDIO_FOOTAGEAUDIO_H
#define AUDIO_FOOTAGEAUDIO_H

#include "scenarioaudio.h"

namespace U1 {
namespace Audio {

/*! \brief Footage audio tools */
struct FootageAudio
{
 protected:
    std::vector<ScenarioAudio *> m_audio = {};  //!< Audio scenarios

 public:
    /*!
     * \brief Latest active time-step of all audio scenarios
     * \return Latest active time-step of all audio scenarios
     */
    inline size_t latestAudioTimeStep() const
    {
        size_t result = 0UL;
        for (const ScenarioAudio *const &as : std::as_const(m_audio))
            result = std::max(result, as->latestTimeStep());
        return result;
    }

    /*!
     * \brief Add audio scenario
     * \param _name Audio scenario name
     * \return Constructed audio scenario object
     */
    inline ScenarioAudio *addAudio(const std::string &_name)
    {
        ScenarioAudio *result = new ScenarioAudio(_name);
        m_audio.push_back(result);
        return result;
    }

    /*!
     * \brief Add text-to-speech audio scenario
     * \param _name Audio scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _ttsBin Text-to-speech external program
     * \param _ttsArgFile Argument name for output file
     * \param _fileSuffix Default audio file suffix for generated speech
     * \param _ttsArgs Additional arguments for text-to-speech program
     * \param _addSpace Keep single space character at the end of speech text
     * \param _doubleQuotes Flag that defines if text-to-speech program uses double quotes for speech text
     * \return Constructed text-to-speech audio scenario object
     */
    inline ScenarioAudioTTS *addAudioTTS(const std::string &_name,
                                         const QString &_workDir,
                                         const QString &_ttsBin,
                                         const QString &_ttsArgFile,
                                         const QString &_fileSuffix,
                                         const QStringList &_ttsArgs,
                                         const bool _addSpace = false,
                                         const bool _doubleQuotes = false)
    {
        ScenarioAudioTTS *result = new ScenarioAudioTTS(
            _name, _workDir, _ttsBin, _ttsArgFile, _fileSuffix, _ttsArgs, _addSpace, _doubleQuotes);
        m_audio.push_back(result);
        return result;
    }

    /*!
     * \brief Create and add default \b espeak audio scenario
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _voice \b espeak voice (mb-us1, mb-us2, mb-us3)
     * \param _bin \b espeak binary
     * \return \b espeak audio scenario
     */
    inline ScenarioAudioTTS *addAudio_espeak(const std::string &_name,
                                             const QString &_workDir,
                                             const QString &_voice = "mb-us3",
                                             const QString &_bin = "/usr/bin/espeak")
    {
        ScenarioAudioTTS *result = ScenarioAudioTTS::espeak(_name, _workDir, _voice, _bin);
        m_audio.push_back(result);
        return result;
    }

    /*!
     * \brief Create and add default \b pico2wave audio scenario
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _lang \b pico2wave language (en-US)
     * \param _bin \b pico2wave binary
     * \return \b pico2wave audio scenario
     */
    inline ScenarioAudioTTS *addAudio_pico2wave(const std::string &_name,
                                                const QString &_workDir,
                                                const QString &_lang = "en-US",
                                                const QString &_bin = "/usr/bin/pico2wave")
    {
        ScenarioAudioTTS *result = ScenarioAudioTTS::pico2wave(_name, _workDir, _lang, _bin);
        m_audio.push_back(result);
        return result;
    }

    /*!
     * \brief Create and add default \b google_speech audio scenario
     * \param _name Scenario name
     * \param _workDir Working directory for generated speech audio files
     * \param _lang \b google_speech language (en-US)
     * \param _bin \b google_speech binary
     * \return \b google_speech audio scenario
     */
    inline ScenarioAudioTTS *addAudio_google_speech(const std::string &_name,
                                                    const QString &_workDir,
                                                    const QString &_lang = "en-US",
                                                    const QString &_bin = "~/.local/bin/google_speech")
    {
        ScenarioAudioTTS *result = ScenarioAudioTTS::google_speech(_name, _workDir, _lang, _bin);
        m_audio.push_back(result);
        return result;
    }

    /*!
     * \brief Create audio - mix all audio scenarios
     * \param _settings Audio settings
     * \param _workDir Working directory for temporary audio files
     * \param _fileName Output file name
     * \param _latestTimeStep Latest time step (total audio duration in milliseconds)
     * \return Success flag
     */
    bool createAudio(const SettingsAudio &_settings,
                     const QString &_workDir,
                     const QString &_fileName,
                     const size_t _latestTimeStep) const;
};

}  // namespace Audio
}  // namespace U1

#endif  // AUDIO_FOOTAGEAUDIO_H
