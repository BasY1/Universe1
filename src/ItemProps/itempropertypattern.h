/*!
 * \file src/ItemProps/itempropertypattern.h
 * \brief Line pattern dynamic item property
 */

#ifndef PROPS_ITEMPROPERTYPATTERN_H
#define PROPS_ITEMPROPERTYPATTERN_H

#include "itemproperty.h"

#include "../Math/multithread.h"

#include <map>
#include <QList>

namespace U1 {
namespace Props {

/*! \brief Line pattern dynamic item property */
class ItemPropertyPattern : public ItemProperty
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    ItemPropertyPattern(const std::string &_name, const uint64_t _initialValue = PATTERN_SOLID);

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
    uint64_t value(const size_t _timeStep) const;

    /*!
     * \brief Pattern at specific time step converted to \b QT format
     * \param _timeStep Time step
     * \return Pattern in \b QT format
     */
    inline QList<qreal> valueQt(const size_t _timeStep) const
    {
        return toQDashPattern(value(_timeStep));
    }

    /*!
     * \brief Setup new value at time-step
     * \param _timeStep Time-step
     * \param _value Value at time-step
     */
    void setValue(const size_t _timeStep, const uint64_t _value);

    /*!
     * \brief Setup solid pattern
     * \param _timeStep Time-step
     */
    inline void setSolid(const size_t _timeStep)
    {
        setValue(_timeStep, PATTERN_SOLID);
    }

    /*!
     * \brief Setup initial value
     * \param _value Initial value
     */
    void initValue(const uint64_t _value);

    /*!
     * \brief Setup solid pattern as initial value
     */
    inline void initSolid()
    {
        initValue(PATTERN_SOLID);
    }

    /*!
     * \brief Last value at last time-step
     * \return Value stored at latest time-step
     */
    inline bool latestValue() const
    {
        if (m_jobs.empty())
            return false;

        return (*m_jobs.crbegin()).second;
    }

    /*!
     * \brief Jobs getter
     * \return Jobs map
     */
    inline const std::map<size_t, uint64_t> &jobs() const
    {
        return m_jobs;
    }

    /*!
     * \brief \b QT line pattern
     * \param _pattern Pattern to convert
     * \return Pattern converted to \b QT format
     */
    static QList<qreal> toQDashPattern(const uint64_t _pattern);

 protected:
    std::map<size_t, uint64_t> m_jobs;  //!< Property jobs
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYPATTERN_H
