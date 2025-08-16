/*!
 * \file src/Items/Text/itemtext.h
 * \brief Dynamic 3D text video item
 */

#ifndef ITEMS_ITEMTEXT_H
#define ITEMS_ITEMTEXT_H

#include "../item3d.h"

#include "../../ItemProps/itempropertytext.h"
#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertycolor.h"

namespace U1 {
namespace Items {

/*!
 * \namespace U1::Items::Text
 * \brief 3D Text item tools
 */
namespace Text {
Q_NAMESPACE

/*! \brief Text visibility modes */
enum TextVisibleType : int
{
    TextFrontBack,  //!< Visible from both front and back
    TextFront,      //!< Visible from front
    TextBack,       //!< Visible from back
};
Q_ENUM_NS(TextVisibleType)

}  // namespace Text

/*! \brief Dynamic 3D text video item */
class ItemText : public Item3DExt
{
 public:
    Props::ItemPropertyText text;            //!< Dynamic text
    Props::ItemPropertyColor color;          //!< Dynamic text color
    Props::ItemPropertyText fontFamily;      //!< Dynamic font name
    Props::ItemPropertyUInt32 fontHeight;    //!< Dynamic font height
    Props::ItemPropertyUInt32 borderOffset;  //!< Dynamic offset distance from border based on alignment
    Props::ItemPropertyFloat pixelSize;      //!< Dynamic pixel size
    Props::ItemPropertyEnum textAlign;       //!< Dynamic text alignment
    Props::ItemPropertyEnum visibleFrom;     //!< Dynamic visibility type

 protected:
    std::vector<std::pair<QString, const Props::ItemProperty *>> m_textProps;  //!< Dynamic properties to print values

 public:
    /*!
     * \brief Add external item property to print its value within the text
     * \param _key Property key
     * \param _property External item property object
     */
    void addTextProp(const QString &_key, const Props::ItemProperty *_property);

    /*!
     * \brief Setter for dynamic properties to print values
     * \param _textProps New dynamic properties to print values
     */
    inline void setTextProps(const std::vector<std::pair<QString, const Props::ItemProperty *>> &_textProps)
    {
        m_textProps = _textProps;
    }

    /*!
     * \brief Getter for a collection of known external external item properties
     * \return Collection of known external external item properties
     */
    inline const std::vector<std::pair<QString, const Props::ItemProperty *>> textProps() const
    {
        return m_textProps;
    }

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _text Initial text
     * \param _color Initial text color
     * \param _fontFamily Initial text font name
     * \param _fontHeight Initial font height
     * \param _borderOffset Initial offset distance
     * \param _pixelSize Initial pixel size
     * \param _textAlign Initial text alignment
     * \param _visibleFrom Initial visibility type
     * \param _alpha Initial alpha
     * \param _visible Initial visibility flag
     */
    ItemText(const std::string &_name = "3D-Text",
             const Math::Vec3F &_center = {},
             const Math::Vec3F &_normal = Math::Vec3F::unitX(),
             const Math::Vec3F &_arm = Math::Vec3F::unitY(),
             const QString &_text = "",
             const Math::ColorRGB &_color = ItemDefaultValues::textColor,
             const QString &_fontFamily = ItemDefaultValues::textFont,
             const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
             const uint32_t _borderOffset = 0,
             const float _pixelSize = ItemDefaultValues::textPixelSize,
             const Math::AlignType _textAlign = Math::_AlignBottomLeft,
             const Text::TextVisibleType _visibleFrom = Text::TextFrontBack,
             const uint8_t _alpha = 255U,
             const bool _visible = true);

    /*!
     * \brief Create text 3D data
     * \param _data Output data objects
     * \param _orientation Text orientation
     * \param _text Text
     * \param _color Text color
     * \param _alpha Text color alpha
     * \param _fontFamily Text font name
     * \param _fontHeight Font height
     * \param _borderOffset Offset distance from border
     * \param _pixelSize Pixel size
     * \param _textAlign Text alignment
     * \param _visibleFromFront Flag - text visible from front (\c true) or back (\c false)
     * \return
     */
    static void createText(std::list<OpenGL::Data3D *> &_data,
                           const Math::OrientF &_orientation,
                           const QString &_text,
                           const Math::ColorRGB &_color,
                           const uint8_t _alpha,
                           const QString &_fontFamily,
                           const uint32_t _fontHeight,
                           const uint32_t _borderOffset,
                           const float _pixelSize,
                           const Math::AlignType _textAlign,
                           const bool _visibleFromFront = true);

    /*!
     * \brief Tool function replace text with current property values
     * \param txt Output text
     * \param _textProps Text properties
     * \param _timeStep Time-step
     * \return
     */
    static void replaceTextValues(QString &txt,
                                  const std::vector<std::pair<QString, const Props::ItemProperty *>> &_textProps,
                                  const size_t _timeStep);

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;
};

/*! \brief Dynamic 3D text video item with the plane normal that is always oriented towards camera position */
class ItemTextCamera : public Item3D
{
 public:
    Props::ItemPropertyVec3F center;         //!< Text center point
    Props::ItemPropertyFloat spin;           //!< Additional spin along the view normal (in radians)
    Props::ItemPropertyText text;            //!< Dynamic text
    Props::ItemPropertyColor color;          //!< Dynamic text color
    Props::ItemPropertyText fontFamily;      //!< Dynamic font name
    Props::ItemPropertyUInt32 fontHeight;    //!< Dynamic font height
    Props::ItemPropertyUInt32 borderOffset;  //!< Dynamic offset distance from border based on alignment
    Props::ItemPropertyFloat pixelSize;      //!< Dynamic pixel size
    Props::ItemPropertyEnum textAlign;       //!< Dynamic text alignment

 protected:
    std::vector<std::pair<QString, const Props::ItemProperty *>> m_textProps;  //!< Dynamic properties to print values

 public:
    /*!
     * \brief Add external item property to print its value within the text
     * \param _key Property key
     * \param _property External item property object
     */
    void addTextProp(const QString &_key, const Props::ItemProperty *_property);

    /*!
     * \brief Setter for dynamic properties to print values
     * \param _textProps New dynamic properties to print values
     */
    inline void setTextProps(const std::vector<std::pair<QString, const Props::ItemProperty *>> &_textProps)
    {
        m_textProps = _textProps;
    }

    /*!
     * \brief Getter for a collection of known external external item properties
     * \return Collection of known external external item properties
     */
    inline const std::vector<std::pair<QString, const Props::ItemProperty *>> textProps() const
    {
        return m_textProps;
    }

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _spin Initial value for additional spin along the view normal (in radians)
     * \param _text Initial text
     * \param _color Initial text color
     * \param _fontFamily Initial text font name
     * \param _fontHeight Initial font height
     * \param _borderOffset Initial offset distance
     * \param _pixelSize Initial pixel size
     * \param _textAlign Initial text alignment
     * \param _alpha Initial alpha
     * \param _visible Initial visibility flag
     */
    ItemTextCamera(const std::string &_name = "3D-Text",
                   const Math::Vec3F &_center = {},
                   const float _spin = 0.0f,
                   const QString &_text = "",
                   const Math::ColorRGB &_color = ItemDefaultValues::textColor,
                   const QString &_fontFamily = ItemDefaultValues::textFont,
                   const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
                   const uint32_t _borderOffset = 0,
                   const float _pixelSize = ItemDefaultValues::textPixelSize,
                   const Math::AlignType _textAlign = Math::_AlignBottomLeft,
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

#endif  // ITEMS_ITEMTEXT_H
