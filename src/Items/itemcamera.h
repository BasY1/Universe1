/*!
 * \file src/Items/itemcamera.h
 * \brief Video camera item
 */

#ifndef ITEMS_ITEMCAMERA_H
#define ITEMS_ITEMCAMERA_H

#include "item3d.h"

#include "../Math/camera.h"

#include "../ItemProps/itempropertyvec3.h"
#include "../ItemProps/itempropertymaterial.h"

#include <QOpenGLTexture>

namespace U1 {
namespace Items {

/*! \brief Video camera item */
class ItemCamera : public Item3D
{
 public:
    Props::ItemPropertyVec3F position;  //!< Camera position
    Props::ItemPropertyVec3F lookAt;    //!< Camera observing point
    Props::ItemPropertyVec3F up;        //!< Camera up direction

    Props::ItemPropertyFloat fieldOfView;  //!< Field of view in degrees
    Props::ItemPropertyFloat nearPlane;    //!< Near plane distance
    Props::ItemPropertyFloat farPlane;     //!< Far plane distance

    Props::ItemPropertyUInt32 imageWidth;          //!< Camera image width in pixels
    Props::ItemPropertyUInt32 imageHeight;         //!< Camera image height in pixels
    Props::ItemPropertyFloat imagePixelSize;       //!< Image texture pixel size
    Props::ItemPropertyBool imagePositionDynamic;  //!< Flag for dynamic orientation of generated image texture

    Props::ItemPropertyFloat bodySize;    //!< Camera body size
    Props::ItemPropertyFloat lineRadius;  //!< Pyramid and arrow line radius

    Props::ItemPropertyQuality bodyQuality;  //!< Camera body lens circle quality
    Props::ItemPropertyQuality lineQuality;  //!< Pyramid and arrow line circle quality

    Props::ItemPropertyBool showImage;        //!< Show image flag
    Props::ItemPropertyBool showBody;         //!< Show body
    Props::ItemPropertyBool showViewArrow;    //!< Show look at arrow
    Props::ItemPropertyBool showViewPyramid;  //!< Show view pyramid

    Props::ItemPropertyMaterialRGB materialBody1;  //!< Major camera body material
    Props::ItemPropertyMaterialRGB materialBody2;  //!< Minor camera body material
    Props::ItemPropertyMaterialRGB materialLines;  //!< Pyramid and arrow material

    /*!
     * \brief Constructor
     * \param _name Camera name
     * \param _position Initial value for camera position
     * \param _lookAt Initial value for camera observing point
     * \param _up Initial value for camera up direction
     * \param _fieldOfView Initial value for field of view in degrees
     * \param _nearPlane Initial value for near plane distance
     * \param _farPlane Initial value for far plane distance
     * \param _imageWidth Initial value for camera image width in pixels
     * \param _imageHeight Initial value for camera image height in pixels
     * \param _imagePixelSize Initial value for image texture pixel size
     * \param _imagePositionDynamic Initial value for dynamic orientation of generated image texture
     * \param _bodySize Initial value for camera body size
     * \param _lineRadius Initial value for pyramid and arrow line radius
     * \param _bodyQuality Initial value for camera body lens circle quality
     * \param _lineQuality Initial value for pyramid and arrow line circle quality
     * \param _showImage Initial value for show image flag
     * \param _showBody Initial value for show body
     * \param _showViewArrow Initial value for show look at arrow
     * \param _showViewPyramid Initial value for show view pyramid
     * \param _materialBody1 Initial value for major camera body material
     * \param _materialBody2 Initial value for minor camera body material
     * \param _materialLines Initial value for pyramid and arrow material
     * \param _alpha Initial value for alpha
     * \param _visible Initial value for visible flag
     */
    ItemCamera(const std::string &_name,
               const Math::Vec3F &_position,
               const Math::Vec3F &_lookAt,
               const Math::Vec3F &_up,
               const float _fieldOfView,
               const float _nearPlane,
               const float _farPlane,
               const uint32_t _imageWidth,
               const uint32_t _imageHeight,
               const float _imagePixelSize,
               const bool _imagePositionDynamic,
               const float _bodySize,
               const float _lineRadius,
               const size_t _bodyQuality,
               const size_t _lineQuality,
               const bool _showImage,
               const bool _showBody,
               const bool _showViewArrow,
               const bool _showViewPyramid,
               const Math::MaterialRGB &_materialBody1,
               const Math::MaterialRGB &_materialBody2,
               const Math::MaterialRGB &_materialLines,
               const uint8_t _alpha,
               const bool _visible);

