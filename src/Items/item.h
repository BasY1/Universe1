/*!
 * \file src/Items/item.h
 * \brief Basic video item
 */

#ifndef ITEMS_ITEM_H
#define ITEMS_ITEM_H

#include "../ItemProps/itempropertygroup.h"
#include "../ItemProps/itempropertybool.h"
#include "../ItemProps/itempropertynum.h"

#include <QColor>
#include <QTextDocument>

namespace U1 {

/*!
 * \namespace U1::Items
 * \brief Video items
 */
namespace Items {

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief Basic video item */
class Item : public Props::ItemPropertyGroup
{
 public:
    Props::ItemPropertyUInt8 alpha;   //!< General alpha factor
    Props::ItemPropertyBool visible;  //!< Visible flag

 protected:
    /*!
     * \brief Protected constructor
     * \param _name Item name
     * \param _alpha Initial alpha factor
     * \param _visible Initial visible flag
     */
    Item(const std::string &_name, const uint8_t _alpha = 255U, const bool _visible = true);

 public:
    /*!
     * \brief Create HTML based text document
     * \param _text Text
     * \param _fontFamily Font
     * \param _fontHeight Font height
     * \param _usedColor Font color
     * \return \b QT text document
     */
    static QTextDocument *createTextDocument(const QString &_text,
                                             const QString &_fontFamily,
                                             const uint32_t _fontHeight,
                                             const QColor &_usedColor = QColor());
};

/*! \brief The default initial values for similar properties */
struct ItemDefaultValues
{
    static QString latexWorkDir;  //!< Directory for generated LaTeX images

    static size_t sphereQuality;  //!< Default circle quality index for spheres
    static size_t lineQuality;    //!< Default circle quality index for lines (cylinders)

    static float pixelSize;    //!< Default pixel size for textures
    static float lineRadius;   //!< Default line radius
    static float arrowLength;  //!< Default arrow length
    static float arrowRadius;  //!< Default arrow radius

    static QColor lineColor;  //!< Default line color
    static QColor textColor;  //!< Default text color

    static QString textFont;  //!< Default text font name

    static uint fontHeight;  //!< Default font height [6|7|8|9|10|11|12|14|16|18|20|22|24|26|28|36|48|72]
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM_H
