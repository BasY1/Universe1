/*!
 * \file src/Math/cylinderarc.h
 * \brief Cylinder-arc geometry tools
 */

#ifndef MATH_CYLINDERARC_H
#define MATH_CYLINDERARC_H

#include "circle.h"
#include "planeindices.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D Cylinder structure
 * \tparam T Template floating point type
 */
template <typename T>
struct CylinderArc
{
    /*!
     * \brief Prepare cylinder arc angles
     * \param _out Output cylinder arc angles in radians
     * \param _radiusArc Cylinder arc radius
     * \param _cylinderLength Cylinder length
     * \param _quality Cylinder arc quality
     * \param _offsetAngle Start angle in radians
     * \return
     */
    inline static void cylinderArcAngles(std::vector<T> &_out,
                                         const T _radiusArc,
                                         const T _cylinderLength,
                                         const size_t _quality,
                                         const T _offsetAngle = T(0))
    {
        static const T _2PI = T(2.0l * M_PIl);
        const T angleStep = _2PI / T(circlePointCount(_quality));
        const T angleCylinder = _cylinderLength / _radiusArc;
        fillSteps<T>(_out, _offsetAngle, _offsetAngle + angleCylinder, angleStep);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  uint *_outIndex,
                                  const Orientation<T> &_orientation,
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  uint *_outIndex,
                                  const Orientation<T> &_orientation,
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         uint *_outIndex,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         uint *_outIndex,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  T *_outAlpha,
                                  uint *_outIndex,
                                  const Orientation<T> &_orientation,
                                  const T _alpha1,
                                  const T _alpha2,
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  T *_outAlpha,
                                  uint *_outIndex,
                                  const Orientation<T> &_orientation,
                                  const T _alpha1,
                                  const T _alpha2,
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         T *_outAlpha,
                                         uint *_outIndex,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _alpha1,
                                         const T _alpha2,
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         T *_outAlpha,
                                         uint *_outIndex,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _alpha1,
                                         const T _alpha2,
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  uint *_outIndex,
                                  const Orientation<T> &_orientation,
                                  const Vec3<T> &_ambient1,
                                  const Vec3<T> &_ambient2,
                                  const Vec3<T> &_diffuse1,
                                  const Vec3<T> &_diffuse2,
                                  const Vec3<T> &_specular1,
                                  const Vec3<T> &_specular2,
                                  const T _shine1,
                                  const T _shine2,
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  uint *_outIndex,
                                  const Orientation<T> &_orientation,
                                  const Vec3<T> &_ambient1,
                                  const Vec3<T> &_ambient2,
                                  const Vec3<T> &_diffuse1,
                                  const Vec3<T> &_diffuse2,
                                  const Vec3<T> &_specular1,
                                  const Vec3<T> &_specular2,
                                  const T _shine1,
                                  const T _shine2,
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         uint *_outIndex,
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
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         uint *_outIndex,
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
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCylinderOuter(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  T *_outAlpha,
                                  uint *_outIndex,
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
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    static void fillCylinderInner(Vec3<T> *_outVertex,
                                  Vec3<T> *_outNormal,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  T *_outAlpha,
                                  uint *_outIndex,
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
                                  const T _radiusArc,
                                  const T _radius1,
                                  const T _radius2,
                                  const size_t _quality,
                                  const std::vector<T> &_angles);

    inline static void fillCylinderOuter(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         T *_outAlpha,
                                         uint *_outIndex,
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
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);

    inline static void fillCylinderInner(Vec3<T> *_outVertex,
                                         Vec3<T> *_outNormal,
                                         Vec3<T> *_outAmbient,
                                         Vec3<T> *_outDiffuse,
                                         Vec3<T> *_outSpecular,
                                         T *_outShine,
                                         T *_outAlpha,
                                         uint *_outIndex,
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
                                         const T _radiusArc,
                                         const T _radius1,
                                         const T _radius2,
                                         const size_t _quality,
                                         const std::vector<T> &_angles);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Orientation<T> &_orientation,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, cntCircle, _orientation, _radius1, _radiusArc](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D, const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        const T RD = _radius2 - _radius1;
        const T AD = _angles.back() - _angles.front();
        const T LL = _radiusArc * AD;
        const T AP = std::atan2(RD, LL);
        const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T RR = _radius1 + RD * ((_angles[ia] - _angles[0]) / AD);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, RD, AP, AD, offset, cntCircle, angleStep, _orientation, _radius1, _radius2, _radiusArc](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D, const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T RR = _radius1 + RD * ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Orientation<T> &_orientation,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = -N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, cntCircle, _orientation, _radius1, _radiusArc](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D, const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = -N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        const T RD = _radius2 - _radius1;
        const T AD = _angles.back() - _angles.front();
        const T LL = _radiusArc * AD;
        const T AP = std::atan2(RD, LL);
        const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

        if (pool.empty())
        {
            for (size_t i = 0UL; i < data2D.size(); i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T RR = _radius1 + RD * ((_angles[ia] - _angles[0]) / AD);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = -N;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, RD, AP, AD, offset, cntCircle, angleStep, _orientation, _radius1, _radius2, _radiusArc](
                        Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec2<T> *_data2D, const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T RR = _radius1 + RD * ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = -N;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outIndex,
                      Orientation<T>(_center, _normal, _arm),
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outIndex,
                      Orientation<T>(_center, _normal, _arm),
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       T *_outAlpha,
                                       uint *_outIndex,
                                       const Orientation<T> &_orientation,
                                       const T _alpha1,
                                       const T _alpha2,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    const T AFD = _alpha2 - _alpha1;
    const T RD = _radius2 - _radius1;
    const T AD = _angles.back() - _angles.front();
    const T LL = _radiusArc * AD;
    const T AP = std::atan2(RD, LL);
    const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const T ratio = ((_angles[ia] - _angles[0]) / AD);

                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = N;
                _outAlpha[i] = _alpha1 + AFD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, AD, AFD, offset, cntCircle, _orientation, _radius1, _radiusArc, _alpha1](Vec3<T> *__outVertex,
                                                                                                 Vec3<T> *__outNormal,
                                                                                                 T *__outAlpha,
                                                                                                 const Vec2<T> *_data2D,
                                                                                                 const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = N;
                            __outAlpha[i] = _alpha1 + AFD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
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
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T ratio = ((_angles[ia] - _angles[0]) / AD);
                const T RR = _radius1 + RD * ratio;
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = N;
                _outAlpha[i] = _alpha1 + AFD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     RD,
                     AP,
                     AFD,
                     offset,
                     cntCircle,
                     angleStep,
                     _orientation,
                     _radius1,
                     _radius2,
                     _radiusArc,
                     _alpha1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              T *__outAlpha,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const T RR = _radius1 + RD * ratio;
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = N;
                            __outAlpha[i] = _alpha1 + AFD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       T *_outAlpha,
                                       uint *_outIndex,
                                       const Orientation<T> &_orientation,
                                       const T _alpha1,
                                       const T _alpha2,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    const T AFD = _alpha2 - _alpha1;
    const T RD = _radius2 - _radius1;
    const T AD = _angles.back() - _angles.front();
    const T LL = _radiusArc * AD;
    const T AP = std::atan2(RD, LL);
    const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const T ratio = ((_angles[ia] - _angles[0]) / AD);

                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = -N;
                _outAlpha[i] = _alpha1 + AFD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, AD, AFD, offset, cntCircle, _orientation, _radius1, _radiusArc, _alpha1](Vec3<T> *__outVertex,
                                                                                                 Vec3<T> *__outNormal,
                                                                                                 T *__outAlpha,
                                                                                                 const Vec2<T> *_data2D,
                                                                                                 const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = -N;
                            __outAlpha[i] = _alpha1 + AFD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
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
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T ratio = ((_angles[ia] - _angles[0]) / AD);
                const T RR = _radius1 + RD * ratio;
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = -N;
                _outAlpha[i] = _alpha1 + AFD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     RD,
                     AP,
                     AFD,
                     offset,
                     cntCircle,
                     angleStep,
                     _orientation,
                     _radius1,
                     _radius2,
                     _radiusArc,
                     _alpha1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              T *__outAlpha,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const T RR = _radius1 + RD * ratio;
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = -N;
                            __outAlpha[i] = _alpha1 + AFD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       T *_outAlpha,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _alpha1,
                                       const T _alpha2,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outAlpha,
                      _outIndex,
                      Orientation<T>(_center, _normal, _arm),
                      _alpha1,
                      _alpha2,
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
 * \param _center Cylinder center point
 * \param _normal Cylinder plane normal
 * \param _arm Cylinder start arm
 * \param _alpha1 Cylinder alpha at start
 * \param _alpha2 Cylinder alpha at end
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       T *_outAlpha,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _alpha1,
                                       const T _alpha2,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outAlpha,
                      _outIndex,
                      Orientation<T>(_center, _normal, _arm),
                      _alpha1,
                      _alpha2,
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outIndex Output index array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       uint *_outIndex,
                                       const Orientation<T> &_orientation,
                                       const Vec3<T> &_ambient1,
                                       const Vec3<T> &_ambient2,
                                       const Vec3<T> &_diffuse1,
                                       const Vec3<T> &_diffuse2,
                                       const Vec3<T> &_specular1,
                                       const Vec3<T> &_specular2,
                                       const T _shine1,
                                       const T _shine2,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    const Vec3<T> ACD = _ambient2 - _ambient1;
    const Vec3<T> DCD = _diffuse2 - _diffuse1;
    const Vec3<T> SCD = _specular2 - _specular1;
    const T SSD = _shine2 - _shine1;
    const T RD = _radius2 - _radius1;
    const T AD = _angles.back() - _angles.front();
    const T LL = _radiusArc * AD;
    const T AP = std::atan2(RD, LL);
    const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const T ratio = ((_angles[ia] - _angles[0]) / AD);

                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     offset,
                     cntCircle,
                     _orientation,
                     _radius1,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data(),
                    _angles.data()));
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
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T ratio = ((_angles[ia] - _angles[0]) / AD);
                const T RR = _radius1 + RD * ratio;
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     RD,
                     AP,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     offset,
                     cntCircle,
                     angleStep,
                     _orientation,
                     _radius1,
                     _radius2,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const T RR = _radius1 + RD * ratio;
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outIndex Output index array
 * \param _orientation Cylinder plane orientation in 3D space
 * \param _ambient1 Cylinder ambient at start
 * \param _ambient2 Cylinder ambient at end
 * \param _diffuse1 Cylinder diffuse at start
 * \param _diffuse2 Cylinder diffuse at end
 * \param _specular1 Cylinder specular at start
 * \param _specular2 Cylinder specular at end
 * \param _shine1 Cylinder shine at start
 * \param _shine2 Cylinder shine at end
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       uint *_outIndex,
                                       const Orientation<T> &_orientation,
                                       const Vec3<T> &_ambient1,
                                       const Vec3<T> &_ambient2,
                                       const Vec3<T> &_diffuse1,
                                       const Vec3<T> &_diffuse2,
                                       const Vec3<T> &_specular1,
                                       const Vec3<T> &_specular2,
                                       const T _shine1,
                                       const T _shine2,
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    const Vec3<T> ACD = _ambient2 - _ambient1;
    const Vec3<T> DCD = _diffuse2 - _diffuse1;
    const Vec3<T> SCD = _specular2 - _specular1;
    const T SSD = _shine2 - _shine1;
    const T RD = _radius2 - _radius1;
    const T AD = _angles.back() - _angles.front();
    const T LL = _radiusArc * AD;
    const T AP = std::atan2(RD, LL);
    const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const T ratio = ((_angles[ia] - _angles[0]) / AD);

                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = -N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     offset,
                     cntCircle,
                     _orientation,
                     _radius1,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = -N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data(),
                    _angles.data()));
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
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T ratio = ((_angles[ia] - _angles[0]) / AD);
                const T RR = _radius1 + RD * ratio;
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = -N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     RD,
                     AP,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     offset,
                     cntCircle,
                     angleStep,
                     _orientation,
                     _radius1,
                     _radius2,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const T RR = _radius1 + RD * ratio;
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = -N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outIndex Output index array
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
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       uint *_outIndex,
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
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      _outIndex,
                      Orientation<T>(_center, _normal, _arm),
                      _ambient1,
                      _ambient2,
                      _diffuse1,
                      _diffuse2,
                      _specular1,
                      _specular2,
                      _shine1,
                      _shine2,
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outIndex Output index array
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
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       uint *_outIndex,
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
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      _outIndex,
                      Orientation<T>(_center, _normal, _arm),
                      _ambient1,
                      _ambient2,
                      _diffuse1,
                      _diffuse2,
                      _specular1,
                      _specular2,
                      _shine1,
                      _shine2,
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
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
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       T *_outAlpha,
                                       uint *_outIndex,
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
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    const Vec3<T> ACD = _ambient2 - _ambient1;
    const Vec3<T> DCD = _diffuse2 - _diffuse1;
    const Vec3<T> SCD = _specular2 - _specular1;
    const T SSD = _shine2 - _shine1;
    const T AAD = _alpha2 - _alpha1;
    const T RD = _radius2 - _radius1;
    const T AD = _angles.back() - _angles.front();
    const T LL = _radiusArc * AD;
    const T AP = std::atan2(RD, LL);
    const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const T ratio = ((_angles[ia] - _angles[0]) / AD);

                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
                _outAlpha[i] = _alpha1 + AAD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     AAD,
                     offset,
                     cntCircle,
                     _orientation,
                     _radius1,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1,
                     _alpha1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                            __outAlpha[i] = _alpha1 + AAD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
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
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T ratio = ((_angles[ia] - _angles[0]) / AD);
                const T RR = _radius1 + RD * ratio;
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
                _outAlpha[i] = _alpha1 + AAD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     RD,
                     AP,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     AAD,
                     offset,
                     cntCircle,
                     angleStep,
                     _orientation,
                     _radius1,
                     _radius2,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1,
                     _alpha1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const T RR = _radius1 + RD * ratio;
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                            __outAlpha[i] = _alpha1 + AAD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
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
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       T *_outAlpha,
                                       uint *_outIndex,
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
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    const std::vector<Vec2<T>> &data2D = Circle2<T>::unitCircle(_quality).first;
    const size_t cntCircle = circlePointCount(_quality);
    const size_t offset = cntCircle + 1UL;
    const size_t cntVertex = offset * _angles.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    const Vec3<T> ACD = _ambient2 - _ambient1;
    const Vec3<T> DCD = _diffuse2 - _diffuse1;
    const Vec3<T> SCD = _specular2 - _specular1;
    const T SSD = _shine2 - _shine1;
    const T AAD = _alpha2 - _alpha1;
    const T RD = _radius2 - _radius1;
    const T AD = _angles.back() - _angles.front();
    const T LL = _radiusArc * AD;
    const T AP = std::atan2(RD, LL);
    const T angleStep = T(2.0l * M_PIl) / T(cntCircle);

