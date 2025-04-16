/*!
 * \file src/Items/Rectangle/itemrectangle.h
 * \brief Dynamic rectangle video item
 */

#ifndef ITEMS_ITEMRECTANGLE_H
#define ITEMS_ITEMRECTANGLE_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::Rectangle
 * \brief 3D Rectangle item tools
 */
namespace Rectangle {
Q_NAMESPACE

/*! \brief Show rectangle modes */
enum ShowRectangleType : int
{
    RectangleFrontBack,        //!< Show single color rectangle visible from both front and back
    RectangleFront,            //!< Show single color rectangle visible from front
    RectangleBack,             //!< Show single color rectangle visible from back
    RectangleVertexFrontBack,  //!< Show rectangle visible from both front and back (per vertex color)
    RectangleVertexFront,      //!< Show rectangle visible from front (per vertex color)
    RectangleVertexBack,       //!< Show rectangle visible from back (per vertex color)
};
Q_ENUM_NS(ShowRectangleType)

}  // namespace Rectangle

/*! \brief Dynamic rectangle video item */
class ItemRectangle : public Item3DExt
{
 public:
    Props::ItemPropertyFloat radius1;  //!< Rectangle radius (within the direction of arm)
    Props::ItemPropertyFloat radius2;  //!< Rectangle radius (within the perpendicular direction to the arm and normal)

    Props::ItemPropertyEnum show;                    //!< Show rectangle mode
    Props::ItemPropertyMaterialRGB materialFront;    //!< Front side material
    Props::ItemPropertyMaterialRGB materialBack;     //!< Back side material
    Props::ItemPropertyMaterialRGBA material1Front;  //!< Vertex 1 front side material
    Props::ItemPropertyMaterialRGBA material2Front;  //!< Vertex 2 front side material
    Props::ItemPropertyMaterialRGBA material3Front;  //!< Vertex 3 front side material
    Props::ItemPropertyMaterialRGBA material4Front;  //!< Vertex 3 front side material
    Props::ItemPropertyMaterialRGBA material1Back;   //!< Vertex 1 back side material
    Props::ItemPropertyMaterialRGBA material2Back;   //!< Vertex 2 back side material
    Props::ItemPropertyMaterialRGBA material3Back;   //!< Vertex 3 back side material
    Props::ItemPropertyMaterialRGBA material4Back;   //!< Vertex 3 back side material

    Props::ItemPropertyBool showWire;              //!< Show rectangle wire-frame
    Props::ItemPropertyFloat radiusWire;           //!< Wire radius
    Props::ItemPropertyQuality qualityWire;        //!< Wire circle quality
    Props::ItemPropertyMaterialRGBA materialWire;  //!< Wire-frame material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _radius1 Initial rectangle radius (within the direction of arm)
     * \param _radius2 Initial secondary rectangle radius (within the perpendicular direction to the arm and normal)
     * \param _show Initial value for show rectangle mode
     * \param _showWire Initial value for show rectangle wire-frame
     * \param _materialFront Initial value for front side material
     * \param _materialBack Initial value for back side material
     * \param _material1Front Initial value for vertex 1 front side material
     * \param _material2Front Initial value for vertex 2 front side material
     * \param _material3Front Initial value for vertex 3 front side material
     * \param _material4Front Initial value for vertex 4 front side material
     * \param _material1Back Initial value for vertex 1 back side material
     * \param _material2Back Initial value for vertex 2 back side material
     * \param _material3Back Initial value for vertex 3 back side material
     * \param _material4Back Initial value for vertex 4 back side material
     * \param _materialWire Initial value for wire material
     * \param _radiusWire Initial value for wire radius
     * \param _qualityWire Initial value for wire circle quality
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemRectangle(const std::string &_name = "Rectangle",
                  const Math::Vec3F &_center = {},
                  const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                  const Math::Vec3F &_arm = Math::Vec3F::unitY(),
                  const float _radius1 = 1.0f,
                  const float _radius2 = 0.5f,
                  const Rectangle::ShowRectangleType _show = Rectangle::RectangleFrontBack,
                  const bool _showWire = false,
                  const Math::MaterialRGB &_materialFront = {Qt::white},
                  const Math::MaterialRGB &_materialBack = {Qt::lightGray},
                  const Math::MaterialRGBA &_material1Front = {Qt::red},
                  const Math::MaterialRGBA &_material2Front = {Qt::green},
                  const Math::MaterialRGBA &_material3Front = {Qt::blue},
                  const Math::MaterialRGBA &_material4Front = {Qt::white},
                  const Math::MaterialRGBA &_material1Back = {Qt::yellow},
                  const Math::MaterialRGBA &_material2Back = {Qt::cyan},
                  const Math::MaterialRGBA &_material3Back = {Qt::magenta},
                  const Math::MaterialRGBA &_material4Back = {Qt::gray},
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

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMRECTANGLE_H
