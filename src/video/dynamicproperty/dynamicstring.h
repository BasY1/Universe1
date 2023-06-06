#ifndef UNIVERSE1_VIDEO_DYNAMICSTRING_H
#define UNIVERSE1_VIDEO_DYNAMICSTRING_H

#include "dynamiccolor.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic string property
 */
struct DynamicString : public DynamicProperty
{
    std::list<std::pair<uint64_t, QString>> values;  //!< Values at time-steps

    /*!
     * \brief Constructor
     * \param _value Initial color
     * \param _name Property name
     */
    DynamicString(const QString &_value, const std::string &_name);

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
    QString getValue(const uint64_t _timeStep) const;

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
    inline DynamicString &operator=(const QString &_value)
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
    void add(const uint64_t _timeStep, const QString &_value);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICSTRING_H
