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
