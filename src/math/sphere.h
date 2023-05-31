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
        : radius(T(0))
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

    static T surfaceAreaCup(const T _radius, const T _height);
    inline T surfaceAreaCup(const T _height) const;

    void createSpherePoints(std::vector<Vec3<T>> &_out, const size_t _latitudes, const size_t _longitudes) const;
    void createSphereNormals(std::vector<Vec3<T>> &_out, const size_t _latitudes, const size_t _longitudes) const;

    template <typename UI>
    void createSphereIndicesTriangles(std::vector<UI> &_out,
                                      const size_t _latitudes,
                                      const size_t _longitudes,
                                      const bool _counterClockWise = true) const;

    template <typename UI>
    void createSphereIndicesWireframe(std::vector<UI> &_out, const size_t _latitudes, const size_t _longitudes) const;
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
    radius = T(0);
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
 * \brief Returns sphere volume \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volume() const
{
    return Const::T_4PI_3<T>() * radius * radius * radius;
}

/*!
 * \brief Returns sphere cup volume \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \param _height Cup height
 * \return Sphere cup volume
 */
template <typename T>
inline T Sphere<T>::volumeCup(const T _height) const
{
    return Const::T_PI_3<T>() * _height * _height * (T(3) * radius - _height);
}

/*!
 * \brief Returns surface area of sphere cup - static version
 * \tparam T Template floating point type
 * \param _radius Sphere radius
 * \param _height Sphere cup height
 * \return Surface area of sphere cup
 */
template <typename T>
T Sphere<T>::surfaceAreaCup(const T _radius, const T _height)
{
    const T hr = _radius * _height;
    return Const::T_2PI<T>() * hr + Const::T_PI<T>() * (T(2) * hr - _height * _height);
}

/*!
 * \brief Returns surface area of sphere cup
 * \tparam T Template floating point type
 * \param _height Sphere cup height
 * \return Surface area of sphere cup
 */
