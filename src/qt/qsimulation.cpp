/*!
 * \file qt/qsimulation.cpp
 * \author Michal Steller
 * \brief The QT Simulation abstract class implementation
 */

#include "qsimulation.h"

Universe1::QSimulation::QSimulation(const QString &ID, QObject *parent)
    : QObject(parent)
    , m_ID(ID)
{
}

const QString &Universe1::QSimulation::ID() const
{
    return m_ID;
}

QString Universe1::QSimulation::name() const
{
    return m_name;
}

QString Universe1::QSimulation::description() const
{
    return m_description;
}

void Universe1::QSimulation::setName(const QString &name)
{
    m_name = name;
}

void Universe1::QSimulation::setDescription(const QString &description)
{
    m_description = description;
}
