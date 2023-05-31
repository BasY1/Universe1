/*!
 * \file math/vec3.h
 * \author Michal Steller
 * \brief 3D vector template implementation
 */

#ifndef UNIVERSE1_MATH_VEC3_H
#define UNIVERSE1_MATH_VEC3_H

#include "vec2.h"

#ifdef UNIVERSE1_USE_QT_LIB
#include <QColor>
#include <QVector3D>
#endif

namespace Universe1 {
namespace Math {

template <typename T>
struct Quaternion;

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
        : x(T(0))
        , y(T(0))
        , z(T(0))
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
     * \param _other Other vector
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec3(const Vec3<T> &_other)
        : x(_other.x)
        , y(_other.y)
        , z(_other.z)
    {
    }

#ifdef UNIVERSE1_USE_QT_LIB
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec3(const QVector3D &_other)
        : x(_other.x())
        , y(_other.y())
        , z(_other.z())
    {
    }
#endif

    static Vec3<T> unitX();
    static Vec3<T> unitY();
    static Vec3<T> unitZ();

    inline bool isNull() const;
    inline bool equals(const Vec3<T> &_other) const;
    inline bool operator==(const Vec3<T> &_other) const;
    inline bool operator!=(const Vec3<T> &_other) const;

    inline void clear();

    inline Vec3<T> &operator+=(const Vec3<T> &_value);
    inline Vec3<T> &operator-=(const Vec3<T> &_value);
    inline Vec3<T> &operator*=(const T _value);
    inline Vec3<T> &operator/=(const T _value);

    inline Vec3<T> inverted() const;
    inline void invert();

    inline bool isNormalized() const;
    inline Vec3<T> normalized() const;
    inline void normalize();

    inline bool isPerpendicular(const Vec3<T> &_other) const;
    inline Vec3<T> perpendicularNormal() const;
    static void makePerpendicularNormals(Vec3<T> &_normal1, Vec3<T> &_normal2);

    inline bool isSameDir(const Vec3<T> &_other) const;
    inline bool isParallel(const Vec3<T> &_other) const;
    inline bool isParallelInDir(const Vec3<T> &_other, bool &_isSameDirection) const;

    static T dot(const Vec3<T> &_v1, const Vec3<T> &_v2);

    static Vec3<T> cross(const Vec3<T> &_v1, const Vec3<T> &_v2);
    static Vec3<T> crossLeftHand(const Vec3<T> &_v1, const Vec3<T> &_v2);
    static Vec3<T> crossByHand(const Vec3<T> &_v1, const Vec3<T> &_v2, const bool _rightHanded);

    inline T lengthSquared() const;
    inline T length() const;

    inline T sum() const;

    inline T distanceToPoint(const Vec3<T> &_point) const;
    inline T distanceToLine(const Vec3<T> &_linePoint, const Vec3<T> &_lineNormal) const;
    inline T distanceToPlane(const Vec3<T> &_planePoint, const Vec3<T> &_planeNormal) const;

    inline T projectedLength(const Vec3<T> &_projDirection) const;
    inline Vec3<T> projected(const Vec3<T> &_projDirection) const;
    inline Vec3<T> projectedOnPlane(const Vec3<T> &_planeNormal) const;

    static Vec3<T> planeLineIntersection(const Vec3<T> &_planePoint,
                                         const Vec3<T> &_planeNormal,
                                         const Vec3<T> &_linePoint,
                                         const Vec3<T> &_lineNormal,
                                         bool *_outOk = nullptr);

    inline T cosAngle(const Vec3<T> &_v) const;
    inline T cosAnglePow2(const Vec3<T> &_v) const;

    inline T sinAngle(const Vec3<T> &_v) const;
    inline T sinAnglePow2(const Vec3<T> &_v) const;

    inline T angleRad(const Vec3<T> &_v) const;
    inline T angleDeg(const Vec3<T> &_v) const;

    inline T angleNormRad(const Vec3<T> &_v, const Vec3<T> &_normal) const;
    inline T angleNormDeg(const Vec3<T> &_v, const Vec3<T> &_normal) const;

    static Vec3<T> rotate(const Vec3<T> &_point, const Vec3<T> &_normal, const T _sinAngle, const T _cosAngle);
    static Vec3<T> rotate(const Vec3<T> &_point, const Vec3<T> &_normal, const T _angleRad);
    inline Vec3<T> rotated(const Vec3<T> &_normal, const T _sinAngle, const T _cosAngle) const;
    inline Vec3<T> rotated(const Vec3<T> &_normal, const T _angleRad) const;

