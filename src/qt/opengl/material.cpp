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
    shininess = _settings.value(key + "shininess", shininess).toFloat();
    alpha = _settings.value(key + "alpha", alpha).toFloat();
    ADSColors::loadSettings(_settings, key);
}

/*!
 * \brief Constructor
 * \param _material Default material
 * \param _parent parent \c QObject
 */
Universe1::OpenGL::MaterialDB::MaterialDB(const Material &_material, QObject *_parent)
    : QObject(_parent)
    , m_defaultMaterial(_material)
{
}

/*!
 * \brief Getter for present names
 * \returns Names collection
 */
QStringList Universe1::OpenGL::MaterialDB::names() const
{
    QStringList result;
    for (const std::pair<const QString, Material> &p : m_map)
        result.push_back(p.first);
    return result;
}
