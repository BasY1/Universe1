/*!
 * \file simulation/timestamp.h
 * \author Michal Steller
 * \brief Timestamp data template implementation
 */

#ifndef UNIVERSE1_SIMULATION_TIMESTAMP_H
#define UNIVERSE1_SIMULATION_TIMESTAMP_H

#include "../math/vec3.h"

namespace Universe1 {
namespace Simulation {

/*!
 * \brief Base time-stamp class
 * \tparam T Template floating point type
 * \details Holds object's position at specific time-stamp
 */
template <typename T>
struct TimeStamp
{
    T timeStamp;             //!< Time-stamp value    [s]
    Math::Vec3<T> position;  //!< Object position     [m]

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline TimeStamp()
        : timeStamp(Const::T_0<T>())
        , position()
    {
    }

    /*!
     * \brief Constructor with object components
     * \param _timeStamp    Time-stamp value    [s]
     * \param _position     Object position     [m]
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline TimeStamp(const T _timeStamp, const Math::Vec3<T> &_position)
        : timeStamp(_timeStamp)
        , position(_position)
    {
    }

    /*!
     * \brief Returns time when wave from current time-stamp hits event at specific position
     * \param _universeVelocity Speed of the Universe
     * \param _eventPosition Event location
     * \returns Time when wave from current time-stamp hits event at specific position
     */
    inline T getTimeWhenWaveHitEvent(const T _universeVelocity, const Math::Vec3<T> &_eventPosition) const
    {
        return timeStamp + position.distanceToPoint(_eventPosition) / _universeVelocity;
    }
};

}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_TIMESTAMP_H
