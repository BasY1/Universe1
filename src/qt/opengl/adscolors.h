/*!
 * \file qt/opengl/adscolors.h
 * \author Michal Steller
 * \brief Base QT Open GL ambient - diffuse - specular colors class declarations
 */

#ifndef UNIVERSE1_OPENGL_ADSCOLORS_H
#define UNIVERSE1_OPENGL_ADSCOLORS_H

#include <QColor>
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

    inline QVector3D ambientVector() const;
    inline QVector3D diffuseVector() const;
    inline QVector3D specularVector() const;

    ADSColors();
    ADSColors(const QColor &_ambient, const QColor &_diffuse, const QColor &_specular);
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

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::ADSColors)

#endif  // UNIVERSE1_OPENGL_ADSCOLORS_H
