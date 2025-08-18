/*!
 * \file src/Items/Path/itempathbezier.h
 * \brief Dynamic 3D line - bezier curve path video item
 */

#ifndef ITEMS_ITEMPATHBEZIER_H
#define ITEMS_ITEMPATHBEZIER_H

#include "../item3d.h"

#include "../../ItemProps/itempropertypattern.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic 3D line - bezier curve path video item */
class ItemPathBezier : public Item3D
{
 public:
    Props::ItemPropertyVec3F point1;          //!< Point 1
    Props::ItemPropertyVec3F point2;          //!< Point 2
    Props::ItemPropertyVec3F normal1;         //!< Normal direction for point 1
    Props::ItemPropertyVec3F normal2;         //!< Normal direction for point 2
    Props::ItemPropertyFloat weight1;         //!< Normal 1 weight
    Props::ItemPropertyFloat weight2;         //!< Normal 2 weight
    Props::ItemPropertyFloat radius;          //!< Line path circle radius
    Props::ItemPropertyUInt16 segments;       //!< Line path segment count
    Props::ItemPropertyPattern pattern;       //!< Line pattern
    Props::ItemPropertyQuality quality;       //!< Line circle quality
    Props::ItemPropertyMaterialRGB material;  //!< Material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _point1 Initial point 1
     * \param _point2 Initial point 2
     * \param _normal1 Initial normal 1
     * \param _normal2 Initial normal 2
     * \param _weight1 Initial normal 1 weight
     * \param _weight2 Initial normal 2 weight
     * \param _radius Initial path circle radius
     * \param _segments Initial line path segment count
     * \param _pattern Initial line pattern
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathBezier(const std::string &_name = "Bezier",
                   const Math::Vec3F &_point1 = {},
                   const Math::Vec3F &_point2 = {0, 0, 1},
                   const Math::Vec3F &_normal1 = Math::Vec3F::unitZ(),
                   const Math::Vec3F &_normal2 = Math::Vec3F::unitX(),
                   const float _weight1 = 1.0f,
                   const float _weight2 = 1.0f,
                   const float _radius = ItemDefaultValues::lineRadius,
                   const uint16_t _segments = 32U,
                   const uint64_t _pattern = PATTERN_SOLID,
                   const uint64_t _quality = ItemDefaultValues::lineQuality,
                   const Math::MaterialRGB &_material = {Qt::white},
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

/*! \brief Dynamic 3D line - bezier curve path video item - with start and end color */
class ItemPathBezier2Color : public Item3D
{
 public:
    Props::ItemPropertyVec3F point1;     //!< Point 1
    Props::ItemPropertyVec3F point2;     //!< Point 2
    Props::ItemPropertyVec3F normal1;    //!< Normal direction for point 1
    Props::ItemPropertyVec3F normal2;    //!< Normal direction for point 2
    Props::ItemPropertyFloat weight1;    //!< Normal 1 weight
    Props::ItemPropertyFloat weight2;    //!< Normal 2 weight
    Props::ItemPropertyFloat radius;     //!< Line path circle radius
    Props::ItemPropertyUInt16 segments;  //!< Line path segment count
    Props::ItemPropertyPattern pattern;  //!< Line pattern
    Props::ItemPropertyQuality quality;  //!< Line circle quality
    Props::ItemPropertyColor color1;     //!< Color at point 1
    Props::ItemPropertyColor color2;     //!< Color at point 2

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _point1 Initial point 1
     * \param _point2 Initial point 2
     * \param _normal1 Initial normal 1
     * \param _normal2 Initial normal 2
     * \param _weight1 Initial normal 1 weight
     * \param _weight2 Initial normal 2 weight
     * \param _radius Initial path circle radius
     * \param _segments Initial line path segment count
     * \param _pattern Initial line pattern
     * \param _quality Initial line circle quality
     * \param _color1 Initial color point 1
     * \param _color2 Initial color point 2
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathBezier2Color(const std::string &_name = "Bezier",
                         const Math::Vec3F &_point1 = {},
                         const Math::Vec3F &_point2 = {0, 0, 1},
                         const Math::Vec3F &_normal1 = Math::Vec3F::unitZ(),
                         const Math::Vec3F &_normal2 = Math::Vec3F::unitX(),
                         const float _weight1 = 1.0f,
                         const float _weight2 = 1.0f,
                         const float _radius = ItemDefaultValues::lineRadius,
                         const uint16_t _segments = 32U,
                         const uint64_t _pattern = PATTERN_SOLID,
                         const uint64_t _quality = ItemDefaultValues::lineQuality,
                         const Math::ColorRGB &_color1 = {Qt::red},
                         const Math::ColorRGB &_color2 = {Qt::green},
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

/*! \brief Dynamic 3D line - bezier curve path video item */
class ItemPathBezierRainbow : public Item3D
{
 public:
    Props::ItemPropertyVec3F point1;     //!< Point 1
    Props::ItemPropertyVec3F point2;     //!< Point 2
    Props::ItemPropertyVec3F normal1;    //!< Normal direction for point 1
    Props::ItemPropertyVec3F normal2;    //!< Normal direction for point 2
    Props::ItemPropertyFloat weight1;    //!< Normal 1 weight
    Props::ItemPropertyFloat weight2;    //!< Normal 2 weight
    Props::ItemPropertyFloat radius;     //!< Line path circle radius
    Props::ItemPropertyUInt16 segments;  //!< Line path segment count
    Props::ItemPropertyPattern pattern;  //!< Line pattern
    Props::ItemPropertyQuality quality;  //!< Line circle quality

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _point1 Initial point 1
     * \param _point2 Initial point 2
     * \param _normal1 Initial normal 1
     * \param _normal2 Initial normal 2
     * \param _weight1 Initial normal 1 weight
     * \param _weight2 Initial normal 2 weight
     * \param _radius Initial path circle radius
     * \param _segments Initial line path segment count
     * \param _pattern Initial line pattern
     * \param _quality Initial line circle quality
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathBezierRainbow(const std::string &_name = "Bezier",
                          const Math::Vec3F &_point1 = {},
                          const Math::Vec3F &_point2 = {0, 0, 1},
                          const Math::Vec3F &_normal1 = Math::Vec3F::unitZ(),
                          const Math::Vec3F &_normal2 = Math::Vec3F::unitX(),
                          const float _weight1 = 1.0f,
                          const float _weight2 = 1.0f,
                          const float _radius = ItemDefaultValues::lineRadius,
                          const uint16_t _segments = 32U,
                          const uint64_t _pattern = PATTERN_SOLID,
                          const uint64_t _quality = ItemDefaultValues::lineQuality,
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

#endif  // ITEMS_ITEMPATHBEZIER_H
