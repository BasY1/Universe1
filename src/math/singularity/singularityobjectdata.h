/*!
 * \file math/singularity/singularityobjectdata.h
 * \author Michal Steller
 * \brief Singularity object data template implementation
 */

#ifndef SINGULARITYOBJECTDATA_H
#define SINGULARITYOBJECTDATA_H

#include "../vec3.h"

/*!
 * \defgroup SingularityWithMass Singularity with mass
 * \brief Tools for relativistic - newton gravitation simulations based on massive singularities
 */

/*!
 * \brief Singularity object data in specific \b time in simulation
 * \tparam T Template floating point type
 * \ingroup SingularityWithMass
 * \details Holds singularity object data in single simulation time-stamp.
 */
template <typename T>
struct SingularityObjectData
{
    T timeStamp;           //!< Time-stamp value    [s]
    Vec3<T> position;      //!< Object position     [m]
    Vec3<T> moveVelocity;  //!< Object velocity     [m/s]
    Vec3<T> moveAccel;     //!< Object acceleration [m/s^2]

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline SingularityObjectData()
        : timeStamp(T_0<T>())
        , position()
        , moveVelocity()
        , moveAccel()
    {
    }

    /*!
     * \brief Constructor with object components
     * \param _timeStamp    Time-stamp value    [s]
     * \param _position     Object position     [m]
     * \param _moveVelocity Object velocity     [m/s]
     * \param _moveAccel    Object acceleration [m/s^2]
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline SingularityObjectData(const T _timeStamp,
                                 const Vec3<T> &_position,
                                 const Vec3<T> &_moveVelocity,
                                 const Vec3<T> &_moveAccel)
        : timeStamp(_timeStamp)
        , position(_position)
        , moveVelocity(_moveVelocity)
        , moveAccel(_moveAccel)
    {
    }

    /*!
     * \brief Constructor from other object
     * \param other Other object
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline SingularityObjectData(const SingularityObjectData<T> &other)
        : timeStamp(other.timeStamp)
        , position(other.position)
        , moveVelocity(other.moveVelocity)
        , moveAccel(other.moveAccel)
    {
    }

    inline bool isNull() const;

    SingularityObjectData<T> moved(const T timeDelta) const;

    inline SingularityObjectData<T> atTime(const T timeStamp) const;

    inline T getTimeWhenWaveHitEvent(const T universeVelocity, const Vec3<T> &eventPosition) const;

    SingularityObjectData<T>
    getSource(const T universeVelocity, const T eventTimeStamp, const Vec3<T> &eventPosition) const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if object is null
 * \tparam T Template floating point type
 * \returns \c true if all object's components are null
 */
template <typename T>
bool SingularityObjectData<T>::isNull() const
{
    return TypeIsNormal<T>(timeStamp) && position.isNull() && moveVelocity.isNull() && moveAccel.isNull();
}

/*!
 * \brief Returns this object moved in time
 * \tparam T Template floating point type
 * \param timeDelta Time duration of move
 * \returns This object moved in time
 * \details
 *
 * | Property        | Calculation                                                                         |
 * | :-------------- | :---------------------------------------------------------------------------------- |
 * | \a timeStamp    | \f$t_N + \Delta t\f$                                                                |
 * | \a position     | \f$\vec{P}_{t_N} + \vec{V}_{t_N} \Delta t + \frac{1}{2} \vec{A}_{t_N} \Delta t^2\f$ |
 * | \a moveVelocity | \f$\vec{V}_{t_N} + \vec{A}_{t_N} \Delta t\f$                                        |
 * | \a moveAccel    | \f$[0,0,0]\f$                                                                       |
 */
template <typename T>
SingularityObjectData<T> SingularityObjectData<T>::moved(const T timeDelta) const
{
    return SingularityObjectData<T>(timeStamp + timeDelta,
                                    position + moveVelocity * timeDelta +
                                        moveAccel * (timeDelta * timeDelta * T_05<T>()),
                                    moveVelocity + moveAccel * timeDelta,
                                    Vec3<T>());
}

/*!
 * \brief Returns this object moved to time-stamp
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required output object
 * \returns This object moved to passed time-stamp
 * \sa SingularityObjectData<T>::moved(const T timeDelta) const
 */
template <typename T>
inline SingularityObjectData<T> SingularityObjectData<T>::atTime(const T _timeStamp) const
{
    return moved(_timeStamp - timeStamp);
}

/*!
 * \brief Returns time when wave from current time-stamp hits event at specific position
 * \tparam T Template floating point type
 * \param universeVelocity Speed of the Universe
 * \param eventPosition Event location
 * \returns Time when wave from current time-stamp hits event at specific position
 */
template <typename T>
inline T SingularityObjectData<T>::getTimeWhenWaveHitEvent(const T universeVelocity, const Vec3<T> &eventPosition) const
{
    return timeStamp + position.distanceToPoint(eventPosition) / universeVelocity;
}

/*!
 * \brief Returns this object moved in time to position from where gravitation wave hits event
 * \tparam T Template floating point type
 * \param universeVelocity Speed of the Universe
 * \param eventTimeStamp Time-stamp of event
 * \param eventPosition Event location
 * \returns This object moved in time to position from where gravitation wave hits event
 */
template <typename T>
SingularityObjectData<T> SingularityObjectData<T>::getSource(const T universeVelocity,
                                                             const T eventTimeStamp,
                                                             const Vec3<T> &eventPosition) const
{
    T time1Add = T_0<T>();
    T timeHit = getTimeWhenWaveHitEvent(universeVelocity, eventPosition);
    if (TypeEquals<T>(timeHit, eventTimeStamp))
        return SingularityObjectData<T>(timeStamp, position, moveVelocity, Vec3<T>());

    T time1Diff = eventTimeStamp - timeHit;

    T time2Add = time1Diff;
    SingularityObjectData<T> tmpObject = moved(time2Add);
    timeHit = tmpObject.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);

    if (TypeEquals<T>(timeHit, eventTimeStamp))
        return tmpObject;

    T time2Diff = eventTimeStamp - timeHit;

    for (int step = 3; step < 20; ++step)
    {
        const T time3Add = time1Add - (time1Add - time2Add) * time1Diff / (time1Diff - time2Diff);

        tmpObject = moved(time3Add);
        timeHit = tmpObject.getTimeWhenWaveHitEvent(universeVelocity, eventPosition);

        if (TypeEquals<T>(timeHit, eventTimeStamp))
            return tmpObject;

        time1Add = time2Add;
        time2Add = time3Add;
        time1Diff = time2Diff;
        time2Diff = (eventTimeStamp - timeHit);
    }
    return SingularityObjectData<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param os Output text stream
 * \param obj Singularity object data
 * \returns Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const SingularityObjectData<T> &obj)
{
    return os << "[T[" << obj.timeStamp << "],P" << obj.position << ",V" << obj.moveVelocity << ",A" << obj.moveAccel
              << ']';
}

#endif  // SINGULARITYOBJECTDATA_H
