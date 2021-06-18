/*!
 * \file math/singularity/singularitysimulation.h
 * \author Michal Steller
 * \brief Simulation of singularities template implementation
 */

#ifndef SINGULARITYSIMULATION_H
#define SINGULARITYSIMULATION_H

#include "singularityobject.h"

/*!
 * \brief Simulation of gravitation using massive singularity objects
 * \tparam T Template floating point type
 * \ingroup SingularityWithMass
 */
template <typename T>
class SingularitySimulation
{
 public:
    /*!
     * \brief Method for gravitation force calculation
     */
    enum Method
    {
        NewtonCurrent,  //!< Newton gravitation force method base on current object positions
        NewtonByWave,   //!< Newton gravitation force method base on history object positions
        // EinsteinCurrent,  // ! < Einstein gravitation force method base on current object positions
        // EinsteinByWave,   // ! < Einstein gravitation force method base on history object positions
    };

 protected:
    const Method m_method;       //!< Method for gravitation force calculation
    const T m_universeVelocity;  //!< Velocity of gravitation wave spreading within universe
    const T m_gravityConstant;   //!< Gravitational constant

    T m_maximumStepTime;       //!< Maximum step time duration
    T m_maximumCurveAngleRad;  //!< Maximum curve angle within step

    std::list<SingularityObject<T> *> m_data;  //!< Objects

