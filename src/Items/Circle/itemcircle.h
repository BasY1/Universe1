/*!
 * \file src/Items/Circle/itemcircle.h
 * \brief Dynamic circle video item
 */

#ifndef ITEMS_ITEMCIRCLE_H
#define ITEMS_ITEMCIRCLE_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::Circle
 * \brief 3D Circle item tools
 */
namespace Circle {
Q_NAMESPACE

/*! \brief Show circle modes */
enum ShowCircleType : int
{
    CircleHidden,  //!< Circle plane hidden

    CircleFrontBack,  //!< Single color circle visible from both front and back
    CircleFront,      //!< Single color circle visible from front
    CircleBack,       //!< Single color circle visible from back

    CircleBorderFrontBack,  //!< Two color circle visible from both front and back
    CircleBorderFront,      //!< Two color circle visible from front
    CircleBorderBack,       //!< Two color circle visible from back
};
Q_ENUM_NS(ShowCircleType)

/*! \brief Show circle modes */
enum ShowCircleCameraType : int
{
    CircleCameraHidden,  //!< Circle plane hidden
    CircleCameraSingle,  //!< Single color circle
    CircleCameraBorder,  //!< Two color circle
};
Q_ENUM_NS(ShowCircleCameraType)

}  // namespace Circle

/*! \brief Dynamic circle video item */
class ItemCircle : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius;     //!< Circle radius
    Props::ItemPropertyQuality quality;  //!< Circle quality

    Props::ItemPropertyEnum show;  //!< Show circle mode

    Props::ItemPropertyMaterialRGB materialFront;  //!< Front side material
    Props::ItemPropertyMaterialRGB materialBack;   //!< Back side material

    Props::ItemPropertyMaterialRGBA materialCenterFront;  //!< Center front side material
    Props::ItemPropertyMaterialRGBA materialBorderFront;  //!< Border front side material
    Props::ItemPropertyMaterialRGBA materialCenterBack;   //!< Center back side material
    Props::ItemPropertyMaterialRGBA materialBorderBack;   //!< Border back side material

    Props::ItemPropertyBool showWire;              //!< Show circle wire-frame
    Props::ItemPropertyFloat radiusWire;           //!< Wire radius
    Props::ItemPropertyQuality qualityWire;        //!< Wire circle quality
    Props::ItemPropertyMaterialRGBA materialWire;  //!< Wire-frame material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _radius Initial circle radius
     * \param _quality Initial circle quality
     * \param _show Initial value for show circle mode
     * \param _showWire Initial value for show circle wire-frame
     * \param _materialFront Initial value for front side material
     * \param _materialBack Initial value for back side material
     * \param _materialCenterFront Initial value for center front side material
     * \param _materialBorderFront Initial value for border front side material
     * \param _materialCenterBack  Initial value for center back side material
     * \param _materialBorderBack  Initial value for border back side material
     * \param _materialWire Initial value for wire material
     * \param _radiusWire Initial value for wire radius
     * \param _qualityWire Initial value for wire circle quality
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemCircle(const std::string &_name = "Circle",
               const Math::Vec3F &_center = {},
               const Math::Vec3F &_normal = Math::Vec3F::unitX(),
               const Math::Vec3F &_arm = Math::Vec3F::unitY(),
               const float _radius = 0.5f,
               const size_t _quality = ItemDefaultValues::sphereQuality,
               const Circle::ShowCircleType _show = Circle::CircleFrontBack,
               const bool _showWire = false,
               const Math::MaterialRGB &_materialFront = {Qt::white},
               const Math::MaterialRGB &_materialBack = {Qt::lightGray},
               const Math::MaterialRGBA &_materialCenterFront = {Qt::red},
               const Math::MaterialRGBA &_materialBorderFront = {Qt::green},
               const Math::MaterialRGBA &_materialCenterBack = {Qt::blue},
               const Math::MaterialRGBA &_materialBorderBack = {Qt::white},
               const Math::MaterialRGBA &_materialWire = {ItemDefaultValues::lineColor},
               const float _radiusWire = ItemDefaultValues::lineRadius,
               const size_t _qualityWire = ItemDefaultValues::lineQuality,
               const uint8_t _alpha = 255U,
               const bool _visible = true);

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;
};

/*! \brief Dynamic circle video item with the plane normal that is always oriented towards camera position */
class ItemCircleCamera : public Item3D
{
 public:
    Props::ItemPropertyVec3F center;     //!< Circle center point
    Props::ItemPropertyFloat radius;     //!< Circle radius
    Props::ItemPropertyQuality quality;  //!< Circle quality

    Props::ItemPropertyEnum show;                    //!< Show circle mode
    Props::ItemPropertyMaterialRGB material;         //!< Single material
    Props::ItemPropertyMaterialRGBA materialCenter;  //!< Vertex 1 material
    Props::ItemPropertyMaterialRGBA materialBorder;  //!< Vertex 2 material

    Props::ItemPropertyBool showWire;              //!< Show circle wire-frame
    Props::ItemPropertyFloat radiusWire;           //!< Wire radius
    Props::ItemPropertyQuality qualityWire;        //!< Wire circle quality
    Props::ItemPropertyMaterialRGBA materialWire;  //!< Wire-frame material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _radius Initial circle radius
     * \param _quality Initial circle quality
     * \param _show Initial value for show circle mode
     * \param _showWire Initial value for show circle wire-frame
     * \param _material Initial value for single material
     * \param _materialCenter Initial value for center material
     * \param _materialBorder Initial value for border material
     * \param _materialWire Initial value for wire material
     * \param _radiusWire Initial value for wire radius
     * \param _qualityWire Initial value for wire circle quality
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemCircleCamera(const std::string &_name = "Circle",
                     const Math::Vec3F &_center = {},
                     const float _radius = 0.5f,
                     const size_t _quality = ItemDefaultValues::sphereQuality,
                     const Circle::ShowCircleCameraType _show = Circle::CircleCameraSingle,
                     const bool _showWire = false,
                     const Math::MaterialRGB &_material = {Qt::white},
                     const Math::MaterialRGBA &_materialCenter = {Qt::red},
                     const Math::MaterialRGBA &_materialBorder = {Qt::green},
                     const Math::MaterialRGBA &_materialWire = {ItemDefaultValues::lineColor},
                     const float _radiusWire = ItemDefaultValues::lineRadius,
                     const size_t _qualityWire = ItemDefaultValues::lineQuality,
                     const uint8_t _alpha = 255U,
                     const bool _visible = true);

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _camera Camera data
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data,
                        const Math::CamF &_camera,
                        const size_t _timeStep) const override;
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMCIRCLE_H
