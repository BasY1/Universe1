#ifndef UNIVERSE1_VIDEO_DYNAMICALIGN_H
#define UNIVERSE1_VIDEO_DYNAMICALIGN_H

#include "dynamicenum.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic alignment property
 */
struct DynamicAlign : public DynamicProperty
{
    std::list<std::pair<uint64_t, Qt::Alignment>> values;  //!< Values at time-steps

    /*!
     * \brief Constructor
     * \param _value Initial value
     * \param _name Property name
     */
    DynamicAlign(const Qt::Alignment _value, const std::string &_name);

    /*!
     * \brief Initialize enumeration property
     * \param _duration Footage duration
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Returns enumeration value at specific time-step
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    inline Qt::Alignment getValue(const uint64_t _timeStep) const
    {
        return getValueConstant<Qt::Alignment>(values, _timeStep);
    }

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
    inline DynamicAlign &operator=(const Qt::Alignment _value)
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
    void add(const uint64_t _timeStep, const Qt::Alignment _value);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICALIGN_H
