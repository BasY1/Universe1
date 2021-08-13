/*!
 * \file simulation/simulation.h
 * \author Michal Steller
 * \brief Simulation base class template implementation
 */

#ifndef UNIVERSE1_SIMULATION_SIMULATION_H
#define UNIVERSE1_SIMULATION_SIMULATION_H

#include "objecthistory.h"
#include "simulationproperty.h"

namespace Universe1 {
namespace Simulation {

/*!
 * \brief The simulation class
 * \tparam T Template floating point type
 * \tparam ObjectClass \c ObjectHistory class extension
 * \tparam TimeStampClass \c TimeStamp class extension
 */
template <typename T, typename ObjectClass, typename TimeStampClass>
struct Simulation
{
 protected:
    Constants<T> m_physics;    //!< Universe physics constants
    T m_maximumStepTime;       //!< Maximum step time duration [s]
    T m_maximumCurveAngleRad;  //!< Maximum curve angle within step [rad]
    T m_startTime;             //!< Simulation start time (first calculated time-stamp) [s]
    size_t m_calculatedSteps;  //!< Calculated step count

    std::list<ObjectClass> m_initObjects;  //!< Object list for initialization phase
    std::vector<ObjectClass> m_objects;    //!< Object vector for calculation phase

 public:
    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value &&
                                        std::is_base_of<TimeStamp<T>, TimeStampClass>::value &&
                                        std::is_base_of<ObjectHistory<T, TimeStampClass>, ObjectClass>::value>>
    inline Simulation()
        : m_physics()
        , m_maximumStepTime(Const::T_001<T>())
        , m_maximumCurveAngleRad(Math::toRad(Const::T_1<T>()))
    {
    }

    /*!
     * \brief Default constructor
     * \param _maximumStepTime      Maximum step time duration
     * \param _maximumCurveAngleRad Maximum curve angle within step
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value &&
                                        std::is_base_of<TimeStamp<T>, TimeStampClass>::value &&
                                        std::is_base_of<ObjectHistory<T, TimeStampClass>, ObjectClass>::value>>
    inline Simulation(const T _maximumStepTime, const T _maximumCurveAngleRad)
        : m_physics()
        , m_maximumStepTime(_maximumStepTime)
        , m_maximumCurveAngleRad(_maximumCurveAngleRad)
    {
    }

    /*!
     * \brief Getter for universe physics constants
     * \returns Universe physics constants
     */
    inline const Constants<T> &physics() const;

    /*!
     * \brief Getter for maximum step time duration
     * \returns Maximum step time duration
     */
    inline T maximumStepTime() const;

    /*!
     * \brief Getter for maximum curve angle within step
     * \returns Maximum curve angle within step
     */
    inline T maximumCurveAngleRad() const;

    /*!
     * \brief Getter for simulation start time (time of first calculated time-stamp)
     * \returns Simulation start time
     */
    inline T startTime() const;

    /*!
     * \brief Getter for calculated step count
     * \returns Calculated step count
     */
    inline size_t calculatedSteps() const;

    /*!
     * \brief Getter for initialization object list
     * \returns Object list for initialization phase
     */
    inline std::list<ObjectClass> &initObjects();

    /*!
     * \brief Getter for initialization object list
     * \returns Object list for initialization phase
     */
    inline const std::list<ObjectClass> &initObjects() const;

    /*!
     * \brief Getter for calculation object vector
     * \returns Object vector for calculation phase
     */
    inline const std::vector<ObjectClass> &objects() const;

    /*!
     * \brief Setter for physics constants
     * \param _physics New physics constants values
     * \returns \c true if new physics constants values has valid values and we are using them
     */
    inline bool setPhysics(const Constants<T> &_physics);

    /*!
     * \brief Setter for maximum step time duration
     * \param _maximumStepTime New maximum step time duration value
     * \note Only positive values are accepted
     */
    inline void setMaximumStepTime(const T _maximumStepTime);

    /*!
     * \brief Setter for maximum curve angle within step
     * \param _maximumCurveAngleRad New maximum curve angle within step [rad]
     * \note Negative values or zero will disable test angle behavior
     */
    inline void setMaximumCurveAngleRad(const T _maximumCurveAngleRad);

    /*!
     * \brief Setter for maximum curve angle within step (degrees version)
     * \param _maximumCurveAngleDeg New maximum curve angle within step [deg]
     * \note Negative values or zero will disable test angle behavior
     */
    inline void setMaximumCurveAngleDeg(const T _maximumCurveAngleDeg);

    /*!
     * \brief Test is simulation can start
     * \returns \c 0 when no error occur or error flags
     * \sa Universe1::Simulation::SimulationProperty
     */
    uint32_t testStart() const;

