/*!
 * \file src/Math/orientation.h
 * \brief 3D Orientation structure
 */

#ifndef MATH_ORIENTATION3D_H
#define MATH_ORIENTATION3D_H

#include "camera.h"

#include "multithread.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D Orientation within the space
 * \tparam T Template floating point type
 */
template <typename T>
struct Orientation
{
    Vec3<T> center = {};                 //!< Central point
    Vec3<T> normal1 = Vec3<T>::unitX();  //!< Major axis
    Vec3<T> normal2 = Vec3<T>::unitY();  //!< Secondary axis
    Vec3<T> normal3 = Vec3<T>::unitZ();  //!< Third axis

    /*! \brief Default constructor */
    Orientation() = default;

    /*!
     * \brief Constructor
     * \param _center Initial central point
     * \param _normal Initial major axis
     */
    inline Orientation(const Vec3<T> &_center, const Vec3<T> &_normal)
        : center(_center)
        , normal1(_normal.normalized())
        , normal2(normal1.perpendicularNormal())
        , normal3(Vec3<T>::cross(normal1, normal2).normalized())
    {
    }

    /*!
     * \brief Constructor
     * \param _center Initial central point
     * \param _normal Initial major axis
     * \param _arm Initial secondary axis
     */
    inline Orientation(const Vec3<T> &_center, const Vec3<T> &_normal, const Vec3<T> &_arm)
        : center(_center)
        , normal1(_normal.normalized())
    {
        normal3 = Vec3<T>::cross(normal1, _arm).normalized();
        normal2 = Vec3<T>::cross(normal3, normal1).normalized();
    }

    /*!
     * \brief Constructor
     * \param _center Initial central point
     * \param _normal1 Initial major axis
     * \param _normal2 Initial secondary axis
     * \param _normal3 Initial third axis
     */
    inline Orientation(const Vec3<T> &_center,
                       const Vec3<T> &_normal1,
                       const Vec3<T> &_normal2,
                       const Vec3<T> &_normal3)
        : center(_center)
        , normal1(_normal1)
        , normal2(_normal2)
        , normal3(_normal3)
    {
    }

    /*!
     * \brief Constructor
     * \param _camera Camera
     * \param _center Initial central point
     * \param _spinRad Rotation angle (in radians) around major view axis
     */
    inline Orientation(const Camera<T> &_camera, const Vec3<T> &_center, const T &_spinRad = T(0))
        : center(_center)
        , normal1((_camera.position - _center).normalized())
        , normal2(Vec3<T>::cross(Vec3<T>::unitZ(), normal1).normalized())
        , normal3(Vec3<T>::cross(normal1, normal2).normalized())
    {
        if (!isNull(_spinRad))
        {
            const T sa = std::sin(_spinRad);
            const T ca = std::cos(_spinRad);
            normal2 = normal2.rotated(normal1, sa, ca);
            normal3 = normal3.rotated(normal1, sa, ca);
        }
    }

    /*!
     * \brief Returns a copy of this orientation, but moved to new center position
     * \param _newCenter New center position
     * \return Copy of this orientation, but moved to new center position
     */
    inline Orientation<T> moved(const Vec3<T> &_newCenter) const
    {
        Orientation<T> result = *this;
        result.center = _newCenter;
        return result;
    }

    /*!
     * \brief Invert all normals
     * \return This orientation object
     */
    inline Orientation<T> &invert()
    {
        normal1.invert();
        normal2.invert();
        normal3.invert();
        return *this;
    }

    /*!
     * \brief Invert major and secondary normal
     * \return This orientation object
     */
    inline Orientation<T> &invert12()
    {
        normal1.invert();
        normal2.invert();
        return *this;
    }

    /*!
     * \brief Create orientation with inverted major and secondary normal
     * \return Orientation object with invert major and secondary normal
     */
    inline Orientation<T> toInvert12() const
    {
        Orientation<T> result = *this;
        return result.invert12();
    }

    /*!
     * \brief Test unit orientation; center=(0,0,0), N1=(1,0,0), N2=(0,1,0), N3=(0,0,1)
     * \return \c true if this is an unit orientation
     */
    inline bool isUnit() const
    {
        return center.isNull() && normal1 == Vec3<T>::unitX() && normal2 == Vec3<T>::unitY() &&
            normal3 == Vec3<T>::unitZ();
    }

    /*!
     * \brief Test if this is a right-handed orientation
     * \return \c true for right-handed orientation
     */
    inline bool isRightHanded() const
    {
        return isPositive(Vec3<T>::dot(normal3, Vec3<T>::cross(normal1, normal2)));
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return mixHash(center.toHash(), normal1.toHash(), normal2.toHash(), normal3.toHash());
    }

    /*!
     * \brief Transform point
     * \param _origPos Origin point position
     * \return Transformed point
     */
    inline Vec3<T> getPoint(const Vec3<T> &_origPos) const
    {
        return center + normal1 * _origPos.x + normal2 * _origPos.y + normal3 * _origPos.z;
    }

    /*!
     * \brief Transform point
     * \param _origPos Origin point position
     * \param _scale Scale factor
     * \return Transformed point
     */
    inline Vec3<T> getPoint(const Vec3<T> &_origPos, const T _scale) const
    {
        return center + normal1 * (_origPos.x * _scale) + normal2 * (_origPos.y * _scale) +
            normal3 * (_origPos.z * _scale);
    }

    /*!
     * \brief Vertices for oriented rectangular shape
     * \param _radius1 Radius within the secondary normal
     * \param _radius2 Radius within the third normal
     * \return Rectangle vertices
     */
    inline std::array<Vec3<T>, 4> rectVertex(const float _radius1, const float _radius2) const
    {
        return {{center - normal2 * _radius1 + normal3 * _radius2,
                 center - normal2 * _radius1 - normal3 * _radius2,
                 center + normal2 * _radius1 - normal3 * _radius2,
                 center + normal2 * _radius1 + normal3 * _radius2}};
    }

    void transformPoints(Vec3<T> *_out,
                         const Vec3<T> *_orig,
                         const size_t _count,
                         const std::vector<std::pair<size_t, size_t>> &_pool) const;

    void transformPoints(Vec3<T> *_out,
                         const Vec3<T> *_orig,
                         const T _scale,
                         const size_t _count,
                         const std::vector<std::pair<size_t, size_t>> &_pool) const;

    void transformNormals(Vec3<T> *_out,
                          const Vec3<T> *_orig,
                          const size_t _count,
                          const std::vector<std::pair<size_t, size_t>> &_pool) const;

    static void
    repairPathNormals(Orientation<T> *_data, const size_t _count, const std::vector<std::pair<size_t, size_t>> &_pool);

    static void repairPathNormals(std::pair<Orientation<T>, ColorRGB> *_data,
                                  const size_t _count,
                                  const std::vector<std::pair<size_t, size_t>> &_pool);

