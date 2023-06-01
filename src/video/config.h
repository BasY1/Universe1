#ifndef UNIVERSE1_VIDEO_CONFIG_H
#define UNIVERSE1_VIDEO_CONFIG_H

#include "material.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Configuration structure
 * \details Contains speech and silence audio database
 */
struct Config
{
    // clang-format off
    /*!
     * \brief Export level
     * \details
     * | Value | Screen size | Accuracy | GL samples | Font height (Subs, 2D, 3D)| Border offset (Side, Subs) | Quality (line, sphere) |
     * | :---- | :---------: | :------: | :--------: | :-----------------------: | :------------------------: | :--------------------: |
     * | 1     | 1920 x 1080 | 0.1      | 4          | 20, 20, 40 (0.0025)       | 40, 150                    | 1, 7                   |
     * | 2     | 3840 x 2160 | 0.01     | 8          | 36, 36, 50 (0.002)        | 60, 200                    | 3, 15                  |
     * | 3     | 3840 x 2160 | 0.001    | 16         | 36, 36, 100 (0.001)       | 60, 200                    | 7, 31                  |
     * | other | 1024 x 576  | 0.1      | 0          | 12, 16, 20 (0.005)        | 20, 100                    | 0, 3                   |
     */
    uint level;
    // clang-format on

    uint threads;         //!< Multi-thread support, thread count (0 = auto-detect, 1= single thread)
    QString outPath;      //!< Output directory
    QString outFileName;  //!< Output file name (without suffix)

    bool showGui = true;  //!< Show GUI before rendering
    bool verbose = true;  //!< Log to console
    bool addSubs = true;  //!< Show subtitles in video

    QString fileIndex = "index.txt";     //!< Index file with list of images and timings for ffmpeg
    QString fileSubsHtml = "subs.html";  //!< Output subtitle as HTML file

    QString dirSpeech = QString("speech") + QDir::separator();  //!< Directory name for speech and silence database
    QString dirImages = QString("images") + QDir::separator();  //!< Directory name for temporary images
    QString dirAudio = QString("audio") + QDir::separator();    //!< Directory name for temporary footage audio files

    QString suffixVideo = "avi";   //!< File extension for output video file
    QString suffixAudio = "wav";   //!< File extension for audio files
    QString suffixImages = "png";  //!< File extension for images files

    /*! \brief Used kHz for audio files */
    QString audioKhz = "22050";  // 16000 for pico2wave

    /*! \brief Used kHz for audio files - shortcut */
    QString audioKhzShorcut = "22k";  // 16k for pico2wave

    double audioNormalize = 0.3;  //!< Normalizing factor for final audio (0 = disabled)

    /*! \brief Text-to-speech engine */
    QString ttsBin = "/usr/bin/espeak";  // "/usr/bin/pico2wave"

    /*! \brief Options for text-to-speech */
    QStringList ttsOpts = {};  // espeak
    // QStringList ttsOpts = {"-l", "en-US"};                                   // pico2wave
    // QStringList ttsOpts = {"-k10", "-p", "30", "-s", "150"};                 // espeak modified
    // QStringList ttsOpts = {"-v", "slovak", "-k10", "-p", "30", "-s", "150"}; // espeak Slovak

    bool ttsAddSpace = (ttsBin == "/usr/bin/espeak");  //!< Add 1 space character after last sentence dot

    uint widthScreen = 1024U;       //!< Screen width
    uint heightScreen = 576U;       //!< Screen height
    uint64_t frameDuration = 40UL;  //!< Frame duration in ms

    float glAccuracy = 0.1f;  //!< Open GL accuracy
    float glFov = 60.0f;      //!< Open GL field of view in degrees
    float glNear = 0.001f;    //!< Open GL near plane
    float glFar = 10000.0f;   //!< Open GL far plane
    bool glBlend = true;      //!< Open GL apply blend
    bool glCullFront = true;  //!< Open GL apply cull front
    uint glSamples = 0U;      //!< Open GL multi-sampling

    QString textSubsFontFamily = "";  //!< Font family for subtitles
    QString text2DFontFamily = "";    //!< Font family for 2D text
    QString text3DFontFamily = "";    //!< Font family for 3D text

    uint textSubsFontHeight = 12U;  //!< Font height for subtitles
    uint text2DFontHeight = 16U;    //!< Font height for 2D text
    uint text3DFontHeight = 20U;    //!< Font height for 3D text

    float text3DPixelSize = 0.005f;  //!< Font pixel size in 3D space

    qreal text2DOffsetBorder = 20.0;  //!< 2D text minimum offset from screen border
    qreal text2DOffsetSubs = 100.0;   //!< 2D text bottom offset for subtitles

    uint qualityLine = 0U;     //!< Quality for line circle
    uint qualitySphere = 3U;   //!< Quality for sphere circle
    uint qualityLatLong = 1U;  //!< Quality for wire-frame sphere latitude-longitude steps

 private:
    static QHash<QString, std::pair<QString, uint64_t>> speechDB;  //!< Speech files database
    static QHash<uint64_t, QString> silenceDB;                     //!< Silence files database
    static Config m_cfg;                                           //!< Singleton instance