    /*!
     * \brief Test if all objects are correctly initialized within \a m_initObjects list
     * \param _invalid Output list: Invalid object indexes (Index of invalid object in \a m_initObjects list, not the
     *                  object ID!)
     * \returns \c true if all object within \a m_initObjects are correctly initialized
     */
    bool testObjectsInitialized(std::list<size_t> *_invalid = nullptr) const;

    /*!
     * \brief Test if all objects histories are correctly continuous
     * \param _invalid Output list: Invalid object indexes (Index of invalid object in \a m_initObjects list, not the
     *                  object ID!)
     * \returns \c true if all object histories within \a m_initObjects are correctly continuous
     */
    bool testObjectsPath(std::list<size_t> *_invalid = nullptr) const;

    /*!
     * \brief Test if all objects current time is the same
     * \returns \c true if all objects current time is the same
     */
    bool testSameCurrentTime() const;

    /*!
     * \brief All objects histories are filled enough that their waves can reach all other objects
     * \param _invalid Output list: Pairs of invisible object (\a first is too short to reach \a second)
     *
     * \returns \c true if objects histories are filled enough
     */
    bool testHistoryVisibility(std::list<std::pair<size_t, size_t>> *_invalid = nullptr) const;

    /*!
     * \brief Initialize calculation
     * \param _objectHistorySize History size of calculation object
     *                           (if equals zero object keeps initialization history size)
     * \return \c true if initialization success \details Initialize vector of calculation objects \a m_objects
     * from initialization object list \a m_initObjects
     */
    bool initialize(const size_t _objectHistorySize = 0U);

