/*!
 * \file math/objecthistory.h
 * \author Michal Steller
 * \brief Object history base template implementation
 */

#ifndef OBJECTHISTORY_H
#define OBJECTHISTORY_H

#include "timestamp.h"

#include <list>
#include <vector>

namespace Universe1 {
namespace Simulation {

/*!
 * \brief Enumeration for type of found result within event-source lookup
 */
enum EventSourceResult : uint8_t
{
    EventSourceEmptyPath,  //!< Object's history is empty (\b Error state)

    EventSourceFoundExact,  //!< Source for event found at exact position

    EventSourceFoundClosest,  //!< Exact source position for event lies in between returned and next step in history
                              //!< (Result needs additional move in time forward)

    EventSourceFoundFirst,  //!< Exact source position for event lies behind current step in history (\b Warning state,
                            //!< object needs more progress, result needs additional move in time forward)

    EventSourceMissing,  //!< Exact source position for event lies behind last step in history (\b Warning state,
                         //!< object's history is too short, result needs additional move in time backwards)

};

/*!
 * \brief Base object history class
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \details When history is fully-filled, then it continue looping by replacing oldest time-stamps
 */
template <typename T, typename TimeStampClass>
struct ObjectHistory
{
 protected:
    bool m_filled;                          //!< History filled / looping enabled flag
    size_t m_currentIdx;                    //!< Index of current object data in history buffer
    std::vector<TimeStampClass> m_history;  //!< History object data buffer

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value &&
                                        std::is_base_of<TimeStamp<T>, TimeStampClass>::value>>
    inline ObjectHistory()
        : m_filled(false)
        , m_currentIdx(0U)
    {
    }

    /*!
     * \brief Constructor
     * \param _size History buffer size
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value &&
                                        std::is_base_of<TimeStamp<T>, TimeStampClass>::value>>
    inline ObjectHistory(const size_t _size)
        : m_filled(false)
        , m_currentIdx(0U)
    {
        m_history.resize(_size);
    }

 public:
    /*!
     * \brief Getter for history buffer
     * \returns History buffer
     */
    inline const std::vector<TimeStampClass> &history() const;

    /*!
     * \brief Getter for current time-stamp data
     * \returns Current time-stamp data
     */
    inline const TimeStampClass *current() const;

    /*!
     * \brief Getter for current time-stamp data
     * \returns Current time-stamp data
     */
    inline TimeStampClass *current();

    void initHistory(const size_t _size);

 protected:
    void addToHistory(const TimeStampClass &newData);

