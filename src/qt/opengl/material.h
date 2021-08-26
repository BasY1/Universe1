/*!
 * \file qt/opengl/material.h
 * \author Michal Steller
 * \brief The QT Open GL material class declarations
 */

#ifndef UNIVERSE1_OPENGL_MATERIAL_H
#define UNIVERSE1_OPENGL_MATERIAL_H

#include "adscolors.h"

#include <QObject>
#include <map>

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Material properties
 */
struct Material : public ADSColors
{
    /*!
     * \brief Material modes
     */
    enum Mode : int
    {
        MaterialADS = 0,       //!< Dynamic ambient - diffuse - specular material
        MaterialAmbient = 1,   //!< Forced ambient color mode (no light calculations)
        MaterialDiffuse = 2,   //!< Forced diffuse color mode (no light calculations)
        MaterialSpecular = 3,  //!< Forced specular color mode (no light calculations)
    };

    Mode mode;        //!< Material mode
    float shininess;  //!< Material shininess
    float alpha;      //!< Material alpha

    Material(const QColor &_ambient,
             const QColor &_diffuse,
             const QColor &_specular,
             const float _shininess,
             const float _alpha);

    Material(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular);

    Material(const ADSColors &_colors, const float _shininess, const float _alpha);
    Material(const ADSColors &_colors);
    Material();

    inline Material darker(int _factor = 200) const;
    inline Material lighter(int _factor = 150) const;

    void saveSettings(QSettings &_settings, const QString &_keyGroup) const;
    void loadSettings(const QSettings &_settings, const QString &_keyGroup);
};

/*!
 * \brief Returns material with darker colors and same shininess and alpha
 * \param _factor Darker factor
 * \returns Darker colors material
 */
inline Material Material::darker(int _factor) const
{
    return Material(ambient.darker(_factor), diffuse.darker(_factor), specular.darker(_factor), shininess, alpha);
}

/*!
 * \brief Returns material with lighter colors and same shininess and alpha
 * \param _factor Lighter factor
 * \returns Lighter colors material
 */
inline Material Material::lighter(int _factor) const
{
    return Material(ambient.lighter(_factor), diffuse.lighter(_factor), specular.lighter(_factor), shininess, alpha);
}

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::Material)

#endif  // UNIVERSE1_OPENGL_MATERIAL_H
