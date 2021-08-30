/*!
 * \file qt/widgets/simulationeditor/dialogsimulationeditor.cpp
 * \author Michal Steller
 * \brief Simulation editor - Main dialog class implementation
 */

#include "dialogsimulationeditor.h"

#include <QDialogButtonBox>
#include <QGridLayout>

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::DialogSimulationEditor::DialogSimulationEditor(Project::QSimulation *_simulation,
                                                                                     QWidget *_parent)
    : QDialog(_parent)
    , m_rootWidget(new WidgetSimulationEditor(_simulation))
{
    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(m_rootWidget, 0, 0);
    lay->addWidget(buttons, 1, 0);
    setLayout(lay);

    const QSettings settings;
    move(settings.value("SimulationEditor/Dialog/pos", pos()).toPoint());
    resize(settings.value("SimulationEditor/Dialog/size", size()).toSize());
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::SimulationEditor::DialogSimulationEditor::~DialogSimulationEditor()
{
    QSettings settings;
    settings.setValue("SimulationEditor/Dialog/pos", pos());
    settings.setValue("SimulationEditor/Dialog/size", size());
}
