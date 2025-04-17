/*!
 * \file src/Math/sphere.h
 * \brief 3D sphere structure
 */

#ifndef MATH_SPHERE_H
#define MATH_SPHERE_H

#include "orientation.h"
#include "planeindices.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D Sphere representation
 * \tparam T Template floating point type
 */
template <typename T>
struct Sphere
{
 private:
    /*! \brief Unit sphere cache */
    static std::map<size_t, std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>>> m_unitSpheres;

 public:
    Vec3<T> center;    //!< Sphere position
    T radius;          //!< Sphere radius

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere()
        : center()
        , radius(T(0))
    {
    }

    /*!
     * \brief Constructor with sphere components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere(const T _x,  //!< X component
                  const T _y,  //!< Y component
                  const T _z,  //!< Z component
                  const T _r)  //!< Radius component
        : center(_x, _y, _z)
        , radius(_r)
    {
    }

    /*!
     * \brief Constructor with sphere components
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Sphere(const Vec3<T> &_center,  //!< Position component
                  const T _radius = T(1))  //!< Radius component
        : center(_center)
        , radius(_radius)
    {
    }

    inline void reset(const T _radius, const Vec3<T> &_position);

    inline bool isNull() const;
    inline bool isValid() const;

    inline bool equals(const Sphere<T> &_other) const;
    inline bool operator==(const Sphere<T> &_other) const;
    inline bool operator!=(const Sphere<T> &_other) const;

    inline void clear();

    inline T surfaceArea() const;
    inline T circleArea() const;

    inline T volume() const;
    inline T volumeCup(const T _height) const;

    std::vector<Vec3<T>> lineIntersections(const Vec3<T> &_linePoint, const Vec3<T> &_lineNormal) const;

    static const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &
    unitSphere(const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Sphere vertex count by circle quality
     * \param _quality Circle quality
     * \return Sphere vertex count
     */
    inline static size_t sphereVertexCount(const size_t _quality)
    {
        const size_t cntCircle = circlePointCount(_quality);
        const size_t cntLon = cntCircle;
        const size_t cntLat = cntCircle / 2UL;
        return (cntLon + 1UL) * (cntLat + 1UL);
    }

    /*!
     * \brief Sphere index count by circle quality
     * \param _quality Circle quality
     * \return Sphere index count
     */
    inline static size_t sphereIndexCount(const size_t _quality)
    {
        const size_t cntCircle = circlePointCount(_quality);
        const size_t cntLon = cntCircle;
        const size_t cntLat = cntCircle / 2UL;
        return cntLon * cntLat * 4UL;
    }

    /*!
     * \brief Sphere step angle for given circle quality
     * \param _quality Circle quality
     * \return Sphere step angle in radians
     */
    inline static size_t sphereStepAngle(const size_t _quality)
    {
        return T(2.0l * M_PIl) / T(circlePointCount(_quality));
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillSphereOuter(Vec3<T> *_outVertex,
                                Vec3<T> *_outNormal,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
                                const size_t _quality);

    static void fillSphereInner(Vec3<T> *_outVertex,
                                Vec3<T> *_outNormal,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
                                const size_t _quality);

    inline static void fillSphereOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radius,
                                       const size_t _quality);

    inline static void fillSphereInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radius,
                                       const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillSphereOuter(Vec3<T> *_outVertex,
                                Vec2<T> *_outCoords,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
                                const size_t _quality);

    static void fillSphereInner(Vec3<T> *_outVertex,
                                Vec2<T> *_outCoords,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
                                const size_t _quality);

    inline static void fillSphereOuter(Vec3<T> *_outVertex,
                                       Vec2<T> *_outCoords,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radius,
                                       const size_t _quality);

