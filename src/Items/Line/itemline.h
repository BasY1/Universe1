/*!
 * \file src/Items/Line/itemline.h
 * \brief Dynamic 3D line video item
 */

#ifndef ITEMS_ITEMLINE_H
#define ITEMS_ITEMLINE_H

#include "../item3d.h"

#include "../../ItemProps/itempropertytext.h"
#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertypattern.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {
/*!
 * \namespace U1::Items::Line
 * \brief 3D Line item tools
 */
namespace Line {
Q_NAMESPACE

/*! \brief Show line text modes */
enum LineTextPosition : int
{
    LineTextHidden = 0,
    LineTextStart,
    LineTextCenter,
    LineTextEnd
};
Q_ENUM_NS(LineTextPosition)
}  // namespace Line

/*! \brief Dynamic 3D line video item */
class ItemLine : public Item3DExt
{
 public:
    Props::ItemPropertyFloat length;     //!< Line length
    Props::ItemPropertyFloat radius;     //!< Line radius
    Props::ItemPropertyPattern pattern;  //!< Line pattern
    Props::ItemPropertyQuality quality;  //!< Line circle quality

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
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _pattern Initial line pattern
     * \param _quality Initial line circle quality
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
    ItemLine(const std::string &_name = "Line",
             const Math::Vec3F &_center = {},
             const Math::Vec3F &_normal = Math::Vec3F::unitZ(),
             const Math::Vec3F &_arm = Math::Vec3F::unitX(),
             const float _length = 1.0f,
             const float _radius = ItemDefaultValues::lineRadius,
             const uint64_t _pattern = PATTERN_SOLID,
             const uint64_t _quality = ItemDefaultValues::lineQuality,
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
     * \param _o Orientation
     * \param _l length
     * \return
     * \details Uses tags:
     * \b Point \b 1: $$$P1$$$, $$$P1$0$, $$$P1$1$, $$$P1$2$, ..., $$$P1$6$
     * \b Point \b 2: $$$P2$$$, $$$P2$0$, $$$P2$1$, $$$P2$2$, ..., $$$P2$6$
     * \b Length: $$$LENGTH$$$, $$$LENGTH$0$, $$$LENGTH$1$, ..., $$$LENGTH$6$
     */
    static void replaceText(QString &_txt, const Math::OrientF &_o, const float _l);

    /*!
     * \brief Replace text with \c float value
     * \param _txt Text
     * \param _from Replace text from index
     * \param _count Replace text character count
     * \param _keyEnd Key end string
     * \param _value Float value
     * \return \c true if the key end string is valid
     */
    static bool replaceTextValue(
        QString &_txt, const qsizetype _from, const qsizetype _count, const QString &_keyEnd, const float _value);

    /*!
     * \brief Replace text with \c float 3D vector value
     * \param _txt Text
     * \param _from Replace text from index
     * \param _count Replace text character count
     * \param _keyEnd Key end string
     * \param _value \c float 3D vector value
     * \return \c true if the key end string is valid
     */
    static bool replaceTextValue(QString &_txt,
                                 const qsizetype _from,
                                 const qsizetype _count,
                                 const QString &_keyEnd,
                                 const Math::Vec3F &_value);
};

/*! \brief Dynamic 3D Cartesian coordinate system (3D axes) video item */
class ItemCoordAxis : public Item3DExt
{
 public:
    Props::ItemPropertyFloat length;       //!< Line length
    Props::ItemPropertyFloat radius;       //!< Line radius
    Props::ItemPropertyFloat arrowLength;  //!< Arrow length
    Props::ItemPropertyFloat arrowRadius;  //!< Arrow radius
    Props::ItemPropertyPattern pattern;    //!< Line pattern
    Props::ItemPropertyQuality quality;    //!< Line circle quality

    Props::ItemPropertyBool arrowShow;  //!< Show arrows
    Props::ItemPropertyBool textShow;   //!< Show text

    Props::ItemPropertyMaterialRGB materialX;  //!< Axis \b X material
    Props::ItemPropertyMaterialRGB materialY;  //!< Axis \b Y material
    Props::ItemPropertyMaterialRGB materialZ;  //!< Axis \b Z material

    Props::ItemPropertyColor textColorX;  //!< Text "X" color
    Props::ItemPropertyColor textColorY;  //!< Text "Y" color
    Props::ItemPropertyColor textColorZ;  //!< Text "Z" color

    Props::ItemPropertyText fontFamily;      //!< Text font name
    Props::ItemPropertyUInt32 fontHeight;    //!< Font height
    Props::ItemPropertyUInt32 borderOffset;  //!< Border offset distance
    Props::ItemPropertyFloat pixelSize;      //!< Pixel size

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _pattern Initial line pattern
     * \param _quality Initial line circle quality
     * \param _arrowShow Initial show arrows flag
     * \param _textShow Initial show text flag
     * \param _materialX Initial axis \b X material
     * \param _materialY Initial axis \b Y material
     * \param _materialZ Initial axis \b Z material
     * \param _textColorX Initial text "X" color
     * \param _textColorY Initial text "Y" color
     * \param _textColorZ Initial text "Z" color
     * \param _fontFamily Initial text font name
     * \param _fontHeight Initial font height
     * \param _borderOffset Initial border offset distance
     * \param _pixelSize Initial pixel size
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemCoordAxis(const std::string &_name = "Coord-Axis",
                  const Math::Vec3F &_center = {},
                  const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                  const Math::Vec3F &_arm = Math::Vec3F::unitY(),
                  const float _length = 1.0f,
                  const float _radius = ItemDefaultValues::lineRadius,
                  const float _arrowLength = ItemDefaultValues::arrowLength,
                  const float _arrowRadius = ItemDefaultValues::arrowRadius,
                  const uint64_t _pattern = PATTERN_SOLID,
                  const uint64_t _quality = ItemDefaultValues::lineQuality,
                  const bool _arrowShow = true,
                  const bool _textShow = true,
                  const Math::MaterialRGB &_materialX = {Qt::red},
                  const Math::MaterialRGB &_materialY = {Qt::green},
                  const Math::MaterialRGB &_materialZ = {Qt::blue},
                  const Math::ColorRGB &_textColorX = {Qt::darkRed},
                  const Math::ColorRGB &_textColorY = {Qt::darkGreen},
                  const Math::ColorRGB &_textColorZ = {Qt::darkBlue},
                  const QString &_fontFamily = ItemDefaultValues::textFont,
                  const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
                  const uint32_t _borderOffset = 0U,
                  const float _pixelSize = ItemDefaultValues::textPixelSize,
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
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMLINE_H
