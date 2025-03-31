/*!
 * \file src/Math/circle.h
 * \brief 2D and 3D circle structure
 */

#ifndef MATH_CIRCLE_H
#define MATH_CIRCLE_H

#include "vec3.h"
#include "multithread.h"
#include "orientation.h"

#include <map>

namespace U1 {
namespace Math {

/*!
 * \brief 2D circle structure
 * \tparam T Template floating point type
 */
template <typename T>
struct Circle2
{
 private:
    /*! \brief  Unit 2D circle cache */
    static std::map<size_t, std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>>> m_unitCircles;

 public:
    Vec2<T> center;  //!< Circle center
    T radius;        //!< Circle radius

    /*! \brief Default constructor */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle2()
        : center()
        , radius(T(0))
    {
    }

    /*! \brief Constructor with circle components */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle2(const Vec2<T> &_center,  //!< Circle center
                   const T &_radius)        //!< Circle radius
        : center(_center)
        , radius(_radius)
    {
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return Math::mixHash(center.toHash(), std::hash<T>{}(radius));
    }

    inline bool isValid() const;

    inline void clear();

    inline T circumference() const;
    inline T area() const;

    inline Vec2<T> arm() const;

    Vec2<T> point(const T _angleRad) const;

    static const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &
    unitCircle(const size_t _quality);

    inline static void arcAngles(std::vector<T> &_out, const T _angleStart, const T _angleEnd, const size_t _quality);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief 3D circle structure
 * \tparam T Template floating point type
 */
template <typename T>
struct Circle3
{
    Vec3<T> center;    //!< Circle center
    Vec3<T> normal;    //!< Circle normal (unit 3D vector)
    T radius;          //!< Circle radius

    /*! \brief Default constructor */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle3()
        : center()
        , normal()
        , radius(T(0))
    {
    }

    /*! \brief Constructor with circle components */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Circle3(const Vec3<T> &_center,  //!< Circle center
                   const Vec3<T> &_normal,  //!< Circle normal (unit 3D vector)
                   const T &_radius)        //!< Circle radius
        : center(_center)
        , normal(_normal)
        , radius(_radius)
    {
    }

    /*!
     * \brief Calculate hash value
     * \return Hash value from data
     */
    inline size_t toHash() const
    {
        return Math::mixHash(center.toHash(), normal.toHash(), std::hash<T>{}(radius));
    }

    inline bool isValid() const;

    inline void clear();

    inline T circumference() const;
    inline T area() const;

    inline Vec3<T> arm() const;

    Vec3<T> point(const T _angleRad) const;

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Circle vertex count by circle quality
     * \param _quality Circle quality
     * \return Circle vertex count
     * \sa circlePointCount(const size_t)
     */
    inline static size_t circleVertexCount(const size_t _quality)
    {
        return circlePointCount(_quality);
    }