 public:
    /*!
     * \brief Constructor
     * \param method Method for gravitation force calculation
     * \param maximumStepTime Maximum step time duration
     * \param maximumCurveAngleRad Maximum curve angle within step
     * \param universeVelocity Velocity of the universe
     * \param gravityConstant Gravitational constant
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    SingularitySimulation(const Method method,
                          const T maximumStepTime,
                          const T maximumCurveAngleRad,
                          const T universeVelocity = T_1<T>(),
                          const T gravityConstant = T_1<T>())
        : m_method(method)
        , m_universeVelocity(universeVelocity)
        , m_gravityConstant(gravityConstant)
        , m_maximumStepTime(maximumStepTime)
        , m_maximumCurveAngleRad(maximumCurveAngleRad)
    {
    }

    Method method() const;
    T universeVelocity() const;
    T gravityConstant() const;
    T maximumStepTime() const;
    T maximumCurveAngleRad() const;

    const std::list<SingularityObject<T> *> &data() const;

 protected:
    bool isValidConfig() const;
    bool isValidCurrentTime() const;
    bool isValidObjectsPath() const;
    bool isValidHistoryVisibility() const;

 public:
    bool isReadyToStart() const;

    inline void setMaximumStepTime(const T maximumStepTime);
    inline void setMaximumCurveAngleRad(const T maximumCurveAngleRad);

    void addObject(const SingularityObject<T> &object);

    T addStep(const size_t stepCount = 1U);

 protected:
    T getMaxCurveDuration(const Vec3<T> &velocity, const Vec3<T> &accel) const;
    T addStepNewtonCurrent();
    T addStepNewtonByWave();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for gravitation force calculation method
 * \tparam T Template floating point type
 * \returns Gravitation force calculation method
 */
template <typename T>
typename SingularitySimulation<T>::Method SingularitySimulation<T>::method() const
{
    return m_method;
}

/*!
 * \brief Getter for velocity of the universe
 * \tparam T Template floating point type
 * \returns Velocity of the universe
 */
template <typename T>
T SingularitySimulation<T>::universeVelocity() const
{
    return m_universeVelocity;
}

/*!
 * \brief Getter for gravitational constant
 * \tparam T Template floating point type
 * \returns Gravitational constant
 */
template <typename T>
T SingularitySimulation<T>::gravityConstant() const
{
    return m_gravityConstant;
}

/*!
 * \brief Getter for maximum step time duration
 * \tparam T Template floating point type
 * \returns Maximum step time duration
 */
template <typename T>
T SingularitySimulation<T>::maximumStepTime() const
{
    return m_maximumStepTime;
}

/*!
 * \brief Getter for maximum curve angle within step
 * \tparam T Template floating point type
 * \returns Maximum curve angle within step
 */
template <typename T>
T SingularitySimulation<T>::maximumCurveAngleRad() const
{
    return m_maximumCurveAngleRad;
}

/*!
 * \brief Getter for objects data
 * \tparam T Template floating point type
 * \returns Simulated objects list
 */
template <typename T>
const std::list<SingularityObject<T> *> &SingularitySimulation<T>::data() const
{
    return m_data;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if universe constants are positive values and objects list contains at least 2 objects
 * \tparam T Template floating point type
 * \returns \c true if constants are valid and objects list is filled
 */
template <typename T>
bool SingularitySimulation<T>::isValidConfig() const
{

    switch (m_method)
    {
    case NewtonCurrent: break;
    case NewtonByWave:
        if (!TypeIsPositive<T>(m_universeVelocity))
            return false;
        break;
    }
    if (!TypeIsPositive<T>(m_gravityConstant) || !TypeIsPositive<T>(m_maximumStepTime) ||
        !TypeIsPositive<T>(m_maximumCurveAngleRad) || m_data.size() < 2U)
        return false;

    typename std::list<SingularityObject<T> *>::const_iterator it = m_data.cbegin();
    for (; it != m_data.cend(); ++it)
        if (!(*it)->isValid())
            return false;

    return true;
}

/*!
 * \brief Test if current time is same for all objects
 * \tparam T Template floating point type
 * \returns \c true if current time is same for all objects
 */
template <typename T>
bool SingularitySimulation<T>::isValidCurrentTime() const
{
    if (m_data.size() < 2U)
        return false;

    typename std::list<SingularityObject<T> *>::const_iterator it = m_data.cbegin();
    const T curTime = (*it)->currentTime();
    ++it;

    for (; it != m_data.cend(); ++it)
        if (!TypeEquals<T>(curTime, (*it)->currentTime()))
            return false;

    return true;
}

/*!
 * \brief Test if current time is same for all objects
 * \tparam T Template floating point type
 * \returns \c true if current time is same for all objects
 */
template <typename T>
bool SingularitySimulation<T>::isValidObjectsPath() const
{
    typename std::list<SingularityObject<T> *>::const_iterator it = m_data.cbegin();
    for (; it != m_data.cend(); ++it)
        if (!(*it)->isValidPath())
            return false;
    return true;
}

/*!
 * \brief Test if all objects histories are filled enough that their gravitation waves can reach all other objects
 * \tparam T Template floating point type
 * \returns \c true when all objects histories are filled enough to reach all other objects
 */
template <typename T>
bool SingularitySimulation<T>::isValidHistoryVisibility() const
{

    typename std::list<SingularityObject<T> *>::const_iterator it1 = m_data.cbegin();
    for (; it1 != m_data.cend(); ++it1)
    {
        const size_t ID = (*it1)->ID();
        const SingularityObjectData<T> &obj1 = (*it1)->currentData();
        const T eventTime = obj1.timeStamp;
        const Vec3<T> eventPos = obj1.position;

        typename std::list<SingularityObject<T> *>::const_iterator it2 = m_data.cbegin();
        for (; it2 != m_data.cend(); ++it2)
            if ((*it2)->ID() != ID)
            {
                const T time2 = (*it2)->oldestData().getTimeWhenWaveHitEvent(m_universeVelocity, eventPos);
                if (!TypeEquals<T>(eventTime, time2) && eventTime < time2)
                    return false;
            }
    }

    return true;
}

/*!
 * \brief Test if simulation can start
 * \tparam T Template floating point type
 * \returns \c true when simulation can start
 */
template <typename T>
bool SingularitySimulation<T>::isReadyToStart() const
{
    if (!isValidConfig())
    {
        std::cerr << "Error: Invalid simulation setup !" << std::endl;
        return false;
    }

    if (!isValidCurrentTime())
    {
        std::cerr << "Error: Invalid objects current time-stamp !" << std::endl;
        return false;
    }

    switch (m_method)
    {
    case NewtonCurrent: break;
    case NewtonByWave:
        if (!isValidObjectsPath())
        {
            std::cerr << "Error: Invalid objects path !" << std::endl;
            return false;
        }

        if (!isValidHistoryVisibility())
        {
            std::cerr << "Error: Invalid objects history visibility !" << std::endl;
            return false;
        }

        break;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Setter for maximum step time duration
 * \tparam T Template floating point type
 * \param maximumStepTime Maximum step time duration
 */
template <typename T>
inline void SingularitySimulation<T>::setMaximumStepTime(const T maximumStepTime)
{
    m_maximumStepTime = maximumStepTime;
}

/*!
 * \brief Setter for maximum curve angle within step
 * \tparam T Template floating point type
 * \param maximumCurveAngleRad Maximum curve angle within step
 */
template <typename T>
inline void SingularitySimulation<T>::setMaximumCurveAngleRad(const T maximumCurveAngleRad)
{
    m_maximumCurveAngleRad = maximumCurveAngleRad;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Add new singularity object into simulation
 * \tparam T Template floating point type
 * \param object New singularity object
 */
template <typename T>
void SingularitySimulation<T>::addObject(const SingularityObject<T> &object)
{
    m_data.push_back(new SingularityObject<T>(m_data.size(), object));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns maximum step duration for objects movement components
 * \param velocity Object velocity
 * \param accel Object acceleration
 * \return Maximum step duration for objects movement components
 */
template <typename T>
T SingularitySimulation<T>::getMaxCurveDuration(const Vec3<T> &velocity, const Vec3<T> &accel) const
{
    if (velocity.isNull() || accel.isNull())
        return m_maximumStepTime;

    const Vec3<T> sideAccel = accel - accel.projected(velocity);

    if (sideAccel.isNull())
        return m_maximumStepTime;

    return std::min(m_maximumCurveAngleRad * T_2<T>() * velocity.length() / sideAccel.length(), m_maximumStepTime);
}

/*!
 * \brief Calculates next simulation step
 * \tparam T Template floating point type
 * \param stepCount Step count to
 * \returns Total time duration of created steps
 */
template <typename T>
T SingularitySimulation<T>::addStep(const size_t stepCount)
{
    const T resultTime = T_0<T>();
    switch (m_method)
    {
    case NewtonCurrent:
        for (size_t step = 0U; step < stepCount; ++step)
            resultTime += addStepNewtonCurrent();
        break;

    case NewtonByWave:
        for (size_t step = 0U; step < stepCount; ++step)
            resultTime += addStepNewtonByWave();
        break;
    }
    return resultTime;
}

/*!
 * \brief Calculates next simulation step using <b>Newton - current</b> method
 * \tparam T Template floating point type
 * \returns Total time duration of created step
 */
template <typename T>
T SingularitySimulation<T>::addStepNewtonCurrent()
{
    T resultStepDuration = m_maximumStepTime;

    typename std::list<SingularityObject<T> *>::const_iterator it1 = m_data.cbegin();
    for (; it1 != m_data.cend(); ++it1)
    {
        Vec3<T> accel;

        const size_t ID = (*it1)->ID();
        const SingularityObjectData<T> &data1 = (*it1)->currentData();
        const Vec3<T> &pos1 = data1.position;

        typename std::list<SingularityObject<T> *>::const_iterator it2 = m_data.cbegin();
        for (; it2 != m_data.cend(); ++it2)
            if ((*it2)->ID() != ID)
                accel += m_gravityConstant * (*it2)->mass() / (pos1 - (*it2)->currentData().position).lengthSquared();

        (*it1)->setCurrentAccel(accel);

        const T curveTime = getMaxCurveDuration(data1.moveVelocity, accel);

        if (resultStepDuration > curveTime)
            resultStepDuration = curveTime;
    }

    for (it1 = m_data.cbegin(); it1 != m_data.cend(); ++it1)
        (*it1)->addStep(resultStepDuration);

    return resultStepDuration;
}

/*!
 * \brief Calculates next simulation step using <b>Newton - by wave</b> method
 * \tparam T Template floating point type
 * \returns Total time duration of created step
 */
template <typename T>
T SingularitySimulation<T>::addStepNewtonByWave()
{
    T resultStepDuration = m_maximumStepTime;

    typename std::list<SingularityObject<T> *>::const_iterator it1 = m_data.cbegin();
    for (; it1 != m_data.cend(); ++it1)
    {
        Vec3<T> accel;

        const size_t ID = (*it1)->ID();
        const SingularityObjectData<T> &data1 = (*it1)->currentData();
        const Vec3<T> &pos1 = data1.position;
        const T time1 = data1.timeStamp;

        typename std::list<SingularityObject<T> *>::const_iterator it2 = m_data.cbegin();
        for (; it2 != m_data.cend(); ++it2)
            if ((*it2)->ID() != ID)
                accel += m_gravityConstant * (*it2)->mass() /
                    (pos1 - (*it2)->getSource(m_universeVelocity, time1, pos1).position).lengthSquared();

        (*it1)->setCurrentAccel(accel);

        resultStepDuration = std::min(resultStepDuration, getMaxCurveDuration(data1.moveVelocity, accel));
    }

    for (it1 = m_data.cbegin(); it1 != m_data.cend(); ++it1)
        (*it1)->addStep(resultStepDuration);

    return resultStepDuration;
}

#endif  // SINGULARITYSIMULATION_H