    static Vec3<T>
    centerPoint(const Orientation<T> *_data, const size_t _count, const std::vector<std::pair<size_t, size_t>> &_pool);

    static Vec3<T> centerPoint(const std::pair<Orientation<T>, ColorRGB> *_data,
                               const size_t _count,
                               const std::vector<std::pair<size_t, size_t>> &_pool);

    static T
    pathLength(const Orientation<T> *_data, const size_t _count, const std::vector<std::pair<size_t, size_t>> &_pool);
    static T pathLength(const std::pair<Orientation<T>, ColorRGB> *_data,
                        const size_t _count,
                        const std::vector<std::pair<size_t, size_t>> &_pool);

    void createSpiralPath(std::vector<Orientation<T>> &_path,
                          Vec3<T> &_pathCenter,
                          T &_pathLength,
                          const bool _helicity,
                          const T _periodLength,
                          const T _spiralRadius,
                          const T _angleStart,
                          const T _angleEnd,
                          const size_t _quality) const;

    void createSpiralPath(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                          Vec3<T> &_pathCenter,
                          T &_pathLength,
                          const bool _helicity,
                          const T _periodLength,
                          const T _spiralRadius,
                          const T _angleStart,
                          const T _angleEnd,
                          const size_t _quality,
                          const ColorRGB &_colorStart,
                          const ColorRGB &_colorEnd) const;

    void createSpiralPathRainbow(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                 Vec3<T> &_pathCenter,
                                 T &_pathLength,
                                 const bool _helicity,
                                 const T _periodLength,
                                 const T _spiralRadius,
                                 const T _angleStart,
                                 const T _angleEnd,
                                 const size_t _quality) const;

    void createSpiralArcPath(std::vector<Orientation<T>> &_path,
                             Vec3<T> &_pathCenter,
                             T &_pathLength,
                             const bool _helicity,
                             const T _periodLength,
                             const T _armRadius,
                             const T _spiralRadius,
                             const T _angleStart,
                             const T _angleEnd,
                             const size_t _quality) const;

    void createSpiralArcPath(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                             Vec3<T> &_pathCenter,
                             T &_pathLength,
                             const bool _helicity,
                             const T _periodLength,
                             const T _armRadius,
                             const T _spiralRadius,
                             const T _angleStart,
                             const T _angleEnd,
                             const size_t _quality,
                             const ColorRGB &_colorStart,
                             const ColorRGB &_colorEnd) const;

    void createSpiralArcPathRainbow(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                    Vec3<T> &_pathCenter,
                                    T &_pathLength,
                                    const bool _helicity,
                                    const T _periodLength,
                                    const T _armRadius,
                                    const T _spiralRadius,
                                    const T _angleStart,
                                    const T _angleEnd,
                                    const size_t _quality) const;

    static void createBezierPath(std::vector<Orientation<T>> &_path,
                                 Vec3<T> &_pathCenter,
                                 T &_pathLength,
                                 const Vec3<T> &_1,
                                 const Vec3<T> &_2,
                                 const Vec3<T> &_3,
                                 const Vec3<T> &_4,
                                 const uint16_t _segments);

    static void createBezierPath(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                 Vec3<T> &_pathCenter,
                                 T &_pathLength,
                                 const Vec3<T> &_1,
                                 const Vec3<T> &_2,
                                 const Vec3<T> &_3,
                                 const Vec3<T> &_4,
                                 const uint16_t _segments,
                                 const ColorRGB &_color1,
                                 const ColorRGB &_color2);

    static void createBezierPathRainbow(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                        Vec3<T> &_pathCenter,
                                        T &_pathLength,
                                        const Vec3<T> &_1,
                                        const Vec3<T> &_2,
                                        const Vec3<T> &_3,
                                        const Vec3<T> &_4,
                                        const uint16_t _segments);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Transform point array
 * \tparam T Template floating point type
 * \param _out Output vertices
 * \param _orig Input origin vertices
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T>
void Orientation<T>::transformPoints(Vec3<T> *_out,
                                     const Vec3<T> *_orig,
                                     const size_t _count,
                                     const std::vector<std::pair<size_t, size_t>> &_pool) const
{
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _count; ++i)
            _out[i] = getPoint(_orig[i]);
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, this](Vec3<T> *__to, const Vec3<T> *__from) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __to[i] = getPoint(__from[i]);
                },
                _out,
                _orig));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Transform and scale point array
 * \tparam T Template floating point type
 * \param _out Output vertices
 * \param _orig Input origin vertices
 * \param _scale Scaling factor
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T>
void Orientation<T>::transformPoints(Vec3<T> *_out,
                                     const Vec3<T> *_orig,
                                     const T _scale,
                                     const size_t _count,
                                     const std::vector<std::pair<size_t, size_t>> &_pool) const
{
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _count; ++i)
            _out[i] = getPoint(_orig[i] * _scale);
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _scale, this](Vec3<T> *__to, const Vec3<T> *__from) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __to[i] = getPoint(__from[i] * _scale);
                },
                _out,
                _orig));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Transform normalized vector array
 * \tparam T Template floating point type
 * \param _out Output vertices
 * \param _orig Input origin normals
 * \param _count Number of items
 * \param _pool Multi-thread indices
 */
template <typename T>
void Orientation<T>::transformNormals(Vec3<T> *_out,
                                      const Vec3<T> *_orig,
                                      const size_t _count,
                                      const std::vector<std::pair<size_t, size_t>> &_pool) const
{
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _count; ++i)
            _out[i] = (normal1 * _orig[i].x + normal2 * _orig[i].y + normal3 * _orig[i].z).normalized();
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, this](Vec3<T> *__to, const Vec3<T> *__from) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __to[i] = (normal1 * __from[i].x + normal2 * __from[i].y + normal3 * __from[i].z).normalized();
                },
                _out,
                _orig));
        for (std::thread &t : threads)
            t.join();
    }
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Repair path normals based on current positions
 * \tparam T Template floating point type
 * \param _data Output vertex data
 * \param _count Number of vertices
 * \param _pool Multi-thread indices
 * \return
 */
