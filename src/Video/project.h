/*!
 * \file src/Video/project.h
 * \brief Video project
 */

#ifndef VIDEO_PROJECT_H
#define VIDEO_PROJECT_H

#include "footage.h"

namespace U1 {
namespace Video {

/*! \brief Video project */
class Project : public Props::ItemPropertyGroup
{
 protected:
    std::vector<Footage *> m_footages;  //!< Project footage sequence

 public:
    SettingsSubtitles settingsSubtitles;  //!< Subtitle settings
    SettingsOpenGL settingsOpenGL;        //!< Open GL settings
    SettingsVideo settingsVideo;          //!< Video settings
    Audio::SettingsAudio settingsAudio;   //!< Audio settings

    /*!
     * \brief Constructor
     * \param _name Project name
     */
    inline Project(const std::string &_name)
        : Props::ItemPropertyGroup(_name)
    {
    }

    ~Project();  //!< Destructor

    /*!
     * \brief Append footage
     * \param _name Footage name
     * \return Created footage object
     */
    inline Footage *addFootage(const std::string &_name)
    {
        Footage *result = new Footage(_name);
        m_footages.push_back(result);
        addProperty(result);
        return result;
    }

    /*! \brief Setup minimum resolution (640x480, 25FPS, Font:10, Quality: 1-0, Open GL: disabled) */
    inline void setupMinimum()
    {
        settingsVideo.setupMinimum();
        settingsOpenGL.useGlBlend = false;
        settingsOpenGL.useGlSamples = 0U;
        settingsSubtitles.fontHeight = 10;
        settingsSubtitles.bottomOffset = 10;
        Items::ItemDefaultValues::fontHeight = 10;
        Items::ItemDefaultValues::sphereQuality = 1UL;
        Items::ItemDefaultValues::lineQuality = 0UL;
    }

    /*! \brief Setup small resolution (1024x768, 30FPS, Font:12, Quality: 3-1, Open GL: 2 samples) */
    inline void setupSmall()
    {
        settingsVideo.setupSmall();
        settingsOpenGL.useGlBlend = true;
        settingsOpenGL.useGlSamples = 2U;
        settingsSubtitles.fontHeight = 12;
        settingsSubtitles.bottomOffset = 12;
        Items::ItemDefaultValues::fontHeight = 12;
        Items::ItemDefaultValues::sphereQuality = 3UL;
        Items::ItemDefaultValues::lineQuality = 1UL;
    }

    /*! \brief Setup Full HD resolution (1920x1080, 30FPS, Font:24, Quality: 15-3, Open GL: 4 samples) */
    inline void setupFullHD()
    {
        settingsVideo.setupFullHD();
        settingsOpenGL.useGlBlend = true;
        settingsOpenGL.useGlSamples = 4U;
        settingsSubtitles.fontHeight = 24;
        settingsSubtitles.bottomOffset = 24;
        Items::ItemDefaultValues::fontHeight = 24;
        Items::ItemDefaultValues::sphereQuality = 15UL;
        Items::ItemDefaultValues::lineQuality = 3UL;
    }

    /*! \brief Setup 4K resolution (3840x2160, 60FPS, Font:48, Quality: 31-7, Open GL: 4 samples) */
    inline void setup4K()
    {
        settingsVideo.setup4K();
        settingsOpenGL.useGlBlend = true;
        settingsOpenGL.useGlSamples = 4U;
        settingsSubtitles.fontHeight = 48;
        settingsSubtitles.bottomOffset = 48;
        Items::ItemDefaultValues::fontHeight = 48;
        Items::ItemDefaultValues::sphereQuality = 31UL;
        Items::ItemDefaultValues::lineQuality = 7UL;
    }

    /*! \brief Setup 8K resolution (7680x4320, 60FPS, Font:72, Quality: 63-15, Open GL: 8 samples)*/
    inline void setup8K()
    {
        settingsVideo.setup8K();
        settingsOpenGL.useGlBlend = true;
        settingsOpenGL.useGlSamples = 8U;
        settingsSubtitles.fontHeight = 72;
        settingsSubtitles.bottomOffset = 72;
        Items::ItemDefaultValues::fontHeight = 72;
        Items::ItemDefaultValues::sphereQuality = 63UL;
        Items::ItemDefaultValues::lineQuality = 15UL;
    }

    /*!
     * \brief Create video file
     * \param _workDir Working directory for temporary images and files
     * \param _fileName Output video file name
     * \return Success flag
     */
    bool createVideo(const QString &_workDir, const QString &_fileName) const;
};

}  // namespace Video
}  // namespace U1

#endif  // VIDEO_FOOTAGE_H
