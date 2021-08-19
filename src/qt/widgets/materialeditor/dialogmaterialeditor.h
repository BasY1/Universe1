/*!
 * \file qt/widgets/materialeditor/dialogmaterialeditor.h
 * \author Michal Steller
 * \brief Material editor - Main dialog class declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_DIALOGMATERIALEDITOR_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_DIALOGMATERIALEDITOR_H

#include "widgetmaterialeditor.h"

#include <QDialog>

namespace Universe1 {
namespace Widgets {
namespace MaterialEditor {

/*!
 * \brief Material editor root dialog
 */
class DialogMaterialEditor : public QDialog
{
    Q_OBJECT
 public:
    explicit DialogMaterialEditor(OpenGL::MaterialDB *_materialDB, QWidget *_parent = nullptr);
    ~DialogMaterialEditor();

    inline const OpenGL::Material &material() const;

 protected:
    WidgetMaterialEditor *m_rootWidget;  //!< The root widget
};

/*!
 * \brief Getter for selected material
 * \returns Selected material
 */
inline const OpenGL::Material &DialogMaterialEditor::material() const
{
    return m_rootWidget->material();
}

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_DIALOGMATERIALEDITOR_H
