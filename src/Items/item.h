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
};

/*! \brief The default initial values for similar properties */
struct ItemDefaultValues
{
    static size_t sphereQuality;  //!< Default circle quality index for spheres
    static size_t lineQuality;    //!< Default circle quality index for lines (cylinders)

    static float pixelSize;    //!< Default pixel size for textures
    static float lineRadius;   //!< Default line radius
    static float arrowLength;  //!< Default arrow length
    static float arrowRadius;  //!< Default arrow radius

    static QColor lineColor;  //!< Default line color
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM_H
