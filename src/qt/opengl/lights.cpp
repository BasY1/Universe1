/*!
 * \file qt/opengl/lights.cpp
 * \author Michal Steller
 * \brief The QT Open GL lights classes implementation
 */

#include "lights.h"

/*!
 * \brief Constructor
 * \param _direction Light direction
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 */
Universe1::OpenGL::DirectionLight::DirectionLight(const QVector3D &_direction,
                                                  const QColor &_ambient,
                                                  const QColor &_diffuse,
                                                  const QColor &_specular)
    : ADSColors(_ambient, _diffuse, _specular)
    , mode(LightOn)
    , direction(_direction)
{
}

/*!
 * \brief Constructor
 * \param _mode Light mode
 * \param _position Light position
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 */
Universe1::OpenGL::PointLight::PointLight(const Mode _mode,
                                          const QVector3D &_position,
                                          const QColor &_ambient,
                                          const QColor &_diffuse,
                                          const QColor &_specular,
                                          const float _constant,
                                          const float _linear,
                                          const float _quadratic)
    : ADSColors(_ambient, _diffuse, _specular)
    , mode(_mode)
    , position(_position)
    , constant(_constant)
    , linear(_linear)
    , quadratic(_quadratic)
{
}
