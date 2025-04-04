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
}

bool Item::isVisible(const size_t _timeStep) const
{
    return visible.value(_timeStep) && alpha.value(_timeStep) != 0U;
}

}  // namespace Items
}  // namespace U1
