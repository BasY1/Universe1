/*!
 * \file src/Video/settingsvideo.h
 * \brief General video settings
 */

#ifndef VIDEO_SETTINGSVIDEO_H
#define VIDEO_SETTINGSVIDEO_H

#include "../Math/type.h"
#include "../Audio/settingsaudio.h"

#include <QOpenGLFunctions>

#include <QColor>
#include <QFont>
#include <QSize>

namespace U1 {

/*!
 * \namespace U1::Video
 * \brief Video tools
 */
namespace Video {

/*! \brief The Open GL settings */
struct SettingsOpenGL
{
    bool useGlBlend = true;  //!< Use blend method
    uint useGlSamples = 4U;  //!< Open GL samples

    /*!
     * \brief To hash value
     * \return A hash value from current settings
     */
    inline size_t toHash() const
    {
        return Math::mixHash(std::hash<bool>{}(useGlBlend), std::hash<uint>{}(useGlSamples));
    }

    /*!
     * \brief Setup Open GL variables
     * \param _fun Open GL functions
     */
    inline void setupGL(QOpenGLFunctions *_fun) const
    {
        _fun->glEnable(GL_DEPTH_TEST);
        if (useGlBlend)
        {
            _fun->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            _fun->glEnable(GL_BLEND);
            if (useGlSamples > 0U)
                _fun->glEnable(GL_MULTISAMPLE);
        }
        _fun->glEnable(GL_CULL_FACE);
        _fun->glCullFace(GL_BACK);
        _fun->glFrontFace(GL_CCW);
    }

    /*!
     * \brief Check setting validity
     * \return \c true when this settings are valid
     */
    bool isValid() const;
};

/*! \brief Video subtitles settings */
struct SettingsSubtitles
{
    bool useSubtitles = true;           //!< Major on/off flag for subtitles
    bool upperCase = false;             //!< Flag for always overwrite subtitles with its upper-case version
    QColor fontColor = Qt::white;       //!< Subtitles color
    QString fontFamily = "Sans Serif";  //!< Subtitles font
    uint fontHeight = 48;               //!< Subtitles font height [6|7|8|9|10|11|12|14|16|18|20|22|24|26|28|36|48|72]
    uint bottomOffset = 50;             //!< Subtitles offset from the bottom of the screen

    /*!
     * \brief To hash value
     * \return A hash value from current settings
     */
    inline size_t toHash() const
    {
        return Math::mixHash(std::hash<std::string>{}(fontFamily.toStdString()),
                             std::hash<uint>{}(fontHeight),
                             std::hash<uint>{}(bottomOffset));
    }

    /*!
     * \brief Check setting validity
     * \return \c true when this settings are valid
     */
    bool isValid() const;

    /*!
     * \brief Setup font for subtitles
     * \param _fontFamily Subtitles font
     * \param _fontHeight Subtitles font height (use [6|7|8|9|10|11|12|14|16|18|20|22|24|26|28|36|48|72])
     * \param _bottomOffset Subtitles offset from the bottom of the screen
     * \return Success flag (checks if font exists)
     */
    bool setupFont(const QString &_fontFamily, const int _fontHeight, const uint _bottomOffset);
};

/*! \brief Video format settings */
struct SettingsVideo
{
    static QString ffmpegBin;  //!< \b ffmpeg tool binary (/usr/bin/ffmpeg)

    QString imgSuffix = "png";                //!< Single frame image suffix (image type)
    QString videoCodec = "libx264";           //!< Video codec for \b ffmpeg tool (libx264)
    QString videoPixelFormat = "yuv420p";     //!< Video pixel format for \b ffmpeg tool (yuv420p)
    QSize resolution = {1920, 1080};          //!< Video resolution
    float frameDuration = (1000.0f / 30.0f);  //!< Frame duration

    /*! \brief Setup minimum resolution (640x480, 25FPS) */
    inline void setupMinimum()
    {
        resolution = {640, 480};
        frameDuration = (1000.0f / 25.0f);
    }

    /*! \brief Setup small resolution (1024x768, 30FPS)*/
    inline void setupSmall()
    {
        resolution = {1024, 768};
        frameDuration = (1000.0f / 30.0f);
    }

    /*! \brief Setup Full HD resolution (1920x1080, 30FPS)*/
    inline void setupFullHD()
    {
        resolution = {1920, 1080};
        frameDuration = (1000.0f / 30.0f);
    }

    /*! \brief Setup 4K resolution (3840x2160, 60FPS)*/
    inline void setup4K()
    {
        resolution = {3840, 2160};
        frameDuration = (1000.0f / 60.0f);
    }

    /*! \brief Setup 8K resolution (7680x4320, 60FPS)*/
    inline void setup8K()
    {
        resolution = {7680, 4320};
        frameDuration = (1000.0f / 60.0f);
    }

    /*!
     * \brief To hash value
     * \return A hash value from current settings
     */
    inline size_t toHash() const
    {
        return Math::mixHash(std::hash<std::string>{}(imgSuffix.toStdString()),
                             std::hash<std::string>{}(videoCodec.toStdString()),
                             std::hash<std::string>{}(videoPixelFormat.toStdString()),
                             std::hash<int>{}(resolution.width()),
                             std::hash<int>{}(resolution.height()),
                             std::hash<float>{}(frameDuration));
    }

    /*!
     * \brief Check setting validity
     * \return \c true when this settings are valid
     */
    bool isValid() const;

    /*!
     * \brief Create video from images with audio
     * \param _outFileName Output video file name
     * \param _audioSettings Audio setting
     * \param _audioFileName Audio stream
     * \param _images Image file name collection
     * \param _hash Video hash value
     * \return Success flag
     */
    bool createVideo(const QString &_outFileName,
                     const Audio::SettingsAudio &_audioSettings,
                     const QString &_audioFileName,
                     const QStringList &_images,
                     const size_t _hash = 0UL) const;
};

}  // namespace Video
}  // namespace U1

#endif  // VIDEO_SETTINGSVIDEO_H
