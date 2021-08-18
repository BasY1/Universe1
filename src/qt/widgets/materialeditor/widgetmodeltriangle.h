/*!
 * \file qt/widgets/materialeditor/widgetmodeltriangle.h
 * \author Michal Steller
 * \brief Material editor - Triangle model widget class declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELTRIANGLE_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELTRIANGLE_H

#include "../../opengl/models/trianglemodel.h"

#include "widgetmodel.h"

#include <QCheckBox>
#include <QComboBox>

namespace Universe1 {
namespace Widgets {
namespace MaterialEditor {

/*!
 * \brief Triangle model widget
 */
class WidgetModelTriangle : public WidgetModel
{
    Q_OBJECT
 public:
    explicit WidgetModelTriangle(OpenGL::Models::TriangleModel *_model, QWidget *_parent = nullptr);
    ~WidgetModelTriangle();

    OpenGL::Models::GLModel *model() override;
    QString name() const override;

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

    OpenGL::Models::TriangleModel *m_model;  //!< Triangle model

    QCheckBox *m_boxCWW;     //!< Counter-clockwise check-box
    QComboBox *m_boxNormal;  //!< Vertex normal selector
};

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODELTRIANGLE_H
