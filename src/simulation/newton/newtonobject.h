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
 * \brief Singularity object for newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct NewtonObject : public ObjectHistory<T, NewtonTimeStamp<T>>
{
 protected:
    // friend struct NewtonSimulation<T>;

    const size_t m_objectID;  //!< Object's ID
    const T m_mass;           //!< Object's mass [kg]

 public:
    /*!
     * \brief Default constructor
     * \param _objectID Object's ID
     * \param _mass Object's mass
     */
    inline NewtonObject(const size_t _objectID, const T _mass)
        : ObjectHistory<T, NewtonTimeStamp<T>>()
        , m_objectID(_objectID)
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
        : ObjectHistory<T, NewtonTimeStamp<T>>(_size)
        , m_objectID(_objectID)
        , m_mass(_mass)
    {
    }

    /*!
     * \brief Getter for object's ID
     * \returns Object's ID
     */
    inline size_t objectID() const
    {
        return m_objectID;
    }

    /*!
     * \brief Getter for object's mass
     * \returns Object's mass
     */
    inline T mass() const
    {
        return m_mass;
    }

    void initStepByCurrent(const std::list<NewtonObject<T> *> &objects, const T gravityConstant);
    void initStepByWave(const std::list<NewtonObject<T> *> &objects, const T gravityConstant, const T universeVelocity);

    inline T currentCurvingTimeDuration(const T angleRad) const;
};

/*!
 * \brief Calculate current move acceleration, force direction points to current object position
 * \tparam T Template floating point type
 * \param objects List of all simulated objects
 * \param gravityConstant Gravitational constant
 */
template <typename T>
void NewtonObject<T>::initStepByCurrent(const std::list<NewtonObject<T> *> &objects, const T gravityConstant)
{
    NewtonTimeStamp<T> *cur = ObjectHistory<T, NewtonTimeStamp<T>>::current();
    Math::Vec3<T> accel;
    for (const NewtonObject<T> *obj : objects)
        if (obj->m_objectID != m_objectID)
            accel += gravityConstant * obj->mass() / (cur->position - obj->current()->position).lengthSquared();
    cur->moveAccel = accel;
}

/*!
 * \brief Calculate current move acceleration, force direction points to current object position
 * \tparam T Template floating point type
 * \param objects List of all simulated objects
 * \param gravityConstant Gravitational constant
 * \param universeVelocity Velocity of the universe
 */
template <typename T>
void NewtonObject<T>::initStepByWave(const std::list<NewtonObject<T> *> &objects,
                                     const T gravityConstant,
                                     const T universeVelocity)
{
    NewtonTimeStamp<T> *cur = ObjectHistory<T, NewtonTimeStamp<T>>::current();
    Math::Vec3<T> accel;
    for (const NewtonObject<T> *obj : objects)
        if (obj->m_objectID != m_objectID)
        {
            const std::pair<EventSourceResult, const NewtonTimeStamp<T> *> source =
                obj->eventSource(universeVelocity, cur->timeStamp, cur->position);

            switch (source.first)
            {
            case EventSourceEmptyPath: break;

            case EventSourceFoundExact:
                accel += gravityConstant * obj->mass() / (cur->position - source.second->position).lengthSquared();
                break;

            case EventSourceFoundClosest:
            case EventSourceFoundFirst:
            case EventSourceMissing:
                accel += gravityConstant * obj->mass() /
                    (cur->position -
                     source.second->movedToEventSource(universeVelocity, cur->timeStamp, cur->position).position)
                        .lengthSquared();
                break;
            }
        }
    cur->moveAccel = accel;
}

template <typename T>
inline T NewtonObject<T>::currentCurvingTimeDuration(const T angleRad) const
{
    return ObjectHistory<T, NewtonTimeStamp<T>>::m_history.empty()
        ? -Const::T_1<T>()
        : ObjectHistory<T, NewtonTimeStamp<T>>::m_history.at(ObjectHistory<T, NewtonTimeStamp<T>>::m_currentIdx)
              .curvingTimeDuration(angleRad);
}

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // NEWTONOBJECT_H
