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
