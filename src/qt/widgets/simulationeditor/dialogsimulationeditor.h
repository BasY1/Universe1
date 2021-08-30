/*!
 * \file qt/widgets/simulationeditor/dialogsimulationeditor.h
 * \author Michal Steller
 * \brief Simulation editor - Main dialog class declaration
 */

#ifndef UNIVERSE1_WIDGETS_SIMULATIONEDITOR_DIALOGSIMULATIONEDITOR_H
#define UNIVERSE1_WIDGETS_SIMULATIONEDITOR_DIALOGSIMULATIONEDITOR_H

#include "widgetsimulationeditor.h"

#include <QDialog>

namespace Universe1 {
namespace Widgets {
namespace SimulationEditor {

/*!
 * \brief Simulation editor root dialog
 */
class DialogSimulationEditor : public QDialog
{
    Q_OBJECT
 public:
    explicit DialogSimulationEditor(Project::QSimulation *_simulation, QWidget *_parent = nullptr);
    ~DialogSimulationEditor();

 protected:
    WidgetSimulationEditor *m_rootWidget;  //!< The root widget
};

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_DIALOGSIMULATIONEDITOR_H
