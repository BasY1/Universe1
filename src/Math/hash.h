/*!
 * \file src/Math/hash.h
 * \brief Hash tools
 */
#ifndef MATH_HASH_H
#define MATH_HASH_H

#include "type.h"

#include <QStringList>

namespace U1 {
namespace Math {

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

}  // namespace Math
}  // namespace U1

#endif  // MATH_HASH_H
