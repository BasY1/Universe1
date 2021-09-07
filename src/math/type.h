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
    static const long double _EPS = 1000.0L * std::numeric_limits<long double>::epsilon();
    return _EPS;
}
#endif  // DOXYGEN_SKIP

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isNull(const T value)
{
    return -epsilon<T>() < value && epsilon<T>() > value;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isPositive(const T value)
{
    return epsilon<T>() < value;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isNegative(const T value)
{
    return -epsilon<T>() > value;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool equals(const T value1, const T value2)
{
    return isNull<T>(value1 - value2);
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool equals(const T value1, const T value2, const T value3)
{
    return                            //
        equals<T>(value1, value2) &&  //
        equals<T>(value1, value3);    // && TypeEquals<T>(value2, value3);
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline bool isUnit(const T value)
{
    return equals<T>(value, Const::T_1<T>());
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T alignedToPM1(const T value)
{
    return std::min(Const::T_1<T>(), std::max(-Const::T_1<T>(), value));
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

    if (r2 <= (q3 + epsilon<T>()))
    {
        const T t = std::acos(alignedToPM1<T>(r / std::sqrt(q3)));
        const T qq = -_2 * std::sqrt(q);
        _out1 = qq * std::cos(t / _3) - AAA;
        _out2 = qq * std::cos((t + _2PI) / _3) - AAA;
        _out3 = qq * std::cos((t - _2PI) / _3) - AAA;
        return 3;
    }
    const T AA = (Type::isNegative(r) ? T_1<T>() : -T_1<T>()) * std::cbrt(std::fabs(r) + std::sqrt(r2 - q3));
    const T BB = Type::isNull(AA) ? T_0<T>() : (q / AA);

    _out1 = (AA + BB) - AAA;
    _out2 = -_05 * (AA + BB) - AAA;
    _out3 = _SQRT3_2 * (AA - BB);
    if (std::fabs(_out3) < epsilon<T>())
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
 * \fn Universe1::Type::epsilon()
 * \brief Type specific epsilon value
 * \tparam T Template floating point type
 * \returns Type specific epsilon value
 */

/*!
 * \fn Universe1::Type::isNull(const T value)
 * \brief Test if floating point value is zero or very close to zero
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is very close to zero
 */

/*!
 * \fn Universe1::Type::isPositive(const T value)
 * \brief Test if floating point value is not zero and positive
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is not zero and positive
 */

/*!
 * \fn Universe1::Type::isNegative(const T value)
 * \brief Test if floating point value is not zero and negative
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is not zero and negative
 */

/*!
 * \fn Universe1::Type::equals(const T value1, const T value2)
 * \brief Test if floating point values equals
 * \tparam T Template floating point type
 * \param value1 First value to check
 * \param value2 Second value to check
 * \returns \c true if \a values equals
 */

/*!
 * \fn Universe1::Type::equals(const T value1, const T value2, const T value3)
 * \brief Test if three floating point values equals
 * \tparam T Template floating point type
 * \param value1 First value to check
 * \param value2 Second value to check
 * \param value3 Third value to check
 * \returns \c true if values equals
 */

/*!
 * \fn Universe1::Type::isUnit(const T value)
 * \brief Test if floating point value equals 1 or very close to 1
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is very close to zero
 */

/*!
 * \fn Universe1::Type::alignedToPM1(const T value)
 * \brief Returns value aligned to -1 to +1 range
 * \tparam T Template floating point type
 * \param value Value to align
 * \returns Aligned value
 */

/*!
 * \fn Universe1::Type::solvePolynom3(T &_out1, T &_out2, T &_out3, const T _A, const T _B, const T _C)
 * \brief Solves third grade polynom \f$x^3 + A*x^2 + B*x + C = 0\f$
 * \param _out1 Output equation root 1
 * \param _out2 Output equation root 2
 * \param _out3 Output equation root 3
 * \param _A Equation cubic parameter
 * \param _B Equation linear parameter
 * \param _C Equation scalar parameter
 * \returns Number of roots
 * \details
 *  - In case 3 real roots return 3
 *  - In case 2 real roots return 2
 *  - In case 1 real and 2 imaginary roots return 2
 */

/*! \} */  // End of group: TypeCompare

}  // namespace Type
}  // namespace Universe1

#endif  // UNIVERSE1_TYPE_TYPE_H
