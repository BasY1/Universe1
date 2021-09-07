/*!
 * \file qt/project/qsimulationneutrino.cpp
 * \author Michal Steller
 * \brief Class implementation - QT Simulation for neutrino - pure gravity physics
 */

#include "qsimulationneutrino.h"

/*!
 * \brief Constructor
 * \param _ID Simulation ID
 * \param _parent Parent \c QObject
 */
Universe1::Project::QSimulationNeutrino::QSimulationNeutrino(const QString &_ID, QObject *_parent)
    : QSimulation(_ID, _parent)
    , m_precision(PrecisionFloat)
{
}

/*!
 * \brief Getter for simulation type (\a QSimulation::SimulationNeutrino)
 * \returns The simulation type (\a QSimulation::SimulationNeutrino)
 */
Universe1::Project::QSimulation::SimulationType Universe1::Project::QSimulationNeutrino::simulationType() const
{
    return QSimulation::SimulationNeutrino;
}

/*!
 * \brief Getter for simulation precision
 * \returns The simulation precision
 */
Universe1::Project::QSimulation::Precision Universe1::Project::QSimulationNeutrino::precision() const
{
    return m_precision;
}

/*!
 * \brief Getter for using history flag (\c true)
 * \returns Using history flag (\c true)
 */
bool Universe1::Project::QSimulationNeutrino::usesHistory() const
{
    return true;
}

/*!
 * \brief Object's can access higher generation
 * \returns \c true
 */
bool Universe1::Project::QSimulationNeutrino::usesGenerations() const
{
    return true;
}

/*!
 * \brief Getter for using element radius flag (\c false - Elements are singularities)
 * \returns Using element radius flag (\c false - Elements are singularities)
 */
bool Universe1::Project::QSimulationNeutrino::usesRadius() const
{
    return true;
}

/*!
 * \brief Load object's wave sources positions for observer
 * \param _out Output buffer
 * \param _eventTimeStamp Time-stamp of observer
 * \param _eventPosition Observer location
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNeutrino::loadEventSource(std::vector<std::pair<double, QVector3D>> &_out,
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
 * \brief Getter for collection of supported/required physics constants
 * \returns Supported physics constants
 */
const std::set<Universe1::Simulation::ConstantName> &
Universe1::Project::QSimulationNeutrino::supportedPhysicsConstants() const
{
    static const std::set<Universe1::Simulation::ConstantName> supported = {
        Universe1::Simulation::Const_UniverseVelocity,
        Universe1::Simulation::Const_UniverseVelocity,
        Universe1::Simulation::Const_ElementRadius

    };
    return supported;
}

/*!
 * \brief Getter for physics constant
 * \param _name Constant name
 * \returns Physics constant value
 */
double
Universe1::Project::QSimulationNeutrino::getPhysicsConstant(const Universe1::Simulation::ConstantName &_name) const
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
double Universe1::Project::QSimulationNeutrino::getMaximumStepTime() const
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
double Universe1::Project::QSimulationNeutrino::getMaximumCurveAngleDeg() const
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
Universe1::Project::QSimulationNeutrino::supportedElementProperties() const
{
    static const ElementProperties supported = PropertyVelocity1 | PropertyVelocity2 | PropertyVelocity3 |
        PropertySpin1 | PropertySpin2 | PropertySpin3 | PropertyAcceleration1 | PropertyAcceleration2 |
        PropertyCurving1 | PropertyCurving2 | PropertyPosition2 | PropertyPosition3;
    return supported;
}

/*!
 * \brief Getter for count of object under initialization
 * \returns Count of object under initialization
 */
size_t Universe1::Project::QSimulationNeutrino::objectCountInit() const
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
size_t Universe1::Project::QSimulationNeutrino::objectCountCalc() const
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
bool Universe1::Project::QSimulationNeutrino::loadInitPath(std::vector<std::pair<double, QVector3D>> &_out,
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
bool Universe1::Project::QSimulationNeutrino::loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out,
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
 * \brief Fill output vector with initialization object time-stamps and positions - generation 2
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNeutrino::loadInitPath2(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadInitPath2(_out, _objectID);
    case PrecisionDouble: return m_simD.loadInitPath2(_out, _objectID);
    case PrecisionLongDouble: return m_simL.loadInitPath2(_out, _objectID);
    }
    return false;
}

