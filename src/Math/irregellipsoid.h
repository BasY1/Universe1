/*!
 * \file src/Math/irregellipsoid.h
 * \brief 3D irregular ellipsoid structure
 */

#ifndef MATH_IRREGELLIPSOID_H
#define MATH_IRREGELLIPSOID_H

#include "sphere.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D irregular ellipsoid representation
 * \tparam T Template floating point type
 */
template <typename T>
struct IrregEllipsoid
{

    /*!
     * \brief Ellipsoid vertex count by circle quality
     * \param _quality Circle quality
     * \return Ellipsoid vertex count
     */
    inline static size_t ellipsoidVertexCount(const size_t _quality)
    {
        const size_t cntCircle = circlePointCount(_quality);
        const size_t cntLon = cntCircle;
        const size_t cntLat = cntCircle / 2UL;
        return (cntLon + 1UL) * (cntLat + 1UL);
    }

    /*!
     * \brief Ellipsoid index count by circle quality
     * \param _quality Circle quality
     * \return Ellipsoid index count
     */
    inline static size_t ellipsoidIndexCount(const size_t _quality)
    {
        const size_t cntCircle = circlePointCount(_quality);
        const size_t cntLon = cntCircle;
        const size_t cntLat = cntCircle / 2UL;
        return cntLon * cntLat * 4UL;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipsoidOuter(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const T _radius3P,
                                   const T _radius3M,
                                   const size_t _quality);

    static void fillEllipsoidInner(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const T _radius3P,
                                   const T _radius3M,
                                   const size_t _quality);

    inline static void fillEllipsoidOuter(Vec3<T> *_outVertex,
                                          Vec3<T> *_outNormal,
                                          uint *_outIndex,
                                          const Vec3<T> &_center,
                                          const Vec3<T> &_normal,
                                          const Vec3<T> &_arm,
                                          const T _radius1P,
                                          const T _radius1M,
                                          const T _radius2P,
                                          const T _radius2M,
                                          const T _radius3P,
                                          const T _radius3M,
                                          const size_t _quality);

    inline static void fillEllipsoidInner(Vec3<T> *_outVertex,
                                          Vec3<T> *_outNormal,
                                          uint *_outIndex,
                                          const Vec3<T> &_center,
                                          const Vec3<T> &_normal,
                                          const Vec3<T> &_arm,
                                          const T _radius1P,
                                          const T _radius1M,
                                          const T _radius2P,
                                          const T _radius2M,
                                          const T _radius3P,
                                          const T _radius3M,
                                          const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipsoidOuter(Vec3<T> *_outVertex,
                                   Vec2<T> *_outCoord,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const T _radius3P,
                                   const T _radius3M,
                                   const size_t _quality);

    static void fillEllipsoidInner(Vec3<T> *_outVertex,
                                   Vec2<T> *_outCoord,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const T _radius3P,
                                   const T _radius3M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline static void arcAngles(std::vector<T> &_outLon,
                                 std::vector<T> &_outLat,
                                 const T _angleLonStart,
                                 const T _angleLonEnd,
                                 const T _angleLatStart,
                                 const T _angleLatEnd,
                                 const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipsoidArcOuter(Vec3<T> *_outVertex,
                                      Vec3<T> *_outNormal,
                                      uint *_outIndex,
                                      const Orientation<T> &_orientation,
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const T _radius3P,
                                      const T _radius3M,
                                      const std::vector<T> &_anglesLon,
                                      const std::vector<T> &_anglesLat);

    static void fillEllipsoidArcInner(Vec3<T> *_outVertex,
                                      Vec3<T> *_outNormal,
                                      uint *_outIndex,
                                      const Orientation<T> &_orientation,
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const T _radius3P,
                                      const T _radius3M,
                                      const std::vector<T> &_anglesLon,
                                      const std::vector<T> &_anglesLat);

    inline static void fillEllipsoidArcOuter(Vec3<T> *_outVertex,
                                             Vec3<T> *_outNormal,
                                             uint *_outIndex,
                                             const Vec3<T> &_center,
                                             const Vec3<T> &_normal,
                                             const Vec3<T> &_arm,
                                             const T _radius1P,
                                             const T _radius1M,
                                             const T _radius2P,
                                             const T _radius2M,
                                             const T _radius3P,
                                             const T _radius3M,
                                             const std::vector<T> &_anglesLon,
                                             const std::vector<T> &_anglesLat);

    inline static void fillEllipsoidArcInner(Vec3<T> *_outVertex,
                                             Vec3<T> *_outNormal,
                                             uint *_outIndex,
                                             const Vec3<T> &_center,
                                             const Vec3<T> &_normal,
                                             const Vec3<T> &_arm,
                                             const T _radius1P,
                                             const T _radius1M,
                                             const T _radius2P,
                                             const T _radius2M,
                                             const T _radius3P,
                                             const T _radius3M,
                                             const std::vector<T> &_anglesLon,
                                             const std::vector<T> &_anglesLat);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill irregular ellipsoid vertices - ellipsoid visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Ellipsoid orientation in 3D space
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidOuter(Vec3<T> *_outVertex,
                                           Vec3<T> *_outNormal,
                                           uint *_outIndex,
                                           const Orientation<T> &_orientation,
                                           const T _radius1P,
                                           const T _radius1M,
                                           const T _radius2P,
                                           const T _radius2M,
                                           const T _radius3P,
                                           const T _radius3M,
                                           const size_t _quality)
{
    const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &us = Sphere<T>::unitSphere(_quality);
    const std::vector<Vec3<T>> &data = us.first;
    const std::vector<std::pair<size_t, size_t>> &pool = us.second;

    if (pool.empty())
    {
        for (size_t i = 0UL; i < data.size(); ++i)
        {
            const Vec3<T> &N0 = data[i];
            const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
            const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
            const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;

            const Vec3<T> N1 = (T(2) * Vec3<T>(N0.x / R1, N0.y / R2, N0.z / R3)).normalized();
            const Vec3<T> N2 =
                (_orientation.normal1 * N1.x + _orientation.normal2 * N1.y + _orientation.normal3 * N1.z).normalized();

            _outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);

            _outNormal[i] = N2;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M](
                    Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec3<T> *_data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> &N0 = _data[i];
                        const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
                        const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
                        const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;

                        const Vec3<T> N1 = (T(2) * Vec3<T>(N0.x / R1, N0.y / R2, N0.z / R3)).normalized();
                        const Vec3<T> N2 =
                            (_orientation.normal1 * N1.x + _orientation.normal2 * N1.y + _orientation.normal3 * N1.z)
                                .normalized();

                        __outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                            _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);

                        __outNormal[i] = N2;
                    }
                },
                _outVertex,
                _outNormal,
                data.data()));
        for (std::thread &t : threads)
            t.join();
    }

