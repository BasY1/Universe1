/*!
 * \file math/sphere.h
 * \author Michal Steller
 * \brief 3D Sphere template implementation
 */

#ifndef UNIVERSE1_MATH_SPHERE_H
#define UNIVERSE1_MATH_SPHERE_H

#include "circle.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief 3D Sphere representation
 * \tparam T Template floating point type
 */
template <typename T>
struct Sphere
{
    T radius;          //!< Sphere radius
    Vec3<T> position;  //!< Sphere position

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere()
        : radius(Const::T_0<T>())
        , position()
    {
    }

    /*!
     * \brief Constructor with sphere components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere(const T _r,  //!< Radius component
                  const T _x,  //!< X component
                  const T _y,  //!< Y component
                  const T _z)  //!< Z component
        : radius(_r)
        , position(_x, _y, _z)
    {
    }

    /*!
     * \brief Constructor with sphere components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere(const T _radius,           //!< Radius component
                  const Vec3<T> &_position)  //!< Position component
        : radius(_radius)
        , position(_position)
    {
    }

    inline void reset(const T _radius, const Vec3<T> &_position);

    inline bool isNull() const;
    inline bool isValid() const;

    inline bool isCovered(const Vec3<T> &_position) const;

    inline bool equals(const Sphere<T> &_other) const;
    inline bool operator==(const Sphere<T> &_other) const;
    inline bool operator!=(const Sphere<T> &_other) const;

    inline void clear();

    inline T surfaceArea() const;
    inline T circleArea() const;

    inline T volume() const;
    inline T volumeCup(const T _height) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Reset sphere properties
 * \tparam T Template floating point type
 * \param _radius New radius
 * \param _position New position
 */
template <typename T>
inline void Sphere<T>::reset(const T _radius, const Vec3<T> &_position)
{
    radius = _radius;
    position = _position;
}

/*!
 * \brief Test if sphere is null (only radius must be null)
 * \tparam T Template floating point type
 * \return \c true if sphere is null
 */
template <typename T>
inline bool Sphere<T>::isNull() const
{
    return Math::isNull<T>(radius);
}

/*!
 * \brief Test if sphere is valid (only radius must be not null and positive)
 * \tparam T Template floating point type
 * \return \c true if sphere is valid
 */
template <typename T>
inline bool Sphere<T>::isValid() const
{
    return isPositive<T>(radius);
}

/*!
 * \brief Test if sphere covers vertex
 * \param _position Vertex position
 * \return \c true if distance of vertex and sphere center position is lower or equals sphere radius
 */
template <typename T>
inline bool Sphere<T>::isCovered(const Vec3<T> &_position) const
{
    const T dist = _position.distanceToPoint(position);
    return Math::equals(dist, radius) || dist < radius;
}

/*!
 * \brief Test if spheres are equal
 * \tparam T Template floating point type
 * \param _other Other sphere
 * \return \c true if spheres are equal
 * \sa TypeEquals<T>(const T, const T)
 */
template <typename T>
inline bool Sphere<T>::equals(const Sphere<T> &_other) const
{
    return Math::equals<T>(radius, _other.radius) && position.equals(_other.position);
}

/*!
 * \brief Operator for test if spheres are equal
 * \tparam T Template floating point type
 * \param _other Other sphere
 * \return \c true if spheres are equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Sphere<T>::operator==(const Sphere<T> &_other) const
{
    return equals(_other);
}

/*!
 * \brief Operator for test if spheres are not equal
 * \tparam T Template floating point type
 * \param _other Other sphere
 * \return \c true if spheres are not equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Sphere<T>::operator!=(const Sphere<T> &_other) const
{
    return !equals(_other);
}

/*!
 * \brief Clear sphere
 * \tparam T Template floating point type
 */
template <typename T>
inline void Sphere<T>::clear()
{
    radius = Const::T_0<T>();
    position.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns sphere surface area \f$4 \pi r^2\f$
 * \tparam T Template floating point type
 * \return Sphere surface area
 */
template <typename T>
inline T Sphere<T>::surfaceArea() const
{
    return Const::T_4PI<T>() * radius * radius;
}

/*!
 * \brief Returns sphere circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Sphere circle area
 */
template <typename T>
inline T Sphere<T>::circleArea() const
{
    return Const::T_PI<T>() * radius * radius;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns sphere circle area \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volume() const
{
    return Const::T_4PI_3<T>() * radius * radius * radius;
}

/*!
 * \brief Returns sphere circle area \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \param _height Cup height
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volumeCup(const T _height) const
{
    return Const::T_PI_3<T>() * _height * _height * (Const::T_3<T>() * radius - _height);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _s Sphere
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Sphere<T> &_s)
{
    return _os << "[R[" << _s.radius << ']' << _s.position << ']';
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_SPHERE_H
