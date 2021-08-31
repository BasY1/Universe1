/*!
 * \file qt/widgets/simulationeditor/widgetsimulationeditor.cpp
 * \author Michal Steller
 * \brief Simulation editor widget class implementation
 */

#include "widgetsimulationeditor.h"

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::WidgetSimulationEditor(Project::QSimulation *_simulation,
                                                                                     QWidget *_parent)
    : QWidget(_parent)

    , m_simulation(_simulation)

    , m_timeRangeMult(1.0)
    , m_timeRange({0.0, 0.0})
    , m_sceneRange({QVector3D(), QVector3D()})

    , m_view(new WidgetSimulationEditorView(m_simulation,
                                            &m_sceneRange,
                                            &m_pathData,
                                            &m_currentTimePositionsData,
                                            &m_currentTimePropertyData,
                                            &m_currentTimePropertyMaxLength))

    , m_mainSplitter(new QSplitter(Qt::Horizontal))
    , m_mainTab(new QTabWidget())

    , m_buildButton(new QPushButton(tr("Build")))
    , m_currentTimeSlider(new QSlider(Qt::Horizontal))
    , m_currentTimeBox(new QDoubleSpinBox())

    , m_precision(new QComboBox())
    , m_calculationStepCount(new QSpinBox())
    , m_calculationStepTime(new QDoubleSpinBox())
    , m_calculationStepAngle(new QDoubleSpinBox())

    , m_universeVelocity(nullptr)
    , m_gravityConstant(nullptr)
    , m_elementRadius(nullptr)

    , m_name(new QLineEdit())
    , m_description(new QTextBrowser())

    , m_generatorTabs(new QTabWidget())

    , m_objectsData(new QTableWidget())

    , m_pointSize(new GUI::GuiFloat(m_view->pointSize(), 1, 8, 0, Qt::Horizontal))
    , m_lineWidth(new GUI::GuiFloat(m_view->lineWidth(), 1, 8, 0, Qt::Horizontal))
    , m_showAxis(new QCheckBox())
    , m_showDots(new QCheckBox())
    , m_showProperty(new QTableWidget())

    , m_lightsTabs(new QTabWidget())
    , m_guiDirectionLight(new GUI::GuiDirectionLight(m_view->directionLight()))

    , m_observersEnabled(nullptr)
    , m_observerTime(nullptr)
    , m_observer1Position(nullptr)
    , m_observer2Position(nullptr)
{
    static const QString key = "SimulationEditor/MainWidget/";
    const QSettings settings;

    const Project::QSimulation::ElementProperties props = m_simulation->supportedElementProperties();
    const std::list<Project::QSimulation::ElementProperty> pList = Project::QSimulation::parseElementProperties(props);

    connect(m_simulation, &Project::QSimulation::dataChanged, this, &WidgetSimulationEditor::simulationChanged);

    connect(m_view,
            &WidgetSimulationEditorView::selectionChangeRequest,
            this,
            &WidgetSimulationEditor::selectionChangeRequest);

    connect(m_view,
            &WidgetSimulationEditorView::selectionInsertRequest,
            this,
            &WidgetSimulationEditor::selectionInsertRequest);

    connect(m_view,
            &WidgetSimulationEditorView::selectionClearRequest,
            this,
            &WidgetSimulationEditor::selectionClearRequest);

    m_mainTab->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Bottom status widget
    m_buildButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(m_buildButton, &QPushButton::clicked, this, &WidgetSimulationEditor::buildSimulation);

    m_currentTimeBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_currentTimeBox->setDecimals(3);
    m_currentTimeBox->setRange(-1000000.0, 1000000.0);

    m_currentTimeSlider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    connect(m_currentTimeBox,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &WidgetSimulationEditor::currentTimeBoxChanged);
    connect(m_currentTimeSlider, &QSlider::valueChanged, this, &WidgetSimulationEditor::currentTimeSliderChanged);

    QGridLayout *layBottom = new QGridLayout();
    layBottom->addWidget(m_currentTimeBox, 0, 0);
    layBottom->addWidget(m_currentTimeSlider, 0, 1);
    layBottom->addWidget(m_buildButton, 0, 2);
    QWidget *widBottom = new QWidget();
    widBottom->setLayout(layBottom);

    // Tab 0 - calculation settings
    QGridLayout *layTab0 = new QGridLayout();
    int row = 0;

    m_precision->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_precision->addItem(tr("Float"), static_cast<int>(Project::QSimulation::PrecisionFloat));
    m_precision->addItem(tr("Double"), static_cast<int>(Project::QSimulation::PrecisionDouble));
    m_precision->addItem(tr("Long double"), static_cast<int>(Project::QSimulation::PrecisionLongDouble));
    m_precision->setCurrentIndex(m_precision->findData(static_cast<int>(m_simulation->precision())));
    connect(m_precision,
            static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,
            &WidgetSimulationEditor::precisionChanged);

    m_calculationStepCount->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_calculationStepCount->setRange(2, 10000);
    m_calculationStepCount->setValue(m_simulation->calculationStepCount());
    connect(m_calculationStepCount,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            m_simulation,
            &Project::QSimulation::setCalculationStepCount);

    m_calculationStepTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_calculationStepTime->setDecimals(3);
    m_calculationStepTime->setRange(0.001, 10.0);
    m_calculationStepTime->setValue(m_simulation->getMaximumStepTime());
    connect(m_calculationStepTime,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            m_simulation,
            &Project::QSimulation::setMaximumStepTime);

    m_calculationStepAngle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_calculationStepAngle->setDecimals(2);
    m_calculationStepAngle->setRange(0.0, 90.0);
    m_calculationStepAngle->setValue(m_simulation->getMaximumCurveAngleDeg());
    connect(m_calculationStepAngle,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            m_simulation,
            &Project::QSimulation::setMaximumCurveAngleDeg);

    layTab0->addWidget(new QLabel(tr("Precision")), row, 0);
    layTab0->addWidget(m_precision, row++, 1);
    layTab0->addWidget(new QLabel(tr("Step count")), row, 0);
    layTab0->addWidget(m_calculationStepCount, row++, 1);
    layTab0->addWidget(new QLabel(tr("Maximum step duration")), row, 0);
    layTab0->addWidget(m_calculationStepTime, row++, 1);
    layTab0->addWidget(new QLabel(tr("Maximum step curving angle")), row, 0);
    layTab0->addWidget(m_calculationStepAngle, row++, 1);

    const std::set<Simulation::ConstantName> usedConstants = m_simulation->supportedPhysicsConstants();
    if (usedConstants.find(Simulation::ConstantName::Const_UniverseVelocity) != usedConstants.cend())
    {
        m_universeVelocity = new QDoubleSpinBox();
        m_universeVelocity->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_universeVelocity->setDecimals(3);
        m_universeVelocity->setRange(0.001, 1000.0);
        m_universeVelocity->setValue(m_simulation->getConstantUniverseVelocity());

        connect(m_universeVelocity,
                static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                m_simulation,
                &Project::QSimulation::setConstantUniverseVelocity);

        layTab0->addWidget(new QLabel(tr("Universe velocity")), row, 0);
        layTab0->addWidget(m_universeVelocity, row++, 1);
    }

    if (usedConstants.find(Simulation::ConstantName::Const_GravityConstant) != usedConstants.cend())
    {
        m_gravityConstant = new QDoubleSpinBox();
        m_gravityConstant->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_gravityConstant->setDecimals(3);
        m_gravityConstant->setRange(0.001, 1000.0);
        m_gravityConstant->setValue(m_simulation->getConstantGravityConstant());

        connect(m_gravityConstant,
                static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                m_simulation,
                &Project::QSimulation::setConstantGravityConstant);

        layTab0->addWidget(new QLabel(tr("Gravitational constant")), row, 0);
        layTab0->addWidget(m_gravityConstant, row++, 1);
    }

    if (usedConstants.find(Simulation::ConstantName::Const_ElementRadius) != usedConstants.cend())
    {
        m_elementRadius = new QDoubleSpinBox();
        m_elementRadius->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        m_elementRadius->setDecimals(3);
        m_elementRadius->setRange(0.001, 1000.0);
        m_elementRadius->setValue(m_simulation->getConstantElementRadius());

        connect(m_elementRadius,
                static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                m_simulation,
                &Project::QSimulation::setConstantElementRadius);

        layTab0->addWidget(new QLabel(tr("Element radius")), row, 0);
        layTab0->addWidget(m_elementRadius, row++, 1);
    }

    m_name->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    m_name->setText(m_simulation->name());
    connect(m_name, &QLineEdit::textChanged, m_simulation, &Project::QSimulation::setName);

    layTab0->addWidget(new QLabel(tr("Simulation name")), row, 0);
    layTab0->addWidget(m_name, row++, 1);

    m_description->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_description->setReadOnly(false);
    m_description->setText(m_simulation->description());
    connect(m_description, &QTextBrowser::textChanged, this, &WidgetSimulationEditor::descriptionChanged);

    layTab0->addWidget(new QLabel(tr("Description")), row++, 0, 1, 2);
    layTab0->addWidget(m_description, row++, 0, 1, 2);

    QWidget *widTab0 = new QWidget();
    widTab0->setLayout(layTab0);
    m_mainTab->addTab(widTab0, tr("Properties"));

    // Tab 1 - calculation settings

    m_newtonCurrent[0] = nullptr;
    m_newtonCurrent[1] = nullptr;

    m_generatorTabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    switch (m_simulation->simulationType())
    {
    case Universe1::Project::QSimulation::SimulationNewtonCurrent: {
        Project::QSimulationNewtonCurrent *simulationNewtonCurrent =
            qobject_cast<Project::QSimulationNewtonCurrent *>(m_simulation);
        if (simulationNewtonCurrent != nullptr)
        {
            m_newtonCurrent[0] = new WidgetGeneratorNewtonCurrentUser3(simulationNewtonCurrent);

            WidgetGeneratorNewtonCurrentBinary *tmpBin =
                new WidgetGeneratorNewtonCurrentBinary(simulationNewtonCurrent);
            m_newtonCurrent[1] = tmpBin;
            connect(m_simulation,
                    &Project::QSimulation::physicsChanged,
                    tmpBin,
                    &WidgetGeneratorNewtonCurrentBinary::rebuild);
            m_generatorTabs->addTab(m_newtonCurrent[0], tr("3 objects"));
            m_generatorTabs->addTab(m_newtonCurrent[1], tr("Binary"));
        }
    }
    break;

    case Universe1::Project::QSimulation::SimulationNewtonByWave: break;
    }

    m_generatorTabs->setCurrentIndex(settings.value(key + "generatorTab", m_generatorTabs->currentIndex()).toInt());

    m_mainTab->addTab(m_generatorTabs, tr("Generator"));

    // Tab 2 - calculated data info

    m_objectsData->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_objectsData->setSelectionMode(QAbstractItemView::ExtendedSelection);
    m_objectsData->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_objectsData->setColumnCount(pList.size() + 1);
    connect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    m_mainTab->addTab(m_objectsData, tr("Current data"));

    // Tab 3 - Visual settings

    m_showAxis->setChecked(m_view->showAxis());
    m_showDots->setChecked(m_view->showDots());

    m_showProperty->setColumnCount(2);
    m_showProperty->setHorizontalHeaderLabels({tr("Selected"), tr("All objects")});
    m_showProperty->setRowCount(pList.size() + 1);
    row = 0;
    QStringList vertlabs;
    QStringList horizLabs;
    horizLabs << tr("Position");
    vertlabs << tr("History path");

    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item->setCheckState(m_view->showPathSelected() ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, -1);
        m_showProperty->setItem(row, 0, item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item->setCheckState(m_view->showPathAll() ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, -1);
        m_showProperty->setItem(row, 1, item);

        row++;
    }

    for (const Project::QSimulation::ElementProperty p : pList)
    {
        const int iData = static_cast<int>(p);
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item->setCheckState(m_view->propertySelected().testFlag(p) ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, iData);
        m_showProperty->setItem(row, 0, item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
        item->setCheckState(m_view->propertyAll().testFlag(p) ? Qt::Checked : Qt::Unchecked);
        item->setData(Qt::UserRole, iData);
        m_showProperty->setItem(row, 1, item);

        vertlabs << Project::QSimulation::getElementPropertyName(p);
        horizLabs << vertlabs.back();
        row++;
    }
    m_showProperty->setVerticalHeaderLabels(vertlabs);
    m_showProperty->resizeColumnsToContents();
    m_showProperty->resizeRowsToContents();
    m_objectsData->setHorizontalHeaderLabels(horizLabs);

    connect(m_pointSize, &GUI::GuiFloat::changed, m_view, &WidgetSimulationEditorView::setPointSize);
    connect(m_lineWidth, &GUI::GuiFloat::changed, m_view, &WidgetSimulationEditorView::setLineWidth);
    connect(m_showAxis, &QCheckBox::toggled, m_view, &WidgetSimulationEditorView::setShowAxis);
    connect(m_showDots, &QCheckBox::toggled, m_view, &WidgetSimulationEditorView::setShowDots);
    connect(m_showProperty, &QTableWidget::itemChanged, this, &WidgetSimulationEditor::showPropertyChanged);

    QGridLayout *layTab3 = new QGridLayout();
    layTab3->addWidget(new QLabel(tr("Line width")), 0, 0);
    layTab3->addWidget(m_lineWidth->box(), 0, 1);
    layTab3->addWidget(m_lineWidth->slider(), 0, 2);
    layTab3->addWidget(new QLabel(tr("Show axis")), 0, 3);
    layTab3->addWidget(m_showAxis, 0, 4);

    layTab3->addWidget(new QLabel(tr("Point size")), 1, 0);
    layTab3->addWidget(m_pointSize->box(), 1, 1);
    layTab3->addWidget(m_pointSize->slider(), 1, 2);
    layTab3->addWidget(new QLabel(tr("Show dots")), 1, 3);
    layTab3->addWidget(m_showDots, 1, 4);

    layTab3->addWidget(m_showProperty, 2, 0, 1, 5);

    QWidget *widTab3 = new QWidget();
    widTab3->setLayout(layTab3);
    m_mainTab->addTab(widTab3, tr("Visual settings"));

    // Tab 4 - lights

    static const float lightsRange = 20.0F;

    m_lightsTabs->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_lightsTabs->addTab(m_guiDirectionLight->createWidget(), tr("Direction"));
    connect(
        m_guiDirectionLight, &GUI::GuiDirectionLight::changed, m_view, &WidgetSimulationEditorView::setDirectionLight);

    m_guiPointLight.resize(m_view->program()->pointLightsCount());
    for (int i = 0; i < m_view->program()->pointLightsCount(); ++i)
    {
        m_guiPointLight[i] = new GUI::GuiPointLight(
            i,
            m_view->pointLights().at(i),
            {QVector3D(-lightsRange, -lightsRange, -lightsRange), QVector3D(lightsRange, lightsRange, lightsRange)},
            2);
        m_lightsTabs->addTab(m_guiPointLight[i]->createWidget(), tr("Point %1").arg(i + 1));
        connect(m_guiPointLight[i], &GUI::GuiPointLight::changed, m_view, &WidgetSimulationEditorView::setPointLight);
    }

    m_guiSpotLight.resize(m_view->program()->spotLightsCount());
    for (int i = 0; i < m_view->program()->spotLightsCount(); ++i)
    {
        m_guiSpotLight[i] = new GUI::GuiSpotLight(
            i,
            m_view->spotLights().at(i),
            {QVector3D(-lightsRange, -lightsRange, -lightsRange), QVector3D(lightsRange, lightsRange, lightsRange)},
            2);
        m_lightsTabs->addTab(m_guiSpotLight[i]->createWidget(), tr("Spot %1").arg(i + 1));
        connect(m_guiSpotLight[i], &GUI::GuiSpotLight::changed, m_view, &WidgetSimulationEditorView::setSpotLight);
    }

    m_mainTab->addTab(m_lightsTabs, tr("Lights"));

    // Tab 5 - observers (Only if simulation uses history)
    if (m_simulation->usesHistory())
    {

        m_observersEnabled = new QCheckBox();
        m_observersEnabled->setTristate(true);
        m_observersEnabled->setChecked(false);

        m_observerTime = new QDoubleSpinBox();
        m_observerTime->setDecimals(5);
        m_observerTime->setRange(-1000000.0, 1000000.0);
        m_observerTime->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

        // static const float observerRange = 100.0F;
        static const float observerRange = lightsRange;

        m_observer1Position = new GUI::GuiVector3D(QVector3D(5.0F, 5.0F, 5.0F),
                                                   {QVector3D(-observerRange, -observerRange, -observerRange),
                                                    QVector3D(observerRange, observerRange, observerRange)},
                                                   3,
                                                   Qt::Horizontal);
        m_observer2Position = new GUI::GuiVector3D(QVector3D(-5.0F, -5.0F, 5.0F),
                                                   {QVector3D(-observerRange, -observerRange, -observerRange),
                                                    QVector3D(observerRange, observerRange, observerRange)},
                                                   3,
                                                   Qt::Horizontal);

        m_observerTime->setEnabled(false);
        m_observer1Position->setEnabled(false);
        m_observer2Position->setEnabled(false);

        connect(m_observersEnabled, &QCheckBox::stateChanged, this, &WidgetSimulationEditor::observerEnabledChanged);
        connect(m_observerTime,
                static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                this,
                &WidgetSimulationEditor::observerTimeChanged);
        connect(m_observer1Position, &GUI::GuiVector3D::changed, this, &WidgetSimulationEditor::observer1Changed);
        connect(m_observer2Position, &GUI::GuiVector3D::changed, this, &WidgetSimulationEditor::observer2Changed);

        QGridLayout *layTab5 = new QGridLayout();
        row = 0;

        layTab5->addWidget(new QLabel(tr("Enable")), row, 0, 1, 2);
        layTab5->addWidget(m_observersEnabled, row++, 2, 1, 2);

        layTab5->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

        m_observer1Position->layoutRow(tr("Observer 1"), layTab5, row);

        layTab5->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

        m_observer2Position->layoutRow(tr("Observer 2"), layTab5, row);

        layTab5->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 4);

        QWidget *widTab5 = new QWidget();
        widTab5->setLayout(layTab5);

        m_mainTab->addTab(widTab5, tr("Observer"));
    }

    // Finalize
    m_mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_mainSplitter->addWidget(m_view);
    m_mainSplitter->addWidget(m_mainTab);

    if (settings.contains(key + "splitter"))
        m_mainSplitter->restoreState(settings.value(key + "splitter").toByteArray());

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(m_mainSplitter, 0, 0);
    lay->addWidget(widBottom, 1, 0);
    setLayout(lay);

    simulationChanged();
};

