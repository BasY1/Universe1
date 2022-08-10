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

#include <list>
#include <map>
#include <set>
#include <vector>

#ifdef UNIVERSE1_USE_QT_LIB
#include <QString>
#include <QStringList>
#endif

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
 * \brief Join group of strings into single string
 * \tparam IT_t Template collection of strings iterator type
 * \param _first Iterator pointer to first text in collection
 * \param _last Iterator pointer to end of collection
 * \param _separator Separator text
 * \return Single string created from collection of strings
 */
template <typename IT_t>
inline std::string joinStrings(const IT_t &_first, const IT_t &_last, const std::string &_separator = "")
{
    std::stringstream ss;

    for (IT_t it = _first; it != _last;)
    {
        ss << (*it);
        ++it;
        if (it != _last)
            ss << _separator;
    }
    return ss.str();
}

/*!
 * \brief Join group of strings into single string
 * \param _values Collection of texts
 * \param _separator Separator text
 * \return Single string created from collection of strings
 */
inline std::string joinStrings(const std::list<std::string> &_values, const std::string &_separator = "")
{
    return joinStrings(_values.cbegin(), _values.cend(), _separator);
}

/*!
 * \brief Float value to \c std::string
 * \tparam T Template floating point type
 * \param _value Value for conversion
 * \return Value as \c std::string
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
 * \return Value as \c std::string
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

#ifdef UNIVERSE1_USE_QT_LIB

/*!
 * \brief Float value to \c QString
 * \tparam T Template floating point type
 * \param _value Value for conversion
 * \return Value as \c QString
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
 * \return Value as \c QString
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline QString toQString(const T _value, const int _decimals)
{
    if (_decimals < 0)
        return QString::fromStdString(toString<T>(_value));
    return QString::fromStdString(toString<T>(_value, std::max(0, _decimals)));
}

#endif

//

/*!
 * \brief Tool function prepare HTML table row (with 2 cols)
 * \param _name Attribute name
 * \param _value Attribute value
 * \return HTML table row
 */
inline std::string htmlRow(const std::string &_name, const std::string &_value)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + _value + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row (with 2 cols)
 * \param _name Attribute name
 * \param _value Attribute value
 * \param _decimals Decimals count
 * \return HTML table row
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline std::string htmlRow(const std::string &_name, const T _value, const int _decimals = -1)
{
    return htmlRow(_name, toString(_value, _decimals));
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value Attribute value
 * \param _decimals Decimals count
 * \return HTML table row
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline std::string htmlRow1of3(const std::string &_name, const T _value, const int _decimals = -1)
{
    return "<tr><td><b>" + _name + "</b></td><td colspan=\"2\">" + toString(_value, _decimals) + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value1 Attribute 1 value
 * \param _value2 Attribute 2 value
 * \param _decimals Decimals count
 * \return HTML table row
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline std::string htmlRow2of3(const std::string &_name, const T _value1, const T _value2, const int _decimals = -1)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + toString(_value1, _decimals) + "</td><td>" +
        toString(_value2, _decimals) + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value Attribute value
 * \return HTML table row
 */
inline std::string htmlRow1of3(const std::string &_name, const std::string &_value)
{
    return "<tr><td><b>" + _name + "</b></td><td colspan=\"2\">" + _value + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value1 Attribute 1 value
 * \param _value2 Attribute 2 value
 * \return HTML table row
 */
inline std::string htmlRow2of3(const std::string &_name, const std::string &_value1, const std::string &_value2)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + _value1 + "</td><td>" + _value2 + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _values Collection of values
 * \return HTML table row
 */
inline std::string htmlRow(const std::string &_name, const std::list<std::string> &_values)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + joinStrings(_values, "</td><td>") + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _values Collection of values
 * \return HTML table row
 */
inline std::string htmlRowH(const std::list<std::string> &_values)
{
    return "<tr><th>" + joinStrings(_values, "</th><th>") + "</th></tr>";
}

/*! \} */  // End of group: TypeString

}  // namespace TextTools

}  // namespace Universe1

#endif  // UNIVERSE1_TEXTTOOLS_TOOLSTEXT_H
