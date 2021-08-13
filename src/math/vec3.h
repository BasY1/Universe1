/*!
 * \file math/vec3.h
 * \author Michal Steller
 * \brief 3D vector template implementation
 */

#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "texttools.h"
#include "type.h"

namespace Universe1 {
namespace Math {

/*!
 * \defgroup TypeAngles Angle tools
 * \brief Angle conversion tools
 * \{
 */

/*!
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param degValue Value to convert
 * \returns Angle in radians
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T toRad(const T degValue)
{
    return degValue / Const::T_RadInDeg<T>();
}

/*!
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param radValue Value to convert
 * \returns Angle in radians
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T toDeg(const T radValue)
{
    return radValue * Const::T_RadInDeg<T>();
}

/*!
 * \brief 3D vector template for various floating point types
 * \tparam T Template floating point type
 */
template <typename T>
struct Vec3
{
    /*! \brief The anonymous union, for indexed component access or access by component name */
    union
    {
        /*!
         * \brief Union array representation, access vector component by axis index
         * \details
         * | Index | Component  |
         * | :---- | :--------- |
         * | 0     | Position X |
         * | 1     | Position Y |
         * | 2     | Position Z |
         */
        T m_data[3];

        /*! \brief The anonymous structure, access vector component by axis name */
        struct
        {
            T x;  //!< Union \b X axis (first) component representation
            T y;  //!< Union \b Y axis (second) component representation
            T z;  //!< Union \b Z axis (third) component representation
        };
    };

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec3()
        : x(Const::T_0<T>())
        , y(Const::T_0<T>())
        , z(Const::T_0<T>())
    {
    }

