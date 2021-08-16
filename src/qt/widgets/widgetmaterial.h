/*!
 * \file qt/widgets/widgetmaterial.h
 * \author Michal Steller
 * \brief The QT material widget class declarations
 */

#ifndef UNIVERSE1_WIDGETS_WIDGETMATERIAL_H
#define UNIVERSE1_WIDGETS_WIDGETMATERIAL_H

#include "../opengl/material.h"

#include "widgetcolorads.h"
#include "widgetfloat.h"

namespace Universe1 {
namespace Widgets {

/*!
 * \brief Material widget
 */
class WidgetMaterial : public QWidget
{
    Q_OBJECT
 public:
    WidgetMaterial(const OpenGL::Material &_material, const Qt::Orientation _orientation, QWidget *_parent = nullptr);

    inline WidgetMaterial(const OpenGL::Material &_material, QWidget *_parent = nullptr);

    ~WidgetMaterial();

    inline const OpenGL::Material &material() const;

 public slots:
    void setMaterial(const OpenGL::Material &_material);

 protected slots:
    void adsChanged(const OpenGL::ADSColors &_value);
    void shininessChanged(float _value);

 signals:
    /*!
     * \brief Emits when material was changed
     * \param _material New material values
     */
    void changed(const OpenGL::Material &_material);

 protected:
    OpenGL::Material m_material;  //!< Current colors
    WidgetFloat *m_shininess;     //!< Material shininess widget
    WidgetColorADS *m_colors;     //!< Ambient - diffuse - specular color widget
};

/*!
 * \brief Constructor
 * \param _material Initialization material
 * \param _parent Parent \c QWidget
 * \note Default horizontal orientation
 */
inline WidgetMaterial::WidgetMaterial(const OpenGL::Material &_material, QWidget *_parent)
    : WidgetMaterial(_material, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current material
 * \return Current material
 */
inline const OpenGL::Material &WidgetMaterial::material() const
{
    return m_material;
}

}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_WIDGETMATERIAL_H
