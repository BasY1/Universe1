/*!
 * \file simulation/newton/newtontimestamp.h
 * \author Michal Steller
 * \brief Newton based time-stamp template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONTIMESTAMP_H
#define UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONTIMESTAMP_H

#include "../timestamp.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

/*!
 * \brief Time-stamp extension for newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct NewtonTimeStamp : public TimeStamp<T>
{

    Math::Vec3<T> moveVelocity;  //!< Object velocity     [m/s]
    Math::Vec3<T> moveAccel;     //!< Object acceleration [m/s^2]

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline NewtonTimeStamp()
        : TimeStamp<T>()
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
    inline NewtonTimeStamp(const T _timeStamp,
                           const Math::Vec3<T> &_position,
                           const Math::Vec3<T> &_moveVelocity,
                           const Math::Vec3<T> &_moveAccel = Math::Vec3<T>())
        : TimeStamp<T>(_timeStamp, _position)
        , moveVelocity(_moveVelocity)
        , moveAccel(_moveAccel)
    {
    }

    inline NewtonTimeStamp<T> moved(const T _timeDelta) const;

    T curvingAngleRad(const T _timeDelta) const;
    T curvingTimeDuration(const T _angleRad) const;

    std::pair<NewtonTimeStamp<T>, bool>
    movedToEventSource(const T _universeVelocity, const T _eventTimeStamp, const Math::Vec3<T> &_eventPosition) const;

    static bool compareMoved(const NewtonTimeStamp<T> &_previous, const NewtonTimeStamp<T> &_next);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns angle between current move direction and direction after given time duration
 * \tparam T Template floating point type
 * \param _timeDelta Time duration of move
 * \returns Angle between current move direction and direction after given time duration
 * \details
 * New move velocity after time duration:
 * \f$\vec{V}_{t_\Delta} = \vec{V}_{t_N} + \vec{A}_{t_N} \Delta t\f$
 *
 * Returned value is angle (in radians) in between \f$\vec{V}_{t_N}\f$ and \f$\vec{V}_{t_\Delta}\f$
 */
template <typename T>
T NewtonTimeStamp<T>::curvingAngleRad(const T _timeDelta) const
{
    return moveVelocity.angleRad(moveVelocity + moveAccel * _timeDelta);
}

