/*!
 * \file simulation/newton/newtonobject.h
 * \author Michal Steller
 * \brief Object history base template implementation
 */

#ifndef NEWTONOBJECT_H
#define NEWTONOBJECT_H

#include "newtontimestamp.h"

#include "../objecthistory.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

// template <typename T>
// struct NewtonSimulation;

/*!
 * \brief Base class for singularity object for newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct NewtonObject : public ObjectHistory<T, NewtonTimeStamp<T>>
{
 protected:
    // friend struct NewtonSimulation<T>;

    const T m_mass;  //!< Object's mass [kg]

    /*!
     * \brief Default constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     */
    inline NewtonObject(const size_t _objectID, const T _mass)
        : ObjectHistory<T, NewtonTimeStamp<T>>(_objectID)
        , m_mass(_mass)
    {
    }

    /*!
     * \brief Constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     * \param _size History buffer size
     */
    inline NewtonObject(const size_t _objectID, const T _mass, const size_t _size)
        : ObjectHistory<T, NewtonTimeStamp<T>>(_objectID, _size)
        , m_mass(_mass)
    {
    }

 public:
    /*!
     * \brief Getter for object's mass
     * \returns Object's mass
     */
    inline T mass() const;

    /*!
     * \brief Returns time duration that is needed to curve (turn) move direction by given angle
     * \param _angleRad Curving angle on radians
     * \returns Angle between current move direction and direction after given time duration
     * \sa Universe1::Simulation::GravityNewton::NewtonTimeStamp::curvingTimeDuration(const T) const
     */
    inline T currentCurvingTimeDuration(const T _angleRad) const;

 protected:
    /*!
     * \brief Calculate acceleration using Newton gravitational law
     * \param _current Current object position
     * \param _other Source object position
     * \param _otherMass Source object position
     * \param _gravityConstant Gravitational constant
     * \return Calculated acceleration using Newton gravitational law
     */
    static Math::Vec3<T>
    getAccel(const Math::Vec3<T> &_current, const Math::Vec3<T> &_other, const T _otherMass, const T _gravityConstant);
};

template <typename T>
inline T NewtonObject<T>::mass() const
{
    return m_mass;
}

template <typename T>
inline T NewtonObject<T>::currentCurvingTimeDuration(const T _angleRad) const
{
    return ObjectHistory<T, NewtonTimeStamp<T>>::m_history.empty()
        ? -Const::T_1<T>()
        : ObjectHistory<T, NewtonTimeStamp<T>>::m_history.at(ObjectHistory<T, NewtonTimeStamp<T>>::m_currentIdx)
              .curvingTimeDuration(_angleRad);
}

template <typename T>
Math::Vec3<T> NewtonObject<T>::getAccel(const Math::Vec3<T> &_current,
                                        const Math::Vec3<T> &_other,
                                        const T _otherMass,
                                        const T _gravityConstant)
{
    const Math::Vec3<T> result = _other - _current;
    const T ls = result.lengthSquared();
    return Type::isNull<T>(ls) ? result : (result * (_gravityConstant * _otherMass / (ls * std::sqrt(ls))));
    // result /= std::sqrt(ls);                         // Normalize
    // result *= (_gravityConstant * _otherMass / ls);  // Calculate acceleration
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
     * \return Clone of this object
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

#endif  // NEWTONOBJECT_H
