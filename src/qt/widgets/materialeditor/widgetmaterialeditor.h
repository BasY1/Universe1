/*!
 * \file qt/widgets/materialeditor/widgetmaterialeditor.h
 * \author Michal Steller
 * \brief Material editor - Main widget class declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMATERIALEDITOR_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMATERIALEDITOR_H

#include "../gui/guidirectionlight.h"
#include "../gui/guimaterial.h"
#include "../gui/guipointlight.h"

#include "../widgetglsettings.h"

#include "widgetmodels.h"
#include "widgetview.h"

#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QTabWidget>
#include <QTableWidget>

namespace Universe1 {
namespace Widgets {
namespace MaterialEditor {

/*!
 * \brief Material editor root widget
 */
class WidgetMaterialEditor : public QSplitter
{
    Q_OBJECT
 public:
    explicit WidgetMaterialEditor(OpenGL::MaterialDB *_materialDB, QWidget *_parent = nullptr);
    ~WidgetMaterialEditor();

    inline const OpenGL::Material &material() const;

 protected slots:
    void materialNameChanged(QString _materialName);
    void namesCurrentChanged(QTableWidgetItem *_current, QTableWidgetItem *_previous);
    void namesDoubleClicked(QTableWidgetItem *_item);
    void addClicked();
    void delClicked();

    void pointLightChanged(int _idx, const OpenGL::PointLight &_pointLight);

 protected:
    OpenGL::MaterialDB *m_materialDB;  //!< Processing material database

    WidgetView *m_view;  //!< Editor's Open GL view

    GUI::GuiFloat *m_sceneAmbient;    //!< Scene ambient factor
    GUI::GuiMaterial *m_guiMaterial;  //!< Material GUI widgets
    QLineEdit *m_materialName;        //!< Line editor for material name
    QPushButton *m_addMaterial;       //!< Add material button
    QPushButton *m_delMaterial;       //!< Delete material button
    QTableWidget *m_tableDB;          //!< Material names table

    GUI::GuiDirectionLight *m_guiDirectionLight;                                   //!< Direction light GUI widgets
    GUI::GuiPointLight *m_guiPointLight[OpenGL::ShaderProgram::pointLightsCount];  //!< Point light GUI widgets

    WidgetGLSettings *m_widgetGLSettings;  //!< Open GL settings widget

    WidgetModelSphere *m_widgetSphere;      //!< Sphere model widget
    WidgetModelBox *m_widgetBox;            //!< Box model widget
    WidgetModelTriangle *m_widgetTriangle;  //!< Triangle model widget
    WidgetModelPlane *m_widgetPlane;        //!< Plane model widget

    QTabWidget *m_tabModels;       //!< Tab for model widgets and current model selection
    QTabWidget *m_tabPointLights;  //!< Tab for point lights collection
    QTabWidget *m_tabSettings;     //!< Main setting tab
};

/*!
 * \brief Getter for current material
 * \returns Current material
 */
inline const OpenGL::Material &WidgetMaterialEditor::material() const
{
    return m_guiMaterial->material();
}

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMATERIALEDITOR_H
