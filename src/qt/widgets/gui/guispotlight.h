/*!
 * \file qt/widgets/gui/guispotlight.h
 * \author Michal Steller
 * \brief The QT spot light GUI classes declarations
 */

#ifndef UNIVERSE1_WIDGETS_GUI_GUISPOTLIGHT_H
#define UNIVERSE1_WIDGETS_GUI_GUISPOTLIGHT_H

#include "../../opengl/lights.h"

#include "guicolorads.h"
#include "guivector3d.h"

#include <QComboBox>

namespace Universe1 {
namespace Widgets {
namespace GUI {

/*!
 * \brief Spot light GUI
 */
class GuiSpotLight : public QObject
{
    Q_OBJECT
 public:
    GuiSpotLight(const int _index,
                 const OpenGL::SpotLight &_light,
                 const std::pair<QVector3D, QVector3D> &_sceneRange,
                 const int _decimals,
                 const Qt::Orientation _orientation,
                 QObject *_parent = nullptr);

    inline GuiSpotLight(const int _index,
                        const OpenGL::SpotLight &_light,
                        const std::pair<QVector3D, QVector3D> &_sceneRange,
                        const int _decimals,
                        QObject *_parent = nullptr);

    inline GuiSpotLight(const int _index,
                        const OpenGL::SpotLight &_light,
                        const std::pair<QVector3D, QVector3D> &_sceneRange,
                        const Qt::Orientation _orientation,
                        QObject *_parent = nullptr);

    inline GuiSpotLight(const int _index,
                        const OpenGL::SpotLight &_light,
                        const std::pair<QVector3D, QVector3D> &_sceneRange,
                        QObject *_parent = nullptr);

    ~GuiSpotLight();

    inline int index() const;
    inline const OpenGL::SpotLight &light() const;
    inline QComboBox *lightMode();
    inline GuiVector3D *positionWidgets();
    inline GuiVector3D *directionWidgets();
    inline GuiFloat *cutOffWidgets();
    inline GuiFloat *outerCutOffWidgets();
    inline GuiColorADS *colorsWidgets();
    inline GuiFloat *constantWidgets();
    inline GuiFloat *linearWidgets();
    inline GuiFloat *quadraticWidgets();

    void layoutRow(QGridLayout *_lay, int &_row, const bool _addSingleColor = true);

 public slots:
    void setLight(const OpenGL::SpotLight &_light);
    void setOrientation(Qt::Orientation _orientation);
    void setEnabled(bool _value);

 protected slots:
    void modeChanged(int _idx);
    void positionChanged(const QVector3D &_value);
    void directionChanged(const QVector3D &_value);
    void cutOffChanged(float _value);
    void outerCutOffChanged(float _value);
    void constantChanged(float _value);
    void linearChanged(float _value);
    void quadraticChanged(float _value);
    void adsChanged(const OpenGL::ADSColors &_value);

 protected:
    void connectAll();
    void disconnectAll();

 signals:
    /*!
     * \brief Emits when light was changed
     * \param _index Light index
     * \param _light New light values
     */
    void changed(int _index, const OpenGL::SpotLight &_light);

