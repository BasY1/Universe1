/*!
 * \file qt/project/qsimulation.h
 * \author Michal Steller
 * \brief The QT Simulation abstract class declaration
 */

#ifndef UNIVERSE1_PROJECT_QSIMULATION_H
#define UNIVERSE1_PROJECT_QSIMULATION_H

#include "../../simulation/simulation.h"

#include <QMetaEnum>
#include <QObject>
#include <set>

namespace Universe1 {
namespace Project {

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
        PropertyNone = 0b00000000000000000000000000000000,   //!< Helper zero value for flags
        PropertyMass = 0b00000000000000000000000000000001,   //!< Element's mass
        PropertyForce = 0b00000000000000000000000000000010,  //!< Element's gravitational force resp. acceleration

        PropertyVelocity1 = 0b00000000000000000000000000000100,  //!< Velocity within generation 1
        PropertyVelocity2 = 0b00000000000000000000000000001000,  //!< Velocity within generation 2
        PropertyVelocity3 = 0b00000000000000000000000000010000,  //!< Velocity within generation 3
        PropertyVelocity = PropertyVelocity1,                    //!< Velocity (Non-generation elements)

        PropertySpin1 = 0b00000000000000000000000000100000,  //!< Spin angular velocity within generation 1
        PropertySpin2 = 0b00000000000000000000000001000000,  //!< Spin angular velocity within generation 2
        PropertySpin3 = 0b00000000000000000000000010000000,  //!< Spin angular velocity within generation 3
        PropertySpinR = 0b00000000000000000000000100000000,  //!< Color angular velocity - red spin
        PropertySpinG = 0b00000000000000000000001000000000,  //!< Color angular velocity - green spin
        PropertySpinB = 0b00000000000000000000010000000000,  //!< Color angular velocity - blue spin

        PropertyAcceleration1 = 0b00000000000000000000100000000000,  //!< Acceleration acting on generation 1 move
        PropertyAcceleration2 = 0b00000000000000000001000000000000,  //!< Acceleration acting on generation 2 move
        PropertyAccelerationR = 0b00000000000000000010000000000000,  //!< Acceleration acting on red move
        PropertyAccelerationG = 0b00000000000000000100000000000000,  //!< Acceleration acting on green move
        PropertyAccelerationB = 0b00000000000000001000000000000000,  //!< Acceleration acting on blue move
        PropertyAcceleration = PropertyAcceleration1,                //!< Acceleration (Non-generation elements)

        PropertyCurving1 = 0b00000000000000100000000000000000,  // Arm for curving of generation 1 velocity
        PropertyCurving2 = 0b00000000000001000000000000000000,  // Arm for curving of generation 2 velocity

        PropertyPosition2 = 0b00000000000010000000000000000000,  // Generation 2 sphere center
        PropertyPosition3 = 0b00000000000100000000000000000000,  // Generation 3 sphere center
    };
    Q_DECLARE_FLAGS(ElementProperties, ElementProperty)
    Q_FLAG(ElementProperties)

    static std::list<ElementProperty> parseElementProperties(const ElementProperties _value);
    static QString getElementPropertyName(const ElementProperty _value);
    static uint getElementPropertyGeneration(const ElementProperty _value);

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

    inline const QString &ID() const;
    inline QString name() const;
    inline QString description() const;
    inline int calculationStepCount() const;

    /*!
     * \brief Getter for simulation type
     * \returns The simulation type
     */
    virtual SimulationType simulationType() const = 0;

    inline QString simulationTypeName() const;

    /*!
     * \brief Getter for simulation precision
     * \returns The simulation precision
     */
    virtual Precision precision() const = 0;

    /*!
     * \brief Getter for using history flag (Simulation uses objects history position for forces calculations)
     * \returns Using history flag
     * \details
     * | Value    | Simulation type                                  |
     * | :------- | :----------------------------------------------- |
     * | \c true  | Current time position based simulation           |
     * | \c false | History time - information wave based simulation |
     */
    virtual bool usesHistory() const = 0;

    /*!
     * \brief Getter for using generation flag elements can be in second and third generation
     * \returns Using generations flag
     */
    virtual bool usesGenerations() const = 0;

    /*!
     * \brief Load object historical positions from where wave hits event positions
     * \param _out Output buffer
     * \param _eventTimeStamp Time-stamp of event
     * \param _eventPosition Event location
     * \returns Success flag
     */
    virtual bool loadEventSource(std::vector<std::pair<double, QVector3D>> &_out,
                                 const double _eventTimeStamp,
                                 const QVector3D &_eventPosition) const = 0;

    /*!
     * \brief Getter for using element radius flag (\c true - Elements are spheres with radius,
     *        or \c false - Elements are singularities)
     * \returns Using element radius flag
     * | Value    | Simulation type                            |
     * | :------- | :----------------------------------------- |
     * | \c true  | Elements are spherical objects with radius |
     * | \c false | Elements are singularity objects           |
     */
    virtual bool usesRadius() const = 0;

    /*!
     * \brief Getter for collection of supported/required physics constants
     * \returns Supported physics constants
     */
    virtual const std::set<Universe1::Simulation::ConstantName> &supportedPhysicsConstants() const = 0;

    /*!
     * \brief Getter for value of universe constant
     * \param _name Universe constant name
     * \returns Value of universe constant
     */
    virtual double getPhysicsConstant(const Universe1::Simulation::ConstantName &_name) const = 0;

    inline double getConstantUniverseVelocity() const;
    inline double getConstantGravityConstant() const;
    inline double getConstantElementRadius() const;