template <typename T>
void Orientation<T>::repairPathNormals(Orientation<T> *_data,
                                       const size_t _count,
                                       const std::vector<std::pair<size_t, size_t>> &_pool)
{
    if (_count < 2UL)
        return;

    if (_count == 2UL)
    {
        _data[0].normal1 = (_data[1].center - _data[0].center).normalized();
        _data[0].normal2 = _data[0].normal1.perpendicularNormalUp();
        _data[0].normal3 = Vec3<T>::cross(_data[0].normal1, _data[0].normal2).normalized();
        _data[1].normal1 = _data[0].normal1;
        _data[1].normal2 = _data[0].normal2;
        _data[1].normal3 = _data[0].normal3;
        return;
    }

    _data[0].normal1 = (_data[1].center - _data[0].center).normalized();
    _data[0].normal2 = _data[0].normal1.perpendicularNormalUp();
    _data[0].normal3 = Vec3<T>::cross(_data[0].normal1, _data[0].normal2).normalized();

    const size_t lastInner = _count - 1UL;
    if (_pool.empty())
    {
        size_t i = 1UL;
        for (; i < lastInner; ++i)
        {
            _data[i].normal1 = ((_data[i].center - _data[i - 1UL].center).normalized() +
                                (_data[i + 1UL].center - _data[i].center).normalized())
                                   .normalized();

            _data[i].normal3 = Vec3<T>::cross(_data[i].normal1, _data[i - 1UL].normal2).normalized();
            _data[i].normal2 = Vec3<T>::cross(_data[i].normal3, _data[i].normal1).normalized();
        }

        _data[i].normal1 = (_data[i].center - _data[i - 1UL].center).normalized();
        _data[i].normal3 = Vec3<T>::cross(_data[i].normal1, _data[i - 1UL].normal2).normalized();
        _data[i].normal2 = Vec3<T>::cross(_data[i].normal3, _data[i].normal1).normalized();
        return;
    }

    std::vector<std::thread> threads;
    threads.reserve(_pool.size());

    for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
        threads.push_back(std::thread(
            [t, lastInner](Orientation<T> *__data) {
                const size_t end = t.first + t.second;
                for (size_t i = std::max(1UL, t.first); i < end; ++i)
                    if (i == lastInner)
                        __data[i].normal1 = (__data[i].center - __data[i - 1UL].center).normalized();
                    else
                        __data[i].normal1 = ((__data[i].center - __data[i - 1UL].center).normalized() +
                                             (__data[i + 1UL].center - __data[i].center).normalized())
                                                .normalized();
            },
            _data));

    for (std::thread &t : threads)
        t.join();

    for (size_t i = 1UL; i < _count; ++i)
    {
        _data[i].normal3 = Vec3<T>::cross(_data[i].normal1, _data[i - 1UL].normal2).normalized();
        _data[i].normal2 = Vec3<T>::cross(_data[i].normal3, _data[i].normal1).normalized();
    }
}

/*!
 * \brief Repair path normals based on current positions
 * \tparam T Template floating point type
 * \param _data Output vertex data
 * \param _count Number of vertices
 * \param _pool Multi-thread indices
 * \return
 */
template <typename T>
void Orientation<T>::repairPathNormals(std::pair<Orientation<T>, ColorRGB> *_data,
                                       const size_t _count,
                                       const std::vector<std::pair<size_t, size_t>> &_pool)
{
    if (_count < 2UL)
        return;

    if (_count == 2UL)
    {
        _data[0].first.normal1 = (_data[1].first.center - _data[0].first.center).normalized();
        _data[0].first.normal2 = _data[0].first.normal1.perpendicularNormalUp();
        _data[0].first.normal3 = Vec3<T>::cross(_data[0].first.normal1, _data[0].first.normal2).normalized();
        _data[1].first.normal1 = _data[0].first.normal1;
        _data[1].first.normal2 = _data[0].first.normal2;
        _data[1].first.normal3 = _data[0].first.normal3;
        return;
    }

    _data[0].first.normal1 = (_data[1].first.center - _data[0].first.center).normalized();
    _data[0].first.normal2 = _data[0].first.normal1.perpendicularNormalUp();
    _data[0].first.normal3 = Vec3<T>::cross(_data[0].first.normal1, _data[0].first.normal2).normalized();

    const size_t lastInner = _count - 1UL;
    if (_pool.empty())
    {
        size_t i = 1UL;
        for (; i < lastInner; ++i)
        {
            _data[i].first.normal1 = ((_data[i].first.center - _data[i - 1UL].first.center).normalized() +
                                      (_data[i + 1UL].first.center - _data[i].first.center).normalized())
                                         .normalized();

            _data[i].first.normal3 = Vec3<T>::cross(_data[i].first.normal1, _data[i - 1UL].first.normal2).normalized();
            _data[i].first.normal2 = Vec3<T>::cross(_data[i].first.normal3, _data[i].first.normal1).normalized();
        }

        _data[i].first.normal1 = (_data[i].first.center - _data[i - 1UL].first.center).normalized();
        _data[i].first.normal3 = Vec3<T>::cross(_data[i].first.normal1, _data[i - 1UL].first.normal2).normalized();
        _data[i].first.normal2 = Vec3<T>::cross(_data[i].first.normal3, _data[i].first.normal1).normalized();
        return;
    }

    std::vector<std::thread> threads;
    threads.reserve(_pool.size());

    for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
        threads.push_back(std::thread(
            [t, lastInner](std::pair<Orientation<T>, ColorRGB> *__data) {
                const size_t end = t.first + t.second;
                for (size_t i = std::max(1UL, t.first); i < end; ++i)
                    if (i == lastInner)
                        __data[i].first.normal1 = (__data[i].first.center - __data[i - 1UL].first.center).normalized();
                    else
                        __data[i].first.normal1 =
                            ((__data[i].first.center - __data[i - 1UL].first.center).normalized() +
                             (__data[i + 1UL].first.center - __data[i].first.center).normalized())
                                .normalized();
            },
            _data));

    for (std::thread &t : threads)
        t.join();

    for (size_t i = 1UL; i < _count; ++i)
    {
        _data[i].first.normal3 = Vec3<T>::cross(_data[i].first.normal1, _data[i - 1UL].first.normal2).normalized();
        _data[i].first.normal2 = Vec3<T>::cross(_data[i].first.normal3, _data[i].first.normal1).normalized();
    }
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculate central point
 * \tparam T Template floating point type
 * \param _data Vertex data
 * \param _count Number of vertices
 * \param _pool Multi-thread indices
 * \return Central point
 */
template <typename T>
Vec3<T> Orientation<T>::centerPoint(const Orientation<T> *_data,
                                    const size_t _count,
                                    const std::vector<std::pair<size_t, size_t>> &_pool)
{
    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _count; ++i)
            _data[i].center.updateRange(min, max);
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(_pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t](std::pair<Vec3<T>, Vec3<T>> &_minMax, const Orientation<T> *__data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __data[i].center.updateRange(_minMax.first, _minMax.second);
                },
                std::ref(tData[tt++]),
                _data));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    return (min + max) * 0.5f;
}

/*!
 * \brief Calculate central point
 * \tparam T Template floating point type
 * \param _data Vertex data
 * \param _count Number of vertices
 * \param _pool Multi-thread indices
 * \return Central point
 */
