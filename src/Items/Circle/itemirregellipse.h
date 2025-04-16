/*!
 * \file src/Items/Circle/itemirregellipse.h
 * \brief Dynamic irregular ellipse video item
 */

#ifndef ITEMS_ITEMIRREGELLIPSE_H
#define ITEMS_ITEMIRREGELLIPSE_H

#include "itemellipse.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic irregular ellipse video item */
class ItemIrregEllipse : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius1P;   //!< Ellipse radius 1 positive orientation within the normal 2 (arm)
    Props::ItemPropertyFloat radius1M;   //!< Ellipse radius 1 negative orientation within the normal 2 (arm)
    Props::ItemPropertyFloat radius2P;   //!< Ellipse radius 2 positive orientation within the normal 3
    Props::ItemPropertyFloat radius2M;   //!< Ellipse radius 2 negative orientation within the normal 3
    Props::ItemPropertyQuality quality;  //!< Ellipse quality

    Props::ItemPropertyEnum show;  //!< Show ellipse mode

    Props::ItemPropertyMaterialRGB materialFront;  //!< Front side material
    Props::ItemPropertyMaterialRGB materialBack;   //!< Back side material

    Props::ItemPropertyMaterialRGBA materialCenterFront;  //!< Center front side material
    Props::ItemPropertyMaterialRGBA materialBorderFront;  //!< Border front side material
    Props::ItemPropertyMaterialRGBA materialCenterBack;   //!< Center back side material
    Props::ItemPropertyMaterialRGBA materialBorderBack;   //!< Border back side material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _radius1P Initial ellipse radius 1 positive orientation within the normal 2 (arm)
     * \param _radius1M Initial ellipse radius 1 negative orientation within the normal 2 (arm)
     * \param _radius2P Initial ellipse radius 2 positive orientation within the normal 3
     * \param _radius2M Initial ellipse radius 2 negative orientation within the normal 3
     * \param _quality Initial ellipse quality
     * \param _show Initial value for show ellipse mode
     * \param _materialFront Initial value for front side material
     * \param _materialBack Initial value for back side material
     * \param _materialCenterFront Initial value for center front side material
     * \param _materialBorderFront Initial value for border front side material
     * \param _materialCenterBack  Initial value for center back side material
     * \param _materialBorderBack  Initial value for border back side material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemIrregEllipse(const std::string &_name = "Ellipse",
                     const Math::Vec3F &_center = {},
                     const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                     const Math::Vec3F &_arm = Math::Vec3F::unitY(),
                     const float _radius1P = 1.0f,
                     const float _radius1M = 0.8f,
                     const float _radius2P = 0.6f,
                     const float _radius2M = 0.4f,
                     const size_t _quality = ItemDefaultValues::sphereQuality,
                     const Ellipse::ShowEllipseType _show = Ellipse::EllipseFrontBack,
                     const Math::MaterialRGB &_materialFront = {Qt::white},
                     const Math::MaterialRGB &_materialBack = {Qt::lightGray},
                     const Math::MaterialRGBA &_materialCenterFront = {Qt::red},
                     const Math::MaterialRGBA &_materialBorderFront = {Qt::green},
                     const Math::MaterialRGBA &_materialCenterBack = {Qt::blue},
                     const Math::MaterialRGBA &_materialBorderBack = {Qt::white},
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

/*! \brief Dynamic ellipse video item with the plane normal that is always oriented towards camera position */
class ItemIrregEllipseCamera : public Item3D
{
 public:
    Props::ItemPropertyVec3F center;     //!< Ellipse center point
    Props::ItemPropertyFloat radius1P;   //!< Ellipse radius 1 positive orientation within the normal 2 (arm)
    Props::ItemPropertyFloat radius1M;   //!< Ellipse radius 1 negative orientation within the normal 2 (arm)
    Props::ItemPropertyFloat radius2P;   //!< Ellipse radius 2 positive orientation within the normal 3
    Props::ItemPropertyFloat radius2M;   //!< Ellipse radius 2 negative orientation within the normal 3
    Props::ItemPropertyQuality quality;  //!< Ellipse quality

    Props::ItemPropertyEnum show;                    //!< Show ellipse mode
    Props::ItemPropertyMaterialRGB material;         //!< Single material
    Props::ItemPropertyMaterialRGBA materialCenter;  //!< Vertex 1 material
    Props::ItemPropertyMaterialRGBA materialBorder;  //!< Vertex 2 material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _radius1P Initial ellipse radius 1 positive orientation within the normal 2 (arm)
     * \param _radius1M Initial ellipse radius 1 negative orientation within the normal 2 (arm)
     * \param _radius2P Initial ellipse radius 2 positive orientation within the normal 3
     * \param _radius2M Initial ellipse radius 2 negative orientation within the normal 3
     * \param _quality Initial ellipse quality
     * \param _show Initial value for show ellipse mode
     * \param _material Initial value for single material
     * \param _materialCenter Initial value for center material
     * \param _materialBorder Initial value for border material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemIrregEllipseCamera(const std::string &_name = "Ellipse",
                           const Math::Vec3F &_center = {},
                           const float _radius1P = 1.0f,
                           const float _radius1M = 0.8f,
                           const float _radius2P = 0.6f,
                           const float _radius2M = 0.4f,
                           const size_t _quality = ItemDefaultValues::sphereQuality,
                           const Ellipse::ShowEllipseCameraType _show = Ellipse::EllipseCameraSingle,
                           const Math::MaterialRGB &_material = {Qt::white},
                           const Math::MaterialRGBA &_materialCenter = {Qt::red},
                           const Math::MaterialRGBA &_materialBorder = {Qt::green},
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

#endif  // ITEMS_ITEMIRREGELLIPSE_H
