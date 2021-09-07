/*!
 * \file simulation/objecthistory.h
 * \author Michal Steller
 * \brief Object history base template implementation
 */

#ifndef UNIVERSE1_SIMULATION_OBJECTHISTORY_H
#define UNIVERSE1_SIMULATION_OBJECTHISTORY_H

#include "constants.h"
#include "timestamp.h"

#include <list>
#include <map>
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Base object history class
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \details When history is fully-filled, then it continue looping by replacing oldest time-stamps
 */
template <typename T, typename TimeStampClass>
struct ObjectHistory
{
    static const size_t minimumHistorySize{3U};  //!< Default minimum size for history size

 protected:
    const size_t m_objectID;                //!< Object's ID
    size_t m_currentIdx;                    //!< Index of current object data in history buffer
    bool m_filled;                          //!< History filled / looping enabled flag
    std::vector<TimeStampClass> m_history;  //!< History object data buffer

    /*!
     * \brief Default constructor
     * \param _objectID Object's ID
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value &&
                                        std::is_base_of<TimeStamp<T>, TimeStampClass>::value>>
    inline ObjectHistory(const size_t _objectID)
        : m_objectID(_objectID)
        , m_currentIdx(0U)
        , m_filled(false)
    {
    }

    /*!
     * \brief Constructor
     * \param _objectID Object's ID
     * \param _size History buffer size
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value &&
                                        std::is_base_of<TimeStamp<T>, TimeStampClass>::value>>
    inline ObjectHistory(const size_t _objectID, const size_t _size)
        : m_objectID(_objectID)
        , m_currentIdx(0U)
        , m_filled(false)
    {
        if (_size >= minimumHistorySize)
            m_history.resize(_size);
    }

 public:
    /*!
     * \brief Getter for history filled / looping enabled flag
     * \returns History filled / looping enabled flag
     */
    inline bool filled() const;

    /*!
     * \brief Getter for index of current object data in history buffer
     * \returns Index of current object data in history buffer
     */
    inline size_t currentIdx() const;

    /*!
     * \brief Getter for object's ID
     * \returns Object's ID
     */
    inline size_t ID() const;

    /*!
     * \brief Getter for history initialized flag (History size is at least )
     * \returns History initialized flag
     */
    inline bool initialized() const;

    /*!
     * \brief Getter for history buffer
     * \returns History buffer
     */
    inline const std::vector<TimeStampClass> &history() const;

    /*!
     * \brief Getter for history buffer
     * \returns History buffer
     */
    inline std::vector<TimeStampClass> &history();

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

    /*!
     * \brief Returns index in history by step count from current
     * \param _offset Offset - step count from current index
     * \returns Index in history by step count from current
     */
    inline size_t historyIdxByOffset(const size_t _offset) const;

    /*!
     * \brief Getter for time-stamp data N steps before current
     * \param _offset Offset (N) - step count from current index
     * \returns Time-stamp data "offset" steps before current time-stamp
     * \note When given \a _offset is out of history vector range, then null is returned
     */
    inline const TimeStampClass *historyTimeStampByOffset(const size_t _offset) const;

    /*!
     * \brief Returns count of stored time-stamps in history
     * \returns Stored time-stamp count
     */
    size_t historyStepCount() const;

    /*!
     * \brief Test if object history is continuous and contains at least 2 time-stamps
     * \returns \c true when object history is continuous and filled
     */
    bool isValidPath() const;

 protected:
    /*!
     * \brief Test if object history is continuous and contains at least 2 time-stamps
     * \param _firstIDX First index in history (oldest)
     * \param _lastIDX Last index in history (newest)
     * \returns \c true when object history is continuous and filled
     */
    bool isValidPathPart(const size_t _firstIDX, const size_t _lastIDX) const;

 public:
    /*!
     * \brief Initialize history buffer
     * \param _size New history buffer size
     */
    void initHistory(const size_t _size);

    /*!
     * \brief Initialize history buffer
     * \param _filled  History filled / looping enabled flag
     * \param _currentIdx New current history index
     * \param _historySize New history buffer size
     */
    void initHistory(const bool _filled, const size_t _currentIdx, const size_t _historySize);

    /*!
     * \brief Initialize history buffer
     * \param _list New history buffer
     * \param _add Count of empty steps to add
     */
    void initHistory(const std::list<TimeStampClass> &_list, const size_t _add = 0U);

