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
    Props::ItemPropertyFloat radiusWire;  //!< Pyramid and arrow line radius

    Props::ItemPropertyQuality quality;      //!< Camera body lens circle quality
    Props::ItemPropertyQuality qualityWire;  //!< Pyramid and arrow line circle quality

    Props::ItemPropertyBool showImage;        //!< Show image flag
    Props::ItemPropertyBool showBody;         //!< Show body
    Props::ItemPropertyBool showViewArrow;    //!< Show look at arrow
    Props::ItemPropertyBool showViewPyramid;  //!< Show view pyramid

    Props::ItemPropertyMaterialRGB materialBody1;  //!< Major camera body material
    Props::ItemPropertyMaterialRGB materialBody2;  //!< Minor camera body material
    Props::ItemPropertyMaterialRGB materialWire;   //!< Pyramid and arrow material

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
     * \param _radiusWire Initial value for pyramid and arrow line radius
     * \param _quality Initial value for camera body lens circle quality
     * \param _qualityWire Initial value for pyramid and arrow line circle quality
     * \param _showImage Initial value for show image flag
     * \param _showBody Initial value for show body
     * \param _showViewArrow Initial value for show look at arrow
     * \param _showViewPyramid Initial value for show view pyramid
     * \param _materialBody1 Initial value for major camera body material
     * \param _materialBody2 Initial value for minor camera body material
     * \param _materialWire Initial value for pyramid and arrow material
     * \param _alpha Initial value for alpha
     * \param _visible Initial value for visible flag
     */
    ItemCamera(const std::string &_name = "Camera",
               const Math::Vec3F &_position = {10.0F, 0.0F, 0.0F},
               const Math::Vec3F &_lookAt = {},
               const Math::Vec3F &_up = Math::Vec3F::unitZ(),
               const float _fieldOfView = 90.0F,
               const float _nearPlane = 0.1F,
               const float _farPlane = 20.0F,
               const uint32_t _imageWidth = 1920U,   // 1024
               const uint32_t _imageHeight = 1080U,  // 768
               const float _imagePixelSize = ItemDefaultValues::pixelSize,
               const bool _imagePositionDynamic = true,
               const float _bodySize = 1.0F,
               const float _radiusWire = ItemDefaultValues::lineRadius,
               const size_t _quality = ItemDefaultValues::sphereQuality,
               const size_t _qualityWire = ItemDefaultValues::lineQuality,
               const bool _showImage = true,
               const bool _showBody = true,
               const bool _showViewArrow = false,
               const bool _showViewPyramid = false,
               const Math::MaterialRGB &_materialBody1 = {QColor(192, 156, 0)},
               const Math::MaterialRGB &_materialBody2 = {QColor(90, 200, 250)},
               const Math::MaterialRGB &_materialWire = {ItemDefaultValues::lineColor},
               const uint8_t _alpha = 255U,
               const bool _visible = true);

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
