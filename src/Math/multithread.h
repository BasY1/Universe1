/*!
 * \file src/Math/multithread.h
 * \brief Multithread mathematics tools
 */
#ifndef MATH_MULTITHREAD_H
#define MATH_MULTITHREAD_H

#include "type.h"

#include <thread>
#include <vector>
#include <list>

namespace U1 {
namespace Math {

/*!
 * \brief Creates an array of evenly distributed indices up to given count
 * \tparam IT Unsigned integer type
 * \param _itemCount Item count
 * \param _minThreadItems Minimal count of items for a single thread
 * \param _maxPoolSize Maximum multi-thread pool size, default \sa std::thread::hardware_concurrency()
 * \return Evenly distributed indices up to given \a _itemCount
 */
template <typename IT, typename = std::enable_if<std::is_unsigned<IT>::value>>
std::vector<std::pair<IT, IT>> createPool(const IT _itemCount,
                                          const IT _minThreadItems = 1UL,
                                          const IT _maxPoolSize = std::thread::hardware_concurrency())
{
    if (_itemCount <= IT(1) || _maxPoolSize < IT(2))
        return {};

    const IT minCnt = std::max(IT(1), _minThreadItems);
    if (_itemCount <= minCnt)
        return {};

    const IT poolSizeNeed = _itemCount / minCnt;
    if (poolSizeNeed <= IT(1))
        return {};

    const IT poolSizeUsed = std::min(_maxPoolSize, poolSizeNeed);

    std::vector<std::pair<IT, IT>> result;
    result.resize(poolSizeUsed);

    IT t = IT(0);
    IT i = IT(0);
    IT vc2 = _itemCount;
    IT tc2 = poolSizeUsed;

    while (tc2 != IT(0))
    {
        const IT io = ((vc2 % tc2) == IT(0) ? IT(0) : IT(1)) + vc2 / tc2;
        result[t++] = {i, io};
        i += io;
        vc2 -= io;
        --tc2;
    }

    return result;
}

/*!
 * \brief Copy data between two arrays
 * \tparam T Any type with defined \c operator==
 * \tparam IT Unsigned integer type
 * \param _to Output data array pointer
 * \param _from Input data array pointer
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T, typename IT, typename = std::enable_if<std::is_unsigned<IT>::value>>
void copyData(T *_to, const T *_from, const IT _count, const std::vector<std::pair<IT, IT>> &_pool)
{
    if (_pool.empty())
    {
        for (IT i = 0UL; i < _count; ++i)
            _to[i] = _from[i];
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<IT, IT> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t](T *__to, const T *__from) {
                    const IT end = t.first + t.second;
                    for (IT i = t.first; i < end; ++i)
                        __to[i] = __from[i];
                },
                _to,
                _from));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Search for the minimum and maximum value
 * \tparam T Any numeric type
 * \tparam IT Unsigned integer type
 * \param _outMin Output minimum
 * \param _outMax Output maximum
 * \param _data Pointer to data array
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T,
          typename IT,
          typename = std::enable_if<std::is_arithmetic<T>::value && std::is_unsigned<IT>::value>>
void minMaxData(T &_outMin, T &_outMax, const T *_data, const IT _count, const std::vector<std::pair<IT, IT>> &_pool)
{
    if (_count == IT(0))
        return;
    _outMin = _data[IT(0)];
    _outMax = _data[IT(0)];
    if (_pool.empty() || ((_count / IT(_pool.size())) < IT(2)))
    {
        for (IT i = IT(1); i < _count; ++i)
        {
            if (_outMin > _data[i])
                _outMin = _data[i];
            if (_outMax < _data[i])
                _outMax = _data[i];
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<T> tDataMin(_pool.size(), _outMin);
        std::vector<T> tDataMax(_pool.size(), _outMax);
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<IT, IT> &t : std::as_const(_pool))
        {
            threads.push_back(std::thread(
                [t](T &__outMin, T &__outMax, const T *__data) {
                    const IT end = t.first + t.second;
                    for (IT i = t.first; i < end; ++i)
                    {
                        if (__outMin > __data[i])
                            __outMin = __data[i];
                        if (__outMax < __data[i])
                            __outMax = __data[i];
                    }
                },
                std::ref(tDataMin[tt]),
                std::ref(tDataMax[tt]),
                _data));
            tt++;
        }
        for (std::thread &t : threads)
            t.join();
        for (const T &i : std::as_const(tDataMin))
            if (_outMin > i)
                _outMin = i;
        for (const T &i : std::as_const(tDataMax))
            if (_outMax < i)
                _outMax = i;
    }
}

/*!
 * \brief Setup constant value to all items in the array
 * \tparam T Any numeric type
 * \tparam IT Unsigned integer type
 * \param _data Output data array
 * \param _value Constant value to set
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T,
          typename IT,
          typename = std::enable_if<std::is_arithmetic<T>::value && std::is_unsigned<IT>::value>>
void setConstantData(T *_data, const T _value, const IT _count, const std::vector<std::pair<IT, IT>> &_pool)
{
    if (_pool.empty())
    {
        for (IT i = 0UL; i < _count; ++i)
            _data[i] = _value;
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<IT, IT> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _value](T *__data) {
                    const IT end = t.first + t.second;
                    for (IT i = t.first; i < end; ++i)
                        __data[i] = _value;
                },
                _data));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Add constant value to all items in the array
 * \tparam T Any numeric type
 * \tparam IT Unsigned integer type
 * \param _data Output data array
 * \param _value Constant value to add to all array items
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T,
          typename IT,
          typename = std::enable_if<std::is_arithmetic<T>::value && std::is_unsigned<IT>::value>>
void addConstantData(T *_data, const T _value, const IT _count, const std::vector<std::pair<IT, IT>> &_pool)
{
    if (_pool.empty())
    {
        for (IT i = 0UL; i < _count; ++i)
            _data[i] += _value;
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<IT, IT> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _value](T *__data) {
                    const IT end = t.first + t.second;
                    for (IT i = t.first; i < end; ++i)
                        __data[i] += _value;
                },
                _data));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Multiple items in the array by a constant value
 * \tparam T Any numeric type
 * \tparam IT Unsigned integer type
 * \param _data Output data array
 * \param _value Constant value to multiple all array items
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T,
          typename IT,
          typename = std::enable_if<std::is_arithmetic<T>::value && std::is_unsigned<IT>::value>>
void multConstantData(T *_data, const T _value, const IT _count, const std::vector<std::pair<IT, IT>> &_pool)
{
    if (_pool.empty())
    {
        for (IT i = 0UL; i < _count; ++i)
            _data[i] *= _value;
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<IT, IT> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _value](T *__data) {
                    const IT end = t.first + t.second;
                    for (IT i = t.first; i < end; ++i)
                        __data[i] *= _value;
                },
                _data));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Create array with values from \a _valueStart up to \a _valueEnd with given \a _step
 * \tparam T Floating point type
 * \param _out Output vector
 * \param _valueStart Start value (included in output collection)
 * \param _valueEnd End value (included in output collection)
 * \param _step Distribution step
 * \return Collection of steps between \a _valueStart and \a _valueEnd
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
size_t fillSteps(std::vector<T> &_out, const T _valueStart, const T _valueEnd, const T _step)
{
    _out.clear();
    if (!isPositive(_step))
        return 0UL;

    const T beg = std::min(_valueStart, _valueEnd);
    const T end = std::max(_valueStart, _valueEnd);

    if (equals(beg, end))
    {
        _out = {beg};
        return _out.size();
    }

    int64_t idxBeg = static_cast<int64_t>(beg / _step);
    T beg2 = idxBeg * _step;

    while (isLessOrEqual(beg2, beg))
    {
        idxBeg++;
        beg2 += _step;
    }

    int64_t idxEnd = static_cast<int64_t>(end / _step);
    T end2 = idxEnd * _step;

    while (isMoreOrEqual(end2, end))
    {
        idxEnd--;
        end2 -= _step;
    }

    if (idxBeg > idxEnd)
    {
        _out = {beg, end};
        return _out.size();
    }

    if (idxBeg == idxEnd)
    {
        _out = {beg, beg2, end};
        return _out.size();
    }

    const size_t cntInn = 1UL + idxEnd - idxBeg;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntInn);

    if (pool.empty())
    {
        _out.reserve(cntInn + 2UL);
        _out.push_back(beg);
        for (size_t i = 0UL; i < cntInn; ++i)
            _out.push_back(beg2 + static_cast<T>(i) * _step);
        _out.push_back(end);
        return _out.size();
    }

    _out.resize(cntInn + 2UL);
    _out[0UL] = beg;
    _out[cntInn + 1UL] = end;

    std::vector<std::thread> threads;
    threads.reserve(pool.size());
    for (const std::pair<size_t, size_t> &t : std::as_const(pool))
        threads.push_back(std::thread(
            [t, beg2, _step](T *__out) {
                const size_t end = t.first + t.second;
                for (size_t i = t.first; i < end; ++i)
                    __out[i + 1UL] = beg2 + static_cast<T>(i) * _step;
            },
            _out.data()));

    for (std::thread &t : threads)
        t.join();

    return _out.size();
}

/*!
 * \brief Create array with values from \a _valueStart up to \a _valueEnd with given \a _step
 * \tparam T Floating point type
 * \param _out Output vector
 * \param _valueStart Start value (included in output collection only when aligned with step)
 * \param _valueEnd End value (included in output collection only when aligned with step)
 * \param _step Distribution step
 * \return Collection of steps between \a _valueStart and \a _valueEnd
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
size_t fillAlignedSteps(std::vector<T> &_out, const T _valueStart, const T _valueEnd, const T _step)
{
    _out.clear();
    if (!isPositive(_step))
        return 0UL;

    const T beg = std::min(_valueStart, _valueEnd);
    const T end = std::max(_valueStart, _valueEnd);

    if (equals(beg, end))
    {
        const T beg2 = static_cast<T>(static_cast<int64_t>(beg / _step)) * _step;
        if (equals(beg, beg2))
            _out = {beg};
        return _out.size();
    }

    int64_t idxBeg = static_cast<int64_t>(beg / _step);
    T beg2 = idxBeg * _step;

    const bool isBeg = equals(beg, beg2);
    while (isLessOrEqual(beg2, beg))
    {
        idxBeg++;
        beg2 += _step;
    }

    int64_t idxEnd = static_cast<int64_t>(end / _step);
    T end2 = idxEnd * _step;
    const bool isEnd = equals(end, end2);

    while (isMoreOrEqual(end2, end))
    {
        idxEnd--;
        end2 -= _step;
    }

    if (idxBeg > idxEnd)
    {
        if (isBeg)
            _out.push_back(beg);
        if (isEnd)
            _out.push_back(end);
        return _out.size();
    }

    if (idxBeg == idxEnd)
    {
        if (isBeg)
            _out.push_back(beg);
        else
            _out.push_back(beg2);

        if (isEnd && !equals(end, beg2))
            _out.push_back(end);
        return _out.size();
    }

    const size_t begOffset = (isBeg ? 1UL : 0UL);
    const size_t cntInn = 1UL + idxEnd - idxBeg;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntInn);
    if (pool.empty())
    {
        _out.reserve(cntInn + begOffset + (isEnd ? 1UL : 0UL));
        if (isBeg)
            _out.push_back(beg);
        for (size_t i = 0UL; i < cntInn; ++i)
            _out.push_back(beg2 + static_cast<T>(i) * _step);
        if (isEnd)
            _out.push_back(end);
        return _out.size();
    }

    _out.resize(cntInn + begOffset + (isEnd ? 1UL : 0UL));
    if (isBeg)
        _out[0UL] = beg;
    if (isEnd)
        _out[cntInn + begOffset] = end;

    std::vector<std::thread> threads;
    threads.reserve(pool.size());
    for (const std::pair<size_t, size_t> &t : std::as_const(pool))
        threads.push_back(std::thread(
            [t, beg2, _step](T *__out) {
                const size_t end = t.first + t.second;
                for (size_t i = t.first; i < end; ++i)
                    __out[i] = beg2 + static_cast<T>(i) * _step;
            },
            &_out.data()[begOffset]));

    for (std::thread &t : threads)
        t.join();

    return _out.size();
}
// clang-format off
#define PATTERN_SOLID          0b1111111111111111111111111111111111111111111111111111111111111111  //!< Solid line
#define PATTERN_DASH_L         0b1111111111111111111111111111111111111111111111110000000000000000  //!< Dash long-short
#define PATTERN_DASH_S         0b1111111111111111000000000000000000000000000000000000000000000000  //!< Dash short-long
#define PATTERN_DASH_1         0b1111111111111111111111111111111100000000000000000000000000000000  //!< Dash 1 - longest
#define PATTERN_DASH_2         0b1111111111111111000000000000000011111111111111110000000000000000  //!< Dash 2
#define PATTERN_DASH_3         0b1111111100000000111111110000000011111111000000001111111100000000  //!< Dash 3
#define PATTERN_DASH_4         0b1111000011110000111100001111000011110000111100001111000011110000  //!< Dash 4 - shortest
#define PATTERN_DOTS_1         0b1100110011001100110011001100110011001100110011001100110011001100  //!< Dots 1 short space
#define PATTERN_DOTS_2         0b1010101010101010101010101010101010101010101010101010101010101010  //!< Dots 2 short space
#define PATTERN_DOTS_1S        0b1100000011000000110000001100000011000000110000001100000011000000  //!< Dots 1 
#define PATTERN_DOTS_2S        0b1000100010001000100010001000100010001000100010001000100010001000  //!< Dots 2 
#define PATTERN_DOTS_1XS       0b1100000000000000110000000000000011000000000000001100000000000000  //!< Dots 1       
#define PATTERN_DOTS_2XS       0b1000000010000000100000001000000010000000100000001000000010000000  //!< Dots 2       
#define PATTERN_DOTS_1XXS      0b1100000000000000000000000000000011000000000000000000000000000000  //!< Dots 1 long space
#define PATTERN_DOTS_2XXS      0b1000000000000000100000000000000010000000000000001000000000000000  //!< Dots 2 long space
#define PATTERN_DASH_DOT_1     0b1111111111111111111111111111111100000000000011111111000000000000  //!< Dash-dot 1    
#define PATTERN_DASH_DOT_2     0b1111111111111111000000111100000011111111111111110000001111000000  //!< Dash-dot 2    
#define PATTERN_DASH_DOT_3     0b1111111100011000111111110001100011111111000110001111111100011000  //!< Dash-dot 3    
#define PATTERN_DASH_DOT_DOT_1 0b1111111111111111111111111111111100000011111110000001111111000000  //!< Dash-dot-dot 1
#define PATTERN_DASH_DOT_DOT_2 0b1111111111110000111100001111000011111111111100001111000011110000  //!< Dash-dot-dot 2
#define PATTERN_DASH_DOT_DOT_3 0b1111110011001100111111001100110011111100110011001111110011001100  //!< Dash-dot-dot 3
// clang-format on

/*!
 * \brief fillDashPattern
 * \param _out Output collection
 * \param _pattern Pattern binary mask
 * \param _start Start value
 * \param _end End value
 * \param _step Step for single bit
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
void fillDashPattern(
    std::vector<std::pair<T, T>> &_out, const uint64_t _pattern, const T _start, const T _end, const T _step)
{
    _out.clear();
    if (_pattern == 0UL)
        return;

    if (_pattern == PATTERN_SOLID)
    {
        _out = {{_start, _end}};
        return;
    }

    std::list<std::pair<uint64_t, uint64_t>> pl;
    {
        uint64_t mask = (1UL << 63UL);
        uint64_t start = 0UL;
        uint64_t idx = 1UL;
        bool is1 = ((_pattern & mask) == mask);
        uint64_t cnt = is1 ? 1UL : 0UL;

        mask >>= 1UL;
        while (mask != 0UL)
        {
            const bool nextIs1 = ((_pattern & mask) == mask);
            if (is1 && nextIs1)
            {
                cnt++;
            }
            else if (is1 && !nextIs1)
            {
                pl.push_back({start, cnt});
                is1 = nextIs1;
            }
            else if (!is1 && nextIs1)
            {
                is1 = nextIs1;
                start = idx;
                cnt = 1UL;
            }

            idx++;
            mask >>= 1UL;
        }
    }

    const uint64_t cntSeg = pl.size();
    std::vector<std::pair<T, T>> p;
    p.reserve(cntSeg);
    for (const std::pair<uint64_t, uint64_t> &i : std::as_const(pl))
        p.push_back({T(i.first) * _step, T(i.first + i.second) * _step});

    const T beg = std::min(_start, _end);
    const T end = std::max(_start, _end);
    const T pLen = T(64) * _step;

    int64_t oBeg = int64_t(beg / pLen);
    int64_t oEnd = int64_t(end / pLen);
    while (Math::isMoreNotEqual(T(oBeg) * pLen, beg))
        --oBeg;

    while (Math::isLessNotEqual(T(oEnd) * pLen, end))
        ++oEnd;

    const T beg2 = T(oBeg) * pLen;
    const T end2 = T(oEnd) * pLen;
    const bool isBeg = Math::equals(beg, beg2);
    const bool isEnd = Math::equals(end, end2);

    if (isBeg && isEnd)
    {
        const uint64_t cntSegs = uint64_t(oEnd - oBeg);
        const uint64_t cntItems = cntSegs * cntSeg;
        const std::vector<std::pair<uint64_t, uint64_t>> pool = createPool(cntItems);
        if (pool.empty())
        {
            _out.reserve(cntItems);
            for (uint64_t s1 = 0UL; s1 < cntSegs; ++s1)
            {
                const T beg3 = beg2 + T(s1) * pLen;
                for (uint64_t s2 = 0UL; s2 < cntSeg; ++s2)
                    _out.push_back({beg3 + p[s2].first, beg3 + p[s2].second});
            }
        }
        else
        {
            _out.resize(cntItems);
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<uint64_t, uint64_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, cntSeg, beg2, pLen](std::pair<T, T> *__out, const std::pair<T, T> *__seg) {
                        const uint64_t end = t.first + t.second;
                        for (uint64_t i = t.first; i < end; ++i)
                        {
                            const uint64_t s2 = i % cntSeg;
                            const T beg3 = beg2 + T(i / cntSeg) * pLen;
                            __out[i] = {beg3 + __seg[s2].first, beg3 + __seg[s2].second};
                        }
                    },
                    _out.data(),
                    p.data()));

            for (std::thread &t : threads)
                t.join();
        }

        return;
    }

    std::list<std::pair<T, T>> pBeg;
    if (!isBeg)
    {
        for (uint64_t s2 = 0UL; s2 < cntSeg; ++s2)
        {
            const T x2 = beg2 + p[s2].second;
            if (Math::isLessOrEqual(x2, beg))
                continue;

            const T x1 = beg2 + p[s2].first;
            if (Math::isMoreOrEqual(x1, end))
            {
                if (!pBeg.empty())
                {
                    _out.reserve(pBeg.size());
                    _out.insert(_out.end(), pBeg.cbegin(), pBeg.cend());
                }
                return;
            }

            T xx1 = x1;
            if (Math::isLessOrEqual(x1, beg))
                xx1 = beg;

            if (Math::isMoreOrEqual(x2, end))
            {
                pBeg.push_back({xx1, end});
                _out.reserve(pBeg.size());
                _out.insert(_out.end(), pBeg.cbegin(), pBeg.cend());
                return;
            }

            pBeg.push_back({xx1, x2});
        }
    }

    std::list<std::pair<T, T>> pEnd;
    if (!isEnd)
    {
        const T beg3 = end2 - pLen;
        for (uint64_t s2 = 0UL; s2 < cntSeg; ++s2)
        {
            const T x1 = beg3 + p[s2].first;
            if (Math::isMoreOrEqual(x1, end))
                break;

            const T x2 = beg3 + p[s2].second;
            if (Math::isMoreOrEqual(x2, end))
            {
                pEnd.push_back({x1, end});
                break;
            }
            pEnd.push_back({x1, x2});
        }
    }

    const uint64_t cntSegsIn = (oEnd - (isEnd ? 0UL : 1UL)) - (oBeg + (isBeg ? 0UL : 1UL));
    const uint64_t cntItemsIn = cntSegsIn * cntSeg;
    const uint64_t cntItems = cntItemsIn + pBeg.size() + pEnd.size();

    _out.resize(cntItems);

    uint64_t i = 0;
    for (const std::pair<T, T> &x : std::as_const(pBeg))
        _out[i++] = x;

    i = cntItemsIn + pBeg.size();
    for (const std::pair<T, T> &x : std::as_const(pEnd))
        _out[i++] = x;

    if (cntSegsIn == 0UL)
        return;

    const T beg3 = isBeg ? beg : (beg2 + pLen);
    const std::vector<std::pair<uint64_t, uint64_t>> pool = createPool(cntItemsIn);
    if (pool.empty())
    {
        i = pBeg.size();
        for (uint64_t s1 = 0UL; s1 < cntSegsIn; ++s1)
        {
            const T beg4 = beg3 + T(s1) * pLen;
            for (uint64_t s2 = 0UL; s2 < cntSeg; ++s2)
                _out[i++] = {beg4 + p[s2].first, beg4 + p[s2].second};
        }
    }
    else
    {
        const uint64_t pbs = pBeg.size();
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<uint64_t, uint64_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, pbs, cntSeg, beg3, pLen](std::pair<T, T> *__out, const std::pair<T, T> *__seg) {
                    const uint64_t end = t.first + t.second;
                    for (uint64_t i = t.first; i < end; ++i)
                    {
                        const uint64_t s2 = i % cntSeg;
                        const T beg4 = beg3 + T(i / cntSeg) * pLen;
                        __out[i + pbs] = {beg4 + __seg[s2].first, beg4 + __seg[s2].second};
                    }
                },
                _out.data(),
                p.data()));

        for (std::thread &t : threads)
            t.join();
    }
}

}  // namespace Math
}  // namespace U1

#endif  // MATH_MULTITHREAD_H