    std::pair<EventSourceResult, const TimeStampClass *>
    eventSource(const T universeVelocity, const T eventTimeStamp, const Math::Vec3<T> &eventPosition) const;
};

template <typename T, typename TimeStampClass>
inline const std::vector<TimeStampClass> &ObjectHistory<T, TimeStampClass>::history() const
{
    return m_history;
}

template <typename T, typename TimeStampClass>
inline const TimeStampClass *ObjectHistory<T, TimeStampClass>::current() const
{
    return m_history.empty() ? nullptr : &m_history.at(m_currentIdx);
}

template <typename T, typename TimeStampClass>
inline TimeStampClass *ObjectHistory<T, TimeStampClass>::current()
{
    return m_history.empty() ? nullptr : &m_history.at(m_currentIdx);
}

/*!
 * \brief Initialize history buffer
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \param _size New history buffer size
 */
template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::initHistory(const size_t _size)
{
    m_filled = false;
    m_currentIdx = 0U;
    m_history.resize(_size);
}

/*!
 * \brief Append new time-stamp data into history buffer
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \param newData New time-stamp data
 */
template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::addToHistory(const TimeStampClass &newData)
{
    const size_t hs = m_history.size();
    if (hs == 0U)
        return;

    m_currentIdx++;
    if (m_currentIdx == hs)
    {
        m_currentIdx = 0U;
        m_filled = true;
    }
    m_history[m_currentIdx] = newData;
}

/*!
 * \brief Macro check if time equals and possible exit with \c EventSourceFoundExact result
 * \param ATTR_TIME Variable to check
 * \param ATTR_OBJ Possible found result
 */
#define EVENT_SOURCE_CHECK_EXACT(ATTR_TIME, ATTR_OBJ)                                                                  \
    if (Type::equals<T>(ATTR_TIME, eventTimeStamp))                                                                    \
        return                                                                                                         \
        {                                                                                                              \
            EventSourceFoundExact, ATTR_OBJ                                                                            \
        }

/*!
 * \brief Macro that setup and check absolute \b marked first and last (\c idxBefore and \c idxAfter) history items
 */
#define EVENT_SOURCE_FIRST_CHECK()                                                                                     \
    objBefore = &m_history.at(idxBefore);                                                                              \
    timeBefore = objBefore->getTimeWhenWaveHitEvent(universeVelocity, eventPosition);                                  \
    EVENT_SOURCE_CHECK_EXACT(timeBefore, objBefore);                                                                   \
    if (timeBefore > eventTimeStamp)                                                                                   \
        return {EventSourceFoundFirst, objBefore};                                                                     \
                                                                                                                       \
    objAfter = &m_history.at(idxAfter);                                                                                \
    timeAfter = objAfter->getTimeWhenWaveHitEvent(universeVelocity, eventPosition);                                    \
    EVENT_SOURCE_CHECK_EXACT(timeAfter, objAfter);                                                                     \
    if (timeAfter < eventTimeStamp)                                                                                    \
        return                                                                                                         \
        {                                                                                                              \
            EventSourceMissing, objAfter                                                                               \
        }

/*!
 * \brief Find closest position in history, from where wave hits event
 * \param universeVelocity Speed of the Universe
 * \param eventTimeStamp Time-stamp of event
 * \param eventPosition Event location
 * \return Pair of result type + closest time-stamp
 */
template <typename T, typename TimeStampClass>
std::pair<EventSourceResult, const TimeStampClass *> ObjectHistory<T, TimeStampClass>::eventSource(
    const T universeVelocity, const T eventTimeStamp, const Math::Vec3<T> &eventPosition) const
{
    if (m_history.size() < 2U || (!m_filled && m_currentIdx == 0U))
        return {EventSourceEmptyPath, nullptr};

    const size_t idxLastHist = m_history.size() - 1U;

    size_t idxBefore;
    size_t idxAfter;

    const TimeStampClass *objBefore = nullptr;
    const TimeStampClass *objAfter = nullptr;

    T timeBefore;
    T timeAfter;

    if (m_filled && m_currentIdx != idxLastHist)
    {
        if (m_currentIdx == 0U)
        {
            idxBefore = idxLastHist;
            idxAfter = 1U;
            EVENT_SOURCE_FIRST_CHECK();
        }
        else
        {
            idxBefore = m_currentIdx - 1U;
            idxAfter = m_currentIdx + 1U;
            EVENT_SOURCE_FIRST_CHECK();

            const TimeStampClass *objBreak0 = &m_history.at(0U);
            const T timeBreak0 = objBreak0->getTimeWhenWaveHitEvent(universeVelocity, eventPosition);
            EVENT_SOURCE_CHECK_EXACT(timeBreak0, objBreak0);

            if (timeBreak0 > eventTimeStamp)
            {
                idxAfter = 0U;
                objAfter = objBreak0;
                timeAfter = timeBreak0;
            }
            else
            {
                idxBefore = idxLastHist;
                objBefore = &m_history.at(idxBefore);
                timeBefore = objBefore->getTimeWhenWaveHitEvent(universeVelocity, eventPosition);
                EVENT_SOURCE_CHECK_EXACT(timeBefore, objBefore);
                if (timeBefore > eventTimeStamp)
                    return {EventSourceFoundClosest, objBefore};
            }
        }
    }
    else
    {
        idxBefore = m_currentIdx - 1U;
        idxAfter = 0U;
        EVENT_SOURCE_FIRST_CHECK();
    }

    size_t idxRange = idxBefore - idxAfter;

    while (idxRange > 1U)
    {
        T timeDeltaBefore = eventTimeStamp - timeBefore;
        T timeDeltaAfter = timeAfter - eventTimeStamp;
        T timeDeltaSum = timeDeltaBefore + timeDeltaAfter;

        const size_t idxMiddle = idxAfter +
            std::max(size_t(1U), static_cast<size_t>(static_cast<double>(idxRange) * timeDeltaAfter / timeDeltaSum));

        const TimeStampClass *objMiddle = &m_history.at(idxMiddle);
        const T timeMiddle = objMiddle->getTimeWhenWaveHitEvent(universeVelocity, eventPosition);
        EVENT_SOURCE_CHECK_EXACT(timeMiddle, objMiddle);

        if (timeMiddle < eventTimeStamp)
        {
            idxBefore = idxMiddle;
            // objBefore = objMiddle;
            timeBefore = timeMiddle;
        }
        else
        {
            idxAfter = idxMiddle;
            objAfter = objMiddle;
            timeAfter = timeMiddle;
        }
        idxRange = idxBefore - idxAfter;
    }

    return {EventSourceFoundClosest, objAfter};
}

#undef EVENT_SOURCE_CHECK_EXACT
#undef EVENT_SOURCE_FIRST_CHECK

}  // namespace Simulation
}  // namespace Universe1

#endif  // OBJECTHISTORY_H
