#ifndef UNIVERSE1_VIDEO_DYNAMICBOOL_H
#define UNIVERSE1_VIDEO_DYNAMICBOOL_H

#include "dynamicalign.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic boolean property
 */
struct DynamicBool : public DynamicProperty
{

    std::list<std::pair<uint64_t, bool>> values;  //!< Boolean values at time-steps

    /*!
     * \brief Constructor
     * \param _value Initial value
     * \param _name Property name
     */
    DynamicBool(const bool _value, const std::string &_name);

    /*!
     * \brief Initialize property
     * \param _duration Footage duration
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Returns value at specific time-step
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    bool getValue(const uint64_t _timeStep) const;

    /*!
     * \brief Returns value at specific time-step as string
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    QString getValueText(const uint64_t _timeStep) const;

    /*!
     * \brief Assign operator, setup value to last item in data list
     * \param _value Value to set
     * \return This object
     */
    inline DynamicBool &operator=(const bool _value)
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
    void add(const uint64_t _timeStep, const bool _value);

    /*!
     * \brief Add on-off values
     * \param _timeStepStart Start time ms
     * \param _timeStepEnd End time ms
     * \param _durationOn Duration on ms
     * \param _durationOff Duration off ms
     */
    void addLoop(const uint64_t _timeStepStart,
                 const uint64_t _timeStepEnd,
                 const uint64_t _durationOn = 1000UL,
                 const uint64_t _durationOff = 1000UL);

    /*!
     * \brief Add \b on value at time-step
     * \param _timeStep
     */
    inline void addOn(const uint64_t _timeStep)
    {
        add(_timeStep, true);
    }

    /*!
     * \brief Add \b off value at time-step
     * \param _timeStep
     */
    inline void addOff(const uint64_t _timeStep)
    {
        add(_timeStep, false);
    }

    /*!
     * \brief Add \b off and \b off values
     * \param _timeStepOn On time ms
     * \param _timeStepOff Off time ms
     */
    inline void addOnOff(const uint64_t _timeStepOn, const uint64_t _timeStepOff)
    {
        add(_timeStepOn, true);
        add(_timeStepOff, false);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICBOOL_H
