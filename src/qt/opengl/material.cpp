/*!
 * \file qt/opengl/material.cpp
 * \author Michal Steller
 * \brief The QT Open GL material class implementation
 */

#include "material.h"
#include <QSettings>

/*!
 * \brief Default constructor
 */
Universe1::OpenGL::Material::Material()
    : ADSColors()
    , mode(MaterialADS)
    , shininess(32.0F)
    , alpha(1.0F)
{
}

/*!
 * \brief Constructor
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _shininess Material shininess
 * \param _alpha Material color alpha
 */
Universe1::OpenGL::Material::Material(
    const QColor &_ambient, const QColor &_diffuse, const QColor &_specular, const float _shininess, const float _alpha)
    : ADSColors(_ambient, _diffuse, _specular)
    , mode(MaterialADS)
    , shininess(_shininess)
    , alpha(_alpha)
{
}

/*!
 * \brief Constructor
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 */
Universe1::OpenGL::Material::Material(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular)
    : ADSColors(_ambient, _diffuse, _specular)
    , mode(MaterialADS)
    , shininess(32.0F)
    , alpha(1.0F)
{
}

/*!
 * \brief Constructor
 * \param _colors Ambient - Diffuse - Specular colors
 * \param _shininess Material shininess
 * \param _alpha Material color alpha
 */
Universe1::OpenGL::Material::Material(const ADSColors &_colors, const float _shininess, const float _alpha)
    : ADSColors(_colors)
    , mode(MaterialADS)
    , shininess(_shininess)
    , alpha(_alpha)
{
}

/*!
 * \brief Constructor
 * \param _colors Ambient - Diffuse - Specular colors
 */
Universe1::OpenGL::Material::Material(const ADSColors &_colors)
    : ADSColors(_colors)
    , mode(MaterialADS)
    , shininess(32.0F)
    , alpha(1.0F)
{
}

/*!
 * \brief Save material into \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::Material::saveSettings(QSettings &_settings, const QString &_keyGroup) const
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    _settings.setValue(key + "mode", static_cast<int>(mode));
    _settings.setValue(key + "shininess", shininess);
    _settings.setValue(key + "alpha", alpha);
    ADSColors::saveSettings(_settings, key);
}

/*!
 * \brief Load material from \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 */
void Universe1::OpenGL::Material::loadSettings(const QSettings &_settings, const QString &_keyGroup)
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    mode = static_cast<Mode>(_settings.value(key + "mode", static_cast<int>(mode)).toInt());
    shininess = _settings.value(key + "shininess", shininess).toFloat();
    alpha = _settings.value(key + "alpha", alpha).toFloat();
    ADSColors::loadSettings(_settings, key);
}
