/*!
 * \file qt/qsimulationnewtoncurrent.cpp
 * \author Michal Steller
 * \brief Class implementation - QT Simulation for newton \b current physics
 */

#include "qsimulationnewtoncurrent.h"

Universe1::QSimulationNewtonCurrent::QSimulationNewtonCurrent(const QString &ID, QObject *parent)
    : QSimulation(ID, parent)
    , m_precision(PrecisionFloat)
{
}

Universe1::QSimulation::SimulationType Universe1::QSimulationNewtonCurrent::simulationType() const
{
    return QSimulation::SimulationNewtonCurrent;
}

Universe1::QSimulation::Precision Universe1::QSimulationNewtonCurrent::precision() const
{
    return m_precision;
}

bool Universe1::QSimulationNewtonCurrent::usesHistory() const
{
    return false;
}

bool Universe1::QSimulationNewtonCurrent::usesRadius() const
{
    return false;
}

const std::vector<Universe1::Simulation::ConstantName> &
Universe1::QSimulationNewtonCurrent::supportedPhysicsConstants() const
{
    static const std::vector<Universe1::Simulation::ConstantName> supported = {
        Universe1::Simulation::Const_GravityConstant};
    return supported;
}

const std::vector<Universe1::QSimulation::ElementProperty> &
Universe1::QSimulationNewtonCurrent::supportedElementProperties() const
{
    static const std::vector<ElementProperty> supported = {PropertyPosition, PropertyVelocity, PropertyForce};
    return supported;
}

size_t Universe1::QSimulationNewtonCurrent::objectCountCalc() const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.objects().size();
    case PrecisionDouble: return m_simD.objects().size();
    case PrecisionLongDouble: return m_simL.objects().size();
    }
    return 0U;
}

size_t Universe1::QSimulationNewtonCurrent::lastInitObjectID() const
{
    switch (m_precision)
    {
    case PrecisionFloat: return m_simF.lastInitObjectID();
    case PrecisionDouble: return m_simD.lastInitObjectID();
    case PrecisionLongDouble: return m_simL.lastInitObjectID();
    }
    return 0U;
}

void Universe1::QSimulationNewtonCurrent::loadInitObjectIDs(std::vector<size_t> &_out) const
{
    switch (m_precision)
    {
    case PrecisionFloat: m_simF.loadInitObjectIDs(_out); break;
    case PrecisionDouble: m_simD.loadInitObjectIDs(_out); break;
    case PrecisionLongDouble: m_simL.loadInitObjectIDs(_out); break;
    }
}

bool Universe1::QSimulationNewtonCurrent::loadInitPath(std::vector<std::pair<double, QVector3D>> &_out,
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

bool Universe1::QSimulationNewtonCurrent::loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out,
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

std::pair<bool, QVector3D> Universe1::QSimulationNewtonCurrent::loadInitProperty(const ElementProperty _property,
                                                                                 const size_t _objectID,
                                                                                 const double _timeStamp) const
{
    switch (_property)
    {
    case QSimulation::PropertyPosition:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitPosition(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitPosition(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitPosition(_objectID, _timeStamp);
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
    case QSimulation::PropertyForce:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadInitAccel(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadInitAccel(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadInitAccel(_objectID, _timeStamp);
        }
        break;

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

std::pair<bool, QVector3D> Universe1::QSimulationNewtonCurrent::loadCalcProperty(const ElementProperty _property,
                                                                                 const size_t _objectID,
                                                                                 const double _timeStamp) const
{
    switch (_property)
    {
    case QSimulation::PropertyPosition:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcPosition(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcPosition(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcPosition(_objectID, _timeStamp);
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
    case QSimulation::PropertyForce:
        switch (m_precision)
        {
        case PrecisionFloat: return m_simF.loadCalcAccel(_objectID, _timeStamp);
        case PrecisionDouble: return m_simD.loadCalcAccel(_objectID, _timeStamp);
        case PrecisionLongDouble: return m_simL.loadCalcAccel(_objectID, _timeStamp);
        }
        break;

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

bool Universe1::QSimulationNewtonCurrent::createSimulation(int _stepCount)
{
    if (_stepCount < 1)
        return false;
    bool result = false;
    switch (m_precision)
    {
    case PrecisionFloat: result = m_simF.createSimulation(_stepCount); break;
    case PrecisionDouble: result = m_simD.createSimulation(_stepCount); break;
    case PrecisionLongDouble: result = m_simL.createSimulation(_stepCount); break;
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
void initObj(const std::vector<Universe1::QSimulationNewtonCurrent::InitObject> &_objects,
             Universe1::Simulation::GravityNewton::SimulationNewtonCurrent<T> &_sim)
{
    std::vector<std::tuple<T, Universe1::Math::Vec3<T>, Universe1::Math::Vec3<T>>> tmp(_objects.size());
    size_t idx = 0;
    for (const Universe1::QSimulationNewtonCurrent::InitObject &io : _objects)
    {
        std::get<0>(tmp.at(idx)) = io.mass;
        std::get<1>(tmp.at(idx)) = io.position.converted<T>();
        std::get<2>(tmp.at(idx)) = io.velocity.converted<T>();
        ++idx;
    }
    _sim.initializeObjects(tmp);
}

void Universe1::QSimulationNewtonCurrent::initializeFromObjects(const std::vector<InitObject> &_objects)
{
    switch (m_precision)
    {
    case PrecisionFloat: initObj(_objects, m_simF); break;
    case PrecisionDouble: initObj(_objects, m_simD); break;
    case PrecisionLongDouble: initObj(_objects, m_simL); break;
    }
    emit dataChanged();
}

void Universe1::QSimulationNewtonCurrent::setPrecision(Precision _precision)
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
