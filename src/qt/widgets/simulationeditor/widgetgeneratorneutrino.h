/*!
 * \file qt/widgets/simulationeditor/widgetgeneratorneutrino.h
 * \author Michal Steller
 * \brief Neutrino simulation initialization data generator widget classes declaration
 */

#ifndef UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEUTRINO_H
#define UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEUTRINO_H

#include "../../project/qsimulationneutrino.h"

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
 * \brief Neutrino simulation initialization data generator widget - base abstract class
 */
class WidgetGeneratorNeutrino : public QWidget
{
    Q_OBJECT
 protected:
    WidgetGeneratorNeutrino(Project::QSimulationNeutrino *_simulation, QWidget *_parent = nullptr);

 public:
    inline Project::QSimulationNeutrino *simulationNeutrino();
    inline const std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> &initObjects() const;

    /*!
     * \brief Pure virtual generator name getter
     * \returns Generator name
     */
    virtual QString generatorName() const = 0;

 protected:
    Project::QSimulationNeutrino *m_simulation;  //!< Processing Newton current simulation
    std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> m_initObjects;  //!< Initialization data
};

/*!
 * \brief Getter for processed simulation object
 * \returns Processed simulation object
 */
inline Project::QSimulationNeutrino *WidgetGeneratorNeutrino::simulationNeutrino()
{
    return m_simulation;
}

/*!
 * \brief Getter for generated initialization data
 * \returns Initialization data
 */
inline const std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> &
WidgetGeneratorNeutrino::initObjects() const
{
    return m_initObjects;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Single neutrino
 */
class WidgetGeneratorNeutrinoSingle : public WidgetGeneratorNeutrino
{
    Q_OBJECT
 public:
    WidgetGeneratorNeutrinoSingle(Project::QSimulationNeutrino *_simulation, QWidget *_parent = nullptr);
    ~WidgetGeneratorNeutrinoSingle();

    QString generatorName() const;

 public slots:
    void rebuild();

 protected:
    // GUI::GuiFloat *m_mass1;         //!< GUI widgets for object 1 mass
    // GUI::GuiFloat *m_mass2;         //!< GUI widgets for object 2 mass
    // GUI::GuiVector3D *m_position1;  //!< GUI widgets for object 1 position
    // GUI::GuiVector3D *m_position2;  //!< GUI widgets for object 2 position
    // GUI::GuiVector3D *m_velocity1;  //!< GUI widgets for object 1 velocity
    // GUI::GuiVector3D *m_velocity2;  //!< GUI widgets for object 2 velocity
    // QLabel *m_info;                 //!< Information label
};

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETGENERATORNEUTRINO_H
