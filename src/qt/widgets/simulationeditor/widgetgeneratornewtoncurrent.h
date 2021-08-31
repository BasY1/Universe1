/*!
 * \file qt/widgets/simulationeditor/widgetgeneratornewtoncurrent.h
 * \author Michal Steller
 * \brief Newton current simulation initialization data generator widget classes declaration
 */

#ifndef UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEWTONCURRENT_H
#define UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEWTONCURRENT_H

#include "../../project/qsimulationnewtoncurrent.h"

#include "../horizontallinespacer.h"

#include "../gui/guiint.h"
#include "../gui/guivector3d.h"

#include <QCheckBox>
#include <QComboBox>
#include <QWidget>

namespace Universe1 {
namespace Widgets {
namespace SimulationEditor {

/*!
 * \brief Newton current simulation initialization data generator widget - base abstract class
 */
class WidgetGeneratorNewtonCurrent : public QWidget
{
    Q_OBJECT
 protected:
    WidgetGeneratorNewtonCurrent(Project::QSimulationNewtonCurrent *_simulation, QWidget *_parent = nullptr);

 public:
    inline Project::QSimulationNewtonCurrent *simulationNewtonCurrent();
    inline const std::vector<Project::QSimulationNewtonCurrent::InitObject> &initObjects() const;

    /*!
     * \brief Pure virtual generator name getter
     * \returns Generator name
     */
    virtual QString generatorName() const = 0;

 protected:
    Project::QSimulationNewtonCurrent *m_simulation;  //!< Processing Newton current simulation

    std::vector<Project::QSimulationNewtonCurrent::InitObject> m_initObjects;  //!< Initialization data
};

/*!
 * \brief Getter for processed simulation object
 * \returns Processed simulation object
 */
inline Project::QSimulationNewtonCurrent *WidgetGeneratorNewtonCurrent::simulationNewtonCurrent()
{
    return m_simulation;
}

/*!
 * \brief Getter for generated initialization data
 * \returns Initialization data
 */
inline const std::vector<Project::QSimulationNewtonCurrent::InitObject> &
WidgetGeneratorNewtonCurrent::initObjects() const
{
    return m_initObjects;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Newton current simulation initialization data generator widget - 2 or 3 objects
 */
class WidgetGeneratorNewtonCurrentUser3 : public WidgetGeneratorNewtonCurrent
{
    Q_OBJECT
 public:
    static const int countObjects{3};  //!< Maximum object count

    WidgetGeneratorNewtonCurrentUser3(Project::QSimulationNewtonCurrent *_simulation, QWidget *_parent = nullptr);
    ~WidgetGeneratorNewtonCurrentUser3();

    QString generatorName() const;

    inline int countBySwitchState() const;

 protected slots:
    void countSwitchChanged(int _state);
    void objectValueChanged();

 protected:
    QCheckBox *m_countSwitch;         //!< Count switch "tristate" check-box
    GUI::GuiFloat *m_mass[countObjects];         //!< GUI widgets for mass
    GUI::GuiVector3D *m_position[countObjects];  //!< GUI widgets for position
    GUI::GuiVector3D *m_velocity[countObjects];  //!< GUI widgets for velocity
};

/*!
 * \brief Count objects by switch check-state
 * \returns Count objects
 */
inline int Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser3::countBySwitchState() const
{
    return m_countSwitch->isChecked() ? 3 : 2;
    // switch (m_countSwitch->checkState())
    //{
    // case Qt::Unchecked: break;
    // case Qt::PartiallyChecked: return 3;
    // case Qt::Checked: return 4;
    //}
    // return 2;
}

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEWTONCURRENT_H
