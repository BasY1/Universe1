/*!
 * \file src/ItemProps/itempropertytext.h
 * \brief Text dynamic item property
 */

#ifndef PROPS_ITEMPROPERTYTEXT_H
#define PROPS_ITEMPROPERTYTEXT_H

#include "itemproperty.h"

#include <map>
#include <QString>

namespace U1 {
namespace Props {

/*! \brief Text dynamic item property */
class ItemPropertyText : public ItemProperty
{
 protected:
    std::map<size_t, QString> m_jobs;  //!< Property jobs

 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    ItemPropertyText(const std::string &_name, const QString &_initialValue = "");

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
    QString value(const size_t _timeStep) const;

    /*!
     * \brief Setup new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void setValue(const size_t _timeStep, const QString &_value);

    /*!
     * \brief Setup initial value
     * \param _value Initial value
     */
    inline void initValue(const QString &_value)
    {
        m_jobs[0UL] = _value;
    }

    /*!
     * \brief Latest time-step value
     * \return Value stored at latest time-step
     */
    inline QString latestValue() const
    {
        if (m_jobs.empty())
            return "";

        return (*m_jobs.crbegin()).second;
    }

    /*!
     * \brief Jobs getter
     * \return Jobs map
     */
    inline const std::map<size_t, QString> &jobs() const
    {
        return m_jobs;
    }
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYTEXT_H
