/*!
 * \file qt/qsimulation.cpp
 * \author Michal Steller
 * \brief The QT Simulation abstract class implementation
 */

#include "qsimulation.h"

QSimulation::QSimulation(const QString &ID, QObject *parent)
    : QObject(parent)
    , m_ID(ID)
{
}

const QString &QSimulation::ID() const
{
    return m_ID;
}

QString QSimulation::name() const
{
    return m_name;
}

QString QSimulation::description() const
{
    return m_description;
}

void QSimulation::setName(const QString &name)
{
    m_name = name;
}

void QSimulation::setDescription(const QString &description)
{
    m_description = description;
}
