/*!
 * \file src/Math/irregellipse.h
 * \brief Irregular ellipse structure
 */

#ifndef MATH_IRREGELLIPSE_H
#define MATH_IRREGELLIPSE_H

#include "circle.h"

namespace U1 {
namespace Math {

/*!
 * \brief 3D Irregular Ellipse structure
 * \tparam T Template floating point type
 */
template <typename T>
struct IrregEllipse
{
    /*!
     * \brief Irregular ellipse vertex count by circle quality
     * \param _quality Circle quality
     * \return Irregular ellipse vertex count
     * \sa circlePointCount(const size_t)
     */
    inline static size_t ellipseVertexCount(const size_t _quality)
    {
        return circlePointCount(_quality);
    }

    /*!
     * \brief Irregular ellipse vertex count by circle quality
     * \param _quality Irregular ellipse Circle quality
     * \return Ellipse vertex count
     * \details Irregular ellipse vertex count includes 2 pints: center point and loop-enclosing point
     * \sa circlePointCount(const size_t)
     */
    inline static size_t ellipseCenterVertexCount(const size_t _quality)
    {
        return circlePointCount(_quality) + 2UL;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipse(Vec3<T> *_outVertex,
                            const Orientation<T> &_orientation,
                            const T _radius1P,
                            const T _radius1M,
                            const T _radius2P,
                            const T _radius2M,
                            const size_t _quality);

    inline static void fillEllipse(Vec3<T> *_outVertex,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipse(Vec3<T> *_outVertex,
                            T *_outAlpha,
                            const Orientation<T> &_orientation,
                            const T _alphaCenter,
                            const T _alphaBorder,
                            const T _radius1P,
                            const T _radius1M,
                            const T _radius2P,
                            const T _radius2M,
                            const size_t _quality);

    inline static void fillEllipse(Vec3<T> *_outVertex,
                                   T *_outAlpha,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _alphaCenter,
                                   const T _alphaBorder,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipse(Vec3<T> *_outVertex,
                            Vec2<T> *_outCoords,
                            const Orientation<T> &_orientation,
                            const T _radius1P,
                            const T _radius1M,
                            const T _radius2P,
                            const T _radius2M,
                            const size_t _quality);

    inline static void fillEllipse(Vec3<T> *_outVertex,
                                   Vec2<T> *_outCoords,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipse(Vec3<T> *_outVertex,
                            Vec2<T> *_outCoords,
                            T *_outAlpha,
                            const Orientation<T> &_orientation,
                            const T _alphaCenter,
                            const T _alphaBorder,
                            const T _radius1P,
                            const T _radius1M,
                            const T _radius2P,
                            const T _radius2M,
                            const size_t _quality);

    inline static void fillEllipse(Vec3<T> *_outVertex,
                                   Vec2<T> *_outCoords,
                                   T *_outAlpha,
                                   const Vec3<T> &_center,
                                   const Vec3<T> &_normal,
                                   const Vec3<T> &_arm,
                                   const T _alphaCenter,
                                   const T _alphaBorder,
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipse(Vec3<T> *_outVertex,
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
                            const T _radius1P,
                            const T _radius1M,
                            const T _radius2P,
                            const T _radius2M,
                            const size_t _quality);

    inline static void fillEllipse(Vec3<T> *_outVertex,
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
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipse(Vec3<T> *_outVertex,
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
                            const T _radius1P,
                            const T _radius1M,
                            const T _radius2P,
                            const T _radius2M,
                            const size_t _quality);

    inline static void fillEllipse(Vec3<T> *_outVertex,
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
                                   const T _radius1P,
                                   const T _radius1M,
                                   const T _radius2P,
                                   const T _radius2M,
                                   const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    inline static void arcAngles(std::vector<T> &_out, const T _angleStart, const T _angleEnd, const size_t _quality);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipseArc(Vec3<T> *_outVertex,
                               const Orientation<T> &_orientation,
                               const T _radius1P,
                               const T _radius1M,
                               const T _radius2P,
                               const T _radius2M,
                               const std::vector<T> &_angles);

    inline static void fillEllipseArc(Vec3<T> *_outVertex,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipseArc(Vec3<T> *_outVertex,
                               T *_outAlpha,
                               const Orientation<T> &_orientation,
                               const T _alphaCenter,
                               const T _alphaBorder,
                               const T _radius1P,
                               const T _radius1M,
                               const T _radius2P,
                               const T _radius2M,
                               const std::vector<T> &_angles);

    inline static void fillEllipseArc(Vec3<T> *_outVertex,
                                      T *_outAlpha,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _alphaCenter,
                                      const T _alphaBorder,
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipseArc(Vec3<T> *_outVertex,
                               Vec2<T> *_outCoords,
                               const Orientation<T> &_orientation,
                               const T _radius1P,
                               const T _radius1M,
                               const T _radius2P,
                               const T _radius2M,
                               const std::vector<T> &_angles);

    inline static void fillEllipseArc(Vec3<T> *_outVertex,
                                      Vec2<T> *_outCoords,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipseArc(Vec3<T> *_outVertex,
                               Vec2<T> *_outCoords,
                               T *_outAlpha,
                               const Orientation<T> &_orientation,
                               const T _alphaCenter,
                               const T _alphaBorder,
                               const T _radius1P,
                               const T _radius1M,
                               const T _radius2P,
                               const T _radius2M,
                               const std::vector<T> &_angles);

    inline static void fillEllipseArc(Vec3<T> *_outVertex,
                                      Vec2<T> *_outCoords,
                                      T *_outAlpha,
                                      const Vec3<T> &_center,
                                      const Vec3<T> &_normal,
                                      const Vec3<T> &_arm,
                                      const T _alphaCenter,
                                      const T _alphaBorder,
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipseArc(Vec3<T> *_outVertex,
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
                               const T _radius1P,
                               const T _radius1M,
                               const T _radius2P,
                               const T _radius2M,
                               const std::vector<T> &_angles);

    inline static void fillEllipseArc(Vec3<T> *_outVertex,
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
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const std::vector<T> &_angles);

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    static void fillEllipseArc(Vec3<T> *_outVertex,
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
                               const T _radius1P,
                               const T _radius1M,
                               const T _radius2P,
                               const T _radius2M,
                               const std::vector<T> &_angles);

    inline static void fillEllipseArc(Vec3<T> *_outVertex,
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
                                      const T _radius1P,
                                      const T _radius1M,
                                      const T _radius2P,
                                      const T _radius2M,
                                      const std::vector<T> &_angles);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                  const Orientation<T> &_orientation,
                                  const T _radius1P,
                                  const T _radius1M,
                                  const T _radius2P,
                                  const T _radius2M,
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
            _outVertex[i] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M](Vec3<T> *__out, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        __out[i] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
                    }
                },
                _outVertex,
                data2D.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill ellipse vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */

template <typename T>
inline void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _radius1P,
                                         const T _radius1M,
                                         const T _radius2P,
                                         const T _radius2M,
                                         const size_t _quality)
{
    fillEllipse(
        _outVertex, Orientation<T>(_center, _normal, _arm), _radius1P, _radius1M, _radius2P, _radius2M, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse vertices - with center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                  T *_outAlpha,
                                  const Orientation<T> &_orientation,
                                  const T _alphaCenter,
                                  const T _alphaBorder,
                                  const T _radius1P,
                                  const T _radius1M,
                                  const T _radius2P,
                                  const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _alphaBorder](
                    Vec3<T> *__outVertex, T *__outAlpha, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse vertices - with center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                         T *_outAlpha,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _alphaCenter,
                                         const T _alphaBorder,
                                         const T _radius1P,
                                         const T _radius1M,
                                         const T _radius2P,
                                         const T _radius2M,
                                         const size_t _quality)
{
    fillEllipse(_outVertex,
                _outAlpha,
                Orientation<T>(_center, _normal, _arm),
                _alphaCenter,
                _alphaBorder,
                _radius1P,
                _radius1M,
                _radius2P,
                _radius2M,
                _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse vertices - with texture coordinates
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                  Vec2<T> *_outCoords,
                                  const Orientation<T> &_orientation,
                                  const T _radius1P,
                                  const T _radius1M,
                                  const T _radius2P,
                                  const T _radius2M,
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
            _outVertex[i] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
            _outCoords[i] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)), alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M](
                    Vec3<T> *__outVertex, Vec2<T> *__outCoords, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        __outVertex[i] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse vertices - with texture coordinates
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                         Vec2<T> *_outCoords,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _radius1P,
                                         const T _radius1M,
                                         const T _radius2P,
                                         const T _radius2M,
                                         const size_t _quality)
{
    fillEllipse(_outVertex,
                _outCoords,
                Orientation<T>(_center, _normal, _arm),
                _radius1P,
                _radius1M,
                _radius2P,
                _radius2M,
                _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse vertices - with texture coordinates, center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                  Vec2<T> *_outCoords,
                                  T *_outAlpha,
                                  const Orientation<T> &_orientation,
                                  const T _alphaCenter,
                                  const T _alphaBorder,
                                  const T _radius1P,
                                  const T _radius1M,
                                  const T _radius2P,
                                  const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _alphaBorder](
                    Vec3<T> *__outVertex, Vec2<T> *__outCoords, T *__outAlpha, const Vec2<T> *_data2D) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> &p2d = _data2D[i];
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse vertices - with texture coordinates, center and border alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoords Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
                                         Vec2<T> *_outCoords,
                                         T *_outAlpha,
                                         const Vec3<T> &_center,
                                         const Vec3<T> &_normal,
                                         const Vec3<T> &_arm,
                                         const T _alphaCenter,
                                         const T _alphaBorder,
                                         const T _radius1P,
                                         const T _radius1M,
                                         const T _radius2P,
                                         const T _radius2M,
                                         const size_t _quality)
{
    fillEllipse(_outVertex,
                _outCoords,
                _outAlpha,
                Orientation<T>(_center, _normal, _arm),
                _alphaCenter,
                _alphaBorder,
                _radius1P,
                _radius1M,
                _radius2P,
                _radius2M,
                _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse vertices - with center and border material
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
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
                                  const T _radius1P,
                                  const T _radius1M,
                                  const T _radius2P,
                                  const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
                [t,
                 _orientation,
                 _radius1P,
                 _radius1M,
                 _radius2P,
                 _radius2M,
                 _ambientBorder,
                 _diffuseBorder,
                 _specularBorder,
                 _shineBorder](Vec3<T> *__outVertex,
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
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse vertices - with center and border material
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
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
                                         const T _radius1P,
                                         const T _radius1M,
                                         const T _radius2P,
                                         const T _radius2M,
                                         const size_t _quality)
{
    fillEllipse(_outVertex,
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
                _radius1P,
                _radius1M,
                _radius2P,
                _radius2M,
                _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse vertices - with center and border material and alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
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
                                  const T _radius1P,
                                  const T _radius1M,
                                  const T _radius2P,
                                  const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
                [t,
                 _orientation,
                 _radius1P,
                 _radius1M,
                 _radius2P,
                 _radius2M,
                 _ambientBorder,
                 _diffuseBorder,
                 _specularBorder,
                 _shineBorder,
                 _alphaBorder](Vec3<T> *__outVertex,
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
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse vertices - with center and border material and alpha
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipse(Vec3<T> *_outVertex,
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
                                         const T _radius1P,
                                         const T _radius1M,
                                         const T _radius2P,
                                         const T _radius2M,
                                         const size_t _quality)
{
    fillEllipse(_outVertex,
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
                _radius1P,
                _radius1M,
                _radius2P,
                _radius2M,
                _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Create ellipse arc angles aligned with circle quality
 * \tparam T Template floating point type
 * \param _out Output ellipse arc angles
 * \param _angleStart Start angle in radians
 * \param _angleEnd End angle in radians
 * \param _quality Circle quality
 * \return
 */
template <typename T>
inline void
IrregEllipse<T>::arcAngles(std::vector<T> &_out, const T _angleStart, const T _angleEnd, const size_t _quality)
{
    Circle2<T>::arcAngles(_out, _angleStart, _angleEnd, _quality);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                     const Orientation<T> &_orientation,
                                     const T _radius1P,
                                     const T _radius1M,
                                     const T _radius2P,
                                     const T _radius2M,
                                     const std::vector<T> &_angles)
{
    _outVertex[0UL] = _orientation.center;

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_angles.size());
    if (pool.empty())
    {
        for (size_t i = 0UL; i < _angles.size(); i++)
        {
            const Vec2<T> p2d = {std::sin(_angles[i]), std::cos(_angles[i])};
            _outVertex[i + 1UL] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M](Vec3<T> *__out, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        __out[i + 1UL] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
                    }
                },
                _outVertex,
                _angles.data()));
        for (std::thread &t : threads)
            t.join();
    }
}

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                            const Vec3<T> &_center,
                                            const Vec3<T> &_normal,
                                            const Vec3<T> &_arm,
                                            const T _radius1P,
                                            const T _radius1M,
                                            const T _radius2P,
                                            const T _radius2M,
                                            const std::vector<T> &_angles)
{
    fillEllipseArc(
        _outVertex, Orientation<T>(_center, _normal, _arm), _radius1P, _radius1M, _radius2P, _radius2M, _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                     T *_outAlpha,
                                     const Orientation<T> &_orientation,
                                     const T _alphaCenter,
                                     const T _alphaBorder,
                                     const T _radius1P,
                                     const T _radius1M,
                                     const T _radius2P,
                                     const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
            _outAlpha[j] = _alphaBorder;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _alphaBorder](
                    Vec3<T> *__outVertex, T *__outAlpha, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAlpha Output alpha array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                            T *_outAlpha,
                                            const Vec3<T> &_center,
                                            const Vec3<T> &_normal,
                                            const Vec3<T> &_arm,
                                            const T _alphaCenter,
                                            const T _alphaBorder,
                                            const T _radius1P,
                                            const T _radius1M,
                                            const T _radius2P,
                                            const T _radius2M,
                                            const std::vector<T> &_angles)
{
    fillEllipseArc(_outVertex,
                   _outAlpha,
                   Orientation<T>(_center, _normal, _arm),
                   _alphaCenter,
                   _alphaBorder,
                   _radius1P,
                   _radius1M,
                   _radius2P,
                   _radius2M,
                   _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                     Vec2<T> *_outCoord,
                                     const Orientation<T> &_orientation,
                                     const T _radius1P,
                                     const T _radius1M,
                                     const T _radius2P,
                                     const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
            _outCoord[j] = {alignedTo0_1((p2d.x + T(1)) * T(0.5)), alignedTo0_1(T(1) - (p2d.y + T(1)) * T(0.5))};
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M](
                    Vec3<T> *__out, Vec2<T> *__outCoord, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __out[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                            Vec2<T> *_outCoord,
                                            const Vec3<T> &_center,
                                            const Vec3<T> &_normal,
                                            const Vec3<T> &_arm,
                                            const T _radius1P,
                                            const T _radius1M,
                                            const T _radius2P,
                                            const T _radius2M,
                                            const std::vector<T> &_angles)
{
    fillEllipseArc(_outVertex,
                   _outCoord,
                   Orientation<T>(_center, _normal, _arm),
                   _radius1P,
                   _radius1M,
                   _radius2P,
                   _radius2M,
                   _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                     Vec2<T> *_outCoord,
                                     T *_outAlpha,
                                     const Orientation<T> &_orientation,
                                     const T _alphaCenter,
                                     const T _alphaBorder,
                                     const T _radius1P,
                                     const T _radius1M,
                                     const T _radius2P,
                                     const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
                [t, _orientation, _radius1P, _radius1M, _radius2P, _radius2M, _alphaBorder](
                    Vec3<T> *__outVertex, Vec2<T> *__outCoord, T *__outAlpha, const T *__angles) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const Vec2<T> p2d = {std::sin(__angles[i]), std::cos(__angles[i])};
                        const size_t j = i + 1UL;
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outCoord Output texture coordinates array
 * \param _outAlpha Output alpha array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
                                            Vec2<T> *_outCoord,
                                            T *_outAlpha,
                                            const Vec3<T> &_center,
                                            const Vec3<T> &_normal,
                                            const Vec3<T> &_arm,
                                            const T _alphaCenter,
                                            const T _alphaBorder,
                                            const T _radius1P,
                                            const T _radius1M,
                                            const T _radius2P,
                                            const T _radius2M,
                                            const std::vector<T> &_angles)
{
    fillEllipseArc(_outVertex,
                   _outCoord,
                   _outAlpha,
                   Orientation<T>(_center, _normal, _arm),
                   _alphaCenter,
                   _alphaBorder,
                   _radius1P,
                   _radius1M,
                   _radius2P,
                   _radius2M,
                   _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
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
                                     const T _radius1P,
                                     const T _radius1M,
                                     const T _radius2P,
                                     const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
                [t,
                 _orientation,
                 _radius1P,
                 _radius1M,
                 _radius2P,
                 _radius2M,
                 _ambientBorder,
                 _diffuseBorder,
                 _specularBorder,
                 _shineBorder](Vec3<T> *__outVertex,
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
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
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
                                            const T _radius1P,
                                            const T _radius1M,
                                            const T _radius2P,
                                            const T _radius2M,
                                            const std::vector<T> &_angles)
{
    fillEllipseArc(_outVertex,
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
                   _radius1P,
                   _radius1M,
                   _radius2P,
                   _radius2M,
                   _angles);
}
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _orientation Ellipse plane orientation in 3D space
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _alphaCenter Shine at ellipse center
 * \param _alphaBorder Shine at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
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
                                     const T _radius1P,
                                     const T _radius1M,
                                     const T _radius2P,
                                     const T _radius2M,
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
            _outVertex[j] = _orientation.center +
                _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
                [t,
                 _orientation,
                 _radius1P,
                 _radius1M,
                 _radius2P,
                 _radius2M,
                 _ambientBorder,
                 _diffuseBorder,
                 _specularBorder,
                 _shineBorder,
                 _alphaBorder](Vec3<T> *__outVertex,
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
                        __outVertex[j] = _orientation.center +
                            _orientation.normal2 * (p2d.x * (isNegative(p2d.x) ? _radius1M : _radius1P)) +
                            _orientation.normal3 * (p2d.y * (isNegative(p2d.y) ? _radius2M : _radius2P));
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
 * \brief Fill ellipse arc vertices
 * \tparam T Template floating point type
 * \param _outVertex Output vertex array
 * \param _outAmbient Output ambient color array
 * \param _outDiffuse Output diffuse color array
 * \param _outSpecular Output specular color array
 * \param _outShine Output shine array
 * \param _outAlpha Output alpha array
 * \param _center Ellipse center point
 * \param _normal Ellipse plane normal
 * \param _arm Ellipse start arm
 * \param _ambientCenter Ambient color at ellipse center
 * \param _ambientBorder Ambient color at ellipse border
 * \param _diffuseCenter Diffuse color at ellipse center
 * \param _diffuseBorder Diffuse color at ellipse border
 * \param _specularCenter Specular color at ellipse center
 * \param _specularBorder Specular color at ellipse border
 * \param _shineCenter Shine at ellipse center
 * \param _shineBorder Shine at ellipse border
 * \param _alphaCenter Alpha at ellipse center
 * \param _alphaBorder Alpha at ellipse border
 * \param _radius1P Ellipse radius within axis 1 in positive direction
 * \param _radius1M Ellipse radius within axis 1 in negative direction
 * \param _radius2P Ellipse radius within axis 2 in positive direction
 * \param _radius2M Ellipse radius within axis 2 in negative direction
 * \param _angles Circle arc angles in radian
 * \return
 */
template <typename T>
inline void IrregEllipse<T>::fillEllipseArc(Vec3<T> *_outVertex,
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
                                            const T _radius1P,
                                            const T _radius1M,
                                            const T _radius2P,
                                            const T _radius2M,
                                            const std::vector<T> &_angles)
{
    fillEllipseArc(_outVertex,
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
                   _radius1P,
                   _radius1M,
                   _radius2P,
                   _radius2M,
                   _angles);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef IrregEllipse<float> IrregEllipseF;        //!< 32 bit floating point precision 3D irregular ellipse
typedef IrregEllipse<double> IrregEllipseD;       //!< 64 bit floating point precision 3D irregular ellipse
typedef IrregEllipse<long double> IrregEllipseL;  //!< 128 bit floating point precision 3D irregular ellipse

}  // namespace Math
}  // namespace U1

#endif  // MATH_IRREGELLIPSE_H
