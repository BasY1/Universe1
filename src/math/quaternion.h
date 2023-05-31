/*!
 * \file math/quaternion.h
 * \author Michal Steller
 * \brief 3D Quaternion template implementation
 */

#ifndef UNIVERSE1_MATH_QUATERNION_H
#define UNIVERSE1_MATH_QUATERNION_H

#include "vec3.h"

#ifdef UNIVERSE1_USE_QT_LIB
#include <QQuaternion>
#endif

namespace Universe1 {
namespace Math {

/*!
 * \brief 3D quaternion template for various floating point types
 * \tparam T Template floating point type
 */
template <typename T>
struct Quaternion
{
    /*! \brief The anonymous union, for indexed component access or access by component name */
    union
    {
        /*!
         * \brief Union array representation, access quaternion component by axis index
         * \details
         * | Index | Component |
         * | :---- | :-------- |
         * | 0     | Axis X    |
         * | 1     | Axis Y    |
         * | 2     | Axis Z    |
         * | 3     | Angle W   |
         */
        T m_data[4];

        /*! \brief The anonymous structure, access quaternion component by axis name */
        struct
        {
            /*! \brief The anonymous union for vector access */
            union
            {
                Vec3<T> m_vec;  //!< Union axis vector representation

                /*! \brief The anonymous structure, access vector component by axis name */
                struct
                {
                    T x;  //!< Union \b X axis (first) component representation
                    T y;  //!< Union \b Y axis (second) component representation
                    T z;  //!< Union \b Z axis (third) component representation
                };
            };

            T w;  //!< Union \b W angle component representation
        };
    };

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Quaternion()
        : x(T(0))
        , y(T(0))
        , z(T(0))
        , w(T(0))
    {
    }