    /*!
     * \brief Getter for maximum calculation step time duration
     * \returns Maximum calculation step time duration
     */
    virtual double getMaximumStepTime() const = 0;

    /*!
     * \brief Getter for maximum calculation step curving angle
     * \returns Maximum calculation step curving angle [degrees]
     */
    virtual double getMaximumCurveAngleDeg() const = 0;

    /*!
     * \brief Getter for collection of supported element properties
     * \returns Supported element properties
     */
    virtual ElementProperties supportedElementProperties() const = 0;

    /*!
     * \brief Getter for count of object under initialization
     * \returns Count of object under initialization
     */
    virtual size_t objectCountInit() const = 0;

    /*!
     * \brief Getter for count of object under calculation
     * \returns Count of object under calculation
     */
    virtual size_t objectCountCalc() const = 0;

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
     * \brief Fill output vector with initialization object time-stamps and positions of generation 2
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    virtual bool loadInitPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                               const size_t _objectID) const = 0;

    /*!
     * \brief Fill output vector with calculation object time-stamps and positions of generation 2
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    virtual bool loadCalcPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                               const size_t _objectID) const = 0;

    /*!
     * \brief Fill output vector with initialization object time-stamps and positions of generation 3
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    virtual bool loadInitPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                               const size_t _objectID) const = 0;

    /*!
     * \brief Fill output vector with calculation object time-stamps and positions of generation 3
     * \param _out Output vector
     * \param _objectID Object's index
     * \returns \c true if success
     */
    virtual bool loadCalcPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                               const size_t _objectID) const = 0;

    /*!
     * \brief Getter for initialization object position at time-stamp
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D> loadInitPosition(const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Getter for calculation object position at time-stamp
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D> loadCalcPosition(const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Getter for initialization object generation 2 position at time-stamp
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D> loadInitPosition2(const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Getter for calculation object generation 2 position at time-stamp
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D> loadCalcPosition2(const size_t _objectID, const double _timeStamp) const = 0;
    /*!
     * \brief Getter for initialization object generation 3 position at time-stamp
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D> loadInitPosition3(const size_t _objectID, const double _timeStamp) const = 0;

    /*!
     * \brief Getter for calculation object generation 3 position at time-stamp
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is position (as \c QVector3D)
     */
    virtual std::pair<bool, QVector3D> loadCalcPosition3(const size_t _objectID, const double _timeStamp) const = 0;

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
     * \returns Success flag
     * \sa Universe1::Simulation::Simulation::createSimulation(const size_t)
     */
    virtual bool createSimulation() = 0;

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

    /*!
     * \brief Setter for universe constant
     * \param _constantName New constant name
     * \param _value New constant value
     */
    virtual void setUniverseConstant(const Universe1::Simulation::ConstantName _constantName, const double _value) = 0;

    void setConstantUniverseVelocity(double _value);
    void setConstantGravityConstant(double _value);
    void setConstantElementRadius(double _value);
    void setCalculationStepCount(int _value);

    /*!
     * \brief Setter for maximum calculation step time duration
     * \param _value New value
     */
    virtual void setMaximumStepTime(double _value) = 0;

    /*!
     * \brief Setter for maximum calculation step curving angle
     * \param _value New angle value [degrees]
     */
    virtual void setMaximumCurveAngleDeg(double _value) = 0;

 signals:
    void dataChanged();     //!< Simulation data was changed
    void physicsChanged();  //!< Simulation physics constants was changed

 protected:
    const QString m_ID;          //!< Simulation ID
    int m_calculationStepCount;  //!< Calculation step count
    QString m_name;              //!< Simulation name
    QString m_description;       //!< Simulation description
};

Q_DECLARE_OPERATORS_FOR_FLAGS(QSimulation::ElementProperties)

/*!
 * \brief Getter simulation ID
 * \returns Simulation ID
 */
inline const QString &QSimulation::ID() const
{
    return m_ID;
}

/*!
 * \brief Getter simulation name
 * \returns Simulation name
 */
inline QString QSimulation::name() const
{
    return m_name;
}

/*!
 * \brief Getter simulation description
 * \returns Simulation description
 */
inline QString QSimulation::description() const
{
    return m_description;
}

/*!
 * \brief Tool function - simulation type name
 * \returns Name of simulation type
 */
inline QString QSimulation::simulationTypeName() const
{
    const QMetaEnum me = QMetaEnum::fromType<SimulationType>();
    return me.valueToKey(simulationType());
}

/*!
 * \brief Getter for calculation step count
 * \returns Calculation step count
 */
inline int QSimulation::calculationStepCount() const
{
    return m_calculationStepCount;
}

/*!
 * \brief Getter for speed of the universe constant
 * \returns Speed of the universe constant
 */
inline double QSimulation::getConstantUniverseVelocity() const
{
    return getPhysicsConstant(Simulation::Const_UniverseVelocity);
}

/*!
 * \brief Getter for gravitational constant
 * \returns Gravitational constant
 */
inline double QSimulation::getConstantGravityConstant() const
{
    return getPhysicsConstant(Simulation::Const_GravityConstant);
}

/*!
 * \brief Getter for element radius
 * \returns Element radius
 */
inline double QSimulation::getConstantElementRadius() const
{
    return getPhysicsConstant(Simulation::Const_ElementRadius);
}

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

}  // namespace Project
}  // namespace Universe1

#endif  // UNIVERSE1_PROJECT_QSIMULATION_H
