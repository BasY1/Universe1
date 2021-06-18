/*!
 * \file math/singularity/singularityobject.h
 * \author Michal Steller
 * \brief Singularity object template implementation
 */

#ifndef SINGULARITYOBJECT_H
#define SINGULARITYOBJECT_H

#include "singularityobjectdata.h"

/*!
 * \brief Massive singularity object with history path data
 * \tparam T Template floating point type
 * \ingroup SingularityWithMass
 */
template <typename T>
class SingularityObject
{
 protected:
    const size_t m_objectID;                          //!< Object's ID
    const T m_mass;                                   //!< Object's mass [kg]
    bool m_filled;                                    //!< History filled / looping enabled flag
    size_t m_currentIdx;                              //!< Index of current object data in history buffer
    std::vector<SingularityObjectData<T>> m_history;  //!< History object data buffer

 public:
    /*!
     * \brief Constructor
     * \param ID Object's ID
     * \param historySize Object's history buffer size
     * \param mass Object's mass [kg]
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline SingularityObject(const size_t ID, const size_t historySize, const T mass)
        : m_objectID(ID)
        , m_mass(mass)
        , m_filled(false)
        , m_currentIdx(0U)
    {
        m_history.resize(historySize);
    }

    SingularityObject(const size_t ID,
                      const size_t historySize,
                      const T mass,
                      const SingularityObjectData<T> &initData);

    SingularityObject(const size_t ID,
                      const size_t historySize,
                      const T mass,
                      const std::vector<SingularityObjectData<T>> &initPath);

    SingularityObject(const size_t ID, const SingularityObject<T> &other);

    inline size_t ID() const;
    inline T mass() const;
    inline bool isFilled() const;
    inline size_t currentIdx() const;
    inline size_t historySize() const;
    inline size_t usedSize() const;

    inline const std::vector<SingularityObjectData<T>> &history() const;

    inline const SingularityObjectData<T> &currentData() const;
    const SingularityObjectData<T> &oldestData() const;

    inline T currentTime() const;

    bool isValid() const;
    bool isValidPath() const;

    inline void setCurrentAccel(const Vec3<T> &accel);

    void addStep(const T timeDelta);

    SingularityObjectData<T>
    getSource(const T universeVelocity, const T eventTimeStamp, const Vec3<T> &eventPosition) const;

 protected:
    SingularityObjectData<T> getSourceInRange(const size_t maxIdx,
                                              const size_t minIdx,
                                              const T universeVelocity,
                                              const T eventTimeStamp,
                                              const Vec3<T> &eventPosition) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \tparam T Template floating point type
 * \param ID Object's ID
 * \param historySize Object's history buffer size
 * \param mass Object's mass [kg]
 * \param initData Initial data
 */
template <typename T>
SingularityObject<T>::SingularityObject(const size_t ID,
                                        const size_t historySize,
                                        const T mass,
                                        const SingularityObjectData<T> &initData)
    : SingularityObject(ID, historySize, mass)
{
    if (historySize > 0U)
        m_history[m_currentIdx] = initData;
}

/*!
 * \brief Constructor
 * \tparam T Template floating point type
 * \param ID Object's ID
 * \param historySize Object's history buffer size
 * \param mass Object's mass [kg]
 * \param initPath Initial path
 */
template <typename T>
SingularityObject<T>::SingularityObject(const size_t ID,
                                        const size_t historySize,
                                        const T mass,
                                        const std::vector<SingularityObjectData<T>> &initPath)
    : SingularityObject(ID, historySize, mass)
{
    if (!initPath.empty() && historySize > 0U)
    {
        if (initPath.size() <= historySize)
        {
            for (size_t i = 0U; i < initPath.size(); ++i)
                m_history[i] = initPath[i];
            m_currentIdx = initPath.size() - 1U;
        }
        else
        {
            const size_t offset = initPath.size() - historySize;
            for (size_t i = 0U; i < historySize; ++i)
                m_history[i] = initPath[i + offset];

            m_currentIdx = historySize - 1U;
        }
    }
}

/*!
 * \brief Constructor
 * \tparam T Template floating point type
 * \param ID Object's ID
 * \param other Other object with values
 */
template <typename T>
SingularityObject<T>::SingularityObject(const size_t ID, const SingularityObject<T> &other)
    : m_objectID(ID)
    , m_mass(other.m_mass)
    , m_filled(other.m_filled)
    , m_currentIdx(other.m_currentIdx)
{
    m_history.resize(other.m_history.size());
    for (size_t i = 0U; i < other.m_history.size(); ++i)
        m_history[i] = other.m_history[i];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Object ID getter
 * \tparam T Template floating point type
 * \return Object ID
 */
template <typename T>
inline size_t SingularityObject<T>::ID() const
{
    return m_objectID;
}

/*!
 * \brief Object mass getter
 * \tparam T Template floating point type
 * \return Object mass
 */
template <typename T>
inline T SingularityObject<T>::mass() const
{
    return m_mass;
}

/*!
 * \brief Object history fully filled flag
 * \tparam T Template floating point type
 * \return History filled flag
 */
template <typename T>
inline bool SingularityObject<T>::isFilled() const
{
    return m_filled;
}

/*!
 * \brief Getter for index of current (latest) data in history
 * \tparam T Template floating point type
 * \return Index of current data in history
 */
template <typename T>
inline size_t SingularityObject<T>::currentIdx() const
{
    return m_currentIdx;
}

/*!
 * \brief Returns history size
 * \tparam T Template floating point type
 * \return History size
 */
template <typename T>
inline size_t SingularityObject<T>::historySize() const
{
    return m_history.size();
}

/*!
 * \brief Returns used history size
 * \tparam T Template floating point type
 * \return Used history size
 */
template <typename T>
inline size_t SingularityObject<T>::usedSize() const
{
    return m_filled ? m_history.size() : (m_currentIdx + 1U);
}

/*!
 * \brief Object history getter
 * \tparam T Template floating point type
 * \return Object history
 */
template <typename T>
const std::vector<SingularityObjectData<T>> &SingularityObject<T>::history() const
{
    return m_history;
}

/*!
 * \brief Getter for current (latest) data in history
 * \tparam T Template floating point type
 * \return Current data in history
 */
template <typename T>
inline const SingularityObjectData<T> &SingularityObject<T>::currentData() const
{
    return m_history.at(m_currentIdx);
}

/*!
 * \brief Getter for oldest data in history
 * \tparam T Template floating point type
 * \return Oldest data in history
 * \note Oldest history data contains lowest time-stamp
 */
template <typename T>
const SingularityObjectData<T> &SingularityObject<T>::oldestData() const
{
    if (m_filled && m_currentIdx != historySize() - 1U)
        return m_history.at(m_currentIdx + 1U);

    return m_history.at(0U);
}

/*!
 * \brief Getter for current (latest) time-stamp in history
 * \tparam T Template floating point type
 * \return Current time-stamp in history
 */
template <typename T>
inline T SingularityObject<T>::currentTime() const
{
    return m_history.at(m_currentIdx).timeStamp;
}

/*!
 * \brief Test if object is valid
 * \tparam T Template floating point type
 * \return \c true when object is valid
 */
template <typename T>
bool SingularityObject<T>::isValid() const
{
    return TypeIsPositive<T>(m_mass) && m_history.size() > 2U && (m_filled || m_currentIdx > 1U);
}

/*!
 * \brief Test if objects history path is valid (data are continuous)
 * \tparam T Template floating point type
 * \return \c true when objects history path is valid
 */
template <typename T>
bool SingularityObject<T>::isValidPath() const
{
    for (size_t iBefore = 0U, iAfter = 1U; iBefore < m_currentIdx; ++iBefore, ++iAfter)
    {
        const SingularityObjectData<T> &objBefore = m_history.at(iBefore);
        const SingularityObjectData<T> &objAfrer = m_history.at(iAfter);
        const SingularityObjectData<T> objBeforeMoved = objBefore.atTime(objAfrer.timeStamp);
        if (objBeforeMoved.position != objAfrer.position || objBeforeMoved.moveVelocity != objAfrer.moveVelocity)
            return false;
    }

    if (m_filled)
    {
        {
            const SingularityObjectData<T> &objBefore = m_history.at(historySize() - 1U);
            const SingularityObjectData<T> &objAfrer = m_history.at(0U);
            const SingularityObjectData<T> objBeforeMoved = objBefore.atTime(objAfrer.timeStamp);
            if (objBeforeMoved.position != objAfrer.position || objBeforeMoved.moveVelocity != objAfrer.moveVelocity)
                return false;
        }

        for (size_t iBefore = m_currentIdx + 1U, iAfter = m_currentIdx + 2U; iBefore < historySize() - 1U;
             ++iBefore, ++iAfter)
        {
            const SingularityObjectData<T> &objBefore = m_history.at(iBefore);
            const SingularityObjectData<T> &objAfrer = m_history.at(iAfter);
            const SingularityObjectData<T> objBeforeMoved = objBefore.atTime(objAfrer.timeStamp);
            if (objBeforeMoved.position != objAfrer.position || objBeforeMoved.moveVelocity != objAfrer.moveVelocity)
                return false;
        }
    }

    return m_history.size() > 2U && (m_filled || m_currentIdx > 1U);
}

/*!
 * \brief Setter for acceleration for current data in history
 * \tparam T Template floating point type
 * \param accel Acceleration of current
 */
template <typename T>
void SingularityObject<T>::setCurrentAccel(const Vec3<T> &accel)
{
    m_history.at(m_currentIdx).moveAccel = accel;
}

/*!
 * \brief Add next step into history
 * \param timeDelta Step time duration
 * \details
 * New object's time-stamp data is created by moving current position and is placed on next index in history.
 * New current index will be setup to our next index.
 * If history is filled (next index = history size), then \b filled flag is enabled and next index falls back to zero.
 * From this moment next step will always overwrite oldest data in history.
 */
template <typename T>
void SingularityObject<T>::addStep(const T timeDelta)
{
    size_t nextIdx = m_currentIdx + 1U;

    if (nextIdx == m_history.size())
    {
        m_filled = true;
        nextIdx = 0U;
    }

    m_history.at(nextIdx) = m_history.at(m_currentIdx).moved(timeDelta);
    m_currentIdx = nextIdx;
}

/*!
 * \brief Returns time-stamp data in history path from where gravitation wave hits event
 * \tparam T Template floating point type
 * \param universeVelocity Speed of the Universe
 * \param eventTimeStamp Time-stamp of event
 * \param eventPosition Event location
 * \returns Data in history path from where gravitation wave hits event
 */
template <typename T>
SingularityObjectData<T>
SingularityObject<T>::getSource(const T universeVelocity, const T eventTimeStamp, const Vec3<T> &eventPosition) const
{
    if (m_filled)
    {
        if (m_currentIdx == 0U)
            return getSourceInRange(m_history.size() - 1U, 1U, universeVelocity, eventTimeStamp, eventPosition);

        const SingularityObjectData<T> &obj1 = m_history.at(m_currentIdx - 1U);
        const T time1 = obj1.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);

        if (TypeEquals<T>(time1, eventTimeStamp))
            return SingularityObjectData<T>(obj1);
        else if (time1 < eventTimeStamp)
            return obj1.getSource(universeVelocity, eventTimeStamp, eventPosition);

        const SingularityObjectData<T> &obj2 = m_history.at(0U);
        const T time2 = obj2.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);
        if (TypeEquals<T>(time2, eventTimeStamp))
            return SingularityObjectData<T>(obj2);
        else if (time2 < eventTimeStamp)
            return getSourceInRange(m_currentIdx - 1U, 0U, universeVelocity, eventTimeStamp, eventPosition);

        return getSourceInRange(
            m_history.size() - 1U, m_currentIdx + 1U, universeVelocity, eventTimeStamp, eventPosition);
    }
    else
    {
        return (m_currentIdx == 0U)
            ? SingularityObjectData<T>()
            : getSourceInRange(m_currentIdx - 1U, 0U, universeVelocity, eventTimeStamp, eventPosition);
    }
}

