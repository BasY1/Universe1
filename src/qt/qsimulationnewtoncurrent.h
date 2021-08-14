/*!
 * \file qt/qsimulationnewtoncurrent.h
 * \author Michal Steller
 * \brief Class declaration - QT Simulation for newton \b current physics
 */

#ifndef UNIVERSE1_QSIMULATIONNEWTONCURRENT_H
#define UNIVERSE1_QSIMULATIONNEWTONCURRENT_H

#include "qsimulation.h"

#include "../simulation/newton/newtonsimulation.h"

#include <QObject>

/*!
 * \brief The QT Simulation abstract class
 */
class QSimulationNewtonCurrent : public QSimulation
{
    Q_OBJECT
 public:

    /*!
     * \brief Constructor
     * \param _ID Simulation ID
     * \param _parent Parent \c QObject
     */
    QSimulationNewtonCurrent(const QString &_ID, QObject *_parent = nullptr);

    /*!
     * \brief Default destructor
     */
    ~QSimulationNewtonCurrent() = default;

    /*!
     * \brief Getter for simulation type (\a QSimulation::SimulationNewtonCurrent)
     * \returns The simulation type (\a QSimulation::SimulationNewtonCurrent)
     */
    SimulationType simulationType() const;

    /*!
     * \brief Getter for simulation precision
     * \returns The simulation precision
     */
    Precision precision() const;

    /*!
     * \brief Getter for using history flag (\c false)
     * \returns Using history flag (\c false)
     */
    bool usesHistory() const;

    /*!
     * \brief Getter for using element radius flag (\c false - Elements are singularities)
     * \returns Using element radius flag (\c false - Elements are singularities)
     */
    bool usesRadius() const;

    /*!
     * \brief Getter for collection of supported/required physics constants
     * \returns Supported physics constants
     */
    const std::vector<Universe1::Simulation::ConstantName> &supportedPhysicsConstants() const;

    /*!
     * \brief Getter for collection of supported element properties
     * \returns Supported element properties
     */
    const std::vector<ElementProperty> &supportedElementProperties() const;

    /*!
     * \brief Getter for count of object under calculation
     * \returns Count of object under calculation
     */
    size_t objectCountCalc() const;

    /*!
     * \brief Returns object ID that is last in initialization list
     * \returns Last initialization object ID
     */
    size_t lastInitObjectID() const;

    /*!
     * \brief Fill output vector with collection of object IDs under initialization
     * \param _out Output vector
     */
    void loadInitObjectIDs(std::vector<size_t> &_out) const;

    /*!
     * \brief Fill output vector with initialization object time-stamps and positions
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    bool loadInitPath(std::vector<std::pair<double, QVector3D>> &_out, const size_t _objectID) const;

    /*!
     * \brief Fill output vector with calculation object time-stamps and positions
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    bool loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out, const size_t _objectID) const;

    /*!
     * \brief Universal getter for initialization object property
     * \param _property Property to load
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
     */
    std::pair<bool, QVector3D>
    loadInitProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Universal getter for calculation object property
     * \param _property Property to load
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
     */
    std::pair<bool, QVector3D>
    loadCalcProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Calculate simulation, filling all object's histories
     * \param _stepCount Step count to calculate
     * \returns Success flag
     * \sa Universe1::Simulation::Simulation::createSimulation(const size_t)
     */
    bool createSimulation(int _stepCount);

    /*!
     * \brief Helper structure, holds object's starting properties in \c long \c double precision
     */
    struct InitObject
    {
        long double mass;                             //!< Object's mass
        Universe1::Math::Vec3<long double> position;  //!< Object's starting position
        Universe1::Math::Vec3<long double> velocity;  //!< Object's starting velocity
    };

    /*!
     * \brief Initialize objects from given collection
     * \param _objects Collection of starting object's properties
     */
    void initializeFromObjects(const std::vector<InitObject> &_objects);

 public slots:
    /*!
     * \brief Setter for simulation precision
     * \param _precision New simulation precision
     */
    void setPrecision(Precision _precision);

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

#endif  // UNIVERSE1_QSIMULATIONNEWTONCURRENT_H
