/*!
 * \file src/Items/Path/itempath.h
 * \brief Dynamic 3D line path video item
 */

#ifndef ITEMS_ITEMPATH_H
#define ITEMS_ITEMPATH_H

#include "../item3d.h"

#include "../../ItemProps/itempropertypattern.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic 3D line path video item */
class ItemPath : public Item3D
{
 public:
    const std::vector<Math::OrientF> path;  //!< Path vertices
    const Math::Vec3F pathCenter;           //!< Path central position
    const float pathLength;                 //!< Path length

    Props::ItemPropertyFloat radius;          //!< Path line radius
    Props::ItemPropertyPattern pattern;       //!< Path line pattern
    Props::ItemPropertyQuality quality;       //!< Line circle quality
    Props::ItemPropertyMaterialRGB material;  //!< Path material

    /*!
     * \brief Constructor
     * \param _path Path vertices
     * \param _name Item name
     * \param _radius Initial path line radius
     * \param _pattern Initial path line pattern
     * \param _quality Initial line circle quality
     * \param _material Initial path material
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPath(const std::vector<Math::OrientF> &_path,
             const std::string &_name = "Path",
             const float _radius = ItemDefaultValues::lineRadius,
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

 public:
    /*!
     * \brief Create 3D path Open GL data objects
     * \param _data Output data objects
     * \param _path Path points
     * \param _pathCenter Path center point
     * \param _pathLength Path length
     * \param _pathRadius Path line radius
     * \param _pattern Path line pattern
     * \param _quality Path line circle quality
     * \param _material Material
     * \param _alpha Alpha
     * \param _invertedIndices Flag - use inverted indexes
     * \return
     */
    static void createPath(std::list<OpenGL::Data3D *> &_data,
                           const std::vector<Math::OrientF> &_path,
                           const Math::Vec3F &_pathCenter,
                           const float _pathLength,
                           const float _pathRadius,
                           const size_t _pattern,
                           const size_t _quality,
                           const Math::MaterialRGB &_material,
                           const uint8_t _alpha,
                           const bool _invertedIndices = false);
};

/*! \brief Dynamic 3D line colored path video item */
class ItemPathColor : public Item3D
{
 public:
    const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path;  //!< Path vertices
    const Math::Vec3F pathCenter;                                      //!< Path central position
    const float pathLength;                                            //!< Path length

    Props::ItemPropertyFloat radius;     //!< Path line radius
    Props::ItemPropertyPattern pattern;  //!< Path line pattern
    Props::ItemPropertyQuality quality;  //!< Line circle quality

    /*!
     * \brief Constructor
     * \param _path Path vertices
     * \param _name Item name
     * \param _radius Initial path line radius
     * \param _pattern Initial path line pattern
     * \param _quality Initial line circle quality
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathColor(const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                  const std::string &_name = "Path",
                  const float _radius = ItemDefaultValues::lineRadius,
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

 public:
    /*!
     * \brief Create 3D path Open GL data objects
     * \param _data Output data objects
     * \param _path Path points
     * \param _pathCenter Path center point
     * \param _pathLength Path length
     * \param _pathRadius Path line radius
     * \param _pattern Path line pattern
     * \param _quality Path line circle quality
     * \param _alpha Alpha
     * \param _invertedIndices Flag - use inverted indexes
     * \return
     */
    static void createPath(std::list<OpenGL::Data3D *> &_data,
                           const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                           const Math::Vec3F &_pathCenter,
                           const float _pathLength,
                           const float _pathRadius,
                           const size_t _pattern,
                           const size_t _quality,
                           const uint8_t _alpha,
                           const bool _invertedIndices = false);
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMPATH_H
