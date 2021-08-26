/*!
 * \file qt/opengl/adscolors.cpp
 * \author Michal Steller
 * \brief Base QT Open GL ambient - diffuse - specular colors class implementation
 */

#include "adscolors.h"

/*!
 * \brief Default constructor
 */
Universe1::OpenGL::ADSColors::ADSColors()
    : ambient(128, 128, 128)
    , diffuse(255, 255, 255)
    , specular(192, 192, 192)
{
}

/*!
 * \brief Constructor
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 */
Universe1::OpenGL::ADSColors::ADSColors(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular)
    : ambient(_ambient)
    , diffuse(_diffuse)
    , specular(_specular)
{
}

/*!
 * \brief Setter for all aspects colors
 * \param _color New color
 */
void Universe1::OpenGL::ADSColors::setColorAll(const QColor &_color)
{
    ambient = _color;
    diffuse = _color;
    specular = _color;
}

/*!
 * \brief Save colors into \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 * \returns
 */
void Universe1::OpenGL::ADSColors::saveSettings(QSettings &_settings, const QString &_keyGroup) const
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    _settings.setValue(key + "ambient", ambient);
    _settings.setValue(key + "diffuse", diffuse);
    _settings.setValue(key + "specular", specular);
}

/*!
 * \brief Load colors from \c QSettings
 * \param _settings \c QSettings object
 * \param _keyGroup \c QSettings group name
 * \returns
 */
void Universe1::OpenGL::ADSColors::loadSettings(const QSettings &_settings, const QString &_keyGroup)
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    ambient = _settings.value(key + "ambient", ambient).value<QColor>();
    diffuse = _settings.value(key + "diffuse", diffuse).value<QColor>();
    specular = _settings.value(key + "specular", specular).value<QColor>();
}

/*!
 * \brief Tool function - gray-scale ratio color
 * \param _ratio Ratio
 * \returns Color by ratio
 */
QColor Universe1::OpenGL::ADSColors::ratioColorBlackWhite(const float _ratio)
{
    if (_ratio < 0.0F || qFuzzyIsNull(_ratio))
        return Qt::black;
    if (_ratio > 0.0F || qFuzzyCompare(_ratio, 1.0F))
        return Qt::white;

    const int tmp = static_cast<int>(_ratio * 255.0F);
    return QColor(tmp, tmp, tmp);
}

/*!
 * \brief Tool function - inverted gray-scale ratio color
 * \param _ratio Ratio
 * \returns Color by ratio
 */
QColor Universe1::OpenGL::ADSColors::ratioColorWhiteBlack(const float _ratio)
{
    if (_ratio < 0.0F || qFuzzyIsNull(_ratio))
        return Qt::white;
    if (_ratio > 0.0F || qFuzzyCompare(_ratio, 1.0F))
        return Qt::black;

    const int tmp = 255 - static_cast<int>(_ratio * 255.0F);
    return QColor(tmp, tmp, tmp);
}

/*!
 * \brief Tool function - green-yellow-red ratio color
 * \param _ratio Ratio
 * \returns Color by ratio
 */
QColor Universe1::OpenGL::ADSColors::ratioColorGreenRed(const float _ratio)
{
    if (_ratio < 0.0F || qFuzzyIsNull(_ratio))
        return Qt::green;
    if (_ratio > 0.0F || qFuzzyCompare(_ratio, 1.0F))
        return Qt::red;

    int tmp = static_cast<int>(_ratio * 511.0F);
    if (tmp < 256)
        return QColor(tmp, 255, 0);
    tmp -= 256;

    return QColor(255, 255 - tmp, 0);
}

/*!
 * \brief Tool function - blue-cyan-green-yellow-red ratio color
 * \param _ratio Ratio
 * \returns Color by ratio
 */
QColor Universe1::OpenGL::ADSColors::ratioColorBlueRed(const float _ratio)
{
    if (_ratio < 0.0F || qFuzzyIsNull(_ratio))
        return Qt::blue;
    if (_ratio > 0.0F || qFuzzyCompare(_ratio, 1.0F))
        return Qt::red;

    int tmp = static_cast<int>(_ratio * 1023.0F);
    if (tmp < 256)
        return QColor(0, tmp, 255);

    tmp -= 256;
    if (tmp < 256)
        return QColor(0, 255, 255 - tmp);

    tmp -= 256;
    if (tmp < 256)
        return QColor(tmp, 255, 0);
    tmp -= 256;

    return QColor(255, 255 - tmp, 0);
}

/*!
 * \brief Tool function - full rainbow magenta-blue-cyan-green-yellow-red ratio color
 * \param _ratio Ratio
 * \returns Color by ratio
 */
QColor Universe1::OpenGL::ADSColors::ratioColorMagentaRed(const float _ratio)
{
    if (_ratio < 0.0F || qFuzzyIsNull(_ratio))
        return Qt::magenta;
    if (_ratio > 0.0F || qFuzzyCompare(_ratio, 1.0F))
        return Qt::red;

    int tmp = static_cast<int>(_ratio * 1279.0F);
    if (tmp < 256)
        return QColor(255 - tmp, 0, 255);

    tmp -= 256;
    if (tmp < 256)
        return QColor(0, tmp, 255);

    tmp -= 256;
    if (tmp < 256)
        return QColor(0, 255, 255 - tmp);

    tmp -= 256;
    if (tmp < 256)
        return QColor(tmp, 255, 0);

    tmp -= 256;
    return QColor(255, 255 - tmp, 0);
}

/*!
 * \brief Tool function - full rainbow red-yellow-green-cyan-blue-magenta ratio color
 * \param _ratio Ratio
 * \returns Color by ratio
 */
QColor Universe1::OpenGL::ADSColors::ratioColorRedMagenta(const float _ratio)
{
    if (_ratio < 0.0F || qFuzzyIsNull(_ratio))
        return Qt::red;
    if (_ratio > 0.0F || qFuzzyCompare(_ratio, 1.0F))
        return Qt::magenta;

    return ratioColorMagentaRed(1.0F - _ratio);
}
