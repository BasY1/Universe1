/*!
 * \file qt/widgets/simulationeditor/widgetgeneratorneutrino.cpp
 * \author Michal Steller
 * \brief Neutrino simulation initialization data generator widget classes implementation
 */

#include "widgetgeneratorneutrino.h"

#include "../../../math/texttools.h"

#include <QSettings>

/*!
 * \brief Constructor
 * \param _simulation Processing simulation
 * \param _parent Parent \c QWidget
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNeutrino::WidgetGeneratorNeutrino(
    Project::QSimulationNeutrino *_simulation, QWidget *_parent)
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
Universe1::Widgets::SimulationEditor::WidgetGeneratorNeutrinoSingle::WidgetGeneratorNeutrinoSingle(
    Project::QSimulationNeutrino *_simulation, QWidget *_parent)
    : WidgetGeneratorNeutrino(_simulation, _parent)
// , m_info(new QLabel())
{
    // const QSettings settings;
    // static const QString key = "SimulationEditor/WidgetGeneratorNeutrinoSingle/";
    // static const std::pair<QVector3D, QVector3D> refRangePos = {QVector3D(-10.0F, -10.0F, -10.0F),
    //                                                             QVector3D(10.0F, 10.0F, 10.0F)};
    // static const std::pair<QVector3D, QVector3D> refRangeVel = {QVector3D(-2.0F, -2.0F, -2.0F),
    //                                                             QVector3D(2.0F, 2.0F, 2.0F)};
    // int row = 0;
    // QGridLayout *lay = new QGridLayout();
    //
    // m_mass1 = new GUI::GuiFloat(settings.value(key + "mass1", 1.0F).toFloat(), 0.01F, 100.0F, 2, Qt::Horizontal);
    // m_mass2 = new GUI::GuiFloat(settings.value(key + "mass2", 1.0F).toFloat(), 0.01F, 100.0F, 2, Qt::Horizontal);
    //
    // m_position1 =
    //     new GUI::GuiVector3D(settings.value(key + "position1", QVector3D(-2.0F, -2.0F, 1.0F)).value<QVector3D>(),
    //                          refRangePos,
    //                          3,
    //                          Qt::Horizontal);
    //
    // m_position2 =
    //     new GUI::GuiVector3D(settings.value(key + "position2", QVector3D(2.0F, 2.0F, 1.0F)).value<QVector3D>(),
    //                          refRangePos,
    //                          3,
    //                          Qt::Horizontal);
    //
    // m_velocity1 =
    //     new GUI::GuiVector3D(settings.value(key + "velocity1", QVector3D(-1.0F, 1.0F, 0.0F) *
    //     0.1F).value<QVector3D>(),
    //                          refRangeVel,
    //                          3,
    //                          Qt::Horizontal);
    //
    // m_velocity2 =
    //     new GUI::GuiVector3D(settings.value(key + "velocity2", QVector3D(1.0F, -1.0F, 0.0F) *
    //     0.1F).value<QVector3D>(),
    //                          refRangeVel,
    //                          3,
    //                          Qt::Horizontal);
    //
    // connect(m_mass1, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonByWaveUser2::rebuild);
    // connect(m_mass2, &GUI::GuiFloat::changed, this, &WidgetGeneratorNewtonByWaveUser2::rebuild);
    // connect(m_position1, &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonByWaveUser2::rebuild);
    // connect(m_position2, &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonByWaveUser2::rebuild);
    // connect(m_velocity1, &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonByWaveUser2::rebuild);
    // connect(m_velocity2, &GUI::GuiVector3D::changed, this, &WidgetGeneratorNewtonByWaveUser2::rebuild);
    //
    // m_mass1->layoutRow(tr("Mass 1"), lay, row);
    // m_position1->layoutRow(tr("Position"), lay, row);
    // m_velocity1->layoutRow(tr("Velocity"), lay, row);
    //
    // lay->addWidget(new HorizontalLineSpacer(), row++, 0, 1, 4);
    //
    // m_mass2->layoutRow(tr("Mass 2"), lay, row);
    // m_position2->layoutRow(tr("Position"), lay, row);
    // m_velocity2->layoutRow(tr("Velocity"), lay, row);
    //
    // m_info->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // m_info->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    //
    // lay->addWidget(m_info, row++, 0, 1, 4);
    //
    // setLayout(lay);
    //
    // rebuild();
}

/*!
 * \brief Destructor
 */
