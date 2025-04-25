/*!
 * \file src/ItemProps/itempropertynum.h
 * \brief Dynamic numeric properties
 */

#ifndef PROPS_ITEMPROPERTYNUM_H
#define PROPS_ITEMPROPERTYNUM_H

#include "../Math/type.h"
#include "itemproperty.h"

#include <map>
#include <iostream>

namespace U1 {
namespace Props {

/*!
 * \brief Base class for numeric properties
 * \tparam T Numeric type
 */
template <typename T>
class ItemPropertyNum
{

 public:
    /*! \brief Job name */
    enum JobType : int
    {
        _JobConstantValue = 0,  //!< Keep constant value
        _JobLinearValue,        //!< Linear interpolate to value
        _JobAcceleratedValue,   //!< Accelerated - linear - decelerated interpolation to value
    };

    /*! \brief Numeric property job */
    struct Job
    {
        JobType type;               //!< Job name
        T value;                    //!< Job final value
        double acceleration = 0.0;  //!< Acceleration duration as ratio to total job duration
        double deceleration = 0.0;  //!< Deceleration duration as ratio to total job duration
    };

 protected:
    std::map<size_t, Job> m_jobs;   //!< Property jobs
    const T m_minimumValue = T(0);  //!< Minimum possible value
    const T m_maximumValue = T(0);  //!< Maximum possible value

    /*!
     * \brief Constructor
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    template <typename = std::enable_if<std::is_arithmetic<T>::value>>
    ItemPropertyNum(const T _initialValue, const T _minimumValue, const T _maximumValue)
        : m_minimumValue(std::min(_minimumValue, _maximumValue))
        , m_maximumValue(std::max(_minimumValue, _maximumValue))
    {

        if (Math::equals(m_minimumValue, m_maximumValue))
            std::cerr << "Warning: ItemPropertyNum(" << _initialValue << ", " << _minimumValue << ", " << _maximumValue
                      << ") Invalid range!\n";

        if (Math::isAligned(_initialValue, m_minimumValue, m_maximumValue))
        {
            m_jobs[0UL] = {_JobConstantValue, _initialValue, 0.0, 0.0};
        }
        else if (_initialValue < m_minimumValue)
        {
            std::cerr << "Error: ItemPropertyNum(" << _initialValue << ") Value out off range (" << m_minimumValue
                      << ", " << m_maximumValue << ")!\n";
            m_jobs[0UL] = {_JobConstantValue, m_minimumValue, 0.0, 0.0};
        }
        else
        {
            std::cerr << "Error: ItemPropertyNum(" << _initialValue << ") Value out off range (" << m_minimumValue
                      << ", " << m_maximumValue << ")!\n";
            m_jobs[0UL] = {_JobConstantValue, m_maximumValue, 0.0, 0.0};
        }
    }

    /*!
     * \brief Constructor
     * \param _initialValue Initial value
     * \note Minimum and maximum possible value are min/max values of template type T
     */
    template <typename = std::enable_if<std::is_arithmetic<T>::value>>
    ItemPropertyNum(const T _initialValue)
        : ItemPropertyNum(_initialValue, std::numeric_limits<T>::lowest(), std::numeric_limits<T>::max())
    {
    }

 public:
    /*!
     * \brief Minimum value getter
     * \return Minimum value
     */
    inline T minimumValue() const
    {
        return m_minimumValue;
    }

    /*!
     * \brief Maximum value getter
     * \return Maximum value
     */
    inline T maximumValue() const
    {
        return m_maximumValue;
    }

    /*!
     * \brief Calculates linearly distributed value in interval
     * \param _timeStep Time-step for required value
     * \param _timeStepPrev Interval begin time
     * \param _timeStepNext Interval end time
     * \param _valuePrev Interval begin value
     * \param _valueNext Interval end value
     * \return Linearly distributed value
     */
    static T getLinearValue(const size_t &_timeStep,
                            const size_t &_timeStepPrev,
                            const size_t &_timeStepNext,
                            const T &_valuePrev,
                            const T &_valueNext)
    {
        return _valuePrev +
            static_cast<T>((static_cast<double>(_valueNext) - static_cast<double>(_valuePrev)) *
                           (static_cast<double>(_timeStep - _timeStepPrev) /
                            static_cast<double>(_timeStepNext - _timeStepPrev)));
    }

