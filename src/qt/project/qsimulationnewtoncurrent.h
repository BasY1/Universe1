/*!
 * \file qt/project/qsimulationnewtoncurrent.h
 * \author Michal Steller
 * \brief Class declaration - QT Simulation for newton \b current physics
 */

#ifndef UNIVERSE1_PROJECT_QSIMULATIONNEWTONCURRENT_H
#define UNIVERSE1_PROJECT_QSIMULATIONNEWTONCURRENT_H

#include "qsimulation.h"

#include "../../simulation/newton/newtonsimulation.h"

#include <QObject>

namespace Universe1 {
namespace Project {

/*!
 * \brief The QT Simulation using Newton current method
 */
class QSimulationNewtonCurrent : public QSimulation
{
    Q_OBJECT
 public:

    QSimulationNewtonCurrent(const QString &_ID, QObject *_parent = nullptr);

    /*!
     * \brief Default destructor
     */
    ~QSimulationNewtonCurrent() = default;

    SimulationType simulationType() const override;
    Precision precision() const override;
    bool usesHistory() const override;
    bool usesRadius() const override;
    bool loadEventSource(std::vector<std::pair<double, QVector3D>> &_out,
                         const double _eventTimeStamp,
                         const QVector3D &_eventPosition) const override;

    const std::set<Universe1::Simulation::ConstantName> &supportedPhysicsConstants() const override;
    double getPhysicsConstant(const Universe1::Simulation::ConstantName &_name) const override;

    double getMaximumStepTime() const override;
    double getMaximumCurveAngleDeg() const override;

    ElementProperties supportedElementProperties() const override;

    size_t objectCountCalc() const override;
    size_t objectCountInit() const override;

    bool loadInitPath(std::vector<std::pair<double, QVector3D>> &_out, const size_t _objectID) const override;
    bool loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out, const size_t _objectID) const override;

    std::pair<bool, QVector3D> loadInitPosition(const size_t _objectID, const double _timeStamp) const override;
    std::pair<bool, QVector3D> loadCalcPosition(const size_t _objectID, const double _timeStamp) const override;

    std::pair<bool, QVector3D>
    loadInitProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const override;

    std::pair<bool, QVector3D>
    loadCalcProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const override;

    bool createSimulation() override;

    /*!
     * \brief Helper structure, holds object's starting properties in \c long \c double precision
     */
    struct InitObject
    {
        long double mass;                             //!< Object's mass
        Universe1::Math::Vec3<long double> position;  //!< Object's starting position
        Universe1::Math::Vec3<long double> velocity;  //!< Object's starting velocity
    };

    void initializeFromObjects(const std::vector<InitObject> &_objects);

    bool rebuildSimulation(const std::vector<InitObject> &_objects);

 public slots:
    void setPrecision(Precision _precision) override;
    void setUniverseConstant(const Universe1::Simulation::ConstantName _constantName, const double _value) override;
    void setMaximumStepTime(double _value) override;
    void setMaximumCurveAngleDeg(double _value) override;

 protected:
    Precision m_precision;  //!< Simulation precision

    Universe1::Simulation::GravityNewton::SimulationNewtonCurrent<float>
        m_simF;  //!< \c float \b 32bit precision simulation
    Universe1::Simulation::GravityNewton::SimulationNewtonCurrent<double>
        m_simD;  //!< \c double \b 64bit precision simulation
    Universe1::Simulation::GravityNewton::SimulationNewtonCurrent<long double>
        m_simL;  //!< \c long \c double \b 128bit precision simulation

    std::vector<InitObject> m_currentInitObjects;  //!< Collection of starting object's properties
};

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_QSIMULATIONNEWTONCURRENT_H