    /*!
     * \brief Constructor with vector components
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec3(const T _x,  //!< X component
                const T _y,  //!< Y component
                const T _z)  //!< Z component
        : x(_x)
        , y(_y)
        , z(_z)
    {
    }

    /*!
     * \brief Constructor from other vector
     * \param other Other vector
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec3(const Vec3<T> &other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
    {
    }

    inline bool isNull() const;
    inline bool equals(const Vec3<T> &other) const;
    inline bool operator==(const Vec3<T> &other) const;
    inline bool operator!=(const Vec3<T> &other) const;

    inline void clear();

    inline Vec3<T> &operator+=(const Vec3<T> &value);
    inline Vec3<T> &operator-=(const Vec3<T> &value);
    inline Vec3<T> &operator*=(const T value);
    inline Vec3<T> &operator/=(const T value);

    inline Vec3<T> inverted() const;
    inline void invert();

    inline bool isNormalized() const;
    inline Vec3<T> normalized() const;
    inline void normalize();

    inline bool isPerpendicular(const Vec3<T> &other) const;
    inline Vec3<T> perpendicularNormal() const;

    inline bool isSameDir(const Vec3<T> &other) const;
    inline bool isParallel(const Vec3<T> &other) const;
    inline bool isParallelInDir(const Vec3<T> &other, bool &isSameDirection) const;

    static T dot(const Vec3<T> &v1, const Vec3<T> &v2);

    static Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2);
    static Vec3<T> crossLeftHand(const Vec3<T> &v1, const Vec3<T> &v2);
    static Vec3<T> crossByHand(const Vec3<T> &v1, const Vec3<T> &v2, const bool rightHanded);

    inline T lengthSquared() const;
    inline T length() const;

    inline T sum() const;

    inline T distanceToPoint(const Vec3<T> &point) const;
    inline T distanceToLine(const Vec3<T> &linePoint, const Vec3<T> &lineNormal) const;
    inline T distanceToPlane(const Vec3<T> &planePoint, const Vec3<T> &planeNormal) const;

    inline T projectedLength(const Vec3<T> &projDirection) const;
    inline Vec3<T> projected(const Vec3<T> &projDirection) const;
    inline Vec3<T> projectedOnPlane(const Vec3<T> &planeNormal) const;

    inline T cosAngle(const Vec3<T> &v) const;
    inline T cosAnglePow2(const Vec3<T> &v) const;

    inline T sinAngle(const Vec3<T> &v) const;
    inline T sinAnglePow2(const Vec3<T> &v) const;

    inline T angleRad(const Vec3<T> &v) const;
    inline T angleDeg(const Vec3<T> &v) const;

    inline T angleNormRad(const Vec3<T> &v, const Vec3<T> &normal) const;
    inline T angleNormDeg(const Vec3<T> &v, const Vec3<T> &normal) const;

    static Vec3<T> rotate(const Vec3<T> &point, const Vec3<T> &normal, const T angleRad);
    inline Vec3<T> rotated(const Vec3<T> &normal, const T angleRad) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is null
 * \tparam T Template floating point type
 * \returns \c true if vector is null
 */
template <typename T>
inline bool Vec3<T>::isNull() const
{
    return Type::isNull<T>(x) && Type::isNull<T>(y) && Type::isNull<T>(z);
}

/*!
 * \brief Test if vectors are equal
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns \c true if vectors are equal
 * \sa TypeEquals<T>(const T, const T)
 */
template <typename T>
inline bool Vec3<T>::equals(const Vec3<T> &other) const
{
    return Type::equals<T>(x, other.x) && Type::equals<T>(y, other.y) && Type::equals<T>(z, other.z);
}

/*!
 * \brief Operator for test if vectors are equal
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns \c true if vectors are equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T> &other) const
{
    return equals(other);
}

/*!
 * \brief Operator for test if vectors are not equal
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns \c true if vectors are not equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T> &other) const
{
    return !equals(other);
}

/*!
 * \brief Clear vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec3<T>::clear()
{
    x = Const::T_0<T>();
    y = Const::T_0<T>();
    z = Const::T_0<T>();
}

/*!
 * \brief Add other vector
 * \tparam T Template floating point type
 * \param value Other vector
 * \returns \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &value)
{
    x += value.x;
    y += value.y;
    z += value.z;
    return *this;
}

/*!
 * \brief Subtract other vector
 * \tparam T Template floating point type
 * \param value Other vector
 * \returns \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &value)
{
    x -= value.x;
    y -= value.y;
    z -= value.z;
    return *this;
}

/*!
 * \brief Multiply vector by value
 * \tparam T Template floating point type
 * \param value Other vector
 * \returns \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator*=(const T value)
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

/*!
 * \brief Divide vector by value
 * \tparam T Template floating point type
 * \param value Other vector
 * \returns \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator/=(const T value)
{
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sum operator for two vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \returns Sum vectors
 */
template <typename T>
inline Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return Vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Subtract operator for two vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \returns Subtract vectors
 */
template <typename T>
inline Vec3<T> operator-(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return Vec3<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

/*!
 * \brief Inverted operator
 * \tparam T Template floating point type
 * \param v Vector
 * \returns Inverted vector
 */
template <typename T>
inline Vec3<T> operator-(const Vec3<T> &v)
{
    return v.inverted();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Multiply operator for vector by value
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second value
 * \returns Multiply of vector by value
 */
template <typename T>
inline Vec3<T> operator*(const Vec3<T> &v1, const T v2)
{
    return Vec3<T>(v1.x * v2, v1.y * v2, v1.z * v2);
}

/*!
 * \brief Multiply operator for value by vector
 * \tparam T Template floating point type
 * \param v1 First value
 * \param v2 Second vector
 * \returns Multiply of value by vector
 */
template <typename T>
inline Vec3<T> operator*(const T v1, const Vec3<T> &v2)
{
    return Vec3<T>(v1 * v2.x, v1 * v2.y, v1 * v2.z);
}

/*!
 * \brief Divide operator for vector by value
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second value
 * \returns Divide of vector by value
 */
template <typename T>
inline Vec3<T> operator/(const Vec3<T> &v1, const T v2)
{
    return Vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns inverted vector
 * \tparam T Template floating point type
 * \returns Inverted vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::inverted() const
{
    return Vec3<T>(-x, -y, -z);
}

/*!
 * \brief Inverts this vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec3<T>::invert()
{
    x = -x;
    y = -y;
    z = -z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is normalized (length equals 1)
 * \tparam T Template floating point type
 * \returns \c true if vector is normalized
 */
template <typename T>
inline bool Vec3<T>::isNormalized() const
{
    return Type::isUnit<T>(lengthSquared());
}

/*!
 * \brief Returns normalized vector
 * \tparam T Template floating point type
 * \returns Normalized vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::normalized() const
{
    const T lenSq = lengthSquared();
    if (Type::isNull<T>(lenSq) || Type::isUnit<T>(lenSq))
        return Vec3<T>(x, y, z);
    return *this / std::sqrt(lenSq);
}

/*!
 * \brief Normalize this vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec3<T>::normalize()
{
    const T lenSq = lengthSquared();
    if (!Type::isNull<T>(lenSq) && !Type::isUnit<T>(lenSq))
        *this /= std::sqrt(lenSq);
}

/*!
 * \brief Test if other vector is perpendicular to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns \c true if vectors are perpendicular
 */
template <typename T>
inline bool Vec3<T>::isPerpendicular(const Vec3<T> &other) const
{
    return Type::isNull<T>(Vec3<T>::dot(*this, other));
}

/*!
 * \brief Returns normalized vector that is perpendicular to this vector
 * \tparam T Template floating point type
 * \returns Normalized perpendicular vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::perpendicularNormal() const
{
    static const Vec3<T> n1(Const::T_1<T>(), Const::T_0<T>(), Const::T_0<T>());
    static const Vec3<T> n2(Const::T_0<T>(), Const::T_1<T>(), Const::T_0<T>());
    return (isParallel(n1) ? Vec3<T>::cross(*this, n2).normalized() : Vec3<T>::cross(*this, n1).normalized());
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isSameDir(const Vec3<T> &other) const
{
    return !isNull() && normalized() == other.normalized();
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isParallel(const Vec3<T> &other) const
{
    const Vec3<T> n1 = normalized();
    const Vec3<T> n2 = other.normalized();
    return !n1.isNull() && (n1 == n2 || n1 == -n2);
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \param[out] isSameDirection Output is same direction flag
 * \returns \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isParallelInDir(const Vec3<T> &other, bool &isSameDirection) const
{
    if (isNull() || other.isNull())
    {
        isSameDirection = false;
        return false;
    }
    const Vec3<T> n1 = normalized();
    const Vec3<T> n2 = other.normalized();
    isSameDirection = (n1 == n2);
    return isSameDirection || (n1 == -n2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Dot product of two 3D vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \returns Dot product of two 3D vectors
 */
template <typename T>
T Vec3<T>::dot(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Right handed cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \returns Right handed cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return Vec3<T>(v1.y * v2.z - v1.z * v2.y,   //
                   v1.z * v2.x - v1.x * v2.z,   //
                   v1.x * v2.y - v1.y * v2.x);  //
}

/*!
 * \brief Left handed cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \returns Left handed cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::crossLeftHand(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return Vec3<T>(v1.z * v2.y - v1.y * v2.z,   //
                   v1.x * v2.z - v1.z * v2.x,   //
                   v1.y * v2.x - v1.x * v2.y);  //
}

/*!
 * \brief Oriented cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \param rightHanded Hand rule orientation
 * \returns Oriented cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::crossByHand(const Vec3<T> &v1, const Vec3<T> &v2, const bool rightHanded)
{
    return rightHanded ? cross(v1, v2) : crossLH(v1, v2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns vectors length squared
 * \tparam T Template floating point type
 * \returns Vectors length squared
 */
template <typename T>
inline T Vec3<T>::lengthSquared() const
{
    return dot(*this, *this);
}

/*!
 * \brief Returns vectors length
 * \tparam T Template floating point type
 * \returns Vectors length
 */
template <typename T>
inline T Vec3<T>::length() const
{
    return std::sqrt(lengthSquared());
}

/*!
 * \brief Returns sum of vector components
 * \tparam T Template floating point type
 * \returns Sum of vector components
 */
template <typename T>
inline T Vec3<T>::sum() const
{
    return x + y + z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns distance to point
 * \tparam T Template floating point type
 * \param point Other point
 * \returns Distance to point
 */
template <typename T>
inline T Vec3<T>::distanceToPoint(const Vec3<T> &point) const
{
    return (*this - point).length();
}

/*!
 * \brief Returns distance to line
 * \tparam T Template floating point type
 * \param linePoint Line point
 * \param lineNormal Line normal
 * \returns Distance to line
 */
template <typename T>
inline T Vec3<T>::distanceToLine(const Vec3<T> &linePoint, const Vec3<T> &lineNormal) const
{
    const T lenSq = lineNormal.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Const::T_0<T>();  // distanceToPoint(linePoint);
    const T tmp = cross(*this - linePoint, *this - linePoint - lineNormal).length();
    return Type::isUnit<T>(lenSq) ? tmp : (tmp / std::sqrt(lenSq));
}

/*!
 * \brief Returns distance to plane
 * \tparam T Template floating point type
 * \param planePoint Plane point
 * \param planeNormal Plane normal
 * \returns Distance to plane
 */
template <typename T>
inline T Vec3<T>::distanceToPlane(const Vec3<T> &planePoint, const Vec3<T> &planeNormal) const
{
    const T lenSq = planeNormal.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Const::T_0<T>();
    if (Type::isUnit<T>(lenSq))
        return dot(*this - planePoint, planeNormal);
    return dot(*this - planePoint, planeNormal) / std::sqrt(lenSq);
}

/*!
 * \brief Returns length of projection to other vector
 * \tparam T Template floating point type
 * \param projDirection Projection direction
 * \returns Length of projection to other vector
 * \note Opposite directions have negative values
 */
template <typename T>
inline T Vec3<T>::projectedLength(const Vec3<T> &projDirection) const
{
    const T lenSq = projDirection.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Const::T_0<T>();
    if (Type::isUnit<T>(lenSq))
        return dot(*this, projDirection);
    return dot(*this, projDirection) / std::sqrt(lenSq);
}

/*!
 * \brief Returns projection to other vector
 * \tparam T Template floating point type
 * \param projDirection Projection direction
 * \returns Projection of this vector to other vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::projected(const Vec3<T> &projDirection) const
{
    const T lenSq = projDirection.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Vec3<T>();
    if (Type::isUnit<T>(lenSq))
        return projDirection * dot(*this, projDirection);
    return projDirection * (dot(*this, projDirection) / std::sqrt(lenSq));
}

/*!
 * \brief Returns projection on plane defined by normal
 * \tparam T Template floating point type
 * \param planeNormal Plane normal
 * \returns Projection of this vector to other plane
 */
template <typename T>
inline Vec3<T> Vec3<T>::projectedOnPlane(const Vec3<T> &planeNormal) const
{
    return *this - projected(planeNormal);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Co-sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns Co-sinus of angle between this and other 3D vector
 * \details Used equation:
 * \f$\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}}\f$
 */
template <typename T>
inline T Vec3<T>::cosAngle(const Vec3<T> &other) const
{
    const T lenSq = lengthSquared() * other.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Const::T_0<T>();
    if (Type::isUnit<T>(lenSq))
        return dot(*this, other);
    return dot(*this, other) / std::sqrt(lenSq);
}

/*!
 * \brief <b>Power 2</b> of cosinus angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns <b>Power 2</b> of cosinus angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::cosAnglePow2(const Vec3<T> &other) const
{
    const T lenSq = lengthSquared() * other.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Const::T_0<T>();
    const T result = dot(*this, other);
    if (Type::isUnit<T>(lenSq))
        return result * result;
    return result * result / lenSq;
}

/*!
 * \brief Sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns Sinus of angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::sinAngle(const Vec3<T> &other) const
{
    return std::sqrt(sinAnglePow2(other));
}

/*!
 * \brief Sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns Sinus of angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::sinAnglePow2(const Vec3<T> &other) const
{
    return Const::T_1<T>() - cosAnglePow2(other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Angle between this and other 3D vector in radians
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns Angle between this and other 3D vector in radians
 * \note Result angle range: \f$\langle 0, \pi \rangle\f$
 * \details Used equation:
 * \f$acos(\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}})\f$
 */
template <typename T>
inline T Vec3<T>::angleRad(const Vec3<T> &other) const
{
    const T lenSq = lengthSquared() * other.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Const::T_0<T>();
    T result = dot(*this, other);
    if (!Type::isUnit<T>(lenSq))
        result /= std::sqrt(lenSq);
    return std::acos(std::min(Const::T_1<T>(), std::max(-Const::T_1<T>(), result)));
}

/*!
 * \brief Angle between this and other 3D vector in degrees
 * \tparam T Template floating point type
 * \param other Other vector
 * \returns Angle between this and other 3D vector in degrees
 * \note Result angle range: \f$\langle 0, 180 \rangle\f$ degrees
 */
template <typename T>
inline T Vec3<T>::angleDeg(const Vec3<T> &other) const
{
    return toDeg<T>(angleRad(other));
}

/*!
 * \brief Angle between this and other 3D vector in radians
 * \tparam T Template floating point type
 * \param other Other vector
 * \param normal Normal vector
 * \returns Angle between this and other 3D vector in radians
 * \note Returned angle is in range \f$( -\pi, pi \rangle\f$
 */
template <typename T>
inline T Vec3<T>::angleNormRad(const Vec3<T> &other, const Vec3<T> &normal) const
{
    const T result = angleRad(other);
    return Vec3<T>::dot(normal, Vec3<T>::cross(*this, other)) < Const::T_0<T>() ? -result : result;
}

/*!
 * \brief Angle between this and other 3D vector in degrees
 * \tparam T Template floating point type
 * \param v Other vector
 * \param normal Normal vector
 * \returns Angle between this and other 3D vector in degrees
 * \note Result angle range: \f$( -180, 180 \rangle\f$ degrees
 */
template <typename T>
inline T Vec3<T>::angleNormDeg(const Vec3<T> &v, const Vec3<T> &normal) const
{
    return toDeg<T>(angleNormRad(v, normal));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns rotated point around normal by angle (right-handed rotation)
 * \tparam T Template floating point type
 * \param point Point to rotate
 * \param normal Rotation normal (axis)
 * \param angleRad Angle in radians
 * \returns Rotated point around normal by angle
 */
template <typename T>
Vec3<T> Vec3<T>::rotate(const Vec3<T> &point, const Vec3<T> &normal, const T angleRad)
{
    const T lenSq = normal.lengthSquared();
    if (Type::isNull<T>(lenSq))
        return Vec3<T>(point);

    const T sa = std::sin(angleRad);
    const T ca = std::cos(angleRad);
    const Vec3<T> n = Type::isUnit<T>(lenSq) ? normal : (normal / std::sqrt(lenSq));
    const Vec3<T> u = n.x * point;
    const Vec3<T> v = n.y * point;
    const Vec3<T> w = n.z * point;
    return Vec3<T>(n.x * u.x + sa * (v.z - w.y) + ca * point.x * (n.y * n.y + n.z * n.z),
                   n.y * v.y + sa * (w.x - u.z) + ca * point.y * (n.x * n.x + n.z * n.z),
                   n.z * w.z + sa * (u.y - v.x) + ca * point.z * (n.x * n.x + n.y * n.y));
}

/*!
 * \brief Returns rotated point around normal by angle in radians
 * \tparam T Template floating point type
 * \param normal Rotation normal (axis)
 * \param angleRad Angle in radians
 * \returns Rotated point around normal by angle
 */
template <typename T>
inline Vec3<T> Vec3<T>::rotated(const Vec3<T> &normal, const T angleRad) const
{
    return Vec3<T>::rotate(*this, normal, angleRad);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param os Output text stream
 * \param v Vector
 * \returns Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &os, const Vec3<T> &v)
{
    return os << '[' << v.x << 'x' << v.y << 'x' << v.z << ']';
}

}  // namespace Math
}  // namespace Universe1

#endif  // MATH_VEC3_H
