/*!
 * \file src/Items/Circle/itemcirclearc.h
 * \brief Dynamic circle arc video item
 */

#ifndef ITEMS_ITEMCIRCLEARC_H
#define ITEMS_ITEMCIRCLEARC_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::CircleArc
 * \brief 3D Circle arc item tools
 */
namespace CircleArc {
Q_NAMESPACE

/*! \brief Show circle arc modes */
enum ShowCircleArcType : int
{
    CircleArcFrontBack,  //!< Single color circle visible from both front and back
    CircleArcFront,      //!< Single color circle visible from front
    CircleArcBack,       //!< Single color circle visible from back

    CircleArcBorderFrontBack,  //!< Two color circle visible from both front and back
    CircleArcBorderFront,      //!< Two color circle visible from front
    CircleArcBorderBack,       //!< Two color circle visible from back
};
Q_ENUM_NS(ShowCircleArcType)

/*! \brief Show circle arc modes */
enum ShowCircleArcCameraType : int
{
    CircleArcCameraSingle,  //!< Single color circle
    CircleArcCameraBorder,  //!< Two color circle
};
Q_ENUM_NS(ShowCircleArcCameraType)

}  // namespace CircleArc

/*! \brief Dynamic circle arc video item */
class ItemCircleArc : public Item3DExt
{
 public:
    Props::ItemPropertyFloat angleStart;  //!< Starting angle for circle arc (in radians)
    Props::ItemPropertyFloat angleEnd;    //!< Ending angle for circle arc (in radians)
    Props::ItemPropertyFloat radius;      //!< Circle radius
    Props::ItemPropertyQuality quality;   //!< Circle quality

    Props::ItemPropertyEnum show;  //!< Show circle mode

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
     * \param _angleStart Initial starting angle for circle arc (in radians)
     * \param _angleEnd Initial ending angle for circle arc (in radians)
     * \param _radius Initial circle radius
     * \param _quality Initial circle quality
     * \param _show Initial value for show circle mode
     * \param _materialFront Initial value for front side material
     * \param _materialBack Initial value for back side material
     * \param _materialCenterFront Initial value for center front side material
     * \param _materialBorderFront Initial value for border front side material
     * \param _materialCenterBack  Initial value for center back side material
     * \param _materialBorderBack  Initial value for border back side material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemCircleArc(const std::string &_name = "Circle-arc",
                  const Math::Vec3F &_center = {},
                  const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                  const Math::Vec3F &_arm = Math::Vec3F::unitY(),
                  const float _angleStart = 0.0f,
                  const float _angleEnd = M_PI,
                  const float _radius = 0.5f,
                  const size_t _quality = ItemDefaultValues::sphereQuality,
                  const CircleArc::ShowCircleArcType _show = CircleArc::CircleArcFrontBack,
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

/*! \brief Dynamic circle arc video item with the plane normal that is always oriented towards camera position */
class ItemCircleArcCamera : public Item3D
{
 public:
    Props::ItemPropertyVec3F center;      //!< Circle center point
    Props::ItemPropertyFloat angleStart;  //!< Starting angle for circle arc (in radians)
    Props::ItemPropertyFloat angleEnd;    //!< Ending angle for circle arc (in radians)
    Props::ItemPropertyFloat radius;      //!< Circle radius
    Props::ItemPropertyQuality quality;   //!< Circle quality

    Props::ItemPropertyEnum show;                    //!< Show circle mode
    Props::ItemPropertyMaterialRGB material;         //!< Single material
    Props::ItemPropertyMaterialRGBA materialCenter;  //!< Vertex 1 material
    Props::ItemPropertyMaterialRGBA materialBorder;  //!< Vertex 2 material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _angleStart Initial starting angle for circle arc (in radians)
     * \param _angleEnd Initial ending angle for circle arc (in radians)
     * \param _radius Initial circle radius
     * \param _quality Initial circle quality
     * \param _show Initial value for show circle mode
     * \param _material Initial value for single material
     * \param _materialCenter Initial value for center material
     * \param _materialBorder Initial value for border material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemCircleArcCamera(const std::string &_name = "Circle-arc",
                        const Math::Vec3F &_center = {},
                        const float _angleStart = 0.0f,
                        const float _angleEnd = M_PI,
                        const float _radius = 0.5f,
                        const size_t _quality = ItemDefaultValues::sphereQuality,
                        const CircleArc::ShowCircleArcCameraType _show = CircleArc::CircleArcCameraSingle,
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

#endif  // ITEMS_ITEMCIRCLEARC_H