/*!
 * \brief Destructor
 */
Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::~WidgetSimulationEditor()
{
    static const QString key = "SimulationEditor/MainWidget/";
    QSettings settings;
    settings.setValue(key + "splitter", m_mainSplitter->saveState());
    settings.setValue(key + "generatorTab", m_generatorTabs->currentIndex());

    disconnect(m_simulation, &Project::QSimulation::dataChanged, this, &WidgetSimulationEditor::simulationChanged);

    disconnect(m_view,
               &WidgetSimulationEditorView::selectionChangeRequest,
               this,
               &WidgetSimulationEditor::selectionChangeRequest);

    disconnect(m_view,
               &WidgetSimulationEditorView::selectionInsertRequest,
               this,
               &WidgetSimulationEditor::selectionInsertRequest);

    disconnect(m_view,
               &WidgetSimulationEditorView::selectionClearRequest,
               this,
               &WidgetSimulationEditor::selectionClearRequest);

    disconnect(m_buildButton, &QPushButton::clicked, this, &WidgetSimulationEditor::buildSimulation);
    disconnect(m_currentTimeSlider, &QSlider::valueChanged, this, &WidgetSimulationEditor::currentTimeSliderChanged);
    disconnect(m_currentTimeBox,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetSimulationEditor::currentTimeBoxChanged);

    disconnect(m_precision,
               static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
               this,
               &WidgetSimulationEditor::precisionChanged);
    disconnect(m_calculationStepCount,
               static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
               m_simulation,
               &Project::QSimulation::setCalculationStepCount);
    disconnect(m_calculationStepTime,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               m_simulation,
               &Project::QSimulation::setMaximumStepTime);
    disconnect(m_calculationStepAngle,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               m_simulation,
               &Project::QSimulation::setMaximumCurveAngleDeg);

    if (m_universeVelocity != nullptr)
        disconnect(m_universeVelocity,
                   static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                   m_simulation,
                   &Project::QSimulation::setConstantUniverseVelocity);
    if (m_gravityConstant != nullptr)
        disconnect(m_gravityConstant,
                   static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                   m_simulation,
                   &Project::QSimulation::setConstantGravityConstant);
    if (m_elementRadius != nullptr)
        disconnect(m_elementRadius,
                   static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                   m_simulation,
                   &Project::QSimulation::setConstantElementRadius);

    disconnect(m_name, &QLineEdit::textChanged, m_simulation, &Project::QSimulation::setName);
    disconnect(m_description, &QTextBrowser::textChanged, this, &WidgetSimulationEditor::descriptionChanged);

    disconnect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    disconnect(m_pointSize, &GUI::GuiFloat::changed, m_view, &WidgetSimulationEditorView::setPointSize);
    disconnect(m_lineWidth, &GUI::GuiFloat::changed, m_view, &WidgetSimulationEditorView::setLineWidth);
    disconnect(m_showAxis, &QCheckBox::toggled, m_view, &WidgetSimulationEditorView::setShowAxis);
    disconnect(m_showDots, &QCheckBox::toggled, m_view, &WidgetSimulationEditorView::setShowDots);
    disconnect(m_showProperty, &QTableWidget::itemChanged, this, &WidgetSimulationEditor::showPropertyChanged);

    disconnect(
        m_guiDirectionLight, &GUI::GuiDirectionLight::changed, m_view, &WidgetSimulationEditorView::setDirectionLight);

    for (int i = 0; i < m_view->program()->pointLightsCount(); ++i)
        disconnect(
            m_guiPointLight[i], &GUI::GuiPointLight::changed, m_view, &WidgetSimulationEditorView::setPointLight);

    for (int i = 0; i < m_view->program()->spotLightsCount(); ++i)
        disconnect(m_guiSpotLight[i], &GUI::GuiSpotLight::changed, m_view, &WidgetSimulationEditorView::setSpotLight);

    switch (m_simulation->simulationType())
    {
    case Universe1::Project::QSimulation::SimulationNewtonCurrent: {
        Project::QSimulationNewtonCurrent *simulationNewtonCurrent =
            qobject_cast<Project::QSimulationNewtonCurrent *>(m_simulation);
        if (simulationNewtonCurrent != nullptr)
        {
            WidgetGeneratorNewtonCurrentBinary *tmpBin =
                qobject_cast<WidgetGeneratorNewtonCurrentBinary *>(m_newtonCurrent[1]);
            if (tmpBin != nullptr)
                disconnect(m_simulation,
                           &Project::QSimulation::physicsChanged,
                           tmpBin,
                           &WidgetGeneratorNewtonCurrentBinary::rebuild);
        }
    }
    break;

    case Universe1::Project::QSimulation::SimulationNewtonByWave: break;
    }

    if (m_simulation->usesHistory())
    {
        disconnect(m_observersEnabled, &QCheckBox::stateChanged, this, &WidgetSimulationEditor::observerEnabledChanged);
        disconnect(m_observerTime,
                   static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                   this,
                   &WidgetSimulationEditor::observerTimeChanged);
        disconnect(m_observer1Position, &GUI::GuiVector3D::changed, this, &WidgetSimulationEditor::observer1Changed);
        disconnect(m_observer2Position, &GUI::GuiVector3D::changed, this, &WidgetSimulationEditor::observer2Changed);

        delete m_observer1Position;
        delete m_observer2Position;
    }

    delete m_guiDirectionLight;
    for (int i = 0; i < m_view->program()->pointLightsCount(); ++i)
        delete m_guiPointLight[i];
    for (int i = 0; i < m_view->program()->spotLightsCount(); ++i)
        delete m_guiSpotLight[i];
}

