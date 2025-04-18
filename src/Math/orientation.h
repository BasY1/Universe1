/*!
 * \file src/Math/orientation.h
 * \brief 3D Orientation structure
 */

#ifndef MATH_ORIENTATION3D_H
#define MATH_ORIENTATION3D_H

#include "camera.h"

#include <thread>

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
        return Math::mixHash(center.toHash(), normal1.toHash(), normal2.toHash(), normal3.toHash());
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

typedef Orientation<float> OrientF;        //!< 32 bit floating point precision 3D orientation
typedef Orientation<double> OrientD;       //!< 64 bit floating point precision 3D orientation
typedef Orientation<long double> OrientL;  //!< 128 bit floating point precision 3D orientation

}  // namespace Math
}  // namespace U1

#endif  // MATH_ORIENTATION3D_H