    /*!
     * \brief Append new time-stamp data into history buffer
     * \param _timeDelta Step time duration
     * \details
     * Creates new time-stamp data from current data by moving it in time by given duration \a _timeDelta
     */
    void addStep(const T _timeDelta);

    std::pair<EventSourceResult, const TimeStampClass *>
    eventSource(const T _universeVelocity, const T _eventTimeStamp, const Math::Vec3<T> &_eventPosition) const;

    size_t
    offsetForEventSource(const T _universeVelocity, const T _eventTimeStamp, const Math::Vec3<T> &_eventPosition) const;

 protected:
    void cloneHistory(ObjectHistory<T, TimeStampClass> &other) const;

 public:
    /*!
     * \brief Fill output vector with object time-stamps and positions
     * \param _out Output vector
     * \returns \c true if success
     */
    bool loadPath(std::vector<std::pair<double, QVector3D>> &_out) const;

    /*!
     * \brief Getter for time-stamp data that is exactly at given time-stamp or before (needs to move forward time)
     * \param _timeStamp Time-stamp of required data
     * \returns Time-stamp data before or exactly at given \a _timeStamp
     * \note If given time-stamp is before oldest stored time-stamp, then oldest stored item is returned (needs
     *        to move backwards in time)
     */
    const TimeStampClass *dataAtTime(const T _timeStamp) const;

    /*!
     * \brief Getter for index of time-stamp data that is exactly at given time-stamp or before
     * \param _timeStamp Time-stamp of required data
     * \returns Index of time-stamp data in history, that is before or exactly at given \a _timeStamp
     */
    size_t indexAtTime(const T _timeStamp) const;

    /*!
     * \brief Getter for offset in history of time-stamp data that is exactly at given time-stamp or before
     * \param _timeStamp Time-stamp of required data
     * \returns Offset of time-stamp data in history, that is before or exactly at given \a _timeStamp
     */
    size_t offsetAtTime(const T _timeStamp) const;

