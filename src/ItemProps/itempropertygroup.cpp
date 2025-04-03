/*!
 * \file src/ItemProps/itempropertygroup.h
 * \brief Base class for dynamic item property groups
 */

#include "itempropertygroup.h"

namespace U1 {
namespace Props {

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemProperty::PropertyType ItemPropertyGroup::type() const
{
    return _PropertyGroup;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t ItemPropertyGroup::latestTimeStep() const
{
    size_t result = 0UL;
    for (const ItemProperty *ip : std::as_const(m_itemProperties))
        result = std::max(result, ip->latestTimeStep());
    return result;
}

}  // namespace Props
}  // namespace U1
