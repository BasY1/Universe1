/*!
 * \file src/Items/Path/itempathspiralarc.h
 * \brief Dynamic 3D line arc spiral path video item
 */

#ifndef ITEMS_ITEMPATHSPIRALARC_H
#define ITEMS_ITEMPATHSPIRALARC_H

#include "../item3d.h"

#include "../../ItemProps/itempropertypattern.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic 3D line arc spiral path video item */
class ItemPathSpiralArc : public Item3DExt
{
 public:
    Props::ItemPropertyBool sign;             //!< Helicity sign
    Props::ItemPropertyFloat angleStart;      //!< Start spiral angle in radians
    Props::ItemPropertyFloat angleEnd;        //!< End spiral angle in radians
    Props::ItemPropertyFloat length;          //!< Period length
    Props::ItemPropertyFloat radiusArc;       //!< Arc curve radius
    Props::ItemPropertyFloat radiusSpiral;    //!< Spiral radius
    Props::ItemPropertyFloat radiusLine;      //!< Line path circle radius
    Props::ItemPropertyPattern pattern;       //!< Line pattern
    Props::ItemPropertyQuality quality;       //!< Spiral curve quality
    Props::ItemPropertyQuality qualityLine;   //!< Line circle quality
    Props::ItemPropertyMaterialRGB material;  //!< Material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _sign Initial helicity sign
     * \param _angleStart Initial start angle in radians
     * \param _angleEnd Initial end angle in radians
     * \param _length Initial Period length
     * \param _radiusArc Initial arc radius
     * \param _radiusSpiral Initial spiral radius
     * \param _radiusLine Initial path circle radius
     * \param _pattern Initial line pattern
     * \param _quality Initial spiral curve quality
     * \param _qualityLine Initial line circle quality
     * \param _material Initial material
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathSpiralArc(const std::string &_name = "Spiral-arc",
                      const Math::Vec3F &_center = {},
                      const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
                      const Math::Vec3F &_arm = Math::Vec3F::unitX(),
                      const bool _sign = true,
                      const float _angleStart = 0.0f,
                      const float _angleEnd = 2.0 * M_PI,
                      const float _length = 1.0f,
                      const float _radiusArc = 10.0f,
                      const float _radiusSpiral = 0.5f,
                      const float _radiusLine = ItemDefaultValues::lineRadius,
                      const uint64_t _pattern = PATTERN_SOLID,
                      const uint64_t _quality = ItemDefaultValues::sphereQuality,
                      const uint64_t _qualityLine = ItemDefaultValues::lineQuality,
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

/*! \brief Dynamic 3D line spiral path video item - with start and end color */
class ItemPathSpiralArc2Color : public Item3DExt
{
 public:
    Props::ItemPropertyBool sign;            //!< Helicity sign
    Props::ItemPropertyFloat angleStart;     //!< Start spiral angle in radians
    Props::ItemPropertyFloat angleEnd;       //!< End spiral angle in radians
    Props::ItemPropertyFloat length;         //!< Period length
    Props::ItemPropertyFloat radiusArc;      //!< Arc curve radius
    Props::ItemPropertyFloat radiusSpiral;   //!< Spiral radius
    Props::ItemPropertyFloat radiusLine;     //!< Line path circle radius
    Props::ItemPropertyPattern pattern;      //!< Line pattern
    Props::ItemPropertyQuality quality;      //!< Spiral curve quality
    Props::ItemPropertyQuality qualityLine;  //!< Line circle quality
    Props::ItemPropertyColor colorStart;     //!< Color at start
    Props::ItemPropertyColor colorEnd;       //!< Color at end

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _sign Initial helicity sign
     * \param _angleStart Initial start angle in radians
     * \param _angleEnd Initial end angle in radians
     * \param _length Initial Period length
     * \param _radiusArc Initial arc radius
     * \param _radiusSpiral Initial spiral radius
     * \param _radiusLine Initial path circle radius
     * \param _pattern Initial line pattern
     * \param _quality Initial spiral curve quality
     * \param _qualityLine Initial line circle quality
     * \param _colorStart Initial color at start
     * \param _colorEnd Initial color at end
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathSpiralArc2Color(const std::string &_name = "Spiral-arc",
                            const Math::Vec3F &_center = {},
                            const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
                            const Math::Vec3F &_arm = Math::Vec3F::unitX(),
                            const bool _sign = true,
                            const float _angleStart = 0.0f,
                            const float _angleEnd = 2.0 * M_PI,
                            const float _length = 1.0f,
                            const float _radiusArc = 10.0f,
                            const float _radiusSpiral = 0.5f,
                            const float _radiusLine = ItemDefaultValues::lineRadius,
                            const uint64_t _pattern = PATTERN_SOLID,
                            const uint64_t _quality = ItemDefaultValues::sphereQuality,
                            const uint64_t _qualityLine = ItemDefaultValues::lineQuality,
                            const Math::ColorRGB &_colorStart = {Qt::red},
                            const Math::ColorRGB &_colorEnd = {Qt::green},
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

/*! \brief Dynamic 3D line rainbow color spiral path video item */
class ItemPathSpiralArcRainbow : public Item3DExt
{
 public:
    Props::ItemPropertyBool sign;            //!< Helicity sign
    Props::ItemPropertyFloat angleStart;     //!< Start spiral angle in radians
    Props::ItemPropertyFloat angleEnd;       //!< End spiral angle in radians
    Props::ItemPropertyFloat length;         //!< Period length
    Props::ItemPropertyFloat radiusArc;      //!< Arc curve radius
    Props::ItemPropertyFloat radiusSpiral;   //!< Spiral radius
    Props::ItemPropertyFloat radiusLine;     //!< Line path circle radius
    Props::ItemPropertyPattern pattern;      //!< Line pattern
    Props::ItemPropertyQuality quality;      //!< Spiral curve quality
    Props::ItemPropertyQuality qualityLine;  //!< Line circle quality

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _sign Initial helicity sign
     * \param _angleStart Initial start angle in radians
     * \param _angleEnd Initial end angle in radians
     * \param _length Initial Period length
     * \param _radiusArc Initial arc radius
     * \param _radiusSpiral Initial spiral radius
     * \param _radiusLine Initial path circle radius
     * \param _pattern Initial line pattern
     * \param _quality Initial spiral curve quality
     * \param _qualityLine Initial line circle quality
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemPathSpiralArcRainbow(const std::string &_name = "Spiral-arc",
                             const Math::Vec3F &_center = {},
                             const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
                             const Math::Vec3F &_arm = Math::Vec3F::unitX(),
                             const bool _sign = true,
                             const float _angleStart = 0.0f,
                             const float _angleEnd = 2.0 * M_PI,
                             const float _length = 1.0f,
                             const float _radiusArc = 10.0f,
                             const float _radiusSpiral = 0.5f,
                             const float _radiusLine = ItemDefaultValues::lineRadius,
                             const uint64_t _pattern = PATTERN_SOLID,
                             const uint64_t _quality = ItemDefaultValues::sphereQuality,
                             const uint64_t _qualityLine = ItemDefaultValues::lineQuality,
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

#endif  // ITEMS_ITEMPATHSPIRALARC_H