 protected:
    const int m_index;                 //!< Light index
    OpenGL::SpotLight m_light;         //!< Current light
    QComboBox *m_lightMode;            //!< Light mode combo box
    GuiVector3D *m_position;           //!< Light position widgets
    GuiVector3D *m_direction;          //!< Light direction widgets
    GuiFloat *m_cutOffWidgets;         //!< Cut-off widgets
    GuiFloat *m_outerCutOffWidgets;    //!< Outer cut-off widgets
    GuiFloat *m_constantWidgets;       //!< Constant attenuation factor widgets
    GuiFloat *m_linearWidgets;         //!< Linear attenuation factor widgets
    GuiFloat *m_quadraticWidgets;      //!< Quadratic attenuation factor widgets
    GuiColorADS *m_colors;             //!< Ambient - diffuse - specular color widgets
};

/*!
 * \brief Constructor
 * \param _index Light index
 * \param _light Initialization light
 * \param _sceneRange Scene range - light position range will be + 50% greater
 * \param _decimals Decimal count (range 0 to 6)
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 * \note Default decimal count 3
 */
inline GuiSpotLight::GuiSpotLight(const int _index,
                                  const OpenGL::SpotLight &_light,
                                  const std::pair<QVector3D, QVector3D> &_sceneRange,
                                  const int _decimals,
                                  QObject *_parent)
    : GuiSpotLight(_index, _light, _sceneRange, _decimals, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Constructor
 * \param _index Light index
 * \param _light Initialization light
 * \param _sceneRange Scene range - light position range will be + 50% greater
 * \param _orientation Widgets orientation
 * \param _parent Parent \c QObject
 * \note Default decimal count 3
 */
inline GuiSpotLight::GuiSpotLight(const int _index,
                                  const OpenGL::SpotLight &_light,
                                  const std::pair<QVector3D, QVector3D> &_sceneRange,
                                  const Qt::Orientation _orientation,
                                  QObject *_parent)
    : GuiSpotLight(_index, _light, _sceneRange, 3, _orientation, _parent)
{
}
/*!
 * \brief Constructor
 * \param _index Light index
 * \param _light Initialization light
 * \param _sceneRange Scene range - light position range will be + 50% greater
 * \param _parent Parent \c QObject
 * \note Default horizontal orientation
 * \note Default decimal count 3
 */
inline GuiSpotLight::GuiSpotLight(const int _index,
                                  const OpenGL::SpotLight &_light,
                                  const std::pair<QVector3D, QVector3D> &_sceneRange,
                                  QObject *_parent)
    : GuiSpotLight(_index, _light, _sceneRange, 3, Qt::Horizontal, _parent)
{
}

/*!
 * \brief Getter for light index
 * \returns Light index
 */
inline int GuiSpotLight::index() const
{
    return m_index;
}

/*!
 * \brief Getter for current light
 * \returns Current light
 */
inline const OpenGL::SpotLight &GuiSpotLight::light() const
{
    return m_light;
}

/*!
 * \brief Getter for light mode combo box
 * \returns Light mode combo box
 */
inline QComboBox *GuiSpotLight::lightMode()
{
    return m_lightMode;
}

/*!
 * \brief Getter for position widgets
 * \returns Position widgets
 */
inline GuiVector3D *GuiSpotLight::positionWidgets()
{
    return m_position;
}

/*!
 * \brief Getter for direction widgets
 * \returns Direction widgets
 */
inline GuiVector3D *GuiSpotLight::directionWidgets()
{
    return m_direction;
}

/*!
 * \brief Getter for cut-off widgets
 * \returns Cut-off widgets
 */
inline GuiFloat *GuiSpotLight::cutOffWidgets()
{
    return m_cutOffWidgets;
}

/*!
 * \brief Getter for outer cut-off widgets
 * \returns Outer cut-off widgets
 */
inline GuiFloat *GuiSpotLight::outerCutOffWidgets()
{
    return m_outerCutOffWidgets;
}

/*!
 * \brief Getter for constant attenuation factor widgets
 * \returns Constant attenuation factor widgets
 */
inline GuiFloat *GuiSpotLight::constantWidgets()
{
    return m_constantWidgets;
}

/*!
 * \brief Getter for linear attenuation factor widgets
 * \returns Linear attenuation factor widgets
 */
inline GuiFloat *GuiSpotLight::linearWidgets()
{
    return m_linearWidgets;
}

/*!
 * \brief Getter for quadratic attenuation factor widgets
 * \returns Quadratic attenuation factor widgets
 */
inline GuiFloat *GuiSpotLight::quadraticWidgets()
{
    return m_quadraticWidgets;
}

/*!
 * \brief Getter for colors widgets
 * \returns Colors widgets
 */
inline GuiColorADS *GuiSpotLight::colorsWidgets()
{
    return m_colors;
}

}  // namespace GUI
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_GUI_GUISPOTLIGHT_H
