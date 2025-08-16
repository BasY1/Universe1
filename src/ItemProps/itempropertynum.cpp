/*!
 * \file src/ItemProps/itempropertynum.cpp
 * \brief Dynamic numeric properties
 */

#include "itempropertynum.h"

namespace U1 {
namespace Props {

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemProperty::PropertyType ItemPropertyUInt8::type() const
{
    return _PropertyUInt8;
}
ItemProperty::PropertyType ItemPropertyInt8::type() const
{
    return _PropertyInt8;
}
ItemProperty::PropertyType ItemPropertyUInt16::type() const
{
    return _PropertyUInt16;
}
ItemProperty::PropertyType ItemPropertyInt16::type() const
{
    return _PropertyInt16;
}
ItemProperty::PropertyType ItemPropertyUInt32::type() const
{
    return _PropertyUInt32;
}
ItemProperty::PropertyType ItemPropertyInt32::type() const
{
    return _PropertyInt32;
}
ItemProperty::PropertyType ItemPropertyUInt64::type() const
{
    return _PropertyUInt64;
}
ItemProperty::PropertyType ItemPropertyInt64::type() const
{
    return _PropertyInt64;
}
ItemProperty::PropertyType ItemPropertyQuality::type() const
{
    return _PropertyQuality;
}
ItemProperty::PropertyType ItemPropertyFloat::type() const
{
    return _PropertyFloat;
}
ItemProperty::PropertyType ItemPropertyDouble::type() const
{
    return _PropertyDouble;
}
ItemProperty::PropertyType ItemPropertyLongDouble::type() const
{
    return _PropertyLongDouble;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t ItemPropertyUInt8::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyInt8::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyUInt16::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyInt16::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyUInt32::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyInt32::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyUInt64::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyInt64::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyQuality::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyFloat::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyDouble::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}
size_t ItemPropertyLongDouble::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString ItemPropertyUInt8::textValue(const size_t _timeStep) const
{
    return QString::number((int)value(_timeStep));
}
QString ItemPropertyInt8::textValue(const size_t _timeStep) const
{
    return QString::number((int)value(_timeStep));
}
QString ItemPropertyUInt16::textValue(const size_t _timeStep) const
{
    return QString::number((int)value(_timeStep));
}
QString ItemPropertyInt16::textValue(const size_t _timeStep) const
{
    return QString::number((int)value(_timeStep));
}
QString ItemPropertyUInt32::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyInt32::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyUInt64::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyInt64::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyQuality::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyFloat::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyDouble::textValue(const size_t _timeStep) const
{
    return QString::number(value(_timeStep));
}
QString ItemPropertyLongDouble::textValue(const size_t _timeStep) const
{
    return QString::number((double)value(_timeStep));
}

}  // namespace Props
}  // namespace U1
