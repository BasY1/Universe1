/*!
 * \file qt/widgets/materialeditor/widgetmodels.h
 * \author Michal Steller
 * \brief Material editor - Models widget classes declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H

#include "../../opengl/models/modelarrow.h"
#include "../../opengl/models/modelbox.h"
#include "../../opengl/models/modelplane.h"
#include "../../opengl/models/modelsphere.h"
#include "../../opengl/models/modeltriangle.h"

#include "../gui/guiint.h"
#include "../gui/guimaterial.h"
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
    void normal1XChanged(float _value);
    void normal2ZChanged(float _value);

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Box model widget
 */
class WidgetModelBox : public QWidget
{
    Q_OBJECT
 public:
    explicit WidgetModelBox(OpenGL::Models::ModelBox *_model, QWidget *_parent = nullptr);
    ~WidgetModelBox();

 signals:
    /*!
     * \brief Wire-frame changed
     * \param _value New flag value
     */
    void wireFrameChanged(bool _value);

    /*!
     * \brief Box normal setup changed
     * \param _value New normal setup value
     */
    void normalSetupChanged(OpenGL::Models::ModelBox::NormalSetup _value);

    /*!
     * \brief Box size 1 changed
     * \param _value New box size 1
     */
    void boxSize1Changed(float _value);

    /*!
     * \brief Box size 2 changed
     * \param _value New box size 2
     */
    void boxSize2Changed(float _value);

    /*!
     * \brief Box size 3 changed
     * \param _value New box size 3
     */
    void boxSize3Changed(float _value);

 protected slots:
    void normalComboChanged(int _idx);

 protected:
    OpenGL::Models::ModelBox *m_model;  //!< Box model

    QCheckBox *m_wireFrame;     //!< Draw wire-frame check-box
    QComboBox *m_normalSetup;   //!< Box normal setup combo-box
    GUI::GuiFloat *m_boxSize1;  //!< Box size 1 GIU
    GUI::GuiFloat *m_boxSize2;  //!< Box size 2 GIU
    GUI::GuiFloat *m_boxSize3;  //!< Box size 3 GIU
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Arrow model widget
 */
class WidgetModelArrow : public QWidget
{
    Q_OBJECT
 public:
    explicit WidgetModelArrow(OpenGL::Models::ModelArrow *_model, QWidget *_parent = nullptr);
    ~WidgetModelArrow();

 signals:
    /*!
     * \brief Wire-frame changed
     * \param _value New flag value
     */
    void wireFrameChanged(bool _value);

    /*!
     * \brief Point count on circle changed
     * \param _value New point count
     */
    void circlePointCountChanged(int _value);

    /*!
     * \brief Line material changed
     * \param _value New material
     */
    void materialLineChanged(const OpenGL::Material &_value);

    /*!
     * \brief Bottom material changed
     * \param _value New material
     */
    void materialBottomChanged(const OpenGL::Material &_value);

 protected:
    OpenGL::Models::ModelArrow *m_model;  //!< Arrow model

    QCheckBox *m_wireFrame;           //!< Draw wire-frame check-box
    GUI::GuiInt *m_circlePointCount;  //!< Point count on circle widget

    GUI::GuiMaterial *m_guiLine;    //!< Line material GUI
    GUI::GuiMaterial *m_guiBottom;  //!< Header bottom material GUI

    QTabWidget *m_tabs;  //!< Materials tab
};

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H