/*!
 * \brief Description edited handler
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::descriptionChanged()
{
    m_simulation->setDescription(m_description->toPlainText());
}

/*!
 * \brief Precision combo changed handler
 * \param _idx New combo-box index
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::precisionChanged(int _idx)
{
    Q_UNUSED(_idx)
    m_simulation->setPrecision(static_cast<Project::QSimulation::Precision>(m_precision->currentData().toInt()));
}

/*!
 * \brief Simulation finished calculation handler
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::simulationChanged()
{
    if (m_simulation->usesHistory())
    {
        disconnect(m_observersEnabled, &QCheckBox::stateChanged, this, &WidgetSimulationEditor::observerEnabledChanged);
        m_observersEnabled->setChecked(false);
        connect(m_observersEnabled, &QCheckBox::stateChanged, this, &WidgetSimulationEditor::observerEnabledChanged);

        m_observerTime->setEnabled(false);
        m_observer1Position->setEnabled(false);
        m_observer2Position->setEnabled(false);
        m_view->hideObserver1();
        m_view->hideObserver2();
    }

    m_selected.clear();
    m_view->setSelected(m_selected);

    m_pathData.clear();
    m_currentTimePositionsData.clear();
    m_currentTimePropertyData.clear();
    m_currentTimePropertyMaxLength.clear();

    m_timeRangeMult = 1.0;
    m_timeRange.first = 0.0;
    m_timeRange.second = 0.0;
    m_sceneRange.first = QVector3D();
    m_sceneRange.second = QVector3D();

    disconnect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);
    m_objectsData->clearSelection();
    m_objectsData->setRowCount(0);
    connect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    const size_t cntObjects = m_simulation->objectCountInit();

    m_pathData.resize(cntObjects);
    for (size_t i = 0U; i < cntObjects; ++i)
        if (!m_simulation->loadCalcPath(m_pathData[i], i))
            m_simulation->loadInitPath(m_pathData[i], i);

    bool isInit = false;
    for (const std::vector<std::pair<double, QVector3D>> &objPath : m_pathData)
    {
        for (const std::pair<double, QVector3D> &pathPos : objPath)
        {
            if (isInit)
            {
                if (m_sceneRange.first.x() > pathPos.second.x())
                    m_sceneRange.first.setX(pathPos.second.x());
                if (m_sceneRange.first.y() > pathPos.second.y())
                    m_sceneRange.first.setY(pathPos.second.y());
                if (m_sceneRange.first.z() > pathPos.second.z())
                    m_sceneRange.first.setZ(pathPos.second.z());
                if (m_sceneRange.second.x() < pathPos.second.x())
                    m_sceneRange.second.setX(pathPos.second.x());
                if (m_sceneRange.second.y() < pathPos.second.y())
                    m_sceneRange.second.setY(pathPos.second.y());
                if (m_sceneRange.second.z() < pathPos.second.z())
                    m_sceneRange.second.setZ(pathPos.second.z());
                if (m_timeRange.first > pathPos.first)
                    m_timeRange.first = pathPos.first;
                if (m_timeRange.second < pathPos.first)
                    m_timeRange.second = pathPos.first;
            }
            else
            {
                isInit = true;
                m_sceneRange.first = pathPos.second;
                m_sceneRange.second = pathPos.second;
                m_timeRange.first = pathPos.first;
                m_timeRange.second = pathPos.first;
            }
        }
    }

    m_currentTimeSlider->setEnabled(isInit);
    m_currentTimeBox->setEnabled(isInit);

    double rangeTime = m_timeRange.second - m_timeRange.first;

    if (!isInit || qFuzzyIsNull(rangeTime))
    {
        m_pathData.clear();
        m_timeRange.first = 0.0;
        m_timeRange.second = 0.0;
        m_sceneRange.first = QVector3D();
        m_sceneRange.second = QVector3D();
        m_view->rebuildSimulation();
        return;
    }


    while (static_cast<int>(rangeTime * m_timeRangeMult) > 100000)
        m_timeRangeMult *= 0.1;

    while (static_cast<int>(rangeTime * m_timeRangeMult) < 1000)
        m_timeRangeMult *= 10.0;

    disconnect(m_currentTimeBox,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetSimulationEditor::currentTimeBoxChanged);

    m_currentTimeBox->setValue(0.0);

    m_currentTimeBox->setRange(m_timeRange.first, m_timeRange.second);

    if (m_simulation->usesHistory())
        m_observerTime->setRange(m_timeRange.first, m_timeRange.second);

    connect(m_currentTimeBox,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &WidgetSimulationEditor::currentTimeBoxChanged);

    disconnect(m_currentTimeSlider, &QSlider::valueChanged, this, &WidgetSimulationEditor::currentTimeSliderChanged);

    m_currentTimeSlider->setRange(0, static_cast<int>(rangeTime * m_timeRangeMult));
    m_currentTimeSlider->setValue(static_cast<int>((-m_timeRange.first * m_timeRangeMult) / rangeTime));

    connect(m_currentTimeSlider, &QSlider::valueChanged, this, &WidgetSimulationEditor::currentTimeSliderChanged);

    rebuildCurrentTime();
}

/*!
 * \brief Current time slider change handler
 * \param _value New slider position
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::currentTimeSliderChanged(int _value)
{
    disconnect(m_currentTimeBox,
               static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
               this,
               &WidgetSimulationEditor::currentTimeBoxChanged);

    m_currentTimeBox->setValue(m_timeRange.first +
                               (m_timeRange.second - m_timeRange.first) *
                                   (static_cast<double>(_value) / static_cast<double>(m_currentTimeSlider->maximum())));

    connect(m_currentTimeBox,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,
            &WidgetSimulationEditor::currentTimeBoxChanged);

    rebuildCurrentTime();
}

/*!
 * \brief Current time spin-box change handler
 * \param _value New box value
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::currentTimeBoxChanged(double _value)
{
    disconnect(m_currentTimeSlider, &QSlider::valueChanged, this, &WidgetSimulationEditor::currentTimeSliderChanged);
    m_currentTimeSlider->setValue(static_cast<int>(m_timeRangeMult * _value));
    connect(m_currentTimeSlider, &QSlider::valueChanged, this, &WidgetSimulationEditor::currentTimeSliderChanged);
    rebuildCurrentTime();
}

/*!
 * \brief Tool function vector to string
 * \param _vector Vector
 * \return Vector as \c QString
 */