template <typename T>
inline T Sphere<T>::surfaceAreaCup(const T _height) const
{
    return surfaceAreaCup(radius, _height);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create sphere points (sphere axis in \b Z direction)
 * \tparam T Template floating point type
 * \param _out Output point positions vector
 * \param _latitudes Latitudes count
 * \param _longitudes Longitudes count
 */
template <typename T>
void Sphere<T>::createSpherePoints(std::vector<Vec3<T>> &_out, const size_t _latitudes, const size_t _longitudes) const
{
    if (!isValid())
        return;

    const size_t la = std::max(1UL, _latitudes);
    const size_t lo = std::max(4UL, _longitudes);
    const size_t pointCount = 2UL + la * lo;

    const T angleLa = Const::T_PI<T>() / static_cast<T>(la + 1UL);
    const T angleLo = Const::T_2PI<T>() / static_cast<T>(lo);

    const T saLa = std::sin(angleLa);
    const T caLa = std::cos(angleLa);
    const T saLo = std::sin(angleLo);
    const T caLo = std::cos(angleLo);

    if (_out.size() != pointCount)
        _out.resize(pointCount);

    size_t i = 0UL;
    _out[i++].set(position.x, position.y, position.z + radius);

    Vec3<T> armLa = Vec3<T>::unitZ().rotated(Vec3<T>::unitY(), saLa, caLa).normalized();
    for (size_t sla = 0UL; sla < la; ++sla, armLa = armLa.rotated(Vec3<T>::unitY(), saLa, caLa).normalized())
    {
        Vec3<T> arm = armLa;
        for (size_t slo = 0UL; slo < lo; ++slo, arm = arm.rotated(Vec3<T>::unitZ(), saLo, caLo).normalized())
            _out[i++] = position + arm * radius;
    }

    _out[i].set(position.x, position.y, position.z - radius);
}

/*!
 * \brief Create sphere points normal (sphere axis in \b Z direction)
 * \tparam T Template floating point type
 * \param _out Output points normal vector
 * \param _latitudes Latitudes count
 * \param _longitudes Longitudes count
 */
template <typename T>
void Sphere<T>::createSphereNormals(std::vector<Vec3<T>> &_out, const size_t _latitudes, const size_t _longitudes) const
{
    if (!isValid())
        return;

    const size_t la = std::max(1UL, _latitudes);
    const size_t lo = std::max(4UL, _longitudes);
    const size_t pointCount = 2UL + la * lo;

    const T angleLa = Const::T_PI<T>() / static_cast<T>(la + 1UL);
    const T angleLo = Const::T_2PI<T>() / static_cast<T>(lo);

    const T saLa = std::sin(angleLa);
    const T caLa = std::cos(angleLa);
    const T saLo = std::sin(angleLo);
    const T caLo = std::cos(angleLo);

    if (_out.size() != pointCount)
        _out.resize(pointCount);

    size_t i = 0UL;
    _out[i++] = Vec3<T>::unitZ();

    Vec3<T> armLa = Vec3<T>::unitZ().rotated(Vec3<T>::unitY(), saLa, caLa).normalized();
    for (size_t sla = 0UL; sla < la; ++sla, armLa = armLa.rotated(Vec3<T>::unitY(), saLa, caLa).normalized())
    {
        Vec3<T> arm = armLa;
        for (size_t slo = 0UL; slo < lo; ++slo, arm = arm.rotated(Vec3<T>::unitZ(), saLo, caLo).normalized())
            _out[i++] = arm;
    }

    _out[i] = -Vec3<T>::unitZ();
}

/*!
 * \brief Create sphere triangle indices (for \b GL_TRIANGLES)
 * \tparam T Template floating point type
 * \tparam UI Template indices integer type
 * \param _out Output triangle indices
 * \param _latitudes Latitudes count
 * \param _longitudes Longitudes count
 * \param _counterClockWise Counter clockwise orientation flag
 */
template <typename T>
template <typename UI>
void Sphere<T>::createSphereIndicesTriangles(std::vector<UI> &_out,
                                             const size_t _latitudes,
                                             const size_t _longitudes,
                                             const bool _counterClockWise) const
{
    const size_t la = std::max(1UL, _latitudes);
    const size_t lo = std::max(4UL, _longitudes);
    const size_t indicesCount = lo * la * 6UL;
    const UI lastPointIdx = static_cast<UI>(2UL + la * lo - 1UL);

    if (_out.size() != indicesCount)
        _out.resize(indicesCount);

    size_t idx = 0UL;
    if (_counterClockWise)
    {
        for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
        {
            _out[idx++] = UI(0);
            _out[idx++] = static_cast<UI>(slo + 1UL);
            _out[idx++] = static_cast<UI>(slo + 2UL);
        }

        _out[idx++] = UI(0);
        _out[idx++] = static_cast<UI>(lo);
        _out[idx++] = UI(1);

        size_t tmp = 1UL;
        for (size_t sla = 0UL; sla < la - 1UL; ++sla)
        {
            for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
            {
                _out[idx++] = static_cast<UI>(tmp + slo);
                _out[idx++] = static_cast<UI>(tmp + slo + lo);
                _out[idx++] = static_cast<UI>(tmp + slo + lo + 1UL);

                _out[idx++] = static_cast<UI>(tmp + slo + lo + 1UL);
                _out[idx++] = static_cast<UI>(tmp + slo + 1UL);
                _out[idx++] = static_cast<UI>(tmp + slo);
            }

            _out[idx++] = static_cast<UI>(tmp + lo - 1UL);
            _out[idx++] = static_cast<UI>(tmp + lo - 1UL + lo);
            _out[idx++] = static_cast<UI>(tmp + lo);

            _out[idx++] = static_cast<UI>(tmp + lo);
            _out[idx++] = static_cast<UI>(tmp);
            _out[idx++] = static_cast<UI>(tmp + lo - 1UL);

            tmp += lo;
        }

        for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
        {
            _out[idx++] = lastPointIdx;
            _out[idx++] = static_cast<UI>(tmp + slo + 1UL);
            _out[idx++] = static_cast<UI>(tmp + slo);
        }
        _out[idx++] = lastPointIdx;
        _out[idx++] = static_cast<UI>(tmp);
        _out[idx++] = static_cast<UI>(tmp + lo - 1UL);
    }
    else
    {
        for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
        {
            _out[idx++] = UI(0);
            _out[idx++] = static_cast<UI>(slo + 2UL);
            _out[idx++] = static_cast<UI>(slo + 1UL);
        }

        _out[idx++] = UI(0);
        _out[idx++] = UI(1);
        _out[idx++] = static_cast<UI>(lo);

        size_t tmp = 1UL;
        for (size_t sla = 0UL; sla < la - 1UL; ++sla)
        {
            for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
            {
                _out[idx++] = static_cast<UI>(tmp + slo);
                _out[idx++] = static_cast<UI>(tmp + slo + lo + 1UL);
                _out[idx++] = static_cast<UI>(tmp + slo + lo);

                _out[idx++] = static_cast<UI>(tmp + slo + lo + 1UL);
                _out[idx++] = static_cast<UI>(tmp + slo);
                _out[idx++] = static_cast<UI>(tmp + slo + 1UL);
            }

            _out[idx++] = static_cast<UI>(tmp + lo - 1UL);
            _out[idx++] = static_cast<UI>(tmp + lo);
            _out[idx++] = static_cast<UI>(tmp + lo - 1UL + lo);

            _out[idx++] = static_cast<UI>(tmp + lo);
            _out[idx++] = static_cast<UI>(tmp + lo - 1UL);
            _out[idx++] = static_cast<UI>(tmp);

            tmp += lo;
        }

        for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
        {
            _out[idx++] = lastPointIdx;
            _out[idx++] = static_cast<UI>(tmp + slo);
            _out[idx++] = static_cast<UI>(tmp + slo + 1UL);
        }
        _out[idx++] = lastPointIdx;
        _out[idx++] = static_cast<UI>(tmp + lo - 1UL);
        _out[idx++] = static_cast<UI>(tmp);
    }
}

/*!
 * \brief Create sphere wire-frame indices (for \b GL_LINES)
 * \tparam T Template floating point type
 * \tparam UI Template indices integer type
 * \param _out Output sphere wire-frame indices
 * \param _latitudes Latitudes count
 * \param _longitudes Longitudes count
 */
template <typename T>
template <typename UI>
void Sphere<T>::createSphereIndicesWireframe(std::vector<UI> &_out,
                                             const size_t _latitudes,
                                             const size_t _longitudes) const
{
    const size_t la = std::max(1UL, _latitudes);
    const size_t lo = std::max(4UL, _longitudes);
    const size_t indicesCount = 2UL * lo * (2UL * la + 1UL);
    const UI lastPointIdx = static_cast<UI>(2UL + la * lo - 1UL);

    if (_out.size() != indicesCount)
        _out.resize(indicesCount);

    size_t idx = 0UL;
    size_t tmp = 1UL;
    for (size_t sla = 0UL; sla < la; ++sla)
    {
        for (size_t slo = 0UL; slo < lo - 1UL; ++slo)
        {
            _out[idx++] = static_cast<UI>(tmp + slo);
            _out[idx++] = static_cast<UI>(tmp + slo + 1UL);
        }
        _out[idx++] = static_cast<UI>(tmp + lo - 1UL);
        _out[idx++] = static_cast<UI>(tmp);
        tmp += lo;
    }

    for (size_t slo = 0UL; slo < lo; ++slo)
    {
        tmp = 1UL + slo;
        _out[idx++] = UI(0);
        _out[idx++] = static_cast<UI>(tmp);
        for (size_t sla = 0UL; sla < la - 1UL; ++sla, tmp += lo)
        {
            _out[idx++] = static_cast<UI>(tmp);
            _out[idx++] = static_cast<UI>(tmp + lo);
        }
        _out[idx++] = static_cast<UI>(tmp);
        _out[idx++] = lastPointIdx;
    }
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
