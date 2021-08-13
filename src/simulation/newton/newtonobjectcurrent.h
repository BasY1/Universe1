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

    void initStep(const std::vector<NewtonObjectCurrent<T>> &_objects, const Constants<T> &_physics);

    /*!
     * \brief Create clone of this object with new ID and history size
     * \param _objectID New object ID
     * \param _size New object history size (if equals zero object keeps history size)
     * \return Clone of this object
     */
    inline NewtonObjectCurrent<T> clone(const size_t _objectID, const size_t _size) const
    {
        NewtonObjectCurrent<T> result(_objectID,
                                      NewtonObject<T>::m_mass,
                                      std::max(_size, ObjectHistory<T, NewtonTimeStamp<T>>::m_history.size()));
        ObjectHistory<T, NewtonTimeStamp<T>>::cloneHistory(result);
        return result;
    }
};

/*!
 * \brief Test physics constants, returns \c true when gravitational constant has positive value
 * \tparam T Template floating point type
 * \param _physics Physics constants to test
 * \returns \c true when gravitational constant has positive value
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
 */
template <typename T>
void NewtonObjectCurrent<T>::initStep(const std::vector<NewtonObjectCurrent<T>> &_objects, const Constants<T> &_physics)
{
    NewtonTimeStamp<T> *cur = ObjectHistory<T, NewtonTimeStamp<T>>::current();
    Math::Vec3<T> accel;
    for (const NewtonObjectCurrent<T> &obj : _objects)
        if (obj.m_objectID != ObjectHistory<T, NewtonTimeStamp<T>>::m_objectID)
            accel +=
                NewtonObject<T>::getAccel(cur->position, obj.current()->position, obj.m_mass, _physics.gravityConstant);

    cur->moveAccel = accel;
}

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECTCURRENT_H
