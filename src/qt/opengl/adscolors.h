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
    QVector3D ambient;   //!< Ambient color
    QVector3D diffuse;   //!< Diffuse color
    QVector3D specular;  //!< Specular color

    inline QColor ambientColor() const;
    inline QColor diffuseColor() const;
    inline QColor specularColor() const;

    inline void setAmbientColor(const QColor _color);
    inline void setDiffuseColor(const QColor _color);
    inline void setSpecularColor(const QColor _color);
};

/*!
 * \brief Getter for ambient color as \c QColor
 * \returns Ambient color as \c QColor
 */
inline QColor ADSColors::ambientColor() const
{
    return QColor::fromRgbF(ambient.x(), ambient.y(), ambient.z());
}

/*!
 * \brief Getter for diffuse color as \c QColor
 * \returns Diffuse color as \c QColor
 */
inline QColor ADSColors::diffuseColor() const
{
    return QColor::fromRgbF(diffuse.x(), diffuse.y(), diffuse.z());
}

/*!
 * \brief Getter for specular color as \c QColor
 * \returns Specular color as \c QColor
 */
inline QColor ADSColors::specularColor() const
{
    return QColor::fromRgbF(specular.x(), specular.y(), specular.z());
}

/*!
 * \brief Set ambient color from \c QColor
 * \param _color New ambient color
 */
inline void ADSColors::setAmbientColor(const QColor _color)
{
    ambient = QVector3D(_color.redF(), _color.greenF(), _color.blueF());
}

/*!
 * \brief Set diffuse color from \c QColor
 * \param _color New diffuse color
 */
inline void ADSColors::setDiffuseColor(const QColor _color)
{
    diffuse = QVector3D(_color.redF(), _color.greenF(), _color.blueF());
}

/*!
 * \brief Set specular color from \c QColor
 * \param _color New specular color
 */
inline void ADSColors::setSpecularColor(const QColor _color)
{
    specular = QVector3D(_color.redF(), _color.greenF(), _color.blueF());
}

}  // namespace OpenGL
}  // namespace Universe1

Q_DECLARE_METATYPE(Universe1::OpenGL::ADSColors)

#endif  // UNIVERSE1_OPENGL_ADSCOLORS_H
