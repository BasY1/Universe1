/*!
 * \file src/Items/Sphere/itemirregellipsoid.h
 * \brief Dynamic irregular ellipsoid video item
 */

#ifndef ITEMS_ITEMIRREGELLIPSOID_H
#define ITEMS_ITEMIRREGELLIPSOID_H

#include "itemellipsoid.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic ellipsoid video item */
class ItemIrregEllipsoid : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius1P;   //!< Ellipsoid radius along normal direction
    Props::ItemPropertyFloat radius1M;   //!< Ellipsoid radius along opposite of a normal direction
    Props::ItemPropertyFloat radius2P;   //!< Ellipsoid radius along arm direction
    Props::ItemPropertyFloat radius2M;   //!< Ellipsoid radius along opposite of a arm direction
    Props::ItemPropertyFloat radius3P;   //!< Ellipsoid radius along third perpendicular normal
    Props::ItemPropertyFloat radius3M;   //!< Ellipsoid radius along opposite of a third perpendicular normal
    Props::ItemPropertyQuality quality;  //!< Ellipsoid quality

    Props::ItemPropertyEnum show;  //!< Show ellipsoid mode

    Props::ItemPropertyMaterialRGB materialOuter;  //!< Outer ellipsoid material
    Props::ItemPropertyMaterialRGB materialInner;  //!< Inner ellipsoid material

    Props::ItemPropertyText textureImage;  //!< Path to the texture image file

    Props::ItemPropertyBool showWire;              //!< Show ellipsoid wire-frame
    Props::ItemPropertyFloat radiusWire;           //!< Wire radius
    Props::ItemPropertyFloat stepWire;             //!< Wire-frame matrix step
    Props::ItemPropertyQuality qualityWire;        //!< Wire circle quality
    Props::ItemPropertyMaterialRGBA materialWire;  //!< Wire-frame material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _radius1P Initial ellipsoid radius 1 along normal direction
     * \param _radius1M Initial ellipsoid radius 1 along opposite of a normal direction
     * \param _radius2P Initial ellipsoid radius 2 along arm direction
     * \param _radius2M Initial ellipsoid radius 2 along opposite of a arm direction
     * \param _radius3P Initial ellipsoid radius 3 along third perpendicular normal
     * \param _radius3M Initial ellipsoid radius 3 along opposite of a third perpendicular normal
     * \param _quality Initial ellipsoid quality
     * \param _show Initial value for show ellipsoid mode
     * \param _showWire Initial value for show ellipsoid wire-frame
     * \param _textureImage Initial value for a path to the texture image file
     * \param _materialOuter Initial value for outer ellipsoid material
     * \param _materialInner Initial value for inner ellipsoid material
     * \param _materialWire Initial value for wire material
     * \param _radiusWire Initial value for wire radius
     * \param _stepWire Initial value for wire-frame matrix step
     * \param _qualityWire Initial value for wire circle quality
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemIrregEllipsoid(const std::string &_name = "Ellipsoid",
                       const Math::Vec3F &_center = {},
                       const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
                       const Math::Vec3F &_arm = Math::Vec3F::unitX(),
                       const float _radius1P = 0.3f,
                       const float _radius1M = 0.7f,
                       const float _radius2P = 0.4f,
                       const float _radius2M = 0.6f,
                       const float _radius3P = 0.2f,
                       const float _radius3M = 0.8f,
                       const size_t _quality = ItemDefaultValues::sphereQuality,
                       const Ellipsoid::ShowEllipsoidType _show = Ellipsoid::EllipsoidOuter,
                       const bool _showWire = false,
                       const QString &_textureImage = "",
                       const Math::MaterialRGB &_materialOuter = {Qt::white},
                       const Math::MaterialRGB &_materialInner = {Qt::lightGray},
                       const Math::MaterialRGBA &_materialWire = {ItemDefaultValues::lineColor},
                       const float _radiusWire = ItemDefaultValues::lineRadius,
                       const float _stepWire = 0.5f,
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

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMIRREGELLIPSOID_H
