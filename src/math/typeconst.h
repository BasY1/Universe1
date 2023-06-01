/*!
 * \file math/typeconst.h
 * \author Michal Steller
 * \brief Floating point value constants
 */

#ifndef UNIVERSE1_CONST_TYPECONST_H
#define UNIVERSE1_CONST_TYPECONST_H

#include <cmath>
#include <cstdint>
#include <limits>

#include <cstring>
#include <iostream>
#include <sstream>

#include <thread>

#include <type_traits>

#include <list>
#include <map>
#include <set>
#include <vector>

#ifdef UNIVERSE1_USE_QT_LIB
#include <QCommandLineParser>
#include <QGuiApplication>

#include <QOffscreenSurface>
#include <QOpenGLBuffer>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QPainter>
#include <QProcess>
#include <QTextDocument>

#include <QDir>
#include <QFile>

#include <QColor>
#include <QDateTime>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QString>
#include <QStringList>
#include <QVector3D>
#endif

namespace Universe1 {
namespace Math {
namespace Const {

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
inline T T_2PIxR(const T _R)
{
    return _R * T_2PI<T>();
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_PIxRxR(const T _R)
{
    return _R * _R * T_PI<T>();
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_4PIxRxR(const T _R)
{
    static const T tmp = static_cast<T>(4.0l * M_PIl);
    return _R * _R * tmp;
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
inline T T_PI_4()
{
    static const T tmp = static_cast<T>(M_PIl / 4.0l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_2PI_3()
{
    static const T tmp = static_cast<T>((2.0l * M_PIl) / 3.0l);
    return tmp;
}

template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline T T_3PI_4()
{
    static const T tmp = static_cast<T>((3.0l * M_PIl) / 4.0l);
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
 * \fn Universe1::Math::Const::T_PI()
 * \brief Getter for type specific value: \f$\pi\f$
 * \tparam T Template floating point type
 * \return \f$\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_2PI()
 * \brief Getter for type specific value: \f$2\pi\f$
 * \tparam T Template floating point type
 * \return \f$2\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_2PIxR(const T _R)
 * \brief Circle length
 * \tparam T Template floating point type
 * \param _R Radius
 * \return Length of circle with given radius
 */

/*!
 * \fn Universe1::Math::Const::T_PIxRxR(const T _R)
 * \brief Circle area
 * \tparam T Template floating point type
 * \param _R Radius
 * \return Area of circle with given radius
 */

/*!
 * \fn Universe1::Math::Const::T_4PI()
 * \brief Getter for type specific value: \f$4\pi\f$
 * \tparam T Template floating point type
 * \return \f$4\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_4PIxRxR(const T _R)
 * \brief 4 times circle area
 * \tparam T Template floating point type
 * \param _R Radius
 * \return \f$4\pi R^2\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_PI_2()
 * \brief Getter for type specific value: \f$0.5\pi\f$
 * \tparam T Template floating point type
 * \return \f$0.5\pi\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_PI_3()
 * \brief Getter for type specific value: \f$\frac{\pi}{3}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{\pi}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_PI_4()
 * \brief Getter for type specific value: \f$\frac{\pi}{4}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{\pi}{4}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_2PI_3()
 * \brief Getter for type specific value: \f$\frac{2\pi}{3}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{2\pi}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_3PI_4()
 * \brief Getter for type specific value: \f$\frac{3\pi}{4}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{3\pi}{4}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_4PI_3()
 * \brief Getter for type specific value: \f$\frac{4\pi}{3}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{4\pi}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_SQRT2()
 * \brief Getter for type specific value: \f$\sqrt{2}\f$
 * \tparam T Template floating point type
 * \return \f$\sqrt{2}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_1_SQRT2()
 * \brief Getter for type specific value: \f$\frac{1}{\sqrt{2}}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{1}{\sqrt{2}}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_SQRT3()
 * \brief Getter for type specific value: \f$\sqrt{3}\f$
 * \tparam T Template floating point type
 * \return \f$\sqrt{2}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_SQRT3_2()
 * \brief Getter for type specific value: \f$\frac{\sqrt{3}}{2}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{\sqrt{3}}{2}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_SQRT3_3()
 * \brief Getter for type specific value: \f$\frac{\sqrt{3}}{3}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{\sqrt{3}}{3}\f$ in specific floating point type
 */

/*!
 * \fn Universe1::Math::Const::T_RadInDeg()
 * \brief Getter for type specific value: \f$\frac{4\pi}{3}\f$
 * \tparam T Template floating point type
 * \return \f$\frac{4\pi}{3}\f$ in specific floating point type
 */

/*! \} */  // End of group: TypeConstants

}  // namespace Const
}  // namespace Math
}  // namespace Universe1

#endif  // UNIVERSE1_CONST_TYPECONST_H
