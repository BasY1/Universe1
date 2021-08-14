/*!
 * \file simulation/newton/newtonsimulation.h
 * \author Michal Steller
 * \brief Newton based simulations template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONSIMULATION_H
#define UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONSIMULATION_H

#include "newtonobjectbywave.h"
#include "newtonobjectcurrent.h"

#include "../simulation.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

/*!
 * \brief Simulation processor for \n classic newton based simulations
 * \tparam T Template floating point type
 */
template <typename T, typename ObjectClass>
struct SimulationNewton : public Universe1::Simulation::Simulation<T, ObjectClass, NewtonTimeStamp<T>>
{
    /*!
     * \brief Constructor
     */
    template <typename = std::enable_if<std::is_base_of<NewtonObject<T>, ObjectClass>::value>>
    inline SimulationNewton()
        : Universe1::Simulation::Simulation<T, ObjectClass, NewtonTimeStamp<T>>()
    {
    }

    /*!
     * \brief Getter for initialization object's velocity
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is initialization object's velocity
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadInitVelocity(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for calculation object's velocity
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is calculation object's velocity
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadCalcVelocity(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for initialization object's acceleration
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is initialization object's acceleration
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadInitAccel(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for calculation object's acceleration
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is calculation object's acceleration
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadCalcAccel(const size_t _objectID, const double _timeStamp) const;
};

template <typename T, typename ObjectClass>
std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadInitVelocity(const size_t _objectID,
                                                                              const double _timeStamp) const
{
    const ObjectClass *foundObj = nullptr;
    for (const ObjectClass &obj : Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects)
    {
        if (obj.ID() == _objectID)
        {
            if (foundObj == nullptr)
                foundObj = &obj;
            else
                return {false, QVector3D()};
        }
    }
    if (foundObj == nullptr)
        return {false, QVector3D()};
    return foundObj->loadVelocity(_timeStamp);
}

template <typename T, typename ObjectClass>
std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadCalcVelocity(const size_t _objectID,
                                                                              const double _timeStamp) const
{
    if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.size())
        return {false, QVector3D()};
    return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.at(_objectID).loadVelocity(_timeStamp);
}

template <typename T, typename ObjectClass>
std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadInitAccel(const size_t _objectID,
                                                                           const double _timeStamp) const
{
    const ObjectClass *foundObj = nullptr;
    for (const ObjectClass &obj : Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects)
    {
        if (obj.ID() == _objectID)
        {
            if (foundObj == nullptr)
                foundObj = &obj;
            else
                return {false, QVector3D()};
        }
    }
    if (foundObj == nullptr)
        return {false, QVector3D()};
    return foundObj->loadAccel(_timeStamp);
}

template <typename T, typename ObjectClass>
std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadCalcAccel(const size_t _objectID,
                                                                           const double _timeStamp) const
{
    if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.size())
        return {false, QVector3D()};
    return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.at(_objectID).loadAccel(_timeStamp);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Simulation processor for \n classic newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct SimulationNewtonCurrent : public SimulationNewton<T, NewtonObjectCurrent<T>>
{
    /*!
     * \brief Constructor
     */
    inline SimulationNewtonCurrent()
        : SimulationNewton<T, NewtonObjectCurrent<T>>()
    {
    }

    /*!
     * \brief Prepare initialization object list \a m_initObjects from given collection
     * \param _objects Objects start time-stamp data (Tuple of \b mass scalar, \b position and \b velocity vectors)
     * \note Initialized objects will have minimum history size
     * \sa Universe1::Simulation::ObjectHistory::minimumHistorySize
     */
    void initializeObjects(std::vector<std::tuple<T, Math::Vec3<T>, Math::Vec3<T>>> &_objects);
};

template <typename T>
void SimulationNewtonCurrent<T>::initializeObjects(std::vector<std::tuple<T, Math::Vec3<T>, Math::Vec3<T>>> &_objects)
{
    Universe1::Simulation::Simulation<T, NewtonObjectCurrent<T>, NewtonTimeStamp<T>>::clear();
    size_t idx = 0U;

    for (const std::tuple<T, Math::Vec3<T>, Math::Vec3<T>> obj : _objects)
    {
        Universe1::Simulation::Simulation<T, NewtonObjectCurrent<T>, NewtonTimeStamp<T>>::m_initObjects.push_back(
            NewtonObjectCurrent<T>(idx++, std::get<0>(obj), 3U));

        NewtonTimeStamp<T> *cur =
            Universe1::Simulation::Simulation<T, NewtonObjectCurrent<T>, NewtonTimeStamp<T>>::m_initObjects.back()
                .current();
        cur->position = std::get<1>(obj);
        cur->moveVelocity = std::get<2>(obj);
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Simulation processor for \n newton based simulations with gravitational waves at speed of the universe
 * \tparam T Template floating point type
 */
template <typename T>
struct SimulationNewtonByWave : public SimulationNewton<T, NewtonObjectByWave<T>>
{
    /*!
     * \brief Constructor
     */
    inline SimulationNewtonByWave()
        : SimulationNewton<T, NewtonObjectByWave<T>>()
    {
    }
};

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONSIMULATION_H
