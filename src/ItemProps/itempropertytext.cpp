/*!
 * \file src/ItemProps/itempropertytext.cpp
 * \brief Text dynamic item property
 */

#include "itempropertytext.h"

#include <iostream>

namespace U1 {
namespace Props {

ItemPropertyText::ItemPropertyText(const std::string &_name, const QString &_initialValue)
    : ItemProperty(_name)
{
    m_jobs[0UL] = _initialValue;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemProperty::PropertyType ItemPropertyText::type() const
{
    return _PropertyText;
}

size_t ItemPropertyText::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QString ItemPropertyText::value(const size_t _timeStep) const
{
    if (m_jobs.empty())
        return "";

    std::map<size_t, QString>::const_iterator it = m_jobs.lower_bound(_timeStep);
    if (it == m_jobs.cend())
        return (*m_jobs.crbegin()).second;

    if (it == m_jobs.cbegin() || (*it).first == _timeStep)
        return (*it).second;

    --it;
    return (*it).second;
}

QString ItemPropertyText::textValue(const size_t _timeStep) const
{
    return value(_timeStep);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyText::setValue(const size_t _timeStep, const QString &_value)
{
    if (m_jobs.empty())
    {
        m_jobs[0UL] = _value;
        if (_timeStep != 0UL)
            m_jobs[_timeStep] = _value;
        return;
    }

    std::map<size_t, QString>::iterator it = m_jobs.find(_timeStep);
    if (it != m_jobs.end())
    {
        if ((*it).second == _value)
            return;
        std::cerr << "Warning: Text[" << name << "]::setValue(" << _timeStep << ", " << _value.toStdString()
                  << ") time-step[" << _timeStep << "] already in use!\n";
        (*it).second = _value;
        return;
    }

    m_jobs[_timeStep] = _value;
}

}  // namespace Props
}  // namespace U1
