/*!
 * \file math/type.h
 * \author Michal Steller
 * \brief Floating point value tools and templates
 */

#ifndef TYPE_H
#define TYPE_H

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <limits>
#include <sstream>
#include <type_traits>

#include <list>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \defgroup TypeEpsilon Type epsilon
 * \brief Floating point epsilon (error or zero) value access tools
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
 * \brief Type specific epsilon value
 * \tparam T Template floating point type
 * \returns Type specific epsilon value
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>> inline T TypeEps();

#ifndef DOXYGEN_SKIP
template <> inline float TypeEps()
{
    static const float _EPS = 10.0F * std::numeric_limits<float>::epsilon();
    return _EPS;
}

template <> inline double TypeEps()
{
    static const double _EPS = 100.0 * std::numeric_limits<double>::epsilon();
    return _EPS;
}

template <> inline long double TypeEps()
{
    static const long double _EPS = 1000.0L * std::numeric_limits<long double>::epsilon();
    return _EPS;
}
#endif  // DOXYGEN_SKIP

/*! \} */  // End of group: TypeEpsilon
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \defgroup TypeCompare Type compare tools
 * \brief Comparison tools for floating point type
 *
 * \{
 */

/*!
 * \brief Test if floating point value is zero or very close to zero
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is very close to zero
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline bool TypeIsNull(const T value)
{
    return -TypeEps<T>() < value && TypeEps<T>() > value;
}

/*!
 * \brief Test if floating point value is not zero and positive
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is not zero and positive
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline bool TypeIsPositive(const T value)
{
    return TypeEps<T>() < value;
}

/*!
 * \brief Test if floating point values equals
 * \tparam T Template floating point type
 * \param value1 First value to check
 * \param value2 Second value to check
 * \returns \c true if \a values equals
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline bool TypeEquals(const T value1, const T value2)
{
    return TypeIsNull<T>(value1 - value2);
}

/*!
 * \brief Test if floating point values equals
 * \tparam T Template floating point type
 * \param value1 First value to check
 * \param value2 Second value to check
 * \param value3 Third value to check
 * \returns \c true if values equals
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline bool TypeEquals(const T value1, const T value2, const T value3)
{
    return                                //
        TypeEquals<T>(value1, value2) &&  //
        TypeEquals<T>(value1, value3);    // && TypeEquals<T>(value2, value3);
}

/*!
 * \brief Test if floating point value is zero or very close to zero
 * \tparam T Template floating point type
 * \param value Value to check
 * \returns \c true if \a value is very close to zero
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline bool TypeIsNormal(const T value)
{
    static const T tmp = 1;
    return TypeEquals<T>(value, tmp);
}

/*! \} */  // End of group: TypeCompare
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \defgroup TypeConstants Type constants
 * \brief Floating point type constants
 * \{
 */

/*!
 * \brief Getter for type specific value: 0
 * \tparam T Template floating point type
 * \returns 0 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_0()
{
    static const T tmp = 0;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 1
 * \tparam T Template floating point type
 * \returns 1 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_1()
{
    static const T tmp = 1;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 0.1
 * \tparam T Template floating point type
 * \returns 0.1 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_01()
{
    static const T tmp = 0.1l;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 0.5
 * \tparam T Template floating point type
 * \returns 0.5 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_05()
{
    static const T tmp = 0.5l;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 2
 * \tparam T Template floating point type
 * \returns 2 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_2()
{
    static const T tmp = 2;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 3
 * \tparam T Template floating point type
 * \returns 3 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_3()
{
    static const T tmp = 3;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 4
 * \tparam T Template floating point type
 * \returns 4 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_4()
{
    static const T tmp = 4;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 10
 * \tparam T Template floating point type
 * \returns 10 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_10()
{
    static const T tmp = 10;
    return tmp;
}

/*!
 * \brief Getter for type specific value: 100
 * \tparam T Template floating point type
 * \returns 100 in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_100()
{
    static const T tmp = 100;
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\pi\f$
 * \tparam T Template floating point type
 * \returns \f$\pi\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_PI()
{
    static const T tmp = static_cast<T>(M_PIl);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$2\pi\f$
 * \tparam T Template floating point type
 * \returns \f$2\pi\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_2PI()
{
    static const T tmp = static_cast<T>(2.0l * M_PIl);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$4\pi\f$
 * \tparam T Template floating point type
 * \returns \f$4\pi\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_4PI()
{
    static const T tmp = static_cast<T>(4.0l * M_PIl);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$0.5\pi\f$
 * \tparam T Template floating point type
 * \returns \f$0.5\pi\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_PI_2()
{
    static const T tmp = static_cast<T>(M_PI_2l);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\frac{\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{\pi}{3}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_PI_3()
{
    static const T tmp = static_cast<T>(M_PIl / 3.0l);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\frac{2\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{2\pi}{3}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_2PI_3()
{
    static const T tmp = static_cast<T>((2.0l * M_PIl) / 3.0l);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\frac{4\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{4\pi}{3}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_4PI_3()
{
    static const T tmp = static_cast<T>((4.0l * M_PIl) / 3.0l);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\sqrt{2}\f$
 * \tparam T Template floating point type
 * \returns \f$\sqrt{2}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_SQRT2()
{
    static const T tmp = static_cast<T>(M_SQRT2l);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\frac{1}{\sqrt{2}}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{1}{\sqrt{2}}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_1_SQRT2()
{
    static const T tmp = static_cast<T>(M_SQRT1_2l);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\sqrt{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\sqrt{2}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_SQRT3()
{
    static const T tmp = std::sqrt(3.0L);
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\frac{\sqrt{3}}{2}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{\sqrt{3}}{2}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_SQRT3_2()
{
    static const T tmp = std::sqrt(3.0L) / 2.0L;
    return tmp;
}

/*!
 * \brief Getter for type specific value: \f$\frac{\sqrt{3}}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{\sqrt{3}}{3}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_SQRT3_3()
{
    static const T tmp = std::sqrt(3.0L) / 3.0L;
    return tmp;
}
/*!
 * \brief Getter for type specific value: \f$\frac{4\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{4\pi}{3}\f$ in specific floating point type
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T T_RadInDeg()
{
    static const T tmp = static_cast<T>(180.0l / M_PIl);
    return tmp;
}

/*! \} */  // End of group: TypeConstants
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T ToRad(const T degValue)
{
    return degValue / T_RadInDeg<T>();
}

/*!
 * \brief Convert degrees to radians
 * \tparam T Template floating point type
 * \param radValue Value to convert
 * \returns Angle in radians
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline T ToDeg(const T radValue)
{
    return radValue * T_RadInDeg<T>();
}

/*! \} */  // End of group: TypeAngles
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*!
 * \defgroup TypeString Type string tools
 * \brief Floating point string tools
 * \details
 *
 * \{
 */

/*!
 * \brief Setup fixed precision for output stream
 * \tparam T Template floating point type
 * \param os Output stream
 * \details
 * Setups fixed precision in output stream and the number of digits after the decimal point.
 * Default values for number of digits after the decimal point by floating point values:
 * | Type              | Precision |
 * | :---------------- | :-------- |
 * | \c float          | 7         |
 * | \c double         | 14        |
 * | \c long \c double | 18        |
 *
 */
template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
inline void TypeSetDefaultPrecision(std::ostream &os);

#ifndef DOXYGEN_SKIP
template <>
inline void TypeSetDefaultPrecision<float>(std::ostream &os)
{
    os.precision(7);
    os << std::fixed;
}

template <>
inline void TypeSetDefaultPrecision<double>(std::ostream &os)
{
    os.precision(14);
    os << std::fixed;
}

template <>
inline void TypeSetDefaultPrecision<long double>(std::ostream &os)
{
    os.precision(18);
    os << std::fixed;
}
#endif  // DOXYGEN_SKIP

/*! \} */  // End of group: TypeString
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // TYPE_H