    /*!
     * \brief Circle vertex count by circle quality
     * \param _quality Circle quality
     * \return Circle vertex count
     * \details Circle vertex count includes 2 pints: center point and loop-enclosing point
     * \sa circlePointCount(const size_t)
     */
    inline static size_t circleCenterVertexCount(const size_t _quality)
    {
        return circlePointCount(_quality) + 2UL;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void
    fillCircle(Vec3<T> *_outVertex, const Orientation<T> &_orientation, const T _radius, const size_t _quality);

    inline static void fillCircle(Vec3<T> *_outVertex,
                                  const Vec3<T> &_center,
                                  const Vec3<T> &_normal,
                                  const Vec3<T> &_arm,
                                  const T _radius,
                                  const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircle(Vec3<T> *_outVertex,
                           T *_outAlpha,
                           const Orientation<T> &_orientation,
                           const T _alphaCenter,
                           const T _alphaBorder,
                           const T _radius,
                           const size_t _quality);

    inline static void fillCircle(Vec3<T> *_outVertex,
                                  T *_outAlpha,
                                  const Vec3<T> &_center,
                                  const Vec3<T> &_normal,
                                  const Vec3<T> &_arm,
                                  const T _alphaCenter,
                                  const T _alphaBorder,
                                  const T _radius,
                                  const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircle(Vec3<T> *_outVertex,
                           Vec2<T> *_outCoords,
                           const Orientation<T> &_orientation,
                           const T _radius,
                           const size_t _quality);

    inline static void fillCircle(Vec3<T> *_outVertex,
                                  Vec2<T> *_outCoords,
                                  const Vec3<T> &_center,
                                  const Vec3<T> &_normal,
                                  const Vec3<T> &_arm,
                                  const T _radius,
                                  const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircle(Vec3<T> *_outVertex,
                           Vec2<T> *_outCoords,
                           T *_outAlpha,
                           const Orientation<T> &_orientation,
                           const T _alphaCenter,
                           const T _alphaBorder,
                           const T _radius,
                           const size_t _quality);

    inline static void fillCircle(Vec3<T> *_outVertex,
                                  Vec2<T> *_outCoords,
                                  T *_outAlpha,
                                  const Vec3<T> &_center,
                                  const Vec3<T> &_normal,
                                  const Vec3<T> &_arm,
                                  const T _alphaCenter,
                                  const T _alphaBorder,
                                  const T _radius,
                                  const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircle(Vec3<T> *_outVertex,
                           Vec3<T> *_outAmbient,
                           Vec3<T> *_outDiffuse,
                           Vec3<T> *_outSpecular,
                           T *_outShine,
                           const Orientation<T> &_orientation,
                           const Vec3<T> &_ambientCenter,
                           const Vec3<T> &_ambientBorder,
                           const Vec3<T> &_diffuseCenter,
                           const Vec3<T> &_diffuseBorder,
                           const Vec3<T> &_specularCenter,
                           const Vec3<T> &_specularBorder,
                           const T _shineCenter,
                           const T _shineBorder,
                           const T _radius,
                           const size_t _quality);

    inline static void fillCircle(Vec3<T> *_outVertex,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  const Vec3<T> &_center,
                                  const Vec3<T> &_normal,
                                  const Vec3<T> &_arm,
                                  const Vec3<T> &_ambientCenter,
                                  const Vec3<T> &_ambientBorder,
                                  const Vec3<T> &_diffuseCenter,
                                  const Vec3<T> &_diffuseBorder,
                                  const Vec3<T> &_specularCenter,
                                  const Vec3<T> &_specularBorder,
                                  const T _shineCenter,
                                  const T _shineBorder,
                                  const T _radius,
                                  const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircle(Vec3<T> *_outVertex,
                           Vec3<T> *_outAmbient,
                           Vec3<T> *_outDiffuse,
                           Vec3<T> *_outSpecular,
                           T *_outShine,
                           T *_outAlpha,
                           const Orientation<T> &_orientation,
                           const Vec3<T> &_ambientCenter,
                           const Vec3<T> &_ambientBorder,
                           const Vec3<T> &_diffuseCenter,
                           const Vec3<T> &_diffuseBorder,
                           const Vec3<T> &_specularCenter,
                           const Vec3<T> &_specularBorder,
                           const T _shineCenter,
                           const T _shineBorder,
                           const T _alphaCenter,
                           const T _alphaBorder,
                           const T _radius,
                           const size_t _quality);

    inline static void fillCircle(Vec3<T> *_outVertex,
                                  Vec3<T> *_outAmbient,
                                  Vec3<T> *_outDiffuse,
                                  Vec3<T> *_outSpecular,
                                  T *_outShine,
                                  T *_outAlpha,
                                  const Vec3<T> &_center,
                                  const Vec3<T> &_normal,
                                  const Vec3<T> &_arm,
                                  const Vec3<T> &_ambientCenter,
                                  const Vec3<T> &_ambientBorder,
                                  const Vec3<T> &_diffuseCenter,
                                  const Vec3<T> &_diffuseBorder,
                                  const Vec3<T> &_specularCenter,
                                  const Vec3<T> &_specularBorder,
                                  const T _shineCenter,
                                  const T _shineBorder,
                                  const T _alphaCenter,
                                  const T _alphaBorder,
                                  const T _radius,
                                  const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline static void arcAngles(std::vector<T> &_out, const T _angleStart, const T _angleEnd, const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircleArc(Vec3<T> *_outVertex,
                              const Orientation<T> &_orientation,
                              const T _radius,
                              const std::vector<T> &_angles);

    inline static void fillCircleArc(Vec3<T> *_outVertex,
                                     const Vec3<T> &_center,
                                     const Vec3<T> &_normal,
                                     const Vec3<T> &_arm,
                                     const T _radius,
                                     const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircleArc(Vec3<T> *_outVertex,
                              T *_outAlpha,
                              const Orientation<T> &_orientation,
                              const T _alphaCenter,
                              const T _alphaBorder,
                              const T _radius,
                              const std::vector<T> &_angles);

    inline static void fillCircleArc(Vec3<T> *_outVertex,
                                     T *_outAlpha,
                                     const Vec3<T> &_center,
                                     const Vec3<T> &_normal,
                                     const Vec3<T> &_arm,
                                     const T _alphaCenter,
                                     const T _alphaBorder,
                                     const T _radius,
                                     const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircleArc(Vec3<T> *_outVertex,
                              Vec2<T> *_outCoords,
                              const Orientation<T> &_orientation,
                              const T _radius,
                              const std::vector<T> &_angles);

    inline static void fillCircleArc(Vec3<T> *_outVertex,
                                     Vec2<T> *_outCoords,
                                     const Vec3<T> &_center,
                                     const Vec3<T> &_normal,
                                     const Vec3<T> &_arm,
                                     const T _radius,
                                     const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircleArc(Vec3<T> *_outVertex,
                              Vec2<T> *_outCoords,
                              T *_outAlpha,
                              const Orientation<T> &_orientation,
                              const T _alphaCenter,
                              const T _alphaBorder,
                              const T _radius,
                              const std::vector<T> &_angles);

    inline static void fillCircleArc(Vec3<T> *_outVertex,
                                     Vec2<T> *_outCoords,
                                     T *_outAlpha,
                                     const Vec3<T> &_center,
                                     const Vec3<T> &_normal,
                                     const Vec3<T> &_arm,
                                     const T _alphaCenter,
                                     const T _alphaBorder,
                                     const T _radius,
                                     const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircleArc(Vec3<T> *_outVertex,
                              Vec3<T> *_outAmbient,
                              Vec3<T> *_outDiffuse,
                              Vec3<T> *_outSpecular,
                              T *_outShine,
                              const Orientation<T> &_orientation,
                              const Vec3<T> &_ambientCenter,
                              const Vec3<T> &_ambientBorder,
                              const Vec3<T> &_diffuseCenter,
                              const Vec3<T> &_diffuseBorder,
                              const Vec3<T> &_specularCenter,
                              const Vec3<T> &_specularBorder,
                              const T _shineCenter,
                              const T _shineBorder,
                              const T _radius,
                              const std::vector<T> &_angles);

    inline static void fillCircleArc(Vec3<T> *_outVertex,
                                     Vec3<T> *_outAmbient,
                                     Vec3<T> *_outDiffuse,
                                     Vec3<T> *_outSpecular,
                                     T *_outShine,
                                     const Vec3<T> &_center,
                                     const Vec3<T> &_normal,
                                     const Vec3<T> &_arm,
                                     const Vec3<T> &_ambientCenter,
                                     const Vec3<T> &_ambientBorder,
                                     const Vec3<T> &_diffuseCenter,
                                     const Vec3<T> &_diffuseBorder,
                                     const Vec3<T> &_specularCenter,
                                     const Vec3<T> &_specularBorder,
                                     const T _shineCenter,
                                     const T _shineBorder,
                                     const T _radius,
                                     const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillCircleArc(Vec3<T> *_outVertex,
                              Vec3<T> *_outAmbient,
                              Vec3<T> *_outDiffuse,
                              Vec3<T> *_outSpecular,
                              T *_outShine,
                              T *_outAlpha,
                              const Orientation<T> &_orientation,
                              const Vec3<T> &_ambientCenter,
                              const Vec3<T> &_ambientBorder,
                              const Vec3<T> &_diffuseCenter,
                              const Vec3<T> &_diffuseBorder,
                              const Vec3<T> &_specularCenter,
                              const Vec3<T> &_specularBorder,
                              const T _shineCenter,
                              const T _shineBorder,
                              const T _alphaCenter,
                              const T _alphaBorder,
                              const T _radius,
                              const std::vector<T> &_angles);

    inline static void fillCircleArc(Vec3<T> *_outVertex,
                                     Vec3<T> *_outAmbient,
                                     Vec3<T> *_outDiffuse,
                                     Vec3<T> *_outSpecular,
                                     T *_outShine,
                                     T *_outAlpha,
                                     const Vec3<T> &_center,
                                     const Vec3<T> &_normal,
                                     const Vec3<T> &_arm,
                                     const Vec3<T> &_ambientCenter,
                                     const Vec3<T> &_ambientBorder,
                                     const Vec3<T> &_diffuseCenter,
                                     const Vec3<T> &_diffuseBorder,
                                     const Vec3<T> &_specularCenter,
                                     const Vec3<T> &_specularBorder,
                                     const T _shineCenter,
                                     const T _shineBorder,
                                     const T _alphaCenter,
                                     const T _alphaBorder,
                                     const T _radius,
                                     const std::vector<T> &_angles);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test if circle is valid - has positive value of radius
 * \tparam T Template floating point type
 * \return \c true if circle is valid
 */
template <typename T>
inline bool Circle2<T>::isValid() const
{
    return Math::isPositive<T>(radius);
}

/*!
 * \brief Test if circle is valid - normal is unit vector and has positive value of radius
 * \tparam T Template floating point type
 * \return \c true if circle is valid
 */
template <typename T>
inline bool Circle3<T>::isValid() const
{
    return Math::isPositive<T>(radius) && normal.isNormalized();
}

/*!
 * \brief Clear circle
 * \tparam T Template floating point type
 */
template <typename T>
inline void Circle2<T>::clear()
{
    center.clear();
    radius = T(0);
}

/*!
 * \brief Clear circle
 * \tparam T Template floating point type
 */
template <typename T>
inline void Circle3<T>::clear()
{
    center.clear();
    normal.clear();
    radius = T(0);
}

/*!
 * \brief Returns circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle2<T>::area() const
{
    return T(M_PIl) * radius * radius;
}

/*!
 * \brief Returns circle area \f$\pi r^2\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle3<T>::area() const
{
    return T(M_PIl) * radius * radius;
}

/*!
 * \brief Returns circle area \f$2 \pi r\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle2<T>::circumference() const
{
    return T(M_PIl * 2.0l) * radius;
}

/*!
 * \brief Returns circle area \f$2 \pi r\f$
 * \tparam T Template floating point type
 * \return Circle area
 */
template <typename T>
inline T Circle3<T>::circumference() const
{
    return T(M_PIl * 2.0l) * radius;
}

/*!
 * \brief Returns base circle arm vector (unit X vector)
 * \tparam T Template floating point type
 * \return Base circle arm vector (unit X vector)
 */
template <typename T>
inline Vec2<T> Circle2<T>::arm() const
{
    return Vec2<T>::unitX();
}

/*!
 * \brief Returns base circle arm vector
 * \tparam T Template floating point type
 * \return Base circle arm vector
 * \details Circle \b arm is vector of length that equals radius and pointing to one circle curve point.
 * All circle curve points can by defined by rotating \b arm vector around \b normal vector.
 * \sa Vec3<T>::perpendicularNormal<T>() const
 */
template <typename T>
inline Vec3<T> Circle3<T>::arm() const
{
    return normal.perpendicularNormal();
}

/*!
 * \brief Returns point on circle, that is created by rotating circle \b arm by given angle
 * \tparam T Template floating point type
 * \param _angleRad Arm rotation angle in radians
 * \return Point on circle
 */
template <typename T>
Vec2<T> Circle2<T>::point(const T _angleRad) const
{
    return Vec2<T>(center.x + std::sin(_angleRad) * radius, center.y + std::cos(_angleRad) * radius);
}

/*!
 * \brief Returns point on circle, that is created by rotating circle \b arm by given angle
 * \tparam T Template floating point type
 * \param _angleRad Arm rotation angle in radians
 * \return Point on circle
 */
template <typename T>
Vec3<T> Circle3<T>::point(const T _angleRad) const
{
    return center + arm().rotated(normal, _angleRad) * radius;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief 2D circle vertices by circle quality
 * \tparam T Template floating point type
 * \param _quality Circle quality
 * \return 2D circle vertices
 * \note Point count equation \f$N = 4 \times (Q + 1)\f$
 * \sa circlePointCount(const size_t)
 */
template <typename T>
const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &
Circle2<T>::unitCircle(const size_t _quality)
{
    typename std::map<size_t, std::vector<Vec2<T>>>::iterator it = m_unitCircles.find(_quality);
    if (it == m_unitCircles.end())
    {
        it = m_unitCircles.insert({_quality, std::vector<Vec2<T>>()}).first;

        std::vector<Vec2<T>> &vertex = (*it).second.first;
        std::vector<std::pair<size_t, size_t>> &pool = (*it).second.second;

        const size_t cntVertex = circlePointCount(_quality);
        const float angle = float(2.0 * M_PI) / float(cntVertex);
        pool = createPool(cntVertex);

        if (pool.empty())
        {
            vertex.reserve(cntVertex);
            for (size_t i = 0UL; i < cntVertex; ++i)
            {
                const float a = angle * float(i);
                vertex.push_back({std::sin(a), std::cos(a)});
            }
        }
        else
        {
            vertex.resize(cntVertex);
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, angle](Vec2F *__out) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const float a = angle * float(i);
                            __out[i] = {std::sin(a), std::cos(a)};
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
 * \brief Fill circle vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _orientation Circle plane orientation in 3D space
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                            const Orientation<T> &_orientation,
                            const T _radius,
                            const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;

    if (pool.empty())
    {
        for (size_t i = 0UL; i < data2D.size(); i++)
        {
            const Vec2<T> &p2d = data2D[i];
            _outVertex[i] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius](Vec3<T> *__out, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        __out[i] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                    }
                },
                _outVertex,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _radius Circle radius
 * \param _quality Circle quality
 */

template <typename T>
inline void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _radius,
                                   const size_t _quality)
{
    fillCircle(_outVertex, Orientation<T>(_center, _normal, _arm), _radius, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle vertices - with center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _orientation Circle plane orientation in 3D space
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                            T *_outAlpha,
                            const Orientation<T> &_orientation,
                            const T _alphaCenter,
                            const T _alphaBorder,
                            const T _radius,
                            const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;
    if (pool.empty())
    {
        for (size_t i = 0UL; i < data2D.size(); i++)
        {
            const Vec2<T> &p2d = data2D[i];
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _alphaBorder](Vec3<T> *__outVertex, T *__outAlpha, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outAlpha[j] = _alphaBorder;
                    }
                },
                _outVertex,
                _outAlpha,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }

    _outVertex[0UL] = _orientation.center;
    _outAlpha[0UL] = _alphaCenter;

    const size_t last = data2D.size() + 1UL;
    _outVertex[last] = _outVertex[1UL];
    _outAlpha[last] = _alphaBorder;
}

/*!
 * \brief Fill circle vertices - with center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
inline void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                                   T *_outAlpha,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _alphaCenter,
                                   const T _alphaBorder,
                                   const T _radius,
                                   const size_t _quality)
{
    fillCircle(
        _outVertex, _outAlpha, Orientation<T>(_center, _normal, _arm), _alphaCenter, _alphaBorder, _radius, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle vertices - with texture coordinates
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _orientation Circle plane orientation in 3D space
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                            Vec2<T> *_outCoords,
                            const Orientation<T> &_orientation,
                            const T _radius,
                            const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;
    if (pool.empty())
    {
        for (size_t i = 0UL; i < data2D.size(); i++)
        {
            const Vec2<T> &p2d = data2D[i];
            _outVertex[i] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outCoords[i] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)), alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius](Vec3<T> *__outVertex, Vec2<T> *__outCoords, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        __outVertex[i] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outCoords[i] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)),
                                          alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
                    }
                },
                _outVertex,
                _outCoords,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle vertices - with texture coordinates
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
inline void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                                   Vec2<T> *_outCoords,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _radius,
                                   const size_t _quality)
{
    fillCircle(_outVertex, _outCoords, Orientation<T>(_center, _normal, _arm), _radius, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle vertices - with texture coordinates, center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _orientation Circle plane orientation in 3D space
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                            Vec2<T> *_outCoords,
                            T *_outAlpha,
                            const Orientation<T> &_orientation,
                            const T _alphaCenter,
                            const T _alphaBorder,
                            const T _radius,
                            const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;
    if (pool.empty())
    {
        for (size_t i = 0UL; i < data2D.size(); i++)
        {
            const Vec2<T> &p2d = data2D[i];
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outCoords[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)), alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _alphaBorder](
                    Vec3<T> *__outVertex, Vec2<T> *__outCoords, T *__outAlpha, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outCoords[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)),
                                          alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
                        __outAlpha[j] = _alphaBorder;
                    }
                },
                _outVertex,
                _outCoords,
                _outAlpha,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }

    _outVertex[0UL] = _orientation.center;
    _outCoords[0UL] = {T(0.5), T(0.5)};
    _outAlpha[0UL] = _alphaCenter;

    const size_t last = data2D.size() + 1UL;
    _outVertex[last] = _outVertex[1UL];
    _outCoords[last] = _outCoords[1UL];
    _outAlpha[last] = _alphaBorder;
}

/*!
 * \brief Fill circle vertices - with texture coordinates, center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
inline void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                                   Vec2<T> *_outCoords,
                                   T *_outAlpha,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _alphaCenter,
                                   const T _alphaBorder,
                                   const T _radius,
                                   const size_t _quality)
{
    fillCircle(_outVertex,
               _outCoords,
               _outAlpha,
               Orientation<T>(_center, _normal, _arm),
               _alphaCenter,
               _alphaBorder,
               _radius,
               _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle vertices - with center and border material
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _orientation Circle plane orientation in 3D space
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                            Vec3<T> *_outAmbient,
                            Vec3<T> *_outDiffuse,
                            Vec3<T> *_outSpecular,
                            T *_outShine,
                            const Orientation<T> &_orientation,
                            const Vec3<T> &_ambientCenter,
                            const Vec3<T> &_ambientBorder,
                            const Vec3<T> &_diffuseCenter,
                            const Vec3<T> &_diffuseBorder,
                            const Vec3<T> &_specularCenter,
                            const Vec3<T> &_specularBorder,
                            const T _shineCenter,
                            const T _shineBorder,
                            const T _radius,
                            const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;
    if (pool.empty())
    {
        for (size_t i = 0UL; i < data2D.size(); i++)
        {
            const size_t j = i + 1UL;
            const Vec2<T> &p2d = data2D[i];
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAmbient[j] = _ambientBorder;
            _outDiffuse[j] = _diffuseBorder;
            _outSpecular[j] = _specularBorder;
            _outShine[j] = _shineBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _ambientBorder, _diffuseBorder, _specularBorder, _shineBorder](
                    Vec3<T> *__outVertex,
                    Vec3<T> *__outAmbient,
                    Vec3<T> *__outDiffuse,
                    Vec3<T> *__outSpecular,
                    T *__outShine,
                    const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outAmbient[j] = _ambientBorder;
                        __outDiffuse[j] = _diffuseBorder;
                        __outSpecular[j] = _specularBorder;
                        __outShine[j] = _shineBorder;
                    }
                },
                _outVertex,
                _outAmbient,
                _outDiffuse,
                _outSpecular,
                _outShine,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }

    _outVertex[0UL] = _orientation.center;
    _outAmbient[0UL] = _ambientCenter;
    _outDiffuse[0UL] = _diffuseCenter;
    _outSpecular[0UL] = _specularCenter;
    _outShine[0UL] = _shineCenter;

    const size_t last = data2D.size() + 1UL;
    _outVertex[last] = _outVertex[1UL];
    _outAmbient[last] = _ambientBorder;
    _outDiffuse[last] = _diffuseBorder;
    _outSpecular[last] = _specularBorder;
    _outShine[last] = _shineBorder;
}

/*!
 * \brief Fill circle vertices - with center and border material
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
inline void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                                   Vec3<T> *_outAmbient,
                                   Vec3<T> *_outDiffuse,
                                   Vec3<T> *_outSpecular,
                                   T *_outShine,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const Vec3<T> &_ambientCenter,
                                   const Vec3<T> &_ambientBorder,
                                   const Vec3<T> &_diffuseCenter,
                                   const Vec3<T> &_diffuseBorder,
                                   const Vec3<T> &_specularCenter,
                                   const Vec3<T> &_specularBorder,
                                   const T _shineCenter,
                                   const T _shineBorder,
                                   const T _radius,
                                   const size_t _quality)
{
    fillCircle(_outVertex,
               _outAmbient,
               _outDiffuse,
               _outSpecular,
               _outShine,
               Orientation<T>(_center, _normal, _arm),
               _ambientCenter,
               _ambientBorder,
               _diffuseCenter,
               _diffuseBorder,
               _specularCenter,
               _specularBorder,
               _shineCenter,
               _shineBorder,
               _radius,
               _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle vertices - with center and border material and alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _orientation Circle plane orientation in 3D space
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                            Vec3<T> *_outAmbient,
                            Vec3<T> *_outDiffuse,
                            Vec3<T> *_outSpecular,
                            T *_outShine,
                            T *_outAlpha,
                            const Orientation<T> &_orientation,
                            const Vec3<T> &_ambientCenter,
                            const Vec3<T> &_ambientBorder,
                            const Vec3<T> &_diffuseCenter,
                            const Vec3<T> &_diffuseBorder,
                            const Vec3<T> &_specularCenter,
                            const Vec3<T> &_specularBorder,
                            const T _shineCenter,
                            const T _shineBorder,
                            const T _alphaCenter,
                            const T _alphaBorder,
                            const T _radius,
                            const size_t _quality)
{
    const std::pair<std::vector<Vec2<T>>, std::vector<std::pair<size_t, size_t>>> &uc =
        Circle2<T>::unitCircle(_quality);
    const std::vector<Vec2<T>> &data2D = uc.first;
    const std::vector<std::pair<size_t, size_t>> &pool = uc.second;
    if (pool.empty())
    {
        for (size_t i = 0UL; i < data2D.size(); i++)
        {
            const size_t j = i + 1UL;
            const Vec2<T> &p2d = data2D[i];
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAmbient[j] = _ambientBorder;
            _outDiffuse[j] = _diffuseBorder;
            _outSpecular[j] = _specularBorder;
            _outShine[j] = _shineBorder;
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _ambientBorder, _diffuseBorder, _specularBorder, _shineBorder, _alphaBorder](
                    Vec3<T> *__outVertex,
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
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outAmbient[j] = _ambientBorder;
                        __outDiffuse[j] = _diffuseBorder;
                        __outSpecular[j] = _specularBorder;
                        __outShine[j] = _shineBorder;
                        __outAlpha[j] = _alphaBorder;
                    }
                },
                _outVertex,
                _outAmbient,
                _outDiffuse,
                _outSpecular,
                _outShine,
                _outAlpha,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }

    _outVertex[0UL] = _orientation.center;
    _outAmbient[0UL] = _ambientCenter;
    _outDiffuse[0UL] = _diffuseCenter;
    _outSpecular[0UL] = _specularCenter;
    _outShine[0UL] = _shineCenter;
    _outAlpha[0UL] = _alphaCenter;

    const size_t last = data2D.size() + 1UL;
    _outVertex[last] = _outVertex[1UL];
    _outAmbient[last] = _ambientBorder;
    _outDiffuse[last] = _diffuseBorder;
    _outSpecular[last] = _specularBorder;
    _outShine[last] = _shineBorder;
    _outAlpha[last] = _alphaBorder;
}

/*!
 * \brief Fill circle vertices - with center and border material and alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _quality Circle quality
 */
template <typename T>
inline void Circle3<T>::fillCircle(Vec3<T> *_outVertex,
                                   Vec3<T> *_outAmbient,
                                   Vec3<T> *_outDiffuse,
                                   Vec3<T> *_outSpecular,
                                   T *_outShine,
                                   T *_outAlpha,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const Vec3<T> &_ambientCenter,
                                   const Vec3<T> &_ambientBorder,
                                   const Vec3<T> &_diffuseCenter,
                                   const Vec3<T> &_diffuseBorder,
                                   const Vec3<T> &_specularCenter,
                                   const Vec3<T> &_specularBorder,
                                   const T _shineCenter,
                                   const T _shineBorder,
                                   const T _alphaCenter,
                                   const T _alphaBorder,
                                   const T _radius,
                                   const size_t _quality)
{
    fillCircle(_outVertex,
               _outAmbient,
               _outDiffuse,
               _outSpecular,
               _outShine,
               _outAlpha,
               Orientation<T>(_center, _normal, _arm),
               _ambientCenter,
               _ambientBorder,
               _diffuseCenter,
               _diffuseBorder,
               _specularCenter,
               _specularBorder,
               _shineCenter,
               _shineBorder,
               _alphaCenter,
               _alphaBorder,
               _radius,
               _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create circle arc angles aligned with circle quality
 * \tparam T Template floating point type
 * \param _out Output circle arc angles
 * \param _angleStart Start angle in radians
 * \param _angleEnd End angle in radians
 * \param _quality Circle quality
 */
template <typename T>
void Circle2<T>::arcAngles(std::vector<T> &_out, const T _angleStart, const T _angleEnd, const size_t _quality)
{
    static const T _2PI = T(2.0l * M_PIl);
    const T angle = _2PI / T(circlePointCount(_quality));
    if (isMoreOrEqual(std::fabs(_angleEnd - _angleStart), _2PI))
        fillAlignedSteps<T>(_out, T(0), _2PI, angle);
    else
        fillAlignedSteps<T>(_out, _angleStart, _angleEnd, angle);
}

/*!
 * \brief Create circle arc angles aligned with circle quality
 * \tparam T Template floating point type
 * \param _out Output circle arc angles
 * \param _angleStart Start angle in radians
 * \param _angleEnd End angle in radians
 * \param _quality Circle quality
 */
template <typename T>
void Circle3<T>::arcAngles(std::vector<T> &_out, const T _angleStart, const T _angleEnd, const size_t _quality)
{
    Circle2<T>::arcAngles(_out, _angleStart, _angleEnd, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _orientation Circle plane orientation in 3D space
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                               const Orientation<T> &_orientation,
                               const T _radius,
                               const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            _outVertex[i + 1UL] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius](Vec3<T> *__out, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        __out[i + 1UL] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                    }
                },
                _outVertex,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
inline void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _radius,
                                      const std::vector<T> &_angles)
{
    fillCircleArc(_outVertex, Orientation<T>(_center, _normal, _arm), _radius, _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _orientation Circle plane orientation in 3D space
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                               T *_outAlpha,
                               const Orientation<T> &_orientation,
                               const T _alphaCenter,
                               const T _alphaBorder,
                               const T _radius,
                               const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;
    _outAlpha[0UL] = _alphaCenter;

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _alphaBorder](Vec3<T> *__outVertex, T *__outAlpha, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outAlpha[j] = _alphaBorder;
                    }
                },
                _outVertex,
                _outAlpha,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
inline void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                                      T *_outAlpha,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _alphaCenter,
                                      const T _alphaBorder,
                                      const T _radius,
                                      const std::vector<T> &_angles)
{
    fillCircleArc(
        _outVertex, _outAlpha, Orientation<T>(_center, _normal, _arm), _alphaCenter, _alphaBorder, _radius, _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _orientation Circle plane orientation in 3D space
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                               Vec2<T> *_outCoord,
                               const Orientation<T> &_orientation,
                               const T _radius,
                               const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;
    _outCoord[0UL] = {T(0.5), T(0.5)};
    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outCoord[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)), alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius](Vec3<T> *__out, Vec2<T> *__outCoord, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __out[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outCoord[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)),
                                         alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
                    }
                },
                _outVertex,
                _outCoord,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
inline void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                                      Vec2<T> *_outCoord,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _radius,
                                      const std::vector<T> &_angles)
{
    fillCircleArc(_outVertex, _outCoord, Orientation<T>(_center, _normal, _arm), _radius, _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _orientation Circle plane orientation in 3D space
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                               Vec2<T> *_outCoord,
                               T *_outAlpha,
                               const Orientation<T> &_orientation,
                               const T _alphaCenter,
                               const T _alphaBorder,
                               const T _radius,
                               const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;
    _outAlpha[0UL] = _alphaCenter;
    _outCoord[0UL] = {T(0.5), T(0.5)};

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAlpha[j] = _alphaBorder;
            _outCoord[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)), alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _alphaBorder](
                    Vec3<T> *__outVertex, Vec2<T> *__outCoord, T *__outAlpha, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outCoord[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)),
                                         alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
                        __outAlpha[j] = _alphaBorder;
                    }
                },
                _outVertex,
                _outCoord,
                _outAlpha,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
inline void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                                      Vec2<T> *_outCoord,
                                      T *_outAlpha,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _alphaCenter,
                                      const T _alphaBorder,
                                      const T _radius,
                                      const std::vector<T> &_angles)
{
    fillCircleArc(_outVertex,
                  _outCoord,
                  _outAlpha,
                  Orientation<T>(_center, _normal, _arm),
                  _alphaCenter,
                  _alphaBorder,
                  _radius,
                  _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _orientation Circle plane orientation in 3D space
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                               Vec3<T> *_outAmbient,
                               Vec3<T> *_outDiffuse,
                               Vec3<T> *_outSpecular,
                               T *_outShine,
                               const Orientation<T> &_orientation,
                               const Vec3<T> &_ambientCenter,
                               const Vec3<T> &_ambientBorder,
                               const Vec3<T> &_diffuseCenter,
                               const Vec3<T> &_diffuseBorder,
                               const Vec3<T> &_specularCenter,
                               const Vec3<T> &_specularBorder,
                               const T _shineCenter,
                               const T _shineBorder,
                               const T _radius,
                               const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;
    _outAmbient[0UL] = _ambientCenter;
    _outDiffuse[0UL] = _diffuseCenter;
    _outSpecular[0UL] = _specularCenter;
    _outShine[0UL] = _shineCenter;

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAmbient[j] = _ambientBorder;
            _outDiffuse[j] = _diffuseBorder;
            _outSpecular[j] = _specularBorder;
            _outShine[j] = _shineBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _ambientBorder, _diffuseBorder, _specularBorder, _shineBorder](
                    Vec3<T> *__outVertex,
                    Vec3<T> *__outAmbient,
                    Vec3<T> *__outDiffuse,
                    Vec3<T> *__outSpecular,
                    T *__outShine,
                    const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outAmbient[j] = _ambientBorder;
                        __outDiffuse[j] = _diffuseBorder;
                        __outSpecular[j] = _specularBorder;
                        __outShine[j] = _shineBorder;
                    }
                },
                _outVertex,
                _outAmbient,
                _outDiffuse,
                _outSpecular,
                _outShine,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
inline void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                                      Vec3<T> *_outAmbient,
                                      Vec3<T> *_outDiffuse,
                                      Vec3<T> *_outSpecular,
                                      T *_outShine,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const Vec3<T> &_ambientCenter,
                                      const Vec3<T> &_ambientBorder,
                                      const Vec3<T> &_diffuseCenter,
                                      const Vec3<T> &_diffuseBorder,
                                      const Vec3<T> &_specularCenter,
                                      const Vec3<T> &_specularBorder,
                                      const T _shineCenter,
                                      const T _shineBorder,
                                      const T _radius,
                                      const std::vector<T> &_angles)
{
    fillCircleArc(_outVertex,
                  _outAmbient,
                  _outDiffuse,
                  _outSpecular,
                  _outShine,
                  Orientation<T>(_center, _normal, _arm),
                  _ambientCenter,
                  _ambientBorder,
                  _diffuseCenter,
                  _diffuseBorder,
                  _specularCenter,
                  _specularBorder,
                  _shineCenter,
                  _shineBorder,
                  _radius,
                  _angles);
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _orientation Circle plane orientation in 3D space
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _alphaCenter Shine at circle center
 * \param _alphaBorder Shine at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                               Vec3<T> *_outAmbient,
                               Vec3<T> *_outDiffuse,
                               Vec3<T> *_outSpecular,
                               T *_outShine,
                               T *_outAlpha,
                               const Orientation<T> &_orientation,
                               const Vec3<T> &_ambientCenter,
                               const Vec3<T> &_ambientBorder,
                               const Vec3<T> &_diffuseCenter,
                               const Vec3<T> &_diffuseBorder,
                               const Vec3<T> &_specularCenter,
                               const Vec3<T> &_specularBorder,
                               const T _shineCenter,
                               const T _shineBorder,
                               const T _alphaCenter,
                               const T _alphaBorder,
                               const T _radius,
                               const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;
    _outAmbient[0UL] = _ambientCenter;
    _outDiffuse[0UL] = _diffuseCenter;
    _outSpecular[0UL] = _specularCenter;
    _outShine[0UL] = _shineCenter;
    _outAlpha[0UL] = _alphaCenter;

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            const size_t j = i + 1UL;
            _outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                _orientation.normal3 * (p2d.y * _radius);
            _outAmbient[j] = _ambientBorder;
            _outDiffuse[j] = _diffuseBorder;
            _outSpecular[j] = _specularBorder;
            _outShine[j] = _shineBorder;
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius, _ambientBorder, _diffuseBorder, _specularBorder, _shineBorder, _alphaBorder](
                    Vec3<T> *__outVertex,
                    Vec3<T> *__outAmbient,
                    Vec3<T> *__outDiffuse,
                    Vec3<T> *__outSpecular,
                    T *__outShine,
                    T *__outAlpha,
                    const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center + _orientation.normal2 * (p2d.x * _radius) +
                            _orientation.normal3 * (p2d.y * _radius);
                        __outAmbient[j] = _ambientBorder;
                        __outDiffuse[j] = _diffuseBorder;
                        __outSpecular[j] = _specularBorder;
                        __outShine[j] = _shineBorder;
                        __outAlpha[j] = _alphaBorder;
                    }
                },
                _outVertex,
                _outAmbient,
                _outDiffuse,
                _outSpecular,
                _outShine,
                _outAlpha,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill circle arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _center Circle center point
 * \param _normal Circle plane normal
 * \param _arm Circle start arm
 * \param _ambientCenter Ambient color at circle center
 * \param _ambientBorder Ambient color at circle border
 * \param _diffuseCenter Diffuse color at circle center
 * \param _diffuseBorder Diffuse color at circle border
 * \param _specularCenter Specular color at circle center
 * \param _specularBorder Specular color at circle border
 * \param _shineCenter Shine at circle center
 * \param _shineBorder Shine at circle border
 * \param _alphaCenter Alpha at circle center
 * \param _alphaBorder Alpha at circle border
 * \param _radius Circle radius
 * \param _angles Circle arc angles in radian
 */
template <typename T>
inline void Circle3<T>::fillCircleArc(Vec3<T> *_outVertex,
                                      Vec3<T> *_outAmbient,
                                      Vec3<T> *_outDiffuse,
                                      Vec3<T> *_outSpecular,
                                      T *_outShine,
                                      T *_outAlpha,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const Vec3<T> &_ambientCenter,
                                      const Vec3<T> &_ambientBorder,
                                      const Vec3<T> &_diffuseCenter,
                                      const Vec3<T> &_diffuseBorder,
                                      const Vec3<T> &_specularCenter,
                                      const Vec3<T> &_specularBorder,
                                      const T _shineCenter,
                                      const T _shineBorder,
                                      const T _alphaCenter,
                                      const T _alphaBorder,
                                      const T _radius,
                                      const std::vector<T> &_angles)
{
    fillCircleArc(_outVertex,
                  _outAmbient,
                  _outDiffuse,
                  _outSpecular,
                  _outShine,
                  _outAlpha,
                  Orientation<T>(_center, _normal, _arm),
                  _ambientCenter,
                  _ambientBorder,
                  _diffuseCenter,
                  _diffuseBorder,
                  _specularCenter,
                  _specularBorder,
                  _shineCenter,
                  _shineBorder,
                  _alphaCenter,
                  _alphaBorder,
                  _radius,
                  _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _c Circle
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Circle2<T> &_c)
{
    return _os << "[R[" << _c.radius << "]P" << _c.center << ']';
}

/*!
 * \brief Fill output text stream
 * \tparam T Template floating point type
 * \param _os Output text stream
 * \param _c Circle
 * \return Output text stream
 */
template <typename T>
inline std::ostream &operator<<(std::ostream &_os, const Circle3<T> &_c)
{
    return _os << "[R[" << _c.radius << "]P" << _c.center << 'N' << _c.normal << ']';
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Circle2<float> Circle2F;        //!< 32 bit floating point precision 2D circle
typedef Circle2<double> Circle2D;       //!< 64 bit floating point precision 2D circle
typedef Circle2<long double> Circle2L;  //!< 128 bit floating point precision 2D circle

typedef Circle3<float> Circle3F;        //!< 32 bit floating point precision 3D circle
typedef Circle3<double> Circle3D;       //!< 64 bit floating point precision 3D circle
typedef Circle3<long double> Circle3L;  //!< 128 bit floating point precision 3D circle

}  // namespace Math
}  // namespace U1

#endif  // MATH_CIRCLE_H