    /*!
     * \brief Calculates accelerated value in interval
     * \param _timeStep Time-step for required value
     * \param _timeStepPrev Interval begin time
     * \param _timeStepNext Interval end time
     * \param _ratioAcceleration Acceleration duration as ratio to total job duration
     * \param _ratioDeceleration Deceleration duration as ratio to total job duration
     * \param _valuePrev Interval begin value
     * \param _valueNext Interval end value
     * \return Linearly distributed value
     */
    static T getAcceleratedValue(const size_t &_timeStep,
                                 const size_t &_timeStepPrev,
                                 const size_t &_timeStepNext,
                                 const double &_ratioAcceleration,
                                 const double &_ratioDeceleration,
                                 const T &_valuePrev,
                                 const T &_valueNext)
    {
        if (Math::equals(_valuePrev, _valueNext))
            return _valuePrev;

        double usedAccel = std::max(_ratioAcceleration, 0.0);
        double usedDecel = std::max(_ratioDeceleration, 0.0);
        double sum = (usedAccel + usedDecel);

        if (Math::isNull(sum))
            return getLinearValue(_timeStep, _timeStepPrev, _timeStepNext, _valuePrev, _valueNext);

        if (Math::isMoreNotEqual(sum, 1.0))
        {
            usedAccel /= sum;
            usedDecel /= sum;
            sum = 1.0;
        }

        const double diffValue = _valueNext - _valuePrev;
        const double timeDur = _timeStepNext - _timeStepPrev;
        double timeApply = _timeStep - _timeStepPrev;

        if (Math::equals(usedAccel, 1.0))  // Only acceleration
        {
            return _valuePrev + static_cast<T>((diffValue * timeApply * timeApply) / (timeDur * timeDur));
        }

        if (Math::equals(usedDecel, 1.0))  // Only deceleration
        {
            const double a = (2.0 * diffValue) / (timeDur * timeDur);
            return _valuePrev + static_cast<T>(a * timeDur * timeApply - 0.5 * a * timeApply * timeApply);
        }

        if (Math::isNull(usedDecel))
        {  // Acceleration and linear movement

            const double timeAcc = timeDur * usedAccel;
            const double timeLin = timeDur - timeAcc;
            const double a = diffValue / (0.5 * timeAcc * timeAcc + timeAcc * timeLin);

            if (Math::equals(timeApply, timeAcc) || timeApply < timeAcc)
                return _valuePrev + static_cast<T>(0.5 * a * timeApply * timeApply);

            timeApply -= timeAcc;

            return _valuePrev + static_cast<T>(0.5 * a * timeAcc * timeAcc + a * timeAcc * timeApply);
        }

        if (Math::isNull(usedAccel))
        {  // Linear movement and deceleration

            const double timeDec = timeDur * usedDecel;
            const double timeLin = timeDur - timeDec;

            const double d = diffValue / (0.5 * timeDec * timeDec + timeDec * timeLin);
            const double v = d * timeDec;

            if (Math::equals(timeApply, timeLin) || timeApply < timeLin)
                return _valuePrev + static_cast<T>(v * timeApply);

            timeApply -= timeLin;

            return _valuePrev + static_cast<T>(v * (timeLin + timeApply) - 0.5 * d * timeApply * timeApply);
        }

        if (Math::equals(sum, 1.0))  // Acceleration and deceleration without linear middle movement
        {

            const double timeAcc = timeDur * usedAccel;
            const double timeDec = timeDur * usedDecel;

            const double d = (2.0 * diffValue) / (timeDec * timeAcc + timeAcc * timeAcc);
            const double a = (d * timeDec) / timeAcc;

            if (Math::equals(timeApply, timeAcc) || timeApply < timeAcc)
                return _valuePrev + static_cast<T>(0.5 * a * timeApply * timeApply);

            timeApply -= timeAcc;

            return _valuePrev +
                static_cast<T>(0.5 * a * timeAcc * timeAcc + a * timeAcc * timeApply - 0.5 * d * timeApply * timeApply);
        }

        const double timeAcc = timeDur * usedAccel;
        const double timeDec = timeDur * usedDecel;
        const double timeLin = timeDur - (timeAcc + timeDec);

        const double d = diffValue / (0.5 * timeAcc * timeDec + timeDec * timeLin + 0.5 * timeDec * timeDec);

        const double a = (d * timeDec) / timeAcc;

        if (Math::equals(timeApply, timeAcc) || timeApply < timeAcc)
            return _valuePrev + static_cast<T>(0.5 * a * timeApply * timeApply);

        const double v = a * timeAcc;
        const double accLen = 0.5 * a * timeAcc * timeAcc;

        timeApply -= timeAcc;
        if (Math::equals(timeApply, timeLin) || timeApply < timeLin)
            return _valuePrev + static_cast<T>(accLen + v * timeApply);

        timeApply -= timeLin;

        return _valuePrev + static_cast<T>(accLen + v * timeLin + v * timeApply - 0.5 * d * timeApply * timeApply);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    T value(const size_t _timeStep) const
    {
        if (m_jobs.empty())
            return m_minimumValue;

        typename std::map<size_t, Job>::const_iterator it = m_jobs.lower_bound(_timeStep);
        if (it == m_jobs.cend())
            return (*m_jobs.crbegin()).second.value;

        if (it == m_jobs.cbegin() || (*it).first == _timeStep)
            return (*it).second.value;

        typename std::map<size_t, Job>::const_iterator itPrev = it;
        --itPrev;

        switch ((*it).second.type)
        {
        case _JobConstantValue: break;

        case _JobLinearValue:
            return getLinearValue(_timeStep, (*itPrev).first, (*it).first, (*itPrev).second.value, (*it).second.value);

        case _JobAcceleratedValue:
            return getAcceleratedValue(_timeStep,
                                       (*itPrev).first,
                                       (*it).first,
                                       (*it).second.acceleration,
                                       (*it).second.deceleration,
                                       (*itPrev).second.value,
                                       (*it).second.value);
        }

        return (*itPrev).second.value;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    void initValue(const T _initialValue)
    {
        if (!Math::isAligned<T>(_initialValue, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::initValue(" << _initialValue << ") Value out off range ("
                      << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: ItemPropertyNum::initValue(" << _initialValue
                      << ") Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }

        m_jobs[0UL] = {_JobConstantValue, _initialValue, 0.0, 0.0};
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    void initValueUpTo(const size_t _timeStep, const T _value)
    {
        if (_timeStep == 0UL)
        {
            std::cerr << "Warning: ItemPropertyNum::initValueUpTo(" << _timeStep << ", " << _value
                      << ") Initial time == 0, using ItemPropertyNum::initValue(" << _value << ")!\n";
            initValue(_value);
            return;
        }

        if (!Math::isAligned<T>(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::initValueUpTo(" << _timeStep << ", " << _value
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: ItemPropertyNum::initValueUpTo(" << _timeStep << ", " << _value
                      << ") Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }

        m_jobs[0UL] = {_JobConstantValue, _value};
        m_jobs[_timeStep] = {_JobConstantValue, _value};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    void addConstantValue(const size_t _timeStep, const T _value)
    {
        if (!Math::isAligned<T>(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addConstantValue(" << _timeStep << ", " << _value
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            m_jobs[0UL] = {_JobConstantValue, _value, 0.0, 0.0};
            if (_timeStep != 0UL)
                m_jobs[_timeStep] = {_JobConstantValue, _value, 0.0, 0.0};
            return;
        }

        if (_timeStep == 0UL)
        {
            if ((*m_jobs.cbegin()).first == _timeStep)
                std::cerr << "Warning: ItemPropertyNum::addConstantValue(" << _timeStep << ", " << _value
                          << ") time-step[" << _timeStep << "] already in use, overwriting with new job!\n";
            m_jobs[_timeStep] = {_JobConstantValue, _value, 0.0, 0.0};
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobConstantValue && Math::equals<T>((*it).second.value, _value))
                return;

            std::cerr << "Warning: ItemPropertyNum::addConstantValue(" << _timeStep << ", " << _value << ") time-step["
                      << _timeStep << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobConstantValue, _value, 0.0, 0.0};
            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyNum::addConstantValue(" << _timeStep << ", " << _value
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobConstantValue, _value, 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to reach at given time-step
     */
    void addLinearValue(const size_t _timeStep, const T _value)
    {
        if (!Math::isAligned<T>(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addLinearValue(" << _timeStep << ", " << _value
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addLinearValue(" << _timeStep << ", " << _value
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyNum::addLinearValue(0, " << _value
                      << ") Job at time-step[0] cannot be linear, it must be constant!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobLinearValue && Math::equals<T>((*it).second.value, _value))
                return;

            std::cerr << "Warning: ItemPropertyNum::addLinearValue(" << _timeStep << ", " << _value << ") time-step["
                      << _timeStep << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobLinearValue, _value, 0.0, 0.0};
            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyNum::addLinearValue(" << _timeStep << ", " << _value
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobLinearValue, _value, 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to reach at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void
    addAcceleratedValue(const size_t _timeStep, const T _value, const double _acceleration, const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyNum::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (!Math::isAligned<T>(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Value out off range (" << m_minimumValue << ", "
                      << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyNum::addAcceleratedValue(0, " << _value << ", " << _acceleration << ", "
                      << _deceleration << ") Job at time-step[0] cannot be accelerated, it must be constant!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobAcceleratedValue && Math::equals<T>((*it).second.value, _value) &&
                Math::equals<double>((*it).second.acceleration, _acceleration) &&
                Math::equals<double>((*it).second.deceleration, _deceleration))
                return;

            std::cerr << "Warning: ItemPropertyNum::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") time-step[" << _timeStep
                      << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobAcceleratedValue, _value, _acceleration, _deceleration};
            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyNum::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobAcceleratedValue, _value, _acceleration, _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const T _value)
    {
        if (!Math::isAligned<T>(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyNum::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyNum::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobLinearValue, _value, 0.0, 0.0};
            return;
        }

        const T lastValue = (*m_jobs.crbegin()).second.value;
        m_jobs[_timeStart] = {_JobConstantValue, lastValue, 0.0, 0.0};
        m_jobs[_timeStop] = {_JobLinearValue, _value, 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addFromAcceleratedValue(const size_t _timeStart,
                                 const size_t _timeStop,
                                 const T _value,
                                 const double _acceleration,
                                 const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyNum::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration
                      << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (!Math::isAligned<T>(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration << ") Value out off range ("
                      << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyNum::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyNum::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobAcceleratedValue, _value, _acceleration, _deceleration};
            return;
        }

        const T lastValue = (*m_jobs.crbegin()).second.value;
        m_jobs[_timeStart] = {_JobConstantValue, lastValue, 0.0, 0.0};
        m_jobs[_timeStop] = {_JobAcceleratedValue, _value, _acceleration, _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linear jobs within given time interval
     * \param _timeStepStart Starting time-step
     * \param _timeStepStop Final time-step
     * \param _valueMax Maximal value
     * \param _valueMin Minimal value
     * \param _durationRaise Duration from minimal value to maximal
     * \param _durationFall Duration from maximal value to minimal
     */
    void addSawInterval(const size_t _timeStepStart,
                        const size_t _timeStepStop,
                        const T _valueMax,
                        const T _valueMin,
                        const size_t _durationRaise = 1000UL,
                        const size_t _durationFall = 1000UL)
    {
        if (_timeStepStart >= _timeStepStop)
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Invalid time-step order!\n";
            return;
        }

        if (Math::isMoreOrEqual(_valueMin, _valueMax))
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueMax << ", " << _valueMin << ", ...) Invalid values!\n";
            return;
        }

        if (_durationRaise == 0UL || _durationFall == 0UL)
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ..., " << _durationRaise << ", " << _durationFall << ") Invalid interval duration!\n";
            return;
        }

        if (!Math::isAligned<T>(_valueMax, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueMin, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueMax << ", " << _valueMin << "...) Values out off range (" << m_minimumValue << ", "
                      << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't add, jobs are not initialized!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first <= _timeStepStart)
        {
            addSawInterval(_timeStepStart,
                           _timeStepStop,
                           _valueMax,
                           _valueMin,
                           (*m_jobs.crbegin()).second.value,
                           (*m_jobs.crbegin()).second.value,
                           _durationRaise,
                           _durationFall);
        }
        else
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't create inner job!\n";
        }
    }

    /*!
     * \brief Append linear jobs within given time interval
     * \param _timeStepStart Starting time-step
     * \param _timeStepStop Final time-step
     * \param _valueStart Initial value at start
     * \param _valueStop Final value at final time-step
     * \param _valueMax Maximal value
     * \param _valueMin Minimal value
     * \param _durationRaise Duration from minimal value to maximal
     * \param _durationFall Duration from maximal value to minimal
     */
    void addSawInterval(const size_t _timeStepStart,
                        const size_t _timeStepStop,
                        const T _valueMax,
                        const T _valueMin,
                        const T _valueStart,
                        const T _valueStop,
                        const size_t _durationRaise = 1000UL,
                        const size_t _durationFall = 1000UL)
    {
        if (_timeStepStart >= _timeStepStop)
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Invalid time-step order!\n";
            return;
        }

        if (Math::isMoreOrEqual(_valueMin, _valueMax) || !Math::isAligned(_valueStart, _valueMin, _valueMax) ||
            !Math::isAligned(_valueStop, _valueMin, _valueMax))
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueStart << ", " << _valueStop << ", " << _valueMax << ", " << _valueMin
                      << "...) Invalid values!\n";
            return;
        }

        if (_durationRaise == 0UL || _durationFall == 0UL)
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ..., " << _durationRaise << ", " << _durationFall << ") Invalid interval duration!\n";
            return;
        }

        if (!Math::isAligned<T>(_valueStart, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueStop, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueMax, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueMin, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueStart << ", " << _valueStop << ", " << _valueMax << ", " << _valueMin
                      << "...) Values out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't add, jobs are not initialized!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStepStart)
        {
            if (_timeStepStart == 0UL)
                (*m_jobs.rbegin()).second.value = _valueStart;

            if (!Math::equals<T>((*m_jobs.rbegin()).second.value, _valueStart))
            {
                std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                          << ", ...) Different value at start time exist!\n";
                return;
            }
        }
        else if ((*m_jobs.crbegin()).first > _timeStepStart)
        {
            std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't create inner job!\n";
            return;
        }
        else
        {
            m_jobs.insert(m_jobs.end(), {_timeStepStart, {_JobConstantValue, _valueStart, 0.0, 0.0}});
        }

        size_t tt = _timeStepStart;
        bool isMax = Math::equals<T>(_valueStart, _valueMax);

        if (!isMax)
        {
            if (!Math::equals<T>(_valueStart, _valueMin))
            {
                tt += static_cast<size_t>(static_cast<long double>(_durationRaise) *
                                          static_cast<long double>(_valueMax - _valueStart) /
                                          static_cast<long double>(_valueMax - _valueMin));

                if (tt >= _timeStepStop)
                {
                    std::cerr << "Error: ItemPropertyNum::addSawInterval(" << _timeStepStart << ", " << _timeStepStop
                              << ", ...) Time interval too short for the first step!\n";
                    return;
                }

                m_jobs.insert(m_jobs.end(), {tt, {_JobLinearValue, _valueMax, 0.0, 0.0}});
                isMax = true;
            }
        }

        while (true)
        {
            isMax = !isMax;
            const size_t ttNext = tt + (isMax ? _durationRaise : _durationFall);

            if (ttNext >= _timeStepStop)
            {
                m_jobs.insert(m_jobs.end(), {ttNext, {_JobLinearValue, _valueStop, 0.0, 0.0}});
                return;
            }

            tt = ttNext;
            m_jobs.insert(m_jobs.end(), {tt, {_JobLinearValue, isMax ? _valueMax : _valueMin, 0.0, 0.0}});
        }
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated jobs within given time interval
     * \param _timeStepStart Starting time-step
     * \param _timeStepStop Final time-step
     * \param _valueMax Maximal value
     * \param _valueMin Minimal value
     * \param _durationRaise Duration from minimal value to maximal
     * \param _durationFall Duration from maximal value to minimal
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addSinusInterval(const size_t _timeStepStart,
                          const size_t _timeStepStop,
                          const T _valueMax,
                          const T _valueMin,
                          const size_t _durationRaise = 1000UL,
                          const size_t _durationFall = 1000UL,
                          const double _acceleration = 0.48,
                          const double _deceleration = 0.48)
    {
        if (_timeStepStart >= _timeStepStop)
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Invalid time-step order!\n";
            return;
        }

        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ... , " << _acceleration << ", " << _deceleration
                      << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (Math::isMoreOrEqual(_valueMin, _valueMax))
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueMax << ", " << _valueMin << ", ...) Invalid values!\n";
            return;
        }

        if (_durationRaise == 0UL || _durationFall == 0UL)
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ..., " << _durationRaise << ", " << _durationFall << ") Invalid interval duration!\n";
            return;
        }

        if (!Math::isAligned<T>(_valueMax, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueMin, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueMax << ", " << _valueMin << "...) Values out off range (" << m_minimumValue << ", "
                      << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't add, jobs are not initialized!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first <= _timeStepStart)
        {
            addSinusInterval(_timeStepStart,
                             _timeStepStop,
                             _valueMax,
                             _valueMin,
                             (*m_jobs.crbegin()).second.value,
                             (*m_jobs.crbegin()).second.value,
                             _durationRaise,
                             _durationFall);
        }
        else
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't create inner job!\n";
        }
    }

    /*!
     * \brief Append sinus like distributed jobs within given time interval
     * \param _timeStepStart Starting time-step
     * \param _timeStepStop Final time-step
     * \param _valueStart Initial value at start
     * \param _valueStop Final value at final time-step
     * \param _valueMax Maximal value
     * \param _valueMin Minimal value
     * \param _durationRaise Duration from minimal value to maximal
     * \param _durationFall Duration from maximal value to minimal
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     * \note Sinus is constructed from accelerated jobs
     */
    void addSinusInterval(const size_t _timeStepStart,
                          const size_t _timeStepStop,
                          const T _valueMax,
                          const T _valueMin,
                          const T _valueStart,
                          const T _valueStop,
                          const size_t _durationRaise = 1000UL,
                          const size_t _durationFall = 1000UL,
                          const double _acceleration = 0.48,
                          const double _deceleration = 0.48)
    {
        if (_timeStepStart >= _timeStepStop)
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Invalid time-step order!\n";
            return;
        }

        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ... , " << _acceleration << ", " << _deceleration
                      << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (Math::isMoreOrEqual(_valueMin, _valueMax) || !Math::isAligned(_valueStart, _valueMin, _valueMax) ||
            !Math::isAligned(_valueStop, _valueMin, _valueMax))
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueStart << ", " << _valueStop << ", " << _valueMax << ", " << _valueMin
                      << "...) Invalid values!\n";
            return;
        }

        if (_durationRaise == 0UL || _durationFall == 0UL)
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ..., " << _durationRaise << ", " << _durationFall << ") Invalid interval duration!\n";
            return;
        }

        if (!Math::isAligned<T>(_valueStart, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueStop, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueMax, m_minimumValue, m_maximumValue) ||
            !Math::isAligned<T>(_valueMin, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop << ", "
                      << _valueStart << ", " << _valueStop << ", " << _valueMax << ", " << _valueMin
                      << "...) Values out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't add, jobs are not initialized!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStepStart)
        {
            if (_timeStepStart == 0UL)
                (*m_jobs.rbegin()).second.value = _valueStart;

            if (!Math::equals<T>((*m_jobs.rbegin()).second.value, _valueStart))
            {
                std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                          << ", ...) Different value at start time exist!\n";
                return;
            }
        }
        else if ((*m_jobs.crbegin()).first > _timeStepStart)
        {
            std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                      << ", ...) Can't create inner job!\n";
            return;
        }
        else
        {
            m_jobs.insert(m_jobs.end(), {_timeStepStart, {_JobConstantValue, _valueStart, 0.0, 0.0}});
        }

        size_t tt = _timeStepStart;
        bool isMax = Math::equals<T>(_valueStart, _valueMax);

        if (!isMax)
        {
            if (!Math::equals<T>(_valueStart, _valueMin))
            {
                tt += static_cast<size_t>(static_cast<long double>(_durationRaise) *
                                          static_cast<long double>(_valueMax - _valueStart) /
                                          static_cast<long double>(_valueMax - _valueMin));

                if (tt >= _timeStepStop)
                {
                    std::cerr << "Error: ItemPropertyNum::addSinusInterval(" << _timeStepStart << ", " << _timeStepStop
                              << ", ...) Time interval too short for the first step!\n";
                    return;
                }

                m_jobs.insert(m_jobs.end(), {tt, {_JobAcceleratedValue, _valueMax, _acceleration, _deceleration}});
                isMax = true;
            }
        }

        while (true)
        {
            isMax = !isMax;
            const size_t ttNext = tt + (isMax ? _durationRaise : _durationFall);

            if (ttNext >= _timeStepStop)
            {
                m_jobs.insert(m_jobs.end(), {ttNext, {_JobAcceleratedValue, _valueStop, _acceleration, _deceleration}});
                return;
            }

            tt = ttNext;
            m_jobs.insert(m_jobs.end(),
                          {tt, {_JobAcceleratedValue, isMax ? _valueMax : _valueMin, _acceleration, _deceleration}});
        }
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Last value at last time-step
     * \return Value stored at latest time-step
     */
    inline T latestValue() const
    {
        if (m_jobs.empty())
            return T(0);

        return (*m_jobs.crbegin()).second.value;
    }

    /*!
     * \brief Jobs getter
     * \return Jobs map
     */
    inline const std::map<size_t, Job> &jobs() const
    {
        return m_jobs;
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 8 bit unsigned integer property */
class ItemPropertyUInt8 : public ItemProperty, public ItemPropertyNum<uint8_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyUInt8(const std::string &_name,
                             const uint8_t _initialValue,
                             const uint8_t _minimumValue,
                             const uint8_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<uint8_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyUInt8(const std::string &_name, const uint8_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<uint8_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 8 bit signed integer property */
class ItemPropertyInt8 : public ItemProperty, public ItemPropertyNum<int8_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyInt8(const std::string &_name,
                            const int8_t _initialValue,
                            const int8_t _minimumValue,
                            const int8_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<int8_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyInt8(const std::string &_name, const int8_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<int8_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 16 bit unsigned integer property */
class ItemPropertyUInt16 : public ItemProperty, public ItemPropertyNum<uint16_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyUInt16(const std::string &_name,
                              const uint16_t _initialValue,
                              const uint16_t _minimumValue,
                              const uint16_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<uint16_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyUInt16(const std::string &_name, const uint16_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<uint16_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 16 bit signed integer property */
class ItemPropertyInt16 : public ItemProperty, public ItemPropertyNum<int16_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyInt16(const std::string &_name,
                             const int16_t _initialValue,
                             const int16_t _minimumValue,
                             const int16_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<int16_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyInt16(const std::string &_name, const int16_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<int16_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 32 bit unsigned integer property */
class ItemPropertyUInt32 : public ItemProperty, public ItemPropertyNum<uint32_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyUInt32(const std::string &_name,
                              const uint32_t _initialValue,
                              const uint32_t _minimumValue,
                              const uint32_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<uint32_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyUInt32(const std::string &_name, const uint32_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<uint32_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 32 bit signed integer property */
class ItemPropertyInt32 : public ItemProperty, public ItemPropertyNum<int32_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyInt32(const std::string &_name,
                             const int32_t _initialValue,
                             const int32_t _minimumValue,
                             const int32_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<int32_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyInt32(const std::string &_name, const int32_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<int32_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 64 bit unsigned integer property */
class ItemPropertyUInt64 : public ItemProperty, public ItemPropertyNum<uint64_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyUInt64(const std::string &_name,
                              const uint64_t _initialValue,
                              const uint64_t _minimumValue,
                              const uint64_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<uint64_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyUInt64(const std::string &_name, const uint64_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<uint64_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 64 bit signed integer property */
class ItemPropertyInt64 : public ItemProperty, public ItemPropertyNum<int64_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyInt64(const std::string &_name,
                             const int64_t _initialValue,
                             const int64_t _minimumValue,
                             const int64_t _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<int64_t>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyInt64(const std::string &_name, const int64_t _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<int64_t>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 64 bit unsigned integer property (circle quality) */
class ItemPropertyQuality : public ItemProperty, public ItemPropertyNum<size_t>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyQuality(const std::string &_name, const size_t _initialValue)
        : ItemProperty(_name)
        , ItemPropertyNum<size_t>(_initialValue, size_t(0UL), size_t(1024UL))
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 32 bit floating point property */
class ItemPropertyFloat : public ItemProperty, public ItemPropertyNum<float>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyFloat(const std::string &_name,
                             const float _initialValue,
                             const float _minimumValue,
                             const float _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<float>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyFloat(const std::string &_name, const float _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<float>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 64 bit floating point property */
class ItemPropertyDouble : public ItemProperty, public ItemPropertyNum<double>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyDouble(const std::string &_name,
                              const double _initialValue,
                              const double _minimumValue,
                              const double _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<double>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyDouble(const std::string &_name, const double _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<double>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 128 bit floating point property */
class ItemPropertyLongDouble : public ItemProperty, public ItemPropertyNum<long double>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyLongDouble(const std::string &_name,
                                  const long double _initialValue,
                                  const long double _minimumValue,
                                  const long double _maximumValue)
        : ItemProperty(_name)
        , ItemPropertyNum<long double>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyLongDouble(const std::string &_name, const long double _initialValue = 0)
        : ItemProperty(_name)
        , ItemPropertyNum<long double>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYNUM_H
