/*!
 * \file src/Items/item.cpp
 * \brief Basic video item
 */

#include "item.h"

namespace U1 {
namespace Items {

Item::Item(const std::string &_name, const uint8_t _alpha, const bool _visible)
    : Props::ItemPropertyGroup(_name)
    , alpha("alpha", _alpha)
    , visible("visible", _visible)
{
    setupProperties({&alpha, &visible});
}

}  // namespace Items
}  // namespace U1
