/*!
 * \file simulation/newton/newtonobjectbywave.h
 * \author Michal Steller
 * \brief Singularity object for newton simulations with gravitational waves template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTBYWAVE_H
#define UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTBYWAVE_H

#include "newtonobject.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

/*!
 * \brief Singularity object for newton simulations with gravitational waves at speed of the universe
 * \tparam T Template floating point type
 * \note Gravitational force points from current object position to mate object position in history
 * (from where gravitational wave at speed of the universe hits current position)
 */
template <typename T>
struct NewtonObjectByWave : public NewtonObject<T>
{
    static const bool usesHistory = true;  //!< Using history

    static uint32_t testConstants(const Constants<T> &_physics);

    /*!
     * \brief Default constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     */

    inline NewtonObjectByWave(const size_t _objectID, const T _mass)
        : NewtonObject<T>(_objectID, _mass)
    {
    }

    /*!
     * \brief Constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     * \param _size History buffer size
     */
    inline NewtonObjectByWave(const size_t _objectID, const T _mass, const size_t _size)
        : NewtonObject<T>(_objectID, _mass, _size)
    {
    }

    void initStep(const std::vector<NewtonObjectByWave<T>> &_objects, const Constants<T> &_physics);

    /*!
     * \brief Create clone of this object with new ID and history size
     * \param _objectID New object ID
     * \param _size New object history size (if equals zero object keeps history size)
     * \returns Clone of this object
     */
    inline NewtonObjectByWave<T> clone(const size_t _objectID, const size_t _size) const
    {
        NewtonObjectByWave<T> result(_objectID,
                                     NewtonObject<T>::m_mass,
                                     std::max(_size, ObjectHistory<T, NewtonTimeStamp<T>>::m_history.size()));
        ObjectHistory<T, NewtonTimeStamp<T>>::cloneHistory(result);
        return result;
    }
};

/*!
 * \brief Test physics constants, returns \c true when gravitational constant and speed of the universe are positive
 * \tparam T Template floating point type
 * \param _physics Physics constants to test
 * \returns \c true when gravitational constant has positive value
 */
template <typename T>
uint32_t NewtonObjectByWave<T>::testConstants(const Constants<T> &_physics)
{
    return (Type::isPositive(_physics.universeVelocity) ? 0U : static_cast<uint32_t>(Const_UniverseVelocity)) |
        (Type::isPositive(_physics.gravityConstant) ? 0U : static_cast<uint32_t>(Const_GravityConstant));
}

/*!
 * \brief Calculate current move acceleration, force direction points to current object position
 * \tparam T Template floating point type
 * \param _objects List of all simulated objects
 * \param _physics Physics constants
 */
template <typename T>
void NewtonObjectByWave<T>::initStep(const std::vector<NewtonObjectByWave<T>> &_objects, const Constants<T> &_physics)
{
    NewtonTimeStamp<T> *cur = ObjectHistory<T, NewtonTimeStamp<T>>::current();
    Math::Vec3<T> accel;
    for (const NewtonObjectByWave<T> &obj : _objects)
        if (obj.m_objectID != ObjectHistory<T, NewtonTimeStamp<T>>::m_objectID)
        {
            const std::pair<EventSourceResult, const NewtonTimeStamp<T> *> source =
                obj.eventSource(_physics.universeVelocity, cur->timeStamp, cur->position);

            switch (source.first)
            {
            case EventSourceEmptyPath: break;

            case EventSourceFoundExact:
                accel += NewtonObject<T>::getAccel(
                    cur->position, source.second->position, obj.m_mass, _physics.gravityConstant);
                break;

            case EventSourceFoundClosest:
            case EventSourceFoundFirst:
            case EventSourceMissing:
                accel += NewtonObject<T>::getAccel(
                    cur->position,
                    source.second->movedToEventSource(_physics.universeVelocity, cur->timeStamp, cur->position)
                        .position,
                    obj.m_mass,
                    _physics.gravityConstant);
                break;
            }
        }
    cur->moveAccel = accel;
}

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTBYWAVE_H