    if (equals<T>(_radius1, _radius2))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; i++)
            {
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const T ratio = ((_angles[ia] - _angles[0]) / AD);

                _outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                _outNormal[i] = -N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
                _outAlpha[i] = _alpha1 + AAD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     AAD,
                     offset,
                     cntCircle,
                     _orientation,
                     _radius1,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1,
                     _alpha1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N * _radius1;
                            __outNormal[i] = -N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                            __outAlpha[i] = _alpha1 + AAD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
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
                const size_t ia = i / offset;
                const size_t ic = i % offset;
                const size_t icc = (ic == cntCircle ? 0UL : ic);
                const T ratio = ((_angles[ia] - _angles[0]) / AD);
                const T RR = _radius1 + RD * ratio;
                const Vec2<T> &p2d = data2D[icc];
                const Vec3<T> N0 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia]).normalized();
                const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                const Vec3<T> N2 = _orientation.normal2.rotated(_orientation.normal1, _angles[ia] + AP).normalized();
                const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                _outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                _outNormal[i] = -N;
                _outAmbient[i] = _ambient1 + ACD * ratio;
                _outDiffuse[i] = _diffuse1 + DCD * ratio;
                _outSpecular[i] = _specular1 + SCD * ratio;
                _outShine[i] = _shine1 + SSD * ratio;
                _outAlpha[i] = _alpha1 + AAD * ratio;
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t,
                     AD,
                     RD,
                     AP,
                     ACD,
                     DCD,
                     SCD,
                     SSD,
                     AAD,
                     offset,
                     cntCircle,
                     angleStep,
                     _orientation,
                     _radius1,
                     _radius2,
                     _radiusArc,
                     _ambient1,
                     _diffuse1,
                     _specular1,
                     _shine1,
                     _alpha1](Vec3<T> *__outVertex,
                              Vec3<T> *__outNormal,
                              Vec3<T> *__outAmbient,
                              Vec3<T> *__outDiffuse,
                              Vec3<T> *__outSpecular,
                              T *__outShine,
                              T *__outAlpha,
                              const Vec2<T> *_data2D,
                              const T *__angles) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const size_t ia = i / offset;
                            const size_t ic = i % offset;
                            const size_t icc = (ic == cntCircle ? 0UL : ic);
                            const T ratio = ((__angles[ia] - __angles[0]) / AD);
                            const T RR = _radius1 + RD * ratio;
                            const Vec2<T> &p2d = _data2D[icc];
                            const Vec3<T> N0 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia]).normalized();
                            const Vec3<T> N1 = (N0 * p2d.x + _orientation.normal1 * p2d.y).normalized();
                            const Vec3<T> N2 =
                                _orientation.normal2.rotated(_orientation.normal1, __angles[ia] + AP).normalized();
                            const Vec3<T> N3 = Vec3<T>::cross(_orientation.normal1, N0).normalized();
                            const Vec3<T> N = N2.rotated(N3, T(icc) * angleStep).normalized();
                            __outVertex[i] = _orientation.center + N0 * _radiusArc + N1 * RR;
                            __outNormal[i] = -N;
                            __outAmbient[i] = _ambient1 + ACD * ratio;
                            __outDiffuse[i] = _diffuse1 + DCD * ratio;
                            __outSpecular[i] = _specular1 + SCD * ratio;
                            __outShine[i] = _shine1 + SSD * ratio;
                            __outAlpha[i] = _alpha1 + AAD * ratio;
                        }
                    },
                    _outVertex,
                    _outNormal,
                    _outAmbient,
                    _outDiffuse,
                    _outSpecular,
                    _outShine,
                    _outAlpha,
                    data2D.data(),
                    _angles.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(_angles.size(), offset);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill cylinder arc vertices - visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
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
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       T *_outAlpha,
                                       uint *_outIndex,
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
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderOuter(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      _outAlpha,
                      _outIndex,
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
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

/*!
 * \brief Fill cylinder arc vertices - visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outAmbient Output ambient array
 * \param _outDiffuse Output diffuse array
 * \param _outSpecular Output specular array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _outIndex Output index array
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
 * \param _radiusArc Cylinder arc radius
 * \param _radius1 Cylinder radius at start
 * \param _radius2 Cylinder radius at end
 * \param _quality Circle quality
 * \param _angles Cylinder arc angles in radians
 * \return
 */
template <typename T>
void CylinderArc<T>::fillCylinderInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       Vec3<T> *_outAmbient,
                                       Vec3<T> *_outDiffuse,
                                       Vec3<T> *_outSpecular,
                                       T *_outShine,
                                       T *_outAlpha,
                                       uint *_outIndex,
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
                                       const T _radiusArc,
                                       const T _radius1,
                                       const T _radius2,
                                       const size_t _quality,
                                       const std::vector<T> &_angles)
{
    fillCylinderInner(_outVertex,
                      _outNormal,
                      _outAmbient,
                      _outDiffuse,
                      _outSpecular,
                      _outShine,
                      _outAlpha,
                      _outIndex,
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
                      _radiusArc,
                      _radius1,
                      _radius2,
                      _quality,
                      _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef CylinderArc<float> CylinderArcF;        //!< 32 bit floating point precision 3D cylinder arc
typedef CylinderArc<double> CylinderArcD;       //!< 64 bit floating point precision 3D cylinder arc
typedef CylinderArc<long double> CylinderArcL;  //!< 128 bit floating point precision 3D cylinder arc

}  // namespace Math
}  // namespace U1

#endif  // MATH_CYLINDERARC_H
