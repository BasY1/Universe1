/*!
 * \file qt/opengl/lights.cpp
 * \author Michal Steller
 * \brief The QT Open GL lights classes implementation
 */

#include "lights.h"
#include <QSettings>
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
 * \brief Save direction light into \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::DirectionLight::saveSettings(QSettings &_settings, const QString &_keyGroup) const
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    _settings.setValue(key + "mode", static_cast<int>(mode));
    _settings.setValue(key + "direction", direction);
    ADSColors::saveSettings(_settings, key);
}

/*!
 * \brief Load direction light from \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::DirectionLight::loadSettings(const QSettings &_settings, const QString &_keyGroup)
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    mode = static_cast<Mode>(_settings.value(key + "mode", static_cast<int>(mode)).toInt());
    direction = _settings.value(key + "direction", direction).value<QVector3D>();
    ADSColors::loadSettings(_settings, key);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/*!
 * \brief Save point light into \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::PointLight::saveSettings(QSettings &_settings, const QString &_keyGroup) const
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    _settings.setValue(key + "mode", static_cast<int>(mode));
    _settings.setValue(key + "position", position);
    _settings.setValue(key + "constant", constant);
    _settings.setValue(key + "linear", linear);
    _settings.setValue(key + "quadratic", quadratic);
    ADSColors::saveSettings(_settings, key);
}

/*!
 * \brief Load point light from \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::PointLight::loadSettings(const QSettings &_settings, const QString &_keyGroup)
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    mode = static_cast<Mode>(_settings.value(key + "mode", static_cast<int>(mode)).toInt());
    position = _settings.value(key + "position", position).value<QVector3D>();
    constant = _settings.value(key + "constant", constant).toFloat();
    linear = _settings.value(key + "linear", linear).toFloat();
    quadratic = _settings.value(key + "quadratic", quadratic).toFloat();
    ADSColors::loadSettings(_settings, key);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _mode Light mode
 * \param _position Light position
 * \param _direction Light direction
 * \param _cutOffRad Cut-off angle [radians]
 * \param _outerCutOffRad Outer cut-off angle [radians]
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _constant Constant attenuation factor
 * \param _linear Linear attenuation factor
 * \param _quadratic Quadratic attenuation factor
 */
Universe1::OpenGL::SpotLight::SpotLight(const Mode _mode,
                                        const QVector3D &_position,
                                        const QVector3D &_direction,
                                        const float _cutOffRad,
                                        const float _outerCutOffRad,
                                        const QColor &_ambient,
                                        const QColor &_diffuse,
                                        const QColor &_specular,
                                        const float _constant,
                                        const float _linear,
                                        const float _quadratic)
    : PointLight(_mode, _position, _ambient, _diffuse, _specular, _constant, _linear, _quadratic)
    , direction(_direction)
    , cutOffRad(_cutOffRad)
    , outerCutOffRad(_outerCutOffRad)
{
}

/*!
 * \brief Save spot light into \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::SpotLight::saveSettings(QSettings &_settings, const QString &_keyGroup) const
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    _settings.setValue(key + "direction", direction);
    _settings.setValue(key + "cutOffRad", cutOffRad);
    _settings.setValue(key + "outerCutOffRad", outerCutOffRad);
    PointLight::saveSettings(_settings, key);
}

/*!
 * \brief Load spot light from \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::SpotLight::loadSettings(const QSettings &_settings, const QString &_keyGroup)
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    direction = _settings.value(key + "direction", direction).value<QVector3D>();
    cutOffRad = _settings.value(key + "cutOffRad", cutOffRad).toFloat();
    outerCutOffRad = _settings.value(key + "outerCutOffRad", outerCutOffRad).toFloat();
    PointLight::loadSettings(_settings, key);
}
