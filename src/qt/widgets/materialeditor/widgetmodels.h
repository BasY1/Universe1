/*!
 * \file qt/widgets/materialeditor/widgetmodels.h
 * \author Michal Steller
 * \brief Material editor - Models widget classes declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H

#include "../../opengl/models/modelsphere.h"
#include "../../opengl/models/modeltriangle.h"

#include "../gui/guiint.h"

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

 protected slots:
    void normalChanged(int _currentIndex);

 protected:
    /*!
     * \brief Tool structure for selection normal values
     */
    struct NormalSetup
    {
        QString name;       //!< Selection name
        QVector3D normal1;  //!< Selection vertex normal 1 value
        QVector3D normal2;  //!< Selection vertex normal 2 value
        QVector3D normal3;  //!< Selection vertex normal 3 value

        static NormalSetup fromAngle(const float _angle, const QString &_nameExt = QString());
    };

    static const std::vector<NormalSetup> m_normals;  //!< Collection of normal selection values

    OpenGL::Models::ModelTriangle *m_model;  //!< Triangle model

    QCheckBox *m_wireFrame;  //!< Draw wire-frame check-box
    QCheckBox *m_boxCWW;     //!< Counter-clockwise check-box
    QComboBox *m_boxNormal;  //!< Vertex normal selector
};

/*!
 * \brief Sphere model widget
 */
class WidgetModelSphere : public QWidget
{
    Q_OBJECT
 public:
    explicit WidgetModelSphere(OpenGL::Models::ModelSphere *_model, QWidget *_parent = nullptr);
    ~WidgetModelSphere();

 protected:
    OpenGL::Models::ModelSphere *m_model;  //!< Sphere model

    QCheckBox *m_wireFrame;            //!< Draw wire-frame check-box
    GUI::GuiInt *m_equatorPointCount;  //!< Point count on equator widget
};

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELS_H
