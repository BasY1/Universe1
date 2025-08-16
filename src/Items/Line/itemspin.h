/*!
 * \file src/Items/Line/itemspin.h
 * \brief Dynamic 3D line spin video item
 */

#ifndef ITEMS_ITEMSPIN_H
#define ITEMS_ITEMSPIN_H

#include "itemline.h"
#include "itemarc.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic 3D line spin video item */
class ItemSpin : public Item3DExt
{
 public:
    Props::ItemPropertyFloat phase;      //!< Additional rotation in radians
    Props::ItemPropertyFloat length;     //!< Line length
    Props::ItemPropertyFloat radius;     //!< Line radius
    Props::ItemPropertyPattern pattern;  //!< Line pattern
    Props::ItemPropertyQuality quality;  //!< Line circle quality

    Props::ItemPropertyUInt8 arrowCount;         //!< Use line arrow at start
    Props::ItemPropertyFloat arrowLength;        //!< Arrow length
    Props::ItemPropertyFloat arrowRadius;        //!< Arrow radius
    Props::ItemPropertyFloat arrowOffsetLength;  //!< Arrow offset from the center within the major normal
    Props::ItemPropertyFloat arrowOffsetAxis;    //!< Arrow offset from the axis
    Props::ItemPropertyQuality arrowQuality;     //!< Arrow circle quality

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
     * \param _phase Initial phase angle in radians
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _pattern Initial line pattern
     * \param _quality Initial line circle quality
     * \param _arrowCount Initial number of arrows
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _arrowOffsetLength Initial arrow offset from the center within the major normal
     * \param _arrowOffsetAxis Initial arrow offset from the axis
     * \param _arrowQuality Initial arrow circle quality
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
    ItemSpin(const std::string &_name = "Spin",
             const Math::Vec3F &_center = {},
             const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
             const Math::Vec3F &_arm = Math::Vec3F::unitX(),
             const float _phase = 0.0f,
             const float _length = 1.0f,
             const float _radius = ItemDefaultValues::lineRadius,
             const uint64_t _pattern = PATTERN_SOLID,
             const uint64_t _quality = ItemDefaultValues::lineQuality,
             const uint8_t _arrowCount = 3U,
             const float _arrowLength = ItemDefaultValues::arrowLength,
             const float _arrowRadius = ItemDefaultValues::arrowRadius,
             const float _arrowOffsetLength = ItemDefaultValues::arrowLength = 0.9f,
             const float _arrowOffsetAxis = ItemDefaultValues::arrowRadius * 10.0f,
             const uint64_t _arrowQuality = ItemDefaultValues::sphereQuality,
             const Math::MaterialRGB &_material = {Qt::white},
             const Math::MaterialRGB &_materialBack = {Qt::lightGray},
             const Math::MaterialRGB &_materialArrow = {Qt::gray},
             const QString &_text = "",
             const Math::ColorRGB &_colorText = {Qt::white},
             const QString &_fontFamily = ItemDefaultValues::textFont,
             const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
             const uint32_t _borderOffset = 0U,
             const float _pixelSize = ItemDefaultValues::textPixelSize,
             const Line::LineTextPosition _textPosition = Line::LineTextEnd,
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

    /*!
     * \brief Replace text values
     * \param _txt Text
     * \param _o Orientation
     * \param _l length
     * \param _a Phase angle
     * \return
     * \details Uses tags:
     * \b Point \b 1: $$$P1$$$, $$$P1$0$, $$$P1$1$, $$$P1$2$, ..., $$$P1$6$
     * \b Point \b 2: $$$P2$$$, $$$P2$0$, $$$P2$1$, $$$P2$2$, ..., $$$P2$6$
     * \b Length: $$$LENGTH$$$, $$$LENGTH$0$, $$$LENGTH$1$, ..., $$$LENGTH$6$
     * \b Phase [rad]: $$$ANGLE_RAD$$$, $$$ANGLE_RAD$0$, $$$ANGLE_RAD$1$, ..., $$$ANGLE_RAD$6$
     * \b Phase [deg]: $$$ANGLE_DEG$$$, $$$ANGLE_DEG$0$, $$$ANGLE_DEG$1$, ..., $$$ANGLE_DEG$6$
     */
    inline static void replaceText(QString &_txt, const Math::OrientF &_o, const float _l, const float _a)
    {
        ItemLine::replaceText(_txt, _o, _l);
        ItemArc::replaceText(_txt, _a);
    }
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMSPIN_H
