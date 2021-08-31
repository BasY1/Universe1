/*!
 * \file qt/widgets/simulationeditor/widgetsimulationeditor.h
 * \author Michal Steller
 * \brief Simulation editor widget class declaration
 */

#ifndef UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITOR_H
#define UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITOR_H

#include "widgetgeneratornewtoncurrent.h"
#include "widgetsimulationeditorview.h"

#include "../gui/guidirectionlight.h"
#include "../gui/guipointlight.h"
#include "../gui/guispotlight.h"

#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QTabWidget>
#include <QTableWidget>
#include <QTextBrowser>

namespace Universe1 {
namespace Widgets {
namespace SimulationEditor {

/*!
 * \brief Simulation QT Open GL widget
 */
class WidgetSimulationEditor : public QWidget
{
    Q_OBJECT
 public:
    WidgetSimulationEditor(Project::QSimulation *_simulation, QWidget *_parent = nullptr);
    ~WidgetSimulationEditor();

 protected slots:
    void descriptionChanged();
    void precisionChanged(int _idx);

    void simulationChanged();

    void currentTimeSliderChanged(int _value);
    void currentTimeBoxChanged(double _value);

 protected:
    void rebuildCurrentTime();

 protected slots:
    void objectsDataSelection();

    void selectionChangeRequest(uint _objectIndex);
    void selectionInsertRequest(uint _objectIndex);
    void selectionClearRequest();

    void showPropertyChanged(QTableWidgetItem *_item);

    void observerEnabledChanged();
    void observer1Changed();
    void observer2Changed();
    void observerTimeChanged(double _value);

    void buildSimulation();

 protected:
    Project::QSimulation *m_simulation;  //!< Processing simulation

    std::set<size_t> m_selected;  //!< Selected objects

    double m_timeRangeMult;                 //!< Time range slider mult
    std::pair<double, double> m_timeRange;  //!< Simulation scene time range of time-stamps

    std::pair<QVector3D, QVector3D> m_sceneRange;  //!< Simulation scene range from all objects paths

    std::vector<std::vector<std::pair<double, QVector3D>>> m_pathData;  //!< Object's path data

    std::vector<QVector3D> m_currentTimePositionsData;  //!< Object's positions at current time

    std::map<Project::QSimulation::ElementProperty, std::vector<std::pair<double, QVector3D>>>
        m_currentTimePropertyData;  //!< Object's Properties at current time

    std::map<Project::QSimulation::ElementProperty, float>
        m_currentTimePropertyMaxLength;  //!< Maximum length of current vector property

    WidgetSimulationEditorView *m_view;  //!< Open GL view widget

    QSplitter *m_mainSplitter;  //!< Main horizontal splitter
    QTabWidget *m_mainTab;      //!< Main tabs widget

    // Bottom status
    QPushButton *m_buildButton;        //!< Build simulation button
    QSlider *m_currentTimeSlider;      //!< Current view time slider
    QDoubleSpinBox *m_currentTimeBox;  //!< Current view time spin-box

    // Main tab 0
    QComboBox *m_precision;                  //!< Precision combo-box
    QSpinBox *m_calculationStepCount;        //!< Calculation step count GUI widgets
    QDoubleSpinBox *m_calculationStepTime;   //!< Calculation step time duration GUI widgets
    QDoubleSpinBox *m_calculationStepAngle;  //!< Calculation step maximum curving angle [degrees] GUI widgets
    QDoubleSpinBox *m_universeVelocity;      //!< GUI widgets for speed of the universe constant
    QDoubleSpinBox *m_gravityConstant;       //!< GUI widgets for gravitational constant
    QDoubleSpinBox *m_elementRadius;         //!< GUI widgets for element radius
    QLineEdit *m_name;                       //!< Simulation name widget
    QTextBrowser *m_description;             //!< Simulation description widget

    // Main tab 1
    QTabWidget *m_generatorTabs;  //!< Tab widget for simulation initialization data generators

    WidgetGeneratorNewtonCurrent *m_newtonCurrent[1];  //!< Newton current generators

    // Main tab 2
    QTableWidget *m_objectsData;  //!< Table of object's properties at current time

    // Main tab 3
    GUI::GuiFloat *m_pointSize;    //!< GUI for point size
    GUI::GuiFloat *m_lineWidth;    //!< GUI for line width
    QCheckBox *m_showAxis;         //!< Switch for show axis flag
    QCheckBox *m_showDots;         //!< Switch for show dots flag (in X-Y plane)
    QTableWidget *m_showProperty;  //!< Show object properties table with switches

    // Main tab 4
    QTabWidget *m_lightsTabs;                           //!< Tab widget for scene lights
    GUI::GuiDirectionLight *m_guiDirectionLight;        //!< Direction light GUI widgets
    std::vector<GUI::GuiPointLight *> m_guiPointLight;  //!< Point light GUI widgets
    std::vector<GUI::GuiSpotLight *> m_guiSpotLight;    //!< Spot light GUI widgets

    // Main tab 5 (Only if simulation uses history)
    QCheckBox *m_observersEnabled;          //!< Observer switch (tristate)
    QDoubleSpinBox *m_observerTime;         //!< Observers time
    GUI::GuiVector3D *m_observer1Position;  //!< Observer 1 position GUI widgets
    GUI::GuiVector3D *m_observer2Position;  //!< Observer 2 position GUI widgets
};

}  // namespace SimulationEditor
}  // namespace Widgets
}  // namespace Universe1

#endif  // UNIVERSE1_WIDGETS_SIMULATIONEDITOR_WIDGETSIMULATIONEDITOR_H
