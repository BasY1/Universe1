/*!
 * \file src/Math/vec3.h
 * \brief 3D vector template implementation
 */

#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "vec2.h"
#include "colorrgb.h"
#include <thread>

namespace U1 {
namespace Math {

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

        /*! \brief The anonymous structure, access vector component by color name */
        struct
        {
            T r;  //!< Union \b red component representation
            T g;  //!< Union \b green component representation
            T b;  //!< Union \b blue component representation
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
     * \param other Other vector
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Vec3(const Vec3<T> &other)
        : x(other.x)
        , y(other.y)
        , z(other.z)
    {
    }

    static Vec3<T> unitX();
    static Vec3<T> unitY();
    static Vec3<T> unitZ();

    static Vec3<T> lowestValue();
    static Vec3<T> maximumValue();

    static Vec3<T> minimum(const Vec3<T> &_v1, const Vec3<T> &_v2);
    static Vec3<T> maximum(const Vec3<T> &_v1, const Vec3<T> &_v2);

    inline void updateRange(Vec3<T> &_minimum, Vec3<T> &_maximum) const;
    static void updateRange(Vec3<T> &_minimum, Vec3<T> &_maximum, const std::pair<Vec3<T>, Vec3<T>> &_data);

    inline static void
    updateRange(Vec3<T> &_minimum, Vec3<T> &_maximum, const Vec3<T> &_dataMinimum, const Vec3<T> &_dataMaximum);

    static bool isAligned(const Vec3<T> &_v, const Vec3<T> &_min, const Vec3<T> &_max);
    inline bool isAligned(const Vec3<T> &_min, const Vec3<T> &_max) const;

    inline bool isNull() const;
    inline bool equals(const Vec3<T> &other) const;
    inline bool operator==(const Vec3<T> &other) const;
    inline bool operator!=(const Vec3<T> &other) const;

    static int8_t compare(const Vec3<T> &_v1, const Vec3<T> &_v2);
    static bool isLessNotEqual(const Vec3<T> &_v1, const Vec3<T> &_v2);

    inline T minimumComponnentValue() const;
    inline T minimumComponnentValueAbs() const;
    inline T maximumComponnentValue() const;
    inline T maximumComponnentValueAbs() const;

    inline uint8_t minimumComponnentIndex() const;
    inline uint8_t minimumComponnentIndexAbs() const;
    inline uint8_t maximumComponnentIndex() const;
    inline uint8_t maximumComponnentIndexAbs() const;

    inline void clear();

    inline Vec3<T> &operator+=(const Vec3<T> &value);
    inline Vec3<T> &operator-=(const Vec3<T> &value);
    inline Vec3<T> &operator*=(const T value);
    inline Vec3<T> &operator/=(const T value);

    inline Vec3<T> inverted() const;
    inline void invert();

    inline bool isUnit() const;
    inline bool isNormalized() const;
    inline Vec3<T> normalized() const;
    inline void normalize();

    inline bool isPerpendicular(const Vec3<T> &other) const;
    inline Vec3<T> perpendicularNormal() const;
    inline Vec3<T> perpendicularNormalUp() const;
    static void makePerpendicularNormals(Vec3<T> &_normal1, Vec3<T> &_normal2);

    inline bool isSameDir(const Vec3<T> &other) const;
    inline bool isParallel(const Vec3<T> &other) const;
    inline bool isParallelInDir(const Vec3<T> &other, bool &isSameDirection) const;

    static T dot(const Vec3<T> &v1, const Vec3<T> &v2);

    static T helicitySign(const Vec3<T> &spin, const Vec3<T> &movement);
    static Helicity helicity(const Vec3<T> &spin, const Vec3<T> &movement);

    static Vec3<T> cross(const Vec3<T> &v1, const Vec3<T> &v2);
    static Vec3<T> crossLeftHand(const Vec3<T> &v1, const Vec3<T> &v2);
    static Vec3<T> crossByHand(const Vec3<T> &v1, const Vec3<T> &v2, const bool rightHanded);

    inline T lengthSquared() const;
    inline T length() const;
    static void minMaxLength(T &_outMinimum,
                             T &_outMaximum,
                             const Vec3<T> *_data,
                             const size_t _count,
                             const std::vector<std::pair<size_t, size_t>> &_pool);

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

    static Vec3<T> rotate(const Vec3<T> &_point, const Vec3<T> &_normal, const T _sinAngle, const T _cosAngle);
    static Vec3<T> rotate(const Vec3<T> &_point, const Vec3<T> &_normal, const T _angleRad);
    inline Vec3<T> rotated(const Vec3<T> &_normal, const T _sinAngle, const T _cosAngle) const;
    inline Vec3<T> rotated(const Vec3<T> &_normal, const T _angleRad) const;
    inline Vec3<T> rotatedDeg(const Vec3<T> &_normal, const T _angleDeg) const;

    static Vec3<T> bezier(const T _ratio,
                          const Vec3<T> &_fromPoint,
                          const Vec3<T> &_fromDirection,
                          const Vec3<T> &_toPoint,
                          const Vec3<T> &_toDirection);