template <typename T>
Vec3<T> Orientation<T>::centerPoint(const std::pair<Orientation<T>, ColorRGB> *_data,
                                    const size_t _count,
                                    const std::vector<std::pair<size_t, size_t>> &_pool)
{
    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < _count; ++i)
            _data[i].first.center.updateRange(min, max);
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(_pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t](std::pair<Vec3<T>, Vec3<T>> &_minMax, const std::pair<Orientation<T>, ColorRGB> *__data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __data[i].first.center.updateRange(_minMax.first, _minMax.second);
                },
                std::ref(tData[tt++]),
                _data));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    return (min + max) * 0.5f;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculate path length
 * \tparam T Template floating point type
 * \param _data Vertex data
 * \param _count Number of vertices
 * \param _pool Multi-thread indices
 * \return Path length
 */
template <typename T>
T Orientation<T>::pathLength(const Orientation<T> *_data,
                             const size_t _count,
                             const std::vector<std::pair<size_t, size_t>> &_pool)
{
    T result = T(0);
    if (_pool.empty())
    {
        for (size_t i = 1UL; i < _count; ++i)
            result += _data[i - 1].center.distanceToPoint(_data[i].center);
    }
    else
    {
        uint tt = 0U;
        std::vector<T> tData(_pool.size(), T(0));
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t](T &_out, const Orientation<T> *__data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = std::max(t.first, 1UL); i < end; ++i)
                        _out += __data[i - 1].center.distanceToPoint(__data[i].center);
                },
                std::ref(tData[tt++]),
                _data));

        for (std::thread &t : threads)
            t.join();

        result = std::accumulate(tData.cbegin(), tData.cend(), T(0));
    }

    return result;
}

/*!
 * \brief Calculate central point
 * \tparam T Template floating point type
 * \param _data Vertex data
 * \param _count Number of vertices
 * \param _pool Multi-thread indices
 * \return Central point
 */
template <typename T>
T Orientation<T>::pathLength(const std::pair<Orientation<T>, ColorRGB> *_data,
                             const size_t _count,
                             const std::vector<std::pair<size_t, size_t>> &_pool)
{
    T result = T(0);
    if (_pool.empty())
    {
        for (size_t i = 1UL; i < _count; ++i)
            result += _data[i - 1].first.center.distanceToPoint(_data[i].first.center);
    }
    else
    {
        uint tt = 0U;
        std::vector<T> tData(_pool.size(), T(0));
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t](T &_out, const std::pair<Orientation<T>, ColorRGB> *__data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = std::max(t.first, 1UL); i < end; ++i)
                        _out += __data[i - 1].first.center.distanceToPoint(__data[i].first.center);
                },
                std::ref(tData[tt++]),
                _data));

        for (std::thread &t : threads)
            t.join();

        result = std::accumulate(tData.cbegin(), tData.cend(), T(0));
    }

    return result;
}

/*!
 * \brief Create spiral path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _helicity Helicity (\c true = right-positive helicity)
 * \param _periodLength Spiral period offset along major normal
 * \param _spiralRadius Spiral arc radius
 * \param _angleStart Spiral angle start in radians
 * \param _angleEnd Spiral angle end in radians
 * \param _quality Spiral arc quality
 */
template <typename T>
void Orientation<T>::createSpiralPath(std::vector<Orientation<T>> &_path,
                                      Vec3<T> &_pathCenter,
                                      T &_pathLength,
                                      const bool _helicity,
                                      const T _periodLength,
                                      const T _spiralRadius,
                                      const T _angleStart,
                                      const T _angleEnd,
                                      const size_t _quality) const
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    const T s = _helicity ? T(1) : T(-1);

    std::vector<T> angles;
    fillSteps<T>(angles, _angleStart, _angleEnd, angle);
    if (angles.size() < 2UL)
    {
        _path.clear();
        _pathCenter = center;
        _pathLength = T(0);
        return;
    }

    const T a0 = angles.front();
    const T aa = angles.back() - a0;
    const T lr = aa * _spiralRadius;
    const T ll = _periodLength * aa / _2PI;
    const T l0 = _periodLength * angles.front() / _2PI;
    const Vec3<T> N0 = (normal3 * (lr * s) + normal1 * ll).normalized();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(angles.size());

    _path.resize(angles.size());

    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (pool.empty())
    {
        for (size_t i = 0UL; i < angles.size(); ++i)
        {
            const T a = s * angles[i];
            const T sa = std::sin(a);
            const T ca = std::cos(a);
            const T lo = l0 + ll * (a - a0) / aa;
            const Vec3<T> N1 = N0.rotated(normal1, sa, ca).normalized();
            const Vec3<T> N2 = normal2.rotated(normal1, sa, ca).normalized();
            _path[i].center = center + normal1 * lo + N2 * _spiralRadius;
            _path[i].normal1 = N1;
            _path[i].normal2 = N2;
            _path[i].normal3 = Vec3<T>::cross(N1, N2).normalized();
            _path[i].center.updateRange(min, max);
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, s, a0, aa, l0, ll, N0, _spiralRadius, this](
                    std::pair<Vec3<T>, Vec3<T>> &_minMax, Orientation<T> *__path, const T *_angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T a = s * _angles[i];
                        const T sa = std::sin(a);
                        const T ca = std::cos(a);
                        const T lo = l0 + ll * (a - a0) / aa;
                        const Vec3<T> N1 = N0.rotated(normal1, sa, ca).normalized();
                        const Vec3<T> N2 = normal2.rotated(normal1, sa, ca).normalized();
                        __path[i].center = center + normal1 * lo + N2 * _spiralRadius;
                        __path[i].normal1 = N1;
                        __path[i].normal2 = N2;
                        __path[i].normal3 = Vec3<T>::cross(N1, N2).normalized();
                        __path[i].center.updateRange(_minMax.first, _minMax.second);
                    }
                },
                std::ref(tData[tt++]),
                _path.data(),
                angles.data()));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    _pathCenter = (min + max) * 0.5f;
    _pathLength = pathLength(_path.data(), angles.size(), pool);  // std::sqrt(ll * ll + lr * lr);
}

/*!
 * \brief Create spiral path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _helicity Helicity (\c true = right-positive helicity)
 * \param _periodLength Spiral period offset along major normal
 * \param _spiralRadius Spiral arc radius
 * \param _angleStart Spiral angle start in radians
 * \param _angleEnd Spiral angle end in radians
 * \param _quality Spiral arc quality
 * \param _colorStart Spiral color at start
 * \param _colorEnd Spiral color at end
 */
