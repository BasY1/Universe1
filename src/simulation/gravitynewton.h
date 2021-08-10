/*!
 * \file math/objecthistory.h
 * \author Michal Steller
 * \brief Object history base template implementation
 */

#ifndef GRAVITYNEWTON_H
#define GRAVITYNEWTON_H

#include "objecthistory.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

template <typename T>
struct NewtonSimulation;

/*!
 * \brief Time-stamp extension for newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct NewtonTimeStamp : public TimeStamp<T>
{
    Math::Vec3<T> moveVelocity;  //!< Object velocity     [m/s]
    Math::Vec3<T> moveAccel;     //!< Object acceleration [m/s^2]
};

/*!
 * \brief Singularity object for newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct NewtonObject : public ObjectHistory<T, NewtonTimeStamp<T>>
{
 protected:
    friend struct NewtonSimulation<T>;

    const size_t m_objectID;  //!< Object's ID
    const T m_mass;           //!< Object's mass [kg]

 public:
    /*!
     * \brief Default constructor
     */
    inline NewtonObject(const size_t _objectID, const T _mass)
        : ObjectHistory<T, NewtonTimeStamp<T>>()
        , m_objectID(_objectID)
        , m_mass(_mass)
    {
    }

    /*!
     * \brief Constructor
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
};

template <typename T>
struct NewtonSimulationCurrent
{
 protected:
    const T m_gravityConstant;  //!< Gravitational constant

    const T m_maximumStepTime;       //!< Maximum step time duration
    const T m_maximumCurveAngleRad;  //!< Maximum curve angle within step

    std::list<NewtonObject<T> *> m_data;  //!< Objects

 public:
    NewtonSimulationCurrent(const T _gravityConstant, const T _maximumStepTime, const T _maximumCurveAngleRad)
        : m_gravityConstant(_gravityConstant)
        , m_maximumStepTime(_maximumStepTime)
        , m_maximumCurveAngleRad(_maximumCurveAngleRad)
    {
    }

    inline void addObject(NewtonObject<T> *_object)
    {
        m_data.push_back(_object);
    }

    inline void addCopy(const NewtonObject<T> &_object)
    {
        m_data.push_back(new NewtonObject<T>(_object));
    }
};

template <typename T>
struct NewtonSimulationWave : public NewtonSimulationCurrent<T>
{
 protected:
    const T m_universeVelocity;  //!< Velocity of gravitation wave spreading within universe
 public:
    NewtonSimulationWave(const T _universeVelocity,
                         const T _gravityConstant,
                         const T _maximumStepTime,
                         const T _maximumCurveAngleRad)
        : NewtonSimulationCurrent<T>(_gravityConstant, _maximumStepTime, _maximumCurveAngleRad)
        , m_universeVelocity(_universeVelocity)
    {
    }
};

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // GRAVITYNEWTON_H
