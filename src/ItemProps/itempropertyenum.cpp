/*!
 * \file src/ItemProps/itempropertyenum.cpp
 * \brief Enumerator dynamic item property
 */

#include "itempropertyenum.h"

#include <iostream>

namespace U1 {
namespace Props {

ItemPropertyEnum::ItemPropertyEnum(const std::string &_name,
                                   const QMetaEnum &_metaEnumData,
                                   const std::map<int, QString> &_enumLiterals,
                                   const int _initialValue)
    : ItemProperty(_name)
    , m_enum(_metaEnumData)
    , m_enumLiterals(_enumLiterals)
{
    if (isValidLiteral(_initialValue))
        m_jobs[0UL] = _initialValue;
    else
    {
        std::cerr << "Error: Enum[" << name << "]::ItemPropertyEnum(... , " << _initialValue << ") Invalid literal!\n";
        m_jobs[0UL] = (*m_enumLiterals.cbegin()).first;
    }
}


// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemProperty::PropertyType ItemPropertyEnum::type() const
{
    return _PropertyEnum;
}

size_t ItemPropertyEnum::latestTimeStep() const
{
    return m_jobs.empty() ? 0UL : (*m_jobs.crbegin()).first;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ItemPropertyEnum::value(const size_t _timeStep) const
{
    if (m_jobs.empty())
        return -1;

    std::map<size_t, int>::const_iterator it = m_jobs.lower_bound(_timeStep);
    if (it == m_jobs.cend())
        return (*m_jobs.crbegin()).second;

    if (it == m_jobs.cbegin() || (*it).first == _timeStep)
        return (*it).second;

    --it;
    return (*it).second;
}

QString ItemPropertyEnum::textValue(const size_t _timeStep) const
{
    return m_enumLiterals.at(value(_timeStep));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ItemPropertyEnum::setValue(const size_t _timeStep, const int _value)
{
    if (m_enumLiterals.find(_value) == m_enumLiterals.cend())
    {
        std::cerr << "Error: Enum[" << name << "]::setValue(" << _timeStep << ", " << _value << ") Invalid literal!\n";
        return;
    }

    if (m_jobs.empty())
    {
        m_jobs[0UL] = _value;
        if (_timeStep != 0UL)
            m_jobs[_timeStep] = _value;
        return;
    }

    std::map<size_t, int>::iterator it = m_jobs.find(_timeStep);
    if (it != m_jobs.end())
    {
        if ((*it).second == _value)
            return;
        std::cerr << "Warning: Enum[" << name << "]::setValue(" << _timeStep << ", " << _value << ") time-step["
                  << _timeStep << "] already in use!\n";
        (*it).second = _value;
        return;
    }

    m_jobs[_timeStep] = _value;
}

void ItemPropertyEnum::initValue(const int _initialValue)
{
    if (m_enumLiterals.find(_initialValue) == m_enumLiterals.cend())
    {
        std::cerr << "Error: Enum[" << name << "]::initValue(" << _initialValue << ") Invalid literal!\n";
        return;
    }

    if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
    {
        std::cerr << "Warning: Enum[" << name << "]::initValue(" << _initialValue
                  << ") Secondary initialization, clearing all jobs!\n";
        m_jobs.clear();
    }

    m_jobs[0UL] = _initialValue;
}

int ItemPropertyEnum::parseLiteral(const QString &_text, bool *_ok)
{
    if (_text.isEmpty())
    {
        if (_ok != nullptr)
            (*_ok) = false;
        return (*m_enumLiterals.cbegin()).first;
    }

    bool ok;
    int result = _text.toInt(&ok);
    if (ok)
    {
        if (m_enumLiterals.find(result) != m_enumLiterals.cend())
        {
            if (_ok != nullptr)
                (*_ok) = true;
            return result;
        }
    }

    result = m_enum.keyToValue(_text.toLatin1(), &ok);
    if (_ok != nullptr)
        (*_ok) = ok;
    if (!ok && result == -1)
        return (*m_enumLiterals.cbegin()).first;
    return result;
}

}  // namespace Props
}  // namespace U1