    static Vec3<T>
    ratio(const Vec3<T> &_v1, const Vec3<T> &_v2, const T _value1, const T _value2, const T _valueCenter);

    inline QVector3D toQVector3D() const;
    static Vec3<T> fromQVector3D(const QVector3D &_value);

    static Vec3<T> fromQColor(const QColor &_value);
    inline QColor toQColor() const;

    static Vec3<T> fromColor(const ColorRGB &_value);
    inline ColorRGB toColor() const;

    inline Vec2<T> toVec2(const uint8_t _skipAxis = 2U) const;

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

    template <typename T2>
    static void convertedData(Vec3<T2> *_out,
                              const Vec3<T> *_in,
                              const size_t _count,
                              const std::vector<std::pair<size_t, size_t>> &_pool);

    inline size_t toHash() const;

    static size_t mixHash(const Vec3<T> *_data, const size_t _count);
    inline static size_t mixHash(const std::vector<Vec3<T>> &_data);

    static size_t mixHash(const std::pair<Vec3<T>, Vec3<T>> *_data, const size_t _count);
    inline static size_t mixHash(const std::vector<std::pair<Vec3<T>, Vec3<T>>> &_data);

    inline std::string toString(const int _decimals = -1) const;
    inline QString toQString(const int _decimals = -1) const;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculate angle between 2 \c QVector3D
 * \param _v1 First \c QVector3D
 * \param _v2 Second \c QVector3D
 * \return Angle between 2 \c QVector3D in radians
 */
inline float angleRad(const QVector3D &_v1, const QVector3D &_v2)
{
    const float lenSq = _v1.lengthSquared() * _v2.lengthSquared();
    if (Math::isNull(lenSq))
        return 0.0f;
    float result = QVector3D::dotProduct(_v1, _v2);
    if (!isUnit<float>(lenSq))
        result /= std::sqrt(lenSq);
    return std::acos(std::min(1.0f, std::max(-1.0f, result)));
}

/*!
 * \brief Calculate angle between 2 \c QVector3D (in degrees)
 * \param _v1 First \c QVector3D
 * \param _v2 Second \c QVector3D
 * \return Angle between 2 \c QVector3D in degrees
 */
inline float angleDeg(const QVector3D &_v1, const QVector3D &_v2)
{
    return Math::toDeg(angleRad(_v1, _v2));
}

/*!
 * \brief Calculate rotated point position
 * \param _point Point to rotate
 * \param _normal Rotation normal
 * \param _angleRad Rotation angle in radians
 * \return Rotated point
 * \note Tool function for \c QVector3D type
 */
inline QVector3D rotatedVec3d(const QVector3D &_point, const QVector3D &_normal, const float _angleRad)
{
    const float lenSq = _normal.lengthSquared();
    if (qFuzzyIsNull(lenSq))
        return _point;

    const float sa = std::sin(_angleRad);
    const float ca = std::cos(_angleRad);

    const QVector3D n = qFuzzyCompare(lenSq, 1.0f) ? _normal : (_normal / std::sqrt(lenSq));
    const QVector3D u = n.x() * _point;
    const QVector3D v = n.y() * _point;
    const QVector3D w = n.z() * _point;
    const float ux_vy_wz = (u.x() + v.y() + w.z());

    return QVector3D(n.x() * ux_vy_wz + sa * (v.z() - w.y()) +
                         ca * (_point.x() * (n.y() * n.y() + n.z() * n.z()) - n.x() * (v.y() + w.z())),
                     n.y() * ux_vy_wz + sa * (w.x() - u.z()) +
                         ca * (_point.y() * (n.x() * n.x() + n.z() * n.z()) - n.y() * (u.x() + w.z())),
                     n.z() * ux_vy_wz + sa * (u.y() - v.x()) +
                         ca * (_point.z() * (n.x() * n.x() + n.y() * n.y()) - n.z() * (u.x() + v.y())));
}

/*!
 * \brief Return unit vector that is perpendicular to the base vector
 * \param _normal Base vector
 * \return A vector perpendicular to the base vector
 * \note Tool function for \c QVector3D type
 */
inline QVector3D perpendicularNormal(const QVector3D &_normal)
{
    if (Math::isNull<float>(_normal.y()) && Math::isNull<float>(_normal.z()))
        return QVector3D::crossProduct(_normal, {0, 1, 0}).normalized();
    else
        return QVector3D::crossProduct(_normal, {1, 0, 0}).normalized();
}

/*!
 * \brief Return unit vector that is perpendicular to the base vector
 * \param _normal Base vector
 * \return A vector perpendicular to the base vector
 * \note Tool function for \c QVector3D type
 */
inline QVector3D perpendicularNormalUp(const QVector3D &_normal)
{
    if (Math::isNull<float>(_normal.x()) && Math::isNull<float>(_normal.y()))
        return QVector3D(1, 0, 0);
    else
        return QVector3D::crossProduct(QVector3D::crossProduct(_normal, {0, 0, 1}).normalized(), _normal).normalized();
}

/*!
 * \brief Fix two vector to be unit vectors that are perpendicular each other
 * \param _normal Major normal
 * \param _arm Secondary normal
 * \note Tool function for \c QVector3D type
 */
inline void fixPerpendicular(QVector3D &_normal, QVector3D &_arm)
{
    float tmp = _normal.lengthSquared();
    if (Math::isNull<float>(tmp))
        _normal = {1, 0, 0};
    else if (!isUnit<float>(tmp))
        _normal = _normal / std::sqrt(tmp);

    tmp = _arm.lengthSquared();
    if (Math::isNull<float>(tmp))
    {
        _arm = perpendicularNormal(_normal);
    }
    else if (Math::isNull<float>(QVector3D::dotProduct(_normal, _arm)))
    {
        if (!isUnit<float>(tmp))
            _arm = _arm / std::sqrt(tmp);
    }
    else
    {
        const QVector3D perpNorm = QVector3D::crossProduct(_normal, _arm);
        if (perpNorm.isNull())
            _arm = perpendicularNormal(_normal);
        else
            _arm = QVector3D::crossProduct(perpNorm, _normal).normalized();
    }
}

/*!
 * \brief Test if floating point value is within range
 * \tparam T Template floating point type
 * \param _value Value to check
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return \c true if \a _value is in range
 * \note Tool function for \c QVector3D type
 */

inline bool isAlignedVec(const QVector3D &_value, const QVector3D &_minimum, const QVector3D &_maximum)
{
    return isAligned<float>(_value.x(), _minimum.x(), _maximum.x()) &&
        isAligned<float>(_value.y(), _minimum.y(), _maximum.y()) &&
        isAligned<float>(_value.z(), _minimum.z(), _maximum.z());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns a vector with lowest possible values of its components
 * \tparam T Template floating point type
 * \return Vector with lowest possible values of its components
 */
template <typename T>
Vec3<T> Vec3<T>::lowestValue()
{
    return Vec3<T>(
        std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest());
}

/*!
 * \brief Returns a vector with maximum possible values of its components
 * \tparam T Template floating point type
 * \return Vector with maximum possible values of its components
 */
template <typename T>
Vec3<T> Vec3<T>::maximumValue()
{
    return Vec3<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
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
Vec3<T> Vec3<T>::minimum(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return {std::min(_v1.x, _v2.x), std::min(_v1.y, _v2.y), std::min(_v1.z, _v2.z)};
}

/*!
 * \brief Create a vector with maximum values of its components from given vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return Vector with maximum values of its components
 */
template <typename T>
Vec3<T> Vec3<T>::maximum(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return {std::max(_v1.x, _v2.x), std::max(_v1.y, _v2.y), std::max(_v1.z, _v2.z)};
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Update range
 * \tparam T Template floating point type
 * \param _minimum Output range minimum
 * \param _maximum Output range maximum
 */
template <typename T>
void Vec3<T>::updateRange(Vec3<T> &_minimum, Vec3<T> &_maximum) const
{
    if (_minimum.x > x)
        _minimum.x = x;
    if (_minimum.y > y)
        _minimum.y = y;
    if (_minimum.z > z)
        _minimum.z = z;
    if (_maximum.x < x)
        _maximum.x = x;
    if (_maximum.y < y)
        _maximum.y = y;
    if (_maximum.z < z)
        _maximum.z = z;
}

/*!
 * \brief Update range
 * \tparam T Template floating point type
 * \param _minimum Output range minimum
 * \param _maximum Output range maximum
 * \param _data Pair with partial minimum and maximum values
 * \return
 */
template <typename T>
void Vec3<T>::updateRange(Vec3<T> &_minimum, Vec3<T> &_maximum, const std::pair<Vec3<T>, Vec3<T>> &_data)
{
    if (_minimum.x > _data.first.x)
        _minimum.x = _data.first.x;
    if (_minimum.y > _data.first.y)
        _minimum.y = _data.first.y;
    if (_minimum.z > _data.first.z)
        _minimum.z = _data.first.z;
    if (_maximum.x < _data.second.x)
        _maximum.x = _data.second.x;
    if (_maximum.y < _data.second.y)
        _maximum.y = _data.second.y;
    if (_maximum.z < _data.second.z)
        _maximum.z = _data.second.z;
}

/*!
 * \brief Update range
 * \tparam T Template floating point type
 * \param _minimum Output range minimum
 * \param _maximum Output range maximum
 * \param _dataMinimum Minimum partial value
 * \param _dataMaximum Maximum partial value
 * \return
 */
template <typename T>
inline void
Vec3<T>::updateRange(Vec3<T> &_minimum, Vec3<T> &_maximum, const Vec3<T> &_dataMinimum, const Vec3<T> &_dataMaximum)
{
    updateRange(_minimum, _maximum, {_dataMinimum, _dataMaximum});
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
bool Vec3<T>::isAligned(const Vec3<T> &_v, const Vec3<T> &_min, const Vec3<T> &_max)
{
    return Math::isAligned(_v.x, _min.x, _max.x) && Math::isAligned(_v.y, _min.y, _max.y) &&
        Math::isAligned(_v.z, _min.z, _max.z);
}

/*!
 * \brief Test if this vector is within range
 * \tparam T Template floating point type
 * \param _min Vector - range minimum
 * \param _max Vector - range maximum
 * \return \c true if all components fits given range
 */
template <typename T>
inline bool Vec3<T>::isAligned(const Vec3<T> &_min, const Vec3<T> &_max) const
{
    return Vec3<T>::isAligned(*this, _min, _max);
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
inline bool Vec3<T>::isNull() const
{
    return Math::isNull<T>(x) && Math::isNull<T>(y) && Math::isNull<T>(z);
}

/*!
 * \brief Test if vectors are equal
 * \tparam T Template floating point type
 * \param other Other vector
 * \return \c true if vectors are equal
 * \sa TypeEquals<T>(const T, const T)
 */
template <typename T>
inline bool Vec3<T>::equals(const Vec3<T> &other) const
{
    return Math::equals<T>(x, other.x) && Math::equals<T>(y, other.y) && Math::equals<T>(z, other.z);
}

/*!
 * \brief Operator for test if vectors are equal
 * \tparam T Template floating point type
 * \param other Other vector
 * \return \c true if vectors are equal
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
 * \return \c true if vectors are not equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T> &other) const
{
    return !equals(other);
}

/*!
 * \brief Compare 3D vectors
 * \tparam T Template floating point type
 * \param _v1 First vector
 * \param _v2 Second vector
 * \return -1, 0 or 1
 */
template <typename T>
int8_t Vec3<T>::compare(const Vec3<T> &_v1, const Vec3<T> &_v2)
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
    diff = _v1.z - _v2.z;
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
bool Vec3<T>::isLessNotEqual(const Vec3<T> &_v1, const Vec3<T> &_v2)
{
    return Math::isLessNotEqual(_v1.x, _v2.x) && Math::isLessNotEqual(_v1.y, _v2.y) &&
        Math::isLessNotEqual(_v1.z, _v2.z);
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
inline T Vec3<T>::minimumComponnentValue() const
{
    return std::min(std::min(x, y), z);
}

/*!
 * \brief Returns minimum absolute value from vector components
 * \tparam T Template floating point type
 * \return Minimum absolute value from vector components
 */
template <typename T>
inline T Vec3<T>::minimumComponnentValueAbs() const
{
    return std::min(std::min(std::abs(x), std::abs(y)), std::abs(z));
}

/*!
 * \brief Returns maximum value from vector components
 * \tparam T Template floating point type
 * \return Maximum value from vector components
 */
template <typename T>
inline T Vec3<T>::maximumComponnentValue() const
{
    return std::max(std::max(x, y), z);
}

/*!
 * \brief Returns maximum absolute value from vector components
 * \tparam T Template floating point type
 * \return Maximum absolute value from vector components
 */
template <typename T>
inline T Vec3<T>::maximumComponnentValueAbs() const
{
    return std::max(std::max(std::abs(x), std::abs(y)), std::abs(z));
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
inline uint8_t Vec3<T>::minimumComponnentIndex() const
{
    return (x < y) ? ((x < z) ? 0U : 2U) : ((y < z) ? 1U : 2U);
}

/*!
 * \brief Returns index of component with minimum absolute value
 * \tparam T Template floating point type
 * \return Index of component with minimum absolute value
 */
template <typename T>
inline uint8_t Vec3<T>::minimumComponnentIndexAbs() const
{
    const T _x = std::abs(x);
    const T _y = std::abs(y);
    const T _z = std::abs(z);
    return (_x < _y) ? ((_x < _z) ? 0U : 2U) : ((_y < _z) ? 1U : 2U);
}

/*!
 * \brief Returns index of component with maximum value
 * \tparam T Template floating point type
 * \return Index of component with maximum value
 */
template <typename T>
inline uint8_t Vec3<T>::maximumComponnentIndex() const
{
    return (x > y) ? ((x > z) ? 0U : 2U) : ((y > z) ? 1U : 2U);
}

/*!
 * \brief Returns index of component with maximum absolute value
 * \tparam T Template floating point type
 * \return Index of component with maximum absolute value
 */
template <typename T>
inline uint8_t Vec3<T>::maximumComponnentIndexAbs() const
{
    const T _x = std::abs(x);
    const T _y = std::abs(y);
    const T _z = std::abs(z);
    return (_x > _y) ? ((_x > _z) ? 0U : 2U) : ((_y > _z) ? 1U : 2U);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
 * \param value Other vector
 * \return \c this vector pointer
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
 * \return \c this vector pointer
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
 * \return \c this vector pointer
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
 * \return \c this vector pointer
 */
template <typename T>
inline Vec3<T> &Vec3<T>::operator/=(const T value)
{
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sum operator for two vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \return Sum vectors
 */
template <typename T>
inline Vec3<T> operator+(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return Vec3<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Subtract operator for two vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \return Subtract vectors
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
 * \return Inverted vector
 */
template <typename T>
inline Vec3<T> operator-(const Vec3<T> &v)
{
    return v.inverted();
}

/*!
 * \brief Tool plus operator
 * \tparam T Template floating point type
 * \param v Vector
 * \return Input vector
 */
template <typename T>
inline Vec3<T> operator+(const Vec3<T> &v)
{
    return v;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Multiply operator for vector by value
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second value
 * \return Multiply of vector by value
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
 * \return Multiply of value by vector
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
 * \return Divide of vector by value
 */
template <typename T>
inline Vec3<T> operator/(const Vec3<T> &v1, const T v2)
{
    return Vec3<T>(v1.x / v2, v1.y / v2, v1.z / v2);
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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if vector is an unit vector (length equals 1)
 * \tparam T Template floating point type
 * \return \c true if vector is normalized
 */
template <typename T>
inline bool Vec3<T>::isUnit() const
{
    return isNormalized();
}

/*!
 * \brief Test if vector is normalized (length equals 1)
 * \tparam T Template floating point type
 * \return \c true if vector is normalized
 */
template <typename T>
inline bool Vec3<T>::isNormalized() const
{
    return Math::isUnit<T>(lengthSquared());
    // return Math::isUnit<T>(length());
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
    if (Math::isNull<T>(lenSq) || Math::isUnit<T>(lenSq))
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
    if (!Math::isNull<T>(lenSq) && !Math::isUnit<T>(lenSq))
        *this /= std::sqrt(lenSq);
}

/*!
 * \brief Test if other vector is perpendicular to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \return \c true if vectors are perpendicular
 */
template <typename T>
inline bool Vec3<T>::isPerpendicular(const Vec3<T> &other) const
{
    return Math::isNull<T>(Vec3<T>::dot(*this, other));
}

/*!
 * \brief Return normalized vector that is perpendicular to this vector
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
 * \brief Return normalized vector that is perpendicular to the base vector, with respect to \b Z axis
 * \tparam T Template floating point type
 * \param _normal Base vector
 * \return A vector perpendicular to the base vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::perpendicularNormalUp() const
{
    if (Math::isNull<T>(x) && Math::isNull<T>(y))
        return unitX();
    else
        return Vec3<T>::cross(Vec3<T>::cross(*this, unitZ()), *this).normalized();
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
    else if (!Math::isUnit<T>(tmp))
        _normal1 = _normal1 / std::sqrt(tmp);

    tmp = _normal2.lengthSquared();
    if (Math::isNull<T>(tmp))
    {
        _normal2 = _normal1.perpendicularNormal();
    }
    else if (Math::isNull<T>(Vec3<T>::dot(_normal1, _normal2)))
    {
        if (!Math::isUnit<T>(tmp))
            _normal2 = _normal2 / std::sqrt(tmp);
    }
    else
    {
        const Vec3<T> perpNorm = Vec3<T>::cross(_normal1, _normal2);
        if (perpNorm.isNull())
            _normal2 = _normal1.perpendicularNormal();
        else
            _normal2 = Vec3<T>::cross(perpNorm, _normal1).normalized();
    }
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \return \c true if vectors are parallel
 */
template <typename T>
inline bool Vec3<T>::isSameDir(const Vec3<T> &other) const
{
    return !isNull() && Math::equals(dot(normalized(), other.normalized()), T(1));
}

/*!
 * \brief Test if other vector is parallel to this vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \return \c true if vectors are parallel
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
 * \return \c true if vectors are parallel
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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Dot product of two 3D vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \return Dot product of two 3D vectors
 */
template <typename T>
T Vec3<T>::dot(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

/*!
 * \brief Helicity sign-function
 * \tparam T Template floating point type
 * \param spin First vector
 * \param movement Second vector
 * \return Helicity sign-function 0, +1 or -1
 */
template <typename T>
T Vec3<T>::helicitySign(const Vec3<T> &spin, const Vec3<T> &movement)
{
    const T d = dot(spin, movement);
    if (Math::isNull(d))
        return T(0);
    return d < T(0) ? T(-1) : T(1);
}

/*!
 * \brief Helicity sign-function
 * \tparam T Template floating point type
 * \param spin First vector
 * \param movement Second vector
 * \return Helicity sign-function 0, +1 or -1
 */
template <typename T>
Helicity Vec3<T>::helicity(const Vec3<T> &spin, const Vec3<T> &movement)
{
    const T d = dot(spin, movement);
    if (Math::isNull(d))
        return _HelicityZero;
    return d < T(0) ? _HelicityLeft : _HelicityRight;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Right handed cross product of two 3D vectors
 * \tparam T Template floating point type
 * \param v1 First vector
 * \param v2 Second vector
 * \return Right handed cross product of two 3D vectors
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
 * \return Left handed cross product of two 3D vectors
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
 * \return Oriented cross product of two 3D vectors
 */
template <typename T>
Vec3<T> Vec3<T>::crossByHand(const Vec3<T> &v1, const Vec3<T> &v2, const bool rightHanded)
{
    return rightHanded ? cross(v1, v2) : crossLeftHand(v1, v2);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
 * \brief Calculate minimum and maximum vector length from vector collection
 * \tparam T Template floating point type
 * \param _outMinimum Output minimum vector length
 * \param _outMaximum Output maximum vector length
 * \param _data Pointer to 3D vector data array
 * \param _count Number of vectors
 * \param _pool Multi-thread indices
 * \return
 */
template <typename T>
void Vec3<T>::minMaxLength(T &_outMinimum,
                           T &_outMaximum,
                           const Vec3<T> *_data,
                           const size_t _count,
                           const std::vector<std::pair<size_t, size_t>> &_pool)
{
    if (_count == 0UL)
    {
        _outMinimum = T(0);
        _outMaximum = T(0);
        return;
    }

    if (_pool.empty())
    {
        T l = _data[0UL].length();
        _outMinimum = l;
        _outMaximum = l;
        for (size_t i = 1UL; i < _count; ++i)
        {
            l = _data[i].length();
            if (_outMinimum > l)
                _outMinimum = l;
            if (_outMaximum < l)
                _outMaximum = l;
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<T> tDataMin(_pool.size(), std::numeric_limits<T>::max());
        std::vector<T> tDataMax(_pool.size(), std::numeric_limits<T>::lowest());
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
        {
            threads.push_back(std::thread(
                [t](T &__outMin, T &__outMax, const Vec3<T> *__data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T l = __data[i].length();
                        if (__outMin > l)
                            __outMin = l;
                        if (__outMax < l)
                            __outMax = l;
                    }
                },
                std::ref(tDataMin[tt]),
                std::ref(tDataMax[tt]),
                _data));
            tt++;
        }
        for (std::thread &t : threads)
            t.join();
        _outMinimum = std::numeric_limits<T>::max();
        _outMaximum = std::numeric_limits<T>::lowest();
        for (const T &i : std::as_const(tDataMin))
            if (_outMinimum > i)
                _outMinimum = i;
        for (const T &i : std::as_const(tDataMax))
            if (_outMaximum < i)
                _outMaximum = i;
    }
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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns distance to point
 * \tparam T Template floating point type
 * \param point Other point
 * \return Distance to point
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
 * \return Distance to line
 */
template <typename T>
inline T Vec3<T>::distanceToLine(const Vec3<T> &linePoint, const Vec3<T> &lineNormal) const
{
    const T lenSq = lineNormal.lengthSquared();
    if (Math::isNull(lenSq))
        return T(0);
    return cross(*this - linePoint, lineNormal).length() / std::sqrt(lenSq);
}

/*!
 * \brief Returns distance to plane
 * \tparam T Template floating point type
 * \param planePoint Plane point
 * \param planeNormal Plane normal
 * \return Distance to plane
 */
template <typename T>
inline T Vec3<T>::distanceToPlane(const Vec3<T> &planePoint, const Vec3<T> &planeNormal) const
{
    const T lenSq = planeNormal.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    if (Math::isUnit<T>(lenSq))
        return dot(*this - planePoint, planeNormal);
    return dot(*this - planePoint, planeNormal) / std::sqrt(lenSq);
}

/*!
 * \brief Returns length of projection to other vector
 * \tparam T Template floating point type
 * \param projDirection Projection direction
 * \return Length of projection to other vector
 * \note Opposite directions have negative values
 */
template <typename T>
inline T Vec3<T>::projectedLength(const Vec3<T> &projDirection) const
{
    const T lenSq = projDirection.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    if (Math::isUnit<T>(lenSq))
        return dot(*this, projDirection);
    return dot(*this, projDirection) / std::sqrt(lenSq);
}

/*!
 * \brief Returns projection to other vector
 * \tparam T Template floating point type
 * \param projDirection Projection direction
 * \return Projection of this vector to other vector
 */
template <typename T>
inline Vec3<T> Vec3<T>::projected(const Vec3<T> &projDirection) const
{
    const T lenSq = projDirection.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return Vec3<T>();
    return projDirection * (dot(*this, projDirection) / lenSq);
}

/*!
 * \brief Returns projection on plane defined by normal
 * \tparam T Template floating point type
 * \param planeNormal Plane normal
 * \return Projection of this vector to other plane
 */
template <typename T>
inline Vec3<T> Vec3<T>::projectedOnPlane(const Vec3<T> &planeNormal) const
{
    return *this - projected(planeNormal);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Co-sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \return Co-sinus of angle between this and other 3D vector
 * \details Used equation:
 * \f$\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}}\f$
 */
template <typename T>
inline T Vec3<T>::cosAngle(const Vec3<T> &other) const
{
    const T lenSq = lengthSquared() * other.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    if (Math::isUnit<T>(lenSq))
        return dot(*this, other);
    return dot(*this, other) / std::sqrt(lenSq);
}

/*!
 * \brief <b>Power 2</b> of cosinus angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \return <b>Power 2</b> of cosinus angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::cosAnglePow2(const Vec3<T> &other) const
{
    const T lenSq = lengthSquared() * other.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    const T result = dot(*this, other);
    if (Math::isUnit<T>(lenSq))
        return result * result;
    return result * result / lenSq;
}

/*!
 * \brief Sinus of angle between this and other 3D vector
 * \tparam T Template floating point type
 * \param other Other vector
 * \return Sinus of angle between this and other 3D vector
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
 * \return Sinus of angle between this and other 3D vector
 */
template <typename T>
inline T Vec3<T>::sinAnglePow2(const Vec3<T> &other) const
{
    return Math::alignedTo0_1(T(1) - cosAnglePow2(other));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Angle between this and other 3D vector in radians
 * \tparam T Template floating point type
 * \param other Other vector
 * \return Angle between this and other 3D vector in radians
 * \note Result angle range: \f$\langle 0, \pi \rangle\f$
 * \details Used equation:
 * \f$acos(\frac{\vec{V_1}\cdot\vec{V_2}}{\sqrt{|\vec{V_1}|^2 |\vec{V_2}|^2}})\f$
 */
template <typename T>
inline T Vec3<T>::angleRad(const Vec3<T> &other) const
{
    const T lenSq = lengthSquared() * other.lengthSquared();
    if (Math::isNull<T>(lenSq))
        return T(0);
    T result = dot(*this, other);
    if (!Math::isUnit<T>(lenSq))
        result /= std::sqrt(lenSq);
    return std::acos(std::min(T(1), std::max(-T(1), result)));
}

/*!
 * \brief Angle between this and other 3D vector in degrees
 * \tparam T Template floating point type
 * \param other Other vector
 * \return Angle between this and other 3D vector in degrees
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
 * \return Angle between this and other 3D vector in radians
 * \note Returned angle is in range \f$( -\pi, pi \rangle\f$
 */
template <typename T>
inline T Vec3<T>::angleNormRad(const Vec3<T> &other, const Vec3<T> &normal) const
{
    const T result = angleRad(other);
    return Vec3<T>::dot(normal, Vec3<T>::cross(*this, other)) < T(0) ? -result : result;
}

/*!
 * \brief Angle between this and other 3D vector in degrees
 * \tparam T Template floating point type
 * \param v Other vector
 * \param normal Normal vector
 * \return Angle between this and other 3D vector in degrees
 * \note Result angle range: \f$( -180, 180 \rangle\f$ degrees
 */
template <typename T>
inline T Vec3<T>::angleNormDeg(const Vec3<T> &v, const Vec3<T> &normal) const
{
    return toDeg<T>(angleNormRad(v, normal));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    // const T sa = sin(_angleRad);
    // const T ca = cos(_angleRad);
    const Vec3<T> n = Math::isUnit<T>(lenSq) ? _normal : (_normal / std::sqrt(lenSq));
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
    return Vec3<T>::rotate(_point, _normal, std::sin(_angleRad), std::cos(_angleRad));
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

/*!
 * \brief Returns rotated point around normal by angle in degree
 * \tparam T Template floating point type
 * \param _normal Rotation normal (axis)
 * \param _angleDeg Angle in degree
 * \return Rotated point around normal by angle
 */
template <typename T>
inline Vec3<T> Vec3<T>::rotatedDeg(const Vec3<T> &_normal, const T _angleDeg) const
{
    return Vec3<T>::rotate(*this, _normal, toRad<T>(_angleDeg));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculates Bezier interpolated value
 * \tparam T Template floating point type
 * \param _ratio Ratio (0 to 1)
 * \param _fromPoint From point
 * \param _fromDirection From direction
 * \param _toPoint To point
 * \param _toDirection To direction
 * \return Bezier interpolated value
 */
template <typename T>
Vec3<T> Vec3<T>::bezier(const T _ratio,
                        const Vec3<T> &_fromPoint,
                        const Vec3<T> &_fromDirection,
                        const Vec3<T> &_toPoint,
                        const Vec3<T> &_toDirection)
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
 * \brief Ratio vector
 * \tparam T Template floating point type
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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Conversion to \c QVector3D
 * \tparam T Template floating point type
 * \return This 3D vector as \c QVector3D
 */
template <typename T>
inline QVector3D Vec3<T>::toQVector3D() const
{
    return QVector3D(x, y, z);
}

/*!
 * \brief Conversion from \c QVector3D
 * \tparam T Template floating point type
 * \param _value Input \c QVector3D vector
 * \return 3D vector from \c QVector3D
 */
template <typename T>
Vec3<T> Vec3<T>::fromQVector3D(const QVector3D &_value)
{
    return Vec3<T>(_value.x(), _value.y(), _value.z());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Take RGB factors from \c QColor
 * \tparam T Template floating point type
 * \param _value \c QColor
 * \return 3D vector from \c QColor
 */
template <typename T>
Vec3<T> Vec3<T>::fromQColor(const QColor &_value)
{
    return {T(_value.redF()), T(_value.greenF()), T(_value.blueF())};
}

/*!
 * \brief Conversion to \c QColor
 * \tparam T Template floating point type
 * \return This vector as \c QColor
 */
template <typename T>
inline QColor Vec3<T>::toQColor() const
{
    return QColor::fromRgbF(alignedTo0_1(float(x)), alignedTo0_1(float(y)), alignedTo0_1(float(z)));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Conversion to 2D vector
 * \tparam T Template floating point type
 * \param _skipAxis Axis to skip
 * \return This as 2D vector
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
 * \tparam T Template floating point type
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

/*!
 * \brief Conversion to 3D vector
 * \tparam T Template floating point type
 * \return Color as 3D vector
 */
template <typename T>
inline Vec3<T> ColorRGB::toVec3() const
{
    return Math::Vec3<T>(T(red) / T(255), T(green) / T(255), T(blue) / T(255));
}

/*!
 * \brief Conversion to 32 bit 3D vector
 * \tparam T Template floating point type
 * \return Color as 3D vector
 */
inline Vec3<float> ColorRGB::toVec3F() const
{
    return toVec3<float>();
}

/*!
 * \brief Create color from a 3D vector
 * \tparam T Template floating point type
 * \param _vector 3D vector
 * \return Color constructed from a 3D vector
 */
template <typename T>
inline ColorRGB ColorRGB::fromVec3(const Math::Vec3<T> &_vector)
{
    return {uint8_t(Math::aligned(_vector.x * T(255), T(0), T(255))),
            uint8_t(Math::aligned(_vector.y * T(255), T(0), T(255))),
            uint8_t(Math::aligned(_vector.z * T(255), T(0), T(255)))};
}

/*!
 * \brief Create 3D vector from color
 * \tparam T Template floating point type
 * \param _value Input color
 * \return 3D vector constructed from color
 */
template <typename T>
Vec3<T> Vec3<T>::fromColor(const ColorRGB &_value)
{
    return _value.toVec3<T>();
}

/*!
 * \brief Create color from this 3D vector
 * \tparam T Template floating point type
 * \return Color constructed from this 3D vector
 */
template <typename T>
inline ColorRGB Vec3<T>::toColor() const
{
    return ColorRGB::fromVec3(*this);
}

/*!
 * \brief Create a ratio color in between given colors
 * \tparam T Template floating point type
 * \param _ratio Ratio factor
 * \param _colorMin Color 1
 * \param _colorMax Color 2
 * \return Ratio color
 */
template <typename T>
ColorRGB ColorRGB::ratioAvg(const T _ratio, const ColorRGB &_colorMin, const ColorRGB &_colorMax)
{
    const Vec3<T> min = _colorMin.toVec3<T>();
    const Vec3<T> max = _colorMax.toVec3<T>();
    return fromVec3<T>(min + alignedTo0_1<T>(_ratio) * (max - min));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Converted data to different precision
 * \tparam T Template floating point type
 * \tparam T2 Template floating point type for output
 * \param _out Output 3D vector array pointer
 * \param _in Input 3D vector array pointer
 * \param _count Vector count
 * \param _pool Multi-thread indices
 * \return
 */
template <typename T>
template <typename T2>
void Vec3<T>::convertedData(Vec3<T2> *_out,
                            const Vec3<T> *_in,
                            const size_t _count,
                            const std::vector<std::pair<size_t, size_t>> &_pool)
{
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _count; ++i)
            _out[i] = _in[i].template converted<T2>();
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t](Vec3<T2> *__out, const Vec3<T> *__in) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __out[i] = __in[i].template converted<T2>();
                },
                _out,
                _in));
        for (std::thread &t : threads)
            t.join();
    }
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
inline size_t Vec3<T>::toHash() const
{
    return Math::mixHash(std::hash<T>{}(x), std::hash<T>{}(y), std::hash<T>{}(z));
}

/*!
 * \brief Calculate hash of 3D vector array
 * \param _data 3D vector array
 * \param _count Array size
 * \return Calculated hash
 */
template <typename T>
size_t Vec3<T>::mixHash(const Vec3<T> *_data, const size_t _count)
{
    if (_count == 0UL)
        return 0UL;
    size_t offset = 1UL;
    size_t result = _data[0UL].toHash();
    for (size_t i = 1UL; i < _count; ++i)
        updateHash(result, offset, _data[i].toHash());
    return result;
}

/*!
 * \brief Calculate hash of 3D vector array
 * \param _data 3D vector array
 * \return Calculated hash
 */
template <typename T>
size_t Vec3<T>::mixHash(const std::vector<Vec3<T>> &_data)
{
    return Vec3<T>::mixHash(_data.data(), _data.size());
}

/*!
 * \brief Calculate hash of 3D vector pair array
 * \param _data 3D vector pair array
 * \param _count Array size
 * \return Calculated hash
 */
template <typename T>
size_t Vec3<T>::mixHash(const std::pair<Vec3<T>, Vec3<T>> *_data, const size_t _count)
{
    if (_count == 0UL)
        return 0UL;
    size_t offset = 1UL;
    size_t result = _data[0UL].first.toHash();
    updateHash(result, offset, _data[0UL].second.toHash());
    for (size_t i = 1UL; i < _count; ++i)
    {
        updateHash(result, offset, _data[i].first.toHash());
        updateHash(result, offset, _data[i].second.toHash());
    }
    return result;
}

/*!
 * \brief Calculate hash of 3D vector pair array
 * \param _data 3D vector pair array
 * \return Calculated hash
 */
template <typename T>
size_t Vec3<T>::mixHash(const std::vector<std::pair<Vec3<T>, Vec3<T>>> &_data)
{
    return Vec3<T>::mixHash(_data.data(), _data.size());
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Vec3<float> Vec3F;        //!< 32 bit floating point precision 3D vector
typedef Vec3<double> Vec3D;       //!< 64 bit floating point precision 3D vector
typedef Vec3<long double> Vec3L;  //!< 128 bit floating point precision 3D vector

}  // namespace Math
}  // namespace U1

#endif  // MATH_VEC3_H
