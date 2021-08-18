/*!
 * \file qt/widgets/materialeditor/widgetmodel.h
 * \author Michal Steller
 * \brief Material editor - base model widget class declaration
 */

#ifndef UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODEL_H
#define UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODEL_H

#include "../../opengl/models/glmodel.h"
#include <QWidget>

namespace Universe1 {
namespace Widgets {
namespace MaterialEditor {

/*!
 * \brief Base abstract class for model widgets
 */
class WidgetModel : public QWidget
{
    Q_OBJECT
 protected:
    explicit WidgetModel(QWidget *_parent = nullptr);

 public:
    /*!
     * \brief Getter for Open GL model object
     * \return Open GL model object
     */
    virtual OpenGL::Models::GLModel *model() = 0;

    /*!
     * \brief Getter for model name
     * \return Model name
     */
    virtual QString name() const = 0;
};

}  // namespace MaterialEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_MATERIALEDITOR_WIDGETMODEL_H
