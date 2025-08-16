/*!
 * \file src/Items/Items2D/item2dtext.h
 * \brief Dynamic 2D text item
 */

#ifndef ITEMS_ITEM2DTEXT_H
#define ITEMS_ITEM2DTEXT_H

#include "../item2d.h"

#include "../../ItemProps/itempropertytext.h"
#include "../../ItemProps/itempropertyenum.h"
#include "../../ItemProps/itempropertycolor.h"

namespace U1 {
namespace Items {

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief Dynamic 2D text item */
class Item2DText : public Item2D
{
 public:
    Props::ItemPropertyText text;            //!< Text
    Props::ItemPropertyText fontFamily;      //!< Font
    Props::ItemPropertyUInt32 fontHeight;    //!< Font height
    Props::ItemPropertyColor fontColor;      //!< Font color
    Props::ItemPropertyEnum screenPosition;  //!< Screen position
    Props::ItemPropertyUInt32 screenOffset;  //!< Offset distance from the edge of a screen

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
     * \param _text Initial value for text
     * \param _screenPosition Initial value for screen position
     * \param _screenOffset Initial value for offset distance from the edge of a screen
     * \param _fontFamily Initial value for font family name
     * \param _fontHeight Initial value for font height
     * \param _fontColor Initial value for font color
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    Item2DText(const std::string &_name = "2D-Text",
               const QString &_text = "",
               const Math::AlignType _screenPosition = Math::_AlignTopLeft,
               const uint32_t _screenOffset = 0U,
               const QString &_fontFamily = ItemDefaultValues::textFont,
               const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
               const Math::ColorRGB &_fontColor = ItemDefaultValues::textColor,
               const uint8_t _alpha = 255U,
               const bool _visible = true);

 protected:
    /*!
     * \brief Paint item
     * \param _painter Painter
     * \param _screenSize Screen size
     * \param _timeStep Time-step
     */
    void paintItem(QPainter &_painter, const QSize &_screenSize, const size_t _timeStep) const override;

 public:
    /*!
     * \brief Paint 2D text
     * \param _painter Painter
     * \param _screenSize Screen size
     * \param _text Text
     * \param _fontFamily Font
     * \param _fontHeight Font height
     * \param _usedColor Font color
     * \param _screenPosition Screen position
     * \param _screenOffset Offset distance from the edge of a screen
     * \return
     */
    static void paintItem2D(QPainter &_painter,
                            const QSize &_screenSize,
                            const QString &_text,
                            const QString &_fontFamily,
                            const uint32_t _fontHeight,
                            const QColor _usedColor,
                            const Math::AlignType _screenPosition,
                            const uint32_t _screenOffset);
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM2DTEXT_H
