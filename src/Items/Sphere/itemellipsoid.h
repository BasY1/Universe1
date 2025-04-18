/*!
 * \file src/Items/Sphere/itemellipsoid.h
 * \brief Dynamic ellipsoid video item
 */

#ifndef ITEMS_ITEMELLIPSOID_H
#define ITEMS_ITEMELLIPSOID_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertytext.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::Ellipsoid
 * \brief 3D Ellipsoid item tools
 */
namespace Ellipsoid {
Q_NAMESPACE

/*! \brief Show ellipsoid modes */
enum ShowEllipsoidType : int
{
    EllipsoidHidden,  //!< Ellipsoid plane hidden

    EllipsoidInnerOuter,  //!< Single color ellipsoid visible from both inside and outside
    EllipsoidOuter,       //!< Single color ellipsoid visible from outside
    EllipsoidInner,       //!< Single color ellipsoid visible from inside

    EllipsoidTextureInnerOuter,  //!< Ellipsoid texture visible from both inside and outside
    EllipsoidTextureOuter,       //!< Ellipsoid texture visible from inside
    EllipsoidTextureInner,       //!< Ellipsoid texture visible from outside

    EllipsoidTextureSoccerBall,   //!< Ellipsoid with soccer ball texture
    EllipsoidTextureSoccerEarth,  //!< Ellipsoid with earth texture

};
Q_ENUM_NS(ShowEllipsoidType)

}  // namespace Ellipsoid

/*! \brief Dynamic ellipsoid video item */
class ItemEllipsoid : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius1;    //!< Ellipsoid radius along normal direction
    Props::ItemPropertyFloat radius2;    //!< Ellipsoid radius along arm direction
    Props::ItemPropertyFloat radius3;    //!< Ellipsoid radius along third perpendicular normal
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
     * \param _radius1 Initial ellipsoid radius 1
     * \param _radius2 Initial ellipsoid radius 2
     * \param _radius3 Initial ellipsoid radius 3
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
    ItemEllipsoid(const std::string &_name = "Ellipsoid",
                  const Math::Vec3F &_center = {},
                  const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
                  const Math::Vec3F &_arm = Math::Vec3F::unitX(),
                  const float _radius1 = 0.4f,
                  const float _radius2 = 0.5f,
                  const float _radius3 = 0.6f,
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

#endif  // ITEMS_ITEMELLIPSOID_H
