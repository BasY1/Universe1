/*!
 * \file src/ItemProps/itempropertyvec3.cpp
 * \brief Base class for 3D vector properties
 */

#include "itempropertyvec3.h"

namespace U1 {
namespace Props {

ItemProperty::PropertyType ItemPropertyVec3F::type() const
{
    return _PropertyVec3F;
}
ItemProperty::PropertyType ItemPropertyVec3D::type() const
{
    return _PropertyVec3D;
}
ItemProperty::PropertyType ItemPropertyVec3L::type() const
{
    return _PropertyVec3L;
}

size_t ItemPropertyVec3F::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyVec3D::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyVec3L::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

}  // namespace Props
}  // namespace U1
