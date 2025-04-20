/*!
 * \file src/Math/planeindices.cpp
 * \brief Plane indices cache implementation
 */

#include "planeindices.h"

namespace U1 {
namespace Math {

std::map<size_t, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>>
    PlaneIndices::m_cache = {};

std::map<size_t, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>>
    PlaneIndices::m_cacheInverted = {};

#ifndef DOXYGEN_SKIP

template <>
std::map<size_t, std::map<size_t, std::pair<std::vector<Vec2<float>>, std::vector<std::pair<size_t, size_t>>>>>
    PlaneCoords<float>::m_cache = {};

template <>
std::map<size_t, std::map<size_t, std::pair<std::vector<Vec2<double>>, std::vector<std::pair<size_t, size_t>>>>>
    PlaneCoords<double>::m_cache = {};

template <>
std::map<size_t, std::map<size_t, std::pair<std::vector<Vec2<long double>>, std::vector<std::pair<size_t, size_t>>>>>
    PlaneCoords<long double>::m_cache = {};

#endif  // DOXYGEN_SKIP

const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &
PlaneIndices::getQuadIndexes(const size_t _width, const size_t _height)
{
    std::map<size_t, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>>::iterator
        iw = m_cache.find(_width);
    if (iw == m_cache.end())
        iw = m_cache
                 .insert(
                     {_width, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>()})
                 .first;

    std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>::iterator ih =
        (*iw).second.find(_height);

    if (ih == (*iw).second.end())
    {
        const size_t offset = (_height - 1UL);
        const size_t cntLoop = (_width - 1UL) * offset;
        const size_t cntIndex = cntLoop * 4UL;

        ih = (*iw).second.insert({_height, {std::vector<uint>(), std::vector<std::pair<size_t, size_t>>()}}).first;
        std::vector<uint> &indices = (*ih).second.first;
        std::vector<std::pair<size_t, size_t>> &pool = (*ih).second.second;

        pool = createPool(cntLoop);

        if (pool.empty())
        {
            indices.reserve(cntIndex);
            const size_t last = (_width - 1UL);
            for (size_t i1 = 0UL; i1 < last; ++i1)
                for (size_t i2 = 0UL; i2 < offset; ++i2)
                {
                    const uint v0 = i1 * _height + i2;
                    indices.push_back(v0);
                    indices.push_back(v0 + 1U);
                    indices.push_back(v0 + _height + 1U);
                    indices.push_back(v0 + _height);
                }
        }
        else
        {

            indices.resize(cntIndex);
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, _height](uint *__out) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t i1 = (i / offset);
                            const size_t i2 = (i % offset);
                            const uint v0 = i1 * _height + i2;
                            size_t ii = (i1 * offset + i2) * 4UL;
                            __out[ii++] = v0;
                            __out[ii++] = v0 + 1U;
                            __out[ii++] = v0 + _height + 1U;
                            __out[ii] = v0 + _height;
                        }
                    },
                    indices.data()));
            for (std::thread &t : threads)
                t.join();
        }

        pool = createPool(cntIndex);
    }

    return (*ih).second;
}

const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &
PlaneIndices::getQuadIndexesInverted(const size_t _width, const size_t _height)
{
    std::map<size_t, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>>::iterator
        iw = m_cacheInverted.find(_width);
    if (iw == m_cacheInverted.end())
        iw = m_cacheInverted
                 .insert(
                     {_width, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>()})
                 .first;

    std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>::iterator ih =
        (*iw).second.find(_height);

    if (ih == (*iw).second.end())
    {
        const size_t offset = (_height - 1UL);
        const size_t cntLoop = (_width - 1UL) * offset;
        const size_t cntIndex = cntLoop * 4UL;

        ih = (*iw).second.insert({_height, {std::vector<uint>(), std::vector<std::pair<size_t, size_t>>()}}).first;
        std::vector<uint> &indices = (*ih).second.first;
        std::vector<std::pair<size_t, size_t>> &pool = (*ih).second.second;

        pool = createPool(cntLoop);

        if (pool.empty())
        {
            indices.reserve(cntIndex);

            const size_t last = (_width - 1UL);
            for (size_t i1 = 0UL; i1 < last; ++i1)
                for (size_t i2 = 0UL; i2 < offset; ++i2)
                {
                    const uint v0 = i1 * _height + i2;
                    indices.push_back(v0);
                    indices.push_back(v0 + _height);
                    indices.push_back(v0 + _height + 1U);
                    indices.push_back(v0 + 1U);
                }
        }
        else
        {
            indices.resize(cntIndex);

            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, _height](uint *__out) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t i1 = (i / offset);
                            const size_t i2 = (i % offset);
                            const uint v0 = i1 * _height + i2;
                            size_t ii = (i1 * offset + i2) * 4UL;
                            __out[ii++] = v0;
                            __out[ii++] = v0 + _height;
                            __out[ii++] = v0 + _height + 1U;
                            __out[ii] = v0 + 1U;
                        }
                    },
                    indices.data()));
            for (std::thread &t : threads)
                t.join();
        }

        pool = createPool(cntIndex);
    }

    return (*ih).second;
}

}  // namespace Math
}  // namespace U1