inline QString vecStr(const QVector3D &_vector)
{
    return QString("%1 x %2 x %3").arg(_vector.x()).arg(_vector.y()).arg(_vector.z());
}

/*!
 * \brief Rebuilds all objects data at current time-stamp, updates \a m_objectsData
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::rebuildCurrentTime()
{
    m_currentTimePositionsData.clear();
    m_currentTimePropertyData.clear();
    m_currentTimePropertyMaxLength.clear();

    const size_t cntObjects = m_simulation->objectCountInit();
    const double curTime = m_currentTimeBox->value();
    const bool isFromInit = (m_simulation->objectCountCalc() == 0U);

    m_currentTimePositionsData.reserve(cntObjects);

    disconnect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    m_objectsData->clearSelection();
    m_objectsData->setRowCount(cntObjects);

    if (isFromInit)
    {
        for (size_t i = 0U; i < cntObjects; ++i)
            m_currentTimePositionsData.push_back(m_simulation->loadInitPosition(i, curTime).second);
    }
    else
    {
        for (size_t i = 0U; i < cntObjects; ++i)
            m_currentTimePositionsData.push_back(m_simulation->loadCalcPosition(i, curTime).second);
    }

    const std::list<Project::QSimulation::ElementProperty> flagsAll =
        Project::QSimulation::parseElementProperties(m_simulation->supportedElementProperties());

    for (size_t i = 0U; i < cntObjects; ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        item->setText(vecStr(m_currentTimePositionsData[i]));
        m_objectsData->setItem(i, 0, item);
    }

    int col = 0;
    for (const Project::QSimulation::ElementProperty propName : flagsAll)
    {
        ++col;

        std::vector<std::pair<double, QVector3D>> &propData =
            m_currentTimePropertyData.insert({propName, std::vector<std::pair<double, QVector3D>>()}).first->second;

        propData.reserve(cntObjects);
        if (isFromInit)
        {
            for (size_t i = 0U; i < cntObjects; ++i)
                propData.push_back(m_simulation->loadInitProperty(propName, i, curTime));
        }
        else
        {
            for (size_t i = 0U; i < cntObjects; ++i)
                propData.push_back(m_simulation->loadCalcProperty(propName, i, curTime));
        }

        float maxLength = 0.0F;

        for (const std::pair<double, QVector3D> &objData : propData)
        {
            const float l = objData.second.length();
            if (maxLength < l)
                maxLength = l;
        }

        if (propName == Project::QSimulation::PropertyMass)
        {
            for (size_t i = 0U; i < cntObjects; ++i)
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                item->setText(QString::number(propData[i].second.x()));
                m_objectsData->setItem(i, col, item);
            }
        }
        else
        {
            for (size_t i = 0U; i < cntObjects; ++i)
            {
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
                item->setText(vecStr(propData[i].second));
                m_objectsData->setItem(i, col, item);
            }
        }

        m_currentTimePropertyMaxLength.insert({propName, maxLength});
    }

    m_objectsData->resizeColumnsToContents();
    m_objectsData->resizeRowsToContents();

    connect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    m_view->setCurrentTime(curTime);
}

/*!
 * \brief Table with calculated object data (\a m_objectsData) changed selection
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::objectsDataSelection()
{
    m_selected.clear();
    const QList<QTableWidgetItem *> sel = m_objectsData->selectedItems();
    for (QTableWidgetItem *s : sel)
        m_selected.insert(static_cast<size_t>(s->row()));
    m_view->setSelected(m_selected);
}

/*!
 * \brief Object double-clicked on Open GL widget
 * \param _objectIndex Double-clicked object index
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::selectionChangeRequest(uint _objectIndex)
{
    if (m_selected.size() == 1U && ((*m_selected.begin()) == _objectIndex))
        return;

    m_selected.clear();
    m_selected.insert(_objectIndex);

    disconnect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    m_objectsData->clearSelection();
    m_objectsData->setCurrentItem(m_objectsData->item(_objectIndex, 0));
    for (int c = 0; c < m_objectsData->columnCount(); ++c)
        m_objectsData->item(_objectIndex, c)->setSelected(true);

    connect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    m_view->setSelected(m_selected);
}

/*!
 * \brief Object double-clicked on Open GL widget (with CTRL down)
 * \param _objectIndex Double-clicked object index
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::selectionInsertRequest(uint _objectIndex)
{
    const size_t oIdx = _objectIndex;
    const bool isRemove = (m_selected.find(oIdx) == m_selected.cend());

    if (isRemove)
        m_selected.erase(oIdx);
    else
        m_selected.insert(_objectIndex);

    disconnect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);

    m_objectsData->clearSelection();

    if (!m_selected.empty())
    {
        if (isRemove)
            m_objectsData->setCurrentItem(m_objectsData->item(_objectIndex, 0));
        else
            m_objectsData->setCurrentItem(m_objectsData->item(*m_selected.cbegin(), 0));

        for (const size_t r : m_selected)
            for (int c = 0; c < m_objectsData->columnCount(); ++c)
                m_objectsData->item(r, c)->setSelected(true);
    }

    connect(m_objectsData, &QTableWidget::itemSelectionChanged, this, &WidgetSimulationEditor::objectsDataSelection);
    m_view->setSelected(m_selected);
}

/*!
 * \brief Selection clear request from right double-clicked on Open GL widget
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::selectionClearRequest()
{
    if (!m_selected.empty())
        m_objectsData->clearSelection();
}

/*!
 * \brief Show property state changed
 * \param _item Item with changed state
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::showPropertyChanged(QTableWidgetItem *_item)
{
    if (_item == nullptr)
        return;

    const bool isClickOnSelectedCol = (_item->column() == 0);
    if (_item->row() == 0)
    {
        if (isClickOnSelectedCol)
            m_view->setShowPathSelected(_item->checkState() == Qt::Checked);
        else
            m_view->setShowPathAll(_item->checkState() == Qt::Checked);
    }
    else
    {
        const Project::QSimulation::ElementProperty prop =
            static_cast<Project::QSimulation::ElementProperty>(_item->data(Qt::UserRole).toInt());

        Project::QSimulation::ElementProperties props =
            isClickOnSelectedCol ? m_view->propertySelected() : m_view->propertyAll();

        props.setFlag(prop, _item->checkState() == Qt::Checked);

        if (isClickOnSelectedCol)
            m_view->setPropertySelected(props);
        else
            m_view->setPropertyAll(props);
    }
}

/*!
 * \brief Observer enable state changed
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::observerEnabledChanged()
{
    m_observerTime->setEnabled(m_observersEnabled->checkState() != Qt::Unchecked);
    m_observer1Position->setEnabled(m_observersEnabled->checkState() != Qt::Unchecked);
    m_observer2Position->setEnabled(m_observersEnabled->checkState() == Qt::Checked);

    if (m_observersEnabled->checkState() == Qt::Checked)
    {
        observer1Changed();
        observer2Changed();
    }
    else if (m_observersEnabled->checkState() == Qt::PartiallyChecked)
    {
        observer1Changed();
        m_view->hideObserver2();
    }
    else
    {
        m_view->hideObserver1();
        m_view->hideObserver2();
    }
}

/*!
 * \brief Setup observer 1
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::observer1Changed()
{
    std::vector<std::pair<double, QVector3D>> eventSource;
    if (m_simulation->loadEventSource(eventSource, m_observerTime->value(), m_observer1Position->value()))
        m_view->setObserver1(m_observer1Position->value(), eventSource);
    else
        m_view->hideObserver1();
}

/*!
 * \brief Setup observer 2
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::observer2Changed()
{
    std::vector<std::pair<double, QVector3D>> eventSource;
    if (m_simulation->loadEventSource(eventSource, m_observerTime->value(), m_observer2Position->value()))
        m_view->setObserver2(m_observer2Position->value(), eventSource);
    else
        m_view->hideObserver2();
}

/*!
 * \brief Observer time changed
 * \param _value New time-stamp value
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::observerTimeChanged(double _value)
{
    Q_UNUSED(_value)
    if (m_observersEnabled->checkState() == Qt::Checked)
    {
        observer1Changed();
        observer2Changed();
    }
    else if (m_observersEnabled->checkState() == Qt::PartiallyChecked)
    {
        observer1Changed();
    }
}

/*!
 * \brief Rebuild simulation
 */
void Universe1::Widgets::SimulationEditor::WidgetSimulationEditor::buildSimulation()
{
    switch (m_simulation->simulationType())
    {
    case Universe1::Project::QSimulation::SimulationNewtonCurrent:
        m_newtonCurrent[m_generatorTabs->currentIndex()]->simulationNewtonCurrent()->rebuildSimulation(
            m_newtonCurrent[m_generatorTabs->currentIndex()]->initObjects());
        break;
    case Universe1::Project::QSimulation::SimulationNewtonByWave: break;
    }
}
