/*!
 * \file math/typeconst.h
 * \author Michal Steller
 * \brief Floating point value constants
 */

#ifndef TYPECONST_H
#define TYPECONST_H

#include <cmath>
#include <type_traits>

namespace Universe1 {
namespace Const {

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_0()
{
    static const T tmp = 0;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_1()
{
    static const T tmp = 1;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_01()
{
    static const T tmp = 0.1l;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_001()
{
    static const T tmp = 0.01l;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_05()
{
    static const T tmp = 0.5l;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_2()
{
    static const T tmp = 2;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_3()
{
    static const T tmp = 3;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_4()
{
    static const T tmp = 4;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_10()
{
    static const T tmp = 10;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_100()
{
    static const T tmp = 100;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_PI()
{
    static const T tmp = static_cast<T>(M_PIl);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_2PI()
{
    static const T tmp = static_cast<T>(2.0l * M_PIl);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_4PI()
{
    static const T tmp = static_cast<T>(4.0l * M_PIl);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_PI_2()
{
    static const T tmp = static_cast<T>(M_PI_2l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_PI_3()
{
    static const T tmp = static_cast<T>(M_PIl / 3.0l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_2PI_3()
{
    static const T tmp = static_cast<T>((2.0l * M_PIl) / 3.0l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_4PI_3()
{
    static const T tmp = static_cast<T>((4.0l * M_PIl) / 3.0l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_SQRT2()
{
    static const T tmp = static_cast<T>(M_SQRT2l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_1_SQRT2()
{
    static const T tmp = static_cast<T>(M_SQRT1_2l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_SQRT3()
{
    static const T tmp = std::sqrt(3.0L);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_SQRT3_2()
{
    static const T tmp = std::sqrt(3.0L) / 2.0L;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_SQRT3_3()
{
    static const T tmp = std::sqrt(3.0L) / 3.0L;
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_RadInDeg()
{
    static const T tmp = static_cast<T>(180.0l / M_PIl);
    return tmp;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \defgroup TypeConstants Type constants
 * \brief Floating point type constants
 * \{
 */

/*!
 * \fn Universe1::Const::T_0()
 * \brief Getter for type specific value: 0
 * \tparam T Template floating point type
 * \returns 0 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_1()
 * \brief Getter for type specific value: 1
 * \tparam T Template floating point type
 * \returns 1 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_01()
 * \brief Getter for type specific value: 0.1
 * \tparam T Template floating point type
 * \returns 0.1 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_001()
 * \brief Getter for type specific value: 0.01
 * \tparam T Template floating point type
 * \returns 0.01 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_05()
 * \brief Getter for type specific value: 0.5
 * \tparam T Template floating point type
 * \returns 0.5 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_2()
 * \brief Getter for type specific value: 2
 * \tparam T Template floating point type
 * \returns 2 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_3()
 * \brief Getter for type specific value: 3
 * \tparam T Template floating point type
 * \returns 3 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_4()
 * \brief Getter for type specific value: 4
 * \tparam T Template floating point type
 * \returns 4 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_10()
 * \brief Getter for type specific value: 10
 * \tparam T Template floating point type
 * \returns 10 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_100()
 * \brief Getter for type specific value: 100
 * \tparam T Template floating point type
 * \returns 100 in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_PI()
 * \brief Getter for type specific value: \f$\pi\f$
 * \tparam T Template floating point type
 * \returns \f$\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_2PI()
 * \brief Getter for type specific value: \f$2\pi\f$
 * \tparam T Template floating point type
 * \returns \f$2\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_4PI()
 * \brief Getter for type specific value: \f$4\pi\f$
 * \tparam T Template floating point type
 * \returns \f$4\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_PI_2()
 * \brief Getter for type specific value: \f$0.5\pi\f$
 * \tparam T Template floating point type
 * \returns \f$0.5\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_PI_3()
 * \brief Getter for type specific value: \f$\frac{\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{\pi}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_2PI_3()
 * \brief Getter for type specific value: \f$\frac{2\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{2\pi}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_4PI_3()
 * \brief Getter for type specific value: \f$\frac{4\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{4\pi}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_SQRT2()
 * \brief Getter for type specific value: \f$\sqrt{2}\f$
 * \tparam T Template floating point type
 * \returns \f$\sqrt{2}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_1_SQRT2()
 * \brief Getter for type specific value: \f$\frac{1}{\sqrt{2}}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{1}{\sqrt{2}}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_SQRT3()
 * \brief Getter for type specific value: \f$\sqrt{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\sqrt{2}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_SQRT3_2()
 * \brief Getter for type specific value: \f$\frac{\sqrt{3}}{2}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{\sqrt{3}}{2}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_SQRT3_3()
 * \brief Getter for type specific value: \f$\frac{\sqrt{3}}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{\sqrt{3}}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Const::T_RadInDeg()
 * \brief Getter for type specific value: \f$\frac{4\pi}{3}\f$
 * \tparam T Template floating point type
 * \returns \f$\frac{4\pi}{3}\f$ in specific floating point type
 */

/*! \} */  // End of group: TypeConstants

}  // namespace Const

}  // namespace Universe1

#endif  // TYPECONST_H
