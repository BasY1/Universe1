/*!
 * \file qt/project/qsimulation.cpp
 * \author Michal Steller
 * \brief The QT Simulation abstract class implementation
 */

#include "qsimulation.h"

Universe1::Project::QSimulation::QSimulation(const QString &ID, QObject *parent)
    : QObject(parent)
    , m_ID(ID)
{
}

const QString &Universe1::Project::QSimulation::ID() const
{
    return m_ID;
}

QString Universe1::Project::QSimulation::name() const
{
    return m_name;
}

QString Universe1::Project::QSimulation::description() const
{
    return m_description;
}

void Universe1::Project::QSimulation::setName(const QString &name)
{
    m_name = name;
}

void Universe1::Project::QSimulation::setDescription(const QString &description)
{
    m_description = description;
}
