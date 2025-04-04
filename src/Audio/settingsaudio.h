/*!
 * \file src/Audio/settingsaudio.h
 * \brief General audio settings
 */

#ifndef AUDIO_SETTINGSAUDIO_H
#define AUDIO_SETTINGSAUDIO_H

#include <QAudioFormat>

namespace U1 {

/*!
 * \namespace U1::Audio
 * \brief Audio tools
 */
namespace Audio {

// {8000, tr("Lowest-quality: human speech but without sibilance")},
// {11025, tr("Lower-quality: subwoofer bandpasses")},
// {16000, tr("VoIP-quality")},
// {22050, tr("Lower-quality audio")},
// {44100, tr("Audio CD quality")},
// {48000, tr("Digital video equipment")},
// {88200, tr("Mixer/Equaliser CD quality")},
// {176400, tr("Audio HDCD quality")},
// {192000, tr("Audio DVD, Blu-ray quality")},
// {352800, tr("Digital eXtreme Definition")},
// {384000, tr("Highest sample rate available")},

/*!
 * \brief General audio settings
 * \details
 * - Supported channels: 1, 2
 * - Supported audio formats: 8000, 11025, 16000, 22050, 44100, 48000, 88200, 176400, 192000, 352800, 384000
 */
struct SettingsAudio
{
    uint channels = 1;                                              //!< Audio channel count
    uint sampleRate = 44100;                                        //!< Sample rate
    QAudioFormat::SampleFormat sampleFormat = QAudioFormat::Int16;  //!< Sample format
    QString fileSuffix = "wav";                                     //!< Default audio file suffix

    /*!
     * \brief Arguments for \c sox audio tools
     * \return Arguments for \c sox audio tools
     */
    inline QStringList soxArgs() const
    {
        static const QString ui = "unsigned-integer";
        static const QString si = "signed-integer";
        static const QString fp = "floating-point";
        switch (sampleFormat)
        {
        case QAudioFormat::UInt8:
            return {"-c", QString::number(channels), "-r", QString::number(sampleRate), "-b", "8", "-e", ui};
        case QAudioFormat::Int16:
            return {"-c", QString::number(channels), "-r", QString::number(sampleRate), "-b", "16", "-e", si};
        case QAudioFormat::Int32:
            return {"-c", QString::number(channels), "-r", QString::number(sampleRate), "-b", "32", "-e", si};
        case QAudioFormat::Float: return {"-c", QString::number(channels), "-r", QString::number(sampleRate), "-e", fp};
        case QAudioFormat::Unknown:
        case QAudioFormat::NSampleFormats: break;
        }
        return {};
    }

    /*!
     * \brief Test audio settings
     * \return \c when audio settings are valid
     */
    bool isValid() const;

    /*!
     * \brief Create silence audio using \b sox
     * \param _outFileName Output file name
     * \param _duration Silence duration in milliseconds
     * \return Success flag
     */
    bool createSilenceAudio(const QString &_outFileName, const size_t _duration) const;

    /*!
     * \brief Convert audio file using \b sox
     * \param _outFileName Output file name
     * \param _fromFile Input file name
     * \return Success flag
     */
    bool convertAudio(const QString &_outFileName, const QString &_fromFile) const;

    /*!
     * \brief Normalize audio file using \b sox
     * \param _outFileName Output file name
     * \param _fromFile Input file name
     * \return Success flag
     */
    bool normalizeAudio(const QString &_outFileName, const QString &_fromFile) const;

    /*!
     * \brief Join audio files using \b sox
     * \param _outFileName Output file name
     * \param _files Files to join
     * \return Success flag
     */
    bool joinAudioFiles(const QString &_outFileName, const QStringList &_files) const;

    /*!
     * \brief Mix audio files using \b sox
     * \param _outFileName Output file name
     * \param _files Files to mix
     * \return Success flag
     */
    bool mixAudioFiles(const QString &_outFileName, const QStringList &_files) const;

    /*!
     * \brief Get audio file duration in milliseconds using \b soxi
     * \param _fileName File name
     * \return File duration (or 0 when audio file is invalid)
     */
    static size_t readAudioFileDuration(const QString &_fileName);

    /*!
     * \brief Run process
     * \param _bin file to execute
     * \param _args Arguments
     * \param _outData Output text
     * \return Error text
     */
    static QString runProcess(const QString &_bin, const QStringList &_args, QString *_outData = nullptr);
};

}  // namespace Audio
}  // namespace U1

#endif  // AUDIO_SETTINGSAUDIO_H
