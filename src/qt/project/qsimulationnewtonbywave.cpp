/*!
 * \file qt/project/qsimulationnewtonbywave.cpp
 * \author Michal Steller
 * \brief Class implementation - QT Simulation for newton \b wave physics
 */

#include "qsimulationnewtonbywave.h"

/*!
 * \brief Constructor
 * \param _ID Simulation ID
 * \param _parent Parent \c QObject
 */
Universe1::Project::QSimulationNewtonByWave::QSimulationNewtonByWave(const QString &_ID, QObject *_parent)
    : QSimulation(_ID, _parent)
    , m_precision(PrecisionFloat)
{
}

/*!
 * \brief Getter for simulation type (\a QSimulation::SimulationNewtonByWave)
 * \returns The simulation type (\a QSimulation::SimulationNewtonByWave)
 */
Universe1::Project::QSimulation::SimulationType Universe1::Project::QSimulationNewtonByWave::simulationType() const
{
    return QSimulation::SimulationNewtonByWave;
}

/*!
 * \brief Getter for simulation precision
 * \returns The simulation precision
 */
Universe1::Project::QSimulation::Precision Universe1::Project::QSimulationNewtonByWave::precision() const
{
    return m_precision;
}

/*!
 * \brief Getter for using history flag (\c true)
 * \returns Using history flag (\c true)
 */
bool Universe1::Project::QSimulationNewtonByWave::usesHistory() const
{
    return true;
}

/*!
 * \brief Object's can't access higher generation
 * \returns \c false
 */
bool Universe1::Project::QSimulationNewtonByWave::usesGenerations() const
{
    return false;
}

/*!
 * \brief Load object's wave sources positions for observer
 * \param _out Output buffer
 * \param _eventTimeStamp Time-stamp of observer
 * \param _eventPosition Observer location
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNewtonByWave::loadEventSource(std::vector<std::pair<double, QVector3D>> &_out,
                                                                  const double _eventTimeStamp,
                                                                  const QVector3D &_eventPosition) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadEventSource(_out, _eventTimeStamp, _eventPosition);
    case PrecisionDouble: return m_simD.loadEventSource(_out, _eventTimeStamp, _eventPosition);
    case PrecisionLongDouble: return m_simL.loadEventSource(_out, _eventTimeStamp, _eventPosition);
    }
    return false;
}

/*!
 * \brief Getter for using element radius flag (\c false - Elements are singularities)
 * \returns Using element radius flag (\c false - Elements are singularities)
 */
bool Universe1::Project::QSimulationNewtonByWave::usesRadius() const
{
    return false;
}

/*!
 * \brief Getter for collection of supported/required physics constants
 * \returns Supported physics constants
 */
const std::set<Universe1::Simulation::ConstantName> &
Universe1::Project::QSimulationNewtonByWave::supportedPhysicsConstants() const
{
    static const std::set<Universe1::Simulation::ConstantName> supported = {
        Universe1::Simulation::Const_UniverseVelocity, Universe1::Simulation::Const_GravityConstant

    };
    return supported;
}

/*!
 * \brief Getter for physics constant
 * \param _name Constant name
 * \returns Physics constant value
 */
double
Universe1::Project::QSimulationNewtonByWave::getPhysicsConstant(const Universe1::Simulation::ConstantName &_name) const
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
double Universe1::Project::QSimulationNewtonByWave::getMaximumStepTime() const
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
double Universe1::Project::QSimulationNewtonByWave::getMaximumCurveAngleDeg() const
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
Universe1::Project::QSimulationNewtonByWave::supportedElementProperties() const
{
    static const ElementProperties supported = PropertyMass | PropertyVelocity | PropertyAcceleration | PropertyForce;
    return supported;
}

/*!
 * \brief Getter for count of object under initialization
 * \returns Count of object under initialization
 */
