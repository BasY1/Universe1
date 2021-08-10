/*!
 * \file math/type.h
 * \author Michal Steller
 * \brief Floating point value tools and templates
 */

#ifndef TYPE_H
#define TYPE_H

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

/*! \} */  // End of group: TypeCompare

}  // namespace Type
}  // namespace Universe1

#endif  // TYPE_H