    /*!
     * \brief Constructor
     * \param _position Initial value for camera position
     * \param _lookAt Initial value for camera observing point
     * \param _up Initial value for camera up direction
     * \param _fieldOfView Initial value for field of view in degrees
     * \param _nearPlane Initial value for near plane distance
     * \param _farPlane Initial value for far plane distance
     * \param _imageWidth Initial value for camera image width in pixels
     * \param _imageHeight Initial value for camera image height in pixels
     * \param _imagePixelSize Initial value for image texture pixel size
     * \param _imagePositionDynamic Initial value for dynamic orientation of generated image texture
     * \param _bodySize Initial value for camera body size
     * \param _lineRadius Initial value for pyramid and arrow line radius
     * \param _bodyQuality Initial value for camera body lens circle quality
     * \param _lineQuality Initial value for pyramid and arrow line circle quality
     * \param _showImage Initial value for show image flag
     * \param _showBody Initial value for show body
     * \param _showViewArrow Initial value for show look at arrow
     * \param _showViewPyramid Initial value for show view pyramid
     * \param _materialBody1 Initial value for major camera body material
     * \param _materialBody2 Initial value for minor camera body material
     * \param _materialLines Initial value for pyramid and arrow material
     * \param _alpha Initial value for alpha
     * \param _visible Initial value for visible flag
     */
    inline ItemCamera(const Math::Vec3F &_position,
                      const Math::Vec3F &_lookAt,
                      const Math::Vec3F &_up,
                      const float _fieldOfView,
                      const float _nearPlane,
                      const float _farPlane,
                      const uint32_t _imageWidth,
                      const uint32_t _imageHeight,
                      const float _imagePixelSize,
                      const bool _imagePositionDynamic,
                      const float _bodySize,
                      const float _lineRadius,
                      const size_t _bodyQuality,
                      const size_t _lineQuality,
                      const bool _showImage,
                      const bool _showBody,
                      const bool _showViewArrow,
                      const bool _showViewPyramid,
                      const Math::MaterialRGB &_materialBody1,
                      const Math::MaterialRGB &_materialBody2,
                      const Math::MaterialRGB &_materialLines,
                      const uint8_t _alpha,
                      const bool _visible)
        : ItemCamera("Camera",
                     _position,
                     _lookAt,
                     _up,
                     _fieldOfView,
                     _nearPlane,
                     _farPlane,
                     _imageWidth,
                     _imageHeight,
                     _imagePixelSize,
                     _imagePositionDynamic,
                     _bodySize,
                     _lineRadius,
                     _bodyQuality,
                     _lineQuality,
                     _showImage,
                     _showBody,
                     _showViewArrow,
                     _showViewPyramid,
                     _materialBody1,
                     _materialBody2,
                     _materialLines,
                     _alpha,
                     _visible)
    {
    }

    /*!
     * \brief Camera object at specific time-step
     * \param _timeStep Time-step
     * \return Camera object
     */
    inline Math::CamF getCamera(const size_t _timeStep) const
    {
        return Math::CamF(position.value(_timeStep),
                          lookAt.value(_timeStep),
                          up.value(_timeStep),
                          imageWidth.value(_timeStep),
                          imageHeight.value(_timeStep),
                          fieldOfView.value(_timeStep),
                          nearPlane.value(_timeStep),
                          farPlane.value(_timeStep));
    }

    /*!
     * \brief Image size at specific time-step
     * \param _timeStep Time-step
     * \return Image size
     */
    inline QSize getImageSize(const size_t _timeStep) const
    {
        return QSize(imageWidth.value(_timeStep), imageHeight.value(_timeStep));
    }

    /*!
     * \brief Create image texture 3D data
     * \param _out Output data objects
     * \param _texture Open GL texture with captured image from this camera
     * \param _mainViewCamera Main camera object
     * \param _timeStep Time-step
     * \return
     */
    virtual void createTexture(std::list<OpenGL::Data3D *> &_out,
                               QOpenGLTexture *_texture,
                               const Math::CamF &_mainViewCamera,
                               const size_t _timeStep);

 protected:
    /*!
     * \brief createDataImpl
     * \param _out Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_out, const size_t _timeStep) const override;
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMCAMERA_H