/*!
 * \brief Returns time duration that is needed to curve (turn) move direction by given angle
 * \tparam T Template floating point type
 * \param _angleRad Curving angle on radians
 * \returns Time duration that is needed to curve move direction by given angle
 * \note Returns <tt><b>-1</b></tt> when object is not curving (move velocity and acceleration are parallel or at least
 * one has zero length)
 * \details
 * Vector property substitutions:
 * \f{eqnarray*}{
 * \vec{V}_{t_N} &-&\mbox {Current velocity}\\
 * A &=& \vec{V}_{t_N} \left( X \right) \\
 * B &=& \vec{V}_{t_N} \left( Y \right) \\
 * C &=& \vec{V}_{t_N} \left( Z \right) \\
 * \\
 * \vec{A}_{t_N} &-&\mbox {Current acceleration}\\
 * D &=& \vec{A}_{t_N} \left( X \right) \\
 * E &=& \vec{A}_{t_N} \left( Y \right) \\
 * F &=& \vec{A}_{t_N} \left( Z \right) \\
 * \\
 * t_X &-& \mbox {Time duration we are looking for} \\
 * \vec{V}_{t_X} &-&\mbox {Velocity after time duration}\\
 * \vec{V}_{t_X} &=& \vec{V}_{t_N} + \vec{A}_{t_N} \cdot t_X \\
 * I &=& \vec{V}_{t_X} \left( X \right) = A + D \cdot t_X \\
 * J &=& \vec{V}_{t_X} \left( Y \right) = B + E \cdot t_X \\
 * K &=& \vec{V}_{t_X} \left( Z \right) = C + F \cdot t_X \\
 * \f}
 *
 * Given angle \f$ \alpha \f$ is angle between \f$\vec{V}_{t_N}\f$ and \f$\vec{V}_{t_X}\f$. We can use cosinus formula:
 * \f{eqnarray*}{
 * cos(\alpha) &=& \frac{\vec{V}_{t_N}\cdot\vec{V}_{t_X}}{\sqrt{|\vec{V}_{t_N}|^2 |\vec{V}_{t_X}|^2}}
 *  = \frac{\vec{V}_{t_N}\cdot\vec{V}_{t_X}}{\sqrt{(\vec{V}_{t_N}\cdot\vec{V}_{t_N}) \cdot
 * (\vec{V}_{t_X}\cdot\vec{V}_{t_X})}}
 * \\
 *             &=& \frac{A \cdot I + B \cdot J + C \cdot K}{
 *                  \sqrt{ (A \cdot A + B \cdot B + C \cdot C) \cdot (I \cdot I + J \cdot J + K \cdot K) }}
 * \\
 * \\
 *             &=& \frac{A \cdot (A + D \cdot t_X) + B \cdot (B + E \cdot t_X) + C \cdot (C + F \cdot t_X)}{
 *                  \sqrt{ (A^2 + B^2 + C^2) \cdot [(A + D \cdot t_X)^2 + (B + E \cdot t_X)^2 + (C + F \cdot t_X)^2] }}
 * \f}
 * Solve equation:
 * \f{eqnarray*}{
 * cos(\alpha)^2 \cdot (A^2 + B^2 + C^2) \cdot [(A + D \cdot t_X)^2 + (B + E \cdot t_X)^2 + (C + F \cdot t_X)^2]
 *             &=& [A \cdot (A + D \cdot t_X) + B \cdot (B + E \cdot t_X) + C \cdot (C + F \cdot t_X)]^2 && |
 * G = cos(\alpha)^2 \cdot (A^2 + B^2 + C^2)
 * \\
 * G \cdot [(A + D \cdot t_X)^2 + (B + E \cdot t_X)^2 + (C + F \cdot t_X)^2]
 *             &=& [A \cdot (A + D \cdot t_X) + B \cdot (B + E \cdot t_X) + C \cdot (C + F \cdot t_X)]^2
 * \\
 * G \cdot [A^2 + 2 \cdot A \cdot D \cdot t_X + D^2 \cdot t_{X}^2 +
 *          B^2 + 2 \cdot B \cdot E \cdot t_X + E^2 \cdot t_{X}^2 +
 *          C^2 + 2 \cdot C \cdot F \cdot t_X + F^2 \cdot t_{X}^2 ]
 *             &=& [ A^2 + A \cdot D \cdot t_X + B^2 + B \cdot E \cdot t_X + C^2 + C \cdot F \cdot t_X ]^2
 *                 && | H = A^2 + B^2 + C^2
 * \\
 * G \cdot [H + 2 \cdot A \cdot D \cdot t_X + D^2 \cdot t_{X}^2
 *            + 2 \cdot B \cdot E \cdot t_X + E^2 \cdot t_{X}^2
 *            + 2 \cdot C \cdot F \cdot t_X + F^2 \cdot t_{X}^2 ]
 *             &=& [ H + A \cdot D \cdot t_X + B \cdot E \cdot t_X + C \cdot F \cdot t_X ]^2
 * \\
 * G \cdot [H + 2 \cdot (A \cdot D + B \cdot E + C \cdot F) \cdot t_X + (D^2 + E^2 + F^2) \cdot t_{X}^2 ]
 *             &=& [ H + ( A \cdot D + B \cdot E + C \cdot F ) \cdot t_X ]^2
 *                 && | L = A \cdot D + B \cdot E + C \cdot F
 * \\
 *             & & && | M = D^2 + E^2 + F^2
 * \\
 * G \cdot [H + 2 \cdot L \cdot t_X + M \cdot t_{X}^2 ] &=& [ H + L \cdot t_X ]^2
 * \\
 * G \cdot H + 2 \cdot G \cdot L \cdot t_X + G \cdot M \cdot t_{X}^2
 *             &=& H^2 + 2 \cdot H \cdot L \cdot t_X + L^2 \cdot t_{X}^2
 * \\
 * t_{X}^2 \cdot [ G \cdot M - L^2 ] + t_X \cdot [ 2 \cdot L \cdot ( G - H ) ] + [G \cdot H - H^2] &=& 0
 * \\
 * t_{X}^2 + t_X \cdot \frac{2 \cdot L \cdot ( G - H )}{G \cdot M - L^2} + \frac{G \cdot H - H^2}{G \cdot M - L^2}
 *             &=& 0
 *                 && | b = \frac{2 \cdot L \cdot ( G - H )}{G \cdot M - L^2}
 * \\
 *             & & && | c = \frac{G \cdot H - H^2}{G \cdot M - L^2}
 * \f}
 * Simplify result:
 * \f{eqnarray*}{
 * t_X &=& \frac{- b \pm \sqrt{ b^2 - 4 \cdot c }}{2}
 * \\
 * t_X &=& \frac{- \frac{2 \cdot L \cdot ( G - H )}{G \cdot M - L^2} \pm
 * \sqrt{ \frac{4 \cdot L^2 \cdot ( G - H )^2}{(G \cdot M - L^2)^2} - 4 \cdot \frac{G \cdot H - H^2}{G \cdot M - L^2}
 * }}{2}
 * \\
 * t_X &=& - \frac{L \cdot ( G - H )}{G \cdot M - L^2} \pm
 * \sqrt{ \frac{L^2 \cdot ( G - H )^2}{(G \cdot M - L^2)^2} - \frac{G \cdot H - H^2}{G \cdot M - L^2}}
 * \\
 * t_X &=& - \frac{L \cdot ( G - H ) \pm \sqrt{ L^2 \cdot ( G - H )^2 - (G \cdot H - H^2) \cdot ( G \cdot M - L^2 )} }
 *                {G \cdot M - L^2}
 * \\
 * t_X &=& - \frac{L \cdot ( G - H ) \pm \sqrt{
 *  ( L^2 \cdot G^2 - 2 \cdot L^2 \cdot G \cdot H + L^2 \cdot H^2 )
 * - (G^2 \cdot H \cdot M - G \cdot H \cdot L^2 - H^2 \cdot G \cdot M + H^2 \cdot L^2)
 * } }{G \cdot M - L^2}
 * \\
 * t_X &=& \frac{L \cdot ( H - G ) \pm \sqrt{
 *   L^2 \cdot G^2 - L^2 \cdot G \cdot H - G^2 \cdot H \cdot M + H^2 \cdot G \cdot M
 * } }{G \cdot M - L^2}
 * \\
 * t_X &=& \frac{L \cdot ( H - G ) \pm \sqrt{
 *   L^2 \cdot G \cdot ( G - H) - G \cdot H \cdot M \cdot ( G - H)
 * } }{G \cdot M - L^2}
 * \\
 * t_X &=& \frac{L \cdot ( H - G ) \pm \sqrt{ G \cdot ( G - H)  \cdot (L^2 - H \cdot M) } }{G \cdot M - L^2}
 * \\
 * \f}
 */
