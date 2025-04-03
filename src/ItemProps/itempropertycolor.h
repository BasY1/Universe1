/*!
 * \file src/ItemProps/itempropertycolor.h
 * \brief Color dynamic item property
 */

#ifndef PROPS_ITEMPROPERTYCOLOR_H
#define PROPS_ITEMPROPERTYCOLOR_H

#include "../Math/colorrgb.h"
#include "itempropertynum.h"
#include "itempropertygroup.h"

namespace U1 {
namespace Props {

/*! \brief Color dynamic item property */
class ItemPropertyColor : public ItemPropertyGroup
{
 public:
    ItemPropertyUInt8 red;    //!< Red component
    ItemPropertyUInt8 green;  //!< Green component
    ItemPropertyUInt8 blue;   //!< Blue component

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial color
     */
    ItemPropertyColor(const std::string &_name, const Math::ColorRGB &_initialValue);

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial \c QColor
     */
    inline ItemPropertyColor(const std::string &_name, const QColor &_initialValue)
        : ItemPropertyColor(_name, Math::ColorRGB(_initialValue))
    {
    }

    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    inline Math::ColorRGB value(const size_t _timeStep) const
    {
        return Math::ColorRGB{red.value(_timeStep), green.value(_timeStep), blue.value(_timeStep)};
    }

    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    inline QColor valueQColor(const size_t _timeStep) const
    {
        return QColor(int(red.value(_timeStep)), int(green.value(_timeStep)), int(blue.value(_timeStep)));
    }

    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    inline QVector3D valueQVec3(const size_t _timeStep) const
    {
        return value(_timeStep).toQVec3();
    }

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const Math::ColorRGB &_initialValue)
    {
        red.initValue(_initialValue.red);
        green.initValue(_initialValue.green);
        blue.initValue(_initialValue.blue);
    }

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const QColor &_initialValue)
    {
        initValue(Math::ColorRGB(_initialValue));
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        red.initValueUpTo(_timeStep, _value.red);
        green.initValueUpTo(_timeStep, _value.green);
        blue.initValueUpTo(_timeStep, _value.blue);
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const QColor &_value)
    {
        initValueUpTo(_timeStep, Math::ColorRGB(_value));
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        red.addConstantValue(_timeStep, _value.red);
        green.addConstantValue(_timeStep, _value.green);
        blue.addConstantValue(_timeStep, _value.blue);
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const QColor &_value)
    {
        addConstantValue(_timeStep, Math::ColorRGB(_value));
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        red.addLinearValue(_timeStep, _value.red);
        green.addLinearValue(_timeStep, _value.green);
        blue.addLinearValue(_timeStep, _value.blue);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const QColor &_value)
    {
        addLinearValue(_timeStep, Math::ColorRGB(_value));
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::ColorRGB &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        red.addAcceleratedValue(_timeStep, _value.red, _acceleration, _deceleration);
        green.addAcceleratedValue(_timeStep, _value.green, _acceleration, _deceleration);
        blue.addAcceleratedValue(_timeStep, _value.blue, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const QColor &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(_timeStep, Math::ColorRGB(_value), _acceleration, _deceleration);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const Math::ColorRGB &_value)
    {
        red.addFromLinearValue(_timeStart, _timeStop, _value.red);
        green.addFromLinearValue(_timeStart, _timeStop, _value.green);
        blue.addFromLinearValue(_timeStart, _timeStop, _value.blue);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const QColor &_value)
    {
        addFromLinearValue(_timeStart, _timeStop, Math::ColorRGB(_value));
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::ColorRGB &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        red.addFromAcceleratedValue(_timeStart, _timeStop, _value.red, _acceleration, _deceleration);
        green.addFromAcceleratedValue(_timeStart, _timeStop, _value.green, _acceleration, _deceleration);
        blue.addFromAcceleratedValue(_timeStart, _timeStop, _value.blue, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const QColor &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart, _timeStop, Math::ColorRGB(_value), _acceleration, _deceleration);
    }
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYCOLOR_H
