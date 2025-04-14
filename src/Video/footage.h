/*!
 * \file src/Video/footage.h
 * \brief Video footage
 */

#ifndef VIDEO_FOOTAGE_H
#define VIDEO_FOOTAGE_H

#include "../Audio/footageaudio.h"
#include "settingsvideo.h"

#include "../ItemProps/itempropertycolor.h"
#include "../ItemProps/itempropertyvec3.h"

#include "../Items/item2d.h"
#include "../Items/item3d.h"
#include "../Items/itemcamera.h"

namespace U1 {
namespace Video {

/*! \brief Video footage */
class Footage : public Props::ItemPropertyGroup, public Audio::FootageAudio
{
 public:
    size_t minimalFootageDuration = 1000UL;  //!< Minimal footage duration in milliseconds

    Props::ItemPropertyVec3F cameraPosition;     //!< Camera position
    Props::ItemPropertyVec3F cameraLookAt;       //!< Camera observing point
    Props::ItemPropertyVec3F cameraUp;           //!< Camera up direction
    Props::ItemPropertyFloat cameraFieldOfView;  //!< Field of view in degrees
    Props::ItemPropertyFloat cameraNearPlane;    //!< Near plane distance
    Props::ItemPropertyFloat cameraFarPlane;     //!< Far plane distance

    Props::ItemPropertyColor bgColor;         //!< Background color
    Props::ItemPropertyColor lightColor;      //!< Light color
    Props::ItemPropertyVec3F lightDirection;  //!< Light direction
    Props::ItemPropertyFloat lightAmbient;    //!< Scene ambient factor

 protected:
    std::vector<Items::Item2D *> m_items2D;        //!< 2D items painted over the Open GL context
    std::vector<Items::Item3D *> m_items3D;        //!< 3D items
    std::vector<Items::ItemCamera *> m_cameras;    //!< Scene camera items
    std::vector<Items::ClipPlane *> m_clipPlanes;  //!< Clipping planes

 public:
    /*!
     * \brief Constructor
     * \param _name Footage name
     */
    Footage(const std::string &_name);

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored (active) time step = footage total duration
     */
    size_t latestTimeStep() const override;

    /*!
     * \brief Maximum possible clipping planes
     * \return Maximum possible clipping planes
     */
    inline size_t maxClipPlanes() const
    {
        return OpenGL::Data3D::MaxClipPlanes;
    }

    /*!
     * \brief Add clip plane for this object
     * \param _center Plane central point
     * \param _normal Plane normal
     * \param _enabled Clipping plane enabled flag
     * \param _name Clipping plane name
     * \return Success flag
     */
    Items::ClipPlane *addClipPlane(const Math::Vec3F &_center,
                                   const Math::Vec3F &_normal,
                                   const bool _enabled = true,
                                   const std::string &_name = "Clip plane");
    /*!
     * \brief Add scene camera item
     * \param _name Camera name
     * \param _position Camera position
     * \param _lookAt Camera observing point
     * \return Scene camera object
     */
    inline Items::ItemCamera *addCamera(const std::string &_name = "Camera",
                                        const Math::Vec3F &_position = {10.0F, 0.0F, 0.0F},
                                        const Math::Vec3F &_lookAt = {})
    {
        Items::ItemCamera *result = new Items::ItemCamera(_name, _position, _lookAt);
        m_cameras.push_back(result);
        addProperty(result);
        return result;
    }

    /*!
     * \brief Add 3D scene item
     * \tparam T Item3D nested class
     * \param _item New 3D item object pointer
     * \return Given 3D item object pointer
     */
    template <typename T>
    inline typename std::enable_if<std::is_base_of<Items::Item3D, T>::value, T *>::type add3D(T *_item)
    {
        if (_item == nullptr)
            return nullptr;
        m_items3D.push_back(_item);
        addProperty(_item);
        return _item;
    }

    /*!
     * \brief Add 2D scene item
     * \tparam T Item2D nested class
     * \param _item New 2D item object pointer
     * \return Given 2D item object pointer
     */
    template <typename T>
    inline typename std::enable_if<std::is_base_of<Items::Item2D, T>::value, T *>::type add2D(T *_item)
    {
        if (_item == nullptr)
            return nullptr;
        m_items2D.push_back(_item);
        addProperty(_item);
        return _item;
    }

    /*!
     * \brief Create video file
     * \param _workDir Working directory for temporary images and files
     * \param _fileName Output video file name
     * \param _settingsSubtitles Subtitles settings
     * \param _settingsOpenGL Open GL settings
     * \param _settingsVideo Video settings
     * \param _settingsAudio Audio settings
     * \return Success flag
     */
    bool createVideo(const QString &_workDir,
                     const QString &_fileName,
                     const SettingsSubtitles &_settingsSubtitles,
                     const SettingsOpenGL &_settingsOpenGL,
                     const SettingsVideo &_settingsVideo,
                     const Audio::SettingsAudio &_settingsAudio) const;

    /*!
     * \brief Capture single frame from video footage
     * \param _fileName Output image file name
     * \param _timeStep The time-step for capturing an image
     * \param _settingsSubtitles Subtitles settings
     * \param _settingsOpenGL Open GL settings
     * \param _settingsVideo Video settings
     * \return Success flag
     */
    bool createImageAt(const QString &_fileName,
                       const size_t _timeStep,
                       const SettingsSubtitles &_settingsSubtitles,
                       const SettingsOpenGL &_settingsOpenGL,
                       const SettingsVideo &_settingsVideo) const;
};

}  // namespace Video
}  // namespace U1

#endif  // VIDEO_FOOTAGE_H