    /*!
     * \brief Getter for object's position
     * \param _timeStamp Time-stamp of required position
     * \returns Pair, where \c first item is success flag, and \c second item is object's position (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadPosition(const T _timeStamp) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename TimeStampClass>
inline bool ObjectHistory<T, TimeStampClass>::filled() const
{
    return m_filled;
}

template <typename T, typename TimeStampClass>
inline size_t ObjectHistory<T, TimeStampClass>::currentIdx() const
{
    return m_currentIdx;
}

template <typename T, typename TimeStampClass>
inline size_t ObjectHistory<T, TimeStampClass>::ID() const
{
    return m_objectID;
}

template <typename T, typename TimeStampClass>
inline bool ObjectHistory<T, TimeStampClass>::initialized() const
{
    return !m_history.empty();
}

template <typename T, typename TimeStampClass>
inline const std::vector<TimeStampClass> &ObjectHistory<T, TimeStampClass>::history() const
{
    return m_history;
}

template <typename T, typename TimeStampClass>
inline std::vector<TimeStampClass> &ObjectHistory<T, TimeStampClass>::history()
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

template <typename T, typename TimeStampClass>
inline size_t ObjectHistory<T, TimeStampClass>::historyIdxByOffset(const size_t _offset) const
{
    if (_offset <= m_currentIdx)
        return m_currentIdx - _offset;

    if (!m_filled || _offset >= (m_history.size() - 1U))
        return m_history.size() + 1U;  // Returns out of range index

    return m_history.size() - _offset + m_currentIdx - 1U;
}

template <typename T, typename TimeStampClass>
inline const TimeStampClass *ObjectHistory<T, TimeStampClass>::historyTimeStampByOffset(const size_t _offset) const
{
    if (_offset <= m_currentIdx)
        return &m_history.at(m_currentIdx - _offset);

    if (!m_filled || _offset >= (m_history.size() - 1U))
        return nullptr;

    return &m_history.at(m_history.size() - _offset + m_currentIdx - 1U);
}

template <typename T, typename TimeStampClass>
inline size_t ObjectHistory<T, TimeStampClass>::historyStepCount() const
{
    if (m_history.empty())
        return 0U;
    if (!m_filled)
        return m_currentIdx;
    return m_history.size() - 1U;
}

template <typename T, typename TimeStampClass>
bool ObjectHistory<T, TimeStampClass>::isValidPath() const
{
    if (!initialized() || historyStepCount() < 2U)
        return false;

    if (!m_filled || m_currentIdx == m_history.size() - 1U)
        return isValidPathPart(0U, m_currentIdx - 1U);

    if (m_currentIdx == 0U)
        return isValidPathPart(m_currentIdx + 1U, m_history.size() - 1U);

    if (!TimeStampClass::compareMoved(m_history[m_history.size() - 1U], m_history[0U]))
        return false;

    if (m_currentIdx == 1U)
        return isValidPathPart(m_currentIdx + 1U, m_history.size() - 1U);

    return isValidPathPart(0U, m_currentIdx - 1U) && isValidPathPart(m_currentIdx + 1U, m_history.size() - 1U);
}

template <typename T, typename TimeStampClass>
bool ObjectHistory<T, TimeStampClass>::isValidPathPart(const size_t _firstIDX, const size_t _lastIDX) const
{
    if (_firstIDX > _lastIDX)
        return false;

    for (size_t i = _firstIDX; i < _lastIDX; ++i)
        if (!TimeStampClass::compareMoved(m_history[i], m_history[i + 1U]))
            return false;
    return true;
}

template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::initHistory(const size_t _size)
{
    m_filled = false;
    m_currentIdx = 0U;
    m_history.resize(_size < minimumHistorySize ? 0U : _size);
}

template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::initHistory(const bool _filled,
                                                   const size_t _currentIdx,
                                                   const size_t _historySize)
{
    m_filled = _filled;
    m_currentIdx = _currentIdx;
    m_history.resize(_historySize < minimumHistorySize ? 0U : _historySize);
}

template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::initHistory(const std::list<TimeStampClass> &_list, const size_t _add)
{
    m_filled = false;
    m_currentIdx = _list.empty() ? 0U : _list.size() - 1U;
    m_history.clear();
    m_history.reserve(_list.size() + _add);
    for (const TimeStampClass &ts : _list)
        m_history.push_back(ts);
}

template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::addStep(const T _timeDelta)
{
    const size_t hs = m_history.size();
    if (hs == 0U)
        return;
    const TimeStampClass &tmpCurrent = m_history[m_currentIdx];

    m_currentIdx++;
    if (m_currentIdx == hs)
    {
        m_currentIdx = 0U;
        m_filled = true;
    }
    m_history[m_currentIdx] = tmpCurrent.moved(_timeDelta);
}

#ifndef DOXYGEN_SKIP

/*!
 * \brief Macro check if time equals and possible exit with \c EventSourceFoundExact result
 * \param ATTR_TIME Variable to check
 * \param ATTR_OBJ Possible found result
 */
#define EVENT_SOURCE_CHECK_EXACT(ATTR_TIME, ATTR_OBJ)                                                                  \
    if (Type::equals<T>(ATTR_TIME, _eventTimeStamp))                                                                   \
        return                                                                                                         \
        {                                                                                                              \
            EventSourceFoundExact, ATTR_OBJ                                                                            \
        }

/*!
 * \brief Macro that setup and check absolute \b marked first and last (\c idxBefore and \c idxAfter) history items
 */
#define EVENT_SOURCE_FIRST_CHECK()                                                                                     \
    objBefore = &m_history.at(idxBefore);                                                                              \
    timeBefore = objBefore->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);                                \
    EVENT_SOURCE_CHECK_EXACT(timeBefore, objBefore);                                                                   \
    if (timeBefore < _eventTimeStamp)                                                                                  \
        return {EventSourceFoundFirst, objBefore};                                                                     \
                                                                                                                       \
    objAfter = &m_history.at(idxAfter);                                                                                \
    timeAfter = objAfter->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);                                  \
    EVENT_SOURCE_CHECK_EXACT(timeAfter, objAfter);                                                                     \
    if (timeAfter > _eventTimeStamp)                                                                                   \
        return                                                                                                         \
        {                                                                                                              \
            EventSourceMissing, objAfter                                                                               \
        }

#endif  // DOXYGEN_SKIP

