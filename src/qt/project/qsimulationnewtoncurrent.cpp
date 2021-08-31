/*!
 * \file qt/project/qsimulationnewtoncurrent.cpp
 * \author Michal Steller
 * \brief Class implementation - QT Simulation for newton \b current physics
 */

#include "qsimulationnewtoncurrent.h"

/*!
 * \brief Constructor
 * \param _ID Simulation ID
 * \param _parent Parent \c QObject
 */
Universe1::Project::QSimulationNewtonCurrent::QSimulationNewtonCurrent(const QString &_ID, QObject *_parent)
    : QSimulation(_ID, _parent)
    , m_precision(PrecisionFloat)
{
}

/*!
 * \brief Getter for simulation type (\a QSimulation::SimulationNewtonCurrent)
 * \returns The simulation type (\a QSimulation::SimulationNewtonCurrent)
 */
Universe1::Project::QSimulation::SimulationType Universe1::Project::QSimulationNewtonCurrent::simulationType() const
{
    return QSimulation::SimulationNewtonCurrent;
}

/*!
 * \brief Getter for simulation precision
 * \returns The simulation precision
 */
Universe1::Project::QSimulation::Precision Universe1::Project::QSimulationNewtonCurrent::precision() const
{
    return m_precision;
}

/*!
 * \brief Getter for using history flag (\c false)
 * \returns Using history flag (\c false)
 */
bool Universe1::Project::QSimulationNewtonCurrent::usesHistory() const
{
    return false;
}

/*!
 * \brief Not supported (This is current time based simulation )
 * \param _out Output buffer
 * \param _eventTimeStamp Time-stamp of event
 * \param _eventPosition Event location
 * \returns \c false
 */
bool Universe1::Project::QSimulationNewtonCurrent::loadEventSource(std::vector<std::pair<double, QVector3D>> &_out,
                                                                   const double _eventTimeStamp,
                                                                   const QVector3D &_eventPosition) const
{
    Q_UNUSED(_out)
    Q_UNUSED(_eventTimeStamp)
    Q_UNUSED(_eventPosition)
    return false;
}

/*!
 * \brief Getter for using element radius flag (\c false - Elements are singularities)
 * \returns Using element radius flag (\c false - Elements are singularities)
 */
bool Universe1::Project::QSimulationNewtonCurrent::usesRadius() const
{
    return false;
}

/*!
 * \brief Getter for collection of supported/required physics constants
 * \returns Supported physics constants
 */
const std::set<Universe1::Simulation::ConstantName> &
Universe1::Project::QSimulationNewtonCurrent::supportedPhysicsConstants() const
{
    static const std::set<Universe1::Simulation::ConstantName> supported = {
        Universe1::Simulation::Const_GravityConstant};
    return supported;
}

/*!
 * \brief Getter for physics constant
 * \param _name Constant name
 * \returns Physics constant value
 */
double
Universe1::Project::QSimulationNewtonCurrent::getPhysicsConstant(const Universe1::Simulation::ConstantName &_name) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return static_cast<double>(m_simF.physics().getValue(_name));
    case PrecisionDouble: return m_simD.physics().getValue(_name);
    case PrecisionLongDouble: return static_cast<double>(m_simL.physics().getValue(_name));
    }
    return 0.0;
}

/*!
 * \brief Getter for maximum calculation step time duration
 * \returns Maximum calculation step time duration
 */
double Universe1::Project::QSimulationNewtonCurrent::getMaximumStepTime() const
{
    switch (m_precision)
    {
    case PrecisionFloat: return static_cast<double>(m_simF.maximumStepTime());
    case PrecisionDouble: return m_simD.maximumStepTime();
    case PrecisionLongDouble: return static_cast<double>(m_simL.maximumStepTime());
    }
    return 0.0;
}

/*!
 * \brief Getter for maximum calculation step time curving angle
 * \returns Maximum calculation step time curving angle [degrees]
 */
double Universe1::Project::QSimulationNewtonCurrent::getMaximumCurveAngleDeg() const
{
    switch (m_precision)
    {
    case PrecisionFloat: return static_cast<double>(m_simF.maximumCurveAngleDeg());
    case PrecisionDouble: return m_simD.maximumCurveAngleDeg();
    case PrecisionLongDouble: return static_cast<double>(m_simL.maximumCurveAngleDeg());
    }
    return 0.0;
}

/*!
 * \brief Getter for collection of supported element properties
 * \returns Supported element properties
 */
Universe1::Project::QSimulation::ElementProperties
Universe1::Project::QSimulationNewtonCurrent::supportedElementProperties() const
{
    static const ElementProperties supported = PropertyMass | PropertyVelocity | PropertyAcceleration | PropertyForce;
    return supported;
}

/*!
 * \brief Getter for count of object under initialization
 * \returns Count of object under initialization
 */
size_t Universe1::Project::QSimulationNewtonCurrent::objectCountInit() const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.initObjects().size();
    case PrecisionDouble: return m_simD.initObjects().size();
    case PrecisionLongDouble: return m_simL.initObjects().size();
    }
    return 0U;
}

