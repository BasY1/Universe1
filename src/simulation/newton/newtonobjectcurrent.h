/*!
 * \file simulation/newton/newtonobjectcurrent.h
 * \author Michal Steller
 * \brief Singularity object for \n classic newton based simulations template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTCURRENT_H
#define UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTCURRENT_H

#include "newtonobject.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

/*!
 * \brief Singularity object for \n classic newton based simulations
 * \tparam T Template floating point type
 * \note Gravitational force points from current object position to mate object position (current)
 */
template <typename T>
struct NewtonObjectCurrent : public NewtonObject<T>
{
    static const bool usesHistory = false;  //!< Does not use history

    static uint32_t testConstants(const Constants<T> &_physics);
    /*!
     * \brief Default constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     */

    inline NewtonObjectCurrent(const size_t _objectID, const T _mass)
        : NewtonObject<T>(_objectID, _mass)
    {
    }

    /*!
     * \brief Constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     * \param _size History buffer size
     */
    inline NewtonObjectCurrent(const size_t _objectID, const T _mass, const size_t _size)
        : NewtonObject<T>(_objectID, _mass, _size)
    {
    }

    bool initStep(const std::vector<NewtonObjectCurrent<T>> &_objects, const Constants<T> &_physics);

    /*!
     * \brief Create clone of this object with new ID and history size
     * \param _objectID New object ID
     * \param _size New object history size (if equals zero object keeps history size)
     * \returns Clone of this object
     */
    inline NewtonObjectCurrent<T> clone(const size_t _objectID, const size_t _size) const
    {
        NewtonObjectCurrent<T> result(_objectID,
                                      NewtonObject<T>::m_mass,
                                      std::max(_size, ObjectHistory<T, NewtonTimeStamp<T>>::m_history.size()));
        ObjectHistory<T, NewtonTimeStamp<T>>::cloneHistory(result);
        return result;
    }

    /*!
     * \brief Create copy of this object in different precision
     * \tparam T2  Other simulation template floating point type
     * \returns Copy of this object in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    NewtonObjectCurrent<T2> createCopy() const
    {
        NewtonObjectCurrent<T2> result(ObjectHistory<T, NewtonTimeStamp<T>>::m_objectID, NewtonObject<T>::m_mass);
        result.initHistory(ObjectHistory<T, NewtonTimeStamp<T>>::m_filled,
                           ObjectHistory<T, NewtonTimeStamp<T>>::m_currentIdx,
                           ObjectHistory<T, NewtonTimeStamp<T>>::m_history.size());
        for (size_t i = 0; i < result.history().size(); ++i)
        {
            result.history()[i].timeStamp = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].timeStamp;
            result.history()[i].position.x = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].position.x;
            result.history()[i].position.y = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].position.y;
            result.history()[i].position.z = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].position.z;
            result.history()[i].moveVelocity.x = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].moveVelocity.x;
            result.history()[i].moveVelocity.y = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].moveVelocity.y;
            result.history()[i].moveVelocity.z = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].moveVelocity.z;
            result.history()[i].moveAccel.x = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].moveAccel.x;
            result.history()[i].moveAccel.y = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].moveAccel.y;
            result.history()[i].moveAccel.z = ObjectHistory<T, NewtonTimeStamp<T>>::m_history[i].moveAccel.z;
        }
        return result;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test physics constants, returns \c true when gravitational constant has positive value
 * \tparam T Template floating point type
 * \param _physics Physics constants to test
 * \returns Zero when gravitational constant has positive value or error flags
 */
template <typename T>
uint32_t NewtonObjectCurrent<T>::testConstants(const Constants<T> &_physics)
{
    return Type::isPositive(_physics.gravityConstant) ? 0U : static_cast<uint32_t>(Const_UniverseVelocity);
}

/*!
 * \brief Calculate current move acceleration, force direction points to mate object's current position
 * \tparam T Template floating point type
 * \param _objects List of all simulated objects
 * \param _physics Physics constants
 * \returns Success flag
 */
template <typename T>
bool NewtonObjectCurrent<T>::initStep(const std::vector<NewtonObjectCurrent<T>> &_objects, const Constants<T> &_physics)
{
    NewtonTimeStamp<T> *cur = ObjectHistory<T, NewtonTimeStamp<T>>::current();
    Math::Vec3<T> accel;
    for (const NewtonObjectCurrent<T> &obj : _objects)
        if (obj.m_objectID != ObjectHistory<T, NewtonTimeStamp<T>>::m_objectID)
            accel +=
                NewtonObject<T>::getAccel(cur->position, obj.current()->position, obj.m_mass, _physics.gravityConstant);

    cur->moveAccel = accel;
    return true;
}

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTCURRENT_H
