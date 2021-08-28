/*!
 * \file qt/opengl/material.cpp
 * \author Michal Steller
 * \brief The QT Open GL material class implementation
 */

#include "material.h"
#include <QSettings>

/*!
 * \brief Constructor
 * \param _mode Initial material mode
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _shininess Material shininess
 * \param _alpha Material color alpha
 */
Universe1::OpenGL::Material::Material(const Mode _mode,
                                      const QColor &_ambient,
                                      const QColor &_diffuse,
                                      const QColor &_specular,
                                      const float _shininess,
                                      const float _alpha)
    : ADSColors(_ambient, _diffuse, _specular)
    , mode(_mode)
    , shininess(_shininess)
    , alpha(_alpha)
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

const QColor Universe1::OpenGL::Material::colorSpecular = QColor(240, 240, 224);
const QColor Universe1::OpenGL::Material::colorSpecularLight = QColor(255, 255, 240);
const QColor Universe1::OpenGL::Material::colorSpecularDark = QColor(224, 224, 208);

#define MATERIAL_DEFAULT_DARK_AMBIENT 150  //!< Default arrow dark ambient color value
#define MATERIAL_DEFAULT_DARK_DIFFUSE 192  //!< Default arrow dark diffuse color value
#define MATERIAL_DEFAULT_AMBIENT 192  //!< Default arrow ambient color value
#define MATERIAL_DEFAULT_DIFFUSE 224  //!< Default arrow diffuse color value
#define MATERIAL_DEFAULT_LIGHT_AMBIENT 224  //!< Default arrow light ambient color value
#define MATERIAL_DEFAULT_LIGHT_DIFFUSE 255  //!< Default arrow light diffuse color value

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialWhite =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_AMBIENT, MATERIAL_DEFAULT_AMBIENT, MATERIAL_DEFAULT_AMBIENT),
                                QColor(MATERIAL_DEFAULT_DIFFUSE, MATERIAL_DEFAULT_DIFFUSE, MATERIAL_DEFAULT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialWhiteLight = Universe1::OpenGL::Material(
    QColor(MATERIAL_DEFAULT_LIGHT_AMBIENT, MATERIAL_DEFAULT_LIGHT_AMBIENT, MATERIAL_DEFAULT_LIGHT_AMBIENT),
    QColor(MATERIAL_DEFAULT_LIGHT_DIFFUSE, MATERIAL_DEFAULT_LIGHT_DIFFUSE, MATERIAL_DEFAULT_LIGHT_DIFFUSE),
    Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialWhiteDark = Universe1::OpenGL::Material(
    QColor(MATERIAL_DEFAULT_DARK_AMBIENT, MATERIAL_DEFAULT_DARK_AMBIENT, MATERIAL_DEFAULT_DARK_AMBIENT),
    QColor(MATERIAL_DEFAULT_DARK_DIFFUSE, MATERIAL_DEFAULT_DARK_DIFFUSE, MATERIAL_DEFAULT_DARK_DIFFUSE),
    Universe1::OpenGL::Material::colorSpecularDark);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialRed =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_AMBIENT, 0, 0),
                                QColor(MATERIAL_DEFAULT_DIFFUSE, 0, 0),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialRedLight =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_LIGHT_AMBIENT, 0, 0),
                                QColor(MATERIAL_DEFAULT_LIGHT_DIFFUSE, 0, 0),
                                Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialRedDark =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_DARK_AMBIENT, 0, 0),
                                QColor(MATERIAL_DEFAULT_DARK_DIFFUSE, 0, 0),
                                Universe1::OpenGL::Material::colorSpecularDark);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialGreen =
    Universe1::OpenGL::Material(QColor(0, MATERIAL_DEFAULT_AMBIENT, 0),
                                QColor(0, MATERIAL_DEFAULT_DIFFUSE, 0),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialGreenLight =
    Universe1::OpenGL::Material(QColor(0, MATERIAL_DEFAULT_LIGHT_AMBIENT, 0),
                                QColor(0, MATERIAL_DEFAULT_LIGHT_DIFFUSE, 0),
                                Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialGreenDark =
    Universe1::OpenGL::Material(QColor(0, MATERIAL_DEFAULT_DARK_AMBIENT, 0),
                                QColor(0, MATERIAL_DEFAULT_DARK_DIFFUSE, 0),
                                Universe1::OpenGL::Material::colorSpecularDark);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialBlue =
    Universe1::OpenGL::Material(QColor(0, 0, MATERIAL_DEFAULT_AMBIENT),
                                QColor(0, 0, MATERIAL_DEFAULT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialBlueLight =
    Universe1::OpenGL::Material(QColor(0, 0, MATERIAL_DEFAULT_LIGHT_AMBIENT),
                                QColor(0, 0, MATERIAL_DEFAULT_LIGHT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialBlueDark =
    Universe1::OpenGL::Material(QColor(0, 0, MATERIAL_DEFAULT_DARK_AMBIENT),
                                QColor(0, 0, MATERIAL_DEFAULT_DARK_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecularDark);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialCyan =
    Universe1::OpenGL::Material(QColor(0, MATERIAL_DEFAULT_AMBIENT, MATERIAL_DEFAULT_AMBIENT),
                                QColor(0, MATERIAL_DEFAULT_DIFFUSE, MATERIAL_DEFAULT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialCyanLight =
    Universe1::OpenGL::Material(QColor(0, MATERIAL_DEFAULT_LIGHT_AMBIENT, MATERIAL_DEFAULT_LIGHT_AMBIENT),
                                QColor(0, MATERIAL_DEFAULT_LIGHT_DIFFUSE, MATERIAL_DEFAULT_LIGHT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialCyanDark =
    Universe1::OpenGL::Material(QColor(0, MATERIAL_DEFAULT_DARK_AMBIENT, MATERIAL_DEFAULT_DARK_AMBIENT),
                                QColor(0, MATERIAL_DEFAULT_DARK_DIFFUSE, MATERIAL_DEFAULT_DARK_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecularDark);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialMagenta =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_AMBIENT, 0, MATERIAL_DEFAULT_AMBIENT),
                                QColor(MATERIAL_DEFAULT_DIFFUSE, 0, MATERIAL_DEFAULT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialMagentaLight =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_LIGHT_AMBIENT, 0, MATERIAL_DEFAULT_LIGHT_AMBIENT),
                                QColor(MATERIAL_DEFAULT_LIGHT_DIFFUSE, 0, MATERIAL_DEFAULT_LIGHT_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialMagentaDark =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_DARK_AMBIENT, 0, MATERIAL_DEFAULT_DARK_AMBIENT),
                                QColor(MATERIAL_DEFAULT_DARK_DIFFUSE, 0, MATERIAL_DEFAULT_DARK_DIFFUSE),
                                Universe1::OpenGL::Material::colorSpecularDark);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialYellow =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_AMBIENT, MATERIAL_DEFAULT_AMBIENT, 0),
                                QColor(MATERIAL_DEFAULT_DIFFUSE, MATERIAL_DEFAULT_DIFFUSE, 0),
                                Universe1::OpenGL::Material::colorSpecular);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialYellowLight =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_LIGHT_AMBIENT, MATERIAL_DEFAULT_LIGHT_AMBIENT, 0),
                                QColor(MATERIAL_DEFAULT_LIGHT_DIFFUSE, MATERIAL_DEFAULT_LIGHT_DIFFUSE, 0),
                                Universe1::OpenGL::Material::colorSpecularLight);

const Universe1::OpenGL::Material Universe1::OpenGL::Material::materialYellowDark =
    Universe1::OpenGL::Material(QColor(MATERIAL_DEFAULT_DARK_AMBIENT, MATERIAL_DEFAULT_DARK_AMBIENT, 0),
                                QColor(MATERIAL_DEFAULT_DARK_DIFFUSE, MATERIAL_DEFAULT_DARK_DIFFUSE, 0),
                                Universe1::OpenGL::Material::colorSpecularDark);
/*!
 * \brief Anti-red (cyan) material
 * \returns Anti-red (cyan) material
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiRed()
{
    return materialCyan;
}

/*!
 * \brief Anti-red (cyan) material - lighter version
 * \returns Anti-red (cyan) material - lighter version
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiRedLight()
{
    return materialCyanLight;
}

/*!
 * \brief Anti-red (cyan) material - darker version
 * \returns Anti-red (cyan) material - darker version
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiRedDark()
{
    return materialCyanDark;
}

/*!
 * \brief Anti-green (magenta) material
 * \returns Anti-green (magenta) material
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiGreen()
{
    return materialMagenta;
}

/*!
 * \brief Anti-green (magenta) material - lighter version
 * \returns Anti-green (magenta) material - lighter version
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiGreenLight()
{
    return materialMagentaLight;
}

/*!
 * \brief Anti-green (magenta) material - darker version
 * \returns Anti-green (magenta) material - darker version
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiGreenDark()
{
    return materialMagentaDark;
}

/*!
 * \brief Anti-blue (yellow) material
 * \returns Anti-blue (yellow) material
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiBlue()
{
    return materialYellow;
}

/*!
 * \brief Anti-blue (yellow) material - lighter version
 * \returns Anti-blue (yellow) material - lighter version
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiBlueLight()
{
    return materialYellowLight;
}

/*!
 * \brief Anti-blue (yellow) material - darker version
 * \returns Anti-blue (yellow) material - darker version
 */
const Universe1::OpenGL::Material &Universe1::OpenGL::Material::materialAntiBlueDark()
{
    return materialYellowDark;
}