template <typename T>
T NewtonTimeStamp<T>::curvingTimeDuration(const T _angleRad) const
{
    if (moveVelocity.isNull() || moveAccel.isNull() || moveVelocity.isParallel(moveAccel))
        return -Const::T_1<T>();

    const T ca = std::cos(_angleRad);

    const T H = moveVelocity.lengthSquared();
    const T G = H * ca * ca;
    const T L = Math::Vec3<T>::dot(moveVelocity, moveAccel);
    const T M = moveAccel.lengthSquared();

    const T GMLL = G * M - L * L;
    if (Type::isNull(GMLL))
        return -Const::T_1<T>();

    // const T DS = L * L * G * G - L * L * G * H - G * G * H * M + H * H * G * M;
    const T DS = G * (G - H) * (L * L - H * M);
    const T LHG = L * (H - G);
    if (Type::isNull(DS))
        return LHG / GMLL;

    if (DS < Const::T_0<T>())
        return -Const::T_1<T>();

    const T DS2 = std::sqrt(DS);

    return std::max((LHG + DS2) / GMLL, (LHG - DS2) / GMLL);
}

/*!
 * \brief Compare previous and moved object
 * \tparam T Template floating point type
 * \param _previous First object
 * \param _next Second object
 * \returns \c true when time-stamp, position and velocity are equal
 * \note Acceleration \a moveAccel is ignored
 */