    /*!
     * \brief Calculate next steps
     * \param _stepCount Step count
     * \return \c true if calculation success
     */
    bool addStep(const size_t _stepCount = 1U);
};

template <typename T, typename ObjectClass, typename TimeStampClass>
inline const Constants<T> &Simulation<T, ObjectClass, TimeStampClass>::physics() const
{
    return m_physics;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline T Simulation<T, ObjectClass, TimeStampClass>::maximumStepTime() const
{
    return m_maximumStepTime;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline T Simulation<T, ObjectClass, TimeStampClass>::maximumCurveAngleRad() const
{
    return m_maximumCurveAngleRad;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline T Simulation<T, ObjectClass, TimeStampClass>::startTime() const
{
    return m_startTime;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline size_t Simulation<T, ObjectClass, TimeStampClass>::calculatedSteps() const
{
    return m_calculatedSteps;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline std::list<ObjectClass> &Simulation<T, ObjectClass, TimeStampClass>::initObjects()
{
    return m_initObjects;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline const std::list<ObjectClass> &Simulation<T, ObjectClass, TimeStampClass>::initObjects() const
{
    return m_initObjects;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline const std::vector<ObjectClass> &Simulation<T, ObjectClass, TimeStampClass>::objects() const
{
    return m_objects;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline bool Simulation<T, ObjectClass, TimeStampClass>::setPhysics(const Constants<T> &_physics)
{
    const uint32_t result = ObjectClass::testConstants(_physics);
    if (result == 0U)
        m_physics = _physics;
    return result == 0U;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline void Simulation<T, ObjectClass, TimeStampClass>::setMaximumStepTime(const T _maximumStepTime)
{
    if (Type::isPositive<T>(_maximumStepTime))
        m_maximumStepTime = _maximumStepTime;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline void Simulation<T, ObjectClass, TimeStampClass>::setMaximumCurveAngleRad(const T _maximumCurveAngleRad)
{
    m_maximumCurveAngleRad = _maximumCurveAngleRad;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
inline void Simulation<T, ObjectClass, TimeStampClass>::setMaximumCurveAngleDeg(const T _maximumCurveAngleDeg)
{
    m_maximumCurveAngleRad = Math::toRad<T>(_maximumCurveAngleDeg);
}

template <typename T, typename ObjectClass, typename TimeStampClass>
uint32_t Simulation<T, ObjectClass, TimeStampClass>::testStart() const
{
    uint32_t result = ObjectClass::testConstants(m_physics);
    if (!Type::isPositive(m_maximumStepTime))
        result |= Property_MaximumStepTime;
    if (!testObjectsInitialized())
        result |= Validity_ObjectsInitialized;
    if (ObjectClass::usesHistory && !testObjectsPath())
        result |= Validity_ObjectsPath;
    if (!testSameCurrentTime())
        result |= Validity_SameCurrentTime;
    if (ObjectClass::usesHistory && !testHistoryVisibility())
        result |= Validity_HistoryVisibility;
    if (!m_objects.empty() && m_calculatedSteps > 0U)
        result |= Validity_Started;
    return result;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
bool Simulation<T, ObjectClass, TimeStampClass>::testObjectsInitialized(std::list<size_t> *_invalid) const
{
    if (_invalid != nullptr)
        _invalid->clear();

    if (m_initObjects.empty())
        return false;

    if (_invalid == nullptr)
    {
        for (const ObjectClass &obj : m_initObjects)
            if (!obj.initialized())
                return false;
        return true;
    }

    size_t idx = 0U;
    for (const ObjectClass &obj : m_initObjects)
    {
        if (!obj.initialized())
            _invalid->push_back(idx);
        ++idx;
    }

    return _invalid->empty();
}

template <typename T, typename ObjectClass, typename TimeStampClass>
bool Simulation<T, ObjectClass, TimeStampClass>::testObjectsPath(std::list<size_t> *_invalid) const
{
    if (_invalid != nullptr)
        _invalid->clear();

    if (m_initObjects.empty())
        return false;

    if (_invalid == nullptr)
    {
        for (const ObjectClass &obj : m_initObjects)
            if (obj.initialized() && !obj.isValidPath())
                return false;
        return true;
    }

    size_t idx = 0U;
    for (const ObjectClass &obj : m_initObjects)
    {
        if (obj.initialized() && !obj.isValidPath())
            _invalid->push_back(idx);
        ++idx;
    }

    return _invalid->empty();
}

template <typename T, typename ObjectClass, typename TimeStampClass>
bool Simulation<T, ObjectClass, TimeStampClass>::testSameCurrentTime() const
{
    if (m_initObjects.empty())
        return false;

    bool isInit = false;
    T curTime = Const::T_0<T>();
    for (const ObjectClass &obj : m_initObjects)
    {
        if (obj.initialized() && obj.isValidPath())
        {
            if (!isInit)
            {
                isInit = true;
                curTime = obj.current()->timeStamp;
            }
            else if (!Type::equals(obj.current()->timeStamp, curTime))
                return false;
        }
    }
    return true;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
bool Simulation<T, ObjectClass, TimeStampClass>::testHistoryVisibility(
    std::list<std::pair<size_t, size_t>> *_invalid) const
{
    if (_invalid != nullptr)
        _invalid->clear();

    size_t i = 0U;
    for (const ObjectClass &objI : m_initObjects)
    {
        if (objI.initialized())
        {
            const TimeStampClass *curI = objI.current();

            size_t j = 0U;
            for (const ObjectClass &objJ : m_initObjects)
            {
                if (i != j && objJ.initialized())
                {
                    const std::pair<EventSourceResult, const TimeStampClass *> es =
                        objJ.eventSource(m_physics.universeVelocity, curI->timeStamp, curI->position);

                    switch (es.first)
                    {
                    case EventSourceFoundExact:
                    case EventSourceFoundClosest:
                    case EventSourceFoundFirst: break;
                    case EventSourceEmptyPath:
                    case EventSourceMissing:
                        if (_invalid == nullptr)
                            return false;
                        _invalid->push_back({j, i});
                        break;
                    }
                }
                ++j;
            }
        }
        ++i;
    }

    return _invalid == nullptr || _invalid->empty();
}

template <typename T, typename ObjectClass, typename TimeStampClass>
bool Simulation<T, ObjectClass, TimeStampClass>::initialize(const size_t _objectHistorySize)
{
    if (m_initObjects.empty() || testStart() != 0U)
        return false;

    size_t idx = 1U;
    m_objects.clear();
    m_objects.reserve(m_initObjects.size());
    for (const ObjectClass &initObj : m_initObjects)
        m_objects.push_back(initObj.clone(idx++, _objectHistorySize));

    m_startTime = m_initObjects.back().current()->timeStamp;
    m_calculatedSteps = 0U;
    return true;
}

template <typename T, typename ObjectClass, typename TimeStampClass>
bool Simulation<T, ObjectClass, TimeStampClass>::addStep(const size_t _stepCount)
{
    if (m_objects.empty())
        return false;

    const bool useAngle = Type::isPositive<T>(m_maximumCurveAngleRad);
    const size_t stepCount = std::max(_stepCount, size_t(1U));

    for (size_t step = 0U; step < stepCount; ++step)
    {
        for (ObjectClass &obj : m_objects)
            obj.initStep(m_objects, m_physics);
        T stepDuration = m_maximumStepTime;
        if (useAngle)
        {
            for (const ObjectClass &obj : m_objects)
            {
                const T objDuration = obj.currentCurvingTimeDuration(m_maximumCurveAngleRad);
                if (Type::isNull<T>(objDuration))
                    return false;
                if (objDuration > Const::T_0<T>())
                {
                    if (stepDuration > objDuration)
                        stepDuration = objDuration;
                }
            }
        }

        for (ObjectClass &obj : m_objects)
            obj.addStep(stepDuration);
    }
    return true;
}

}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_SIMULATION_H
