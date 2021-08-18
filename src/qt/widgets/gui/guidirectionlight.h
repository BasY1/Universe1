/*!
 * \file qt/widgets/gui/guidirectionlight.h
 * \author Michal Steller
 * \brief The QT directional light GUI class declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUIDIRECTIONLIGHT_H
#define UNIVERSE1_WIDGETS_GUI_GUIDIRECTIONLIGHT_H

#include "../../opengl/lights.h"

#include "guicolorads.h"
#include "guivector3d.h"

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Direction light GUI
 */
class GuiDirectionLight : public QObject
{
    Q_OBJECT
 public:
    GuiDirectionLight(const OpenGL::DirectionLight &_light,
                      const Qt::Orientation _orientation,
                      QObject *_parent = nullptr);

    inline GuiDirectionLight(const OpenGL::DirectionLight &_light, QObject *_parent = nullptr);

    ~GuiDirectionLight();

    inline const OpenGL::DirectionLight &light() const;
    inline QCheckBox *lightOnOff();
    inline GuiVector3D *directionWidgets();
    inline GuiColorADS *colorsWidgets();

 public slots:
    void setLight(const OpenGL::DirectionLight &_light);
    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);

 protected slots:
    void adsChanged(const OpenGL::ADSColors &_value);
    void directionChanged(const QVector3D &_value);
    void onOffChanged(bool _value);

 signals:
    /*!
     * \brief Emits when light was changed
     * \param _light New light values
     */
    void changed(const OpenGL::DirectionLight &_light);

 protected:
    OpenGL::DirectionLight m_light;  //!< Current light
    QCheckBox *m_lightOnOff;         //!< Enabled check box
    GuiVector3D *m_direction;        //!< Direction normal widget
    GuiColorADS *m_colors;           //!< Ambient - diffuse - specular color widgets
};

/*!
 * \brief Constructor
 * \param _light Initialization light
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 */
inline GuiDirectionLight::GuiDirectionLight(const OpenGL::DirectionLight &_light, QObject *_parent)
    : GuiDirectionLight(_light, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for current light
 * \returns Current light
 */
inline const OpenGL::DirectionLight &GuiDirectionLight::light() const
{
    return m_light;
}

/*!
 * \brief Getter for on/off check box
 * \returns Enabled check box
 */
inline QCheckBox *GuiDirectionLight::lightOnOff()
{
    return m_lightOnOff;
}

/*!
 * \brief Getter for direction widgets
 * \returns Direction widgets
 */
inline GuiVector3D *GuiDirectionLight::directionWidgets()
{
    return m_direction;
}

/*!
 * \brief Getter for colors widgets
 * \returns Colors widgets
 */
inline GuiColorADS *GuiDirectionLight::colorsWidgets()
{
    return m_colors;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUIDIRECTIONLIGHT_H
