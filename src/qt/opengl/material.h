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

    Material(const Mode _mode,
             const QColor &_ambient,
             const QColor &_diffuse,
             const QColor &_specular,
             const float _shininess,
             const float _alpha);

    inline Material(const QColor &_ambient,
                    const QColor &_diffuse,
                    const QColor &_specular,
                    const float _shininess,
                    const float _alpha);

    inline Material(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular);

    inline Material(const ADSColors &_colors, const float _shininess, const float _alpha);
    inline Material(const ADSColors &_colors);
    inline Material();

    inline Material(const Mode _mode, const Material &_other);

    inline Material darker(int _factor = 200) const;
    inline Material lighter(int _factor = 150) const;

    void saveSettings(QSettings &_settings, const QString &_keyGroup) const;
    void loadSettings(const QSettings &_settings, const QString &_keyGroup);

    static const QColor colorSpecular;       //!< Default specular color
    static const QColor colorSpecularLight;  //!< Default specular color lighter version
    static const QColor colorSpecularDark;   //!< Default specular color darker version

    static const Material materialWhite;       //!< White material
    static const Material materialWhiteLight;  //!< White material - lighter version
    static const Material materialWhiteDark;   //!< White material - darker version

    static const Material materialRed;       //!< Red material
    static const Material materialRedLight;  //!< Red material - lighter version
    static const Material materialRedDark;   //!< Red material - darker version

    static const Material materialGreen;       //!< Green material
    static const Material materialGreenLight;  //!< Green material - lighter version
    static const Material materialGreenDark;   //!< Green material - darker version

    static const Material materialBlue;       //!< Blue material
    static const Material materialBlueLight;  //!< Blue material - lighter version
    static const Material materialBlueDark;   //!< Blue material - darker version

    static const Material materialCyan;       //!< Cyan material
    static const Material materialCyanLight;  //!< Cyan material - lighter version
    static const Material materialCyanDark;   //!< Cyan material - darker version

    static const Material materialMagenta;       //!< Magenta material
    static const Material materialMagentaLight;  //!< Magenta material - lighter version
    static const Material materialMagentaDark;   //!< Magenta material - darker version

    static const Material materialYellow;       //!< Yellow material
    static const Material materialYellowLight;  //!< Yellow material - lighter version
    static const Material materialYellowDark;   //!< Yellow material - darker version

    static const Material &materialAntiRed();         //!< Anti-red (cyan) material
    static const Material &materialAntiRedLight();    //!< Anti-red (cyan) light material
    static const Material &materialAntiRedDark();     //!< Anti-red (cyan) dark material
    static const Material &materialAntiGreen();       //!< Anti-green (magenta) material
    static const Material &materialAntiGreenLight();  //!< Anti-green (magenta) light material
    static const Material &materialAntiGreenDark();   //!< Anti-green (magenta) dark material
    static const Material &materialAntiBlue();        //!< Anti-blue (yellow) material
    static const Material &materialAntiBlueLight();   //!< Anti-blue (yellow) light material
    static const Material &materialAntiBlueDark();    //!< Anti-blue (yellow) dark material

    static const Material &materialAntiCyan();          //!< Anti-red (red) material
    static const Material &materialAntiCyanLight();     //!< Anti-red (red) light material
    static const Material &materialAntiCyanDark();      //!< Anti-red (red) dark material
    static const Material &materialAntiMagenta();       //!< Anti-green (green) material
    static const Material &materialAntiMagentaLight();  //!< Anti-green (green) light material
    static const Material &materialAntiMagentaDark();   //!< Anti-green (green) dark material
    static const Material &materialAntiYellow();        //!< Anti-blue (blue) material
    static const Material &materialAntiYellowLight();   //!< Anti-blue (blue) light material
    static const Material &materialAntiYellowDark();    //!< Anti-blue (blue) dark material

    static Material ratioBlackWhite(const float _ratio);
    static Material ratioWhiteBlack(const float _ratio);
    static Material ratioGreenRed(const float _ratio);
    static Material ratioBlueRed(const float _ratio);
    static Material ratioMagentaRed(const float _ratio);
    static Material ratioRedMagenta(const float _ratio);
};

/*!
 * \brief Constructor
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 * \param _shininess Material shininess
 * \param _alpha Material color alpha
 */
inline Material::Material(
    const QColor &_ambient, const QColor &_diffuse, const QColor &_specular, const float _shininess, const float _alpha)
    : Material(MaterialADS, _ambient, _diffuse, _specular, _shininess, _alpha)
{
}

/*!
 * \brief Constructor
 * \param _ambient Ambient color
 * \param _diffuse Diffuse color
 * \param _specular Specular color
 */
inline Material::Material(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular)
    : Material(_ambient, _diffuse, _specular, 32.0F, 1.0F)
{
}

/*!
 * \brief Constructor
 * \param _colors Ambient - Diffuse - Specular colors
 * \param _shininess Material shininess
 * \param _alpha Material color alpha
 */
inline Material::Material(const ADSColors &_colors, const float _shininess, const float _alpha)
    : Material(_colors.ambient, _colors.diffuse, _colors.specular, _shininess, _alpha)
{
}

/*!
 * \brief Constructor
 * \param _colors Ambient - Diffuse - Specular colors
 */
inline Material::Material(const ADSColors &_colors)
    : Material(_colors.ambient, _colors.diffuse, _colors.specular)
{
}

/*!
 * \brief Default constructor
 */
inline Material::Material()
    : Material(ADSColors())
{
}

/*!
 * \brief Tool constructor - prepare material in specific mode
 * \param _mode Initial material mode
 * \param _other Other material properties
 */
inline Material::Material(const Mode _mode, const Material &_other)
    : Material(_mode, _other.ambient, _other.diffuse, _other.specular, _other.shininess, _other.alpha)
{
}

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
