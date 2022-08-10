/*!
 * \file math/circle.h
 * \author Michal Steller
 * \brief 3D Circle template implementation
 */

#ifndef UNIVERSE1_MATH_CIRCLE_H
#define UNIVERSE1_MATH_CIRCLE_H

#include "vec3.h"

namespace Universe1 {
namespace Math {

/*!
 * \brief 3D Circle representation
 * \tparam T Template floating point type
 */
template <typename T>
struct Circle
{
    T radius;          //!< Circle radius
    Vec3<T> position;  //!< Circle position
    Vec3<T> normal;    //!< Circle normal (unit 3D vector)

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle()
        : radius(Const::T_0<T>())
        , position()
        , normal()
    {
    }

    /*!
     * \brief Constructor with circle components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle(const T &_radius,          //!< Circle radius
                  const Vec3<T> &_position,  //!< Circle position
                  const Vec3<T> &_normal)    //!< Circle normal (unit 3D vector)
        : radius(_radius)
        , position(_position)
        , normal(_normal)
    {
    }

    inline bool isValid() const;

    inline void clear();

    inline T length() const;
    inline T area() const;

    inline Vec3<T> arm() const;

    //
    Vec3<T> point(const T _angleRad) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if circle is valid - normal is unit vector and arm is not null
 * \tparam T Template floating point type
 * \return \c true if circle is valid
 */
template <typename T>
inline bool Circle<T>::isValid() const
{
    return isPositive<T>(radius) && normal.isNormalized();
}

/*!
 * \brief Clear circle
 * \tparam T Template floating point type
 */
template <typename T>
inline void Circle<T>::clear()
{
    radius = Const::T_0<T>();
    position.clear();
    normal.clear();
}

/*!
 * \brief Returns circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle<T>::area() const
{
    return Const::T_PI<T>() * radius * radius;
}

/*!
 * \brief Returns circle area \f$2 \pi r\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle<T>::length() const
{
    return Const::T_2PI<T>() * radius;
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
inline Vec3<T> Circle<T>::arm() const
{
	return radius * normal.perpendicularNormal();
}

/*!
 * \brief Returns point position on circle, that is created by rotating circle \b arm by given angle
 * \tparam T Template floating point type
 * \param _angleRad Arm rotation angle in radians
 * \return Circle point position
 */
template <typename T>
Vec3<T> Circle<T>::point(const T _angleRad) const
{
    return position + arm().rotated(normal, _angleRad);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _c Circle
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Circle<T> &_c)
{
    return _os << "[R[" << _c.radius << "]P" << _c.position << 'N' << _c.normal << ']';
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_CIRCLE_H
