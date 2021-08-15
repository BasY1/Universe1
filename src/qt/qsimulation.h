/*!
 * \file qt/qsimulation.h
 * \author Michal Steller
 * \brief The QT Simulation abstract class declaration
 */

#ifndef UNIVERSE1_QSIMULATION_H
#define UNIVERSE1_QSIMULATION_H

#include "../simulation/simulation.h"

#include <QObject>

namespace Universe1 {

/*!
 * \brief The QT Simulation abstract class
 */
class QSimulation : public QObject
{
    Q_OBJECT
 public:
    /*!
     * \brief Implemented simulation types
     */
    enum SimulationType
    {
        SimulationNewtonCurrent,  //!< Classic newton simulation, force point to mate object's current position
        SimulationNewtonByWave,   //!< Relativistic Newton simulation, force point to mate object's position in history
                                  //!< from where gravitational wave at speed of universe hits current object
    };
    Q_ENUM(SimulationType)

    /*!
     * \brief Supported precision enumeration
     */
    enum Precision
    {
        PrecisionFloat,      //!< \c float \b 32bit precision
        PrecisionDouble,     //!< \c double \b 64bit precision
        PrecisionLongDouble  //!< \c long \c double \b 128bit precision
    };
    Q_ENUM(Precision)

    /*!
     * \brief Supported element property names
     */
    enum ElementProperty
    {
        PropertyPosition,  //!< Element's position
        PropertyVelocity,  //!< Element's velocity

        PropertySpin,       //!< Element's master (gravity) spin
        PropertySpinRed,    //!< Element's red spin
        PropertySpinGreen,  //!< Element's green spin
        PropertySpinBlue,   //!< Element's blue spin

        PropertyForce,       //!< Element's gravitational force resp. acceleration
        PropertyForceRed,    //!< Element's red force
        PropertyForceGreen,  //!< Element's green force
        PropertyForceBlue,   //!< Element's blue force
    };
    Q_ENUM(ElementProperty)

    /*!
     * \brief Constructor
     * \param _ID Simulation ID
     * \param _parent Parent \c QObject
     */
    QSimulation(const QString &_ID, QObject *_parent = nullptr);

    /*!
     * \brief Default destructor
     */
    ~QSimulation() = default;

    /*!
     * \brief Getter for simulation type
     * \returns The simulation type
     */
    virtual SimulationType simulationType() const = 0;

    /*!
     * \brief Getter for simulation precision
     * \returns The simulation precision
     */
    virtual Precision precision() const = 0;

    /*!
     * \brief Getter for using history flag (Simulation uses objects history position for forces calculations)
     * \returns Using history flag
     */
    virtual bool usesHistory() const = 0;

    /*!
     * \brief Getter for using element radius flag (\c true - Elements are spheres with radius,
     *        or \c false - Elements are singularities)
     * \returns Using element radius flag
     */
    virtual bool usesRadius() const = 0;

    /*!
     * \brief Getter for collection of supported/required physics constants
     * \returns Supported physics constants
     */
    virtual const std::vector<Universe1::Simulation::ConstantName> &supportedPhysicsConstants() const = 0;

    /*!
     * \brief Getter for collection of supported element properties
     * \returns Supported element properties
     */
    virtual const std::vector<ElementProperty> &supportedElementProperties() const = 0;

    /*!
     * \brief Getter for count of object under calculation
     * \returns Count of object under calculation
     */
    virtual size_t objectCountCalc() const = 0;

    /*!
     * \brief Returns object ID that is last in initialization list
     * \returns Last initialization object ID
     */
    virtual size_t lastInitObjectID() const = 0;

    /*!
     * \brief Fill output vector with collection of object IDs under initialization
     * \param _out Output vector
     * \returns
     */
    virtual void loadInitObjectIDs(std::vector<size_t> &_out) const = 0;

    /*!
     * \brief Fill output vector with initialization object time-stamps and positions
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    virtual bool loadInitPath(std::vector<std::pair<double, QVector3D>> &_out, const size_t _objectID) const = 0;

    /*!
     * \brief Fill output vector with calculation object time-stamps and positions
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    virtual bool loadCalcPath(std::vector<std::pair<double, QVector3D>> &_out, const size_t _objectID) const = 0;

    /*!
     * \brief Universal getter for initialization object property
     * \param _property Property to load
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D>
    loadInitProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Universal getter for calculation object property
     * \param _property Property to load
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D>
    loadCalcProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Calculate simulation, filling all object's histories
     * \param _stepCount Step count to calculate
     * \returns Success flag
     * \sa Universe1::Simulation::Simulation::createSimulation(const size_t)
     */
    virtual bool createSimulation(int _stepCount) = 0;

    /*!
     * \brief Getter simulation ID
     * \returns Simulation ID
     */
    const QString &ID() const;

    /*!
     * \brief Getter simulation name
     * \returns Simulation name
     */
    QString name() const;

    /*!
     * \brief Getter simulation description
     * \returns Simulation description
     */
    QString description() const;

 public slots:
    /*!
     * \brief Setter for simulation name
     * \param _name New simulation name
     */
    void setName(const QString &_name);

    /*!
     * \brief Setter for simulation description
     * \param _description New simulation description
     */
    void setDescription(const QString &_description);

    /*!
     * \brief Setter for simulation precision
     * \param _precision New simulation precision
     */
    virtual void setPrecision(Precision _precision) = 0;

 signals:
    void dataChanged();  //!< Simulation data was changed

 protected:
    const QString m_ID;     //!< Simulation ID
    QString m_name;         //!< Simulation name
    QString m_description;  //!< Simulation description
};

/*!
 * \brief Tool template function for detecting QSimulation::Precision literal from template parameter
 * \tparam T Template floating point type
 * \returns Detected precision enumeration literal
 */
template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
inline QSimulation::Precision detectPrecision();

#ifndef DOXYGEN_SKIP

template <>
inline QSimulation::Precision detectPrecision<float>()
{
    return QSimulation::PrecisionFloat;
}

template <>
inline QSimulation::Precision detectPrecision<double>()
{
    return QSimulation::PrecisionDouble;
}
template <>

inline QSimulation::Precision detectPrecision<long double>()
{
    return QSimulation::PrecisionLongDouble;
}

#endif  // DOXYGEN_SKIP

}  // namespace Universe1

#endif  // UNIVERSE1_QSIMULATION_H
