/*!
 * \file src/ItemProps/itempropertybool.cpp
 * \brief Dynamic boolean property
 */

#include "itempropertybool.h"

#include <iostream>

#include <QObject>

namespace U1 {
namespace Props {

ItemPropertyBool::ItemPropertyBool(const std::string &_name, const bool _initialValue)
    : ItemProperty(_name)
{
    m_jobs[0UL] = _initialValue;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemProperty::PropertyType ItemPropertyBool::type() const
{
    return _PropertyBool;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

size_t ItemPropertyBool::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool ItemPropertyBool::value(const size_t _timeStep) const
{
    if (m_jobs.empty())
        return false;

    std::map<size_t, bool>::const_iterator it = m_jobs.lower_bound(_timeStep);
    if (it == m_jobs.cend())
        return (*m_jobs.crbegin()).second;

    if (it == m_jobs.cbegin() || (*it).first == _timeStep)
        return (*it).second;

    --it;
    return (*it).second;
}

QString ItemPropertyBool::textValue(const size_t _timeStep) const
{
    return value(_timeStep) ? QObject::tr("ON") : QObject::tr("OFF");
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::setValue(const size_t _timeStep, const bool _value)
{
    if (m_jobs.empty())
    {
        m_jobs[0UL] = _value;
        if (_timeStep != 0UL)
            m_jobs[_timeStep] = _value;
        return;
    }

    std::map<size_t, bool>::iterator it = m_jobs.find(_timeStep);
    if (it != m_jobs.end())
    {
        if ((*it).second == _value)
            return;
        std::cerr << "Warning: Bool[" << name << "]::setValue(" << _timeStep << ", " << (_value ? "On" : "Off")
                  << ") time-step[" << _timeStep << "] already in use!\n";
        (*it).second = _value;
        return;
    }

    m_jobs[_timeStep] = _value;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::initValue(const bool _value)
{
    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Bool[" << name << "]::initValue(" << (_value ? "On" : "Off")
                  << ") Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = _value;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::initOn()
{
    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Bool[" << name << "]::initOn() Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = true;
}

void ItemPropertyBool::initOff()
{
    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Bool[" << name << "]::initOff() Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::initOn_Off(const size_t _timeStepOff)
{
    if (_timeStepOff == 0UL)
    {
        std::cerr << "Warning: Bool[" << name << "]::initOn_Off(0) Use [initOff()] instead.\n";

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: Bool[" << name << "]::initOn_Off(0) Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }
        m_jobs[0UL] = false;
        return;
    }

    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Bool[" << name << "]::initOn_Off(" << _timeStepOff
                  << ") Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = true;
    m_jobs[_timeStepOff] = false;
}

void ItemPropertyBool::initOff_On(const size_t _timeStepOn)
{
    if (_timeStepOn == 0UL)
    {
        std::cerr << "Warning: Bool[" << name << "]::initOff_On(0) Use [initOn()] instead.\n";

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: Bool[" << name << "]::initOff_On(0) Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }
        m_jobs[0UL] = true;
        return;
    }

    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Bool[" << name << "]::initOff_On(" << _timeStepOn
                  << ") Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = false;
    m_jobs[_timeStepOn] = true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::initOff_On_Off(const size_t _timeStepOn, const size_t _timeStepOff)
{
    if (_timeStepOn == 0UL && _timeStepOff > 0UL)
    {
        std::cerr << "Warning: Bool[" << name << "]::initOff_On_Off(0, " << _timeStepOff << ") Use [initOn_Off("
                  << _timeStepOff << ")] instead.\n";

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: Bool[" << name << "]::initOff_On_Off(0, " << _timeStepOff
                      << ") Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }
        m_jobs[_timeStepOn] = true;
        m_jobs[_timeStepOff] = false;
        return;
    }
    if (_timeStepOn >= _timeStepOff)
    {
        std::cerr << "Error: Bool[" << name << "]::initOff_On_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") Invalid time-step order!\n";
        return;
    }

    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Bool[" << name << "]::initOff_On_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = false;
    m_jobs[_timeStepOn] = true;
    m_jobs[_timeStepOff] = false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::addOff_On(const size_t _timeStepOff, const size_t _timeStepOn)
{
    if (_timeStepOff >= _timeStepOn)
    {
        std::cerr << "Error: Bool[" << name << "]::addOff_On(" << _timeStepOff << ", " << _timeStepOn
                  << ") Invalid time-step order!\n";
        return;
    }

    if (m_jobs.empty())
    {
        std::cerr << "Error: Bool[" << name << "]::addOff_On(" << _timeStepOff << ", " << _timeStepOn
                  << ") Can't add, jobs are not initialized!\n";
        return;
    }

    if (m_jobs.find(_timeStepOff) != m_jobs.cend())
        std::cerr << "Warning: Bool[" << name << "]::addOff_On(" << _timeStepOff << ", " << _timeStepOn
                  << ") _timeStepOff[" << _timeStepOff << "] already in use!\n";

    if (m_jobs.find(_timeStepOn) != m_jobs.cend())
        std::cerr << "Warning: Bool[" << name << "]::addOff_On(" << _timeStepOff << ", " << _timeStepOn
                  << ") _timeStepOn[" << _timeStepOn << "] already in use!\n";

    if ((*m_jobs.crbegin()).first >= _timeStepOff)
        std::cerr << "Warning: Bool[" << name << "]::addOff_On(" << _timeStepOff << ", " << _timeStepOn
                  << ") Adding inner job!\n";

    m_jobs[_timeStepOff] = false;
    m_jobs[_timeStepOn] = true;
}

void ItemPropertyBool::addOn_Off(const size_t _timeStepOn, const size_t _timeStepOff)
{
    if (_timeStepOn >= _timeStepOff)
    {
        std::cerr << "Error: Bool[" << name << "]::addOn_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") Invalid time-step order!\n";
        return;
    }

    if (m_jobs.empty())
    {
        std::cerr << "Error: Bool[" << name << "]::addOn_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") Can't add, jobs are not initialized!\n";
        return;
    }

    if (m_jobs.find(_timeStepOn) != m_jobs.cend())
        std::cerr << "Warning: Bool[" << name << "]::addOn_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") _timeStepOn[" << _timeStepOn << "] already in use!\n";

    if (m_jobs.find(_timeStepOff) != m_jobs.cend())
        std::cerr << "Warning: Bool[" << name << "]::addOn_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") _timeStepOff[" << _timeStepOff << "] already in use!\n";

    if ((*m_jobs.crbegin()).first >= _timeStepOn)
        std::cerr << "Warning: Bool[" << name << "]::addOn_Off(" << _timeStepOn << ", " << _timeStepOff
                  << ") Adding inner job!\n";

    m_jobs[_timeStepOn] = true;
    m_jobs[_timeStepOff] = false;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyBool::addSwapInterval(const size_t _timeStepStart,
                                       const size_t _timeStepStop,
                                       const bool _valueStart,
                                       const bool _valueStop,
                                       const size_t _durationOn,
                                       const size_t _durationOff)
{
    if (_timeStepStart >= _timeStepStop)
    {
        std::cerr << "Error: Bool[" << name << "]::addSwapInterval(" << _timeStepStart << ", " << _timeStepStop
                  << ", ...) Invalid time-step order!\n";
        return;
    }

    if (_durationOn == 0UL || _durationOff == 0UL)
    {
        std::cerr << "Error: Bool[" << name << "]::addSwapInterval(" << _timeStepStart << ", " << _timeStepStop
                  << ", ..., " << _durationOn << ", " << _durationOff << ") Invalid interval duration!\n";
        return;
    }

    if (m_jobs.empty())
    {
        std::cerr << "Error: Bool[" << name << "]::addSwapInterval(" << _timeStepStart << ", " << _timeStepStop
                  << ", ...) Can't add, jobs are not initialized!\n";
        return;
    }

    if ((*m_jobs.crbegin()).first == _timeStepStart)
    {
        if (_timeStepStart != 0UL && (*m_jobs.rbegin()).second != _valueStart)
            std::cerr << "Warning: Bool[" << name << "]::addSwapInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Value at start time changed!\n";
        (*m_jobs.rbegin()).second = _valueStart;
    }
    else if ((*m_jobs.crbegin()).first > _timeStepStart)
    {
        std::cerr << "Error: Bool[" << name << "]::addSwapInterval(" << _timeStepStart << ", " << _timeStepStop
                  << ", ...) Can't create inner job!\n";
        return;
    }
    else
    {
        m_jobs.insert(m_jobs.end(), {_timeStepStart, _valueStart});
    }

    size_t t1 = _timeStepStart;
    bool v1 = _valueStart;
    while (true)
    {
        const size_t tNext = t1 + (v1 ? _durationOn : _durationOff);
        if (tNext >= _timeStepStop)
        {
            if (v1 != _valueStop)
                m_jobs.insert(m_jobs.end(), {_timeStepStop, _valueStop});
            return;
        }

        v1 = !v1;
        t1 = tNext;
        m_jobs.insert(m_jobs.end(), {t1, v1});
    }
}

}  // namespace Props
}  // namespace U1
