/*!
 * \file math/timestamp.h
 * \author Michal Steller
 * \brief Timestamp data template implementation
 */

#ifndef TIMESTAMP_H
#define TIMESTAMP_H

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

    inline T getTimeWhenWaveHitEvent(const T universeVelocity, const Math::Vec3<T> &eventPosition) const;
};

/*!
 * \brief Returns time when wave from current time-stamp hits event at specific position
 * \tparam T Template floating point type
 * \param universeVelocity Speed of the Universe
 * \param eventPosition Event location
 * \returns Time when wave from current time-stamp hits event at specific position
 */
template <typename T>
inline T TimeStamp<T>::getTimeWhenWaveHitEvent(const T universeVelocity, const Math::Vec3<T> &eventPosition) const
{
    return timeStamp + position.distanceToPoint(eventPosition) / universeVelocity;
}

}  // namespace Simulation
}  // namespace Universe1

#endif  // TIMESTAMP_H
