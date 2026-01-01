/*!
 * \file src/Math/type.h
 * \brief Basic mathematics tools, methods and enumerations
 */
#ifndef MATH_TYPE_H
#define MATH_TYPE_H

#include <functional>
#include <cmath>
#include <limits>
#include <type_traits>

#include <QStringList>

/*!
 * \namespace U1
 * \brief Major Universe 1 projects namespace
 */
namespace U1 {

/*!
 * \namespace U1::Math
 * \brief Mathematics tools
 */
namespace Math {
Q_NAMESPACE

/*! \brief Enumeration of helicity types */
enum Helicity : int
{
    _HelicityLeft = -1,  //!< Left-handed helicity
    _HelicityZero = 0,   //!< Zero helicity
    _HelicityRight = 1   //!< Right-handed helicity
};

/*! \brief Enumeration floating point types */
enum FloatingPointType : int
{
    _FloatingPoint_float,        //!< 32bit \c float
    _FloatingPoint_double,       //!< 64bit \c double
    _FloatingPoint_long_double,  //!< platform-dependent long double
};

/*! \brief The Alignment type name */
enum AlignType : int
{
    _AlignTopLeft = 0,   //!< Align top-left
    _AlignTopCenter,     //!< Align top-center
    _AlignTopRight,      //!< Align top-right
    _AlignCenterLeft,    //!< Align center-left
    _AlignCenterCenter,  //!< Align center-center
    _AlignCenterRight,   //!< Align center-right
    _AlignBottomLeft,    //!< Align bottom-left
    _AlignBottomCenter,  //!< Align bottom-center
    _AlignBottomRight,   //!< Align bottom-right
};
Q_ENUM_NS(AlignType)

/*!
 * \brief Floating point type to enumeration literal
 * \tparam T Template floating point type
 * \return Template floating point type literal
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline FloatingPointType getFloatingPointType()
{
    if constexpr (std::is_same<T, float>::value)
        return _FloatingPoint_float;
    if constexpr (std::is_same<T, double>::value)
        return _FloatingPoint_double;
    if constexpr (std::is_same<T, long double>::value)
        return _FloatingPoint_long_double;
    return _FloatingPoint_float;
}

/*!
 * \namespace U1::Math::Epsilon
 * \brief Namespace for floating point error handling - \b epsilon tools
 */
namespace Epsilon {

/*!
 * \brief Type specific epsilon value
 * \tparam T Template numeric type
 * \return Type specific epsilon value
 * \note Epsilon from general C++ library
 * \sa std::numeric_limits<T>::epsilon()
 */
template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
inline T limitsEpsilon()
{
    return std::numeric_limits<T>::epsilon();
}

/*!
 * \brief Type specific epsilon value
 * \tparam T Template floating point type
 * \return Type specific epsilon value
 * \details
 *  | Precision | Epsilon    | Type              |
 *  | :-------- | :--------- | :---------------- |
 *  | 32 bit    | 0.0001     | \c float          |
 *  | 64 bit    | 0.000001   | \c double         |
 *  | 128 bit   | 0.00000001 | \c long \c double |
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T epsilon();

#ifndef DOXYGEN_SKIP
template <>
inline float epsilon()
{
    static const float _EPS = 0.0001f;  // 10.0F * std::numeric_limits<float>::epsilon();
    return _EPS;
}

template <>
inline double epsilon()
{
    static const double _EPS = 0.000001;  // 100.0 * std::numeric_limits<double>::epsilon();
    return _EPS;
}

template <>
inline long double epsilon()
{
    static const long double _EPS = 0.00000001;  // 1000.0L * std::numeric_limits<long double>::epsilon();
    return _EPS;
}

#endif  // DOXYGEN_SKIP

}  // namespace Epsilon

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point value is zero or very close to zero
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is very close to zero
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isNull(const T _value)
{
    return -Epsilon::epsilon<T>() < _value && Epsilon::epsilon<T>() > _value;
}

/*!
 * \brief Test if integral value is zero
 * \tparam T Template integral type
 * \param _value Value to check
 * \return \c true if \a _value is zero
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isNull(const T _value)
{
    return _value == T(0);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point value is not zero and positive
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is not zero and positive
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isPositive(const T _value)
{
    return Epsilon::epsilon<T>() < _value;
}

/*!
 * \brief Test if integral value is not zero and positive
 * \tparam T Template integral type
 * \param _value Value to check
 * \return \c true if \a _value is not zero and positive
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isPositive(const T _value)
{
    return _value > T(0);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point value is not zero and negative
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is not zero and negative
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isNegative(const T _value)
{
    return -Epsilon::epsilon<T>() > _value;
}

/*!
 * \brief Test if integral value is not zero and negative
 * \tparam T Template integral type
 * \param _value Value to check
 * \return \c true if \a _value is not zero and negative
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isNegative(const T _value)
{
    return _value < T(0);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point values equals
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if \a _values equals
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type equals(const T _value1, const T _value2)
{
    return isNull<T>(_value1 - _value2);
}

/*!
 * \brief Test if integral values equals
 * \tparam T Template integral type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if \a _values equals
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type equals(const T _value1, const T _value2)
{
    return _value1 == _value2;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point values equals
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \param _value3 Third value to check
 * \return \c true if \a _values equals
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type
equals(const T _value1, const T _value2, const T _value3)
{
    return equals<T>(_value1, _value2) && equals<T>(_value1, _value3);
}

/*!
 * \brief Test if integral values equals
 * \tparam T Template integral type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \param _value3 Third value to check
 * \return \c true if all input values equals
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type
equals(const T _value1, const T _value2, const T _value3)
{
    return _value1 == _value2 && _value1 == _value3;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point values equals or value1 is lower or equal to value2
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is lower or equal to \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isLessOrEqual(const T _value1,
                                                                                           const T _value2)
{
    return -Epsilon::epsilon<T>() < (_value2 - _value1);
}

/*!
 * \brief Test if integral values equals or value1 is lower or equal to value2
 * \tparam T Template integral type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is lower or equal to \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isLessOrEqual(const T _value1, const T _value2)
{
    return _value1 <= _value2;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point values not equals and value1 is lower then value2
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is lower then \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isLessNotEqual(const T _value1,
                                                                                            const T _value2)
{
    return Epsilon::epsilon<T>() < (_value2 - _value1);
}

/*!
 * \brief Test if integral values not equals and value1 is lower then value2
 * \tparam T Template integral type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is lower then \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isLessNotEqual(const T _value1, const T _value2)
{
    return _value1 < _value2;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point values equals or value1 is greater or equal to value2
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is greater or equal to \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isMoreOrEqual(const T _value1,
                                                                                           const T _value2)
{
    return -Epsilon::epsilon<T>() < (_value1 - _value2);
}

/*!
 * \brief Test if integral values equals or value1 is greater or equal to value2
 * \tparam T Template integral type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is greater or equal to \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isMoreOrEqual(const T _value1, const T _value2)
{
    return _value1 >= _value2;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point values not equals and value1 is greater then value2
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is greater then \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isMoreNotEqual(const T _value1,
                                                                                            const T _value2)
{
    return Epsilon::epsilon<T>() < (_value1 - _value2);
}

/*!
 * \brief Test if integral values not equals and value1 is greater then value2
 * \tparam T Template integral type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if values equals or \c value1 is greater then \c value2
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isMoreNotEqual(const T _value1, const T _value2)
{
    return _value1 > _value2;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point value equals 1 or very close to 1
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is very close to 1
 */
template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type isUnit(const T _value)
{
    return equals<T>(_value, T(1));
}

/*!
 * \brief Test if integral value equals 1
 * \tparam T Template integral type
 * \param _value Value to check
 * \return \c true if \a _value is 1
 */
template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type isUnit(const T _value)
{
    return _value == T(1);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if floating point value is within the range
 * \tparam T Template floating point type
 * \param _value Value to check
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return \c true if \a _value is in range
 * \note Return \c false when given \a _value equals \a _minimum or \a _maximum
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isBetween(const T _value, const T _minimum, const T _maximum)
{
    return !equals<T>(_value, _minimum) && !equals<T>(_value, _maximum) && (_minimum < _value && _maximum > _value);
}

/*!
 * \brief Test if floating point value is within the range (0 to PI/2)
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is in range (0 to PI/2)
 * \note Return \c false when given \a _value equals 0 or PI/2
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isBetween0_PI2(const T _value)
{
    return isBetween(_value, T(0), T(M_PI_2));
}

/*!
 * \brief Test if floating point value is within the range (0 to 1)
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is in range (0 to 1)
 * \note Return \c false when given \a _value equals 0 or 1
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isBetween0_1(const T _value)
{
    return isBetween(_value, T(0), T(1));
}

/*!
 * \brief Test if floating point value is within range
 * \tparam T Template floating point type
 * \param _value Value to check
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return \c true if \a _value is in range
 * \note Return \c true when given \a _value equals \a _minimum or \a _maximum
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAligned(const T _value, const T _minimum, const T _maximum)
{
    return equals<T>(_value, _minimum) || equals<T>(_value, _maximum) || (_minimum < _value && _maximum > _value);
}

/*!
 * \brief Test if floating point value is within range
 * \tparam T Template floating point type
 * \param _value Value to check
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return \c true if \a _value is in range
 * \note Return \c true when given \a _value equals \a _maximum
 * \note Return \c false when given \a _value equals \a _minimum
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAlignedOrMax(const T _value, const T _minimum, const T _maximum)
{
    return !equals<T>(_value, _minimum) && (equals<T>(_value, _maximum) || (_minimum < _value && _maximum > _value));
}

/*!
 * \brief Test if floating point value is within range
 * \tparam T Template floating point type
 * \param _value Value to check
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return \c true if \a _value is in range
 * \note Return \c false when given \a _value equals \a _maximum
 * \note Return \c true when given \a _value equals \a _minimum
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAlignedOrMin(const T _value, const T _minimum, const T _maximum)
{
    return !equals<T>(_value, _maximum) && (equals<T>(_value, _minimum) || (_minimum < _value && _maximum > _value));
}

/*!
 * \brief Test if floating point value is within range -1 to 1
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is in range -1 to 1
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAlignedToPM1(const T _value)
{
    return isAligned<T>(_value, -T(1), T(1));
}

/*!
 * \brief Test if floating point value is within range 0 to 1
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is in range 0 to 1
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAlignedTo0_1(const T _value)
{
    return isAligned<T>(_value, T(0), T(1));
}

/*!
 * \brief Return aligned value
 * \tparam T Template floating point type
 * \param _value Value to align
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return Aligned value
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T aligned(const T _value, const T _minimum, const T _maximum)
{
    return std::min(_maximum, std::max(_minimum, _value));
}

/*!
 * \brief Returns value aligned to -1 to +1 range
 * \tparam T Template floating point type
 * \param _value Value to align
 * \return Aligned value
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T alignedToPM1(const T _value)
{
    return std::min(T(1), std::max(-T(1), _value));
}

/*!
 * \brief Returns value aligned to -1 to +1 range
 * \tparam T Template floating point type
 * \param _value Value to align
 * \return Aligned value
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T alignedTo0_1(const T _value)
{
    return std::min(T(1), std::max(T(0), _value));
}

/*!
 * \brief Returns value aligned to 0 to PI range
 * \tparam T Template floating point type
 * \param _value Value to align
 * \return Aligned value
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T alignedTo0_PI(const T _value)
{
    return std::min(T(M_PIl), std::max(T(0), _value));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns sign of value (+1 for positive \a _value, -1 for negative \a _value and 0 for zero \a _value)
 * \tparam T Template floating point type
 * \param _value Value to get sign
 * \return Sign of value
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T valueSign(const T _value)
{
    return isNull<T>(_value) ? T(0) : (_value > T(0) ? T(1) : -T(1));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param _degValue Value to convert
 * \return Angle in radians
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T toRad(const T _degValue)
{
    static const T DegInRad = T(M_PIl / 180.0l);
    return _degValue * DegInRad;
}

/*!
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param _radValue Value to convert
 * \return Angle in radians
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T toDeg(const T _radValue)
{
    static const T RadInDeg = T(180.0l / M_PIl);
    return _radValue * RadInDeg;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns circle point count base on quality index
 * \param _quality Quality index
 * \return Circle point count base on quality index
 * \note Used equation \f$N = 4 \times (Q + 1)\f$
 */
inline size_t circlePointCount(const size_t _quality)
{
    // return std::min(65535U, (_quality + 1UL) * 4UL);
    return (_quality + 1UL) * 4UL;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Update hash value
 * \param _result Current/outcome hash value
 * \param _offset Bit offset index
 * \param _hash Value to update current hash (\a _result)
 * \return Calculated hash value
 */
inline size_t updateHash(size_t &_result, size_t &_offset, const size_t _hash)
{
    _result = _result ^ ((_hash >> _offset) | (_hash << (64UL - _offset)));
    ++_offset;
    if (_offset == 64UL)
        _offset = 1UL;
    return _result;
}

/*!
 * \brief Calculate array hash
 * \tparam T Numeric type
 * \param _data Array with values to hash
 * \param _size Number of items in the \a _data array
 * \return Calculated hash value
 */
template <typename T, typename = std::enable_if<std::is_arithmetic<T>::value>>
inline size_t mixHashData(const T *_data, const size_t _size)
{
    size_t result = 0UL;
    size_t offset = 1UL;
    for (size_t i = 0; i < _size; ++i)
        updateHash(result, offset, std::hash<T>{}(_data[i]));
    return result;
}

/*!
 * \brief Calculate \c QString hash
 * \param _text \c QString text
 * \return \c QString hash
 */
inline size_t mixTextHash(const QString &_text)
{
    size_t result = 0UL;
    size_t offset = 1UL;
    for (qsizetype i = 0; i < _text.length(); ++i)
        updateHash(result, offset, std::hash<char16_t>{}(_text[i].unicode()));
    return result;
}

/*!
 * \brief Calculate \c QStringList hash
 * \param _text Collection of \c QString
 * \return \c QStringList hash
 */
inline size_t mixTextHash(const QStringList &_text)
{
    size_t result = 0UL;
    size_t offset = 1UL;
    for (const QString &t : std::as_const(_text))
        updateHash(result, offset, mixTextHash(t));
    return result;
}

/*!
 * \brief Mix 2 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1, const size_t _2)
{
    return _1 ^ ((_2 >> 1UL) | (_2 << 63UL));
}

/*!
 * \brief Mix 3 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1, const size_t _2, const size_t _3)
{
    return mixHash(_1, _2) ^ ((_3 >> 2UL) | (_3 << 62UL));
}

/*!
 * \brief Mix 4 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1, const size_t _2, const size_t _3, const size_t _4)
{
    return mixHash(_1, _2, _3) ^ ((_4 >> 3UL) | (_4 << 61UL));
}

/*!
 * \brief Mix 5 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1, const size_t _2, const size_t _3, const size_t _4, const size_t _5)
{
    return mixHash(_1, _2, _3, _4) ^ ((_5 >> 4UL) | (_5 << 60UL));
}

/*!
 * \brief Mix 6 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \return Calculated hash value
 */
inline size_t
mixHash(const size_t _1, const size_t _2, const size_t _3, const size_t _4, const size_t _5, const size_t _6)
{
    return mixHash(_1, _2, _3, _4, _5) ^ ((_6 >> 5UL) | (_6 << 59UL));
}

/*!
 * \brief Mix 7 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7)
{
    return mixHash(_1, _2, _3, _4, _5, _6) ^ ((_7 >> 6UL) | (_7 << 58UL));
}

/*!
 * \brief Mix 8 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \param _8 Value 8
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7,
                      const size_t _8)
{
    return mixHash(_1, _2, _3, _4, _5, _6, _7) ^ ((_8 >> 7UL) | (_8 << 57UL));
}

/*!
 * \brief Mix 9 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \param _8 Value 8
 * \param _9 Value 9
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7,
                      const size_t _8,
                      const size_t _9)
{
    return mixHash(_1, _2, _3, _4, _5, _6, _7, _8) ^ ((_9 >> 8UL) | (_9 << 56UL));
}

/*!
 * \brief Mix 10 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \param _8 Value 8
 * \param _9 Value 9
 * \param _10 Value 10
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7,
                      const size_t _8,
                      const size_t _9,
                      const size_t _10)
{
    return mixHash(_1, _2, _3, _4, _5, _6, _7, _8, _9) ^ ((_10 >> 9UL) | (_10 << 55UL));
}

/*!
 * \brief Mix 11 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \param _8 Value 8
 * \param _9 Value 9
 * \param _10 Value 10
 * \param _11 Value 11
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7,
                      const size_t _8,
                      const size_t _9,
                      const size_t _10,
                      const size_t _11)
{
    return mixHash(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10) ^ ((_11 >> 10UL) | (_11 << 54UL));
}

/*!
 * \brief Mix 12     hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \param _8 Value 8
 * \param _9 Value 9
 * \param _10 Value 10
 * \param _11 Value 11
 * \param _12 Value 12
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7,
                      const size_t _8,
                      const size_t _9,
                      const size_t _10,
                      const size_t _11,
                      const size_t _12)
{
    return mixHash(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11) ^ ((_12 >> 11UL) | (_12 << 53UL));
}

/*!
 * \brief Mix 13 hash values
 * \param _1 Value 1
 * \param _2 Value 2
 * \param _3 Value 3
 * \param _4 Value 4
 * \param _5 Value 5
 * \param _6 Value 6
 * \param _7 Value 7
 * \param _8 Value 8
 * \param _9 Value 9
 * \param _10 Value 10
 * \param _11 Value 11
 * \param _12 Value 12
 * \param _13 Value 13
 * \return Calculated hash value
 */
inline size_t mixHash(const size_t _1,
                      const size_t _2,
                      const size_t _3,
                      const size_t _4,
                      const size_t _5,
                      const size_t _6,
                      const size_t _7,
                      const size_t _8,
                      const size_t _9,
                      const size_t _10,
                      const size_t _11,
                      const size_t _12,
                      const size_t _13)
{
    return mixHash(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12) ^ ((_13 >> 12UL) | (_13 << 52UL));
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculate sphere volume \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \param _radius Sphere radius
 * \return Sphere volume
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
T volumeSphere(const T _radius)
{
    return T(M_PIl * 4.0l / 3.0l) * _radius * _radius * _radius;
}

/*!
 * \brief Calculate sphere cup volume \f$\pi h^2 \frac{3r - h}{3}\f$
 * \tparam T Template floating point type
 * \param _radius Sphere radius
 * \param _height Cup height
 * \return Sphere cup volume
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
T volumeSphereCup(const T _radius, const T _height)
{
    return T(M_PIl) * _height * _height * (T(3) * _radius - _height) / T(3);
}


/*!
 * \brief Solve cubic equation \f$x^3 + Ax^2 + Bx + C = 0\f$
 * \param _out1 Output result 1
 * \param _out2 Output result 2
 * \param _out3 Output result 3
 * \param _A Coefficient for \f$x^2\f$
 * \param _B Coefficient for \f$x^1 = x\f$
 * \param _C Coefficient for \f$x^0 = 1\f$
 * \return Number of found roots
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
int solvePolynom3(T &_out1, T &_out2, T &_out3, const T _A, const T _B, const T _C)
{
    static const T _2PI = static_cast<T>(2.0l * M_PIl);
    static const T _SQ3_2 = std::sqrt(3.0L) / 2.0L;

    // solve cubic equation x^3 + a*x^2 + b*x + c = 0

    const T a2 = _A * _A;                                             // a2 = a*a;
    const T q = (a2 - T(3) * _B) / T(9);                              // q  = (a2 - 3*b)/9;
    const T r = (_A * (T(2) * a2 - T(9) * _B) + T(27) * _C) / T(54);  // r  = (a*(2*a2-9*b) + 27*c)/54;

    // equation x^3 + q*x + r = 0

    const T r2 = r * r;      // r2 = r*r;
    const T q3 = q * q * q;  // q3 = q*q*q;
    const T AAA = _A / T(3);

    if (r2 <= (q3 + Epsilon::epsilon<T>()))
    {
        const T t = std::acos(alignedToPM1<T>(r / std::sqrt(q3)));
        const T qq = -T(2) * std::sqrt(q);
        _out1 = qq * std::cos(t / T(3)) - AAA;
        _out2 = qq * std::cos((t + _2PI) / T(3)) - AAA;
        _out3 = qq * std::cos((t - _2PI) / T(3)) - AAA;
        return 3;
    }
    const T AA = (isNegative(r) ? T(1) : -T(1)) * std::cbrt(std::fabs(r) + std::sqrt(r2 - q3));
    const T BB = isNull(AA) ? T(0) : (q / AA);

    _out1 = (AA + BB) - AAA;
    _out2 = -T(0.5) * (AA + BB) - AAA;
    _out3 = _SQ3_2 * (AA - BB);
    if (std::fabs(_out3) < Epsilon::epsilon<T>())
    {
        _out3 = _out2;
        return 2;
    }
    return 1;
}

}  // namespace Math
}  // namespace U1

#endif  // MATH_TYPE_H
