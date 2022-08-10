/*!
 * \file math/type.h
 * \author Michal Steller
 * \brief Floating point value tools and templates
 */

#ifndef UNIVERSE1_TYPE_TYPE_H
#define UNIVERSE1_TYPE_TYPE_H

#include "typeconst.h"

#include <cstdint>
#include <limits>

namespace Universe1 {
namespace Math {
namespace Type {

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T epsilon();

#ifndef DOXYGEN_SKIP
template <>
inline float epsilon()
{
    static const float _EPS = 10.0F * std::numeric_limits<float>::epsilon();
    return _EPS;
}

template <>
inline double epsilon()
{
    static const double _EPS = 100.0 * std::numeric_limits<double>::epsilon();
    return _EPS;
}

template <>
inline long double epsilon()
{
    static const long double _EPS = 10000.0L * std::numeric_limits<long double>::epsilon();
    return _EPS;
}
#endif  // DOXYGEN_SKIP

}  // namespace Type

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isNull(const T _value)
{
    return -Type::epsilon<T>() < _value && Type::epsilon<T>() > _value;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isPositive(const T _value)
{
    return Type::epsilon<T>() < _value;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isNegative(const T _value)
{
    return -Type::epsilon<T>() > _value;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool equals(const T _value1, const T _value2)
{
    return isNull<T>(_value1 - _value2);
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool equals(const T _value1, const T _value2, const T _value3)
{
    return                              //
        equals<T>(_value1, _value2) &&  //
        equals<T>(_value1, _value3);    // && TypeEquals<T>(value2, _value3);
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isUnit(const T _value)
{
    return equals<T>(_value, Const::T_1<T>());
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAligned(const T _value, const T _minimum, const T _maximum)
{
    return equals<T>(_value, _minimum) || equals<T>(_value, _maximum) || (_minimum < _value && _maximum > _value);
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAlignedToPM1(const T _value)
{
    return isAligned<T>(_value, -Const::T_1<T>(), Const::T_1<T>());
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isAlignedTo0_1(const T _value)
{
    return isAligned<T>(_value, Const::T_0<T>(), Const::T_1<T>());
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T alignedToPM1(const T _value)
{
    return std::min(Const::T_1<T>(), std::max(-Const::T_1<T>(), _value));
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T valueSign(const T _value)
{
    return isNull<T>(_value) ? Const::T_0<T>() : (_value > Const::T_0<T>() ? Const::T_1<T>() : -Const::T_1<T>());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T toRad(const T degValue)
{
    return degValue / Const::T_RadInDeg<T>();
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T toDeg(const T radValue)
{
    return radValue * Const::T_RadInDeg<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
int solvePolynom3(T &_out1, T &_out2, T &_out3, const T _A, const T _B, const T _C)
{
    using namespace Const;
    static const T _SQRT3_2 = T_SQRT3_2<T>();
    static const T _2PI = T_2PI<T>();
    static const T _05 = T_05<T>();
    static const T _2 = T_2<T>();
    static const T _3 = T_3<T>();
    static const T _9 = 9;
    static const T _27 = 27;
    static const T _54 = 54;

    // solve cubic equation x^3 + a*x^2 + b*x + c = 0

    const T a2 = _A * _A;                                     // double a2 = a*a;
    const T q = (a2 - _3 * _B) / _9;                          // double q  = (a2 - 3*b)/9;
    const T r = (_A * (_2 * a2 - _9 * _B) + _27 * _C) / _54;  // double r  = (a*(2*a2-9*b) + 27*c)/54;

    // equation x^3 + q*x + r = 0

    const T r2 = r * r;      // double r2 = r*r;
    const T q3 = q * q * q;  // double q3 = q*q*q;
    const T AAA = _A / _3;

    if (r2 <= (q3 + Type::epsilon<T>()))
    {
        const T t = std::acos(alignedToPM1<T>(r / std::sqrt(q3)));
        const T qq = -_2 * std::sqrt(q);
        _out1 = qq * std::cos(t / _3) - AAA;
        _out2 = qq * std::cos((t + _2PI) / _3) - AAA;
        _out3 = qq * std::cos((t - _2PI) / _3) - AAA;
        return 3;
    }
    const T AA = (isNegative(r) ? T_1<T>() : -T_1<T>()) * std::cbrt(std::fabs(r) + std::sqrt(r2 - q3));
    const T BB = isNull(AA) ? T_0<T>() : (q / AA);

    _out1 = (AA + BB) - AAA;
    _out2 = -_05 * (AA + BB) - AAA;
    _out3 = _SQRT3_2 * (AA - BB);
    if (std::fabs(_out3) < Type::epsilon<T>())
    {
        _out3 = _out2;
        return 2;
    }
    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \defgroup TypeCompare Type specific floating point compare tools
 * \brief Type specific floating point \b epsilon and compare tools
 * \details Standard \b C++ epsilon std::numeric_limits<TYPE>::epsilon() is used as base value, but depending on used
 * floating point type this epsilon value is multiplied by factor:
 * | Type              | Value |
 * | :---------------- | :---- |
 * | \c float          | 10    |
 * | \c double         | 100   |
 * | \c long \c double | 1000  |
 *
 * \{
 */

/*!
 * \fn Universe1::Math::Type::epsilon()
 * \brief Type specific epsilon value
 * \tparam T Template floating point type
 * \return Type specific epsilon value
 */

/*!
 * \fn Universe1::Math::isNull(const T _value)
 * \brief Test if floating point value is zero or very close to zero
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is very close to zero
 */

/*!
 * \fn Universe1::Math::isPositive(const T _value)
 * \brief Test if floating point value is not zero and positive
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is not zero and positive
 */

/*!
 * \fn Universe1::Math::isNegative(const T _value)
 * \brief Test if floating point value is not zero and negative
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is not zero and negative
 */

/*!
 * \fn Universe1::Math::equals(const T _value1, const T _value2)
 * \brief Test if floating point values equals
 * \tparam T Template floating point type
 * \param _value1 First value to check
 * \param _value2 Second value to check
 * \return \c true if \a _values equals
 */

/*!
 * \fn Universe1::Math::equals(const T value1, const T value2, const T value3)
 * \brief Test if three floating point values equals
 * \tparam T Template floating point type
 * \param value1 First value to check
 * \param value2 Second value to check
 * \param value3 Third value to check
 * \return \c true if values equals
 */

/*!
 * \fn Universe1::Math::isUnit(const T _value)
 * \brief Test if floating point value equals 1 or very close to 1
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is very close to zero
 */

/*!
 * \fn Universe1::Math::isAligned(const T _value, const T _minimum, const T _maximum)
 * \brief Test if floating point value is within range
 * \tparam T Template floating point type
 * \param _value Value to check
 * \param _minimum Minimum value of aligning range
 * \param _maximum Maximum value of aligning range
 * \return \c true if \a _value is in range
 */

/*!
 * \fn Universe1::Math::isAlignedToPM1(const T _value)
 * \brief Test if floating point value is within range -1 to 1
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is in range -1 to 1
 */

/*!
 * \fn Universe1::Math::isAlignedTo0_1(const T _value)
 * \brief Test if floating point value is within range 0 to 1
 * \tparam T Template floating point type
 * \param _value Value to check
 * \return \c true if \a _value is in range 0 to 1
 */

/*!
 * \fn Universe1::Math::alignedToPM1(const T _value)
 * \brief Returns value aligned to -1 to +1 range
 * \tparam T Template floating point type
 * \param _value Value to align
 * \return Aligned value
 */

/*!
 * \fn Universe1::Math::valueSign(const T _value)
 * \brief Returns sign of value (+1 for positive \a _value, -1 for negative \a _value and 0 for NULL \a _value)
 * \tparam T Template floating point type
 * \param _value Value to get sign
 * \return Sign of value
 */

/*!
 * \fn Universe1::Math::toRad(const T _degValue)
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param _degValue Value to convert
 * \return Angle in radians
 */

/*!
 * \fn Universe1::Math::toDeg(const T _radValue)
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param _radValue Value to convert
 * \return Angle in radians
 */

/*!
 * \fn Universe1::Math::solvePolynom3(T &_out1, T &_out2, T &_out3, const T _A, const T _B, const T _C)
 * \brief Solves third grade polynom \f$x^3 + A*x^2 + B*x + C = 0\f$
 * \param _out1 Output equation root 1
 * \param _out2 Output equation root 2
 * \param _out3 Output equation root 3
 * \param _A Equation cubic parameter
 * \param _B Equation linear parameter
 * \param _C Equation scalar parameter
 * \return Number of roots
 * \details
 *  - In case 3 real roots return 3
 *  - In case 2 real roots return 2
 *  - In case 1 real and 2 imaginary roots return 2
 */

/*! \} */  // End of group: TypeCompare

}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_TYPE_TYPE_H