/*!
 * \brief Fill output vector with calculation object time-stamps and positions - generation 2
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNeutrino::loadCalcPath2(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadCalcPath2(_out, _objectID);
    case PrecisionDouble: return m_simD.loadCalcPath2(_out, _objectID);
    case PrecisionLongDouble: return m_simL.loadCalcPath2(_out, _objectID);
    }
    return false;
}

/*!
 * \brief Fill output vector with initialization object time-stamps and positions - generation 3
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNeutrino::loadInitPath3(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadInitPath3(_out, _objectID);
    case PrecisionDouble: return m_simD.loadInitPath3(_out, _objectID);
    case PrecisionLongDouble: return m_simL.loadInitPath3(_out, _objectID);
    }
    return false;
}

/*!
 * \brief Fill output vector with calculation object time-stamps and positions - generation 3
 * \param _out Output vector
 * \param _objectID Object's index
 * \returns Success flag
 */
bool Universe1::Project::QSimulationNeutrino::loadCalcPath3(
    std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadCalcPath3(_out, _objectID);
    case PrecisionDouble: return m_simD.loadCalcPath3(_out, _objectID);
    case PrecisionLongDouble: return m_simL.loadCalcPath3(_out, _objectID);
    }
    return false;
}

/*!
 * \brief Getter for initialization object position
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadInitPosition(const size_t _objectID,
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
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadCalcPosition(const size_t _objectID,
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
 * \brief Getter for initialization object position - generation 2
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is generation 2 position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadInitPosition2(const size_t _objectID,
                                                                                      const double _timeStamp) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadInitPosition2(_objectID, _timeStamp);
    case PrecisionDouble: return m_simD.loadInitPosition2(_objectID, _timeStamp);
    case PrecisionLongDouble: return m_simL.loadInitPosition2(_objectID, _timeStamp);
    }
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object position - generation 2
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is generation 2 position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadCalcPosition2(const size_t _objectID,
                                                                                      const double _timeStamp) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadCalcPosition2(_objectID, _timeStamp);
    case PrecisionDouble: return m_simD.loadCalcPosition2(_objectID, _timeStamp);
    case PrecisionLongDouble: return m_simL.loadCalcPosition2(_objectID, _timeStamp);
    }
    return {false, QVector3D()};
}

/*!
 * \brief Getter for initialization object position - generation 3
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is generation 3 position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadInitPosition3(const size_t _objectID,
                                                                                      const double _timeStamp) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadInitPosition3(_objectID, _timeStamp);
    case PrecisionDouble: return m_simD.loadInitPosition3(_objectID, _timeStamp);
    case PrecisionLongDouble: return m_simL.loadInitPosition3(_objectID, _timeStamp);
    }
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object position - generation 3
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, where \c first item is success flag, and \c second item is generation 3 position (as \c QVector3D)
 */
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadCalcPosition3(const size_t _objectID,
                                                                                      const double _timeStamp) const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.loadCalcPosition3(_objectID, _timeStamp);
    case PrecisionDouble: return m_simD.loadCalcPosition3(_objectID, _timeStamp);
    case PrecisionLongDouble: return m_simL.loadCalcPosition3(_objectID, _timeStamp);
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
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadInitProperty(const ElementProperty _property,
                                                                                     const size_t _objectID,
                                                                                     const double _timeStamp) const
{
    switch (_property)
    {
    case QSimulation::PropertyVelocity1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitVelocity1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitVelocity1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitVelocity1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyVelocity2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitVelocity2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitVelocity2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitVelocity2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyVelocity3:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitVelocity3(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitVelocity3(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitVelocity3(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertySpin1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitSpin1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitSpin1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitSpin1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertySpin2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitSpin2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitSpin2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitSpin2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertySpin3:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitSpin3(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitSpin3(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitSpin3(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyAcceleration1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitAccel1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitAccel1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitAccel1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyAcceleration2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitAccel2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitAccel2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitAccel2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyCurving1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitCurving1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitCurving1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitCurving1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyCurving2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitCurving2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitCurving2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitCurving2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyPosition2: return loadInitPosition2(_objectID, _timeStamp);
    case QSimulation::PropertyPosition3: return loadInitPosition3(_objectID, _timeStamp);

    case QSimulation::PropertyNone: break;
    case QSimulation::PropertyMass: break;
    case QSimulation::PropertyForce: break;
    case QSimulation::PropertySpinR: break;
    case QSimulation::PropertySpinG: break;
    case QSimulation::PropertySpinB: break;
    case QSimulation::PropertyAccelerationR: break;
    case QSimulation::PropertyAccelerationG: break;
    case QSimulation::PropertyAccelerationB: break;
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
std::pair<bool, QVector3D> Universe1::Project::QSimulationNeutrino::loadCalcProperty(const ElementProperty _property,
                                                                                     const size_t _objectID,
                                                                                     const double _timeStamp) const
{
    switch (_property)
    {
    case QSimulation::PropertyVelocity1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcVelocity1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcVelocity1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcVelocity1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyVelocity2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcVelocity2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcVelocity2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcVelocity2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyVelocity3:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcVelocity3(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcVelocity3(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcVelocity3(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertySpin1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcSpin1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcSpin1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcSpin1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertySpin2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcSpin2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcSpin2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcSpin2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertySpin3:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcSpin3(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcSpin3(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcSpin3(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyAcceleration1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcAccel1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcAccel1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcAccel1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyAcceleration2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcAccel2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcAccel2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcAccel2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyCurving1:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcCurving1(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcCurving1(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcCurving1(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyCurving2:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcCurving2(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcCurving2(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcCurving2(_objectID, _timeStamp);
        }
        break;

    case QSimulation::PropertyPosition2: return loadCalcPosition2(_objectID, _timeStamp);
    case QSimulation::PropertyPosition3: return loadCalcPosition3(_objectID, _timeStamp);

    case QSimulation::PropertyNone: break;
    case QSimulation::PropertyMass: break;
    case QSimulation::PropertyForce: break;
    case QSimulation::PropertySpinR: break;
    case QSimulation::PropertySpinG: break;
    case QSimulation::PropertySpinB: break;
    case QSimulation::PropertyAccelerationR: break;
    case QSimulation::PropertyAccelerationG: break;
    case QSimulation::PropertyAccelerationB: break;
    }
    return {false, QVector3D()};
}

/*!
 * \brief Calculate simulation, filling all object's histories
 * \param _stepCount Step count to calculate
 * \returns Success flag
 * \sa Universe1::Simulation::Simulation::createSimulation(const size_t)
 */
bool Universe1::Project::QSimulationNeutrino::createSimulation()
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
 * \brief Setter for simulation precision
 * \param _precision New simulation precision
 */
void Universe1::Project::QSimulationNeutrino::setPrecision(Precision _precision)
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
void Universe1::Project::QSimulationNeutrino::setUniverseConstant(
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
void Universe1::Project::QSimulationNeutrino::setMaximumStepTime(const double _value)
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
void Universe1::Project::QSimulationNeutrino::setMaximumCurveAngleDeg(const double _value)
{
    switch (m_precision)
    {
    case PrecisionFloat: m_simF.setMaximumCurveAngleDeg(_value); break;
    case PrecisionDouble: m_simD.setMaximumCurveAngleDeg(_value); break;
    case PrecisionLongDouble: m_simL.setMaximumCurveAngleDeg(_value); break;
    }
    emit physicsChanged();
}

/*!
 * \brief Initialize objects from given collection
 * \param _objects Collection of starting object's properties
 * \param _doEmit Flag if emit \c dataChanged() signal
 */
void Universe1::Project::QSimulationNeutrino::initializeFromObjects(
    const std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> &_objects, const bool _doEmit)
{
    switch (m_precision)
    {
    case PrecisionFloat:
        m_simF.initObjects().clear();
        m_simF.initObjects().reserve(_objects.size());
        for (const Universe1::Simulation::GravityNeutrino::NeutrinoObject<long double> &io : _objects)
            m_simF.initObjects().push_back(io.createCopy<float>());
        break;

    case PrecisionDouble:
        m_simD.initObjects().clear();
        m_simD.initObjects().reserve(_objects.size());
        for (const Universe1::Simulation::GravityNeutrino::NeutrinoObject<long double> &io : _objects)
            m_simD.initObjects().push_back(io.createCopy<double>());
        break;

    case PrecisionLongDouble:
        m_simL.initObjects().clear();
        m_simL.initObjects().reserve(_objects.size());
        for (const Universe1::Simulation::GravityNeutrino::NeutrinoObject<long double> &io : _objects)
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
bool Universe1::Project::QSimulationNeutrino::rebuildSimulation(
    const std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> &_objects)
{
    initializeFromObjects(_objects, false);
    return createSimulation();
}
