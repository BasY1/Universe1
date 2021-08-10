/*!
 * \file math/texttools.h
 * \author Michal Steller
 * \brief Floating point value string and standard output tools
 */

#ifndef TOOLSTEXT_H
#define TOOLSTEXT_H

#include <cstring>
#include <iostream>
#include <sstream>
#include <type_traits>

namespace Universe1 {

namespace TextTools {

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
 * \defgroup TypeString Type string tools
 * \brief Floating point string tools
 * \details
 *
 * \{
 */

/*!
 * \fn Universe1::Text::setDefaultPrecision(std::ostream &os)
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

/*! \} */  // End of group: TypeString

}  // namespace TextTools

}  // namespace Universe1

#endif  // TYPE_H