/*!
 * \brief Getter for count of object under calculation
 * \returns Count of object under calculation
 */
size_t Universe1::Project::QSimulationNewtonCurrent::objectCountCalc() const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.objects().size();
    case PrecisionDouble: return m_simD.objects().size();
    case PrecisionLongDouble: return m_simL.objects().size();
    }
    return 0U;
}

/*!
 * \brief Fill output vector with initialization object time-stamps and positions
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns \c true if success
 */
bool Universe1::Project::QSimulationNewtonCurrent::loadInitPath(std::vector<std::pair<double, QVector3D>> &_out,
                                                                const size_t _objectID) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadInitPath(_out, _objectID);
    case PrecisionDouble: return m_simD.loadInitPath(_out, _objectID);
    case PrecisionLongDouble: return m_simL.loadInitPath(_out, _objectID);
    }
    return false;
}

/*!
 * \brief Fill output vector with calculation object time-stamps and positions
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns \c true if success
 */
bool Universe1::Project::QSimulationNewtonCurrent::loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out,
                                                                const size_t _objectID) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadCalcPath(_out, _objectID);
    case PrecisionDouble: return m_simD.loadCalcPath(_out, _objectID);
    case PrecisionLongDouble: return m_simL.loadCalcPath(_out, _objectID);
    }
    return false;
}

/*!
 * \brief Getter for initialization object position
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonCurrent::loadInitPosition(const size_t _objectID,
                                                                                          const double _timeStamp) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadInitPosition(_objectID, _timeStamp);
    case PrecisionDouble: return m_simD.loadInitPosition(_objectID, _timeStamp);
    case PrecisionLongDouble: return m_simL.loadInitPosition(_objectID, _timeStamp);
    }
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object position
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonCurrent::loadCalcPosition(const size_t _objectID,
                                                                                          const double _timeStamp) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadCalcPosition(_objectID, _timeStamp);
    case PrecisionDouble: return m_simD.loadCalcPosition(_objectID, _timeStamp);
    case PrecisionLongDouble: return m_simL.loadCalcPosition(_objectID, _timeStamp);
    }
    return {false, QVector3D()};
}

/*!
 * \brief Universal getter for initialization object property
 * \param _property Property to load
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonCurrent::loadInitProperty(
    const ElementProperty _property, const size_t _objectID, const double _timeStamp) const
{
    switch (_property)
    {
    case QSimulation::PropertyMass:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitMass(_objectID);
        case PrecisionDouble: return m_simD.loadInitMass(_objectID);
        case PrecisionLongDouble: return m_simL.loadInitMass(_objectID);
        }
        break;

    case QSimulation::PropertyVelocity:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitVelocity(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitVelocity(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitVelocity(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyAcceleration:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitAccel(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitAccel(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitAccel(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyForce:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitForce(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitForce(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitForce(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyNone:
    case QSimulation::PropertySpin:
    case QSimulation::PropertySpinRed:
    case QSimulation::PropertySpinGreen:
    case QSimulation::PropertySpinBlue:
    case QSimulation::PropertyForceRed:
    case QSimulation::PropertyForceGreen:
    case QSimulation::PropertyForceBlue: break;
    }
    return {false, QVector3D()};
}

/*!
 * \brief Universal getter for calculation object property
 * \param _property Property to load
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonCurrent::loadCalcProperty(
    const ElementProperty _property, const size_t _objectID, const double _timeStamp) const
{
    switch (_property)
    {
    case QSimulation::PropertyMass:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcMass(_objectID);
        case PrecisionDouble: return m_simD.loadCalcMass(_objectID);
        case PrecisionLongDouble: return m_simL.loadCalcMass(_objectID);
        }
        break;

    case QSimulation::PropertyVelocity:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcVelocity(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcVelocity(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcVelocity(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyAcceleration:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcAccel(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcAccel(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcAccel(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyForce:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcForce(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcForce(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcForce(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyNone:
    case QSimulation::PropertySpin:
    case QSimulation::PropertySpinRed:
    case QSimulation::PropertySpinGreen:
    case QSimulation::PropertySpinBlue:
    case QSimulation::PropertyForceRed:
    case QSimulation::PropertyForceGreen:
    case QSimulation::PropertyForceBlue: break;
    }
    return {false, QVector3D()};
}

/*!
 * \brief Calculate simulation, filling all object's histories
 * \param _stepCount Step count to calculate
 * \returns Success flag
 * \sa Universe1::Simulation::Simulation::createSimulation(const size_t)
 */
bool Universe1::Project::QSimulationNewtonCurrent::createSimulation()
{
    bool result = false;
    switch (m_precision)
    {
    case PrecisionFloat: result = m_simF.createSimulation(m_calculationStepCount); break;
    case PrecisionDouble: result = m_simD.createSimulation(m_calculationStepCount); break;
    case PrecisionLongDouble: result = m_simL.createSimulation(m_calculationStepCount); break;
    }
    emit dataChanged();
    return result;
}

