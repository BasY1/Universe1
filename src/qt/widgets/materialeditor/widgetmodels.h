/*!
 * \file qt/widgets/materialeditor/widgetmodels.h
 * \author Michal Steller
 * \brief Material editor - Models widget classes declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H

#include "../../opengl/models/modelplane.h"
#include "../../opengl/models/modelsphere.h"
#include "../../opengl/models/modeltriangle.h"

#include "../gui/guiint.h"
#include "../gui/guivector3d.h"

#include <QCheckBox>
#include <QComboBox>

namespace Universe1 {
namespace Widgets {
namespace MaterialEditor {

/*!
 * \brief Triangle model widget
 */
class WidgetModelTriangle : public QWidget
{
    Q_OBJECT
 public:
    explicit WidgetModelTriangle(OpenGL::Models::ModelTriangle *_model, QWidget *_parent = nullptr);
    ~WidgetModelTriangle();

 signals:
    /*!
     * \brief Wire-frame changed
     * \param _value New flag value
     */
    void wireFrameChanged(bool _value);

    /*!
     * \brief Counter-clockwise check-box changed
     * \param _value New flag value
     */
    void ccwChanged(bool _value);

    /*!
     * \brief Normal vertex 1 changed
     * \param _value New value
     */
    void normal1Changed(const QVector3D &_value);

    /*!
     * \brief Normal vertex 2 changed
     * \param _value New value
     */
    void normal2Changed(const QVector3D &_value);

    /*!
     * \brief Normal vertex 3 changed
     * \param _value New value
     */
    void normal3Changed(const QVector3D &_value);

 protected:
    OpenGL::Models::ModelTriangle *m_model;  //!< Triangle model

    QCheckBox *m_wireFrame;          //!< Draw wire-frame check-box
    QCheckBox *m_boxCWW;             //!< Counter-clockwise check-box
    GUI::GuiVector3D *m_guiNormal1;  //!< Normal vertex 1 widgets
    GUI::GuiVector3D *m_guiNormal2;  //!< Normal vertex 2 widgets
    GUI::GuiVector3D *m_guiNormal3;  //!< Normal vertex 3 widgets
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Sphere model widget
 */
class WidgetModelSphere : public QWidget
{
    Q_OBJECT
 public:
    explicit WidgetModelSphere(OpenGL::Models::ModelSphere *_model, QWidget *_parent = nullptr);
    ~WidgetModelSphere();

 signals:
    /*!
     * \brief Wire-frame changed
     * \param _value New flag value
     */
    void wireFrameChanged(bool _value);

    /*!
     * \brief Point count on equator changed
     * \param _value New point count
     */
    void equatorPointCountChanged(int _value);

 protected:
    OpenGL::Models::ModelSphere *m_model;  //!< Sphere model

    QCheckBox *m_wireFrame;            //!< Draw wire-frame check-box
    GUI::GuiInt *m_equatorPointCount;  //!< Point count on equator widget
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Plane model widget
 */
class WidgetModelPlane : public QWidget
{
    Q_OBJECT
 public:
    explicit WidgetModelPlane(OpenGL::Models::ModelPlane *_model, QWidget *_parent = nullptr);
    ~WidgetModelPlane();

 protected slots:

    void normal1XChaged(float _value);
    void normal2ZChaged(float _value);

 signals:
    /*!
     * \brief Wire-frame changed
     * \param _value New flag value
     */
    void wireFrameChanged(bool _value);

    /*!
     * \brief Normal 1 changed
     * \param _value New normal
     */
    void normal1Changed(const QVector3D &_value);

    /*!
     * \brief Normal 2 changed
     * \param _value New normal
     */
    void normal2Changed(const QVector3D &_value);

    /*!
     * \brief Count in direction 1 changed
     * \param _value New direction 1 count
     */
    void dots1Changed(int _value);

    /*!
     * \brief Count in direction 2 changed
     * \param _value New direction 2 count
     */
    void dots2Changed(int _value);

 protected:
    OpenGL::Models::ModelPlane *m_model;  //!< Sphere model

    QVector3D m_normal1;  //!< Normal 1 value
    QVector3D m_normal2;  //!< Normal 2 value

    QCheckBox *m_wireFrame;     //!< Draw wire-frame check-box
    GUI::GuiFloat *m_normal1X;  //!< Normal 1 X widget
    GUI::GuiFloat *m_normal2Z;  //!< Normal 2 Z widget
    GUI::GuiInt *m_dots1Count;  //!< Count in direction 1
    GUI::GuiInt *m_dots2Count;  //!< Count in direction 2
};

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H
