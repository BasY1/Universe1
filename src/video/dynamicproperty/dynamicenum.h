#ifndef UNIVERSE1_VIDEO_DYNAMICENUM_H
#define UNIVERSE1_VIDEO_DYNAMICENUM_H

#include "dynamicvalue.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic enumeration property
 * \tparam T Enum type
 */
template <typename T>
struct DynamicEnum : public DynamicProperty
{
    std::list<std::pair<uint64_t, T>> values;  //!< Values at time-steps

    /*!
     * \brief Constructor
     * \param _value Initial value
     * \param _name Property name
     */
    template <typename = std::enable_if<std::is_enum<T>::value>>
    DynamicEnum(const T _value, const std::string &_name)
        : DynamicProperty(_ENUM, _name)
    {
        values.push_back({0UL, _value});
    }

    /*!
     * \brief Initialize enumeration property
     * \param _duration Footage duration
     * \return Success flag
     */
    bool initialize(const uint64_t _duration)
    {
        return initializeImpl<T>(values, _duration);
    }

    /*!
     * \brief Returns enumeration value at specific time-step
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    T getValue(const uint64_t _timeStep) const
    {
        return getValueConstant<T>(values, _timeStep);
    }

    /*!
     * \brief Returns value at specific time-step as string
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    QString getValueText(const uint64_t _timeStep) const
    {
        return QString::number(getValue(_timeStep));
    }

    /*!
     * \brief Assign operator, setup value to last item in data list
     * \param _value Value to set
     * \return This object
     */
    inline DynamicEnum<T> &operator=(const T _value)
    {
        if (!values.empty())
            values.back().second = _value;
        return *this;
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
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICENUM_H
