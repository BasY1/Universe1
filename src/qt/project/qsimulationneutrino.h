/*!
 * \file qt/project/qsimulationneutrino.h
 * \author Michal Steller
 * \brief Class declaration - QT Simulation for neutrino - pure gravity physics
 */

#ifndef UNIVERSE1_PROJECT_QSIMULATIONNEUTRINO_H
#define UNIVERSE1_PROJECT_QSIMULATIONNEUTRINO_H

#include "qsimulation.h"

#include "../../simulation/neutrino/neutrinosimulation.h"

#include <QObject>

namespace Universe1 {
namespace Project {

/*!
 * \brief Neutrino Simulation QT extension
 */
class QSimulationNeutrino : public QSimulation
{
    Q_OBJECT
 public:
    QSimulationNeutrino(const QString &_ID, QObject *_parent = nullptr);

    /*!
     * \brief Default destructor
     */
    ~QSimulationNeutrino() = default;

    SimulationType simulationType() const override;
    Precision precision() const override;
    bool usesHistory() const override;
    bool usesGenerations() const override;
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
    bool loadInitPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                       const size_t _objectID) const override;
    bool loadCalcPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                       const size_t _objectID) const override;
    bool loadInitPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                       const size_t _objectID) const override;
    bool loadCalcPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                       const size_t _objectID) const override;

    std::pair<bool, QVector3D> loadInitPosition(const size_t _objectID, const double _timeStamp) const override;
    std::pair<bool, QVector3D> loadCalcPosition(const size_t _objectID, const double _timeStamp) const override;
    std::pair<bool, QVector3D> loadInitPosition2(const size_t _objectID, const double _timeStamp) const override;
    std::pair<bool, QVector3D> loadCalcPosition2(const size_t _objectID, const double _timeStamp) const override;
    std::pair<bool, QVector3D> loadInitPosition3(const size_t _objectID, const double _timeStamp) const override;
    std::pair<bool, QVector3D> loadCalcPosition3(const size_t _objectID, const double _timeStamp) const override;

    std::pair<bool, QVector3D>
    loadInitProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const override;

    std::pair<bool, QVector3D>
    loadCalcProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const override;

    bool createSimulation() override;

    void initializeFromObjects(const std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> &_objects,
                               const bool _doEmit = true);
    bool rebuildSimulation(const std::vector<Simulation::GravityNeutrino::NeutrinoObject<long double>> &_objects);

 public slots:
    void setPrecision(Precision _precision) override;
    void setUniverseConstant(const Universe1::Simulation::ConstantName _constantName, const double _value) override;
    void setMaximumStepTime(double _value) override;
    void setMaximumCurveAngleDeg(double _value) override;

 protected:
    Precision m_precision;  //!< Simulation precision

    Simulation::GravityNeutrino::SimulationNeutrino<float> m_simF;        //!< \c float \b 32bit precision
    Simulation::GravityNeutrino::SimulationNeutrino<double> m_simD;       //!< \c double \b 64bit precision
    Simulation::GravityNeutrino::SimulationNeutrino<long double> m_simL;  //!< \c long \c double \b 128bit precision
};

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_QSIMULATIONNEUTRINO_H
