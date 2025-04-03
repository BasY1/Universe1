/*!
 * \file src/ItemProps/itempropertyvec2.cpp
 * \brief Base class for 2D vector properties
 */

#include "itempropertyvec2.h"

namespace U1 {
namespace Props {

ItemProperty::PropertyType ItemPropertyVec2F::type() const
{
    return _PropertyVec2F;
}
ItemProperty::PropertyType ItemPropertyVec2D::type() const
{
    return _PropertyVec2D;
}
ItemProperty::PropertyType ItemPropertyVec2L::type() const
{
    return _PropertyVec2L;
}

size_t ItemPropertyVec2F::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyVec2D::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyVec2L::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

}  // namespace Props
}  // namespace U1