size_t Universe1::Project::QSimulationNewtonByWave::objectCountInit() const
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
size_t Universe1::Project::QSimulationNewtonByWave::objectCountCalc() const
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
bool Universe1::Project::QSimulationNewtonByWave::loadInitPath(std::vector<std::pair<double, QVector3D>> &_out,
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
bool Universe1::Project::QSimulationNewtonByWave::loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out,
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
 * \brief Generation 2 not supported
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns \c false
 */
bool Universe1::Project::QSimulationNewtonByWave::loadInitPath2(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    Q_UNUSED(_out)
    Q_UNUSED(_objectID)
    return false;
}

/*!
 * \brief Generation 2 not supported
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns \c false
 */
bool Universe1::Project::QSimulationNewtonByWave::loadCalcPath2(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    Q_UNUSED(_out)
    Q_UNUSED(_objectID)
    return false;
}

/*!
 * \brief Generation 3 not supported
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns \c false
 */
bool Universe1::Project::QSimulationNewtonByWave::loadInitPath3(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    Q_UNUSED(_out)
    Q_UNUSED(_objectID)
    return false;
}

/*!
 * \brief Generation 2 not supported
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns \c false
 */
bool Universe1::Project::QSimulationNewtonByWave::loadCalcPath3(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    Q_UNUSED(_out)
    Q_UNUSED(_objectID)
    return false;
}

/*!
 * \brief Getter for initialization object position
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadInitPosition(const size_t _objectID,
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
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadCalcPosition(const size_t _objectID,
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
 * \brief Generation 2 not supported
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns \c false and null \c QVector3D pair
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadInitPosition2(const size_t _objectID,
                                                                                          const double _timeStamp) const
{
    Q_UNUSED(_objectID)
    Q_UNUSED(_timeStamp)
    return {false, QVector3D()};
}

/*!
 * \brief Generation 2 not supported
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns \c false and null \c QVector3D pair
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadCalcPosition2(const size_t _objectID,
                                                                                          const double _timeStamp) const
{
    Q_UNUSED(_objectID)
    Q_UNUSED(_timeStamp)
    return {false, QVector3D()};
}

/*!
 * \brief Generation 3 not supported
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns \c false and null \c QVector3D pair
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadInitPosition3(const size_t _objectID,
                                                                                          const double _timeStamp) const
{
    Q_UNUSED(_objectID)
    Q_UNUSED(_timeStamp)
    return {false, QVector3D()};
}

/*!
 * \brief Generation 3 not supported
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns \c false and null \c QVector3D pair
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadCalcPosition3(const size_t _objectID,
                                                                                          const double _timeStamp) const
{
    Q_UNUSED(_objectID)
    Q_UNUSED(_timeStamp)
    return {false, QVector3D()};
}

/*!
 * \brief Universal getter for initialization object property
 * \param _property Property to load
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadInitProperty(
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

    default: break;
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
std::pair<bool, QVector3D> Universe1::Project::QSimulationNewtonByWave::loadCalcProperty(
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

    default: break;
    }
    return {false, QVector3D()};
}

/*!
 * \brief Calculate simulation, filling all object's histories
 * \param _stepCount Step count to calculate
 * \returns Success flag
 * \sa Universe1::Simulation::Simulation::createSimulation(const size_t)
 */
bool Universe1::Project::QSimulationNewtonByWave::createSimulation()
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
 * \brief Initialize objects from given collection
 * \param _objects Collection of starting object's properties
 * \param _doEmit Flag if emit \c dataChanged() signal
 */
void Universe1::Project::QSimulationNewtonByWave::initializeFromObjects(
    const std::vector<Simulation::GravityNewton::NewtonObjectByWave<long double>> &_objects, const bool _doEmit)
{
    switch (m_precision)
    {
    case PrecisionFloat:
        m_simF.initObjects().clear();
        m_simF.initObjects().reserve(_objects.size());
        for (const Universe1::Simulation::GravityNewton::NewtonObjectByWave<long double> &io : _objects)
            m_simF.initObjects().push_back(io.createCopy<float>());
        break;

    case PrecisionDouble:
        m_simD.initObjects().clear();
        m_simD.initObjects().reserve(_objects.size());
        for (const Universe1::Simulation::GravityNewton::NewtonObjectByWave<long double> &io : _objects)
            m_simD.initObjects().push_back(io.createCopy<double>());
        break;

    case PrecisionLongDouble:
        m_simL.initObjects().clear();
        m_simL.initObjects().reserve(_objects.size());
        for (const Universe1::Simulation::GravityNewton::NewtonObjectByWave<long double> &io : _objects)
            m_simL.initObjects().push_back(io.createCopy<long double>());
        break;
    }

    if (_doEmit)
        emit dataChanged();
}

/*!
 * \brief Initialize objects from given collection and calculates simulation
 * \param _objects Collection of starting object's properties
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNewtonByWave::rebuildSimulation(
    const std::vector<Simulation::GravityNewton::NewtonObjectByWave<long double>> &_objects)
{
    initializeFromObjects(_objects, false);
    return createSimulation();
}

/*!
 * \brief Setter for simulation precision
 * \param _precision New simulation precision
 */
void Universe1::Project::QSimulationNewtonByWave::setPrecision(Precision _precision)
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
void Universe1::Project::QSimulationNewtonByWave::setUniverseConstant(
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
void Universe1::Project::QSimulationNewtonByWave::setMaximumStepTime(const double _value)
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
void Universe1::Project::QSimulationNewtonByWave::setMaximumCurveAngleDeg(const double _value)
{
    switch (m_precision)
    {
    case PrecisionFloat: m_simF.setMaximumCurveAngleDeg(_value); break;
    case PrecisionDouble: m_simD.setMaximumCurveAngleDeg(_value); break;
    case PrecisionLongDouble: m_simL.setMaximumCurveAngleDeg(_value); break;
    }
    emit physicsChanged();
}
