/*!
 * \file simulation/newton/newtonobject.h
 * \author Michal Steller
 * \brief Base class for singularity object for newton based simulations template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECT_H
#define UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECT_H

#include "newtontimestamp.h"

#include "../objecthistory.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

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

    /*!
     * \brief Getter for object's velocity
     * \param _timeStamp Time-stamp of required position
     * \returns Pair, where \c first item is success flag, and \c second item is object's velocity (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadVelocity(const T _timeStamp) const;

    /*!
     * \brief Getter for object's acceleration
     * \param _timeStamp Time-stamp of required position
     * \returns Pair, where \c first item is success flag, and \c second item is object's acceleration (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadAccel(const T _timeStamp) const;

 protected:
    /*!
     * \brief Calculate acceleration using Newton gravitational law
     * \param _current Current object position
     * \param _other Source object position
     * \param _otherMass Source object position
     * \param _gravityConstant Gravitational constant
     * \returns Calculated acceleration using Newton gravitational law
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
std::pair<bool, QVector3D> NewtonObject<T>::loadVelocity(const T _timeStamp) const
{
    const NewtonTimeStamp<T> *result = ObjectHistory<T, NewtonTimeStamp<T>>::dataAtTime(_timeStamp);
    if (result == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;
    if (Type::isNull(timeDelta))
        return {true, result->moveVelocity.toQVector3D()};

    return {true, result->moved(timeDelta).moveVelocity.toQVector3D()};
}

template <typename T>
std::pair<bool, QVector3D> NewtonObject<T>::loadAccel(const T _timeStamp) const
{
    const NewtonTimeStamp<T> *result = ObjectHistory<T, NewtonTimeStamp<T>>::dataAtTime(_timeStamp);
    if (result == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;
    if (Type::isNull(timeDelta))
        return {true, result->moveAccel.toQVector3D()};

    return {true, result->moved(timeDelta).moveAccel.toQVector3D()};
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

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONOBJECT_H
