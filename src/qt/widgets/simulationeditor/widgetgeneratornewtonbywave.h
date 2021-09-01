/*!
 * \file qt/widgets/simulationeditor/widgetgeneratornewtonbywave.h
 * \author Michal Steller
 * \brief Newton wave based simulation initialization data generator widget classes declaration
 */

#ifndef UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEWTONBYWAVE_H
#define UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEWTONBYWAVE_H

#include "../../project/qsimulationnewtonbywave.h"

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
 * \brief Newton wave based simulation initialization data generator widget - base abstract class
 */
class WidgetGeneratorNewtonByWave : public QWidget
{
    Q_OBJECT
 protected:
    WidgetGeneratorNewtonByWave(Project::QSimulationNewtonByWave *_simulation, QWidget *_parent = nullptr);

 public:
    inline Project::QSimulationNewtonByWave *simulationNewtonByWave();
    inline const std::vector<Simulation::GravityNewton::NewtonObjectByWave<long double>> &initObjects() const;

    /*!
     * \brief Pure virtual generator name getter
     * \returns Generator name
     */
    virtual QString generatorName() const = 0;

 protected:
    Project::QSimulationNewtonByWave *m_simulation;  //!< Processing Newton current simulation

    std::vector<Simulation::GravityNewton::NewtonObjectByWave<long double>> m_initObjects;  //!< Initialization data
};

/*!
 * \brief Getter for processed simulation object
 * \returns Processed simulation object
 */
inline Project::QSimulationNewtonByWave *WidgetGeneratorNewtonByWave::simulationNewtonByWave()
{
    return m_simulation;
}

/*!
 * \brief Getter for generated initialization data
 * \returns Initialization data
 */
inline const std::vector<Simulation::GravityNewton::NewtonObjectByWave<long double>> &
WidgetGeneratorNewtonByWave::initObjects() const
{
    return m_initObjects;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Newton wave based simulation initialization data generator widget - 2 or 3 objects
 */
class WidgetGeneratorNewtonByWaveUser2 : public WidgetGeneratorNewtonByWave
{
    Q_OBJECT
 public:
    WidgetGeneratorNewtonByWaveUser2(Project::QSimulationNewtonByWave *_simulation, QWidget *_parent = nullptr);
    ~WidgetGeneratorNewtonByWaveUser2();

    QString generatorName() const;

 public slots:
    void rebuild();

 protected:
    GUI::GuiFloat *m_mass1;         //!< GUI widgets for object 1 mass
    GUI::GuiFloat *m_mass2;         //!< GUI widgets for object 2 mass
    GUI::GuiVector3D *m_position1;  //!< GUI widgets for object 1 position
    GUI::GuiVector3D *m_position2;  //!< GUI widgets for object 2 position
    GUI::GuiVector3D *m_velocity1;  //!< GUI widgets for object 1 velocity
    GUI::GuiVector3D *m_velocity2;  //!< GUI widgets for object 2 velocity
    QLabel *m_info;                 //!< Information label
};

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEWTONBYWAVE_H
