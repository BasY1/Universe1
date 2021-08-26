/*!
 * \file qt/opengl/adscolors.h
 * \author Michal Steller
 * \brief Base QT Open GL ambient - diffuse - specular colors class declarations
 */

#ifndef UNIVERSE1_OPENGL_ADSCOLORS_H
#define UNIVERSE1_OPENGL_ADSCOLORS_H

#include <QColor>
#include <QSettings>
#include <QVector3D>

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Base class for ambient - diffuse - specular colors objects
 */
struct ADSColors
{
    QColor ambient;   //!< Ambient color
    QColor diffuse;   //!< Diffuse color
    QColor specular;  //!< Specular color

    ADSColors();
    ADSColors(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular);

    inline QVector3D ambientVector() const;
    inline QVector3D diffuseVector() const;
    inline QVector3D specularVector() const;

    inline ADSColors darkerColors(int _factor = 200) const;
    inline ADSColors lighterColors(int _factor = 150) const;

    void setColorAll(const QColor &_color);

    virtual void saveSettings(QSettings &_settings, const QString &_keyGroup) const;
    virtual void loadSettings(const QSettings &_settings, const QString &_keyGroup);

    static QColor ratioColorBlackWhite(const float _ratio);
    static QColor ratioColorWhiteBlack(const float _ratio);
    static QColor ratioColorGreenRed(const float _ratio);
    static QColor ratioColorBlueRed(const float _ratio);
    static QColor ratioColorMagentaRed(const float _ratio);
    static QColor ratioColorRedMagenta(const float _ratio);
};

/*!
 * \brief Getter for ambient color as \c QVector3D
 * \returns Ambient color as \c QVector3D
 */
inline QVector3D ADSColors::ambientVector() const
{
    return QVector3D(ambient.redF(), ambient.greenF(), ambient.blueF());
}

/*!
 * \brief Getter for diffuse color as \c QVector3D
 * \returns Diffuse color as \c QVector3D
 */
inline QVector3D ADSColors::diffuseVector() const
{
    return QVector3D(diffuse.redF(), diffuse.greenF(), diffuse.blueF());
}

/*!
 * \brief Getter for specular color as \c QVector3D
 * \returns Specular color as \c QVector3D
 */
inline QVector3D ADSColors::specularVector() const
{
    return QVector3D(specular.redF(), specular.greenF(), specular.blueF());
}

/*!
 * \brief Returns darker colors
 * \param _factor Darker factor
 * \returns Darker colors
 */
inline ADSColors ADSColors::darkerColors(int _factor) const
{
    return ADSColors(ambient.darker(_factor), diffuse.darker(_factor), specular.darker(_factor));
}

/*!
 * \brief Returns lighter colors
 * \param _factor Lighter factor
 * \returns Lighter colors
 */
inline ADSColors ADSColors::lighterColors(int _factor) const
{
    return ADSColors(ambient.lighter(_factor), diffuse.lighter(_factor), specular.lighter(_factor));
}

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::ADSColors)

#endif  // UNIVERSE1_OPENGL_ADSCOLORS_H