template <typename T>
void Orientation<T>::createSpiralPath(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                      Vec3<T> &_pathCenter,
                                      T &_pathLength,
                                      const bool _helicity,
                                      const T _periodLength,
                                      const T _spiralRadius,
                                      const T _angleStart,
                                      const T _angleEnd,
                                      const size_t _quality,
                                      const ColorRGB &_colorStart,
                                      const ColorRGB &_colorEnd) const
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    const T s = _helicity ? T(1) : T(-1);

    std::vector<T> angles;
    fillSteps<T>(angles, _angleStart, _angleEnd, angle);
    if (angles.size() < 2UL)
    {
        _path.clear();
        _pathCenter = center;
        _pathLength = T(0);
        return;
    }

    const T a0 = angles.front();
    const T aa = angles.back() - a0;
    const T lr = aa * _spiralRadius;
    const T ll = _periodLength * aa / _2PI;
    const T l0 = _periodLength * angles.front() / _2PI;
    const Vec3<T> N0 = (normal3 * (lr * s) + normal1 * ll).normalized();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(angles.size());

    _path.resize(angles.size());

    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (pool.empty())
    {
        for (size_t i = 0UL; i < angles.size(); ++i)
        {
            const T a = s * angles[i];
            const T sa = std::sin(a);
            const T ca = std::cos(a);
            const T r = (a - a0) / aa;
            const T lo = l0 + ll * r;
            const Vec3<T> N1 = N0.rotated(normal1, sa, ca).normalized();
            const Vec3<T> N2 = normal2.rotated(normal1, sa, ca).normalized();
            _path[i].second = ColorRGB::ratioNice(r, _colorStart, _colorEnd);
            _path[i].first.center = center + normal1 * lo + N2 * _spiralRadius;
            _path[i].first.normal1 = N1;
            _path[i].first.normal2 = N2;
            _path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
            _path[i].first.center.updateRange(min, max);
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, s, a0, aa, l0, ll, N0, _spiralRadius, _colorStart, _colorEnd, this](
                    std::pair<Vec3<T>, Vec3<T>> &_minMax,
                    std::pair<Orientation<T>, ColorRGB> *__path,
                    const T *_angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T a = s * _angles[i];
                        const T sa = std::sin(a);
                        const T ca = std::cos(a);
                        const T r = (a - a0) / aa;
                        const T lo = l0 + ll * r;
                        const Vec3<T> N1 = N0.rotated(normal1, sa, ca).normalized();
                        const Vec3<T> N2 = normal2.rotated(normal1, sa, ca).normalized();
                        __path[i].second = ColorRGB::ratioNice(r, _colorStart, _colorEnd);
                        __path[i].first.center = center + normal1 * lo + N2 * _spiralRadius;
                        __path[i].first.normal1 = N1;
                        __path[i].first.normal2 = N2;
                        __path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
                        __path[i].first.center.updateRange(_minMax.first, _minMax.second);
                    }
                },
                std::ref(tData[tt++]),
                _path.data(),
                angles.data()));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    _pathCenter = (min + max) * 0.5f;
    _pathLength = pathLength(_path.data(), angles.size(), pool);  // std::sqrt(ll * ll + lr * lr);
}

/*!
 * \brief Create spiral path - rainbow colors
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _helicity Helicity (\c true = right-positive helicity)
 * \param _periodLength Spiral period offset along major normal
 * \param _spiralRadius Spiral arc radius
 * \param _angleStart Spiral angle start in radians
 * \param _angleEnd Spiral angle end in radians
 * \param _quality Spiral arc quality
 */
template <typename T>
void Orientation<T>::createSpiralPathRainbow(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                             Vec3<T> &_pathCenter,
                                             T &_pathLength,
                                             const bool _helicity,
                                             const T _periodLength,
                                             const T _spiralRadius,
                                             const T _angleStart,
                                             const T _angleEnd,
                                             const size_t _quality) const
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    const T s = _helicity ? T(1) : T(-1);

    std::vector<T> angles;
    fillSteps<T>(angles, _angleStart, _angleEnd, angle);
    if (angles.size() < 2UL)
    {
        _path.clear();
        _pathCenter = center;
        _pathLength = T(0);
        return;
    }

    const T a0 = angles.front();
    const T aa = angles.back() - a0;
    const T lr = aa * _spiralRadius;
    const T ll = _periodLength * aa / _2PI;
    const T l0 = _periodLength * angles.front() / _2PI;
    const Vec3<T> N0 = (normal3 * (lr * s) + normal1 * ll).normalized();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(angles.size());

    _path.resize(angles.size());

    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (pool.empty())
    {
        for (size_t i = 0UL; i < angles.size(); ++i)
        {
            const T a = s * angles[i];
            const T sa = std::sin(a);
            const T ca = std::cos(a);
            const T r = (a - a0) / aa;
            const T lo = l0 + ll * r;
            const Vec3<T> N1 = N0.rotated(normal1, sa, ca).normalized();
            const Vec3<T> N2 = normal2.rotated(normal1, sa, ca).normalized();
            _path[i].second = ColorRGB::rainbow(r);
            _path[i].first.center = center + normal1 * lo + N2 * _spiralRadius;
            _path[i].first.normal1 = N1;
            _path[i].first.normal2 = N2;
            _path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
            _path[i].first.center.updateRange(min, max);
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, s, a0, aa, l0, ll, N0, _spiralRadius, this](std::pair<Vec3<T>, Vec3<T>> &_minMax,
                                                                std::pair<Orientation<T>, ColorRGB> *__path,
                                                                const T *_angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T a = s * _angles[i];
                        const T sa = std::sin(a);
                        const T ca = std::cos(a);
                        const T r = (a - a0) / aa;
                        const T lo = l0 + ll * r;
                        const Vec3<T> N1 = N0.rotated(normal1, sa, ca).normalized();
                        const Vec3<T> N2 = normal2.rotated(normal1, sa, ca).normalized();
                        __path[i].second = ColorRGB::rainbow(r);
                        __path[i].first.center = center + normal1 * lo + N2 * _spiralRadius;
                        __path[i].first.normal1 = N1;
                        __path[i].first.normal2 = N2;
                        __path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
                        __path[i].first.center.updateRange(_minMax.first, _minMax.second);
                    }
                },
                std::ref(tData[tt++]),
                _path.data(),
                angles.data()));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    _pathCenter = (min + max) * 0.5f;
    _pathLength = pathLength(_path.data(), angles.size(), pool);  // std::sqrt(ll * ll + lr * lr);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create spiral path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _helicity Helicity (\c true = right-positive helicity)
 * \param _periodLength Spiral period offset along major normal
 * \param _armRadius Spiral arm radius
 * \param _spiralRadius Spiral arc radius
 * \param _angleStart Spiral angle start in radians
 * \param _angleEnd Spiral angle end in radians
 * \param _quality Spiral arc quality
 */
