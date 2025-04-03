/*!
 * \file src/ItemProps/itempropertypattern.cpp
 * \brief Line pattern dynamic item property
 */

#include "itempropertypattern.h"

#include <iostream>

namespace U1 {
namespace Props {

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemPropertyPattern::ItemPropertyPattern(const std::string &_name, const uint64_t _initialValue)
    : ItemProperty(_name)
{
    m_jobs[0UL] = _initialValue;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemProperty::PropertyType ItemPropertyPattern::type() const
{
    return _PropertyPattern;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t ItemPropertyPattern::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

uint64_t ItemPropertyPattern::value(const size_t _timeStep) const
{
    if (m_jobs.empty())
        return false;

    std::map<size_t, uint64_t>::const_iterator it = m_jobs.lower_bound(_timeStep);
    if (it == m_jobs.cend())
        return (*m_jobs.crbegin()).second;

    if (it == m_jobs.cbegin() || (*it).first == _timeStep)
        return (*it).second;

    --it;
    return (*it).second;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyPattern::setValue(const size_t _timeStep, const uint64_t _value)
{
    if (m_jobs.empty())
    {
        m_jobs[0UL] = _value;
        if (_timeStep != 0UL)
            m_jobs[_timeStep] = _value;
        return;
    }

    std::map<size_t, uint64_t>::iterator it = m_jobs.find(_timeStep);
    if (it != m_jobs.end())
    {
        if ((*it).second == _value)
            return;
        std::cerr << "Warning: Pattern[" << name << "]::setValue(" << _timeStep << ", " << _value << ") time-step["
                  << _timeStep << "] already in use!\n";
        (*it).second = _value;
        return;
    }

    m_jobs[_timeStep] = _value;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyPattern::initValue(const uint64_t _value)
{
    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Pattern[" << name << "]::initValue(" << (_value ? "On" : "Off")
                  << ") Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = _value;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QList<qreal> ItemPropertyPattern::toQDashPattern(const uint64_t _pattern)
{
    QList<qreal> result;
    if (_pattern == 0UL)
        return result;

    uint64_t tmp = 0b1000000000000000000000000000000000000000000000000000000000000000;
    while ((tmp & _pattern) == 0UL)
        tmp >>= 1UL;

    int cnt0 = 0;
    int cnt1 = 1;
    tmp >>= 1UL;

    while (tmp != 0)
    {
        if ((tmp & _pattern) == 0UL)
        {
            if (cnt0 > 0)
            {
                cnt0++;
            }
            else
            {
                result << cnt1;
                cnt0 = 1;
                cnt1 = 0;
            }
        }
        else
        {
            if (cnt1 > 0)
            {
                cnt1++;
            }
            else
            {
                result << cnt0;
                cnt0 = 0;
                cnt1 = 1;
            }
        }
        tmp >>= 1UL;
    }

    if (cnt0 > 0)
        result << cnt0;
    // else result << cnt1 << 0.0;

    return result;
}

}  // namespace Props
}  // namespace U1
