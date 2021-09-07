/*!
 * \file math/texttools.h
 * \author Michal Steller
 * \brief Floating point value string and standard output tools
 */

#ifndef UNIVERSE1_TEXTTOOLS_TOOLSTEXT_H
#define UNIVERSE1_TEXTTOOLS_TOOLSTEXT_H

#include <cstring>
#include <iostream>
#include <sstream>
#include <type_traits>

#include <QString>

namespace Universe1 {

namespace TextTools {

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
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline void setDefaultPrecision(std::ostream &os);

#ifndef DOXYGEN_SKIP
template <>
inline void setDefaultPrecision<float>(std::ostream &os)
{
    os.precision(7);
    os << std::fixed;
}

template <>
inline void setDefaultPrecision<double>(std::ostream &os)
{
    os.precision(14);
    os << std::fixed;
}

template <>
inline void setDefaultPrecision<long double>(std::ostream &os)
{
    os.precision(18);
    os << std::fixed;
}
#endif  // DOXYGEN_SKIP

/*!
 * \brief Float value to \c std::string
 * \tparam T Template floating point type
 * \param _value Value for conversion
 * \returns Value as \c std::string
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline std::string toString(const T _value)
{
    std::stringstream ss;
    setDefaultPrecision<T>(ss);
    ss << _value;
    return ss.str();
}

/*!
 * \brief Float value to \c std::string
 * \tparam T Template floating point type
 * \param _value Value for conversion
 * \param _decimals Decimals count
 * \returns Value as \c std::string
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline std::string toString(const T _value, const std::streamsize _decimals)
{
    std::stringstream ss;
    ss.precision(_decimals);
    ss << std::fixed;
    ss << _value;
    return ss.str();
}

/*!
 * \brief Float value to \c QString
 * \tparam T Template floating point type
 * \param _value Value for conversion
 * \returns Value as \c QString
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline QString toQString(const T _value)
{
    return QString::fromStdString(toString<T>(_value));
}

/*!
 * \brief Float value to \c QString
 * \tparam T Template floating point type
 * \param _value Value for conversion
 * \param _decimals Decimals count
 * \returns Value as \c QString
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline QString toQString(const T _value, const int _decimals)
{
    if (_decimals < 0)
        return QString::fromStdString(toString<T>(_value));
    return QString::fromStdString(toString<T>(_value, std::max(0, _decimals)));
}

//

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value Attribute value
 * \param _decimals Decimals count
 * \returns HTML table row
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline QString htmlRow1of3(const QString &_name, const T _value, const int _decimals = -1)
{
    return "<tr><td><b>" + _name + "</b></td><td colspan=\"2\" align=\"center\">" +
        Universe1::TextTools::toQString(_value, _decimals) + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value1 Attribute 1 value
 * \param _value2 Attribute 2 value
 * \param _decimals Decimals count
 * \returns HTML table row
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline QString htmlRow2of3(const QString &_name, const T _value1, const T _value2, const int _decimals = -1)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + Universe1::TextTools::toQString(_value1, _decimals) + "</td><td>" +
        Universe1::TextTools::toQString(_value2, _decimals) + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value Attribute value
 * \returns HTML table row
 */
inline QString htmlRow1of3(const QString &_name, const QString &_value)
{
    return "<tr><td><b>" + _name + "</b></td><td colspan=\"2\" align=\"center\">" + _value + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value1 Attribute 1 value
 * \param _value2 Attribute 2 value
 * \returns HTML table row
 */
inline QString htmlRow2of3(const QString &_name, const QString &_value1, const QString &_value2)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + _value1 + "</td><td>" + _value2 + "</td></tr>";
}

/*! \} */  // End of group: TypeString

}  // namespace TextTools

}  // namespace Universe1

#endif  // UNIVERSE1_TEXTTOOLS_TOOLSTEXT_H
