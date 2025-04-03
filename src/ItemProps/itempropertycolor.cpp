/*!
 * \file src/ItemProps/itempropertycolor.cpp
 * \brief Color dynamic item property
 */

#include "itempropertycolor.h"

namespace U1 {
namespace Props {

ItemPropertyColor::ItemPropertyColor(const std::string &_name, const Math::ColorRGB &_initialValue)
    : ItemPropertyGroup(_name)
    , red("red", _initialValue.red)
    , green("green", _initialValue.green)
    , blue("blue", _initialValue.blue)
{
    setupProperties({&red, &green, &blue});
}

}  // namespace Props
}  // namespace U1
