#ifndef UNIVERSE1_VIDEO_MATERIAL_H
#define UNIVERSE1_VIDEO_MATERIAL_H

#include "../math/spherecrosssection.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief OpenGL Material
 */
struct Material
{
    QColor ambient = QColor(192, 192, 192);   //!< Ambient color
    QColor diffuse = QColor(255, 255, 255);   //!< Diffuse color
    QColor specular = QColor(255, 255, 224);  //!< Specular color
    float shine = 32.0f;                      //!< Shine factor
    float alpha = 1.0f;                       //!< Alpha factor

    Material() = default;  //!< Default constructor

    /*!
     * \brief Constructor
     * \param _colorAmbient Ambient color
     * \param _colorDiffuse Diffuse color
     * \param _colorSpecular Specular color
     * \param _shine Shine factor
     * \param _alpha Alpha factor
     */
    inline Material(const QColor _colorAmbient,
                    const QColor _colorDiffuse,
                    const QColor _colorSpecular,
                    const float _shine,
                    const float _alpha)
        : ambient(_colorAmbient)
        , diffuse(_colorDiffuse)
        , specular(_colorSpecular)
        , shine(_shine)
        , alpha(_alpha)
    {
    }

    /*!
     * \brief Constructor
     * \param _color Base color
     * \param _shine Shine factor
     * \param _alpha Alpha factor
     */
    inline Material(const QColor _color, const float _shine = 32.0f, const float _alpha = 1.0f)
        : ambient(_color.darker())
        , diffuse(_color)
        , specular(QColor(255, 255, 224))
        , shine(_shine)
        , alpha(_alpha)
    {
    }

    /*!
     * \brief Returns lighter material
     * \param _ratioColor Ratio for color
     * \param _ratioShine Ratio for shine factor
     * \param _ratioAlpha Ratio for alpha factor
     * \return Lighter material
     */
    inline Material
    lighter(const int _ratioColor = 150, const float _ratioShine = 0.5f, const float _ratioAlpha = 1.0f) const
    {
        return Material(ambient.lighter(_ratioColor),
                        diffuse.lighter(_ratioColor),
                        QColor(255, 255, 224).lighter(_ratioColor),
                        shine * _ratioShine,
                        std::min(1.0f, alpha * _ratioAlpha));
    }

    /*!
     * \brief Returns darker material
     * \param _ratioColor Ratio for color
     * \param _ratioShine Ratio for shine factor
     * \param _ratioAlpha Ratio for alpha factor
     * \return Darker material
     */
    inline Material
    darker(const int _ratioColor = 200, const float _ratioShine = 2.0f, const float _ratioAlpha = 1.0f) const
    {
        return Material(ambient.darker(_ratioColor),
                        diffuse.darker(_ratioColor),
                        QColor(255, 255, 224).darker(_ratioColor),
                        shine * _ratioShine,
                        std::min(1.0f, alpha * _ratioAlpha));
    }

    /*!
     * \brief Getter for ambient color as 3D vector
     * \return Ambient color as 3D vector
     */
    inline QVector3D ambientF() const
    {
        return QVector3D(ambient.redF(), ambient.greenF(), ambient.blueF());
    }

    /*!
     * \brief Getter for diffuse color as 3D vector
     * \return Diffuse color as 3D vector
     */
    inline QVector3D diffuseF() const
    {
        return QVector3D(diffuse.redF(), diffuse.greenF(), diffuse.blueF());
    }

    /*!
     * \brief Getter for specular color as 3D vector
     * \return Specular color as 3D vector
     */
    inline QVector3D specularF() const
    {
        return QVector3D(specular.redF(), specular.greenF(), specular.blueF());
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_MATERIAL_H
