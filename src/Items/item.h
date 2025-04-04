/*!
 * \file src/Items/item.h
 * \brief Basic video item
 */

#ifndef ITEMS_ITEM_H
#define ITEMS_ITEM_H

#include "../ItemProps/itempropertygroup.h"
#include "../ItemProps/itempropertybool.h"
#include "../ItemProps/itempropertynum.h"

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
     * \brief Test if item is visible at given time-step
     * \param _timeStep Time step
     * \return \c true if item is visible at given time-step
     */
    virtual bool isVisible(const size_t _timeStep) const;
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM_H
