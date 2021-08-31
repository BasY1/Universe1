/*!
 * \file qt/project/qsimulation.cpp
 * \author Michal Steller
 * \brief The QT Simulation abstract class implementation
 */

#include "qsimulation.h"

Universe1::Project::QSimulation::QSimulation(const QString &ID, QObject *parent)
    : QObject(parent)
    , m_ID(ID)
    , m_calculationStepCount(100)
{
}

void Universe1::Project::QSimulation::setName(const QString &name)
{
    m_name = name;
}

void Universe1::Project::QSimulation::setDescription(const QString &description)
{
    m_description = description;
}

/*!
 * \brief Tool function converts flags to list
 * \tparam FLAGS_TYPE Flags type
 * \tparam ENUM_TYPE Enum type
 * \param _props Flags
 * \returns List of checked flags
 */
template <typename FLAGS_TYPE, typename ENUM_TYPE>
inline std::list<ENUM_TYPE> parseFlags(const FLAGS_TYPE _props)
{
    const QMetaEnum me = QMetaEnum::fromType<FLAGS_TYPE>();
    std::list<ENUM_TYPE> result;
    for (int i = 0; i < me.keyCount(); ++i)
    {
        const int v = me.value(i);
        if (v != 0)
        {
            const ENUM_TYPE vv = static_cast<ENUM_TYPE>(v);
            if (_props.testFlag(vv))
                result.push_back(vv);
        }
    }

    return result;
}

/*!
 * \brief Tool to string function for \c ElementProperty
 * \param _value Value to parse
 * \returns \c ElementProperty as \c QString
 */
QString Universe1::Project::QSimulation::getElementPropertyName(const ElementProperty _value)
{
    const QMetaEnum me = QMetaEnum::fromType<ElementProperties>();
    return me.valueToKey(_value);
}

/*!
 * \brief Tool function converts flags to list
 * \param _value Flags
 * \returns List of checked flags
 */
std::list<Universe1::Project::QSimulation::ElementProperty>
Universe1::Project::QSimulation::parseElementProperties(const ElementProperties _value)
{
    return parseFlags<ElementProperties, ElementProperty>(_value);
}

/*!
 * \brief Setter for speed of the universe constant
 * \param _value New speed of the universe constant
 */
void Universe1::Project::QSimulation::setConstantUniverseVelocity(double _value)
{
    setUniverseConstant(Simulation::Const_UniverseVelocity, _value);
}

/*!
 * \brief Setter for gravitational constant
 * \param _value New gravitational constant
 */
void Universe1::Project::QSimulation::setConstantGravityConstant(double _value)
{
    setUniverseConstant(Simulation::Const_GravityConstant, _value);
}

/*!
 * \brief Setter for element radius
 * \param _value New element radius
 */
void Universe1::Project::QSimulation::setConstantElementRadius(double _value)
{
    setUniverseConstant(Simulation::Const_ElementRadius, _value);
}

/*!
 * \brief Setter for calculation step count
 * \param _value New calculation step count
 */
void Universe1::Project::QSimulation::setCalculationStepCount(int _value)
{
    m_calculationStepCount = std::max(2, _value);
    emit physicsChanged();
}
