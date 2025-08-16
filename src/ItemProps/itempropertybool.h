/*!
 * \file src/ItemProps/itempropertybool.h
 * \brief Dynamic boolean property
 */

#ifndef PROPS_ITEMPROPERTYBOOL_H
#define PROPS_ITEMPROPERTYBOOL_H

#include "itemproperty.h"

#include <map>

namespace U1 {
namespace Props {

/*! \brief Dynamic boolean property */
class ItemPropertyBool : public ItemProperty
{
 protected:
    std::map<size_t, bool> m_jobs;  //!< Property jobs

 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    ItemPropertyBool(const std::string &_name, const bool _initialValue = true);

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

    /*!
     * \brief Getter for property value at specific time step
     * \param _timeStep Time step
     * \return Property value
     */
    bool value(const size_t _timeStep) const;

    /*!
     * \brief Returns value at given time-step as text
     * \param _timeStep Time-step
     * \return Value at given time-step as text
     */
    QString textValue(const size_t _timeStep) const override;

    /*!
     * \brief Setup new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void setValue(const size_t _timeStep, const bool _value);

    /*!
     * \brief Setup initial value
     * \param _value Initial value
     */
    void initValue(const bool _value);

    /*! \brief Setup initial value ON */
    void initOn();

    /*! \brief Setup initial value OFF */
    void initOff();

    /*!
     * \brief Setup initial value ON and then add value OFF at specific time-step
     * \param _timeStepOff Time-step for value OFF
     */
    void initOn_Off(const size_t _timeStepOff);

    /*!
     * \brief Setup initial value OFF and then add value ON at specific time-step
     * \param _timeStepOn Time-step for value ON
     */
    void initOff_On(const size_t _timeStepOn);

    /*!
     * \brief Setup initial value OFF and then add value ON followed by value OFF at specific time-steps
     * \param _timeStepOn Time-step for value ON
     * \param _timeStepOff Time-step for value OFF
     */
    void initOff_On_Off(const size_t _timeStepOn, const size_t _timeStepOff);

    /*!
     * \brief Add value OFF
     * \param _timeStepOff Time-step for value OFF
     */
    inline void addOff(const size_t _timeStepOff)
    {
        setValue(_timeStepOff, false);
    }

    /*!
     * \brief Add value ON
     * \param _timeStepOn Time-step for value ON
     */
    inline void addOn(const size_t _timeStepOn)
    {
        setValue(_timeStepOn, true);
    }

    /*!
     * \brief Add value OFF and then add value ON
     * \param _timeStepOff Time-step for value OFF
     * \param _timeStepOn Time-step for value ON
     */
    void addOff_On(const size_t _timeStepOff, const size_t _timeStepOn);

    /*!
     * \brief Add value ON and then add value OFF
     * \param _timeStepOn Time-step for value ON
     * \param _timeStepOff Time-step for value OFF
     */
    void addOn_Off(const size_t _timeStepOn, const size_t _timeStepOff);

    /*!
     * \brief Append ON/OFF jobs within given time interval
     * \param _timeStepStart Starting time-step
     * \param _timeStepStop Final time-step
     * \param _valueStart Initial value at start
     * \param _valueStop Final value at final time-step
     * \param _durationOn Duration of value ON (in mili-seconds)
     * \param _durationOff Duration of value OFF (in mili-seconds)
     */
    void addSwapInterval(const size_t _timeStepStart,
                         const size_t _timeStepStop,
                         const bool _valueStart = true,
                         const bool _valueStop = true,
                         const size_t _durationOn = 1000,
                         const size_t _durationOff = 1000);

    /*!
     * \brief Getter for the initial value
     * \return Initial value
     */
    inline bool getInitValue() const
    {
        return m_jobs.empty() ? false : (*m_jobs.cbegin()).second;
    }

    /*!
     * \brief Last value at last time-step
     * \return Value stored at latest time-step
     */
    inline bool latestValue() const
    {
        return m_jobs.empty() ? false : (*m_jobs.crbegin()).second;
    }

    /*!
     * \brief Jobs getter
     * \return Jobs map
     */
    inline const std::map<size_t, bool> &jobs() const
    {
        return m_jobs;
    }

};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYBOOL_H
