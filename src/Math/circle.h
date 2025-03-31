/*!
 * \file src/Math/camera.h
 * \brief 2D and 3D circle structure
 */

#ifndef MATH_CIRCLE_H
#define MATH_CIRCLE_H

#include "vec3.h"

namespace U1 {
namespace Math {

/*!
 * \brief 2D circle structure
 * \tparam T Template floating point type
 */
template <typename T>
struct Circle2
{
    Vec2<T> center;  //!< Circle center
    T radius;        //!< Circle radius

    /*! \brief Default constructor */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle2()
        : center()
        , radius(T(0))
    {
    }

    /*! \brief Constructor with circle components */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle2(const Vec3<T> &_center,  //!< Circle center
                   const T &_radius)        //!< Circle radius
        : center(_center)
        , radius(_radius)
    {
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return Math::mixHash(center.toHash(), std::hash<T>{}(radius));
    }

    inline bool isValid() const;

    inline void clear();

    inline T circumference() const;
    inline T area() const;

    inline Vec2<T> arm() const;

    Vec2<T> point(const T _angleRad) const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief 3D circle structure
 * \tparam T Template floating point type
 */
template <typename T>
struct Circle3
{
    Vec3<T> center;    //!< Circle center
    Vec3<T> normal;    //!< Circle normal (unit 3D vector)
    T radius;          //!< Circle radius

    /*! \brief Default constructor */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle3()
        : center()
        , normal()
        , radius(T(0))
    {
    }

    /*! \brief Constructor with circle components */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle3(const Vec3<T> &_center,  //!< Circle center
                   const Vec3<T> &_normal,  //!< Circle normal (unit 3D vector)
                   const T &_radius)        //!< Circle radius
        : center(_center)
        , normal(_normal)
        , radius(_radius)
    {
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return Math::mixHash(center.toHash(), normal.toHash(), std::hash<T>{}(radius));
    }

    inline bool isValid() const;

    inline void clear();

    inline T circumference() const;
    inline T area() const;

    inline Vec3<T> arm() const;

    Vec3<T> point(const T _angleRad) const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if circle is valid - has positive value of radius
 * \tparam T Template floating point type
 * \return \c true if circle is valid
 */
template <typename T>
inline bool Circle2<T>::isValid() const
{
    return Math::isPositive<T>(radius);
}

/*!
 * \brief Test if circle is valid - normal is unit vector and has positive value of radius
 * \tparam T Template floating point type
 * \return \c true if circle is valid
 */
template <typename T>
inline bool Circle3<T>::isValid() const
{
    return Math::isPositive<T>(radius) && normal.isNormalized();
}

/*!
 * \brief Clear circle
 * \tparam T Template floating point type
 */
template <typename T>
inline void Circle2<T>::clear()
{
    center.clear();
    radius = T(0);
}

/*!
 * \brief Clear circle
 * \tparam T Template floating point type
 */
template <typename T>
inline void Circle3<T>::clear()
{
    center.clear();
    normal.clear();
    radius = T(0);
}

/*!
 * \brief Returns circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle2<T>::area() const
{
    return T(M_PIl) * radius * radius;
}

/*!
 * \brief Returns circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle3<T>::area() const
{
    return T(M_PIl) * radius * radius;
}

/*!
 * \brief Returns circle area \f$2 \pi r\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle2<T>::circumference() const
{
    return T(M_PIl * 2.0l) * radius;
}

/*!
 * \brief Returns circle area \f$2 \pi r\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle3<T>::circumference() const
{
    return T(M_PIl * 2.0l) * radius;
}

/*!
 * \brief Returns base circle arm vector (unit X vector)
 * \tparam T Template floating point type
 * \return Base circle arm vector (unit X vector)
 */
template <typename T>
inline Vec2<T> Circle2<T>::arm() const
{
    return Vec2<T>::unitX();
}

/*!
 * \brief Returns base circle arm vector
 * \tparam T Template floating point type
 * \return Base circle arm vector
 * \details Circle \b arm is vector of length that equals radius and pointing to one circle curve point.
 * All circle curve points can by defined by rotating \b arm vector around \b normal vector.
 * \sa Vec3<T>::perpendicularNormal<T>() const
 */
template <typename T>
inline Vec3<T> Circle3<T>::arm() const
{
    return normal.perpendicularNormal();
}

/*!
 * \brief Returns point on circle, that is created by rotating circle \b arm by given angle
 * \tparam T Template floating point type
 * \param _angleRad Arm rotation angle in radians
 * \return Point on circle
 */
template <typename T>
Vec2<T> Circle2<T>::point(const T _angleRad) const
{
    return Vec2<T>(center.x + std::cos(_angleRad) * radius, center.y + std::sin(_angleRad) * radius);
}

/*!
 * \brief Returns point on circle, that is created by rotating circle \b arm by given angle
 * \tparam T Template floating point type
 * \param _angleRad Arm rotation angle in radians
 * \return Point on circle
 */
template <typename T>
Vec3<T> Circle3<T>::point(const T _angleRad) const
{
    return center + arm().rotated(normal, _angleRad) * radius;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _c Circle
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Circle2<T> &_c)
{
    return _os << "[R[" << _c.radius << "]P" << _c.center << ']';
}

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _c Circle
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Circle3<T> &_c)
{
    return _os << "[R[" << _c.radius << "]P" << _c.center << 'N' << _c.normal << ']';
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Circle2<float> Circle2F;        //!< 32 bit floating point precision 2D circle
typedef Circle2<double> Circle2D;       //!< 64 bit floating point precision 2D circle
typedef Circle2<long double> Circle2L;  //!< 128 bit floating point precision 2D circle

typedef Circle3<float> Circle3F;        //!< 32 bit floating point precision 3D circle
typedef Circle3<double> Circle3D;       //!< 64 bit floating point precision 3D circle
typedef Circle3<long double> Circle3L;  //!< 128 bit floating point precision 3D circle

}  // namespace Math
}  // namespace U1

#endif  // MATH_CIRCLE_H
