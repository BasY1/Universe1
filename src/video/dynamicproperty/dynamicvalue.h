#ifndef UNIVERSE1_VIDEO_DYNAMICVALUE_H
#define UNIVERSE1_VIDEO_DYNAMICVALUE_H

#include "dynamicproperty.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic numeric value property
 * \tparam T Numeric type
 */
template <typename T>
struct DynamicValue : public DynamicProperty
{
    std::list<std::pair<uint64_t, T>> values;  //!< Values at time-steps
    bool interpolated = true;                  //!< Use interpolated getter for value at time

    /*!
     * \brief Constructor
     * \param _value Initial value
     * \param _name Property name
     */
    template <typename = std::enable_if<std::is_arithmetic<T>::value>>
    DynamicValue(const T _value, const std::string &_name)
        : DynamicProperty(_VALUE, _name)
    {
        values.push_back({0UL, _value});
    }

    /*!
     * \brief Initialize numeric property
     * \param _duration Footage duration
     * \return Success flag
     */
    bool initialize(const uint64_t _duration)
    {
        return initializeImpl<T>(values, _duration);
    }

    /*!
     * \brief Returns numeric value at specific time-step
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    T getValue(const uint64_t _timeStep) const
    {
        if (interpolated)
            return getValueInterpolated<T>(values, _timeStep);
        return getValueConstant<T>(values, _timeStep);
    }

    /*!
     * \brief Returns value at specific time-step as string
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    QString getValueText(const uint64_t _timeStep) const
    {
        if constexpr (std::is_floating_point_v<T>)
        {
            QString result = QString::number(getValue(_timeStep), 'f', 3);
            if (result.endsWith(".000"))
                result.chop(4);
            else
                while (result.endsWith("0"))
                    result.chop(1);

            return result;
        }
        else
        {
            return QString::number(getValue(_timeStep));
        }
    }

    /*!
     * \brief Assign operator, setup value to last item in data list
     * \param _value Value to set
     * \return This object
     */
    inline DynamicValue<T> &operator=(const T _value)
    {
        if (!values.empty())
            values.back().second = _value;
        return *this;
    }

    /*!
     * \brief Add same value as last stored at time-step
     * \param _timeStep Time-step
     * \return Value at time-step
     */
    T addSame(const uint64_t _timeStep)
    {
        if (values.empty())
        {
            std::cerr << "Error[" << name << "]: addSame(): Empty values !" << std::endl;
            return T();
        }

        const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
        if (_timeStep != timeStepFixed)
            std::cerr << "Warning[" << name << "]: addSame(" << _timeStep
                      << "ms): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

        const T result = values.back().second;
        values.push_back({timeStepFixed, result});
        return result;
    }

    /*!
     * \brief Add new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void add(const uint64_t _timeStep, const T _value)
    {
        const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
        if (_timeStep != timeStepFixed)
            std::cerr << "Warning[" << name << "]: add(" << _timeStep << "ms, " << _value
                      << "): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

        values.push_back({timeStepFixed, _value});
    }

    /*!
     * \brief Add same value as last stored at start time-step and new value at end time-step
     * \param _timeStepStart Jump start time
     * \param _timeStepEnd Jump end time
     * \param _value New value
     */
    void addJump(const uint64_t _timeStepStart, const uint64_t _timeStepEnd, const T _value)
    {
        const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
        const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
        if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
            std::cerr << "Warning[" << name << "]: addJump(" << _timeStepStart << "ms, " << _timeStepEnd << "ms, "
                      << _value << "): Using aligned times: " << timeStepStartFixed << "ms, " << timeStepEndFixed
                      << " !" << std::endl;
        addSame(timeStepStartFixed);
        add(timeStepEndFixed, _value);
    }

    /*!
     * \brief Add loop values
     * \param _timeStepStart Start time ms
     * \param _timeStepEnd End time ms
     * \param _value1 First value
     * \param _value2 Second value
     * \param _durationValue1toValue2 Duration swap value1 to value2
     * \param _durationValue2toValue1 Duration swap value2 to value1
     */
    void addLoop(const uint64_t _timeStepStart,
                 const uint64_t _timeStepEnd,
                 const T _value1,
                 const T _value2,
                 const uint64_t _durationValue1toValue2 = 1000UL,
                 const uint64_t _durationValue2toValue1 = 1000UL)
    {
        const uint64_t timeOn = Config::cfg().fixedTime(_timeStepStart);
        const uint64_t timeOff = Config::cfg().fixedTime(_timeStepEnd);
        const uint64_t dur12 = Config::cfg().fixedTime(_durationValue1toValue2);
        const uint64_t dur21 = Config::cfg().fixedTime(_durationValue1toValue2);

        if (_timeStepStart != timeOn)
            std::cerr << "Warning[" << name << "]: addLoop(): Using aligned time start: " << timeOn << "ms !"
                      << std::endl;
        if (_timeStepEnd != timeOff)
            std::cerr << "Warning[" << name << "]: addLoop(): Using aligned time end: " << timeOff << "ms !"
                      << std::endl;
        if (_durationValue1toValue2 != dur12)
            std::cerr << "Warning[" << name << "]: addLoop(): Using aligned duration 1->2: " << dur12 << "ms !"
                      << std::endl;
        if (_durationValue2toValue1 != dur21)
            std::cerr << "Warning[" << name << "]: addLoop(): Using aligned duration 2->1: " << dur21 << "ms !"
                      << std::endl;

        const uint64_t loopTime = dur12 + dur21;
        uint64_t tt = timeOn;

        if (!values.empty() && values.back().first < tt)
            values.push_back({tt, _value1});

        while (tt + loopTime < timeOff)
        {
            values.push_back({tt + dur12, _value2});
            tt += loopTime;
            values.push_back({tt, _value1});
        }
    }

    /*!
     * \brief Add loop values
     * \param _timeStepStart Start time ms
     * \param _timeStepEnd End time ms
     * \param _value Second value
     * \param _durationValue1toValue2 Duration swap value1 to value2
     * \param _durationValue2toValue1 Duration swap value2 to value1
     */
    inline void addLoop(const uint64_t _timeStepStart,
                        const uint64_t _timeStepEnd,
                        const T _value,
                        const uint64_t _durationValue1toValue2 = 1000UL,
                        const uint64_t _durationValue2toValue1 = 1000UL)
    {
        if (values.empty())
            std::cerr << "Error[" << name << "]: addLoop(): Empty values !" << std::endl;
        else
            addLoop(_timeStepStart,
                    _timeStepEnd,
                    values.back().second,
                    _value,
                    _durationValue1toValue2,
                    _durationValue2toValue1);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICVALUE_H