template <typename T>
void Orientation<T>::createSpiralArcPath(std::vector<Orientation<T>> &_path,
                                         Vec3<T> &_pathCenter,
                                         T &_pathLength,
                                         const bool _helicity,
                                         const T _periodLength,
                                         const T _armRadius,
                                         const T _spiralRadius,
                                         const T _angleStart,
                                         const T _angleEnd,
                                         const size_t _quality) const
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    const T s = _helicity ? T(1) : T(-1);

    std::vector<T> angles;
    fillSteps<T>(angles, _angleStart, _angleEnd, angle);
    if (angles.size() < 2UL)
    {
        _path.clear();
        _pathCenter = center;
        _pathLength = T(0);
        return;
    }

    const T a0 = angles.front();
    const T aa = angles.back() - a0;
    const T lr = aa * _spiralRadius;
    const T ll = _periodLength * aa / _2PI;
    const T l0 = _periodLength * angles.front() / _2PI;
    const T aaa = ll / _armRadius;
    const T aa0 = l0 / _armRadius;
    const Vec3<T> N0 = (normal1 * (lr * s) + normal3 * ll).normalized();

    const std::vector<std::pair<size_t, size_t>> pool = createPool(angles.size());

    _path.resize(angles.size());

    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (pool.empty())
    {
        for (size_t i = 0UL; i < angles.size(); ++i)
        {
            const T a1 = s * angles[i];
            const T a2 = aa0 + aaa * (a1 - a0) / aa;
            const T sa1 = std::sin(a1);
            const T ca1 = std::cos(a1);
            const T sa2 = std::sin(a2);
            const T ca2 = std::cos(a2);
            const Vec3<T> N1 = N0.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N2 = normal2.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N3 = normal3.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N4 = N1.rotated(N3, sa1, ca1).normalized();
            const Vec3<T> N5 = N2.rotated(N3, sa1, ca1).normalized();

            _path[i].center = center + N2 * _armRadius + N5 * _spiralRadius;
            _path[i].center.updateRange(min, max);
            _path[i].normal1 = N4;
            _path[i].normal2 = N5;
            _path[i].normal3 = Vec3<T>::cross(N1, N2).normalized();
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, s, a0, aa, aa0, aaa, N0, _armRadius, _spiralRadius, this](
                    std::pair<Vec3<T>, Vec3<T>> &_minMax, Orientation<T> *__path, const T *_angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T a1 = s * _angles[i];
                        const T a2 = aa0 + aaa * (a1 - a0) / aa;
                        const T sa1 = std::sin(a1);
                        const T ca1 = std::cos(a1);
                        const T sa2 = std::sin(a2);
                        const T ca2 = std::cos(a2);
                        const Vec3<T> N1 = N0.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N2 = normal2.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N3 = normal3.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N4 = N1.rotated(N3, sa1, ca1).normalized();
                        const Vec3<T> N5 = N2.rotated(N3, sa1, ca1).normalized();

                        __path[i].center = center + N2 * _armRadius + N5 * _spiralRadius;
                        __path[i].center.updateRange(_minMax.first, _minMax.second);
                        __path[i].normal1 = N4;
                        __path[i].normal2 = N5;
                        __path[i].normal3 = Vec3<T>::cross(N1, N2).normalized();
                    }
                },
                std::ref(tData[tt++]),
                _path.data(),
                angles.data()));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    _pathCenter = (min + max) * 0.5f;
    _pathLength = pathLength(_path.data(), angles.size(), pool);  // std::sqrt(ll * ll + lr * lr);
}

/*!
 * \brief Create spiral path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _helicity Helicity (\c true = right-positive helicity)
 * \param _periodLength Spiral period offset along major normal
 * \param _armRadius Spiral arm radius
 * \param _spiralRadius Spiral arc radius
 * \param _angleStart Spiral angle start in radians
 * \param _angleEnd Spiral angle end in radians
 * \param _quality Spiral arc quality
 * \param _colorStart Spiral color at start
 * \param _colorEnd Spiral color at end
 */
template <typename T>
void Orientation<T>::createSpiralArcPath(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                         Vec3<T> &_pathCenter,
                                         T &_pathLength,
                                         const bool _helicity,
                                         const T _periodLength,
                                         const T _armRadius,
                                         const T _spiralRadius,
                                         const T _angleStart,
                                         const T _angleEnd,
                                         const size_t _quality,
                                         const ColorRGB &_colorStart,
                                         const ColorRGB &_colorEnd) const
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    const T s = _helicity ? T(1) : T(-1);

    std::vector<T> angles;
    fillSteps<T>(angles, _angleStart, _angleEnd, angle);
    if (angles.size() < 2UL)
    {
        _path.clear();
        _pathCenter = center;
        _pathLength = T(0);
        return;
    }

    const T a0 = angles.front();
    const T aa = angles.back() - a0;
    const T lr = aa * _spiralRadius;
    const T ll = _periodLength * aa / _2PI;
    const T l0 = _periodLength * angles.front() / _2PI;
    const T aaa = ll / _armRadius;
    const T aa0 = l0 / _armRadius;
    const Vec3<T> N0 = (normal1 * (lr * s) + normal3 * ll).normalized();

    const std::vector<std::pair<size_t, size_t>> pool = createPool(angles.size());

    _path.resize(angles.size());

    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (pool.empty())
    {
        for (size_t i = 0UL; i < angles.size(); ++i)
        {
            const T a1 = s * angles[i];
            const T r = (a1 - a0) / aa;
            const T a2 = aa0 + aaa * r;
            const T sa1 = std::sin(a1);
            const T ca1 = std::cos(a1);
            const T sa2 = std::sin(a2);
            const T ca2 = std::cos(a2);
            const Vec3<T> N1 = N0.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N2 = normal2.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N3 = normal3.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N4 = N1.rotated(N3, sa1, ca1).normalized();
            const Vec3<T> N5 = N2.rotated(N3, sa1, ca1).normalized();

            _path[i].second = ColorRGB::ratioNice(r, _colorStart, _colorEnd);
            _path[i].first.center = center + N2 * _armRadius + N5 * _spiralRadius;
            _path[i].first.center.updateRange(min, max);
            _path[i].first.normal1 = N4;
            _path[i].first.normal2 = N5;
            _path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, s, a0, aa, aa0, aaa, N0, _armRadius, _spiralRadius, _colorStart, _colorEnd, this](
                    std::pair<Vec3<T>, Vec3<T>> &_minMax,
                    std::pair<Orientation<T>, ColorRGB> *__path,
                    const T *_angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T a1 = s * _angles[i];
                        const T r = (a1 - a0) / aa;
                        const T a2 = aa0 + aaa * r;
                        const T sa1 = std::sin(a1);
                        const T ca1 = std::cos(a1);
                        const T sa2 = std::sin(a2);
                        const T ca2 = std::cos(a2);
                        const Vec3<T> N1 = N0.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N2 = normal2.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N3 = normal3.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N4 = N1.rotated(N3, sa1, ca1).normalized();
                        const Vec3<T> N5 = N2.rotated(N3, sa1, ca1).normalized();

                        __path[i].second = ColorRGB::ratioNice(r, _colorStart, _colorEnd);
                        __path[i].first.center = center + N2 * _armRadius + N5 * _spiralRadius;
                        __path[i].first.center.updateRange(_minMax.first, _minMax.second);
                        __path[i].first.normal1 = N4;
                        __path[i].first.normal2 = N5;
                        __path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
                    }
                },
                std::ref(tData[tt++]),
                _path.data(),
                angles.data()));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    _pathCenter = (min + max) * 0.5f;
    _pathLength = pathLength(_path.data(), angles.size(), pool);  // std::sqrt(ll * ll + lr * lr);
}

