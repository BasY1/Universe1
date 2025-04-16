/*!
 * \file src/Items/Triangle/itemtriangle.h
 * \brief Dynamic triangle video item
 */

#ifndef ITEMS_ITEMTRIANGLE_H
#define ITEMS_ITEMTRIANGLE_H

#include "../item3d.h"

#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertyvec3.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::Triangle
 * \brief 3D Triangle item tools
 */
namespace Triangle {
Q_NAMESPACE

/*! \brief Show triangle modes */
enum ShowTriangleType : int
{
    TriangleFrontBack,        //!< Show single color triangle visible from both front and back
    TriangleFront,            //!< Show single color triangle visible from front
    TriangleBack,             //!< Show single color triangle visible from back
    TriangleVertexFrontBack,  //!< Show triangle visible from both front and back (per vertex color)
    TriangleVertexFront,      //!< Show triangle visible from front (per vertex color)
    TriangleVertexBack,       //!< Show triangle visible from back (per vertex color)
};
Q_ENUM_NS(ShowTriangleType)

}  // namespace Triangle

/*! \brief Dynamic triangle video item */
class ItemTriangle : public Item3D
{
 public:
    Props::ItemPropertyVec3F point1;  //!< Dynamic position of point 1
    Props::ItemPropertyVec3F point2;  //!< Dynamic position of point 2
    Props::ItemPropertyVec3F point3;  //!< Dynamic position of point 3

    Props::ItemPropertyEnum show;                    //!< Show triangle mode
    Props::ItemPropertyMaterialRGB materialFront;    //!< Front side material
    Props::ItemPropertyMaterialRGB materialBack;     //!< Back side material
    Props::ItemPropertyMaterialRGBA material1Front;  //!< Vertex 1 front side material
    Props::ItemPropertyMaterialRGBA material2Front;  //!< Vertex 2 front side material
    Props::ItemPropertyMaterialRGBA material3Front;  //!< Vertex 3 front side material
    Props::ItemPropertyMaterialRGBA material1Back;   //!< Vertex 1 back side material
    Props::ItemPropertyMaterialRGBA material2Back;   //!< Vertex 2 back side material
    Props::ItemPropertyMaterialRGBA material3Back;   //!< Vertex 3 back side material

    Props::ItemPropertyBool showWire;              //!< Show triangle wire-frame
    Props::ItemPropertyFloat radiusWire;           //!< Wire radius
    Props::ItemPropertyQuality qualityWire;        //!< Wire circle quality
    Props::ItemPropertyMaterialRGBA materialWire;  //!< Wire-frame material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _point1 Initial value for dynamic position of point 1
     * \param _point2 Initial value for dynamic position of point 2
     * \param _point3 Initial value for dynamic position of point 3
     * \param _show Initial value for show triangle mode
     * \param _showWire Initial value for show triangle wire-frame
     * \param _materialFront Initial value for front side material
     * \param _materialBack Initial value for back side material
     * \param _material1Front Initial value for vertex 1 front side material
     * \param _material2Front Initial value for vertex 2 front side material
     * \param _material3Front Initial value for vertex 3 front side material
     * \param _material1Back Initial value for vertex 1 back side material
     * \param _material2Back Initial value for vertex 2 back side material
     * \param _material3Back Initial value for vertex 3 back side material
     * \param _materialWire Initial value for wire material
     * \param _radiusWire Initial value for wire radius
     * \param _qualityWire Initial value for wire circle quality
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemTriangle(const std::string &_name = "Triangle",
                 const Math::Vec3F &_point1 = {0.0F, +0.5F, -0.5F},
                 const Math::Vec3F &_point2 = {0.0F, -0.5F, -0.5F},
                 const Math::Vec3F &_point3 = {0.0F, 0.0F, 0.5F},
                 const Triangle::ShowTriangleType _show = Triangle::TriangleFrontBack,
                 const bool _showWire = false,
                 const Math::MaterialRGB &_materialFront = {Qt::white},
                 const Math::MaterialRGB &_materialBack = {Qt::lightGray},
                 const Math::MaterialRGBA &_material1Front = {Qt::red},
                 const Math::MaterialRGBA &_material2Front = {Qt::green},
                 const Math::MaterialRGBA &_material3Front = {Qt::blue},
                 const Math::MaterialRGBA &_material1Back = {Qt::yellow},
                 const Math::MaterialRGBA &_material2Back = {Qt::cyan},
                 const Math::MaterialRGBA &_material3Back = {Qt::magenta},
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

#endif  // ITEMS_ITEMTRIANGLE_H