    /*!
     * \brief Private constructor
     * \param _outPath Output directory
     * \param _outFileName Output file name (without suffix)
     * \param _level Level of quality
     * \param _threads Thread count (0 = auto-detect, 1= single thread)
     */
    Config(const QString &_outPath, const QString &_outFileName, const uint _level = 0U, const uint _threads = 0U);

    void showInfo() const;  //!< Log status

 public:
    /*!
     * \brief Initialize singleton instance
     * \param _outPath Output directory
     * \param _outFileName Output file name (without suffix)
     * \param _level Level of quality
     * \param _clearSpeechDB Clear speech and single database instead of initializing
     * \param _threads Thread count (0 = auto-detect, 1= single thread)
     * \return Singleton instance
     */
    inline static const Config &init(const QString &_outPath,
                                     const QString &_outFileName,
                                     const uint _level,
                                     const bool _clearSpeechDB = false,
                                     const uint _threads = 0U)
    {
        m_cfg = Config(_outPath, _outFileName, _level, _threads);

        if (_clearSpeechDB)
            clearSpeechDB();
        else
            initSpeechDB();

        m_cfg.showInfo();

        return m_cfg;
    }

    /*!
     * \brief Singleton instance getter
     * \return Singleton instance
     */
    inline static const Config &cfg()
    {
        return m_cfg;
    }

 private:
    /*!
     * \brief Clear speech and single database folder
     * \return Success flag
     */

    static bool clearSpeechDB();
    /*!
     * \brief Initialize speech and single files database
     * \return Success flag
     */
    static bool initSpeechDB();

 public:
    /*!
     * \brief Save current speech and single database
     * \return Success flag
     */
    static bool saveSpeechDB();

    /*!
     * \brief Getter for Open GL perspective matrix
     * \return Open GL perspective matrix
     */
    inline QMatrix4x4 perspectiveMatrix() const
    {
        QMatrix4x4 result;
        result.perspective(glFov, float(widthScreen) / float(heightScreen), glNear, glFar);
        return result;
    }

    /*!
     * \brief Fixes given time-step to match next frame start time
     * \param _timeStep Time-step to fix
     * \return Time-step that match match next frame start time
     */
    inline uint64_t fixedTime(const uint64_t _timeStep) const
    {
        const uint64_t tmod = _timeStep % frameDuration;
        return _timeStep + (tmod == 0UL ? 0UL : (frameDuration - tmod));
    }

    /*!
     * \brief Clear directory with temporary images and footage audio files
     * \param _removedImages Count of removed images
     * \param _removedAudio Count of removed audio files
     * \return Success flag
     */
    bool clearDirectory(uint64_t &_removedImages, uint64_t &_removedAudio) const;

    /*!
     * \brief Prepares full file name for image
     * \param _footageId Footage ID
     * \param _frameId Frame ID within footage
     * \return Full file name for image
     */
    QString pathImage(const uint64_t _footageId, const uint64_t _frameId) const;

    /*!
     * \brief Prepares full file name for footage audio
     * \param _footageId Footage ID
     * \return File name for footage audio
     */
    QString pathFootageAudio(const uint64_t _footageId) const;

    /*!
     * \brief Getter for silence file name
     * \param _duration Silence duration
     * \return Silence file name
     * \details Work with silence database, does not create duplicate audio files
     */
    QString getSilence(const uint64_t _duration) const;

    /*!
     * \brief Getter for speech file name and duration
     * \param _speech Speech text
     * \return Speech file name and duration
     * \details Work with speech database, does not create duplicate audio files
     */
    std::pair<QString, uint64_t> getSpeech(const QString &_speech) const;

 private:
    /*!
     * \brief Create new silence audio file
     * \param _fileNameOut Audio file name
     * \param _duration Silence duration
     * \return Success flag
     */
    bool createSilence(const QString &_fileNameOut, const uint64_t _duration) const;

    /*!
     * \brief Create new speech audio file
     * \param _fileNameOut Audio file name
     * \param _speech Speech text
     * \return Success flag
     */
    bool createSpeech(const QString &_fileNameOut, const QString &_speech) const;

    /*!
     * \brief Checks total audio file duration
     * \param _fileName Audio file name
     * \return Audio file duration in ms
     */
    uint64_t getAudioDuration(const QString &_fileName) const;

 public:
    /*!
     * \brief Connect audio files into one
     * \param _fileNameOut Output audio file name
     * \param _files Input audio files
     * \return Success flag
     */
    bool connectAudio(const QString &_fileNameOut, const QStringList &_files) const;

    /*!
     * \brief Create normalized audio file
     * \param _fileNameOut Output audio file name
     * \param _fileNameIn Input audio file
     * \return Success flag
     */
    bool normalizeAudio(const QString &_fileNameOut, const QString &_fileNameIn) const;

    /*!
     * \brief Create index file for ffmpeg process
     * \param _imageFiles List of image files
     * \return Success flag
     */
    bool createIndex(const QStringList &_imageFiles) const;

    /*!
     * \brief Create final video
     * \return Success flag
     */
    bool createVideo() const;

    /*!
     * \brief Create indexes for multiple threads
     * \param _count Total count
     * \return Indexes for multiple threads
     */
    std::vector<std::pair<uint64_t, uint64_t>> createPool(const uint64_t _count) const;
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_CONFIG_H
