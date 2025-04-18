/*!
 * \file src/Items/Sphere/itemsphere.h
 * \brief Dynamic sphere video item
 */

#ifndef ITEMS_ITEMSPHERE_H
#define ITEMS_ITEMSPHERE_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertytext.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::Sphere
 * \brief 3D Sphere item tools
 */
namespace Sphere {
Q_NAMESPACE

/*! \brief Show sphere visible modes */
enum ShowSphereType : int
{
    SphereHidden,  //!< Sphere plane hidden

    SphereInnerOuter,  //!< Single color sphere visible from both inside and outside
    SphereOuter,       //!< Single color sphere visible from outside
    SphereInner,       //!< Single color sphere visible from inside

    SphereTextureInnerOuter,  //!< Sphere texture visible from both inside and outside
    SphereTextureOuter,       //!< Sphere texture visible from inside
    SphereTextureInner,       //!< Sphere texture visible from outside

    SphereTextureSoccerBall,   //!< Sphere with soccer ball texture
    SphereTextureSoccerEarth,  //!< Sphere with earth texture

};
Q_ENUM_NS(ShowSphereType)

/*! \brief Show sphere cut visible modes */
enum ShowSphereCutType : int
{
    SphereCutInnerOuter,  //!< Single color sphere visible from both inside and outside
    SphereCutOuter,       //!< Single color sphere visible from outside
    SphereCutInner,       //!< Single color sphere visible from inside
};
Q_ENUM_NS(ShowSphereCutType)

/*! \brief Sphere wire-frame modes */
enum ShowSphereWireType : int
{
    SphereWireHidden,        //!< Sphere wire-frame hidden
    SphereWireLatLongStep,   //!< Latitude-longitude wire-frame style with constant wire step
    SphereWireLatLongFixed,  //!< Latitude-longitude wire-frame style with fixed number of latitudes and longitudes
    SphereWireXYZ,           //!< X-Y-Z plane wire-frame style
};
Q_ENUM_NS(ShowSphereWireType)

}  // namespace Sphere

/*! \brief Dynamic sphere video item */
class ItemSphere : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius;     //!< Sphere radius
    Props::ItemPropertyQuality quality;  //!< Sphere quality

    Props::ItemPropertyEnum show;  //!< Show sphere mode

    Props::ItemPropertyMaterialRGB materialOuter;  //!< Outer sphere material
    Props::ItemPropertyMaterialRGB materialInner;  //!< Inner sphere material

    Props::ItemPropertyText textureImage;  //!< Path to the texture image file

    Props::ItemPropertyEnum showWire;              //!< Show sphere wire-frame
    Props::ItemPropertyFloat radiusWire;           //!< Wire radius
    Props::ItemPropertyFloat stepWire;             //!< Wire-frame matrix step
    Props::ItemPropertyQuality qualityWire;        //!< Wire circle quality
    Props::ItemPropertyQuality qualityLatLong;     //!< Latitude-longitude step
    Props::ItemPropertyMaterialRGBA materialWire;  //!< Wire-frame material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere quality
     * \param _show Initial value for show sphere mode
     * \param _showWire Initial value for show sphere wire-frame
     * \param _textureImage Initial value for a path to the texture image file
     * \param _materialOuter Initial value for outer sphere material
     * \param _materialInner Initial value for inner sphere material
     * \param _materialWire Initial value for wire material
     * \param _radiusWire Initial value for wire radius
     * \param _stepWire Initial value for wire-frame matrix step
     * \param _qualityWire Initial value for wire circle quality
     * \param _qualityLatLong Initial value for latitude-longitude step
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemSphere(const std::string &_name = "Sphere",
               const Math::Vec3F &_center = {},
               const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
               const Math::Vec3F &_arm = Math::Vec3F::unitX(),
               const float _radius = 0.5f,
               const size_t _quality = ItemDefaultValues::sphereQuality,
               const Sphere::ShowSphereType _show = Sphere::SphereOuter,
               const Sphere::ShowSphereWireType _showWire = Sphere::SphereWireHidden,
               const QString &_textureImage = "",
               const Math::MaterialRGB &_materialOuter = {Qt::white},
               const Math::MaterialRGB &_materialInner = {Qt::lightGray},
               const Math::MaterialRGBA &_materialWire = {ItemDefaultValues::lineColor},
               const float _radiusWire = ItemDefaultValues::lineRadius,
               const float _stepWire = 0.5f,
               const size_t _qualityWire = ItemDefaultValues::lineQuality,
               const size_t _qualityLatLong = 7UL,
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

/*! \brief Dynamic sphere-cut video item */
class ItemSphereCut : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius;  //!< Sphere radius

    Props::ItemPropertyFloat angleLonStart;  //!< Longitude angle start in radians (0 to 2π)
    Props::ItemPropertyFloat angleLonEnd;    //!< Longitude angle end in radians (0 to 2π)
    Props::ItemPropertyFloat angleLatStart;  //!< Latitude angle start in radians (0 to π)
    Props::ItemPropertyFloat angleLatEnd;    //!< Latitude angle end in radians (0 to π)

    Props::ItemPropertyQuality quality;  //!< Sphere quality

    Props::ItemPropertyEnum show;  //!< Show sphere cut mode

    Props::ItemPropertyMaterialRGB materialOuter;  //!< Outer sphere material
    Props::ItemPropertyMaterialRGB materialInner;  //!< Inner sphere material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _radius Initial sphere radius
     * \param _angleLonStart Initial longitude angle start in radians (0 to 2π)
     * \param _angleLonEnd Initial longitude angle end in radians (0 to 2π)
     * \param _angleLatStart Initial latitude angle start in radians (0 to π)
     * \param _angleLatEnd Initial latitude angle end in radians (0 to π)
     * \param _quality Initial sphere quality
     * \param _show Initial value for show sphere mode
     * \param _materialOuter Initial value for outer sphere material
     * \param _materialInner Initial value for inner sphere material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemSphereCut(const std::string &_name = "Sphere",
                  const Math::Vec3F &_center = {},
                  const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
                  const Math::Vec3F &_arm = Math::Vec3F::unitX(),
                  const float _radius = 0.5f,
                  const float _angleLonStart = 0.0f,
                  const float _angleLonEnd = M_PI,
                  const float _angleLatStart = 0.0f,
                  const float _angleLatEnd = M_PI_2,
                  const size_t _quality = ItemDefaultValues::sphereQuality,
                  const Sphere::ShowSphereCutType _show = Sphere::SphereCutInnerOuter,
                  const Math::MaterialRGB &_materialOuter = {Qt::white},
                  const Math::MaterialRGB &_materialInner = {Qt::lightGray},
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

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMSPHERE_H
