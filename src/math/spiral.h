/*!
 * \file math/spiral.h
 * \author Michal Steller
 * \brief 3D Spiral template implementation
 */

#ifndef UNIVERSE1_MATH_SPIRAL_H
#define UNIVERSE1_MATH_SPIRAL_H

#include "vec3.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief 3D Spiral representation
 * \tparam T Template floating point type
 */
template <typename T>
struct Spiral
{
    Vec3<T> center;    //!< Spiral central position
    Vec3<T> normal;    //!< Spiral normal (unit 3D vector)
    Vec3<T> arm;       //!< Spiral arm (3D vector, \a arm length is spiral radius
    T ratio;           //!< Spiral ratio \f$\frac{V_{NORMAL}}{V_{SPIN}}\f$
    bool rightHanded;  //!< Right-handed orientation flag

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Spiral()
        : center()
        , normal()
        , arm()
        , ratio(Const::T_0<T>())
        , rightHanded(true)
    {
    }

    /*!
     * \brief Constructor with components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Spiral(const Vec3<T> &_center,          //!< Spiral central position
                  const Vec3<T> &_normal,          //!< Spiral central position
                  const Vec3<T> &_arm,             //!< Spiral arm
                  const T _ratio,                  //!< Spiral ratio
                  const bool _rightHanded = true)  //!< Right-handed orientation flag

        : center(_center)
        , normal(_normal)
        , arm(_arm)
        , ratio(_ratio)
        , rightHanded(_rightHanded)
    {
    }

    inline bool isValid() const;

    inline Vec3<T> pointPosition() const;
    Vec3<T> pointDirection() const;

    inline void clear();

    Spiral<T> moved(const T _length) const;

    inline Vec3<T> movedCenter(const T _length) const;
    inline Vec3<T> movedArm(const T _length) const;
    inline Vec3<T> movedPointPosition(const T _length) const;
    inline Vec3<T> movedPointDirection(const T _length) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if spiral is valid - normal is unit vector and arm is not null
 * \tparam T Template floating point type
 * \return \c true if spiral is valid
 */
template <typename T>
inline bool Spiral<T>::isValid() const
{
    return Type::isPositive<T>(ratio) && normal.isNormalized() && !arm.isNull();
}

/*!
 * \brief Returns spiral point position
 * \tparam T Template floating point type
 * \return Spiral point position
 */
template <typename T>
inline Vec3<T> Spiral<T>::pointPosition() const
{
    return center + arm;
}

/*!
 * \brief Returns spiral point direction normal
 * \tparam T Template floating point type
 * \return Spiral point position (unit 3D vector)
 */
template <typename T>
Vec3<T> Spiral<T>::pointDirection() const
{
    if (!isValid())
        return Vec3<T>();
    const T angle = (rightHanded ? Const::T_1<T>() : -Const::T_1<T>()) * std::atan(Const::T_1<T>() / ratio);
    const Vec3<T> n2 = -arm.normalized();
    return normal.rotated(n2, angle);
}

/*!
 * \brief Clear spiral
 * \tparam T Template floating point type
 */
template <typename T>
inline void Spiral<T>::clear()
{
    center.clear();
    normal.clear();
    arm.clear();
    ratio = Const::T_0<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Spiral moved by given length over its own path
 * \tparam T Template floating point type
 * \param _length Length mo move
 * \return Same spiral with shifted "begin" conditions (shifted \a center and \a arm)
 */
template <typename T>
Spiral<T> Spiral<T>::moved(const T _length) const
{
    if (!isValid())
        return Spiral<T>();

    const T spiralR = arm.length();
    const T spinPath = _length / std::sqrt(Const::T_1<T>() + ratio * ratio);
    const T spinAngle = (rightHanded ? Const::T_1<T>() : -Const::T_1<T>()) * spinPath / Const::T_2PIxR<T>(spiralR);
    const T normalPath = spinPath * ratio;
    const Vec3<T> move = normal * normalPath;
    return Spiral<T>(center + move, normal, arm.rotated(normal, spinAngle), ratio, rightHanded);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Center position of spiral moved by given length over its own path
 * \tparam T Template floating point type
 * \param _length Length mo move
 * \return Moved center position
 */
template <typename T>
inline Vec3<T> Spiral<T>::movedCenter(const T _length) const
{
    return moved(_length).center;
}

/*!
 * \brief Arm of spiral moved by given length over its own path
 * \tparam T Template floating point type
 * \param _length Length mo move
 * \return Moved spiral arm
 */
template <typename T>
inline Vec3<T> Spiral<T>::movedArm(const T _length) const
{
    return moved(_length).arm;
}

/*!
 * \brief Point position of spiral moved by given length over its own path
 * \tparam T Template floating point type
 * \param _length Length mo move
 * \return Moved point position
 */
template <typename T>
inline Vec3<T> Spiral<T>::movedPointPosition(const T _length) const
{
    return moved(_length).pointPosition();
}

/*!
 * \brief Point direction of spiral moved by given length over its own path
 * \tparam T Template floating point type
 * \param _length Length mo move
 * \return Moved point direction
 */
template <typename T>
inline Vec3<T> Spiral<T>::movedPointDirection(const T _length) const
{
    return moved(_length).pointDirection();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _s Spiral
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Spiral<T> &_s)
{
    return _os << "[C" << _s.center << 'A' << _s.arm << 'N' << _s.normal << "R[" << _s.ratio << "]]";
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_SPIRAL_H