/*!
 * \brief Find closest position in history, from where wave hits event
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \param _universeVelocity Speed of the Universe
 * \param _eventTimeStamp Time-stamp of event
 * \param _eventPosition Event location
 * \returns Pair of result type + closest time-stamp
 */
template <typename T, typename TimeStampClass>
std::pair<EventSourceResult, const TimeStampClass *> ObjectHistory<T, TimeStampClass>::eventSource(
    const T _universeVelocity, const T _eventTimeStamp, const Math::Vec3<T> &_eventPosition) const
{
    if (m_history.size() < 2U || (!m_filled && m_currentIdx == 0U))
        return {EventSourceEmptyPath, nullptr};

    const size_t idxLastHist = m_history.size() - 1U;

    const TimeStampClass *objBefore = nullptr;
    const TimeStampClass *objAfter = nullptr;

    size_t idxBefore;
    size_t idxAfter;

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
            const T timeBreak0 = objBreak0->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
            EVENT_SOURCE_CHECK_EXACT(timeBreak0, objBreak0);

            if (timeBreak0 < _eventTimeStamp)
            {
                idxAfter = 0U;
                objAfter = objBreak0;
                timeAfter = timeBreak0;
            }
            else
            {
                idxBefore = idxLastHist;
                objBefore = &m_history.at(idxBefore);
                timeBefore = objBefore->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
                EVENT_SOURCE_CHECK_EXACT(timeBefore, objBefore);
                if (timeBefore > _eventTimeStamp)
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
        const T timeDeltaBefore = timeBefore - _eventTimeStamp;
        const T timeDeltaAfter = _eventTimeStamp - timeAfter;
        const T timeDeltaSum = timeDeltaBefore + timeDeltaAfter;
        const T timeRatio = timeDeltaAfter / timeDeltaSum;
        const size_t idxRatio = static_cast<size_t>(static_cast<T>(idxRange) * timeRatio);
        const size_t idxMiddle = idxAfter + std::max(size_t(1U), idxRatio);

        const TimeStampClass *objMiddle = &m_history.at(idxMiddle);
        const T timeMiddle = objMiddle->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
        EVENT_SOURCE_CHECK_EXACT(timeMiddle, objMiddle);

        if (timeMiddle > _eventTimeStamp)
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

/*!
 * \brief Returns count of steps in history needed to be "before" given event
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \param _universeVelocity Speed of the Universe
 * \param _eventTimeStamp Time-stamp of event
 * \param _eventPosition Event location
 * \returns Count of steps in history needed to be "before" given event
 */
template <typename T, typename TimeStampClass>
size_t ObjectHistory<T, TimeStampClass>::offsetForEventSource(const T _universeVelocity,
                                                              const T _eventTimeStamp,
                                                              const Math::Vec3<T> &_eventPosition) const
{
    if (m_history.size() < 2U || (!m_filled && m_currentIdx == 0U))
        return 0U;

    const size_t idxLastHist = m_history.size() - 1U;
    const TimeStampClass *objBefore = nullptr;
    const TimeStampClass *objAfter = nullptr;

    size_t idxBefore;
    size_t idxAfter;
    T timeBefore;
    T timeAfter;
    bool isOffset = false;

    if (m_filled && m_currentIdx != idxLastHist)
    {
        if (m_currentIdx == 0U)
        {
            idxBefore = idxLastHist;
            objBefore = &m_history.at(idxBefore);
            timeBefore = objBefore->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
            if (Type::equals<T>(timeBefore, _eventTimeStamp) || timeBefore < _eventTimeStamp)
                return 1U;

            idxAfter = 1U;
            objAfter = &m_history.at(idxAfter);
            timeAfter = objAfter->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
            if (Type::equals<T>(timeAfter, _eventTimeStamp))
                return idxLastHist;

            if (timeAfter > _eventTimeStamp)
                return 0U;
        }
        else
        {
            idxBefore = m_currentIdx - 1U;
            objBefore = &m_history.at(idxBefore);
            timeBefore = objBefore->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
            if (Type::equals<T>(timeBefore, _eventTimeStamp) || timeBefore < _eventTimeStamp)
                return 1U;

            idxAfter = m_currentIdx + 1U;
            objAfter = &m_history.at(idxAfter);
            timeAfter = objAfter->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
            if (Type::equals<T>(timeAfter, _eventTimeStamp))
                return idxLastHist;

            if (timeAfter > _eventTimeStamp)
                return 0U;

            const TimeStampClass *objBreak0 = &m_history.at(0U);
            const T timeBreak0 = objBreak0->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
            if (Type::equals<T>(timeBreak0, _eventTimeStamp))
                return m_currentIdx;

            if (timeBreak0 < _eventTimeStamp)
            {
                idxAfter = 0U;
                objAfter = objBreak0;
                timeAfter = timeBreak0;
            }
            else
            {
                isOffset = true;
                idxBefore = idxLastHist;
                objBefore = &m_history.at(idxBefore);
                timeBefore = objBefore->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
                if (Type::equals<T>(timeBefore, _eventTimeStamp) || timeBefore > _eventTimeStamp)
                    return m_currentIdx + 1U;
            }
        }
    }
    else
    {
        idxBefore = m_currentIdx - 1U;
        idxAfter = 0U;

        objBefore = &m_history.at(idxBefore);
        timeBefore = objBefore->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
        if (Type::equals<T>(timeBefore, _eventTimeStamp) || timeBefore < _eventTimeStamp)
            return 1U;

        objAfter = &m_history.at(idxAfter);
        timeAfter = objAfter->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
        if (Type::equals<T>(timeAfter, _eventTimeStamp))
            return idxLastHist;

        if (timeAfter > _eventTimeStamp)
            return 0U;
    }

    size_t idxRange = idxBefore - idxAfter;

    while (idxRange > 1U)
    {
        const T timeDeltaBefore = timeBefore - _eventTimeStamp;
        const T timeDeltaAfter = _eventTimeStamp - timeAfter;
        const T timeDeltaSum = timeDeltaBefore + timeDeltaAfter;
        const T timeRatio = timeDeltaAfter / timeDeltaSum;
        const size_t idxRatio = static_cast<size_t>(static_cast<T>(idxRange) * timeRatio);
        const size_t idxMiddle = idxAfter + std::max(size_t(1U), idxRatio);

        const TimeStampClass *objMiddle = &m_history.at(idxMiddle);
        const T timeMiddle = objMiddle->getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
        if (Type::equals<T>(timeMiddle, _eventTimeStamp))
            return isOffset ? (m_currentIdx + m_history.size() - idxMiddle) : (m_currentIdx - idxMiddle);

        if (timeMiddle > _eventTimeStamp)
        {
            idxBefore = idxMiddle;
            timeBefore = timeMiddle;
        }
        else
        {
            idxAfter = idxMiddle;
            timeAfter = timeMiddle;
        }
        idxRange = idxBefore - idxAfter;
    }
    return isOffset ? (m_currentIdx + m_history.size() - idxAfter) : (m_currentIdx - idxAfter);
}

/*!
 * \brief Clone History
 * \tparam T Template floating point type
 * \tparam TimeStampClass \c TimeStamp class extension
 * \param other Other object to setup history
 */
template <typename T, typename TimeStampClass>
void ObjectHistory<T, TimeStampClass>::cloneHistory(ObjectHistory<T, TimeStampClass> &other) const
{
    other.m_filled = false;
    other.m_currentIdx = historyStepCount();

    size_t resIdx = other.m_currentIdx;
    size_t curIdx = m_currentIdx;

    while (true)
    {
        other.m_history[resIdx] = m_history[curIdx];
        if (resIdx == 0U)
            break;
        --resIdx;
        if (curIdx == 0U)
            curIdx = m_history.size() - 1U;
        else
            --curIdx;
    }
}

template <typename T, typename TimeStampClass>
bool ObjectHistory<T, TimeStampClass>::loadPath(std::vector<std::pair<double, QVector3D>> &_out) const
{
    if (m_history.empty())
        return false;

    if (m_filled)
    {
        _out.reserve(m_history.size());

        for (size_t i = m_currentIdx + 1U; i < m_history.size(); ++i)
            _out.push_back({m_history[i].timeStamp, m_history[i].position.toQVector3D()});

        for (size_t i = 0; i <= m_currentIdx; ++i)
            _out.push_back({m_history[i].timeStamp, m_history[i].position.toQVector3D()});
    }
    else
    {
        _out.reserve(m_currentIdx + 1U);
        for (size_t i = 0; i <= m_currentIdx; ++i)
            _out.push_back({m_history[i].timeStamp, m_history[i].position.toQVector3D()});
    }
    return true;
}

template <typename T, typename TimeStampClass>
const TimeStampClass *ObjectHistory<T, TimeStampClass>::dataAtTime(const T _timeStamp) const
{
    if (m_history.empty())
        return nullptr;

    if (Type::equals<T>(m_history[m_currentIdx].timeStamp, _timeStamp) ||
        m_history[m_currentIdx].timeStamp < _timeStamp || (!m_filled && m_currentIdx == 0U))
        return &m_history[m_currentIdx];

    const size_t idxLastHist = m_history.size() - 1U;
    size_t idxAfter;
    size_t idxBefore;
    if (m_filled && m_currentIdx != idxLastHist)
    {
        if (m_currentIdx == 0U)
        {
            idxAfter = 1U;
            idxBefore = idxLastHist;
            if (Type::equals<T>(m_history[idxBefore].timeStamp, _timeStamp) ||
                m_history[idxBefore].timeStamp < _timeStamp)
                return &m_history[idxBefore];
        }
        else
        {
            if (Type::equals<T>(m_history[0U].timeStamp, _timeStamp))
                return &m_history[0U];

            if (m_history[0U].timeStamp < _timeStamp)
            {
                idxAfter = 0U;
                idxBefore = m_currentIdx;
            }
            else
            {
                idxAfter = m_currentIdx + 1U;
                idxBefore = idxLastHist;
                if (Type::equals<T>(m_history[idxBefore].timeStamp, _timeStamp) ||
                    m_history[idxBefore].timeStamp < _timeStamp)
                    return &m_history[idxBefore];
            }
        }
    }
    else
    {
        idxAfter = 0U;
        idxBefore = m_currentIdx;
    }

    if (Type::equals<T>(m_history[idxAfter].timeStamp, _timeStamp) || m_history[idxAfter].timeStamp > _timeStamp)
        return &m_history[idxAfter];

    size_t idxRange = idxBefore - idxAfter;

    while (idxRange > 1U)
    {
        const T timeDeltaBefore = m_history[idxBefore].timeStamp - _timeStamp;
        const T timeDeltaAfter = _timeStamp - m_history[idxAfter].timeStamp;
        const T timeDeltaSum = timeDeltaBefore + timeDeltaAfter;
        const T timeRatio = timeDeltaAfter / timeDeltaSum;
        const size_t idxRatio = static_cast<size_t>(static_cast<T>(idxRange) * timeRatio);
        const size_t idxMiddle = idxAfter + std::max(size_t(1U), idxRatio);

        const T timeMiddle = m_history[idxMiddle].timeStamp - _timeStamp;
        if (Type::isNull<T>(timeMiddle))
            return &m_history[idxMiddle];

        if (timeMiddle > Const::T_0<T>())
            idxBefore = idxMiddle;
        else
            idxAfter = idxMiddle;
        idxRange = idxBefore - idxAfter;
    }
    return &m_history[idxAfter];
}

template <typename T, typename TimeStampClass>
size_t ObjectHistory<T, TimeStampClass>::indexAtTime(const T _timeStamp) const
{
    if (m_history.empty())
        return 0U;

    if (Type::equals<T>(m_history[m_currentIdx].timeStamp, _timeStamp) ||
        m_history[m_currentIdx].timeStamp < _timeStamp || (!m_filled && m_currentIdx == 0U))
        return m_currentIdx;

    const size_t idxLastHist = m_history.size() - 1U;
    size_t idxAfter;
    size_t idxBefore;
    if (m_filled && m_currentIdx != idxLastHist)
    {
        if (m_currentIdx == 0U)
        {
            idxAfter = 1U;
            idxBefore = idxLastHist;
            if (Type::equals<T>(m_history[idxBefore].timeStamp, _timeStamp) ||
                m_history[idxBefore].timeStamp < _timeStamp)
                return idxBefore;
        }
        else
        {
            if (Type::equals<T>(m_history[0U].timeStamp, _timeStamp))
                return 0U;

            if (m_history[0U].timeStamp < _timeStamp)
            {
                idxAfter = 0U;
                idxBefore = m_currentIdx;
            }
            else
            {
                idxAfter = m_currentIdx + 1U;
                idxBefore = idxLastHist;
                if (Type::equals<T>(m_history[idxBefore].timeStamp, _timeStamp) ||
                    m_history[idxBefore].timeStamp < _timeStamp)
                    return idxBefore;
            }
        }
    }
    else
    {
        idxAfter = 0U;
        idxBefore = m_currentIdx;
    }

    if (Type::equals<T>(m_history[idxAfter].timeStamp, _timeStamp) || m_history[idxAfter].timeStamp > _timeStamp)
        return idxAfter;

    size_t idxRange = idxBefore - idxAfter;

    while (idxRange > 1U)
    {
        const T timeDeltaBefore = m_history[idxBefore].timeStamp - _timeStamp;
        const T timeDeltaAfter = _timeStamp - m_history[idxAfter].timeStamp;
        const T timeDeltaSum = timeDeltaBefore + timeDeltaAfter;
        const T timeRatio = timeDeltaAfter / timeDeltaSum;
        const size_t idxRatio = static_cast<size_t>(static_cast<T>(idxRange) * timeRatio);
        const size_t idxMiddle = idxAfter + std::max(size_t(1U), idxRatio);

        const T timeMiddle = m_history[idxMiddle].timeStamp - _timeStamp;
        if (Type::isNull<T>(timeMiddle))
            return idxMiddle;

        if (timeMiddle > Const::T_0<T>())
            idxBefore = idxMiddle;
        else
            idxAfter = idxMiddle;
        idxRange = idxBefore - idxAfter;
    }
    return idxAfter;
}

template <typename T, typename TimeStampClass>
size_t ObjectHistory<T, TimeStampClass>::offsetAtTime(const T _timeStamp) const
{
    if (m_history.empty() || Type::equals<T>(m_history[m_currentIdx].timeStamp, _timeStamp) ||
        m_history[m_currentIdx].timeStamp < _timeStamp || (!m_filled && m_currentIdx == 0U))
        return 0U;

    size_t offsetBegin = 1U;
    size_t idxBegin = historyIdxByOffset(offsetBegin);
    if (Type::equals<T>(m_history[idxBegin].timeStamp, _timeStamp) || m_history[idxBegin].timeStamp < _timeStamp)
        return offsetBegin;

    size_t offsetEnd = historyStepCount();
    size_t idxEnd = historyIdxByOffset(offsetEnd);

    if (Type::equals<T>(m_history[idxEnd].timeStamp, _timeStamp))
        return offsetEnd;

    if (m_history[idxEnd].timeStamp > _timeStamp)
        return 0U;

    size_t offsetRange = offsetEnd - offsetBegin;

    while (offsetRange > 1U)
    {
        const T timeDeltaBegin = m_history[idxBegin].timeStamp - _timeStamp;
        const T timeDeltaEnd = _timeStamp - m_history[idxEnd].timeStamp;
        const T timeDeltaSum = timeDeltaBegin + timeDeltaEnd;
        const T timeRatio = timeDeltaBegin / timeDeltaSum;
        const size_t idxRatio = static_cast<size_t>(static_cast<T>(offsetRange) * timeRatio);
        const size_t offsetMiddle = offsetBegin + std::max(size_t(1U), idxRatio);
        const size_t idxMiddle = historyIdxByOffset(offsetMiddle);

        const T timeMiddle = m_history[idxMiddle].timeStamp - _timeStamp;
        if (Type::isNull<T>(timeMiddle))
            return offsetMiddle;

        if (timeMiddle > Const::T_0<T>())
        {
            offsetBegin = offsetMiddle;
            idxBegin = idxMiddle;
        }
        else
        {
            offsetEnd = offsetMiddle;
            idxEnd = idxMiddle;
        }
        offsetRange = offsetEnd - offsetBegin;
    }
    return offsetEnd;
}

template <typename T, typename TimeStampClass>
std::pair<bool, QVector3D> ObjectHistory<T, TimeStampClass>::loadPosition(const T _timeStamp) const
{
    const TimeStampClass *result = dataAtTime(_timeStamp);
    if (result == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;
    if (Type::isNull(timeDelta))
        return {true, result->position.toQVector3D()};

    return {true, result->moved(timeDelta).position.toQVector3D()};
}

}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_OBJECTHISTORY_H
