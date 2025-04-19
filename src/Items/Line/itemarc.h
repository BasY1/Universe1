/*!
 * \file src/Items/Line/itemarc.h
 * \brief Dynamic 3D line arc video item
 */

#ifndef ITEMS_ITEMARC_H
#define ITEMS_ITEMARC_H

#include "itemline.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic 3D line arc video item */
class ItemArc : public Item3DExt
{
 public:
    Props::ItemPropertyFloat angle;          //!< Arc angle in radians
    Props::ItemPropertyFloat radiusArc;      //!< Arc radius
    Props::ItemPropertyFloat radiusLine;     //!< Line radius
    Props::ItemPropertyPattern pattern;      //!< Line pattern
    Props::ItemPropertyQuality qualityArc;   //!< Arc circle quality
    Props::ItemPropertyQuality qualityLine;  //!< Line circle quality

    Props::ItemPropertyBool arrowStart;    //!< Use line arrow at start
    Props::ItemPropertyBool arrowEnd;      //!< Use line arrow at end
    Props::ItemPropertyFloat arrowLength;  //!< Arrow length
    Props::ItemPropertyFloat arrowRadius;  //!< Arrow radius

    Props::ItemPropertyMaterialRGB material;       //!< Line material
    Props::ItemPropertyMaterialRGB materialBack;   //!< Line edge material
    Props::ItemPropertyMaterialRGB materialArrow;  //!< Arrow material

    Props::ItemPropertyText text;              //!< Attached text
    Props::ItemPropertyColor textColor;        //!< Text color
    Props::ItemPropertyText fontFamily;        //!< Text font name
    Props::ItemPropertyUInt32 fontHeight;      //!< Font height
    Props::ItemPropertyUInt32 borderOffset;    //!< Border offset distance
    Props::ItemPropertyFloat pixelSize;        //!< Pixel size
    Props::ItemPropertyEnum textPosition;      //!< Text position on the line
    Props::ItemPropertyEnum textAlign;         //!< Text alignment
    Props::ItemPropertyBool textAutoAlign;     //!< Text auto-alignment
    Props::ItemPropertyBool textFollowCamera;  //!< Text always oriented towards camera position

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _angle Initial arc angle in radians
     * \param _radiusArc Initial arc radius
     * \param _radiusLine Initial line radius
     * \param _pattern Initial line pattern
     * \param _qualityArc Initial arc circle quality
     * \param _qualityLine Initial line circle quality
     * \param _arrowStart Initial flag for use line arrow at start
     * \param _arrowEnd Initial flag for use line arrow at end
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _material Initial line material
     * \param _materialBack Initial line edge material
     * \param _materialArrow Initial arrow material
     * \param _text Initial text
     * \param _colorText Initial text color
     * \param _fontFamily Initial text font name
     * \param _fontHeight Initial font height
     * \param _borderOffset Initial border offset distance
     * \param _pixelSize Initial pixel size
     * \param _textPosition Initial text position
     * \param _textAlign Initial text alignment
     * \param _textAutoAlign Initial auto-alignment flag
     * \param _textFollowCamera Initial flag for text always oriented towards camera position
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemArc(const std::string &_name = "Line",
            const Math::Vec3F &_center = {},
            const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
            const Math::Vec3F &_arm = Math::Vec3F::unitX(),
            const float _angle = M_PI_2,
            const float _radiusArc = 1.0f,
            const float _radiusLine = ItemDefaultValues::lineRadius,
            const uint64_t _pattern = PATTERN_SOLID,
            const uint64_t _qualityArc = ItemDefaultValues::sphereQuality,
            const uint64_t _qualityLine = ItemDefaultValues::lineQuality,
            const bool _arrowStart = false,
            const bool _arrowEnd = false,
            const float _arrowLength = ItemDefaultValues::arrowLength,
            const float _arrowRadius = ItemDefaultValues::arrowRadius,
            const Math::MaterialRGB &_material = {Qt::white},
            const Math::MaterialRGB &_materialBack = {Qt::lightGray},
            const Math::MaterialRGB &_materialArrow = {Qt::gray},
            const QString &_text = "",
            const Math::ColorRGB &_colorText = {Qt::white},
            const QString &_fontFamily = ItemDefaultValues::textFont,
            const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
            const uint32_t _borderOffset = 0U,
            const float _pixelSize = ItemDefaultValues::textPixelSize,
            const Line::LineTextPosition _textPosition = Line::LineTextCenter,
            const Math::AlignType _textAlign = Math::_AlignCenterCenter,
            const bool _textAutoAlign = true,
            const bool _textFollowCamera = true,
            const uint8_t _alpha = 255U,
            const bool _visible = true);

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;

    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _camera Camera data
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data,
                        const Math::CamF &_camera,
                        const size_t _timeStep) const override;

 public:
    /*!
     * \brief Replace text values
     * \param _txt Text
     * \param _a Arc angle
     * \return
     * \details Uses tags:
     * \b Radians \b 1: $$$ANGLE_RAD$$$, $$$ANGLE_RADANGLE_RAD_0$$$, $$$ANGLE_RAD_1$$$, $$$ANGLE_RAD_2$$$,
     *                  $$$ANGLE_RAD_3$$$, $$$ANGLE_RAD_4$$$, $$$ANGLE_RAD_5$$$
     * \b Degrees \b 1: $$$ANGLE_DEG$$$, $$$ANGLE_DEGANGLE_DEG_0$$$, $$$ANGLE_DEG_1$$$, $$$ANGLE_DEG_2$$$,
     *                  $$$ANGLE_DEG_3$$$, $$$ANGLE_DEG_4$$$, $$$ANGLE_DEG_5$$$
     */
    static void replaceText(QString &_txt, const float _a);
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMLINE_H
