#ifndef UNIVERSE1_VIDEO_DYNAMICCOLOR_H
#define UNIVERSE1_VIDEO_DYNAMICCOLOR_H

#include "dynamicvec3.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic color property
 */
struct DynamicColor : public DynamicProperty
{
    std::list<std::pair<uint64_t, QColor>> values;  //!< Values at time-steps

    /*!
     * \brief Constructor
     * \param _value Initial color
     * \param _name Property name
     */
    DynamicColor(const QColor &_value, const std::string &_name);

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
    QColor getValue(const uint64_t _timeStep) const;

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
    inline DynamicColor &operator=(const QColor &_value)
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
    QColor addSame(const uint64_t _timeStep);

    /*!
     * \brief Add new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void add(const uint64_t _timeStep, const QColor &_value);

    /*!
     * \brief Add same value as last stored at start time-step and new value at end time-step
     * \param _timeStepStart Jump start time
     * \param _timeStepEnd Jump end time
     * \param _value New value
     */
    void addJump(const uint64_t _timeStepStart, const uint64_t _timeStepEnd, const QColor &_value);

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
                 const QColor &_value1,
                 const QColor &_value2,
                 const uint64_t _durationValue1toValue2 = 1000UL,
                 const uint64_t _durationValue2toValue1 = 1000UL);

    /*!
     * \brief Add loop values
     * \param _timeStepStart Start time ms
     * \param _timeStepEnd End time ms
     * \param _value Second value
     * \param _durationValue1toValue2 Duration swap value1 to value2
     * \param _durationValue2toValue1 Duration swap value2 to value1
     */
    void addLoop(const uint64_t _timeStepStart,
                 const uint64_t _timeStepEnd,
                 const QColor &_value,
                 const uint64_t _durationValue1toValue2 = 1000UL,
                 const uint64_t _durationValue2toValue1 = 1000UL);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICCOLOR_H