/*!
 * \brief Helper template function, process job for QSimulationNewtonCurrent::initializeFromObjects
 * \param _objects Collection of starting object's properties
 * \param _sim The simulation
 */
template <typename T>
void initObj(const std::vector<Universe1::Project::QSimulationNewtonCurrent::InitObject> &_objects,
             Universe1::Simulation::GravityNewton::SimulationNewtonCurrent<T> &_sim)
{
    std::vector<std::tuple<T, Universe1::Math::Vec3<T>, Universe1::Math::Vec3<T>>> tmp(_objects.size());
    size_t idx = 0;
    for (const Universe1::Project::QSimulationNewtonCurrent::InitObject &io : _objects)
    {
        std::get<0>(tmp.at(idx)) = io.mass;
        std::get<1>(tmp.at(idx)) = io.position.converted<T>();
        std::get<2>(tmp.at(idx)) = io.velocity.converted<T>();
        ++idx;
    }
    _sim.initializeObjects(tmp);
}

/*!
 * \brief Initialize objects from given collection
 * \param _objects Collection of starting object's properties
 */
void Universe1::Project::QSimulationNewtonCurrent::initializeFromObjects(const std::vector<InitObject> &_objects)
{
    m_currentInitObjects = _objects;
    switch (m_precision)
    {
    case PrecisionFloat: initObj(m_currentInitObjects, m_simF); break;
    case PrecisionDouble: initObj(m_currentInitObjects, m_simD); break;
    case PrecisionLongDouble: initObj(m_currentInitObjects, m_simL); break;
    }
    emit dataChanged();
}

/*!
 * \brief Initialize objects from given collection and calculates simulation
 * \param _objects Collection of starting object's properties
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNewtonCurrent::rebuildSimulation(const std::vector<InitObject> &_objects)
{
    switch (m_precision)
    {
    case PrecisionFloat: initObj(_objects, m_simF); break;
    case PrecisionDouble: initObj(_objects, m_simD); break;
    case PrecisionLongDouble: initObj(_objects, m_simL); break;
    }
    return createSimulation();
}

/*!
 * \brief Setter for simulation precision
 * \param _precision New simulation precision
 */
void Universe1::Project::QSimulationNewtonCurrent::setPrecision(Precision _precision)
{
    if (m_precision == _precision)
        return;

    switch (m_precision)
    {
    case PrecisionFloat:
        switch (_precision)
        {
        case PrecisionFloat: break;
        case PrecisionDouble:
            m_simD.fromType(m_simF);
            m_simF.clear();
            break;
        case PrecisionLongDouble:
            m_simL.fromType(m_simF);
            m_simF.clear();
            break;
        }
        break;

    case PrecisionDouble:
        switch (_precision)
        {
        case PrecisionFloat:
            m_simF.fromType(m_simD);
            m_simD.clear();
            break;
        case PrecisionDouble: break;
        case PrecisionLongDouble:
            m_simL.fromType(m_simD);
            m_simD.clear();
            break;
        }
        break;

    case PrecisionLongDouble:
        switch (_precision)
        {
        case PrecisionFloat:
            m_simF.fromType(m_simL);
            m_simL.clear();
            break;
        case PrecisionDouble:
            m_simD.fromType(m_simL);
            m_simL.clear();
            break;
        case PrecisionLongDouble: break;
        }
        break;
    }

    m_precision = _precision;

    emit dataChanged();
}

/*!
 * \brief Setter for universe constant
 * \param _constantName New constant name
 * \param _value New constant value
 */
void Universe1::Project::QSimulationNewtonCurrent::setUniverseConstant(
    const Universe1::Simulation::ConstantName _constantName, const double _value)
{
    switch (m_precision)
    {
    case PrecisionFloat: m_simF.physics().setValue(_constantName, _value); break;
    case PrecisionDouble: m_simD.physics().setValue(_constantName, _value); break;
    case PrecisionLongDouble: m_simL.physics().setValue(_constantName, _value); break;
    }
    emit physicsChanged();
}

/*!
 * \brief Setter for maximum calculation step time duration
 * \param _value New value
 */
void Universe1::Project::QSimulationNewtonCurrent::setMaximumStepTime(const double _value)
{
    switch (m_precision)
    {
    case PrecisionFloat: m_simF.setMaximumStepTime(_value); break;
    case PrecisionDouble: m_simD.setMaximumStepTime(_value); break;
    case PrecisionLongDouble: m_simL.setMaximumStepTime(_value); break;
    }
    emit physicsChanged();
}

/*!
 * \brief Setter for maximum calculation step curving angle [degrees]
 * \param _value New angle value [degrees]
 */
void Universe1::Project::QSimulationNewtonCurrent::setMaximumCurveAngleDeg(const double _value)
{
    switch (m_precision)
    {
    case PrecisionFloat: m_simF.setMaximumCurveAngleDeg(_value); break;
    case PrecisionDouble: m_simD.setMaximumCurveAngleDeg(_value); break;
    case PrecisionLongDouble: m_simL.setMaximumCurveAngleDeg(_value); break;
    }
    emit physicsChanged();
}
