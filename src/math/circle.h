/*!
 * \file math/circle.h
 * \author Michal Steller
 * \brief 3D Circle template implementation
 */

#ifndef UNIVERSE1_MATH_CIRCLE_H
#define UNIVERSE1_MATH_CIRCLE_H

#include "constellation.h"

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
        : radius(T(0))
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

    void createCirclePoints(std::vector<Vec3<T>> &_out, const size_t _pointCount) const;
    void createArcPoints(std::vector<Vec3<T>> &_out,
                         const T _angleStartRad,
                         const T _angleArcRad,
                         const size_t _pointCount) const;

    static Circle<T> fromPoints(const Vec3<T> &_p1, const Vec3<T> &_p2, const Vec3<T> &_p3, bool *_outOk = nullptr);
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
    radius = T(0);
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

/*!
 * \brief Fills vector with points on this circle
 * \tparam T Template floating point type
 * \param _out Output point positions vector
 * \param _pointCount Required point count
 */
template <typename T>
void Circle<T>::createCirclePoints(std::vector<Vec3<T>> &_out, const size_t _pointCount) const
{
    if (_pointCount == 0UL || !isValid())
        return;

    const T angleStepRad = Const::T_2PI<T>() / static_cast<T>(_pointCount);
    const T angleStepSin = std::sin(angleStepRad);
    const T angleStepCos = std::cos(angleStepRad);

    Vec3<T> a = normal.perpendicularNormal();

    if (_out.empty())
    {
        _out.reserve(_pointCount);
        for (size_t i = 0UL; i < _pointCount; ++i, a = a.rotated(normal, angleStepSin, angleStepCos).normalized())
            _out.push_back(position + a * radius);
    }
    else
    {
        if (_out.size() != _pointCount)
            _out.resize(_pointCount);
        for (size_t i = 0UL; i < _pointCount; ++i, a = a.rotated(normal, angleStepSin, angleStepCos).normalized())
            _out[i] = (position + a * radius);
    }
}

/*!
 * \brief Fills vector with points on this circle within given arc
 * \tparam T Template floating point type
 * \param _out Output point positions vector
 * \param _angleStartRad Start angle in radians
 * \param _angleArcRad Total arc angle in radians
 * \param _pointCount Required point count
 */
template <typename T>
void Circle<T>::createArcPoints(std::vector<Vec3<T>> &_out,
                                const T _angleStartRad,
                                const T _angleArcRad,
                                const size_t _pointCount) const
{
    if (_pointCount == 0UL || !isValid())
        return;

    Vec3<T> a = normal.perpendicularNormal();
    a = a.rotated(normal, _angleStartRad).normalized();

    if (_out.size() != _pointCount)
        _out.resize(_pointCount);

    if (_pointCount == 1UL)
    {
        _out.front() = (position + a * radius);
        return;
    }

    const T angleStepRad = _angleArcRad / static_cast<T>(_pointCount - 1UL);
    const T angleStepSin = std::sin(angleStepRad);
    const T angleStepCos = std::cos(angleStepRad);

    for (size_t i = 0UL; i < _pointCount; ++i, a = a.rotated(normal, angleStepSin, angleStepCos).normalized())
        _out[i] = (position + a * radius);
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

/*!
 * \brief Create circle from 3 points
 * \tparam T Template floating point type
 * \param _p1 1. point
 * \param _p2 2. point
 * \param _p3 3. point
 * \param _outOk Success flag
 * \return Calculated circle object
 */
template <typename T>
Circle<T> Circle<T>::fromPoints(const Vec3<T> &_p1, const Vec3<T> &_p2, const Vec3<T> &_p3, bool *_outOk)
{
    const Vec3<T> t = _p2 - _p1;
    const Vec3<T> u = _p3 - _p1;
    const Vec3<T> v = _p3 - _p2;

    if (t.isNull() || u.isNull() || v.isNull())
    {
        if (_outOk != nullptr)
            *_outOk = false;
        return Circle<T>();
    }

    const Vec3<T> w = Vec3<T>::cross(t, u);
    const T wsl = Vec3<T>::dot(w, w);
    if (isNull<T>(wsl))
    {
        if (_outOk != nullptr)
            *_outOk = false;
        return Circle<T>();
    }

    const T iwsl2 = T(1) / (T(2) * wsl);
    const T tt = Vec3<T>::dot(t, t);
    const T uu = Vec3<T>::dot(u, u);

    if (_outOk != nullptr)
        *_outOk = true;

    return Circle<T>(std::sqrt(tt * uu * (Vec3<T>::dot(v, v)) * iwsl2 * T(0.5)),
                     _p1 + (u * tt * (Vec3<T>::dot(u, v)) - t * uu * (Vec3<T>::dot(t, v))) * iwsl2,
                     w / std::sqrt(wsl));
}

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_CIRCLE_H
