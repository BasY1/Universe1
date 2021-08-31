/*!
 * \file qt/widgets/simulationeditor/widgetgeneratornewtoncurrent.cpp
 * \author Michal Steller
 * \brief Newton current simulation initialization data generator widget classes implementation
 */

#include "widgetgeneratornewtoncurrent.h"

#include "../../../math/texttools.h"

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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser3::WidgetGeneratorNewtonCurrentUser3(
    Project::QSimulationNewtonCurrent *_simulation, QWidget *_parent)
    : WidgetGeneratorNewtonCurrent(_simulation, _parent)
    , m_countSwitch(new QCheckBox())
{
    static const QString key = "SimulationEditor/GeneratorNewtonCurrentUser3/";
    const QSettings settings;

    m_countSwitch->setTristate(true);
    m_countSwitch->setCheckState(static_cast<Qt::CheckState>(settings.value(key + "count", Qt::Checked).toInt()));
    connect(m_countSwitch, &QCheckBox::stateChanged, this, &WidgetGeneratorNewtonCurrentUser3::countSwitchChanged);

    const int usedCnt = countBySwitchState();

    int row = 0;
    QGridLayout *lay = new QGridLayout();
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

    for (int i = 0; i < countObjects; ++i)
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

        connect(m_mass[i], &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentUser3::objectValueChanged);
        connect(
            m_position[i], &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonCurrentUser3::objectValueChanged);
        connect(
            m_velocity[i], &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonCurrentUser3::objectValueChanged);

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
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser3::~WidgetGeneratorNewtonCurrentUser3()
{
    static const QString key = "SimulationEditor/GeneratorNewtonCurrentUser3/";
    QSettings settings;
    settings.setValue(key + "count", static_cast<int>(m_countSwitch->checkState()));
    for (int i = 0; i < countObjects; ++i)
    {
        settings.setValue(QString("%1mass_%2_").arg(key).arg(i), m_mass[i]->value());
        settings.setValue(QString("%1position_%2_").arg(key).arg(i), m_position[i]->value());
        settings.setValue(QString("%1velocity_%2_").arg(key).arg(i), m_velocity[i]->value());
    }

    for (int i = 0; i < countObjects; ++i)
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
QString Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser3::generatorName() const
{
    return tr("User objects [%1]").arg(m_initObjects.size());
}

/*!
 * \brief Count switch changed
 * \param _state New check-state
 */
void Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser3::countSwitchChanged(int _state)
{
    Q_UNUSED(_state)
    const int usedCnt = countBySwitchState();
    for (int i = 0; i < countObjects; ++i)
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
void Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentUser3::objectValueChanged()
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentBinary::WidgetGeneratorNewtonCurrentBinary(
    Project::QSimulationNewtonCurrent *_simulation, QWidget *_parent)
    : WidgetGeneratorNewtonCurrent(_simulation, _parent)
    , m_radius1(new GUI::GuiFloat(1.0F, 0.01F, 100.0F, 2, Qt::Horizontal))
    , m_mass1(new GUI::GuiFloat(1.0F, 0.01F, 100.0F, 2, Qt::Horizontal))
    , m_mass2(new GUI::GuiFloat(1.0F, 0.01F, 100.0F, 2, Qt::Horizontal))
    , m_systemVelocity(new GUI::GuiVector3D(QVector3D(), -5, 5, -5, 5, -5, 5, 3, Qt::Horizontal))
    , m_info(new QLabel())
{
    m_initObjects.resize(2);

    static const QString key = "SimulationEditor/WidgetGeneratorNewtonCurrentBinary/";
    const QSettings settings;
    m_radius1->setValue(settings.value(key + "radius1", m_radius1->value()).toFloat());
    m_mass1->setValue(settings.value(key + "mass1", m_mass1->value()).toFloat());
    m_mass2->setValue(settings.value(key + "mass2", m_mass2->value()).toFloat());
    m_systemVelocity->setValue(settings.value(key + "systemVelocity", m_systemVelocity->value()).value<QVector3D>());

    m_info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_info->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    int row = 0;
    QGridLayout *lay = new QGridLayout();
    m_radius1->layoutRow(tr("Radius 1"), lay, row);
    m_mass1->layoutRow(tr("Mass 1"), lay, row);
    m_mass2->layoutRow(tr("Mass 2"), lay, row);

    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);

    m_systemVelocity->layoutRow(tr("System velocity"), lay, row);

    lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);
    lay->addWidget(m_info, row++, 0, 1, 4);
    setLayout(lay);

    connect(m_radius1, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);
    connect(m_mass1, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);
    connect(m_mass2, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);
    connect(m_systemVelocity, &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);

    rebuild();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentBinary::~WidgetGeneratorNewtonCurrentBinary()
{
    disconnect(m_radius1, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);
    disconnect(m_mass1, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);
    disconnect(m_mass2, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);
    disconnect(m_systemVelocity, &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonCurrentBinary::rebuild);

    static const QString key = "SimulationEditor/WidgetGeneratorNewtonCurrentBinary/";
    QSettings settings;
    settings.setValue(key + "radius1", m_radius1->value());
    settings.setValue(key + "mass1", m_mass1->value());
    settings.setValue(key + "mass2", m_mass2->value());
    settings.setValue(key + "systemVelocity", m_systemVelocity->value());
}

/*!
 * \brief Generator name getter
 * \returns "Binary" string
 */
QString Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentBinary::generatorName() const
{
    return tr("Binary");
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value Attribute value
 * \return HTML table row
 */
inline QString htmlRow1(const QString &_name, const long double _value)
{
    return "<tr><td><b>" + _name + "</b></td><td colspan=\"2\" align=\"center\">" +
        Universe1::TextTools::toQString(_value) + "</td></tr>";
}

/*!
 * \brief Tool function prepare HTML table row
 * \param _name Attribute name
 * \param _value1 Attribute 1 value
 * \param _value2 Attribute 2 value
 * \return HTML table row
 */
inline QString htmlRow2(const QString &_name, const long double _value1, const long double _value2)
{
    return "<tr><td><b>" + _name + "</b></td><td>" + Universe1::TextTools::toQString(_value1) + "</td><td>" +
        Universe1::TextTools::toQString(_value2) + "</td></tr>";
}

/*!
 * \brief Rebuild
 */
void Universe1::Widgets::SimulationEditor::WidgetGeneratorNewtonCurrentBinary::rebuild()
{
    const Math::Vec3<long double> addVelocity = Math::Vec3<long double>::fromQVector3D(m_systemVelocity->value());

    const long double G = m_simulation->getConstantGravityConstant();
    const long double R1 = m_radius1->value();
    const long double M1 = m_mass1->value();
    const long double M2 = m_mass2->value();
    const long double M1_2 = M1 / M2;
    const long double R2 = R1 * M1_2;  // R1*M1 == R2*M2
    const long double D = R1 + R2;
    const long double F = G * M1 * M2 / (D * D);
    const long double A1 = F / M1;  // == V1^2 / R1
    const long double A2 = F / M2;  // == V2^2 / R1
    const long double V1 = std::sqrt(A1 * R1);
    const long double V2 = std::sqrt(A2 * R2);
    const long double L1 = 2.0l * M_PIl * R1;
    const long double L2 = 2.0l * M_PIl * R2;
    const long double T0 = 2.0l * M_PIl * R1 / V1;

    const long double CNT = m_simulation->calculationStepCount();
    const long double DT = m_simulation->getMaximumStepTime();
    const long double TS = CNT * DT;
    const long double TSA = TS * addVelocity.length();

    m_initObjects[0].mass = M1;
    m_initObjects[1].mass = M2;

    m_initObjects[0].position = Math::Vec3<long double>(R1, 0.0L, 1.0L);
    m_initObjects[1].position = Math::Vec3<long double>(-R2, 0.0L, 1.0L);

    m_initObjects[0].velocity = addVelocity + Math::Vec3<long double>(0.0L, V1, 0.0L);
    m_initObjects[1].velocity = addVelocity + Math::Vec3<long double>(0.0L, -V2, 0.0L);

    QString html = "<table cellspacing=\"5\">";
    html += htmlRow1(tr("G [m^3/(kg * s^2)]"), G);
    html += htmlRow1(tr("Force [N]"), F);
    html += htmlRow1(tr("Distance [m]"), D);
    html += htmlRow1(tr("Period [s]"), T0);
    html += htmlRow1(tr("Duration [s]"), TS);
    html += htmlRow1(tr("Angle [deg]"), Math::toDeg<long double>(2.0l * M_PIl * TS / T0));
    html += "<tr><td> </td><td>" + tr("Object 1") + "</td><td>" + tr("Object 2") + "</td></tr>";
    html += htmlRow2(tr("Radius [m]"), R1, R2);
    html += htmlRow2(tr("Velocity [m/s]"), V1, V2);
    html += htmlRow2(tr("Acceleration [m/s^2]"), A1, A2);
    html += htmlRow2(tr("Circle length [m]"), L1, L2);
    html += htmlRow2(tr("Path circle length [m]"), TS * V1, TS * V1);
    if (!Type::isNull(TSA))
    {
        html += htmlRow1(tr("Path add length [m]"), TSA);
        html += htmlRow2(tr("Path total length [m]"), TS * V1 + TSA, TS * V1 + TSA);
    }
    html += "</table>";

    m_info->setText(html);
}