    const size_t cntCircle = circlePointCount(_quality);
    const size_t cntLon = cntCircle;
    const size_t cntLat = cntCircle / 2UL;
    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(cntLon + 1UL, cntLat + 1UL);

    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill irregular ellipsoid vertices - ellipsoid visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Ellipsoid orientation in 3D space
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidInner(Vec3<T> *_outVertex,
                                           Vec3<T> *_outNormal,
                                           uint *_outIndex,
                                           const Orientation<T> &_orientation,
                                           const T _radius1P,
                                           const T _radius1M,
                                           const T _radius2P,
                                           const T _radius2M,
                                           const T _radius3P,
                                           const T _radius3M,
                                           const size_t _quality)
{
    const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &us = Sphere<T>::unitSphere(_quality);
    const std::vector<Vec3<T>> &data = us.first;
    const std::vector<std::pair<size_t, size_t>> &pool = us.second;

    if (pool.empty())
    {
        for (size_t i = 0UL; i < data.size(); ++i)
        {
            const Vec3<T> &N0 = data[i];
            const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
            const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
            const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;
            const Vec3<T> N1 = (T(2) * Vec3<T>(N0.x / R1, N0.y / R2, N0.z / R3)).normalized();
            const Vec3<T> N2 =
                (_orientation.normal1 * N1.x + _orientation.normal2 * N1.y + _orientation.normal3 * N1.z).normalized();

            _outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);

            _outNormal[i] = -N2;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M](
                    Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec3<T> *_data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> &N0 = _data[i];
                        const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
                        const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
                        const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;
                        const Vec3<T> N1 = (T(2) * Vec3<T>(N0.x / R1, N0.y / R2, N0.z / R3)).normalized();
                        const Vec3<T> N2 =
                            (_orientation.normal1 * N1.x + _orientation.normal2 * N1.y + _orientation.normal3 * N1.z)
                                .normalized();

                        __outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                            _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);

                        __outNormal[i] = -N2;
                    }
                },
                _outVertex,
                _outNormal,
                data.data()));
        for (std::thread &t : threads)
            t.join();
    }

    const size_t cntCircle = circlePointCount(_quality);
    const size_t cntLon = cntCircle;
    const size_t cntLat = cntCircle / 2UL;
    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(cntLon + 1UL, cntLat + 1UL);

    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill irregular ellipsoid vertices - ellipsoid visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Ellipsoid center point
 * \param _normal Ellipsoid plane normal
 * \param _arm Ellipsoid start arm
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipsoid<T>::fillEllipsoidOuter(Vec3<T> *_outVertex,
                                                  Vec3<T> *_outNormal,
                                                  uint *_outIndex,
                                                  const Vec3<T> &_center,
                                                  const Vec3<T> &_normal,
                                                  const Vec3<T> &_arm,
                                                  const T _radius1P,
                                                  const T _radius1M,
                                                  const T _radius2P,
                                                  const T _radius2M,
                                                  const T _radius3P,
                                                  const T _radius3M,
                                                  const size_t _quality)
{
    fillEllipsoidOuter(_outVertex,
                       _outNormal,
                       _outIndex,
                       Orientation<T>(_center, _normal, _arm),
                       _radius1P,
                       _radius1M,
                       _radius2P,
                       _radius2M,
                       _radius3P,
                       _radius3M,
                       _quality);
}