/*!
 * \brief Returns time-stamp data in history path (defined by range) from where gravitation wave hits event
 * \tparam T Template floating point type
 * \param maxIdx Maximum index in history where to search
 * \param minIdx Minimum index in history where to search
 * \param universeVelocity Speed of the Universe
 * \param eventTimeStamp Time-stamp of event
 * \param eventPosition Event location
 * \returns Data in history path from where gravitation wave hits event
 */
template <typename T>
SingularityObjectData<T> SingularityObject<T>::getSourceInRange(const size_t maxIdx,
                                                                const size_t minIdx,
                                                                const T universeVelocity,
                                                                const T eventTimeStamp,
                                                                const Vec3<T> &eventPosition) const
{
    size_t idxTop = maxIdx;
    const SingularityObjectData<T> &objTop = m_history.at(idxTop);
    T timeTop = objTop.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);

    if (TypeEquals<T>(timeTop, eventTimeStamp))
        return SingularityObjectData<T>(objTop);
    else if (timeTop < eventTimeStamp)
        return objTop.getSource(universeVelocity, eventTimeStamp, eventPosition);

    size_t idxBottom = minIdx;
    const SingularityObjectData<T> &objBottom = m_history.at(idxBottom);
    T timeBottom = objBottom.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);

    if (TypeEquals<T>(timeBottom, eventTimeStamp))
        return SingularityObjectData<T>(objBottom);
    else if (timeBottom > eventTimeStamp)
        return objBottom.getSource(universeVelocity, eventTimeStamp, eventPosition);

    T timeDiffTop = eventTimeStamp - timeTop;
    T timeDiffBottom = eventTimeStamp - timeBottom;

    while (idxTop != (idxBottom + 1U))
    {
        size_t idxMid = idxTop -
            static_cast<size_t>(static_cast<T>(idxTop - idxBottom) * timeDiffTop / (timeDiffTop - timeDiffBottom));

        if (idxMid == idxTop)
            --idxMid;
        else if (idxMid == idxBottom)
            ++idxMid;

        const SingularityObjectData<T> &objMid = m_history.at(idxMid);
        T timeMid = objMid.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);

        if (TypeEquals<T>(timeMid, eventTimeStamp))
        {
            return SingularityObjectData<T>(objMid);
        }
        else if (timeMid < eventTimeStamp)
        {
            idxBottom = idxMid;
            timeDiffBottom = (eventTimeStamp - timeMid);
        }
        else
        {
            idxTop = idxMid;
            timeDiffTop = (eventTimeStamp - timeMid);
        }
    }

    return m_history.at(idxBottom).getSource(universeVelocity, eventTimeStamp, eventPosition);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param os Output text stream
 * \param obj Singularity object
 * \returns Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const SingularityObject<T> &obj)
{
    return os << '[' << obj.currentData() << "M[" << obj.mass() << "],H[" << obj.usedSize() << '/' << obj.historySize()
              << "],I[" << obj.currentIdx() << "]]";
}

#endif  // SINGULARITYOBJECT_H