    /*!
     * \brief Constructor with vector components
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Quaternion(const T _x,  //!< X component
                      const T _y,  //!< Y component
                      const T _z,  //!< Z component
                      const T _w)  //!< W component
        : x(_x)
        , y(_y)
        , z(_z)
        , w(_w)
    {
    }

    /*!
     * \brief Constructor from other vector
     * \param _other Other vector
     * \param _w W component
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Quaternion(const Vec3<T> &_other, const T _w)
        : x(_other.x)
        , y(_other.y)
        , z(_other.z)
        , w(_w)
    {
    }

    inline bool isNull() const;
    inline bool isIdentity() const;

    inline bool equals(const Quaternion<T> &_other) const;
    inline bool operator==(const Quaternion<T> &_other) const;
    inline bool operator!=(const Quaternion<T> &_other) const;

    inline void clear();

    inline Quaternion<T> &operator+=(const Quaternion<T> &_value);
    inline Quaternion<T> &operator-=(const Quaternion<T> &_value);
    inline Quaternion<T> &operator*=(const T _value);
    inline Quaternion<T> &operator*=(const Quaternion<T> &_value);
    inline Quaternion<T> &operator/=(const T _value);

    inline Quaternion<T> inverted() const;
    inline void invert();

    inline bool isNormalized() const;
    inline Quaternion<T> normalized() const;
    inline void normalize();

    inline Quaternion<T> conjugated() const;
    inline void conjugate();

    inline T lengthSquared() const;
    inline T length() const;

    Vec3<T> rotated(const Vec3<T> &_vector) const;
    void rotate(Vec3<T> &_vector) const;

    static Quaternion<T> fromTwoVectors(const Vec3<T> &_from, const Vec3<T> &_to, bool *_outOk = nullptr);

    static Quaternion<T> fromAxisAndAngle(const Vec3<T> &_axis, const T _angleRad);
    static Quaternion<T> fromAxisAndAngle(const T _x, const T _y, const T _z, const T _angleRad);

    inline std::string toString(const int _decimals = -1) const;
    inline std::string toStringFull(const int _decimals = -1) const;

#ifdef UNIVERSE1_USE_QT_LIB
    inline QQuaternion toQQuaternion() const;
    static Quaternion<T> fromQQuaternion(const QQuaternion &_value);

    inline QString toQString(const int _decimals = -1) const;
    inline QString toQStringFull(const int _decimals = -1) const;
#endif

    /*!
     * \brief Conversion to different precision
     * \tparam T2 Output template floating point type
     * \return Vector in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    inline Quaternion<T2> converted() const
    {
        return Quaternion<T2>(x, y, z, w);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if quaternion is null
 * \tparam T Template floating point type
 * \return \c true if quaternion is null
 */
template <typename T>
inline bool Quaternion<T>::isNull() const
{
    return Math::isNull<T>(x) && Math::isNull<T>(y) && Math::isNull<T>(z) && Math::isNull<T>(w);
}

/*!
 * \brief Test if quaternion is null
 * \tparam T Template floating point type
 * \return \c true if quaternion is null
 */
template <typename T>
inline bool Quaternion<T>::isIdentity() const
{
    return Math::isNull<T>(x) && Math::isNull<T>(y) && Math::isNull<T>(z) && Math::isUnit<T>(w);
}

/*!
 * \brief Test if quaternions are equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if quaternions are equal
 * \sa TypeEquals<T>(const T, const T)
 */
template <typename T>
inline bool Quaternion<T>::equals(const Quaternion<T> &_other) const
{
    return Math::equals<T>(x, _other.x) && Math::equals<T>(y, _other.y) && Math::equals<T>(z, _other.z) &&
        Math::equals<T>(w, _other.w);
}

/*!
 * \brief Operator for test if quaternions are equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if quaternions are equal
 * \sa Quaternion<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Quaternion<T>::operator==(const Quaternion<T> &_other) const
{
    return equals(_other);
}

/*!
 * \brief Operator for test if quaternions are not equal
 * \tparam T Template floating point type
 * \param _other Other vector
 * \return \c true if quaternions are not equal
 * \sa Quaternion<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Quaternion<T>::operator!=(const Quaternion<T> &_other) const
{
    return !equals(_other);
}

/*!
 * \brief Clear quaternion
 * \tparam T Template floating point type
 */
template <typename T>
inline void Quaternion<T>::clear()
{
    x = T(0);
    y = T(0);
    z = T(0);
    w = T(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Add other quaternion
 * \tparam T Template floating point type
 * \param _value Other quaternion
 * \return \c this quaternion pointer
 */
template <typename T>
inline Quaternion<T> &Quaternion<T>::operator+=(const Quaternion<T> &_value)
{
    x += _value.x;
    y += _value.y;
    z += _value.z;
    w += _value.w;
    return *this;
}

/*!
 * \brief Subtract other quaternion
 * \tparam T Template floating point type
 * \param _value Other quaternion
 * \return \c this quaternion pointer
 */
template <typename T>
inline Quaternion<T> &Quaternion<T>::operator-=(const Quaternion<T> &_value)
{
    x -= _value.x;
    y -= _value.y;
    z -= _value.z;
    w -= _value.w;
    return *this;
}

/*!
 * \brief Multiply quaternion by value
 * \tparam T Template floating point type
 * \param _value Value to multiply
 * \return \c this quaternion pointer
 */
template <typename T>
inline Quaternion<T> &Quaternion<T>::operator*=(const T _value)
{
    x *= _value;
    y *= _value;
    z *= _value;
    w *= _value;
    return *this;
}

/*!
 * \brief Multiply quaternion by other quaternion
 * \tparam T Template floating point type
 * \param _q1 First quaternion
 * \param _q2 Second quaternion
 * \return Result of quaternion multiplication
 */
template <typename T>
inline Quaternion<T> operator*(const Quaternion<T> &_q1, const Quaternion<T> &_q2)
{
    const T yy = (_q1.w - _q1.y) * (_q2.w + _q2.z);
    const T zz = (_q1.w + _q1.y) * (_q2.w - _q2.z);
    const T ww = (_q1.z + _q1.x) * (_q2.x + _q2.y);
    const T xx = ww + yy + zz;
    const T qq = T(0.5) * (xx + (_q1.z - _q1.x) * (_q2.x - _q2.y));
    return Quaternion<T>(qq - xx + (_q1.x + _q1.w) * (_q2.x + _q2.w),
                         qq - yy + (_q1.w - _q1.x) * (_q2.y + _q2.z),
                         qq - zz + (_q1.z + _q1.y) * (_q2.w - _q2.x),
                         qq - ww + (_q1.z - _q1.y) * (_q2.y - _q2.z));
}

/*!
 * \brief Multiply quaternion by other quaternion
 * \tparam T Template floating point type
 * \param _value Other quaternion
 * \return \c this quaternion pointer
 */
template <typename T>
inline Quaternion<T> &Quaternion<T>::operator*=(const Quaternion<T> &_value)
{
    *this = *this * _value;
    return *this;
}

/*!
 * \brief Divide quaternion by value
 * \tparam T Template floating point type
 * \param _value Value
 * \return \c this quaternion pointer
 */
template <typename T>
inline Quaternion<T> &Quaternion<T>::operator/=(const T _value)
{
    x /= _value;
    y /= _value;
    z /= _value;
    w /= _value;
    return *this;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sum operator for two quaternions
 * \tparam T Template floating point type
 * \param _v1 First quaternion
 * \param _v2 Second quaternion
 * \return Sum quaternions
 */
template <typename T>
inline Quaternion<T> operator+(const Quaternion<T> &_v1, const Quaternion<T> &_v2)
{
    return Quaternion<T>(_v1.x + _v2.x, _v1.y + _v2.y, _v1.z + _v2.zy, _v1.w + _v2.w);
}

/*!
 * \brief Subtract operator for two quaternions
 * \tparam T Template floating point type
 * \param _v1 First quaternion
 * \param _v2 Second quaternion
 * \return Subtract quaternions
 */
template <typename T>
inline Quaternion<T> operator-(const Quaternion<T> &_v1, const Quaternion<T> &_v2)
{
    return Quaternion<T>(_v1.x - _v2.x, _v1.y - _v2.y, _v1.z - _v2.z, _v1.w - _v2.w);
}

/*!
 * \brief Inverted operator
 * \tparam T Template floating point type
 * \param _v Quaternion
 * \return Inverted quaternion
 */
template <typename T>
inline Quaternion<T> operator-(const Quaternion<T> &_v)
{
    return _v.inverted();
}

/*!
 * \brief Multiply operator for quaternion by value
 * \tparam T Template floating point type
 * \param _v1 First quaternion
 * \param _v2 Second scalar value
 * \return Multiply of quaternion by value
 */
template <typename T>
inline Quaternion<T> operator*(const Quaternion<T> &_v1, const T _v2)
{
    return Quaternion<T>(_v1.x * _v2, _v1.y * _v2, _v1.z * _v2, _v1.w * _v2);
}

/*!
 * \brief Multiply operator for value by quaternion
 * \tparam T Template floating point type
 * \param _v1 First scalar value
 * \param _v2 Second quaternion
 * \return Multiply of value by quaternion
 */
template <typename T>
inline Quaternion<T> operator*(const T _v1, const Quaternion<T> &_v2)
{
    return Quaternion<T>(_v1 * _v2.x, _v1 * _v2.y, _v1 * _v2.z, _v1 * _v2.w);
}

/*!
 * \brief Divide operator for quaternion by value
 * \tparam T Template floating point type
 * \param _v1 First quaternion
 * \param _v2 Second scalar value
 * \return Divide of quaternion by value
 */
template <typename T>
inline Quaternion<T> operator/(const Quaternion<T> &_v1, const T _v2)
{
    return Quaternion<T>(_v1.x / _v2, _v1.y / _v2, _v1.z / _v2, _v1.w / _v2);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns inverted quaternion
 * \tparam T Template floating point type
 * \return Inverted quaternion
 */
template <typename T>
inline Quaternion<T> Quaternion<T>::inverted() const
{
    return Quaternion<T>(-x, -y, -z, -w);
}

/*!
 * \brief Inverts this quaternion
 * \tparam T Template floating point type
 */
template <typename T>
inline void Quaternion<T>::invert()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if quaternion is normalized
 * \tparam T Template floating point type
 * \return \c true if quaternion is normalized
 */
template <typename T>
inline bool Quaternion<T>::isNormalized() const
{
    return isUnit<T>(lengthSquared());
}

/*!
 * \brief Returns normalized quaternion
 * \tparam T Template floating point type
 * \return Normalized quaternion
 */
template <typename T>
inline Quaternion<T> Quaternion<T>::normalized() const
{
    T lenSq = lengthSquared();
    if (Math::isNull<T>(lenSq) || isUnit<T>(lenSq))
        return *this;
    lenSq = std::sqrt(lenSq);
    return Quaternion<T>(x / lenSq, y / lenSq, z / lenSq, w / lenSq);
}

/*!
 * \brief Normalize this quaternion
 * \tparam T Template floating point type
 */
template <typename T>
inline void Quaternion<T>::normalize()
{
    const T lenSq = lengthSquared();
    if (!Math::isNull<T>(lenSq) && !isUnit<T>(lenSq))
        *this /= std::sqrt(lenSq);
}

/*!
 * \brief Returns conjugated quaternion
 * \tparam T Template floating point type
 * \return Conjugated quaternion
 */
template <typename T>
inline Quaternion<T> Quaternion<T>::conjugated() const
{
    return Quaternion<T>(-x, -y, -z, w);
}

/*!
 * \brief Conjugate this quaternion
 * \tparam T Template floating point type
 */
template <typename T>
inline void Quaternion<T>::conjugate()
{
    x = -x;
    y = -y;
    z = -z;
}

/*!
 * \brief Returns quaternion length squared
 * \tparam T Template floating point type
 * \return Quaternion length squared
 */
template <typename T>
inline T Quaternion<T>::lengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}

/*!
 * \brief Returns quaternion length
 * \tparam T Template floating point type
 * \return Quaternion length
 */
template <typename T>
inline T Quaternion<T>::length() const
{
    return std::sqrt(lengthSquared());
}

/*!
 * \brief Returns rotated vector by this quaternion
 * \tparam T Template floating point type
 * \param _vector Vector to rotate
 * \return Rotated vector by this quaternion
 */
template <typename T>
inline Vec3<T> Quaternion<T>::rotated(const Vec3<T> &_vector) const
{
    return (*this * Quaternion<T>(_vector, T(0)) * conjugated()).m_vec;
}

/*!
 * \brief Rotates vector by this quaternion
 * \tparam T Template floating point type
 * \param _vector Vector to rotate
 */
template <typename T>
inline void Quaternion<T>::rotate(Vec3<T> &_vector) const
{
    _vector = rotated(_vector);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create Quaternion from two vectors
 * \tparam T Template floating point type
 * \param _from From direction
 * \param _to To direction
 * \param _outOk Success flag
 * \return Quaternion from two vectors
 */
template <typename T>
Quaternion<T> Quaternion<T>::fromTwoVectors(const Vec3<T> &_from, const Vec3<T> &_to, bool *_outOk)
{
    const Vec3<T> v0 = _from.normalized();
    const Vec3<T> v1 = _to.normalized();

    T d = Vec3<T>::dot(v0, v1) + T(1);
    if (Math::isNull<T>(d))
    {
        if (_outOk != nullptr)
            *_outOk = false;
        // qDebug() << "null";
        Vec3<T> axis = Vec3<T>::cross(Vec3<T>::unitX(), v0);
        if (axis.isNull())
            axis = Vec3<T>::cross(Vec3<T>::unitY(), v0);
        // return Quaternion<T>(axis.normalized(), T(0));
        return fromAxisAndAngle(axis, T(M_PI));
    }
    if (_outOk != nullptr)
        *_outOk = true;

    d = std::sqrt(T(2) * d);
    const Vec3<T> axis(Vec3<T>::cross(v0, v1) / d);
    return Quaternion<T>(axis, d * 0.5f).normalized();
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create quaternion from axis and angle
 * \tparam T Template floating point type
 * \param _axis Axis direction
 * \param _angleRad Angle in radians
 * \return Quaternion from axis and angle
 */
template <typename T>
Quaternion<T> Quaternion<T>::fromAxisAndAngle(const Vec3<T> &_axis, const T _angleRad)
{
    const T h = _angleRad * T(0.5);
    const T s = std::sin(h);
    const Vec3<T> axis = _axis.normalized();
    return Quaternion<T>(axis.x * s, axis.y * s, axis.z * s, std::cos(h)).normalized();
}

/*!
 * \brief Create quaternion from axis and angle
 * \tparam T Template floating point type
 * \param _x \b X axis direction
 * \param _y \b Y axis direction
 * \param _z \b Z axis direction
 * \param _angleRad Angle in radians
 * \return Quaternion from axis and angle
 */
template <typename T>
Quaternion<T> Quaternion<T>::fromAxisAndAngle(const T _x, const T _y, const T _z, const T _angleRad)
{
    return fromAxisAndAngle(Vec3<T>(_x, _y, _z), _angleRad);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef UNIVERSE1_USE_QT_LIB

/*!
 * \brief Conversion to \c QQuaternion
 * \return This quaternion as \c QQuaternion
 */
template <typename T>
inline QQuaternion Quaternion<T>::toQQuaternion() const
{
    return QQuaternion(w, x, y, z);
}

/*!
 * \brief Conversion from \c QQuaternion
 * \param _value Input \c QQuaternion vector
 * \return Quaternion from \c QQuaternion
 */
template <typename T>
Quaternion<T> Quaternion<T>::fromQQuaternion(const QQuaternion &_value)
{
    return Quaternion<T>(_value.x(), _value.y(), _value.z(), _value.scalar());
}

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Quaternion
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Quaternion<T> &_v)
{
    return _os << '[' << _v.x << ',' << _v.y << ',' << _v.z << '|' << _v.w << ']';
}

/*!
 * \brief To \c std::string
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Quaternion as \c std::string
 */
template <typename T>
inline std::string Quaternion<T>::toString(const int _decimals) const
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
 * \return Quaternion as \c std::string
 */
template <typename T>
inline std::string Quaternion<T>::toStringFull(const int _decimals) const
{
    std::stringstream ss;
    if (_decimals >= 0)
    {
        ss.precision(_decimals);
        ss << std::fixed;
    }
    ss << '[' << x << ',' << y << ',' << z << '(' << w << ")|" << length() << ']';
    return ss.str();
}

#ifdef UNIVERSE1_USE_QT_LIB

/*!
 * \brief To \c QString
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Quaternion as \c QString
 */
template <typename T>
inline QString Quaternion<T>::toQString(const int _decimals) const
{
    return QString::fromStdString(toString(_decimals));
}

/*!
 * \brief To \c QString with length
 * \tparam T Template floating point type
 * \param _decimals Decimal count (-1 for default precision)
 * \return Quaternion as \c QString
 */
template <typename T>
inline QString Quaternion<T>::toQStringFull(const int _decimals) const
{
    return QString::fromStdString(toStringFull(_decimals));
}

#endif

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_MATH_QUATERNION_H
