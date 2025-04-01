/*!
 * \file src/Math/cylinder.h
 * \brief Cylinder geometry tools
 */

#ifndef MATH_CYLINDER_H
#define MATH_CYLINDER_H

#include "circle.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D Cylinder structure
 * \tparam T Template floating point type
 */
template <typename T>
struct Cylinder
{
    /*!
     * \brief Cylinder vertex count by circle quality
     * \param _quality Circle quality
     * \return Cylinder vertex count
     * \sa circlePointCount(const size_t)
     */
    inline static size_t cylinderVertexCount(const size_t _quality)
    {
        return 2UL * circlePointCount(_quality) + 2UL;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  const Orientation<T> &_orientation,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  const Orientation<T> &_orientation,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  T *_outAlpha,
                                  const Orientation<T> &_orientation,
                                  const T _alpha1,
                                  const T _alpha2,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  T *_outAlpha,
                                  const Orientation<T> &_orientation,
                                  const T _alpha1,
                                  const T _alpha2,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         T *_outAlpha,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _alpha1,
                                         const T _alpha2,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         T *_outAlpha,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _alpha1,
                                         const T _alpha2,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  const Orientation<T> &_orientation,
                                  const Vec3<T> &_ambient1,
                                  const Vec3<T> &_ambient2,
                                  const Vec3<T> &_diffuse1,
                                  const Vec3<T> &_diffuse2,
                                  const Vec3<T> &_specular1,
                                  const Vec3<T> &_specular2,
                                  const T _shine1,
                                  const T _shine2,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  const Orientation<T> &_orientation,
                                  const Vec3<T> &_ambient1,
                                  const Vec3<T> &_ambient2,
                                  const Vec3<T> &_diffuse1,
                                  const Vec3<T> &_diffuse2,
                                  const Vec3<T> &_specular1,
                                  const Vec3<T> &_specular2,
                                  const T _shine1,
                                  const T _shine2,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const Vec3<T> &_ambient1,
                                         const Vec3<T> &_ambient2,
                                         const Vec3<T> &_diffuse1,
                                         const Vec3<T> &_diffuse2,
                                         const Vec3<T> &_specular1,
                                         const Vec3<T> &_specular2,
                                         const T _shine1,
                                         const T _shine2,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const Vec3<T> &_ambient1,
                                         const Vec3<T> &_ambient2,
                                         const Vec3<T> &_diffuse1,
                                         const Vec3<T> &_diffuse2,
                                         const Vec3<T> &_specular1,
                                         const Vec3<T> &_specular2,
                                         const T _shine1,
                                         const T _shine2,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  T *_outAlpha,
                                  const Orientation<T> &_orientation,
                                  const Vec3<T> &_ambient1,
                                  const Vec3<T> &_ambient2,
                                  const Vec3<T> &_diffuse1,
                                  const Vec3<T> &_diffuse2,
                                  const Vec3<T> &_specular1,
                                  const Vec3<T> &_specular2,
                                  const T _shine1,
                                  const T _shine2,
                                  const T _alpha1,
                                  const T _alpha2,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  T *_outAlpha,
                                  const Orientation<T> &_orientation,
                                  const Vec3<T> &_ambient1,
                                  const Vec3<T> &_ambient2,
                                  const Vec3<T> &_diffuse1,
                                  const Vec3<T> &_diffuse2,
                                  const Vec3<T> &_specular1,
                                  const Vec3<T> &_specular2,
                                  const T _shine1,
                                  const T _shine2,
                                  const T _alpha1,
                                  const T _alpha2,
                                  const T _length,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         T *_outAlpha,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const Vec3<T> &_ambient1,
                                         const Vec3<T> &_ambient2,
                                         const Vec3<T> &_diffuse1,
                                         const Vec3<T> &_diffuse2,
                                         const Vec3<T> &_specular1,
                                         const Vec3<T> &_specular2,
                                         const T _shine1,
                                         const T _shine2,
                                         const T _alpha1,
                                         const T _alpha2,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         T *_outAlpha,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const Vec3<T> &_ambient1,
                                         const Vec3<T> &_ambient2,
                                         const Vec3<T> &_diffuse1,
                                         const Vec3<T> &_diffuse2,
                                         const Vec3<T> &_specular1,
                                         const Vec3<T> &_specular2,
                                         const T _shine1,
                                         const T _shine2,
                                         const T _alpha1,
                                         const T _alpha2,
                                         const T _length,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    const Orientation<T> &_orientation,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j2] = _orientation.center + N * _radius1;
                _outVertex[j1] = _outVertex[j2] + _orientation.normal1 * _length;