Universe1::Widgets::SimulationEditor::WidgetGeneratorNeutrinoSingle::~WidgetGeneratorNeutrinoSingle()
{
    static const QString key = "SimulationEditor/WidgetGeneratorNeutrinoSingle/";
    // QSettings settings;
    //
    // settings.setValue(key + "mass1", m_mass1->value());
    // settings.setValue(key + "mass2", m_mass2->value());
    // settings.setValue(key + "position1", m_position1->value());
    // settings.setValue(key + "position2", m_position2->value());
    // settings.setValue(key + "velocity1", m_velocity1->value());
    // settings.setValue(key + "velocity2", m_velocity2->value());
    //
    // delete m_mass1;
    // delete m_mass2;
    // delete m_position1;
    // delete m_position2;
    // delete m_velocity1;
    // delete m_velocity2;
}

/*!
 * \brief Generator name getter
 * \returns "User objects [2]" string
 */
QString Universe1::Widgets::SimulationEditor::WidgetGeneratorNeutrinoSingle::generatorName() const
{
    return tr("User objects [2]");
}

/*!
 * \brief Object GUI changed value
 */
void Universe1::Widgets::SimulationEditor::WidgetGeneratorNeutrinoSingle::rebuild()
{
    m_initObjects.clear();

    //    static const int maxSearchLoops = 20;
    //
    //    const long double CNT = m_simulation->calculationStepCount();
    //    const long double G = m_simulation->getConstantGravityConstant();
    //    const long double C = m_simulation->getConstantUniverseVelocity();
    //    const long double DT = m_simulation->getMaximumStepTime();
    //    const long double TS = CNT * DT;
    //
    //    const long double M1 = m_mass1->value();
    //    const long double M2 = m_mass2->value();
    //
    //    Math::Vec3<long double> P1 = Math::Vec3<long double>::fromQVector3D(m_position1->value());
    //    Math::Vec3<long double> P2 = Math::Vec3<long double>::fromQVector3D(m_position2->value());
    //    Math::Vec3<long double> V1 = Math::Vec3<long double>::fromQVector3D(m_velocity1->value());
    //    Math::Vec3<long double> V2 = Math::Vec3<long double>::fromQVector3D(m_velocity2->value());
    //    if (P1 == P2)
    //    {
    //        m_info->setText(tr("Same object positions !"));
    //        return;
    //    }
    //
    //    if (V1.length() >= C)
    //    {
    //        m_info->setText(tr("Velocity 1 too fast !"));
    //        return;
    //    }
    //
    //    if (V2.length() >= C)
    //    {
    //        m_info->setText(tr("Velocity 2 too fast !"));
    //        return;
    //    }
    //
    //    std::pair<Simulation::GravityNewton::NewtonTimeStamp<long double>, bool> moved1 = {
    //        Simulation::GravityNewton::NewtonTimeStamp<long double>(), false};
    //    std::pair<Simulation::GravityNewton::NewtonTimeStamp<long double>, bool> moved2 = {
    //        Simulation::GravityNewton::NewtonTimeStamp<long double>(), false};
    //
    //    std::list<Simulation::GravityNewton::NewtonTimeStamp<long double>> history1;
    //    std::list<Simulation::GravityNewton::NewtonTimeStamp<long double>> history2;
    //    history1.push_front(Simulation::GravityNewton::NewtonTimeStamp<long double>(0.0L, P1, V1));
    //    history2.push_front(Simulation::GravityNewton::NewtonTimeStamp<long double>(0.0L, P2, V2));
    //
    //    int step = 0;
    //
    //    while (true)
    //    {
    //        Simulation::GravityNewton::NewtonTimeStamp<long double> &ts1 = history1.front();
    //        Simulation::GravityNewton::NewtonTimeStamp<long double> &ts2 = history2.front();
    //
    //        const long double dist0 = ts1.position.distanceToPoint(ts2.position);
    //        const long double force0 = G * M1 * M2 / (dist0 * dist0);
    //        const long double accel0_1 = force0 / M1;
    //        const long double accel0_2 = force0 / M2;
    //        const Math::Vec3<long double> nor0 = (ts2.position - ts1.position).normalized();
    //
    //        ts1.moveAccel = nor0 * accel0_1;
    //        ts2.moveAccel = -nor0 * accel0_2;
    //
    //        for (int loop = 1; loop <= maxSearchLoops; ++loop)
    //        {
    //            moved1 = ts1.movedToEventSource(C, 0.0L, P2);
    //            if (!moved1.second)
    //            {
    //                m_info->setText(tr("Step %1/%2: can't move object 1!").arg(step).arg(loop));
    //                return;
    //            }
    //
    //            const Math::Vec3<long double> dir2Moved1 = P2 - moved1.first.position;
    //            const Math::Vec3<long double> nor2Moved1 = dir2Moved1.normalized();
    //            const long double dist2Moved1 = dir2Moved1.length();
    //
    //            if (Type::isNull(dist2Moved1))
    //            {
    //                m_info->setText(tr("Step %1/%2: Moved object 1 same as current 2!").arg(step).arg(loop));
    //                return;
    //            }
    //
    //            const long double force2Moved1 = G * M1 * M2 / (dist2Moved1 * dist2Moved1);
    //            const long double accel2Moved1 = force2Moved1 / M2;
    //
    //            const Math::Vec3<long double> newAccel2 = -nor2Moved1 * accel2Moved1;
    //            const long double error2Moved1 = ts2.moveAccel.distanceToPoint(newAccel2);
    //            ts2.moveAccel = newAccel2;
    //            //
    //
    //            moved2 = ts2.movedToEventSource(C, 0.0L, P1);
    //            if (!moved2.second)
    //            {
    //                m_info->setText(tr("Step %1/%2: can't move object 2!").arg(step).arg(loop));
    //                return;
    //            }
    //
    //            const Math::Vec3<long double> dir1Moved2 = moved2.first.position - P1;
    //            const long double dist1Moved2 = dir1Moved2.length();
    //            const Math::Vec3<long double> nor1Moved2 = dir1Moved2.normalized();
    //
    //            if (Type::isNull(dist1Moved2))
    //            {
    //                m_info->setText(tr("Step %1/%2: Moved object 2 same as current 1!").arg(step).arg(loop));
    //                return;
    //            }
    //
    //            const long double force1Moved2 = G * M1 * M2 / (dist1Moved2 * dist1Moved2);
    //            const long double accel1Moved2 = force1Moved2 / M1;
    //
    //            const Math::Vec3<long double> newAccel1 = nor1Moved2 * accel1Moved2;
    //            const long double error1Moved2 = ts1.moveAccel.distanceToPoint(newAccel1);
    //            ts1.moveAccel = newAccel1;
    //
    //            if (Type::isNull(error1Moved2) && Type::isNull(error2Moved1))
    //                break;
    //
    //            if (loop == 20)
    //            {
    //                m_info->setText(tr("Step %1/%2: Out of loop range!").arg(step).arg(loop));
    //                return;
    //            }
    //        }
    //
    //        const Simulation::GravityNewton::NewtonTimeStamp<long double> next1 = ts1.moved(-DT);
    //        const Simulation::GravityNewton::NewtonTimeStamp<long double> next2 = ts2.moved(-DT);
    //        history1.push_front(next1);
    //        history2.push_front(next2);
    //        ++step;
    //
    //        moved1 = next1.movedToEventSource(C, 0.0L, P2);
    //        if (!moved1.second)
    //        {
    //            m_info->setText(tr("Step %1: can't finalize move object 1!").arg(step));
    //            return;
    //        }
    //
    //        moved2 = next2.movedToEventSource(C, 0.0L, P1);
    //        if (!moved2.second)
    //        {
    //            m_info->setText(tr("Step %1: can't finalize move object 2!").arg(step));
    //            return;
    //        }
    //
    //        if (moved1.first.timeStamp > next1.timeStamp && moved2.first.timeStamp > next2.timeStamp)
    //            break;
    //    }
    //
    //    m_initObjects.reserve(2);
    //    m_initObjects.push_back(Simulation::GravityNewton::NewtonObjectByWave<long double>(0U, M1));
    //    m_initObjects.push_back(Simulation::GravityNewton::NewtonObjectByWave<long double>(1U, M2));
    //    Simulation::GravityNewton::NewtonObjectByWave<long double> &obj1 = m_initObjects[0];
    //    Simulation::GravityNewton::NewtonObjectByWave<long double> &obj2 = m_initObjects[1];
    //
    //    std::list<Simulation::GravityNewton::NewtonTimeStamp<long double>>::iterator i1 = history1.begin();
    //    std::list<Simulation::GravityNewton::NewtonTimeStamp<long double>>::iterator i2 = i1;
    //    ++i2;
    //    for (; i2 != history1.end(); ++i1, ++i2)
    //        (*i1).moveAccel = (*i2).moveAccel;
    //
    //    i1 = history2.begin();
    //    i2 = i1;
    //    ++i2;
    //    for (; i2 != history2.end(); ++i1, ++i2)
    //        (*i1).moveAccel = (*i2).moveAccel;
    //
    //    history1.back().moveAccel.clear();
    //    history2.back().moveAccel.clear();
    //    obj1.initHistory(history1);
    //    obj2.initHistory(history2);
    //
    //    static const int decs = 5;
    //    QString html = "<table cellspacing=\"5\">";
    //    html += TextTools::htmlRow1of3(tr("Gravity G [m^3/(kg * s^2)]"), G, decs);
    //    html += TextTools::htmlRow1of3(tr("Velocity C [m/s]"), C, decs);
    //    html += TextTools::htmlRow2of3(tr("Velocity [m/s]"), V1.length(), V2.length(), decs);
    //    html += TextTools::htmlRow2of3(tr("Velocity ratio [%]"), 100.0L * V1.length() / C, 100.0L * V2.length() / C,
    //    decs);
    //
    //    html += TextTools::htmlRow1of3(tr("Steps [1]"), QString::number(step));
    //    html += TextTools::htmlRow1of3(tr("Calc duration [s]"), TS, decs);
    //    html += TextTools::htmlRow1of3(tr("Step duration [s]"), DT, decs);
    //    html += TextTools::htmlRow2of3(tr("History start [s]"), moved1.first.timeStamp, moved2.first.timeStamp, decs);
    //    html +=
    //        TextTools::htmlRow2of3(tr("History steps [N]"), moved1.first.timeStamp / DT, moved2.first.timeStamp / DT,
    //        decs);
    //
    //    html += TextTools::htmlRow1of3(tr("Real T0 distance [m]"), P1.distanceToPoint(P2), decs);
    //    html += TextTools::htmlRow2of3(tr("Wave T0 distance [m]"),
    //                                   moved1.first.position.distanceToPoint(P2),
    //                                   moved2.first.position.distanceToPoint(P1),
    //                                   decs);
    //
    //    html += "</table>";
    //
    //    m_info->setText(html);
}
