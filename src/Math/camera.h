/*!
 * \file src/Math/camera.h
 * \brief Camera data structure
 */

#ifndef MATH_CAMERA_H
#define MATH_CAMERA_H

#include "vec3.h"

#include <QMatrix4x4>

namespace U1 {
namespace Math {

/*!
 * \brief Open GL camera base data
 * \tparam T Template floating point type
 */
template <typename T>
struct Camera
{
    Vec3<T> position;   //!< Camera look from position
    Vec3<T> lookAt;     //!< Camera look at position
    Vec3<T> up;         //!< Camera up direction
    uint screenWidth;   //!< Screen width
    uint screenHeight;  //!< Screen height
    T fieldOfView;      //!< Field of view (in degrees)
    T nearPlane;        //!< Near plane distance
    T farPlane;         //!< Far plane distance
    size_t valueHash;   //!< Calculated hash

    /*!
     * \brief Constructor
     * \param _position Camera look from position
     * \param _lookAt Camera look at position
     * \param _up Camera up direction
     * \param _screenWidth Screen width
     * \param _screenHeight Screen height
     * \param _fieldOfView Field of view (in degrees)
     * \param _nearPlane Near plane distance
     * \param _farPlane Far plane distance
     */
    inline Camera(const Vec3<T> &_position,
                  const Vec3<T> &_lookAt,
                  const Vec3<T> &_up,
                  const uint &_screenWidth,
                  const uint &_screenHeight,
                  const T _fieldOfView,
                  const T _nearPlane,
                  const T _farPlane)
        : position(_position)
        , lookAt(_lookAt)
        , up(_up)
        , fieldOfView(_fieldOfView)
        , nearPlane(_nearPlane)
        , farPlane(_farPlane)
        , screenWidth(_screenWidth)
        , screenHeight(_screenHeight)
        , valueHash(mixHash(position.toHash(),
                            lookAt.toHash(),
                            up.toHash(),
                            std::hash<uint>{}(screenWidth),
                            std::hash<uint>{}(screenHeight),
                            std::hash<T>{}(fieldOfView),
                            std::hash<T>{}(nearPlane),
                            std::hash<T>{}(farPlane)))
    {
    }

    /*!
     * \brief Make MVP matrix
     * \param _pos Camera position
     * \param _lookAt Camera look at
     * \param _up Camera up vector
     * \return MVP matrix
     */
    inline static QMatrix4x4 makeMvp(const Vec3<T> &_pos, const Vec3<T> &_lookAt, const Vec3<T> &_up)
    {
        const Vec3<T> tmpUp = _up.normalized();
        const Vec3<T> camFw = (_pos - _lookAt).normalized();
        const Vec3<T> camLeft = Vec3<T>::cross(tmpUp, camFw).normalized();
        const Vec3<T> camUp = Vec3<T>::cross(camFw, camLeft).normalized();

        QMatrix4x4 result;
        result.setToIdentity();
        result.data()[0] = camLeft.x;
        result.data()[4] = camLeft.y;
        result.data()[8] = camLeft.z;
        result.data()[1] = camUp.x;
        result.data()[5] = camUp.y;
        result.data()[9] = camUp.z;
        result.data()[2] = camFw.x;
        result.data()[6] = camFw.y;
        result.data()[10] = camFw.z;
        result.data()[12] = (-camLeft.x * _pos.x - camLeft.y * _pos.y - camLeft.z * _pos.z);
        result.data()[13] = (-camUp.x * _pos.x - camUp.y * _pos.y - camUp.z * _pos.z);
        result.data()[14] = (-camFw.x * _pos.x - camFw.y * _pos.y - camFw.z * _pos.z);
        return result;
    }

    /*!
     * \brief Getter for MVP matrix
     * \return MVP matrix
     */
    inline QMatrix4x4 getMvp() const
    {
        return makeMvp(position, lookAt, up);
    }

    /*!
     * \brief Getter for view matrix (perspective matrix x MVP matrix)
     * \return View matrix
     */
    inline QMatrix4x4 getView() const
    {
        const float imgWidth = screenWidth;
        const float imgHeight = static_cast<float>(std::max(1U, screenHeight));
        QMatrix4x4 per;
        per.perspective(float(fieldOfView), imgWidth / imgHeight, float(nearPlane), float(farPlane));
        return per * getMvp();
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef Camera<float> CamF;        //!< 32 bit floating point precision camera
typedef Camera<double> CamD;       //!< 64 bit floating point precision camera
typedef Camera<long double> CamL;  //!< 128 bit floating point precision camera

}  // namespace Math
}  // namespace U1

#endif  // MATH_CAMERA_H