                _outNormal[j1] = N;
                _outNormal[j2] = N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _length](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j2] = _orientation.center + N * _radius1;
                            __outVertex[j1] = __outVertex[j2] + _orientation.normal1 * _length;

                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P2;
                _outVertex[j2] = _orientation.center + P1;
                _outNormal[j1] = N;
                _outNormal[j2] = N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _radius2, _length](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P2;
                            __outVertex[j2] = _orientation.center + P1;
                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    _outVertex[data2D.size() * 2UL] = _outVertex[0UL];
    _outVertex[data2D.size() * 2UL + 1UL] = _outVertex[1UL];

    _outNormal[data2D.size() * 2UL] = _outNormal[0UL];
    _outNormal[data2D.size() * 2UL + 1UL] = _outNormal[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    const Orientation<T> &_orientation,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + N * _radius1;
                _outVertex[j2] = _outVertex[j1] + _orientation.normal1 * _length;

                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _length](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + N * _radius1;
                            __outVertex[j2] = __outVertex[j1] + _orientation.normal1 * _length;

                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P1;
                _outVertex[j2] = _orientation.center + P2;
                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _radius2, _length](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P1;
                            __outVertex[j2] = _orientation.center + P2;
                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    _outVertex[data2D.size() * 2UL] = _outVertex[0UL];
    _outVertex[data2D.size() * 2UL + 1UL] = _outVertex[1UL];

    _outNormal[data2D.size() * 2UL] = _outNormal[0UL];
    _outNormal[data2D.size() * 2UL + 1UL] = _outNormal[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderOuter(
        _outVertex, _outNormal, Orientation<T>(_center, _normal, _arm), _length, _radius1, _radius2, _quality);
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderInner(
        _outVertex, _outNormal, Orientation<T>(_center, _normal, _arm), _length, _radius1, _radius2, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    T *_outAlpha,
                                    const Orientation<T> &_orientation,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j2] = _orientation.center + N * _radius1;
                _outVertex[j1] = _outVertex[j2] + _orientation.normal1 * _length;

                _outNormal[j1] = N;
                _outNormal[j2] = N;

                _outAlpha[j1] = _alpha2;
                _outAlpha[j2] = _alpha1;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _length, _alpha1, _alpha2](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, T *__outAlpha, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j2] = _orientation.center + N * _radius1;
                            __outVertex[j1] = __outVertex[j2] + _orientation.normal1 * _length;

                            __outNormal[j1] = N;
                            __outNormal[j2] = N;

                            __outAlpha[j1] = _alpha2;
                            __outAlpha[j2] = _alpha1;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P2;
                _outVertex[j2] = _orientation.center + P1;
                _outNormal[j1] = N;
                _outNormal[j2] = N;
                _outAlpha[j1] = _alpha2;
                _outAlpha[j2] = _alpha1;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _radius2, _length, _alpha1, _alpha2](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, T *__outAlpha, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P2;
                            __outVertex[j2] = _orientation.center + P1;
                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                            __outAlpha[j1] = _alpha2;
                            __outAlpha[j2] = _alpha1;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    _outVertex[data2D.size() * 2UL] = _outVertex[0UL];
    _outVertex[data2D.size() * 2UL + 1UL] = _outVertex[1UL];

    _outNormal[data2D.size() * 2UL] = _outNormal[0UL];
    _outNormal[data2D.size() * 2UL + 1UL] = _outNormal[1UL];

    _outAlpha[data2D.size() * 2UL] = _outAlpha[0UL];
    _outAlpha[data2D.size() * 2UL + 1UL] = _outAlpha[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    T *_outAlpha,
                                    const Orientation<T> &_orientation,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + N * _radius1;
                _outVertex[j2] = _outVertex[j1] + _orientation.normal1 * _length;

                _outNormal[j1] = -N;
                _outNormal[j2] = -N;

                _outAlpha[j1] = _alpha1;
                _outAlpha[j2] = _alpha2;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _length, _alpha1, _alpha2](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, T *__outAlpha, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + N * _radius1;
                            __outVertex[j2] = __outVertex[j1] + _orientation.normal1 * _length;

                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;

                            __outAlpha[j1] = _alpha1;
                            __outAlpha[j2] = _alpha2;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P1;
                _outVertex[j2] = _orientation.center + P2;
                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
                _outAlpha[j1] = _alpha1;
                _outAlpha[j2] = _alpha2;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, _orientation, _radius1, _radius2, _length, _alpha1, _alpha2](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, T *__outAlpha, const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P1;
                            __outVertex[j2] = _orientation.center + P2;
                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                            __outAlpha[j1] = _alpha1;
                            __outAlpha[j2] = _alpha2;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    _outVertex[data2D.size() * 2UL] = _outVertex[0UL];
    _outVertex[data2D.size() * 2UL + 1UL] = _outVertex[1UL];

    _outNormal[data2D.size() * 2UL] = _outNormal[0UL];
    _outNormal[data2D.size() * 2UL + 1UL] = _outNormal[1UL];

    _outAlpha[data2D.size() * 2UL] = _outAlpha[0UL];
    _outAlpha[data2D.size() * 2UL + 1UL] = _outAlpha[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    T *_outAlpha,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outAlpha,
                      Orientation<T>(_center, _normal, _arm),
                      _alpha1,
                      _alpha2,
                      _length,
                      _radius1,
                      _radius2,
                      _quality);
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    T *_outAlpha,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outAlpha,
                      Orientation<T>(_center, _normal, _arm),
                      _alpha1,
                      _alpha2,
                      _length,
                      _radius1,
                      _radius2,
                      _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    const Orientation<T> &_orientation,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j2] = _orientation.center + N * _radius1;
                _outVertex[j1] = _outVertex[j2] + _orientation.normal1 * _length;
                _outNormal[j1] = N;
                _outNormal[j2] = N;
                _outAmbient[j1] = _ambient2;
                _outAmbient[j2] = _ambient1;
                _outDiffuse[j1] = _diffuse2;
                _outDiffuse[j2] = _diffuse1;
                _outSpecular[j1] = _specular2;
                _outSpecular[j2] = _specular1;
                _outShine[j1] = _shine2;
                _outShine[j2] = _shine1;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j2] = _orientation.center + N * _radius1;
                            __outVertex[j1] = __outVertex[j2] + _orientation.normal1 * _length;
                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                            __outAmbient[j1] = _ambient2;
                            __outAmbient[j2] = _ambient1;
                            __outDiffuse[j1] = _diffuse2;
                            __outDiffuse[j2] = _diffuse1;
                            __outSpecular[j1] = _specular2;
                            __outSpecular[j2] = _specular1;
                            __outShine[j1] = _shine2;
                            __outShine[j2] = _shine1;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P2;
                _outVertex[j2] = _orientation.center + P1;
                _outNormal[j1] = N;
                _outNormal[j2] = N;
                _outAmbient[j1] = _ambient2;
                _outAmbient[j2] = _ambient1;
                _outDiffuse[j1] = _diffuse2;
                _outDiffuse[j2] = _diffuse1;
                _outSpecular[j1] = _specular2;
                _outSpecular[j2] = _specular1;
                _outShine[j1] = _shine2;
                _outShine[j2] = _shine1;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _radius2,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P2;
                            __outVertex[j2] = _orientation.center + P1;
                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                            __outAmbient[j1] = _ambient2;
                            __outAmbient[j2] = _ambient1;
                            __outDiffuse[j1] = _diffuse2;
                            __outDiffuse[j2] = _diffuse1;
                            __outSpecular[j1] = _specular2;
                            __outSpecular[j2] = _specular1;
                            __outShine[j1] = _shine2;
                            __outShine[j2] = _shine1;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const size_t last0 = data2D.size() * 2UL, last1 = last0 + 1UL;
    _outVertex[last0] = _outVertex[0UL];
    _outVertex[last1] = _outVertex[1UL];

    _outNormal[last0] = _outNormal[0UL];
    _outNormal[last1] = _outNormal[1UL];

    _outAmbient[last0] = _outAmbient[0UL];
    _outAmbient[last1] = _outAmbient[1UL];

    _outDiffuse[last0] = _outDiffuse[0UL];
    _outDiffuse[last1] = _outDiffuse[1UL];

    _outSpecular[last0] = _outSpecular[0UL];
    _outSpecular[last1] = _outSpecular[1UL];

    _outShine[last0] = _outShine[0UL];
    _outShine[last1] = _outShine[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    const Orientation<T> &_orientation,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + N * _radius1;
                _outVertex[j2] = _outVertex[j1] + _orientation.normal1 * _length;
                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
                _outAmbient[j1] = _ambient1;
                _outAmbient[j2] = _ambient2;
                _outDiffuse[j1] = _diffuse1;
                _outDiffuse[j2] = _diffuse2;
                _outSpecular[j1] = _specular1;
                _outSpecular[j2] = _specular2;
                _outShine[j1] = _shine1;
                _outShine[j2] = _shine2;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + N * _radius1;
                            __outVertex[j2] = __outVertex[j1] + _orientation.normal1 * _length;
                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                            __outAmbient[j1] = _ambient1;
                            __outAmbient[j2] = _ambient2;
                            __outDiffuse[j1] = _diffuse1;
                            __outDiffuse[j2] = _diffuse2;
                            __outSpecular[j1] = _specular1;
                            __outSpecular[j2] = _specular2;
                            __outShine[j1] = _shine1;
                            __outShine[j2] = _shine2;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P1;
                _outVertex[j2] = _orientation.center + P2;
                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
                _outAmbient[j1] = _ambient1;
                _outAmbient[j2] = _ambient2;
                _outDiffuse[j1] = _diffuse1;
                _outDiffuse[j2] = _diffuse2;
                _outSpecular[j1] = _specular1;
                _outSpecular[j2] = _specular2;
                _outShine[j1] = _shine1;
                _outShine[j2] = _shine2;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _radius2,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P1;
                            __outVertex[j2] = _orientation.center + P2;
                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                            __outAmbient[j1] = _ambient1;
                            __outAmbient[j2] = _ambient2;
                            __outDiffuse[j1] = _diffuse1;
                            __outDiffuse[j2] = _diffuse2;
                            __outSpecular[j1] = _specular1;
                            __outSpecular[j2] = _specular2;
                            __outShine[j1] = _shine1;
                            __outShine[j2] = _shine2;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const size_t last0 = data2D.size() * 2UL, last1 = last0 + 1UL;
    _outVertex[last0] = _outVertex[0UL];
    _outVertex[last1] = _outVertex[1UL];

    _outNormal[last0] = _outNormal[0UL];
    _outNormal[last1] = _outNormal[1UL];

    _outAmbient[last0] = _outAmbient[0UL];
    _outAmbient[last1] = _outAmbient[1UL];

    _outDiffuse[last0] = _outDiffuse[0UL];
    _outDiffuse[last1] = _outDiffuse[1UL];

    _outSpecular[last0] = _outSpecular[0UL];
    _outSpecular[last1] = _outSpecular[1UL];

    _outShine[last0] = _outShine[0UL];
    _outShine[last1] = _outShine[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      Orientation<T>(_center, _normal, _arm),
                      _ambient1,
                      _ambient2,
                      _diffuse1,
                      _diffuse2,
                      _specular1,
                      _specular2,
                      _shine1,
                      _shine2,
                      _length,
                      _radius1,
                      _radius2,
                      _quality);
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      Orientation<T>(_center, _normal, _arm),
                      _ambient1,
                      _ambient2,
                      _diffuse1,
                      _diffuse2,
                      _specular1,
                      _specular2,
                      _shine1,
                      _shine2,
                      _length,
                      _radius1,
                      _radius2,
                      _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    T *_outAlpha,
                                    const Orientation<T> &_orientation,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j2] = _orientation.center + N * _radius1;
                _outVertex[j1] = _outVertex[j2] + _orientation.normal1 * _length;
                _outNormal[j1] = N;
                _outNormal[j2] = N;
                _outAmbient[j1] = _ambient2;
                _outAmbient[j2] = _ambient1;
                _outDiffuse[j1] = _diffuse2;
                _outDiffuse[j2] = _diffuse1;
                _outSpecular[j1] = _specular2;
                _outSpecular[j2] = _specular1;
                _outShine[j1] = _shine2;
                _outShine[j2] = _shine1;
                _outAlpha[j1] = _alpha2;
                _outAlpha[j2] = _alpha1;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2,
                     _alpha1,
                     _alpha2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j2] = _orientation.center + N * _radius1;
                            __outVertex[j1] = __outVertex[j2] + _orientation.normal1 * _length;
                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                            __outAmbient[j1] = _ambient2;
                            __outAmbient[j2] = _ambient1;
                            __outDiffuse[j1] = _diffuse2;
                            __outDiffuse[j2] = _diffuse1;
                            __outSpecular[j1] = _specular2;
                            __outSpecular[j2] = _specular1;
                            __outShine[j1] = _shine2;
                            __outShine[j2] = _shine1;
                            __outAlpha[j1] = _alpha2;
                            __outAlpha[j2] = _alpha1;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P2;
                _outVertex[j2] = _orientation.center + P1;
                _outNormal[j1] = N;
                _outNormal[j2] = N;
                _outAmbient[j1] = _ambient2;
                _outAmbient[j2] = _ambient1;
                _outDiffuse[j1] = _diffuse2;
                _outDiffuse[j2] = _diffuse1;
                _outSpecular[j1] = _specular2;
                _outSpecular[j2] = _specular1;
                _outShine[j1] = _shine2;
                _outShine[j2] = _shine1;
                _outAlpha[j1] = _alpha2;
                _outAlpha[j2] = _alpha1;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _radius2,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2,
                     _alpha1,
                     _alpha2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P2;
                            __outVertex[j2] = _orientation.center + P1;
                            __outNormal[j1] = N;
                            __outNormal[j2] = N;
                            __outAmbient[j1] = _ambient2;
                            __outAmbient[j2] = _ambient1;
                            __outDiffuse[j1] = _diffuse2;
                            __outDiffuse[j2] = _diffuse1;
                            __outSpecular[j1] = _specular2;
                            __outSpecular[j2] = _specular1;
                            __outShine[j1] = _shine2;
                            __outShine[j2] = _shine1;
                            __outAlpha[j1] = _alpha2;
                            __outAlpha[j2] = _alpha1;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const size_t last0 = data2D.size() * 2UL, last1 = last0 + 1UL;
    _outVertex[last0] = _outVertex[0UL];
    _outVertex[last1] = _outVertex[1UL];

    _outNormal[last0] = _outNormal[0UL];
    _outNormal[last1] = _outNormal[1UL];

    _outAmbient[last0] = _outAmbient[0UL];
    _outAmbient[last1] = _outAmbient[1UL];

    _outDiffuse[last0] = _outDiffuse[0UL];
    _outDiffuse[last1] = _outDiffuse[1UL];

    _outSpecular[last0] = _outSpecular[0UL];
    _outSpecular[last1] = _outSpecular[1UL];

    _outShine[last0] = _outShine[0UL];
    _outShine[last1] = _outShine[1UL];

    _outAlpha[last0] = _outAlpha[0UL];
    _outAlpha[last1] = _outAlpha[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    T *_outAlpha,
                                    const Orientation<T> &_orientation,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + N * _radius1;
                _outVertex[j2] = _outVertex[j1] + _orientation.normal1 * _length;
                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
                _outAmbient[j1] = _ambient1;
                _outAmbient[j2] = _ambient2;
                _outDiffuse[j1] = _diffuse1;
                _outDiffuse[j2] = _diffuse2;
                _outSpecular[j1] = _specular1;
                _outSpecular[j2] = _specular2;
                _outShine[j1] = _shine1;
                _outShine[j2] = _shine2;
                _outAlpha[j1] = _alpha1;
                _outAlpha[j2] = _alpha2;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2,
                     _alpha1,
                     _alpha2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + N * _radius1;
                            __outVertex[j2] = __outVertex[j1] + _orientation.normal1 * _length;
                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                            __outAmbient[j1] = _ambient1;
                            __outAmbient[j2] = _ambient2;
                            __outDiffuse[j1] = _diffuse1;
                            __outDiffuse[j2] = _diffuse2;
                            __outSpecular[j1] = _specular1;
                            __outSpecular[j2] = _specular2;
                            __outShine[j1] = _shine1;
                            __outShine[j2] = _shine2;
                            __outAlpha[j1] = _alpha1;
                            __outAlpha[j2] = _alpha2;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const Vec2<T> &p2d = data2D[i];
                const Vec3<T> N1 = (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                const Vec3<T> P1 = N1 * _radius1;
                const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                const Math::Vec3F N2 = (P2 - P1).normalized();
                const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                const size_t j1 = i * 2UL;
                const size_t j2 = j1 + 1UL;
                _outVertex[j1] = _orientation.center + P1;
                _outVertex[j2] = _orientation.center + P2;
                _outNormal[j1] = -N;
                _outNormal[j2] = -N;
                _outAmbient[j1] = _ambient1;
                _outAmbient[j2] = _ambient2;
                _outDiffuse[j1] = _diffuse1;
                _outDiffuse[j2] = _diffuse2;
                _outSpecular[j1] = _specular1;
                _outSpecular[j2] = _specular2;
                _outShine[j1] = _shine1;
                _outShine[j2] = _shine2;
                _outAlpha[j1] = _alpha1;
                _outAlpha[j2] = _alpha2;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     _orientation,
                     _radius1,
                     _radius2,
                     _length,
                     _ambient1,
                     _ambient2,
                     _diffuse1,
                     _diffuse2,
                     _specular1,
                     _specular2,
                     _shine1,
                     _shine2,
                     _alpha1,
                     _alpha2](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec2<T> &p2d = _data2D[i];
                            const Vec3<T> N1 =
                                (_orientation.normal2 * p2d.x + _orientation.normal3 * p2d.y).normalized();
                            const Vec3<T> P1 = N1 * _radius1;
                            const Vec3<T> P2 = _orientation.normal1 * _length + N1 * _radius2;
                            const Math::Vec3F N2 = (P2 - P1).normalized();
                            const Math::Vec3F N3 = Math::Vec3F::cross(N2, N1).normalized();
                            const Math::Vec3F N = Math::Vec3F::cross(N3, N2).normalized();
                            const size_t j1 = i * 2UL;
                            const size_t j2 = j1 + 1UL;
                            __outVertex[j1] = _orientation.center + P1;
                            __outVertex[j2] = _orientation.center + P2;
                            __outNormal[j1] = -N;
                            __outNormal[j2] = -N;
                            __outAmbient[j1] = _ambient1;
                            __outAmbient[j2] = _ambient2;
                            __outDiffuse[j1] = _diffuse1;
                            __outDiffuse[j2] = _diffuse2;
                            __outSpecular[j1] = _specular1;
                            __outSpecular[j2] = _specular2;
                            __outShine[j1] = _shine1;
                            __outShine[j2] = _shine2;
                            __outAlpha[j1] = _alpha1;
                            __outAlpha[j2] = _alpha2;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const size_t last0 = data2D.size() * 2UL, last1 = last0 + 1UL;
    _outVertex[last0] = _outVertex[0UL];
    _outVertex[last1] = _outVertex[1UL];

    _outNormal[last0] = _outNormal[0UL];
    _outNormal[last1] = _outNormal[1UL];

    _outAmbient[last0] = _outAmbient[0UL];
    _outAmbient[last1] = _outAmbient[1UL];

    _outDiffuse[last0] = _outDiffuse[0UL];
    _outDiffuse[last1] = _outDiffuse[1UL];

    _outSpecular[last0] = _outSpecular[0UL];
    _outSpecular[last1] = _outSpecular[1UL];

    _outShine[last0] = _outShine[0UL];
    _outShine[last1] = _outShine[1UL];

    _outAlpha[last0] = _outAlpha[0UL];
    _outAlpha[last1] = _outAlpha[1UL];
}

/*!
 * \brief Fill cylinder vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    T *_outAlpha,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      _outAlpha,
                      Orientation<T>(_center, _normal, _arm),
                      _ambient1,
                      _ambient2,
                      _diffuse1,
                      _diffuse2,
                      _specular1,
                      _specular2,
                      _shine1,
                      _shine2,
                      _alpha1,
                      _alpha2,
                      _length,
                      _radius1,
                      _radius2,
                      _quality);
}

/*!
 * \brief Fill cylinder vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _length Cylinder length
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 */
template <typename T>
void Cylinder<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                    Vec3<T> *_outNormal,
                                    Vec3<T> *_outAmbient,
                                    Vec3<T> *_outDiffuse,
                                    Vec3<T> *_outSpecular,
                                    T *_outShine,
                                    T *_outAlpha,
                                    const Vec3<T> &_center,
                                    const Vec3<T> &_normal,
                                    const Vec3<T> &_arm,
                                    const Vec3<T> &_ambient1,
                                    const Vec3<T> &_ambient2,
                                    const Vec3<T> &_diffuse1,
                                    const Vec3<T> &_diffuse2,
                                    const Vec3<T> &_specular1,
                                    const Vec3<T> &_specular2,
                                    const T _shine1,
                                    const T _shine2,
                                    const T _alpha1,
                                    const T _alpha2,
                                    const T _length,
                                    const T _radius1,
                                    const T _radius2,
                                    const size_t _quality)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      _outAlpha,
                      Orientation<T>(_center, _normal, _arm),
                      _ambient1,
                      _ambient2,
                      _diffuse1,
                      _diffuse2,
                      _specular1,
                      _specular2,
                      _shine1,
                      _shine2,
                      _alpha1,
                      _alpha2,
                      _length,
                      _radius1,
                      _radius2,
                      _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Cylinder<float> CylinderF;        //!< 32 bit floating point precision 3D cylinder
typedef Cylinder<double> CylinderD;       //!< 64 bit floating point precision 3D cylinder
typedef Cylinder<long double> CylinderL;  //!< 128 bit floating point precision 3D cylinder

}  // namespace Math
}  // namespace U1

#endif  // MATH_CYLINDER_H
