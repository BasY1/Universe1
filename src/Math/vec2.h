/*!
 * \file src/Math/vec2.h
 * \brief 2D vector template implementation
 */

#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include "type.h"

#include <iostream>

#include <QVector2D>

namespace U1 {
namespace Math {

template <typename T>
struct Vec3;

/*!
 * \brief 2D vector template for various floating point types
 * \tparam T Template floating point type
 */
template <typename T>
struct Vec2
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
         */
        T m_data[2];

        /*! \brief The anonymous structure, access vector component by axis name */
        struct
        {
            T x;  //!< Union \b X axis (first) component representation
            T y;  //!< Union \b Y axis (second) component representation
        };
    };

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec2()
        : x(T(0))
        , y(T(0))
    {
    }

    /*!
     * \brief Constructor with vector components
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec2(const T _x,  //!< X component
                const T _y)  //!< Z component
        : x(_x)
        , y(_y)
    {
    }

    /*!
     * \brief Constructor from other vector
     * \param _other Other vector
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec2(const Vec2<T> &_other)
        : x(_other.x)
        , y(_other.y)
    {
    }

    static Vec2<T> unitX();
    static Vec2<T> unitY();

    static Vec2<T> lowestValue();
    static Vec2<T> maximumValue();

    static Vec2<T> minimum(const Vec2<T> &_v1, const Vec2<T> &_v2);
    static Vec2<T> maximum(const Vec2<T> &_v1, const Vec2<T> &_v2);

    static bool isAligned(const Vec2<T> &_v, const Vec2<T> &_min, const Vec2<T> &_max);
    inline bool isAligned(const Vec2<T> &_min, const Vec2<T> &_max) const;

    inline bool isNull() const;
    inline bool equals(const Vec2<T> &_other) const;
    inline bool operator==(const Vec2<T> &_other) const;
    inline bool operator!=(const Vec2<T> &_other) const;

    static int8_t compare(const Vec2<T> &_v1, const Vec2<T> &_v2);
    static bool isLessNotEqual(const Vec2<T> &_v1, const Vec2<T> &_v2);

    inline T minimumComponnentValue() const;
    inline T minimumComponnentValueAbs() const;
    inline T maximumComponnentValue() const;
    inline T maximumComponnentValueAbs() const;

    inline uint8_t minimumComponnentIndex() const;
    inline uint8_t minimumComponnentIndexAbs() const;
    inline uint8_t maximumComponnentIndex() const;
    inline uint8_t maximumComponnentIndexAbs() const;

    inline void clear();
    inline Vec2<T> &set(const T _x, const T _y);
    inline void swap(Vec2<T> &_other);

    inline Vec2<T> &operator+=(const Vec2<T> &_value);
    inline Vec2<T> &operator-=(const Vec2<T> &_value);
    inline Vec2<T> &operator*=(const T _value);
    inline Vec2<T> &operator/=(const T _value);

    inline Vec2<T> inverted() const;
    inline void invert();
    inline void maybeInvert(const Vec2<T> &_normal);

    inline bool isNormalized() const;
    inline Vec2<T> normalized() const;
    inline void normalize();

    inline bool isPerpendicular(const Vec2<T> &_other) const;
    inline Vec2<T> perpendicular() const;
    inline Vec2<T> perpendicularNormal() const;

    inline bool equalsDir(const Vec2<T> &_other) const;
    inline bool isParallel(const Vec2<T> &_other) const;
    inline bool isParallelInDir(const Vec2<T> &_other, bool &_outequalsDirection) const;

    static T det(const Vec2<T> &_v1, const Vec2<T> &_v2);
    static T dot(const Vec2<T> &_v1, const Vec2<T> &_v2);

    inline T lengthSquared() const;
    inline T length() const;

    inline T sum() const;

    inline T distanceToPoint(const Vec2<T> &_point) const;

    inline T distanceToLine(const Vec2<T> &_linePoint, const Vec2<T> &_lineNormal) const;
    inline T offsetToLine(const Vec2<T> &_linePoint, const Vec2<T> &_lineNormal) const;

    inline T cosAngle(const Vec2<T> &_other) const;
    inline T cosAnglePow2(const Vec2<T> &_other) const;

    inline T sinAngle(const Vec2<T> &_other) const;
    inline T sinAnglePow2(const Vec2<T> &_other) const;

    inline T angleRad(const Vec2<T> &_other) const;
    inline T angleDeg(const Vec2<T> &_other) const;

    inline T angleOrientedRad(const Vec2<T> &_other) const;
    inline T angleOrientedDeg(const Vec2<T> &_other) const;

    static Vec2<T> bezier(const T _ratio,
                          const Vec2<T> &_fromPoint,
                          const Vec2<T> &_fromDirection,
                          const Vec2<T> &_toPoint,
                          const Vec2<T> &_toDirection);

    static Vec2<T>
    betweenByValue(const Vec2<T> &_v1, const Vec2<T> &_v2, const T _value1, const T _value2, const T _valueCenter);

    static Vec2<T> betweenByRatio(const Vec2<T> &_v1, const Vec2<T> &_v2, const T _ratio);

    /*!
     * \brief Conversion to different precision
     * \tparam T2 Output template floating point type
     * \return Vector in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    inline Vec2<T2> converted() const
    {
        return Vec2<T2>(static_cast<T2>(x), static_cast<T2>(y));
    }

    Vec3<T> toVec3(const uint8_t _thirdAxis = 2U, const T _thirdValue = T(0)) const;

    inline QVector2D toQVector2D() const;
    static Vec2<T> fromQVector2D(const QVector2D &_value);

    inline size_t toHash() const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for unit \b X vector (1, 0)
 * \tparam T Template floating point type
 * \return Unit \b X vector (1, 0)
 */
template <typename T>
Vec2<T> Vec2<T>::unitX()
{
    return Vec2<T>(1, 0);
}

/*!
 * \brief Getter for unit \b Y vector (0, 1)
 * \tparam T Template floating point type
 * \return Unit \b Y vector (0, 1)
 */
template <typename T>
Vec2<T> Vec2<T>::unitY()
{
    return Vec2<T>(0, 1);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns a vector with lowest possible values of its components
 * \tparam T Template floating point type
 * \return Vector with lowest possible values of its components
 */
template <typename T>
Vec2<T> Vec2<T>::lowestValue()
{
    return Vec2<T>(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest());
}

/*!
 * \brief Returns a vector with maximum possible values of its components
 * \tparam T Template floating point type
 * \return Vector with maximum possible values of its components
 */
template <typename T>
Vec2<T> Vec2<T>::maximumValue()
{
    return Vec2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create a vector with minimum values of its components from given vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Vector with minimum values of its components
 */
template <typename T>
Vec2<T> Vec2<T>::minimum(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return {std::min(_v1.x, _v2.x), std::min(_v1.y, _v2.y)};
}

/*!
 * \brief Create a vector with maximum values of its components from given vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Vector with maximum values of its components
 */
template <typename T>
Vec2<T> Vec2<T>::maximum(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return {std::max(_v1.x, _v2.x), std::max(_v1.y, _v2.y)};
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is within range
 * \tparam T Template floating point type
 * \param _v Vector
 * \param _min Vector - range minimum
 * \param _max Vector - range maximum
 * \return \c true if all components fits given range
 */
template <typename T>
bool Vec2<T>::isAligned(const Vec2<T> &_v, const Vec2<T> &_min, const Vec2<T> &_max)
{
    return Math::isAligned(_v.x, _min.x, _max.x) && Math::isAligned(_v.y, _min.y, _max.y);
}

/*!
 * \brief Test if this vector is within range
 * \tparam T Template floating point type
 * \param _min Vector - range minimum
 * \param _max Vector - range maximum
 * \return \c true if all components fits given range
 */
template <typename T>
inline bool Vec2<T>::isAligned(const Vec2<T> &_min, const Vec2<T> &_max) const
{
    return Math::isAligned(x, _min.x, _max.x) && Math::isAligned(y, _min.y, _max.y);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is null
 * \tparam T Template floating point type
 * \return \c true if vector is null
 */
template <typename T>
inline bool Vec2<T>::isNull() const
{
    return Math::isNull(x) && Math::isNull(y);
}

/*!
 * \brief Test if vectors are equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are equal
 */
template <typename T>
inline bool Vec2<T>::equals(const Vec2<T> &_other) const
{
    return Math::equals(x, _other.x) && Math::equals(y, _other.y);
}

/*!
 * \brief Operator for test if vectors are equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are equal
 * \sa Vec2<T>::equals<T>(const Vec2<T>&)
 */
template <typename T>
inline bool Vec2<T>::operator==(const Vec2<T> &_other) const
{
    return equals(_other);
}

/*!
 * \brief Operator for test if vectors are not equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are not equal
 * \sa Vec2<T>::equals<T>(const Vec2<T>&)
 */
template <typename T>
inline bool Vec2<T>::operator!=(const Vec2<T> &_other) const
{
    return !equals(_other);
}

/*!
 * \brief Compare 2D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return -1, 0 or 1
 */
template <typename T>
int8_t Vec2<T>::compare(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    T diff = _v1.x - _v2.x;
    if (isNegative(diff))
    {
        return -1;
    }
    if (isPositive(diff))
    {
        return 1;
    }

    diff = _v1.y - _v2.y;
    if (isNegative(diff))
    {
        return -1;
    }
    else if (isPositive(diff))
    {
        return 1;
    }
    return 0;
}

/*!
 * \brief Test if all components of \c _v1 are less than components of \c _v2
 * \tparam T Template floating point type
 * \param _v1 First value to check
 * \param _v2 Second value to check
 * \return \c true if all components of \c _v1 are less than components of \c _v2
 */
template <typename T>
bool Vec2<T>::isLessNotEqual(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return Math::isLessNotEqual(_v1.x, _v2.x) && Math::isLessNotEqual(_v1.y, _v2.y);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns minimum value from vector components
 * \tparam T Template floating point type
 * \return Minimum value from vector components
 */
template <typename T>
inline T Vec2<T>::minimumComponnentValue() const
{
    return std::min(x, y);
}

/*!
 * \brief Returns minimum absolute value from vector components
 * \tparam T Template floating point type
 * \return Minimum absolute value from vector components
 */
template <typename T>
inline T Vec2<T>::minimumComponnentValueAbs() const
{
    return std::min(std::abs(x), std::abs(y));
}

/*!
 * \brief Returns maximum value from vector components
 * \tparam T Template floating point type
 * \return Maximum value from vector components
 */
template <typename T>
inline T Vec2<T>::maximumComponnentValue() const
{
    return std::max(x, y);
}

/*!
 * \brief Returns maximum absolute value from vector components
 * \tparam T Template floating point type
 * \return Maximum absolute value from vector components
 */
template <typename T>
inline T Vec2<T>::maximumComponnentValueAbs() const
{
    return std::max(std::abs(x), std::abs(y));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns index of component with minimum value
 * \tparam T Template floating point type
 * \return Index of component with minimum value
 */
template <typename T>
inline uint8_t Vec2<T>::minimumComponnentIndex() const
{
    return x < y ? 0U : 1U;
}

/*!
 * \brief Returns index of component with minimum absolute value
 * \tparam T Template floating point type
 * \return Index of component with minimum absolute value
 */
template <typename T>
inline uint8_t Vec2<T>::minimumComponnentIndexAbs() const
{
    return std::abs(x) < std::abs(y) ? 0U : 1U;
}

/*!
 * \brief Returns index of component with maximum value
 * \tparam T Template floating point type
 * \return Index of component with maximum value
 */
template <typename T>
inline uint8_t Vec2<T>::maximumComponnentIndex() const
{
    return x > y ? 0U : 1U;
}

/*!
 * \brief Returns index of component with maximum absolute value
 * \tparam T Template floating point type
 * \return Index of component with maximum absolute value
 */
template <typename T>
inline uint8_t Vec2<T>::maximumComponnentIndexAbs() const
{
    return std::abs(x) > std::abs(y) ? 0U : 1U;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Clear vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec2<T>::clear()
{
    x = 0;
    y = 0;
}

/*!
 * \brief Setup component values
 * \param _x New \b X value
 * \param _y New \b Y value
 * \return This vector
 */
template <typename T>
inline Vec2<T> &Vec2<T>::set(const T _x, const T _y)
{
    x = _x;
    y = _y;
    return *this;
}

/*!
 * \brief Swap two vectors
 * \param _other Other vector
 */
template <typename T>
inline void Vec2<T>::swap(Vec2<T> &_other)
{
    const Vec2<T> tmp = *this;
    *this = _other;
    _other = tmp;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Add other vector
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec2<T> &Vec2<T>::operator+=(const Vec2<T> &_value)
{
    x += _value.x;
    y += _value.y;
    return *this;
}

/*!
 * \brief Subtract other vector
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec2<T> &Vec2<T>::operator-=(const Vec2<T> &_value)
{
    x -= _value.x;
    y -= _value.y;
    return *this;
}

/*!
 * \brief Multiply vector by value
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec2<T> &Vec2<T>::operator*=(const T _value)
{
    x *= _value;
    y *= _value;
    return *this;
}

/*!
 * \brief Divide vector by value
 * \tparam T Template floating point type
 * \param _value Other vector
 * \return \c this vector pointer
 */
template <typename T>
inline Vec2<T> &Vec2<T>::operator/=(const T _value)
{
    x /= _value;
    y /= _value;
    return *this;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sum operator for two vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Sum vectors
 */
template <typename T>
inline Vec2<T> operator+(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return Vec2<T>(_v1.x + _v2.x, _v1.y + _v2.y);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Subtract operator for two vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Subtract vectors
 */
template <typename T>
inline Vec2<T> operator-(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return Vec2<T>(_v1.x - _v2.x, _v1.y - _v2.y);
}

/*!
 * \brief Inverted operator
 * \tparam T Template floating point type
 * \param _v Vector
 * \return Inverted vector
 */
template <typename T>
inline Vec2<T> operator-(const Vec2<T> &_v)
{
    return _v.inverted();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Multiply operator for vector by value
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second value
 * \return Multiply of vector by value
 */
template <typename T>
inline Vec2<T> operator*(const Vec2<T> &_v1, const T _v2)
{
    return Vec2<T>(_v1.x * _v2, _v1.y * _v2);
}

/*!
 * \brief Multiply operator for value by vector
 * \tparam T Template floating point type
 * \param _v1 First value
 * \param _v2 Second vector
 * \return Multiply of value by vector
 */
template <typename T>
inline Vec2<T> operator*(const T _v1, const Vec2<T> &_v2)
{
    return Vec2<T>(_v1 * _v2.x, _v1 * _v2.y);
}

/*!
 * \brief Divide operator for vector by value
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second value
 * \return Divide of vector by value
 */
template <typename T>
inline Vec2<T> operator/(const Vec2<T> &_v1, const T _v2)
{
    return Vec2<T>(_v1.x / _v2, _v1.y / _v2);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns inverted vector
 * \tparam T Template floating point type
 * \return Inverted vector
 */
template <typename T>
inline Vec2<T> Vec2<T>::inverted() const
{
    return Vec2<T>(-x, -y);
}

/*!
 * \brief Inverts this vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec2<T>::invert()
{
    x = -x;
    y = -y;
}

/*!
 * \brief Inverts this vector if dot product with \a _normal is negative
 * \tparam T Template floating point type
 * \param _normal Normal for inversion
 */
template <typename T>
inline void Vec2<T>::maybeInvert(const Vec2<T> &_normal)
{
    if (isNegative(dot(*this, _normal)))
        invert();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is normalized (length equals 1)
 * \tparam T Template floating point type
 * \return \c true if vector is normalized
 */
template <typename T>
inline bool Vec2<T>::isNormalized() const
{
    return isUnit(lengthSquared());
}

/*!
 * \brief Returns normalized vector
 * \tparam T Template floating point type
 * \return Normalized vector
 */
template <typename T>
inline Vec2<T> Vec2<T>::normalized() const
{
    const T lenSq = lengthSquared();
    if (Math::isNull(lenSq) || isUnit(lenSq))
        return Vec2<T>(x, y);
    return *this / std::sqrt(lenSq);
}

/*!
 * \brief Normalize this vector
 * \tparam T Template floating point type
 */
template <typename T>
inline void Vec2<T>::normalize()
{
    const T lenSq = lengthSquared();
    if (!Math::isNull(lenSq) && !isUnit(lenSq))
        *this /= std::sqrt(lenSq);
}

/*!
 * \brief Test if other vector is perpendicular to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are perpendicular
 */
template <typename T>
inline bool Vec2<T>::isPerpendicular(const Vec2<T> &_other) const
{
    return Math::isNull(Vec2<T>::dot(*this, _other));
}

/*!
 * \brief Returns normalized vector that is perpendicular to this vector
 * \tparam T Template floating point type
 * \return Normalized perpendicular vector
 */
template <typename T>
inline Vec2<T> Vec2<T>::perpendicular() const
{
    return Vec2<T>(-y, x);
}

/*!
 * \brief Returns normalized vector that is perpendicular to this vector
 * \tparam T Template floating point type
 * \return Normalized perpendicular vector
 */
template <typename T>
inline Vec2<T> Vec2<T>::perpendicularNormal() const
{
    return Vec2<T>(-y, x).normalized();
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if vectors are parallel
 */
template <typename T>
inline bool Vec2<T>::equalsDir(const Vec2<T> &_other) const
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
inline bool Vec2<T>::isParallel(const Vec2<T> &_other) const
{
    const Vec2<T> n1 = normalized();
    const Vec2<T> n2 = _other.normalized();
    return !n1.isNull() && (n1 == n2 || n1 == -n2);
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \param[out] _outequalsDirection Output is same direction flag
 * \return \c true if vectors are parallel
 */
template <typename T>
inline bool Vec2<T>::isParallelInDir(const Vec2<T> &_other, bool &_outequalsDirection) const
{
    if (isNull() || _other.isNull())
    {
        _outequalsDirection = false;
        return false;
    }
    const Vec2<T> n1 = normalized();
    const Vec2<T> n2 = _other.normalized();
    _outequalsDirection = (n1 == n2);
    return _outequalsDirection || (n1 == -n2);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Determinant of two 2D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Determinant of two 2D vectors
 */
template <typename T>
T Vec2<T>::det(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return _v1.x * _v2.y - _v1.y * _v2.x;
}

/*!
 * \brief Dot product of two 2D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Dot product of two 2D vectors
 */
template <typename T>
T Vec2<T>::dot(const Vec2<T> &_v1, const Vec2<T> &_v2)
{
    return _v1.x * _v2.x + _v1.y * _v2.y;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns vectors length squared
 * \tparam T Template floating point type
 * \return Vectors length squared
 */
template <typename T>
inline T Vec2<T>::lengthSquared() const
{
    return dot(*this, *this);
}

/*!
 * \brief Returns vectors length
 * \tparam T Template floating point type
 * \return Vectors length
 */
template <typename T>
inline T Vec2<T>::length() const
{
    return std::sqrt(lengthSquared());
}

/*!
 * \brief Returns sum of vector components
 * \tparam T Template floating point type
 * \return Sum of vector components
 */
template <typename T>
inline T Vec2<T>::sum() const
{
    return x + y;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns distance to point
 * \tparam T Template floating point type
 * \param _point Other point
 * \return Distance to point
 */
template <typename T>
inline T Vec2<T>::distanceToPoint(const Vec2<T> &_point) const
{
    return (*this - _point).length();
}

/*!
 * \brief Returns absolute value of distance to line
 * \tparam T Template floating point type
 * \param _linePoint Line point
 * \param _lineNormal Line normal
 * \return Distance to line
 */
template <typename T>
inline T Vec2<T>::distanceToLine(const Vec2<T> &_linePoint, const Vec2<T> &_lineNormal) const
{
    const T lenSq = _lineNormal.lengthSquared();
    if (Math::isNull(lenSq))
        return T(0);  // return distanceToPoint(_linePoint);
    return (*this -
            (_linePoint +
             _lineNormal *
                 (isUnit(lenSq) ? (dot(*this - _linePoint, _lineNormal))
                                : (dot(*this - _linePoint, _lineNormal) / lenSq))))
        .length();
}

/*!
 * \brief Returns distance to line
 * \tparam T Template floating point type
 * \param _linePoint Line point
 * \param _lineNormal Line normal
 * \return Distance to line
 * \details
 * \b Positive distance values also means that point is in left side against line normal.
 * \b Negative distance values means that point is in right side against line normal
 */
template <typename T>
inline T Vec2<T>::offsetToLine(const Vec2<T> &_linePoint, const Vec2<T> &_lineNormal) const
{
    const T lenSq = _lineNormal.lengthSquared();
    if (Math::isNull(lenSq))
        return T(0);  // return distanceToPoint(_linePoint);
    const Vec2<T> tmp = (*this -
                         (_linePoint +
                          _lineNormal *
                              (isUnit(lenSq) ? (dot(*this - _linePoint, _lineNormal))
                                             : (dot(*this - _linePoint, _lineNormal) / lenSq))));
    return dot(tmp, _lineNormal.perpendicular()) < T(0) ? -tmp.length() : tmp.length();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Co-sinus of angle between this and other 2D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Co-sinus of angle between this and other 2D vector
 * \details Used equation:
 * \f$\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}}\f$
 */
template <typename T>
inline T Vec2<T>::cosAngle(const Vec2<T> &_other) const
{
    const T lenSq = lengthSquared() * _other.lengthSquared();
    if (Math::isNull(lenSq))
        return T(0);
    if (isUnit(lenSq))
        return dot(*this, _other);
    return dot(*this, _other) / std::sqrt(lenSq);
}

/*!
 * \brief <b>Power 2</b> of cosinus angle between this and other 2D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return <b>Power 2</b> of cosinus angle between this and other 2D vector
 */
template <typename T>
inline T Vec2<T>::cosAnglePow2(const Vec2<T> &_other) const
{
    const T lenSq = lengthSquared() * _other.lengthSquared();
    if (Math::isNull(lenSq))
        return T(0);
    const T result = dot(*this, _other);
    if (isUnit(lenSq))
        return result * result;
    return result * result / lenSq;
}

/*!
 * \brief Sinus of angle between this and other 2D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Sinus of angle between this and other 2D vector
 */
template <typename T>
inline T Vec2<T>::sinAngle(const Vec2<T> &_other) const
{
    return std::sqrt(sinAnglePow2(_other));
}

/*!
 * \brief Sinus of angle between this and other 2D vector
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Sinus of angle between this and other 2D vector
 */
template <typename T>
inline T Vec2<T>::sinAnglePow2(const Vec2<T> &_other) const
{
    return T(1) - cosAnglePow2(_other);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Angle between this and other 2D vector in radians
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Angle between this and other 2D vector in radians
 * \note Result angle range: \f$\langle 0, \pi \rangle\f$
 * \details Used equation:
 * \f$acos(\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}})\f$
 */
template <typename T>
inline T Vec2<T>::angleRad(const Vec2<T> &_other) const
{
    const T lenSq = lengthSquared() * _other.lengthSquared();
    if (Math::isNull(lenSq))
        return T(0);
    T result = dot(*this, _other);
    if (!isUnit(lenSq))
        result /= std::sqrt(lenSq);
    return std::acos(std::min(T(1), std::max(T(-1), result)));
}

/*!
 * \brief Angle between this and other 2D vector in degrees
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Angle between this and other 2D vector in degrees
 * \note Result angle range: \f$\langle 0, 180 \rangle\f$ degrees
 */
template <typename T>
inline T Vec2<T>::angleDeg(const Vec2<T> &_other) const
{
    return toDeg(angleRad(_other));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Oriented angle between this and other 2D vector in radians
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Angle between this and other 2D vector in radians
 */
template <typename T>
inline T Vec2<T>::angleOrientedRad(const Vec2<T> &_other) const
{
    const T _dot = x * _other.x + y * _other.y;
    const T _det = x * _other.y - y * _other.x;
    return std::atan2(_det, _dot);
}

/*!
 * \brief Oriented angle between this and other 2D vector in degrees
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return Angle between this and other 2D vector in degrees
 */
template <typename T>
inline T Vec2<T>::angleOrientedDeg(const Vec2<T> &_other) const
{
    return toDeg(angleOrientedRad(_other));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculates Bezier interpolated value
 * \param _ratio Ratio (0 to 1)
 * \param _fromPoint From point
 * \param _fromDirection From direction
 * \param _toPoint To point
 * \param _toDirection To direction
 * \return Bezier interpolated value
 */
template <typename T>
Vec2<T> Vec2<T>::bezier(const T _ratio,
                        const Vec2<T> &_fromPoint,
                        const Vec2<T> &_fromDirection,
                        const Vec2<T> &_toPoint,
                        const Vec2<T> &_toDirection)
{
    const T t = Math::alignedTo0_1(_ratio);
    const T tt = T(1) - t;
    return _fromPoint * (tt * tt * tt) + (_fromPoint + _fromDirection) * (T(3) * tt * tt * t) +
        (_toPoint - _toDirection) * (T(3) * tt * t * t) + _toPoint * (t * t * t);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create ratio vector (point between input vectors)
 * \tparam T Template floating point type
 * \param _v1 Vector 1
 * \param _v2 Vector 2
 * \param _value1 Value for vector 1
 * \param _value2 Value for vector 2
 * \param _valueCenter Value for result vector
 * \return Ratio vector
 */
template <typename T>
Vec2<T>
Vec2<T>::betweenByValue(const Vec2<T> &_v1, const Vec2<T> &_v2, const T _value1, const T _value2, const T _valueCenter)
{
    return _v1 + (_v2 - _v1) * ((_valueCenter - _value1) / (_value2 - _value1));
}

/*!
 * \brief Create ratio vector (point between input vectors)
 * \param _v1 Vector 1
 * \param _v2 Vector 2
 * \param _ratio Ratio for output position
 * \return Ratio vector
 */
template <typename T>
Vec2<T> Vec2<T>::betweenByRatio(const Vec2<T> &_v1, const Vec2<T> &_v2, const T _ratio)
{
    return betweenByValue(_v1, _v2, T(0), T(1), _ratio);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Vector
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Vec2<T> &_v)
{
    return _os << '[' << _v.x << ',' << _v.y << ']';
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Conversion to \c QVector2D
 * \tparam T Template floating point type
 * \return This 2D vector as \c QVector2D
 */
template <typename T>
inline QVector2D Vec2<T>::toQVector2D() const
{
    return QVector2D(x, y);
}

/*!
 * \brief Conversion from \c QVector2D
 * \tparam T Template floating point type
 * \param _value Input \c QVector2D vector
 * \return 2D vector from \c QVector2D
 */
template <typename T>
Vec2<T> Vec2<T>::fromQVector2D(const QVector2D &_value)
{
    return Vec2<T>(_value.x(), _value.y());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculate hash value
 * \tparam T Template floating point type
 * \return Hash value from data
 */
template <typename T>
inline size_t Vec2<T>::toHash() const
{
    return Math::mixHash(std::hash<T>{}(x), std::hash<T>{}(y));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Vec2<float> Vec2F;        //!< 32 bit floating point precision 2D vector
typedef Vec2<double> Vec2D;       //!< 64 bit floating point precision 2D vector
typedef Vec2<long double> Vec2L;  //!< 128 bit floating point precision 2D vector

}  // namespace Math
}  // namespace U1

#endif  // MATH_VEC2_H