    inline static void fillSphereInner(Vec3<T> *_outVertex,
                                       Vec2<T> *_outCoords,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radius,
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

    static void fillSphereArcOuter(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius,
                                   const std::vector<T> &_anglesLon,
                                   const std::vector<T> &_anglesLat);

    static void fillSphereArcInner(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius,
                                   const std::vector<T> &_anglesLon,
                                   const std::vector<T> &_anglesLat);

    inline static void fillSphereArcOuter(Vec3<T> *_outVertex,
                                          Vec3<T> *_outNormal,
                                          uint *_outIndex,
                                          const Vec3<T> &_center,
                                          const Vec3<T> &_normal,
                                          const Vec3<T> &_arm,
                                          const T _radius,
                                          const std::vector<T> &_anglesLon,
                                          const std::vector<T> &_anglesLat);

    inline static void fillSphereArcInner(Vec3<T> *_outVertex,
                                          Vec3<T> *_outNormal,
                                          uint *_outIndex,
                                          const Vec3<T> &_center,
                                          const Vec3<T> &_normal,
                                          const Vec3<T> &_arm,
                                          const T _radius,
                                          const std::vector<T> &_anglesLon,
                                          const std::vector<T> &_anglesLat);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Reset sphere properties
 * \tparam T Template floating point type
 * \param _radius New radius
 * \param _position New position
 */
template <typename T>
inline void Sphere<T>::reset(const T _radius, const Vec3<T> &_position)
{
    radius = _radius;
    center = _position;
}

/*!
 * \brief Test if sphere is null (only radius must be null)
 * \tparam T Template floating point type
 * \return \c true if sphere is null
 */
template <typename T>
inline bool Sphere<T>::isNull() const
{
    return Math::isNull<T>(radius);
}

/*!
 * \brief Test if sphere is valid (only radius must be not null and positive)
 * \tparam T Template floating point type
 * \return \c true if sphere is valid
 */
template <typename T>
inline bool Sphere<T>::isValid() const
{
    return isPositive<T>(radius);
}

/*!
 * \brief Test if spheres are equal
 * \tparam T Template floating point type
 * \param _other Other sphere
 * \return \c true if spheres are equal
 * \sa TypeEquals<T>(const T, const T)
 */
template <typename T>
inline bool Sphere<T>::equals(const Sphere<T> &_other) const
{
    return Math::equals<T>(radius, _other.radius) && center.equals(_other.center);
}

/*!
 * \brief Operator for test if spheres are equal
 * \tparam T Template floating point type
 * \param _other Other sphere
 * \return \c true if spheres are equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Sphere<T>::operator==(const Sphere<T> &_other) const
{
    return equals(_other);
}

/*!
 * \brief Operator for test if spheres are not equal
 * \tparam T Template floating point type
 * \param _other Other sphere
 * \return \c true if spheres are not equal
 * \sa Vec3<T>::equals<T>(const Vec3<T>&)
 */
template <typename T>
inline bool Sphere<T>::operator!=(const Sphere<T> &_other) const
{
    return !equals(_other);
}

/*!
 * \brief Clear sphere
 * \tparam T Template floating point type
 */
template <typename T>
inline void Sphere<T>::clear()
{
    radius = T(0);
    center.clear();
}

/*!
 * \brief Returns sphere surface area \f$4 \pi r^2\f$
 * \tparam T Template floating point type
 * \return Sphere surface area
 */
template <typename T>
inline T Sphere<T>::surfaceArea() const
{
    return T(4.0l * M_PIl) * radius * radius;
}

/*!
 * \brief Returns sphere circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Sphere circle area
 */
template <typename T>
inline T Sphere<T>::circleArea() const
{
    return T(M_PIl) * radius * radius;
}

/*!
 * \brief Returns sphere circle area \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volume() const
{
    return T(M_PIl * 4.0l / 3.0l) * radius * radius * radius;
}

/*!
 * \brief Returns sphere volume cup area \f$\frac{4}{3} \pi r^3\f$
 * \tparam T Template floating point type
 * \param _height Cup height
 * \return Sphere volume
 */
template <typename T>
inline T Sphere<T>::volumeCup(const T _height) const
{
    return T(M_PIl) * _height * _height * (T(3) * radius - _height) / T(3);
}

/*!
 * \brief Sphere line intersections
 * \param _linePoint Line point
 * \param _lineNormal Line normal
 * \return Intersection points
 */
template <typename T>
std::vector<Vec3<T>> Sphere<T>::lineIntersections(const Vec3<T> &_linePoint, const Vec3<T> &_lineNormal) const
{
    const Vec3<T> v = _lineNormal.normalized();
    const T A = Vec3<T>::dot(v, v);
    const T B = T(2) *
        (_linePoint.x * v.x + _linePoint.y * v.y + _linePoint.z * v.z - v.x * center.x - v.y * center.y -
         v.z * center.z);
    const T C = _linePoint.x * _linePoint.x - T(2) * _linePoint.x * center.x + center.x * center.x +
        _linePoint.y * _linePoint.y - T(2) * _linePoint.y * center.y + center.y * center.y +
        _linePoint.z * _linePoint.z - 2 * _linePoint.z * center.z + center.z * center.z - radius * radius;

    const T D = B * B - T(4) * A * C;
    if (Math::isNull(D))
        return {_linePoint + v * (-B / (T(2) * A))};
    else if (D < T(0))
        return {};

    const T SD = std::sqrt(D);
    const T t1 = (-B - SD) / (T(2) * A);
    const T t2 = (-B + SD) / (T(2) * A);

    if (isMoreOrEqual(t1, t2))
        return {_linePoint + v * t1, _linePoint + v * t2};
    return {_linePoint + v * t2, _linePoint + v * t1};
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sphere vertices by circle quality
 * \tparam T Template floating point type
 * \param _quality Circle quality
 * \return Sphere vertices
 * \note Point count equation \f$A = 4 \times (Q + 1); N = (A + 1) \times (\frac{A}{2} + 1)\f$
 * \sa circlePointCount(const size_t)
 */
template <typename T>
const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &
Sphere<T>::unitSphere(const size_t _quality)
{
    typename std::map<size_t, std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>>>::iterator it =
        m_unitSpheres.find(_quality);
    if (it == m_unitSpheres.end())
    {
        it = m_unitSpheres.insert({_quality, {std::vector<Vec3<T>>(), std::vector<std::pair<size_t, size_t>>()}}).first;

        std::vector<Vec3<T>> &vertex = (*it).second.first;
        std::vector<std::pair<size_t, size_t>> &pool = (*it).second.second;

        static const Vec3<T> N1 = Vec3<T>::unitX();
        static const Vec3<T> N2 = Vec3<T>::unitY();

        const size_t cntCircle = circlePointCount(_quality);
        const size_t cntLon = cntCircle;
        const size_t cntLat = cntCircle / 2UL;
        const size_t cntVertex = (cntLon + 1UL) * (cntLat + 1UL);
        const size_t offset = (cntLat + 1UL);
        const T stepRad = T(2.0l * M_PIl) / T(cntCircle);
        pool = createPool(cntVertex);
        vertex.resize(cntVertex);

        if (pool.empty())
        {
            for (size_t i = 0UL; i < cntVertex; ++i)
            {
                const Vec3<T> N3 = N2.rotated(N1, float(i / offset) * stepRad).normalized();
                vertex[i] = N1.rotated(N3, float(i % offset) * stepRad).normalized();
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, stepRad](Vec3<T> *__out) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec3<T> N3 = N2.rotated(N1, float(i / offset) * stepRad).normalized();
                            __out[i] = N1.rotated(N3, float(i % offset) * stepRad).normalized();
                        }
                    },
                    vertex.data()));
            for (std::thread &t : threads)
                t.join();
        }
    }

    return (*it).second;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill sphere vertices - sphere visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Sphere orientation in 3D space
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereOuter(Vec3<T> *_outVertex,
                                Vec3<T> *_outNormal,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
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
            const Vec3<T> N =
                (_orientation.normal1 * N0.x + _orientation.normal2 * N0.y + _orientation.normal3 * N0.z).normalized();
            _outVertex[i] = _orientation.center + N * _radius;
            _outNormal[i] = N;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius](Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec3<T> *_data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> &N0 = _data[i];
                        const Vec3<T> N =
                            (_orientation.normal1 * N0.x + _orientation.normal2 * N0.y + _orientation.normal3 * N0.z)
                                .normalized();
                        __outVertex[i] = _orientation.center + N * _radius;
                        __outNormal[i] = N;
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
 * \brief Fill sphere vertices - sphere visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Sphere orientation in 3D space
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereInner(Vec3<T> *_outVertex,
                                Vec3<T> *_outNormal,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
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
            const Vec3<T> N =
                (_orientation.normal1 * N0.x + _orientation.normal2 * N0.y + _orientation.normal3 * N0.z).normalized();
            _outVertex[i] = _orientation.center + N * _radius;
            _outNormal[i] = -N;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius](Vec3<T> *__outVertex, Vec3<T> *__outNormal, const Vec3<T> *_data) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> &N0 = _data[i];
                        const Vec3<T> N =
                            (_orientation.normal1 * N0.x + _orientation.normal2 * N0.y + _orientation.normal3 * N0.z)
                                .normalized();
                        __outVertex[i] = _orientation.center + N * _radius;
                        __outNormal[i] = -N;
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
 * \brief Fill sphere vertices - sphere visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Sphere center point
 * \param _normal Sphere plane normal
 * \param _arm Sphere start arm
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void Sphere<T>::fillSphereOuter(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radius,
                                       const size_t _quality)
{
    fillSphereOuter(_outVertex, _outNormal, _outIndex, Orientation<T>(_center, _normal, _arm), _radius, _quality);
}

/*!
 * \brief Fill sphere vertices - sphere visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Sphere center point
 * \param _normal Sphere plane normal
 * \param _arm Sphere start arm
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void Sphere<T>::fillSphereInner(Vec3<T> *_outVertex,
                                       Vec3<T> *_outNormal,
                                       uint *_outIndex,
                                       const Vec3<T> &_center,
                                       const Vec3<T> &_normal,
                                       const Vec3<T> &_arm,
                                       const T _radius,
                                       const size_t _quality)
{
    fillSphereInner(_outVertex, _outNormal, _outIndex, Orientation<T>(_center, _normal, _arm), _radius, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill sphere vertices - sphere visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outIndex Output index array
 * \param _orientation Sphere orientation in 3D space
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereOuter(Vec3<T> *_outVertex,
                                Vec2<T> *_outCoords,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
                                const size_t _quality)
{
    const size_t cntCircle = circlePointCount(_quality);
    const size_t cntLon = cntCircle;
    const size_t cntLat = cntCircle / 2UL;

    const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &us = Sphere<T>::unitSphere(_quality);
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        PlaneCoords<T>::getCoords(cntLon + 1UL, cntLat + 1UL);
    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexes(cntLon + 1UL, cntLat + 1UL);

    _orientation.transformPoints(_outVertex, us.first.data(), _radius, us.first.size(), us.second);
    copyData<Vec2<T>, size_t>(_outCoords, uc.first.data(), uc.first.size(), uc.second);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill sphere vertices - sphere visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outIndex Output index array
 * \param _orientation Sphere orientation in 3D space
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereInner(Vec3<T> *_outVertex,
                                Vec2<T> *_outCoords,
                                uint *_outIndex,
                                const Orientation<T> &_orientation,
                                const T _radius,
                                const size_t _quality)
{
    const size_t cntCircle = circlePointCount(_quality);
    const size_t cntLon = cntCircle;
    const size_t cntLat = cntCircle / 2UL;

    const std::pair<std::vector<Vec3<T>>, std::vector<std::pair<size_t, size_t>>> &us = Sphere<T>::unitSphere(_quality);
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        PlaneCoords<T>::getCoords(cntLon + 1UL, cntLat + 1UL);
    const std::pair<std::vector<uint>, std::vector<std::pair<size_t, size_t>>> &ui =
        PlaneIndices::getQuadIndexesInverted(cntLon + 1UL, cntLat + 1UL);

    _orientation.transformPoints(_outVertex, us.first.data(), _radius, us.first.size(), us.second);
    copyData<Vec2<T>, size_t>(_outCoords, uc.first.data(), uc.first.size(), uc.second);
    copyData<uint, size_t>(_outIndex, ui.first.data(), ui.first.size(), ui.second);
}

/*!
 * \brief Fill sphere vertices - sphere visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outIndex Output index array
 * \param _center Sphere center point
 * \param _normal Sphere plane normal
 * \param _arm Sphere start arm
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereOuter(Vec3<T> *_outVertex,
                                Vec2<T> *_outCoords,
                                uint *_outIndex,
                                const Vec3<T> &_center,
                                const Vec3<T> &_normal,
                                const Vec3<T> &_arm,
                                const T _radius,
                                const size_t _quality)
{
    fillSphereOuter(_outVertex, _outCoords, _outIndex, Orientation<T>(_center, _normal, _arm), _radius, _quality);
}

/*!
 * \brief Fill sphere vertices - sphere visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outIndex Output index array
 * \param _center Sphere center point
 * \param _normal Sphere plane normal
 * \param _arm Sphere start arm
 * \param _radius Sphere radius
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereInner(Vec3<T> *_outVertex,
                                Vec2<T> *_outCoords,
                                uint *_outIndex,
                                const Vec3<T> &_center,
                                const Vec3<T> &_normal,
                                const Vec3<T> &_arm,
                                const T _radius,
                                const size_t _quality)
{
    fillSphereInner(_outVertex, _outCoords, _outIndex, Orientation<T>(_center, _normal, _arm), _radius, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create sphere arc angles for longitudes and latitudes, aligned with circle quality
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
void Sphere<T>::arcAngles(std::vector<T> &_outLon,
                          std::vector<T> &_outLat,
                          const T _angleLonStart,
                          const T _angleLonEnd,
                          const T _angleLatStart,
                          const T _angleLatEnd,
                          const size_t _quality)
{
    static const T _2PI = T(2.0l * M_PIl);
    static const T _PI = T(M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));

    if (isMoreOrEqual(std::fabs(_angleLonEnd - _angleLonStart), _2PI))
        fillAlignedSteps<T>(_outLon, T(0), _2PI, angle);
    else
        fillAlignedSteps<T>(_outLon, _angleLonStart, _angleLonEnd, angle);

    if (isMoreOrEqual(std::fabs(_angleLatEnd - _angleLatStart), _PI))
        fillAlignedSteps<T>(_outLat, T(0), _PI, angle);
    else
        fillAlignedSteps<T>(_outLat, _angleLatStart, _angleLatEnd, angle);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill sphere arc vertices - sphere visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Sphere orientation in 3D space
 * \param _radius Sphere radius
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereArcOuter(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius,
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
            const Vec3<T> N = _orientation.normal1.rotated(N1, _anglesLat[(i % offset)]).normalized();
            _outVertex[i] = _orientation.center + N * _radius;
            _outNormal[i] = N;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, offset](
                    Vec3<T> *__outVertex, Vec3<T> *__outNormal, const T *__anglesLon, const T *__anglesLat) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> N1 =
                            _orientation.normal2.rotated(_orientation.normal1, __anglesLon[(i / offset)]).normalized();
                        const Vec3<T> N = _orientation.normal1.rotated(N1, __anglesLat[(i % offset)]).normalized();
                        __outVertex[i] = _orientation.center + N * _radius;
                        __outNormal[i] = N;
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
 * \brief Fill sphere arc vertices - sphere visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _orientation Sphere orientation in 3D space
 * \param _radius Sphere radius
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereArcInner(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Orientation<T> &_orientation,
                                   const T _radius,
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
            const Vec3<T> N = _orientation.normal1.rotated(N1, _anglesLat[(i % offset)]).normalized();
            _outVertex[i] = _orientation.center + N * _radius;
            _outNormal[i] = -N;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, offset](
                    Vec3<T> *__outVertex, Vec3<T> *__outNormal, const T *__anglesLon, const T *__anglesLat) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec3<T> N1 =
                            _orientation.normal2.rotated(_orientation.normal1, __anglesLon[(i / offset)]).normalized();
                        const Vec3<T> N = _orientation.normal1.rotated(N1, __anglesLat[(i % offset)]).normalized();
                        __outVertex[i] = _orientation.center + N * _radius;
                        __outNormal[i] = -N;
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
 * \brief Fill sphere arc vertices - sphere visible from outside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Sphere center point
 * \param _normal Sphere plane normal
 * \param _arm Sphere start arm
 * \param _radius Sphere radius
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereArcOuter(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _radius,
                                   const std::vector<T> &_anglesLon,
                                   const std::vector<T> &_anglesLat)
{
    fillSphereArcOuter(
        _outVertex, _outNormal, _outIndex, Orientation<T>(_center, _normal, _arm), _radius, _anglesLon, _anglesLat);
}

/*!
 * \brief Fill sphere arc vertices - sphere visible from inside
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outNormal Output normal array
 * \param _outIndex Output index array
 * \param _center Sphere center point
 * \param _normal Sphere plane normal
 * \param _arm Sphere start arm
 * \param _radius Sphere radius
 * \param _anglesLon Longitudes angles
 * \param _anglesLat Latitude angles
 * \return
 */
template <typename T>
void Sphere<T>::fillSphereArcInner(Vec3<T> *_outVertex,
                                   Vec3<T> *_outNormal,
                                   uint *_outIndex,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _radius,
                                   const std::vector<T> &_anglesLon,
                                   const std::vector<T> &_anglesLat)
{
    fillSphereArcInner(
        _outVertex, _outNormal, _outIndex, Orientation<T>(_center, _normal, _arm), _radius, _anglesLon, _anglesLat);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _s Sphere
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Sphere<T> &_s)
{
    return _os << "[R[" << _s.radius << ']' << _s.center << ']';
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Sphere<float> SphereF;        //!< 32 bit floating point precision sphere
typedef Sphere<double> SphereD;       //!< 64 bit floating point precision sphere
typedef Sphere<long double> SphereL;  //!< 128 bit floating point precision sphere

}  // namespace Math
}  // namespace U1

#endif  // MATH_SPHERE_H