    static Vec3<T>
    ratio(const Vec3<T> &_v1, const Vec3<T> &_v2, const T _value1, const T _value2, const T _valueCenter);

    inline bool isValidColor() const;

    inline Vec2<T> toVec2(const uint8_t _skipAxis = 2U) const;

    inline std::string toString(const int _decimals = -1) const;
    inline std::string toStringFull(const int _decimals = -1) const;

#ifdef UNIVERSE1_USE_QT_LIB

    inline QVector3D toQVector3D() const;
    static Vec3<T> fromQVector3D(const QVector3D &_value);

    inline QColor toQColor() const;
    static Vec3<T> fromQColor(const QColor _value);

    inline QString toQString(const int _decimals = -1) const;
    inline QString toQStringFull(const int _decimals = -1) const;

#endif

    /*!
     * \brief Conversion to different precision
     * \tparam T2 Output template floating point type
     * \return Vector in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    inline Vec3<T2> converted() const
    {
        return Vec3<T2>(x, y, z);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for unit \b X vector (1, 0, 0)
 * \tparam T Template floating point type
 * \return Unit \b X vector (1, 0, 0)
 */
template <typename T>
Vec3<T> Vec3<T>::unitX()
{
    return Vec3<T>(T(1), T(0), T(0));
}

/*!
 * \brief Getter for unit \b Y vector (0, 1, 0)
 * \tparam T Template floating point type
 * \return Unit \b Y vector (0, 1, 0)
 */
template <typename T>
Vec3<T> Vec3<T>::unitY()
{
    return Vec3<T>(T(0), T(1), T(0));
}

/*!
 * \brief Getter for unit \b Z vector (0, 0, 1)
 * \tparam T Template floating point type
 * \return Unit \b Z vector (0, 0, 1)
 */
template <typename T>
Vec3<T> Vec3<T>::unitZ()
{
    return Vec3<T>(T(0), T(0), T(1));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is null
 * \tparam T Template floating point type
 * \return \c true if vector is null
 */
template <typename T>
inline bool Vec3<T>::isNull() const
{
    return Math::isNull<T>(x) && Math::isNull<T>(y) && Math::isNull<T>(z);
}

/*!
 * \brief Test if vectors are equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are equal
 * \sa TypeEquals<T>(const T, const T)
 */
template <typename T>
inline bool Vec3<T>::equals(const Vec3<T> &_other) const
{
    return Math::equals<T>(x, _other.x) && Math::equals<T>(y, _other.y) && Math::equals<T>(z, _other.z);
}

/*!
 * \brief Operator for test if vectors are equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T> &_other) const
{
    return equals(_other);
}

/*!
 * \brief Operator for test if vectors are not equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are not equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T> &_other) const
{
    return !equals(_other);
}

/*!
 * \brief Clear vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec3<T>::clear()
{
    x = T(0);
    y = T(0);
    z = T(0);
}

/*!
 * \brief Add other vector
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator+=(const Vec3<T> &_value)
{
    x += _value.x;
    y += _value.y;
    z += _value.z;
    return *this;
}

/*!
 * \brief Subtract other vector
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator-=(const Vec3<T> &_value)
{
    x -= _value.x;
    y -= _value.y;
    z -= _value.z;
    return *this;
}

/*!
 * \brief Multiply vector by value
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator*=(const T _value)
{
    x *= _value;
    y *= _value;
    z *= _value;
    return *this;
}

/*!
 * \brief Divide vector by value
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator/=(const T _value)
{
    x /= _value;
    y /= _value;
    z /= _value;
    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sum operator for two vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Sum vectors
 */
template <typename T>
inline Vec3<T> operator+(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return Vec3<T>(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.z);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Subtract operator for two vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Subtract vectors
 */
template <typename T>
inline Vec3<T> operator-(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return Vec3<T>(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z);
}

/*!
 * \brief Inverted operator
 * \tparam T Template floating point type
 * \param _v Vector
 * \return Inverted vector
 */
template <typename T>
inline Vec3<T> operator-(const Vec3<T> &_v)
{
    return _v.inverted();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Multiply operator for vector by value
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second value
 * \return Multiply of vector by value
 */
template <typename T>
inline Vec3<T> operator*(const Vec3<T> &_v1, const T _v2)
{
    return Vec3<T>(_v1.x * _v2, _v1.y * _v2, _v1.z * _v2);
}

/*!
 * \brief Multiply operator for value by vector
 * \tparam T Template floating point type
 * \param _v1 First value
 * \param _v2 Second vector
 * \return Multiply of value by vector
 */
template <typename T>
inline Vec3<T> operator*(const T _v1, const Vec3<T> &_v2)
{
    return Vec3<T>(_v1 * _v2.x, _v1 * _v2.y, _v1 * _v2.z);
}

/*!
 * \brief Divide operator for vector by value
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second value
 * \return Divide of vector by value
 */
template <typename T>
inline Vec3<T> operator/(const Vec3<T> &_v1, const T _v2)
{
    return Vec3<T>(_v1.x / _v2, _v1.y / _v2, _v1.z / _v2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns inverted vector
 * \tparam T Template floating point type
 * \return Inverted vector
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
 * \return \c true if vector is normalized
 */
template <typename T>
inline bool Vec3<T>::isNormalized() const
{
    return isUnit<T>(lengthSquared());
}

/*!
 * \brief Returns normalized vector
 * \tparam T Template floating point type
 * \return Normalized vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::normalized() const
{
    const T lenSq = lengthSquared();
    if (Math::isNull<T>(lenSq) || isUnit<T>(lenSq))
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
    if (!Math::isNull<T>(lenSq) && !isUnit<T>(lenSq))
        *this /= std::sqrt(lenSq);
}

/*!
 * \brief Test if other vector is perpendicular to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are perpendicular
 */
template <typename T>
inline bool Vec3<T>::isPerpendicular(const Vec3<T> &_other) const
{
    return Math::isNull<T>(Vec3<T>::dot(*this, _other));
}

/*!
 * \brief Returns normalized vector that is perpendicular to this vector
 * \tparam T Template floating point type
 * \return Normalized perpendicular vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::perpendicularNormal() const
{
    static const Vec3<T> n1(T(1), T(0), T(0));
    static const Vec3<T> n2(T(0), T(1), T(0));
    return (isParallel(n1) ? Vec3<T>::cross(*this, n2).normalized() : Vec3<T>::cross(*this, n1).normalized());
}

/*!
 * \brief Setup given vectors to be perpendicular and normalized
 * \tparam T Template floating point type
 * \param _normal1 Main normal
 * \param _normal2 Secondary normal
 * \return
 */
template <typename T>
void Vec3<T>::makePerpendicularNormals(Vec3<T> &_normal1, Vec3<T> &_normal2)
{
    T tmp = _normal1.lengthSquared();
    if (Math::isNull<T>(tmp))
        _normal1 = unitX();
    else if (!isUnit<T>(tmp))
        _normal1 = _normal1 / std::sqrt(tmp);

    tmp = _normal2.lengthSquared();
    if (Math::isNull<T>(tmp))
    {
        _normal2 = _normal1.perpendicularNormal();
    }
    else if (Math::isNull<T>(Vec3<T>::dot(_normal1, _normal2)))
    {
        if (!isUnit<T>(tmp))
            _normal2 = _normal2 / std::sqrt(tmp);
    }
    else
    {
        const Vec3<T> perpNorm = Vec3<T>::cross(_normal2, _normal1);
        if (perpNorm.isNull())
            _normal2 = _normal1.perpendicularNormal();
        else
            _normal2 = Vec3<T>::cross(_normal1, perpNorm).normalized();
    }
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isSameDir(const Vec3<T> &_other) const
{
    return !isNull() && normalized() == _other.normalized();
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isParallel(const Vec3<T> &_other) const
{
    const Vec3<T> n1 = normalized();
    const Vec3<T> n2 = _other.normalized();
    return !n1.isNull() && (n1 == n2 || n1 == -n2);
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \param[out] _isSameDirection Output is same direction flag
 * \return \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isParallelInDir(const Vec3<T> &_other, bool &_isSameDirection) const
{
    if (isNull() || _other.isNull())
    {
        _isSameDirection = false;
        return false;
    }
    const Vec3<T> n1 = normalized();
    const Vec3<T> n2 = _other.normalized();
    _isSameDirection = (n1 == n2);
    return _isSameDirection || (n1 == -n2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Dot product of two 3D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Dot product of two 3D vectors
 */
template <typename T>
T Vec3<T>::dot(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return _v1.x * _v2.x + _v1.y * _v2.y + _v1.z * _v2.z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Right handed cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Right handed cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return Vec3<T>(_v1.y * _v2.z - _v1.z * _v2.y,   //
                   _v1.z * _v2.x - _v1.x * _v2.z,   //
                   _v1.x * _v2.y - _v1.y * _v2.x);  //
}

/*!
 * \brief Left handed cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Left handed cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::crossLeftHand(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return Vec3<T>(_v1.z * _v2.y - _v1.y * _v2.z,   //
                   _v1.x * _v2.z - _v1.z * _v2.x,   //
                   _v1.y * _v2.x - _v1.x * _v2.y);  //
}

/*!
 * \brief Oriented cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \param _rightHanded Hand rule orientation
 * \return Oriented cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::crossByHand(const Vec3<T> &_v1, const Vec3<T> &_v2, const bool _rightHanded)
{
    return _rightHanded ? cross(_v1, _v2) : crossLH(_v1, _v2);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns vectors length squared
 * \tparam T Template floating point type
 * \return Vectors length squared
 */
template <typename T>
inline T Vec3<T>::lengthSquared() const
{
    return dot(*this, *this);
}

/*!
 * \brief Returns vectors length
 * \tparam T Template floating point type
 * \return Vectors length
 */
template <typename T>
inline T Vec3<T>::length() const
{
    return std::sqrt(lengthSquared());
}

/*!
 * \brief Returns sum of vector components
 * \tparam T Template floating point type
 * \return Sum of vector components
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
 * \param _point Other point
 * \return Distance to point
 */
template <typename T>
inline T Vec3<T>::distanceToPoint(const Vec3<T> &_point) const
{
    return (*this - _point).length();
}

/*!
 * \brief Returns distance to line
 * \tparam T Template floating point type
 * \param _linePoint Line point
 * \param _lineNormal Line normal
 * \return Distance to line
 */
template <typename T>
inline T Vec3<T>::distanceToLine(const Vec3<T> &_linePoint, const Vec3<T> &_lineNormal) const
{
    const T lenSq = _lineNormal.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);  // distanceToPoint(linePoint);
    const T tmp = cross(*this - _linePoint, *this - _linePoint - _lineNormal).length();
    return isUnit<T>(lenSq) ? tmp : (tmp / std::sqrt(lenSq));
}

/*!
 * \brief Returns distance to plane
 * \tparam T Template floating point type
 * \param _planePoint Plane point
 * \param _planeNormal Plane normal
 * \return Distance to plane
 */
template <typename T>
inline T Vec3<T>::distanceToPlane(const Vec3<T> &_planePoint, const Vec3<T> &_planeNormal) const
{
    const T lenSq = _planeNormal.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    if (isUnit<T>(lenSq))
        return dot(*this - _planePoint, _planeNormal);
    return dot(*this - _planePoint, _planeNormal) / std::sqrt(lenSq);
}

/*!
 * \brief Returns length of projection to other vector
 * \tparam T Template floating point type
 * \param _projDirection Projection direction
 * \return Length of projection to other vector
 * \note Opposite directions have negative values
 */
template <typename T>
inline T Vec3<T>::projectedLength(const Vec3<T> &_projDirection) const
{
    const T lenSq = _projDirection.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    if (isUnit<T>(lenSq))
        return dot(*this, _projDirection);
    return dot(*this, _projDirection) / std::sqrt(lenSq);
}

/*!
 * \brief Returns projection to other vector
 * \tparam T Template floating point type
 * \param _projDirection Projection direction
 * \return Projection of this vector to other vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::projected(const Vec3<T> &_projDirection) const
{
    const T lenSq = _projDirection.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return Vec3<T>();
    if (isUnit<T>(lenSq))
        return _projDirection * dot(*this, _projDirection);
    return _projDirection * (dot(*this, _projDirection) / lenSq);
}

/*!
 * \brief Returns projection on plane defined by normal
 * \tparam T Template floating point type
 * \param _planeNormal Plane normal
 * \return Projection of this vector to other plane
 */
template <typename T>
inline Vec3<T> Vec3<T>::projectedOnPlane(const Vec3<T> &_planeNormal) const
{
    return *this - projected(_planeNormal);
}

/*!
 * \brief Returns plane - line intersection
 * \param _planePoint Plane center point
 * \param _planeNormal Plane normal
 * \param _linePoint Line center point
 * \param _lineNormal Line normal
 * \param _outOk Possible success flag output
 * \return Plane line intersection point
 */
template <typename T>
Vec3<T> Vec3<T>::planeLineIntersection(const Vec3<T> &_planePoint,
                                       const Vec3<T> &_planeNormal,
                                       const Vec3<T> &_linePoint,
                                       const Vec3<T> &_lineNormal,
                                       bool *_outOk)
{

    const T d0 = Vec3<T>::dot(_planeNormal, _lineNormal);
    if (Math::isNull<T>(d0))
    {
        if (_outOk != nullptr)
            *_outOk = false;
        return Vec3<T>();
    }

    if (_outOk != nullptr)
        *_outOk = true;

    return _linePoint +
        _lineNormal * ((Vec3<T>::dot(_planeNormal, _planePoint) - Vec3<T>::dot(_planeNormal, _linePoint)) / d0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Co-sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Co-sinus of angle between this and other 3D vector
 * \details Used equation:
 * \f$\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}}\f$
 */
template <typename T>
inline T Vec3<T>::cosAngle(const Vec3<T> &_other) const
{
    const T lenSq = lengthSquared() * _other.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    if (isUnit<T>(lenSq))
        return dot(*this, _other);
    return dot(*this, _other) / std::sqrt(lenSq);
}

/*!
 * \brief <b>Power 2</b> of cosinus angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return <b>Power 2</b> of cosinus angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::cosAnglePow2(const Vec3<T> &_other) const
{
    const T lenSq = lengthSquared() * _other.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    const T result = dot(*this, _other);
    if (isUnit<T>(lenSq))
        return result * result;
    return result * result / lenSq;
}

/*!
 * \brief Sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Sinus of angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::sinAngle(const Vec3<T> &_other) const
{
    return std::sqrt(sinAnglePow2(_other));
}

/*!
 * \brief Sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Sinus of angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::sinAnglePow2(const Vec3<T> &_other) const
{
    return T(1) - cosAnglePow2(_other);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Angle between this and other 3D vector in radians
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Angle between this and other 3D vector in radians
 * \note Result angle range: \f$\langle 0, \pi \rangle\f$
 * \details Used equation:
 * \f$acos(\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}})\f$
 */
template <typename T>
inline T Vec3<T>::angleRad(const Vec3<T> &_other) const
{
    const T lenSq = lengthSquared() * _other.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    T result = dot(*this, _other);
    if (!isUnit<T>(lenSq))
        result /= std::sqrt(lenSq);
    return std::acos(std::min(T(1), std::max(-T(1), result)));
}

/*!
 * \brief Angle between this and other 3D vector in degrees
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Angle between this and other 3D vector in degrees
 * \note Result angle range: \f$\langle 0, 180 \rangle\f$ degrees
 */
template <typename T>
inline T Vec3<T>::angleDeg(const Vec3<T> &_other) const
{
    return toDeg<T>(angleRad(_other));
}

/*!
 * \brief Angle between this and other 3D vector in radians
 * \tparam T Template floating point type
 * \param _other Other vector
 * \param _normal Normal vector
 * \return Angle between this and other 3D vector in radians
 * \note Returned angle is in range \f$( -\pi, pi \rangle\f$
 */
template <typename T>
inline T Vec3<T>::angleNormRad(const Vec3<T> &_other, const Vec3<T> &_normal) const
{
    const T result = angleRad(_other);
    return Vec3<T>::dot(_normal, Vec3<T>::cross(*this, _other)) < T(0) ? -result : result;
}

/*!
 * \brief Angle between this and other 3D vector in degrees
 * \tparam T Template floating point type
 * \param _v Other vector
 * \param _normal Normal vector
 * \return Angle between this and other 3D vector in degrees
 * \note Result angle range: \f$( -180, 180 \rangle\f$ degrees
 */
template <typename T>
inline T Vec3<T>::angleNormDeg(const Vec3<T> &_v, const Vec3<T> &_normal) const
{
    return toDeg<T>(angleNormRad(_v, _normal));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns rotated point around normal by angle (right-handed rotation)
 * \tparam T Template floating point type
 * \param _point Point to rotate
 * \param _normal Rotation normal (axis)
 * \param _sinAngle Sinus of rotation angle
 * \param _cosAngle Cosinus of rotation angle
 * \return Rotated point around normal by angle
 */
template <typename T>
Vec3<T> Vec3<T>::rotate(const Vec3<T> &_point, const Vec3<T> &_normal, const T _sinAngle, const T _cosAngle)
{
    const T lenSq = _normal.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return Vec3<T>(_point);

    const Vec3<T> n = isUnit<T>(lenSq) ? _normal : (_normal / std::sqrt(lenSq));
    const Vec3<T> u = n.x * _point;
    const Vec3<T> v = n.y * _point;
    const Vec3<T> w = n.z * _point;

    return Vec3<T>(n.x * (u.x + v.y + w.z) + _sinAngle * (v.z - w.y) +
                       _cosAngle * (_point.x * (n.y * n.y + n.z * n.z) - n.x * (v.y + w.z)),
                   n.y * (u.x + v.y + w.z) + _sinAngle * (w.x - u.z) +
                       _cosAngle * (_point.y * (n.x * n.x + n.z * n.z) - n.y * (u.x + w.z)),
                   n.z * (u.x + v.y + w.z) + _sinAngle * (u.y - v.x) +
                       _cosAngle * (_point.z * (n.x * n.x + n.y * n.y) - n.z * (u.x + v.y)));
}

/*!
 * \brief Returns rotated point around normal by angle (right-handed rotation)
 * \tparam T Template floating point type
 * \param _point Point to rotate
 * \param _normal Rotation normal (axis)
 * \param _angleRad Angle in radians
 * \return Rotated point around normal by angle
 */
template <typename T>
Vec3<T> Vec3<T>::rotate(const Vec3<T> &_point, const Vec3<T> &_normal, const T _angleRad)
{
    return Vec3<T>::rotate(_point, _normal, sin(_angleRad), cos(_angleRad));
}

/*!
 * \brief Returns rotated point around normal by angle in radians
 * \tparam T Template floating point type
 * \param _normal Rotation normal (axis)
 * \param _sinAngle Sinus of rotation angle
 * \param _cosAngle Cosinus of rotation angle
 * \return Rotated point around normal by angle
 */
template <typename T>
inline Vec3<T> Vec3<T>::rotated(const Vec3<T> &_normal, const T _sinAngle, const T _cosAngle) const
{
    return Vec3<T>::rotate(*this, _normal, _sinAngle, _cosAngle);
}

/*!
 * \brief Returns rotated point around normal by angle in radians
 * \tparam T Template floating point type
 * \param _normal Rotation normal (axis)
 * \param _angleRad Angle in radians
 * \return Rotated point around normal by angle
 */
template <typename T>
inline Vec3<T> Vec3<T>::rotated(const Vec3<T> &_normal, const T _angleRad) const
{
    return Vec3<T>::rotate(*this, _normal, _angleRad);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Ratio vector
 * \param _v1 Vector 1
 * \param _v2 Vector 2
 * \param _value1 Value for vector 1
 * \param _value2 Value for vector 2
 * \param _valueCenter Value for result vector
 * \return Ratio vector
 */
template <typename T>
Vec3<T> Vec3<T>::ratio(const Vec3<T> &_v1, const Vec3<T> &_v2, const T _value1, const T _value2, const T _valueCenter)
{
    return _v1 + (_v2 - _v1) * ((_valueCenter - _value1) / (_value2 - _value1));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Tests if values of all components are in range 0 to 1 (included 0 and 1)
 * \return \c true when values of all components are in range 0 to 1
 */
template <typename T>
inline bool Vec3<T>::isValidColor() const
{
    return isAlignedTo0_1<T>(x) && isAlignedTo0_1<T>(y) && isAlignedTo0_1<T>(z);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Conversion to 2D vector by not using defined vector component \a _skipAxis
 * \param _skipAxis 3D vector component (axis) that is not used in output 2D vector
 * \return 2D vector from this 3D vector
 */
template <typename T>
inline Vec2<T> Vec3<T>::toVec2(const uint8_t _skipAxis) const
{
    switch (_skipAxis)
    {
    case 0U: return Vec2<T>(m_data[1U], m_data[2U]);
    case 1U: return Vec2<T>(m_data[0U], m_data[2U]);
    default: break;
    }
    return Vec2<T>(m_data[0U], m_data[1U]);
}

/*!
 * \brief Conversion to 3D vector by using value \a _thirdValue for defined vector component \a _thirdAxis
 * \param _thirdAxis Index of third component
 * \param _thirdValue Value for third component
 * \return 3D vector from this 2D vector
 */
template <typename T>
Vec3<T> Vec2<T>::toVec3(const uint8_t _thirdAxis, const T _thirdValue) const
{
    switch (_thirdAxis)
    {
    case 0U: return Vec3<T>(_thirdValue, x, y);
    case 1U: return Vec3<T>(x, _thirdValue, y);
    default: break;
    }
    return Vec3<T>(x, y, _thirdValue);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef UNIVERSE1_USE_QT_LIB

/*!
 * \brief Conversion to \c QVector3D
 * \return This 3D vector as \c QVector3D
 */
template <typename T>
inline QVector3D Vec3<T>::toQVector3D() const
{
    return QVector3D(x, y, z);
}

/*!
 * \brief Conversion from \c QVector3D
 * \param _value Input \c QVector3D vector
 * \return 3D vector from \c QVector3D
 */
template <typename T>
Vec3<T> Vec3<T>::fromQVector3D(const QVector3D &_value)
{
    return Vec3<T>(_value.x(), _value.y(), _value.z());
}

/*!
 * \brief Conversion to \c QColor
 * \return This 3D vector as \c QColor
 */
template <typename T>
inline QColor Vec3<T>::toQColor() const
{
    return QColor(std::max(0, std::min(255, static_cast<int>(x * T(255)))),
                  std::max(0, std::min(255, static_cast<int>(y * T(255)))),
                  std::max(0, std::min(255, static_cast<int>(z * T(255)))));
}

/*!
 * \brief Conversion from \c QColor
 * \param _value Input \c QColor
 * \return 3D vector from \c QColor
 */
template <typename T>
Vec3<T> Vec3<T>::fromQColor(const QColor _value)
{
    return Vec3<T>(static_cast<T>(_value.redF()), static_cast<T>(_value.greenF()), static_cast<T>(_value.blueF()));
}

/*!
 * \brief Tool function, to \c QVector3D to \c QColor
 * \param _value Input 3D vector
 * \return Vector as \c QColor
 */
inline QColor toColor(const QVector3D &_value)
{
    return QColor(std::max(0, std::min(255, static_cast<int>(_value.x() * 255.0F))),
                  std::max(0, std::min(255, static_cast<int>(_value.y() * 255.0F))),
                  std::max(0, std::min(255, static_cast<int>(_value.z() * 255.0F))));
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Vector
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Vec3<T> &_v)
{
    return _os << '[' << _v.x << ',' << _v.y << ',' << _v.z << ']';
}

/*!
 * \brief To \c std::string
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Vector as \c std::string
 */
template <typename T>
inline std::string Vec3<T>::toString(const int _decimals) const
{
    std::stringstream ss;
    if (_decimals >= 0)
    {
        ss.precision(_decimals);
        ss << std::fixed;
    }
    ss << *this;
    return ss.str();
}

/*!
 * \brief To \c std::string with length
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Vector as \c std::string
 */
template <typename T>
inline std::string Vec3<T>::toStringFull(const int _decimals) const
{
    std::stringstream ss;
    if (_decimals >= 0)
    {
        ss.precision(_decimals);
        ss << std::fixed;
    }
    ss << '[' << x << ',' << y << ',' << z << '|' << length() << ']';
    return ss.str();
}

#ifdef UNIVERSE1_USE_QT_LIB

/*!
 * \brief To \c QString
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Vector as \c QString
 */
template <typename T>
inline QString Vec3<T>::toQString(const int _decimals) const
{
    return QString::fromStdString(toString(_decimals));
}

/*!
 * \brief To \c QString with length
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Vector as \c QString
 */
template <typename T>
inline QString Vec3<T>::toQStringFull(const int _decimals) const
{
    return QString::fromStdString(toStringFull(_decimals));
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Vec3<float> Vec3F;        //!< 32 bit floating point precision 3D vector
typedef Vec3<double> Vec3D;       //!< 64 bit floating point precision 3D vector
typedef Vec3<long double> Vec3L;  //!< 128 bit floating point precision 3D vector

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_VEC3_H