/*!
 * \brief Create spiral path - rainbow colors
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _helicity Helicity (\c true = right-positive helicity)
 * \param _periodLength Spiral period offset along major normal
 * \param _armRadius Spiral arm radius
 * \param _spiralRadius Spiral arc radius
 * \param _angleStart Spiral angle start in radians
 * \param _angleEnd Spiral angle end in radians
 * \param _quality Spiral arc quality
 */
template <typename T>
void Orientation<T>::createSpiralArcPathRainbow(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                                Vec3<T> &_pathCenter,
                                                T &_pathLength,
                                                const bool _helicity,
                                                const T _periodLength,
                                                const T _armRadius,
                                                const T _spiralRadius,
                                                const T _angleStart,
                                                const T _angleEnd,
                                                const size_t _quality) const
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    const T s = _helicity ? T(1) : T(-1);

    std::vector<T> angles;
    fillSteps<T>(angles, _angleStart, _angleEnd, angle);
    if (angles.size() < 2UL)
    {
        _path.clear();
        _pathCenter = center;
        _pathLength = T(0);
        return;
    }

    const T a0 = angles.front();
    const T aa = angles.back() - a0;
    const T lr = aa * _spiralRadius;
    const T ll = _periodLength * aa / _2PI;
    const T l0 = _periodLength * angles.front() / _2PI;
    const T aaa = ll / _armRadius;
    const T aa0 = l0 / _armRadius;
    const Vec3<T> N0 = (normal1 * (lr * s) + normal3 * ll).normalized();

    const std::vector<std::pair<size_t, size_t>> pool = createPool(angles.size());

    _path.resize(angles.size());

    Vec3<T> min = Vec3<T>::maximumValue(), max = Vec3<T>::lowestValue();
    if (pool.empty())
    {
        for (size_t i = 0UL; i < angles.size(); ++i)
        {
            const T a1 = s * angles[i];
            const T r = (a1 - a0) / aa;
            const T a2 = aa0 + aaa * r;
            const T sa1 = std::sin(a1);
            const T ca1 = std::cos(a1);
            const T sa2 = std::sin(a2);
            const T ca2 = std::cos(a2);
            const Vec3<T> N1 = N0.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N2 = normal2.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N3 = normal3.rotated(normal1, sa2, ca2).normalized();
            const Vec3<T> N4 = N1.rotated(N3, sa1, ca1).normalized();
            const Vec3<T> N5 = N2.rotated(N3, sa1, ca1).normalized();

            _path[i].second = ColorRGB::rainbow(r);
            _path[i].first.center = center + N2 * _armRadius + N5 * _spiralRadius;
            _path[i].first.center.updateRange(min, max);
            _path[i].first.normal1 = N4;
            _path[i].first.normal2 = N5;
            _path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
        }
    }
    else
    {
        uint tt = 0U;
        std::vector<std::pair<Vec3<T>, Vec3<T>>> tData(pool.size(), {min, max});
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, s, a0, aa, aa0, aaa, N0, _armRadius, _spiralRadius, this](
                    std::pair<Vec3<T>, Vec3<T>> &_minMax,
                    std::pair<Orientation<T>, ColorRGB> *__path,
                    const T *_angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T a1 = s * _angles[i];
                        const T r = (a1 - a0) / aa;
                        const T a2 = aa0 + aaa * r;
                        const T sa1 = std::sin(a1);
                        const T ca1 = std::cos(a1);
                        const T sa2 = std::sin(a2);
                        const T ca2 = std::cos(a2);
                        const Vec3<T> N1 = N0.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N2 = normal2.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N3 = normal3.rotated(normal1, sa2, ca2).normalized();
                        const Vec3<T> N4 = N1.rotated(N3, sa1, ca1).normalized();
                        const Vec3<T> N5 = N2.rotated(N3, sa1, ca1).normalized();

                        __path[i].second = ColorRGB::rainbow(r);
                        __path[i].first.center = center + N2 * _armRadius + N5 * _spiralRadius;
                        __path[i].first.center.updateRange(_minMax.first, _minMax.second);
                        __path[i].first.normal1 = N4;
                        __path[i].first.normal2 = N5;
                        __path[i].first.normal3 = Vec3<T>::cross(N1, N2).normalized();
                    }
                },
                std::ref(tData[tt++]),
                _path.data(),
                angles.data()));

        for (std::thread &t : threads)
            t.join();

        for (const std::pair<Vec3<T>, Vec3<T>> &t : tData)
            Vec3<T>::updateRange(min, max, t);
    }

    _pathCenter = (min + max) * 0.5f;
    _pathLength = pathLength(_path.data(), angles.size(), pool);  // std::sqrt(ll * ll + lr * lr);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create bezier path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _1 Bezier point 1
 * \param _2 Bezier point 2
 * \param _3 Bezier point 3
 * \param _4 Bezier point 4
 * \param _segments Segment count
 * \return
 */
template <typename T>
void Orientation<T>::createBezierPath(std::vector<Orientation<T>> &_path,
                                      Vec3<T> &_pathCenter,
                                      T &_pathLength,
                                      const Vec3<T> &_1,
                                      const Vec3<T> &_2,
                                      const Vec3<T> &_3,
                                      const Vec3<T> &_4,
                                      const uint16_t _segments)
{
    if (_segments == 0U)
        return;

    if (_segments == 1U)
    {
        _path.resize(2UL);

        _path.at(0).center = _1;
        _path.at(0).normal1 = (_4 - _1).normalized();
        _path.at(0).normal2 = _path.at(0).normal1.perpendicularNormalUp();
        _path.at(0).normal3 = Vec3<T>::cross(_path.at(0).normal1, _path.at(0).normal2).normalized();

        _path.at(1).center = _4;
        _path.at(1).normal1 = _path.at(0).normal1;
        _path.at(1).normal2 = _path.at(0).normal2;
        _path.at(1).normal3 = _path.at(0).normal3;

        return;
    }

    const T st = T(1) / T(_segments);
    const size_t np = _segments + 1UL;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(np);

    _path.resize(np);
    if (pool.empty())
    {
        for (size_t s = 0UL; s < np; ++s)
        {
            const T t = T(s) * st;
            const T tt = T(1) - t;
            _path[s].center =
                _1 * (tt * tt * tt) + _2 * (T(3) * tt * tt * t) + _3 * (T(3) * tt * t * t) + _4 * (t * t * t);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, st, _1, _2, _3, _4](Orientation<T> *__path) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T t = T(i) * st;
                        const T tt = T(1) - t;
                        __path[i].center = _1 * (tt * tt * tt) + _2 * (T(3) * tt * tt * t) + _3 * (T(3) * tt * t * t) +
                            _4 * (t * t * t);
                    }
                },
                _path.data()));

        for (std::thread &t : threads)
            t.join();
    }

    repairPathNormals(_path.data(), np, pool);
    _pathCenter = centerPoint(_path.data(), np, pool);
    _pathLength = pathLength(_path.data(), np, pool);
}

