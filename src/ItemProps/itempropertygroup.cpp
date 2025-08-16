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

QString ItemPropertyGroup::textValue(const size_t _timeStep) const
{
    QString result = QString::fromStdString(name) + "[";
    for (const ItemProperty *ip : std::as_const(m_itemProperties))
        result.append("[" + ip->textValue(_timeStep) + "]");
    result.append("]");
    return result;
}

}  // namespace Props
}  // namespace U1
