/*!
 * \file qt/qsimulation.h
 * \author Michal Steller
 * \brief The QT Simulation abstract class declaration
 */

#ifndef UNIVERSE1_QSIMULATION_H
#define UNIVERSE1_QSIMULATION_H

#include "../simulation/simulation.h"

#include <QObject>

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
     * \return The simulation type
     */
    virtual SimulationType simulationType() const = 0;

    /*!
     * \brief Getter for simulation precision
     * \return The simulation precision
     */
    virtual Precision precision() const = 0;

    /*!
     * \brief Getter for using history flag (Simulation uses objects history position for forces calculations)
     * \return Using history flag
     */
    virtual bool usesHistory() const = 0;

    /*!
     * \brief Getter for using element radius flag (\c true - Elements are spheres with radius,
     *        or \c false - Elements are singularities)
     * \return Using element radius flag
     */
    virtual bool usesRadius() const = 0;

    /*!
     * \brief Getter for collection of supported/required physics constants
     * \return Supported physics constants
     */
    virtual const std::vector<Universe1::Simulation::ConstantName> &supportedPhysicsConstants() const = 0;

    /*!
     * \brief Getter for collection of supported element properties
     * \return Supported element properties
     */
    virtual const std::vector<ElementProperty> &supportedElementProperties() const = 0;

    /*!
     * \brief Universal getter for object property
     * \param _property Property to load
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \return Pair, where \c first item is success flag, and \c second item is property value (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D>
    getObjectProperty(const ElementProperty _property, const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Getter simulation ID
     * \return Simulation ID
     */
    const QString &ID() const;

    /*!
     * \brief Getter simulation name
     * \return Simulation name
     */
    QString name() const;

    /*!
     * \brief Getter simulation description
     * \return Simulation description
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
     * \brief Calculate simulation, filling all object's histories
     */
    virtual void calculate() = 0;

 protected:
    const QString m_ID;     //!< Simulation ID
    QString m_name;         //!< Simulation name
    QString m_description;  //!< Simulation description
};

/*!
 * \brief Tool template function for detecting QSimulation::Precision literal from template parameter
 * \tparam T Template floating point type
 * \return Detected precision enumeration literal
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

#endif  // UNIVERSE1_QSIMULATION_H
