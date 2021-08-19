/*!
 * \file qt/widgets/gui/guimaterial.h
 * \author Michal Steller
 * \brief The QT material GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUIMATERIAL_H
#define UNIVERSE1_WIDGETS_GUI_GUIMATERIAL_H

#include "../../opengl/material.h"

#include "guicolorads.h"
#include "guifloat.h"

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Material GUI
 */
class GuiMaterial : public QObject
{
    Q_OBJECT
 public:
    GuiMaterial(const OpenGL::Material &_material, const Qt::Orientation _orientation, QObject *_parent = nullptr);

    inline GuiMaterial(const OpenGL::Material &_material, QObject *_parent = nullptr);

    ~GuiMaterial();

    inline const OpenGL::Material &material() const;
    inline GuiFloat *alphaGui();
    inline GuiFloat *shininessGui();
    inline GuiColorADS *colorsGui();

    void layoutRow(QGridLayout *_lay, int &_row, const bool _addSingleColor = true);

 public slots:
    void setMaterial(const OpenGL::Material &_material);

    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);

 protected slots:
    void adsChanged(const OpenGL::ADSColors &_value);
    void shininessChanged(float _value);
    void alphaChanged(float _value);

 signals:
    /*!
     * \brief Emits when material was changed
     * \param _material New material values
     */
    void changed(const OpenGL::Material &_material);

 protected:
    OpenGL::Material m_material;  //!< Current colors
    GuiFloat *m_alpha;            //!< Material alpha widget
    GuiFloat *m_shininess;        //!< Material shininess widget
    GuiColorADS *m_colors;        //!< Ambient - diffuse - specular color widget
};

/*!
 * \brief Constructor
 * \param _material Initialization material
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiMaterial::GuiMaterial(const OpenGL::Material &_material, QObject *_parent)
    : GuiMaterial(_material, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current material
 * \returns Current material
 */
inline const OpenGL::Material &GuiMaterial::material() const
{
    return m_material;
}

/*!
 * \brief Getter for alpha widgets
 * \returns Alpha widgets
 */
inline GuiFloat *GuiMaterial::alphaGui()
{
    return m_alpha;
}

/*!
 * \brief Getter for shininess widgets
 * \returns Shininess widgets
 */
inline GuiFloat *GuiMaterial::shininessGui()
{
    return m_shininess;
}

/*!
 * \brief Getter for colors widgets
 * \returns Colors widgets
 */
inline GuiColorADS *GuiMaterial::colorsGui()
{
    return m_colors;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUIMATERIAL_H