/*!
 * \brief Fill irregular ellipsoid vertices - ellipsoid visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Ellipsoid center point
 * \param _normal Ellipsoid plane normal
 * \param _arm Ellipsoid start arm
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipsoid<T>::fillEllipsoidInner(Vec3<T> *_outVertex,
                                                  Vec3<T> *_outNormal,
                                                  uint *_outIndex,
                                                  const Vec3<T> &_center,
                                                  const Vec3<T> &_normal,
                                                  const Vec3<T> &_arm,
                                                  const T _radius1P,
                                                  const T _radius1M,
                                                  const T _radius2P,
                                                  const T _radius2M,
                                                  const T _radius3P,
                                                  const T _radius3M,
                                                  const size_t _quality)
{
    fillEllipsoidInner(_outVertex,
                       _outNormal,
                       _outIndex,
                       Orientation<T>(_center, _normal, _arm),
                       _radius1P,
                       _radius1M,
                       _radius2P,
                       _radius2M,
                       _radius3P,
                       _radius3M,
                       _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill irregular ellipsoid vertices - ellipsoid visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outIndex Output index array
 * \param _orientation Ellipsoid orientation in 3D space
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidOuter(Vec3<T> *_outVertex,
                                           Vec2<T> *_outCoords,
                                           uint *_outIndex,
                                           const Orientation<T> &_orientation,
                                           const T _radius1P,
                                           const T _radius1M,
                                           const T _radius2P,
                                           const T _radius2M,
                                           const T _radius3P,
                                           const T _radius3M,
                                           const size_t _quality)
{
    const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &us = Sphere<T>::unitSphere(_quality);
    const std::vector<Vec3<T>> &data = us.first;
    const std::vector<std::pair<size_t, size_t>> &pool = us.second;

    if (pool.empty())
    {
        for (size_t i = 0UL; i < data.size(); ++i)
        {
            const Vec3<T> &N0 = data[i];
            const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
            const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
            const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;
            _outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M](
                    Vec3<T> *__outVertex, const Vec3<T> *_data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> &N0 = _data[i];
                        const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
                        const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
                        const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;
                        __outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                            _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);
                    }
                },
                _outVertex,
                data.data()));
        for (std::thread &t : threads)
            t.join();
    }

    const size_t cntCircle = circlePointCount(_quality);
    const size_t cntLon = cntCircle;
    const size_t cntLat = cntCircle / 2UL;

    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        PlaneCoords<T>::getCoords(cntLon + 1UL, cntLat + 1UL);

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(cntLon + 1UL, cntLat + 1UL);

    copyData<Vec2<T>, size_t>(_outCoords, uc.first.data(), uc.first.size(), uc.second);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill irregular ellipsoid vertices - ellipsoid visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outIndex Output index array
 * \param _orientation Ellipsoid orientation in 3D space
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidInner(Vec3<T> *_outVertex,
                                           Vec2<T> *_outCoords,
                                           uint *_outIndex,
                                           const Orientation<T> &_orientation,
                                           const T _radius1P,
                                           const T _radius1M,
                                           const T _radius2P,
                                           const T _radius2M,
                                           const T _radius3P,
                                           const T _radius3M,
                                           const size_t _quality)
{
    const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &us = Sphere<T>::unitSphere(_quality);
    const std::vector<Vec3<T>> &data = us.first;
    const std::vector<std::pair<size_t, size_t>> &pool = us.second;

    if (pool.empty())
    {
        for (size_t i = 0UL; i < data.size(); ++i)
        {
            const Vec3<T> &N0 = data[i];
            const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
            const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
            const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;
            _outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M](
                    Vec3<T> *__outVertex, const Vec3<T> *_data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> &N0 = _data[i];
                        const T R1 = isNegative(N0.x) ? _radius1M : _radius1P;
                        const T R2 = isNegative(N0.y) ? _radius2M : _radius2P;
                        const T R3 = isNegative(N0.z) ? _radius3M : _radius3P;
                        __outVertex[i] = _orientation.center + _orientation.normal1 * (N0.x * R1) +
                            _orientation.normal2 * (N0.y * R2) + _orientation.normal3 * (N0.z * R3);
                    }
                },
                _outVertex,
                data.data()));
        for (std::thread &t : threads)
            t.join();
    }

    const size_t cntCircle = circlePointCount(_quality);
    const size_t cntLon = cntCircle;
    const size_t cntLat = cntCircle / 2UL;

    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        PlaneCoords<T>::getCoords(cntLon + 1UL, cntLat + 1UL);

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(cntLon + 1UL, cntLat + 1UL);

    copyData<Vec2<T>, size_t>(_outCoords, uc.first.data(), uc.first.size(), uc.second);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create irregular ellipsoid arc angles for longitudes and latitudes, aligned with circle quality
 * \tparam T Template floating point type
 * \param _outLon Output longitude arc angles
 * \param _outLat Output latitude arc angles
 * \param _angleLonStart Start longitude angle in radians
 * \param _angleLonEnd End longitude angle in radians
 * \param _angleLatStart Start latitude angle in radians
 * \param _angleLatEnd End latitude angle in radians
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipsoid<T>::arcAngles(std::vector<T> &_outLon,
                                         std::vector<T> &_outLat,
                                         const T _angleLonStart,
                                         const T _angleLonEnd,
                                         const T _angleLatStart,
                                         const T _angleLatEnd,
                                         const size_t _quality)
{
    return Sphere<T>::arcAngles(_outLon, _outLat, _angleLonStart, _angleLonEnd, _angleLatStart, _angleLatEnd, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill irregular ellipsoid arc vertices - ellipsoid visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Ellipsoid orientation in 3D space
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidArcOuter(Vec3<T> *_outVertex,
                                              Vec3<T> *_outNormal,
                                              uint *_outIndex,
                                              const Orientation<T> &_orientation,
                                              const T _radius1P,
                                              const T _radius1M,
                                              const T _radius2P,
                                              const T _radius2M,
                                              const T _radius3P,
                                              const T _radius3M,
                                              const std::vector<T> &_anglesLon,
                                              const std::vector<T> &_anglesLat)
{
    const size_t cntVertex = _anglesLon.size() * _anglesLat.size();
    const size_t offset = _anglesLat.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < cntVertex; ++i)
        {
            const Vec3<T> N1 =
                _orientation.normal2.rotated(_orientation.normal1, _anglesLon[(i / offset)]).normalized();
            const Vec3<T> N2 = _orientation.normal1.rotated(N1, _anglesLat[(i % offset)]).normalized();
            const T R1 = isNegative(N2.x) ? _radius1M : _radius1P;
            const T R2 = isNegative(N2.y) ? _radius2M : _radius2P;
            const T R3 = isNegative(N2.z) ? _radius3M : _radius3P;

            const Vec3<T> N3 = (T(2) * Vec3<T>(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();
            const Vec3<T> N4 =
                (_orientation.normal1 * N3.x + _orientation.normal2 * N3.y + _orientation.normal3 * N3.z).normalized();
            _outVertex[i] = _orientation.center + _orientation.normal1 * (N2.x * R1) +
                _orientation.normal2 * (N2.y * R2) + _orientation.normal3 * (N2.z * R3);
            _outNormal[i] = N4;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M, offset](
                    Vec3<T> *__outVertex, Vec3<T> *__outNormal, const T *__anglesLon, const T *__anglesLat) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> N1 =
                            _orientation.normal2.rotated(_orientation.normal1, __anglesLon[(i / offset)]).normalized();
                        const Vec3<T> N2 = _orientation.normal1.rotated(N1, __anglesLat[(i % offset)]).normalized();
                        const T R1 = isNegative(N2.x) ? _radius1M : _radius1P;
                        const T R2 = isNegative(N2.y) ? _radius2M : _radius2P;
                        const T R3 = isNegative(N2.z) ? _radius3M : _radius3P;

                        const Vec3<T> N3 = (T(2) * Vec3<T>(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();
                        const Vec3<T> N4 =
                            (_orientation.normal1 * N3.x + _orientation.normal2 * N3.y + _orientation.normal3 * N3.z)
                                .normalized();
                        __outVertex[i] = _orientation.center + _orientation.normal1 * (N2.x * R1) +
                            _orientation.normal2 * (N2.y * R2) + _orientation.normal3 * (N2.z * R3);
                        __outNormal[i] = N4;
                    }
                },
                _outVertex,
                _outNormal,
                _anglesLon.data(),
                _anglesLat.data()));
        for (std::thread &t : threads)
            t.join();
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(_anglesLon.size(), _anglesLat.size());

    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill irregular ellipsoid arc vertices - ellipsoid visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Ellipsoid orientation in 3D space
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidArcInner(Vec3<T> *_outVertex,
                                              Vec3<T> *_outNormal,
                                              uint *_outIndex,
                                              const Orientation<T> &_orientation,
                                              const T _radius1P,
                                              const T _radius1M,
                                              const T _radius2P,
                                              const T _radius2M,
                                              const T _radius3P,
                                              const T _radius3M,
                                              const std::vector<T> &_anglesLon,
                                              const std::vector<T> &_anglesLat)
{
    const size_t cntVertex = _anglesLon.size() * _anglesLat.size();
    const size_t offset = _anglesLat.size();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(cntVertex);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < cntVertex; ++i)
        {
            const Vec3<T> N1 =
                _orientation.normal2.rotated(_orientation.normal1, _anglesLon[(i / offset)]).normalized();
            const Vec3<T> N2 = _orientation.normal1.rotated(N1, _anglesLat[(i % offset)]).normalized();
            const T R1 = isNegative(N2.x) ? _radius1M : _radius1P;
            const T R2 = isNegative(N2.y) ? _radius2M : _radius2P;
            const T R3 = isNegative(N2.z) ? _radius3M : _radius3P;

            const Vec3<T> N3 = (T(2) * Vec3<T>(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();
            const Vec3<T> N4 =
                (_orientation.normal1 * N3.x + _orientation.normal2 * N3.y + _orientation.normal3 * N3.z).normalized();
            _outVertex[i] = _orientation.center + _orientation.normal1 * (N2.x * R1) +
                _orientation.normal2 * (N2.y * R2) + _orientation.normal3 * (N2.z * R3);
            _outNormal[i] = -N4;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _radius3P, _radius3M, offset](
                    Vec3<T> *__outVertex, Vec3<T> *__outNormal, const T *__anglesLon, const T *__anglesLat) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> N1 =
                            _orientation.normal2.rotated(_orientation.normal1, __anglesLon[(i / offset)]).normalized();
                        const Vec3<T> N2 = _orientation.normal1.rotated(N1, __anglesLat[(i % offset)]).normalized();
                        const T R1 = isNegative(N2.x) ? _radius1M : _radius1P;
                        const T R2 = isNegative(N2.y) ? _radius2M : _radius2P;
                        const T R3 = isNegative(N2.z) ? _radius3M : _radius3P;

                        const Vec3<T> N3 = (T(2) * Vec3<T>(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();
                        const Vec3<T> N4 =
                            (_orientation.normal1 * N3.x + _orientation.normal2 * N3.y + _orientation.normal3 * N3.z)
                                .normalized();
                        __outVertex[i] = _orientation.center + _orientation.normal1 * (N2.x * R1) +
                            _orientation.normal2 * (N2.y * R2) + _orientation.normal3 * (N2.z * R3);
                        __outNormal[i] = -N4;
                    }
                },
                _outVertex,
                _outNormal,
                _anglesLon.data(),
                _anglesLat.data()));
        for (std::thread &t : threads)
            t.join();
    }

    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(_anglesLon.size(), _anglesLat.size());

    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill irregular ellipsoid arc vertices - ellipsoid visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Ellipsoid center point
 * \param _normal Ellipsoid plane normal
 * \param _arm Ellipsoid start arm
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidArcOuter(Vec3<T> *_outVertex,
                                              Vec3<T> *_outNormal,
                                              uint *_outIndex,
                                              const Vec3<T> &_center,
                                              const Vec3<T> &_normal,
                                              const Vec3<T> &_arm,
                                              const T _radius1P,
                                              const T _radius1M,
                                              const T _radius2P,
                                              const T _radius2M,
                                              const T _radius3P,
                                              const T _radius3M,
                                              const std::vector<T> &_anglesLon,
                                              const std::vector<T> &_anglesLat)
{
    fillEllipsoidArcOuter(_outVertex,
                          _outNormal,
                          _outIndex,
                          Orientation<T>(_center, _normal, _arm),
                          _radius1P,
                          _radius1M,
                          _radius2P,
                          _radius2M,
                          _radius3P,
                          _radius3M,
                          _anglesLon,
                          _anglesLat);
}

/*!
 * \brief Fill irregular ellipsoid arc vertices - ellipsoid visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Ellipsoid center point
 * \param _normal Ellipsoid plane normal
 * \param _arm Ellipsoid start arm
 * \param _radius1P Ellipsoid radius in normal 1 direction
 * \param _radius1M Ellipsoid radius in normal 1 inverted direction
 * \param _radius2P Ellipsoid radius in normal 2 direction
 * \param _radius2M Ellipsoid radius in normal 2 inverted direction
 * \param _radius3P Ellipsoid radius in normal 3 direction
 * \param _radius3M Ellipsoid radius in normal 3 inverted direction
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void IrregEllipsoid<T>::fillEllipsoidArcInner(Vec3<T> *_outVertex,
                                              Vec3<T> *_outNormal,
                                              uint *_outIndex,
                                              const Vec3<T> &_center,
                                              const Vec3<T> &_normal,
                                              const Vec3<T> &_arm,
                                              const T _radius1P,
                                              const T _radius1M,
                                              const T _radius2P,
                                              const T _radius2M,
                                              const T _radius3P,
                                              const T _radius3M,
                                              const std::vector<T> &_anglesLon,
                                              const std::vector<T> &_anglesLat)
{
    fillEllipsoidArcInner(_outVertex,
                          _outNormal,
                          _outIndex,
                          Orientation<T>(_center, _normal, _arm),
                          _radius1P,
                          _radius1M,
                          _radius2P,
                          _radius2M,
                          _radius3P,
                          _radius3M,
                          _anglesLon,
                          _anglesLat);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef IrregEllipsoid<float> IrregEllipsoidF;        //!< 32 bit floating point precision irregular ellipsoid
typedef IrregEllipsoid<double> IrregEllipsoidD;       //!< 64 bit floating point precision irregular ellipsoid
typedef IrregEllipsoid<long double> IrregEllipsoidL;  //!< 128 bit floating point precision irregular ellipsoid

}  // namespace Math
}  // namespace U1

#endif  // MATH_IRREGELLIPSOID_H
