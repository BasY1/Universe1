/*!
 * \file src/Math/planeindices.h
 * \brief Plane indices cache
 */

#ifndef MATH_PLANEINDICES_H
#define MATH_PLANEINDICES_H

#include "vec2.h"
#include "multithread.h"
#include <map>

namespace U1 {
namespace Math {

/*! \brief Plane indices cache */
struct PlaneIndices
{
 private:
    /*! \brief Indices 2D array like cache */
    static std::map<size_t, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>>
        m_cache;

    /*! \brief Indices 2D array like cache - inverted, to show opposite side */
    static std::map<size_t, std::map<size_t, std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>>>>
        m_cacheInverted;

 public:
    /*! \brief Clear cache */
    inline static void clearCache()
    {
        m_cache.clear();
        m_cacheInverted.clear();
    }

    /*!
     * \brief Get area quad indexes
     * \param _width Steps within the width
     * \param _height Steps within the height
     * \return Cached quad indexes
     */
    static const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &
    getQuadIndexes(const size_t _width, const size_t _height);

    /*!
     * \brief Get area quad indexes - inverted, to show opposite side
     * \param _width Steps within the width
     * \param _height Steps within the height
     * \return Cached quad indexes
     */
    static const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &
    getQuadIndexesInverted(const size_t _width, const size_t _height);
};

/*!
 * \brief  Plane texture coordinates cache
 * \tparam T Template floating point type
 */
template <typename T>
struct PlaneCoords
{
 private:
    /*! \brief 2D array cache */
    static std::map<size_t, std::map<size_t, std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>>>>
        m_cache;

 public:
    static const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &
    getCoords(const size_t _width, const size_t _height);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Get area texture coordinates
 * \tparam T Template floating point type
 * \param _width Steps within the width
 * \param _height Steps within the height
 * \return Cached texture coordinates
 */
template <typename T>
const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &
PlaneCoords<T>::getCoords(const size_t _width, const size_t _height)
{
    typename std::map<
        size_t,
        std::map<size_t, std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>>>>::iterator iw =
        m_cache.find(_width);
    if (iw == m_cache.end())
        iw = m_cache
                 .insert({_width,
                          std::map<size_t, std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>>>()})
                 .first;

    typename std::map<size_t, std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>>>::iterator ih =
        (*iw).second.find(_height);

    if (ih == (*iw).second.end())
    {
        const T widthF = T(_width - 1UL);
        const T heightF = T(_height - 1UL);
        const size_t cntVertex = _width * _height;

        ih = (*iw).second.insert({_height, {std::vector<Vec2<T>>(), std::vector<std::pair<size_t, size_t>>()}}).first;
        std::vector<Vec2<T>> &coords = (*ih).second.first;
        std::vector<std::pair<size_t, size_t>> &pool = (*ih).second.second;
        pool = createPool(cntVertex);
        if (pool.empty())
        {
            coords.reserve(cntVertex);
            for (size_t i = 0UL; i < cntVertex; ++i)
                coords.push_back({T(i / _height) / widthF, T(i % _height) / heightF});
        }
        else
        {
            coords.resize(cntVertex);

            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _height, widthF, heightF](Vec2<T> *__out) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] = {T(i / _height) / widthF, T(i % _height) / heightF};
                    },
                    coords.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    return (*ih).second;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef PlaneCoords<float> PlaneCoordsF;        //!< 32 bit floating point precision plane coordinates cache
typedef PlaneCoords<double> PlaneCoordsD;       //!< 64 bit floating point precision plane coordinates cache
typedef PlaneCoords<long double> PlaneCoordsL;  //!< 128 bit floating point precision plane coordinates cache

}  // namespace Math
}  // namespace U1

#endif  // MATH_PLANEINDICES_H
