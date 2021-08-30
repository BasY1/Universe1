/*!
 * \file qt/widgets/simulationeditor/widgetgeneratornewtoncurrent.cpp
 * \author Michal Steller
 * \brief Newton current simulation initialization data generator widget classes implementation
 */

#include "widgetgeneratornewtoncurrent.h"

#include <QSettings>

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrent::WidgetGeneratorNewtonCurrent(
    Project::QSimulationNewtonCurrent *_simulation, QWidget *_parent)
    : QWidget(_parent)
    , m_simulation(_simulation)
{
}

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser4::WidgetGeneratorNewtonCurrentUser4(
    Project::QSimulationNewtonCurrent *_simulation, QWidget *_parent)
    : WidgetGeneratorNewtonCurrent(_simulation, _parent)
    , m_countSwitch(new QCheckBox())
{
    static const QString key = "SimulationEditor/GeneratorNewtonCurrentUser4/";
    const QSettings settings;

    m_countSwitch->setTristate(true);
    m_countSwitch->setCheckState(static_cast<Qt::CheckState>(settings.value(key + "count", Qt::Checked).toInt()));
    connect(m_countSwitch, &QCheckBox::stateChanged, this, &WidgetGeneratorNewtonCurrentUser4::countSwitchChanged);

    const int usedCnt = countBySwitchState();

    QGridLayout *lay = new QGridLayout();

    int row = 0;
    lay->addWidget(new QLabel(tr("Used objects")), row, 0, 1, 2);
    lay->addWidget(m_countSwitch, row++, 2, 1, 2);

    static const QVector3D defPos[4] = {
        QVector3D(-2.0F, -2.0F, 1.0F),
        QVector3D(2.0F, 2.0F, 1.0F),
        QVector3D(2.0F, -2.0F, 1.0F),
        QVector3D(-2.0F, 2.0F, 1.0F),
    };
    static const QVector3D defVel[4] = {
        QVector3D(1.0F, -1.0F, 0.0F).normalized(),
        QVector3D(-1.0F, 1.0F, 0.0F).normalized(),
        QVector3D(-1.0F, 1.0F, 0.0F).normalized(),
        QVector3D(1.0F, -1.0F, 0.0F).normalized(),
    };
    static const std::pair<QVector3D, QVector3D> refRangePos = {QVector3D(-10.0F, -10.0F, -10.0F),
                                                                QVector3D(10.0F, 10.0F, 10.0F)};
    static const std::pair<QVector3D, QVector3D> refRangeVel = {QVector3D(-2.0F, -2.0F, -2.0F),
                                                                QVector3D(2.0F, 2.0F, 2.0F)};

    for (int i = 0; i < 4; ++i)
    {
        const float m = settings.value(QString("%1mass_%2_").arg(key).arg(i), 1.0F).toFloat();
        const QVector3D p = settings.value(QString("%1position_%2_").arg(key).arg(i), defPos[i]).value<QVector3D>();
        const QVector3D v = settings.value(QString("%1velocity_%2_").arg(key).arg(i), defVel[i]).value<QVector3D>();

        m_mass[i] = new GUI::GuiFloat(m, 0.01F, 100.0F, 2, Qt::Horizontal);
        m_position[i] = new GUI::GuiVector3D(p, refRangePos, 1, Qt::Horizontal);
        m_velocity[i] = new GUI::GuiVector3D(v, refRangeVel, 2, Qt::Horizontal);

        if (i >= usedCnt)
        {
            m_mass[i]->setEnabled(false);
            m_position[i]->setEnabled(false);
            m_velocity[i]->setEnabled(false);
        }

        connect(m_mass[i], &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentUser4::objectValueChanged);
        connect(
            m_position[i], &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonCurrentUser4::objectValueChanged);
        connect(
            m_velocity[i], &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonCurrentUser4::objectValueChanged);

        lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

        m_mass[i]->layoutRow(tr("Mass %1").arg(i + 1), lay, row);
        m_position[i]->layoutRow(tr("Position"), lay, row);
        m_velocity[i]->layoutRow(tr("Velocity"), lay, row);
    }
    lay->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Expanding), row, 0, 1, 4);

    setLayout(lay);

    objectValueChanged();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser4::~WidgetGeneratorNewtonCurrentUser4()
{
    static const QString key = "SimulationEditor/GeneratorNewtonCurrentUser4/";
    QSettings settings;
    settings.setValue(key + "count", static_cast<int>(m_countSwitch->checkState()));
    for (int i = 0; i < 4; ++i)
    {
        settings.setValue(QString("%1mass_%2_").arg(key).arg(i), m_mass[i]->value());
        settings.setValue(QString("%1position_%2_").arg(key).arg(i), m_position[i]->value());
        settings.setValue(QString("%1velocity_%2_").arg(key).arg(i), m_velocity[i]->value());
    }

    for (int i = 0; i < 4; ++i)
    {
        delete m_mass[i];
        delete m_position[i];
        delete m_velocity[i];
    }
}

/*!
 * \brief Generator name getter
 * \returns "User objects [N]" string
 */
QString Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser4::generatorName() const
{
    return tr("User objects [%1]").arg(m_initObjects.size());
}

/*!
 * \brief Count switch changed
 * \param _state New check-state
 */
void Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser4::countSwitchChanged(int _state)
{
    Q_UNUSED(_state)
    const int usedCnt = countBySwitchState();
    for (int i = 0; i < 4; ++i)
    {
        m_mass[i]->setEnabled(i < usedCnt);
        m_position[i]->setEnabled(i < usedCnt);
        m_velocity[i]->setEnabled(i < usedCnt);
    }
    objectValueChanged();
}

/*!
 * \brief Object GUI changed value
 */
void Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser4::objectValueChanged()
{
    const int usedCnt = countBySwitchState();
    m_initObjects.resize(usedCnt);
    for (int i = 0; i < usedCnt; ++i)
    {
        m_initObjects[i].mass = m_mass[i]->value();
        m_initObjects[i].position = Universe1::Math::Vec3<long double>::fromQVector3D(m_position[i]->value());
        m_initObjects[i].velocity = Universe1::Math::Vec3<long double>::fromQVector3D(m_velocity[i]->value());

        m_mass[i]->setEnabled(i < usedCnt);
        m_position[i]->setEnabled(i < usedCnt);
        m_velocity[i]->setEnabled(i < usedCnt);
    }
}