template <typename T>
bool NewtonTimeStamp<T>::compareMoved(const NewtonTimeStamp<T> &_previous, const NewtonTimeStamp<T> &_next)
{
    const T stepDuration = _next.timeStamp - _previous.timeStamp;
    const NewtonTimeStamp<T> movedObject = _previous.moved(stepDuration);
    return Type::equals(_next.timeStamp, movedObject.timeStamp) && _next.position == movedObject.position &&
        _next.moveVelocity == movedObject.moveVelocity;
}

/*!
 * \brief Returns this object moved in time
 * \tparam T Template floating point type
 * \param _timeDelta Time duration of move \f$\Delta t\f$
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
inline NewtonTimeStamp<T> NewtonTimeStamp<T>::moved(const T _timeDelta) const
{
    return NewtonTimeStamp<T>(TimeStamp<T>::timeStamp + _timeDelta,
                              TimeStamp<T>::position + moveVelocity * _timeDelta +
                                  moveAccel * (_timeDelta * _timeDelta * Const::T_05<T>()),
                              moveVelocity + moveAccel * _timeDelta,
                              Math::Vec3<T>());
}

/*!
 * \brief Returns this object moved in time to position from where gravitation wave hits event
 * \tparam T Template floating point type
 * \param _universeVelocity Speed of the Universe
 * \param _eventTimeStamp Time-stamp of event
 * \param _eventPosition Event location
 * \returns Pair of this object moved in time to position from where gravitation wave hits event and success flag
 */
template <typename T>
std::pair<NewtonTimeStamp<T>, bool> NewtonTimeStamp<T>::movedToEventSource(const T _universeVelocity,
                                                                           const T _eventTimeStamp,
                                                                           const Math::Vec3<T> &_eventPosition) const
{
    T time1Add = Const::T_0<T>();
    T timeHit = TimeStamp<T>::getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
    if (Type::equals<T>(timeHit, _eventTimeStamp))
        return {NewtonTimeStamp<T>(TimeStamp<T>::timeStamp, TimeStamp<T>::position, moveVelocity, Math::Vec3<T>()),
                true};

    T time1Diff = _eventTimeStamp - timeHit;

    T time2Add = time1Diff;
    NewtonTimeStamp<T> tmpObject = moved(time2Add);
    timeHit = tmpObject.getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);

    if (Type::equals<T>(timeHit, _eventTimeStamp))
        return {tmpObject, true};

    T time2Diff = _eventTimeStamp - timeHit;

    for (int step = 3; step < 20; ++step)
    {
        const T time3Add = time1Add - (time1Add - time2Add) * time1Diff / (time1Diff - time2Diff);

        tmpObject = moved(time3Add);
        timeHit = tmpObject.getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);

        if (Type::equals<T>(timeHit, _eventTimeStamp))
            return {tmpObject, true};

        time1Add = time2Add;
        time2Add = time3Add;
        time1Diff = time2Diff;
        time2Diff = (_eventTimeStamp - timeHit);
    }
    return {NewtonTimeStamp<T>(), false};
}

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Vector
 * \returns Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const NewtonTimeStamp<T> &_v)
{
    return _os << '[' << _v.timeStamp << '|' << _v.position << '|' << _v.moveVelocity << '|' << _v.moveAccel << ']';
}

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONTIMESTAMP_H
