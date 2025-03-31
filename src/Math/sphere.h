/*!
 * \file src/Math/sphere.h
 * \brief 3D sphere structure
 */

#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H

#include "vec3.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D Sphere representation
 * \tparam T Template floating point type
 */
template <typename T>
struct Sphere
{
    Vec3<T> center;    //!< Sphere position
    T radius;          //!< Sphere radius

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere()
        : center()
        , radius(T(0))
    {
    }

    /*!
     * \brief Constructor with sphere components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere(const T _x,  //!< X component
                  const T _y,  //!< Y component
                  const T _z,  //!< Z component
                  const T _r)  //!< Radius component
        : center(_x, _y, _z)
        , radius(_r)
    {
    }

    /*!
     * \brief Constructor with sphere components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere(const Vec3<T> &_center,  //!< Position component
                  const T _radius = T(1))  //!< Radius component
        : center(_center)
        , radius(_radius)
    {
    }

    inline void reset(const T _radius, const Vec3<T> &_position);

    inline bool isNull() const;
    inline bool isValid() const;

    inline bool equals(const Sphere<T> &_other) const;
    inline bool operator==(const Sphere<T> &_other) const;
    inline bool operator!=(const Sphere<T> &_other) const;

    inline void clear();

    inline T surfaceArea() const;
    inline T circleArea() const;

    inline T volume() const;
    inline T volumeCup(const T _height) const;

    //
    void createBodyPoints(const T _density, std::vector<Vec3<T>> &_outPositions) const;
    void createSurfacePoints(const T _density, std::vector<Vec3<T>> &_outPositions) const;

    std::vector<Vec3<T>> lineIntersections(const Vec3<T> &_linePoint, const Vec3<T> &_lineNormal) const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    center = _position;
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
    return Math::isPositive<T>(radius);
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
    return Math::equals<T>(radius, _other.radius) && center.equals(_other.center);
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
    radius = T(0);
    center.clear();
}

/*!
 * \brief Returns sphere surface area \f$4 \pi r^2\f$
 * \tparam T Template floating point type
 * \return Sphere surface area
 */
template <typename T>
inline T Sphere<T>::surfaceArea() const
{
    return T(4.0l * M_PIl) * radius * radius;
}

/*!
 * \brief Returns sphere circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Sphere circle area
 */
template <typename T>
inline T Sphere<T>::circleArea() const
{
    return T(M_PIl) * radius * radius;
}

/*!
 * \brief Returns sphere circle area \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volume() const
{
    return T(M_PIl * 4.0l / 3.0l) * radius * radius * radius;
}

/*!
 * \brief Returns sphere volume cup area \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \param _height Cup height
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volumeCup(const T _height) const
{
    return T(M_PIl) * _height * _height * (T(3) * radius - _height) / T(3);
}

/*!
 * \brief Sphere line intersections
 * \param _linePoint Line point
 * \param _lineNormal Line normal
 * \return Intersection points
 */
template <typename T>
std::vector<Vec3<T>> Sphere<T>::lineIntersections(const Vec3<T> &_linePoint, const Vec3<T> &_lineNormal) const
{
    const Vec3<T> v = _lineNormal.normalized();
    const T A = Vec3<T>::dot(v, v);
    const T B = T(2) *
        (_linePoint.x * v.x + _linePoint.y * v.y + _linePoint.z * v.z - v.x * center.x - v.y * center.y -
         v.z * center.z);
    const T C = _linePoint.x * _linePoint.x - T(2) * _linePoint.x * center.x + center.x * center.x +
        _linePoint.y * _linePoint.y - T(2) * _linePoint.y * center.y + center.y * center.y +
        _linePoint.z * _linePoint.z - 2 * _linePoint.z * center.z + center.z * center.z - radius * radius;

    const T D = B * B - T(4) * A * C;
    if (Math::isNull(D))
        return {_linePoint + v * (-B / (T(2) * A))};
    else if (D < T(0))
        return {};

    const T SD = std::sqrt(D);
    const T t1 = (-B - SD) / (T(2) * A);
    const T t2 = (-B + SD) / (T(2) * A);

    if (Math::isMoreOrEqual(t1, t2))
        return {_linePoint + v * t1, _linePoint + v * t2};
    return {_linePoint + v * t2, _linePoint + v * t1};
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    return _os << "[R[" << _s.radius << ']' << _s.center << ']';
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Sphere<float> SphereF;        //!< 32 bit floating point precision sphere
typedef Sphere<double> SphereD;       //!< 64 bit floating point precision sphere
typedef Sphere<long double> SphereL;  //!< 128 bit floating point precision sphere

}  // namespace Math
}  // namespace U1

#endif  // MATH_SPHERE_H
