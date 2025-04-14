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

size_t ItemDefaultValues::sphereQuality = 15UL;
size_t ItemDefaultValues::lineQuality = 3UL;

float ItemDefaultValues::pixelSize = 0.001F;
float ItemDefaultValues::lineRadius = 0.005F;
float ItemDefaultValues::arrowLength = 0.075F;
float ItemDefaultValues::arrowRadius = 0.025F;

QColor ItemDefaultValues::lineColor = QColor(255, 255, 255);

}  // namespace Items
}  // namespace U1