/*!
 * \brief Create bezier path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _1 Bezier point 1
 * \param _2 Bezier point 2
 * \param _3 Bezier point 3
 * \param _4 Bezier point 4
 * \param _segments Segment count
 * \param _color1 Color point 1
 * \param _color2 Color point 2
 * \return
 */
template <typename T>
void Orientation<T>::createBezierPath(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                      Vec3<T> &_pathCenter,
                                      T &_pathLength,
                                      const Vec3<T> &_1,
                                      const Vec3<T> &_2,
                                      const Vec3<T> &_3,
                                      const Vec3<T> &_4,
                                      const uint16_t _segments,
                                      const ColorRGB &_color1,
                                      const ColorRGB &_color2)
{
    if (_segments == 0U)
        return;

    if (_segments == 1U)
    {
        _path.resize(2UL);

        _path.at(0).first.center = _1;
        _path.at(0).first.normal1 = (_4 - _1).normalized();
        _path.at(0).first.normal2 = _path.at(0).first.normal1.perpendicularNormalUp();
        _path.at(0).first.normal3 = Vec3<T>::cross(_path.at(0).first.normal1, _path.at(0).first.normal2).normalized();
        _path.at(0).second = _color1;

        _path.at(1).first.center = _4;
        _path.at(1).first.normal1 = _path.at(0).first.normal1;
        _path.at(1).first.normal2 = _path.at(0).first.normal2;
        _path.at(1).first.normal3 = _path.at(0).first.normal3;
        _path.at(1).second = _color2;

        return;
    }

    const T st = T(1) / T(_segments);
    const size_t np = _segments + 1UL;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(np);

    _path.resize(np);
    if (pool.empty())
    {
        for (size_t s = 0UL; s < np; ++s)
        {
            const T t = T(s) * st;
            const T tt = T(1) - t;
            _path[s].first.center =
                _1 * (tt * tt * tt) + _2 * (T(3) * tt * tt * t) + _3 * (T(3) * tt * t * t) + _4 * (t * t * t);
            _path[s].second = ColorRGB::ratioNice(t, _color1, _color2);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, st, _1, _2, _3, _4, _color1, _color2](std::pair<Orientation<T>, ColorRGB> *__path) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T t = T(i) * st;
                        const T tt = T(1) - t;
                        __path[i].first.center = _1 * (tt * tt * tt) + _2 * (T(3) * tt * tt * t) +
                            _3 * (T(3) * tt * t * t) + _4 * (t * t * t);
                        __path[i].second = ColorRGB::ratioNice(t, _color1, _color2);
                    }
                },
                _path.data()));

        for (std::thread &t : threads)
            t.join();
    }

    repairPathNormals(_path.data(), np, pool);
    _pathCenter = centerPoint(_path.data(), np, pool);
    _pathLength = pathLength(_path.data(), np, pool);
}

/*!
 * \brief Create bezier path
 * \param _path Output path
 * \param _pathCenter Output center point
 * \param _pathLength Output path length
 * \param _1 Bezier point 1
 * \param _2 Bezier point 2
 * \param _3 Bezier point 3
 * \param _4 Bezier point 4
 * \param _segments Segment count
 * \return
 */
template <typename T>
void Orientation<T>::createBezierPathRainbow(std::vector<std::pair<Orientation<T>, ColorRGB>> &_path,
                                             Vec3<T> &_pathCenter,
                                             T &_pathLength,
                                             const Vec3<T> &_1,
                                             const Vec3<T> &_2,
                                             const Vec3<T> &_3,
                                             const Vec3<T> &_4,
                                             const uint16_t _segments)
{
    if (_segments == 0U)
        return;

    if (_segments == 1U)
    {
        _path.resize(2UL);

        _path.at(0).first.center = _1;
        _path.at(0).first.normal1 = (_4 - _1).normalized();
        _path.at(0).first.normal2 = _path.at(0).first.normal1.perpendicularNormalUp();
        _path.at(0).first.normal3 = Vec3<T>::cross(_path.at(0).first.normal1, _path.at(0).first.normal2).normalized();
        _path.at(0).second = ColorRGB::rainbow(0.0f);

        _path.at(1).first.center = _4;
        _path.at(1).first.normal1 = _path.at(0).first.normal1;
        _path.at(1).first.normal2 = _path.at(0).first.normal2;
        _path.at(1).first.normal3 = _path.at(0).first.normal3;
        _path.at(1).second = ColorRGB::rainbow(1.0f);

        return;
    }

    const T st = T(1) / T(_segments);
    const size_t np = _segments + 1UL;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(np);

    _path.resize(np);
    if (pool.empty())
    {
        for (size_t s = 0UL; s < np; ++s)
        {
            const T t = T(s) * st;
            const T tt = T(1) - t;
            _path[s].first.center =
                _1 * (tt * tt * tt) + _2 * (T(3) * tt * tt * t) + _3 * (T(3) * tt * t * t) + _4 * (t * t * t);
            _path[s].second = ColorRGB::rainbow(t);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, st, _1, _2, _3, _4](std::pair<Orientation<T>, ColorRGB> *__path) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T t = T(i) * st;
                        const T tt = T(1) - t;
                        __path[i].first.center = _1 * (tt * tt * tt) + _2 * (T(3) * tt * tt * t) +
                            _3 * (T(3) * tt * t * t) + _4 * (t * t * t);
                        __path[i].second = ColorRGB::rainbow(t);
                    }
                },
                _path.data()));

        for (std::thread &t : threads)
            t.join();
    }

    repairPathNormals(_path.data(), np, pool);
    _pathCenter = centerPoint(_path.data(), np, pool);
    _pathLength = pathLength(_path.data(), np, pool);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _v Orientation
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Orientation<T> &_v)
{
    return _os << '[' << _v.center << _v.normal1 << _v.normal2 << _v.normal3 << ']';
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Orientation<float> OrientF;        //!< 32 bit floating point precision 3D orientation
typedef Orientation<double> OrientD;       //!< 64 bit floating point precision 3D orientation
typedef Orientation<long double> OrientL;  //!< 128 bit floating point precision 3D orientation

}  // namespace Math
}  // namespace U1

#endif  // MATH_ORIENTATION3D_H
