/*!
 * \file src/Math/physicsnewton.h
 * \brief Newtonian physics simulation processor
 */

#ifndef MATH_PHYSICSNEWTON_H
#define MATH_PHYSICSNEWTON_H

#include "orientation.h"
#include "material.h"

#include <fstream>
#include <random>

namespace U1 {
namespace Math {

/*!
 * \brief Newtonian physics simulation processor
 * \tparam T Template floating point type
 */
template <typename T>
class PhysicsNewton
{
 public:
    size_t dataHash = 0UL;           //!< Simulation data hash value
    size_t countObjects = 0UL;       //!< Number of objects in the simulation
    size_t countSteps = 0UL;         //!< Number of simulation steps
    T timeStep = T(0);               //!< Time step duration
    T gravitationalConstant = T(0);  //!< Newton's gravitational constant
    T electrostaticConstant = T(0);  //!< Coulomb's electrostatic constant

    T massMinimum = T(0);  //!< Minimum object mass
    T massMaximum = T(0);  //!< Maximum object mass
    T massTotal = T(0);    //!< Total system mass

    T chargeMinimum = T(0);  //!< Minimum object charge
    T chargeMaximum = T(0);  //!< Maximum object charge

    T velocityMinimum = T(0);  //!< Minimum velocity magnitude in the simulation
    T velocityMaximum = T(0);  //!< Maximum velocity magnitude in the simulation

    T accelerationMinimum = T(0);  //!< Minimum acceleration magnitude in the simulation
    T accelerationMaximum = T(0);  //!< Maximum acceleration magnitude in the simulation

    T *mass = nullptr;                //!< Object masses
    T *charge = nullptr;              //!< Object charges
    Vec3<T> *position = nullptr;      //!< Object positions (all steps)
    Vec3<T> *velocity = nullptr;      //!< Object velocities (all steps)
    Vec3<T> *acceleration = nullptr;  //!< Object accelerations (all steps)

    PhysicsNewton() = default;  //!< Default constructor
    /*!
     * \brief Constructor
     * \param _fileName File with data
     */
    PhysicsNewton(const std::string &_fileName);

    ~PhysicsNewton();  //!< Destructor

    /*!
     * \brief Save simulation data into file
     * \param _fileName File name
     * \return Success flag
     */
    bool save(const std::string &_fileName) const;

    /*!
     * \brief Return last calculated time step
     * \return Last calculated time step
     */
    inline T lastTimeStep() const
    {
        return timeStep * T(countSteps > 0UL ? (countSteps - 1UL) : countSteps);
    }

    /*!
     * \brief Build simulation Newtonian gravity forces and Coulomb electrostatic forces
     * \param _dataHash Simulation data hash value
     * \param _countObjects Number of objects in the simulation
     * \param _countSteps Number of simulation steps
     * \param _mass Object masses
     * \param _charge Object charges
     * \param _position Object positions for initial step
     * \param _velocity Object velocities for initial step
     * \param _massTotal Total system mass
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Newton's gravitational constant
     * \param _electrostaticConstant Coulomb's electrostatic constant
     * \return Success flag
     */
    bool build(const size_t _dataHash,
               const size_t _countObjects,
               const size_t _countSteps,
               const T *_mass,
               const T *_charge,
               const Vec3<T> *_position,
               const Vec3<T> *_velocity,
               const T _massTotal,
               const T _timeStep,
               const T _gravitationalConstant,
               const T _electrostaticConstant);

    /*!
     * \brief Build simulation Newtonian gravity forces
     * \param _dataHash Simulation data hash value
     * \param _countObjects Number of objects in the simulation
     * \param _countSteps Number of simulation steps
     * \param _mass Object masses
     * \param _position Object positions for initial step
     * \param _velocity Object velocities for initial step
     * \param _massTotal Total system mass
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Newton's gravitational constant
     * \return Success flag
     */
    bool build(const size_t _dataHash,
               const size_t _countObjects,
               const size_t _countSteps,
               const T *_mass,
               const Vec3<T> *_position,
               const Vec3<T> *_velocity,
               const T _massTotal,
               const T _timeStep,
               const T _gravitationalConstant);

    /*!
     * \brief Build simulation Newtonian gravity forces and Coulomb electrostatic forces using Runge-Kutta
     * \param _dataHash Simulation data hash value
     * \param _countObjects Number of objects in the simulation
     * \param _countSteps Number of simulation steps
     * \param _mass Object masses
     * \param _charge Object charges
     * \param _position Object positions for initial step
     * \param _velocity Object velocities for initial step
     * \param _massTotal Total system mass
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Newton's gravitational constant
     * \param _electrostaticConstant Coulomb's electrostatic constant
     * \return Success flag
     */
    bool buildRK(const size_t _dataHash,
                 const size_t _countObjects,
                 const size_t _countSteps,
                 const T *_mass,
                 const T *_charge,
                 const Vec3<T> *_position,
                 const Vec3<T> *_velocity,
                 const T _massTotal,
                 const T _timeStep,
                 const T _gravitationalConstant,
                 const T _electrostaticConstant);

    /*!
     * \brief Build simulation Newtonian gravity forces using Runge-Kutta
     * \param _dataHash Simulation data hash value
     * \param _countObjects Number of objects in the simulation
     * \param _countSteps Number of simulation steps
     * \param _mass Object masses
     * \param _position Object positions for initial step
     * \param _velocity Object velocities for initial step
     * \param _massTotal Total system mass
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Newton's gravitational constant
     * \return Success flag
     */
    bool buildRK(const size_t _dataHash,
                 const size_t _countObjects,
                 const size_t _countSteps,
                 const T *_mass,
                 const Vec3<T> *_position,
                 const Vec3<T> *_velocity,
                 const T _massTotal,
                 const T _timeStep,
                 const T _gravitationalConstant);

 protected:
    /*!
     * \brief Calculate new positions and velocities in given step
     * \param _step Step
     * \param _timeStep2 0.5*time-step^2
     * \param _pool Multi-thread indices
     */
    void buildStep(const size_t _step, const T _timeStep2, const std::vector<std::pair<size_t, size_t>> &_pool);

    /*!
     * \brief Calculate object acceleration
     * \param _i Object index
     * \param _countObjects Number of objects
     * \param _gravitationalConstant Newton's gravitational constant
     * \param _objectMass Object masses
     * \param _objectPosition Object positions
     * \return Object acceleration
     */
    static Vec3<T> calcAccel(const size_t _i,
                             const size_t _countObjects,
                             const T _gravitationalConstant,
                             const T *_objectMass,
                             const Vec3<T> *_objectPosition);

    /*!
     * \brief Calculate object acceleration
     * \param _i Object index
     * \param _countObjects Number of objects
     * \param _gravitationalConstant Newton's gravitational constant
     * \param _electrostaticConstant Coulomb's electrostatic constant
     * \param _objectMass Object masses
     * \param _objectCharge Object charges
     * \param _objectPosition Object positions
     * \return Object acceleration
     */
    static Vec3<T> calcAccel(const size_t _i,
                             const size_t _countObjects,
                             const T _gravitationalConstant,
                             const T _electrostaticConstant,
                             const T *_objectMass,
                             const T *_objectCharge,
                             const Vec3<T> *_objectPosition);

    /*!
     * \brief Calculate acceleration using Runge-Kutta method
     * \param _i Object ID
     * \param _countObjects Number of objects
     * \param _timeDelta Time step
     * \param _gravitationalConstant Newton's gravitational constant
     * \param _electrostaticConstant Coulomb's electrostatic constant
     * \param _objectMass Object mass
     * \param _objectCharge Object charge
     * \param _objectPosition Object positions
     * \param _objectVelocity Object velocities
     * \return Acceleration of object with given ID
     */
    static Vec3<T> calcAccelRK(const size_t _i,
                               const size_t _countObjects,
                               const T _timeDelta,
                               const T _gravitationalConstant,
                               const T _electrostaticConstant,
                               const T *_objectMass,
                               const T *_objectCharge,
                               const Vec3<T> *_objectPosition,
                               const Vec3<T> *_objectVelocity);
    /*!
     * \brief Calculate acceleration using Runge-Kutta method
     * \param _i Object ID
     * \param _countObjects Number of objects
     * \param _timeDelta Time step
     * \param _gravitationalConstant Newton's gravitational constant
     * \param _objectMass Object mass
     * \param _objectPosition Object positions
     * \param _objectVelocity Object velocities
     * \return Acceleration of object with given ID
     */
    static Vec3<T> calcAccelRK(const size_t _i,
                               const size_t _countObjects,
                               const T _timeDelta,
                               const T _gravitationalConstant,
                               const T *_objectMass,
                               const Vec3<T> *_objectPosition,
                               const Vec3<T> *_objectVelocity);

    /*!
     * \brief Generate random position and masses for objects with total center of the mass at (0,0,0)
     * \param _outPosition Output positions
     * \param _outMass Output masses
     * \param _radiusX Area radius within the X axis
     * \param _radiusY Area radius within the Y axis
     * \param _radiusZ Area radius within the Z axis
     * \param _massMinimum Minimal object mass
     * \param _massMaximum Maximal object mass
     * \param _randomSeed Seed for random number generator
     * \param _countObjects Number of objects
     * \param _pool Multi-thread indices
     * \return Total system mass
     */
    static T generateRandomObjects(Vec3<T> *_outPosition,
                                   T *_outMass,
                                   const T _radiusX,
                                   const T _radiusY,
                                   const T _radiusZ,
                                   const T _massMinimum,
                                   const T _massMaximum,
                                   const size_t _randomSeed,
                                   const size_t _countObjects,
                                   const std::vector<std::pair<size_t, size_t>> &_pool);

    /*!
     * \brief Generate random charges
     * \param _outCharge Output charges
     * \param _chargeQuantum Electric charge quantum
     * \param _chargesMaximum Maximum number of electric quantum that object can hold
     * \param _randomSeed Seed for random number generator
     * \param _countObjects Number of objects
     * \param _pool Multi-thread indices
     * \return
     */
    static void generateRandomCharge(T *_outCharge,
                                     const T _chargeQuantum,
                                     const uint _chargesMaximum,
                                     const size_t _randomSeed,
                                     const size_t _countObjects,
                                     const std::vector<std::pair<size_t, size_t>> &_pool);

 public:
    /*!
     * \brief Calculate positions at specific time-step
     * \param _out Output positions
     * \param _orientation Space orientation
     * \param _timeStep Time-step
     * \param _scale Scale factor
     * \return Success flag
     */
    bool
    getPositionsAtTimeStep(Vec3<T> *_out, const Orientation<T> &_orientation, const T _timeStep, const T _scale) const;

    /*!
     * \brief Calculate positions at specific time-step
     * \tparam T2 Output precision
     * \param _out Output positions
     * \param _orientation Space orientation
     * \param _timeStep Time-step
     * \param _scale Scale factor
     * \return Success flag
     */
    template <typename T2>
    bool getPositionsAtTimeStepT(Vec3<T2> *_out,
                                 const Orientation<T2> &_orientation,
                                 const T2 _timeStep,
                                 const T2 _scale) const;

    /*!
     * \brief Calculate object point sizes relative to the object mass
     * \param _out Output object point sizes
     * \param _maximumPointSize Point size of heaviest object
     */
    void getPointSizeByMass(float *_out, const float _maximumPointSize) const;

    /*!
     * \brief Calculate object point sizes relative to the absolute value of the object charge
     * \param _out Output object point sizes
     * \param _maximumPointSize Point size of the most charged object
     */
    void getPointSizeByCharge(float *_out, const float _maximumPointSize) const;

    /*!
     * \brief Calculate object point sizes relative to the object velocity
     * \param _out Output object point sizes
     * \param _maximumPointSize Point size of the fastest possible object
     * \param _timeStep Time step
     */
    void getPointSizeByVelocity(float *_out, const float _maximumPointSize, const T _timeStep) const;

    /*!
     * \brief Calculate object point sizes relative to the object acceleration
     * \param _out Output object point sizes
     * \param _maximumPointSize Point size of the most accelerating object
     * \param _timeStep Time step
     */
    void getPointSizeByAccel(float *_out, const float _maximumPointSize, const T _timeStep) const;

    /*!
     * \brief Calculate object colors based on the sign of the object charge
     * \param _out Output object colors
     * \param _colorNeutral Neutral object color
     * \param _colorPositive Color for positively charged objects
     * \param _colorNegative Color for negatively charged objects
     */
    void getColorByCharge(Vec3F *_out,
                          const ColorRGB &_colorNeutral,
                          const ColorRGB &_colorPositive,
                          const ColorRGB &_colorNegative) const;

    /*!
     * \brief Calculate object colors relative to the object mass - gray-scale style
     * \param _out Output object colors
     */
    void getColorByMassGrayscale(Vec3F *_out) const;

    /*!
     * \brief Calculate object colors relative to the object mass - rainbow style
     * \param _out Output object colors
     */
    void getColorByMassRainbow(Vec3F *_out) const;

    /*!
     * \brief Calculate object colors relative to the object charge - rainbow style
     * \param _out Output object colors
     */
    void getColorByChargeRainbow(Vec3F *_out) const;

    /*!
     * \brief Calculate object colors relative to the object velocity - rainbow style
     * \param _out Output object colors
     * \param _timeStep Time step
     */
    void getColorByVelocityRainbow(Vec3F *_out, const T _timeStep) const;

    /*!
     * \brief Calculate object colors relative to the object acceleration - rainbow style
     * \param _out Output object colors
     * \param _timeStep Time step
     */
    void getColorByAccelRainbow(Vec3F *_out, const T _timeStep) const;

    /*!
     * \brief Create simulation with Newtons and Coulombs forces
     * \param _fileName Simulation database file
     * \param _randomSeed Seed for random number generator
     * \param _countObjects Number of objects
     * \param _countSteps Number of steps
     * \param _rungeKutta Use Runge-Kutta method
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Gravitational constant
     * \param _electrostaticConstant Electrostatic constant
     * \param _areaRadius Area radius
     * \param _massMinimum Minimal object mass
     * \param _massMaximum Maximal object mass
     * \param _chargeQuantum Electric charge quantum
     * \param _chargesMaximum Maximum number of electric quantum that object can hold
     * \return Created simulation database
     */
    static PhysicsNewton<T> *simulationCoulumb(const std::string &_fileName,
                                               const size_t _randomSeed,
                                               const size_t _countObjects,
                                               const size_t _countSteps,
                                               const bool _rungeKutta,
                                               const T _timeStep,
                                               const T _gravitationalConstant,
                                               const T _electrostaticConstant,
                                               const T _areaRadius,
                                               const T _massMinimum,
                                               const T _massMaximum,
                                               const T _chargeQuantum,
                                               const uint _chargesMaximum);

    /*!
     * \brief Create simulation with Newtons forces
     * \param _fileName Simulation database file
     * \param _randomSeed Seed for random number generator
     * \param _countObjects Number of objects
     * \param _countSteps Number of steps
     * \param _rungeKutta Use Runge-Kutta method
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Gravitational constant
     * \param _areaRadiusXY Area radius within the XY plane
     * \param _areaRadiusZ Area radius within the Z axis
     * \param _massMinimum Minimal object mass
     * \param _massMaximum Maximal object mass
     * \return Created simulation database
     */
    static PhysicsNewton<T> *simulationNewton(const std::string &_fileName,
                                              const size_t _randomSeed,
                                              const size_t _countObjects,
                                              const size_t _countSteps,
                                              const bool _rungeKutta,
                                              const T _timeStep,
                                              const T _gravitationalConstant,
                                              const T _areaRadiusXY,
                                              const T _areaRadiusZ,
                                              const T _massMinimum,
                                              const T _massMaximum);

    /*!
     * \brief Create simulation with Newtons forces
     * \param _fileName Simulation database file
     * \param _randomSeed Seed for random number generator
     * \param _countObjectsBulge Number of objects in galactic bulge
     * \param _countObjectsDisc Number of objects in galactic disk
     * \param _countSteps Number of steps
     * \param _rungeKutta Use Runge-Kutta method
     * \param _timeStep Time step duration
     * \param _gravitationalConstant Gravitational constant
     * \param _bulkRadius Galactic bulge radius
     * \param _discRadius Disc radius within the XY plane
     * \param _discHeight Disc radius within the Z axis
     * \param _massCenter Central galaxy object mass
     * \param _massMinimum Minimal object mass
     * \param _massMaximum Maximal object mass
     * \return Created simulation database
     */
    static PhysicsNewton<T> *simulationGalaxyNewton(const std::string &_fileName,
                                                    const size_t _randomSeed,
                                                    const size_t _countObjectsBulge,
                                                    const size_t _countObjectsDisc,
                                                    const size_t _countSteps,
                                                    const bool _rungeKutta,
                                                    const T _timeStep,
                                                    const T _gravitationalConstant,
                                                    const T _bulkRadius,
                                                    const T _discRadius,
                                                    const T _discHeight,
                                                    const T _massCenter,
                                                    const T _massMinimum,
                                                    const T _massMaximum);
};

template <typename T>
PhysicsNewton<T>::~PhysicsNewton()
{
    if (mass != nullptr)
        std::free(mass);
    if (charge != nullptr)
        std::free(charge);
    if (position != nullptr)
        std::free(position);
    if (velocity != nullptr)
        std::free(velocity);
    if (acceleration != nullptr)
        std::free(acceleration);
}

template <typename T>
PhysicsNewton<T>::PhysicsNewton(const std::string &_fileName)
{
    std::ifstream ifs(_fileName, std::ios::binary);
    if (!ifs.is_open())
    {
        std::cerr << "PhysicsNewton(): Can't read file: " << _fileName << "!\n";
        return;
    }

    ifs >> dataHash;
    ifs >> countObjects;
    ifs >> countSteps;
    ifs >> timeStep;
    ifs >> gravitationalConstant;
    ifs >> electrostaticConstant;
    ifs >> massMinimum;
    ifs >> massMaximum;
    ifs >> massTotal;
    ifs >> chargeMinimum;
    ifs >> chargeMaximum;
    ifs >> velocityMinimum;
    ifs >> velocityMaximum;
    ifs >> accelerationMinimum;
    ifs >> accelerationMaximum;

    mass = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    if (isPositive(electrostaticConstant))
        charge = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    position = reinterpret_cast<Vec3<T> *>(std::malloc(countSteps * countObjects * sizeof(Vec3<T>)));
    velocity = reinterpret_cast<Vec3<T> *>(std::malloc(countSteps * countObjects * sizeof(Vec3<T>)));
    acceleration = reinterpret_cast<Vec3<T> *>(std::malloc(countSteps * countObjects * sizeof(Vec3<T>)));

    ifs.read(reinterpret_cast<char *>(mass), countObjects * sizeof(T));
    if (!isPositive(electrostaticConstant))
        ifs.read(reinterpret_cast<char *>(charge), countObjects * sizeof(T));
    ifs.read(reinterpret_cast<char *>(position), countSteps * countObjects * sizeof(Vec3<T>));
    ifs.read(reinterpret_cast<char *>(velocity), countSteps * countObjects * sizeof(Vec3<T>));
    ifs.read(reinterpret_cast<char *>(acceleration), countSteps * countObjects * sizeof(Vec3<T>));
}

template <typename T>
bool PhysicsNewton<T>::save(const std::string &_fileName) const
{
    if (_fileName.empty())
    {
        std::cerr << "PhysicsNewton::save(): Empty file name!\n";
        return false;
    }

    std::ofstream ofs(_fileName, std::ios::binary);
    if (!ofs.is_open())
    {
        std::cerr << "PhysicsNewton::save(): Can't write into file:" << _fileName << "!\n";
        return false;
    }

    ofs << dataHash;
    ofs << countObjects;
    ofs << countSteps;
    ofs << timeStep;
    ofs << gravitationalConstant;
    ofs << electrostaticConstant;
    ofs << massMinimum;
    ofs << massMaximum;
    ofs << massTotal;
    ofs << chargeMinimum;
    ofs << chargeMaximum;
    ofs << velocityMinimum;
    ofs << velocityMaximum;
    ofs << accelerationMinimum;
    ofs << accelerationMaximum;

    ofs.write(reinterpret_cast<const char *>(mass), countObjects * sizeof(T));
    if (isPositive(electrostaticConstant))
        ofs.write(reinterpret_cast<const char *>(charge), countObjects * sizeof(T));
    ofs.write(reinterpret_cast<const char *>(position), countSteps * countObjects * sizeof(Vec3<T>));
    ofs.write(reinterpret_cast<const char *>(velocity), countSteps * countObjects * sizeof(Vec3<T>));
    ofs.write(reinterpret_cast<const char *>(acceleration), countSteps * countObjects * sizeof(Vec3<T>));

    ofs.close();

    return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool PhysicsNewton<T>::build(const size_t _dataHash,
                             const size_t _countObjects,
                             const size_t _countSteps,
                             const T *_mass,
                             const T *_charge,
                             const Vec3<T> *_position,
                             const Vec3<T> *_velocity,
                             const T _massTotal,
                             const T _timeStep,
                             const T _gravitationalConstant,
                             const T _electrostaticConstant)
{
    if (_countObjects == 0UL || _countSteps == 0UL || !isPositive(_timeStep) || !isPositive(_gravitationalConstant) ||
        _mass == nullptr || _position == nullptr || _velocity == nullptr)
    {
        std::cerr << "PhysicsNewton::build(): Invalid input data !\n";
        return false;
    }

    if (!isPositive(_electrostaticConstant) || _charge == nullptr)
        return build(
            _dataHash, _countObjects, _countSteps, _mass, _position, _velocity, _timeStep, _gravitationalConstant);

    dataHash = _dataHash;
    countObjects = _countObjects;
    countSteps = _countSteps;
    massTotal = _massTotal;
    timeStep = _timeStep;
    gravitationalConstant = _gravitationalConstant;
    electrostaticConstant = _electrostaticConstant;

    const T ts2 = timeStep * timeStep * T(0.5);
    const size_t dataSize = countSteps * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    const std::vector<std::pair<size_t, size_t>> pool2 = createPool(dataSize);

    mass = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    charge = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    position = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    velocity = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    acceleration = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));

    copyData<T, size_t>(mass, _mass, countObjects, pool);
    copyData<T, size_t>(charge, _charge, countObjects, pool);
    copyData<Vec3<T>, size_t>(position, _position, countObjects, pool);
    copyData<Vec3<T>, size_t>(velocity, _velocity, countObjects, pool);

    minMaxData<T, size_t>(massMinimum, massMaximum, mass, countObjects, pool);
    minMaxData<T, size_t>(chargeMinimum, chargeMaximum, charge, countObjects, pool);

    for (size_t step = 1UL; step <= countSteps; ++step)
    {
        const size_t offsetPrev = (step - 1UL) * countObjects;
        // Calculate acceleration
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                acceleration[offsetPrev + i] = calcAccel(
                    i, countObjects, gravitationalConstant, electrostaticConstant, mass, charge, &position[offsetPrev]);
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());

            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, this](Vec3<T> *_outAcc, const Vec3<T> *_objPos, const T *_objMass, const T *_objCharge) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            _outAcc[i] = calcAccel(i,
                                                   countObjects,
                                                   gravitationalConstant,
                                                   electrostaticConstant,
                                                   _objMass,
                                                   _objCharge,
                                                   _objPos);
                    },
                    &acceleration[offsetPrev],
                    &position[offsetPrev],
                    mass,
                    charge));

            for (std::thread &t : threads)
                t.join();
        }

        if (step == countSteps)
            break;

        // Calculate new positions and velocities
        buildStep(step, ts2, pool);
    }
    Vec3<T>::minMaxLength(velocityMinimum, velocityMaximum, velocity, dataSize, pool2);
    Vec3<T>::minMaxLength(accelerationMinimum, accelerationMaximum, acceleration, dataSize, pool2);
    return true;
}

template <typename T>
bool PhysicsNewton<T>::build(const size_t _dataHash,
                             const size_t _countObjects,
                             const size_t _countSteps,
                             const T *_mass,
                             const Vec3<T> *_position,
                             const Vec3<T> *_velocity,
                             const T _massTotal,
                             const T _timeStep,
                             const T _gravitationalConstant)
{
    if (_countObjects == 0UL || _countSteps == 0UL || !isPositive(_timeStep) || !isPositive(_gravitationalConstant) ||
        _mass == nullptr || _position == nullptr || _velocity == nullptr)
    {
        std::cerr << "PhysicsNewton::build(): Invalid input data !\n";
        return false;
    }

    dataHash = _dataHash;
    countObjects = _countObjects;
    countSteps = _countSteps;
    timeStep = _timeStep;
    massTotal = _massTotal;
    gravitationalConstant = _gravitationalConstant;

    const T ts2 = timeStep * timeStep * T(0.5);
    const size_t dataSize = countSteps * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    const std::vector<std::pair<size_t, size_t>> pool2 = createPool(dataSize);

    mass = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    position = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    velocity = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    acceleration = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));

    copyData<T, size_t>(mass, _mass, countObjects, pool);
    copyData<Vec3<T>, size_t>(position, _position, countObjects, pool);
    copyData<Vec3<T>, size_t>(velocity, _velocity, countObjects, pool);

    minMaxData<T, size_t>(massMinimum, massMaximum, mass, countObjects, pool);

    for (size_t step = 1UL; step <= countSteps; ++step)
    {
        const size_t offsetPrev = (step - 1UL) * countObjects;
        // Calculate acceleration
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                acceleration[offsetPrev + i] =
                    calcAccel(i, countObjects, gravitationalConstant, mass, &position[offsetPrev]);
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());

            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, this](Vec3<T> *_outAcc, const Vec3<T> *_objPos, const T *_objMass) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            _outAcc[i] = calcAccel(i, countObjects, gravitationalConstant, _objMass, _objPos);
                    },
                    &acceleration[offsetPrev],
                    &position[offsetPrev],
                    mass));

            for (std::thread &t : threads)
                t.join();
        }

        if (step == countSteps)
            break;

        // Calculate new positions and velocities
        buildStep(step, ts2, pool);
    }

    Vec3<T>::minMaxLength(velocityMinimum, velocityMaximum, velocity, dataSize, pool2);
    Vec3<T>::minMaxLength(accelerationMinimum, accelerationMaximum, acceleration, dataSize, pool2);
    return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool PhysicsNewton<T>::buildRK(const size_t _dataHash,
                               const size_t _countObjects,
                               const size_t _countSteps,
                               const T *_mass,
                               const T *_charge,
                               const Vec3<T> *_position,
                               const Vec3<T> *_velocity,
                               const T _massTotal,
                               const T _timeStep,
                               const T _gravitationalConstant,
                               const T _electrostaticConstant)
{
    if (_countObjects == 0UL || _countSteps == 0UL || !isPositive(_timeStep) || !isPositive(_gravitationalConstant) ||
        _mass == nullptr || _position == nullptr || _velocity == nullptr)
    {
        std::cerr << "PhysicsNewton::buildRK(): Invalid input data !\n";
        return false;
    }

    if (!isPositive(_electrostaticConstant) || _charge == nullptr)
        return build(
            _dataHash, _countObjects, _countSteps, _mass, _position, _velocity, _timeStep, _gravitationalConstant);

    dataHash = _dataHash;
    countObjects = _countObjects;
    countSteps = _countSteps;
    massTotal = _massTotal;
    timeStep = _timeStep;
    gravitationalConstant = _gravitationalConstant;
    electrostaticConstant = _electrostaticConstant;

    const T ts2 = timeStep * timeStep * T(0.5);
    const size_t dataSize = countSteps * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    const std::vector<std::pair<size_t, size_t>> pool2 = createPool(dataSize);

    mass = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    charge = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    position = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    velocity = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    acceleration = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));

    copyData<T, size_t>(mass, _mass, countObjects, pool);
    copyData<T, size_t>(charge, _charge, countObjects, pool);
    copyData<Vec3<T>, size_t>(position, _position, countObjects, pool);
    copyData<Vec3<T>, size_t>(velocity, _velocity, countObjects, pool);

    minMaxData<T, size_t>(massMinimum, massMaximum, mass, countObjects, pool);
    minMaxData<T, size_t>(chargeMinimum, chargeMaximum, charge, countObjects, pool);

    for (size_t step = 1UL; step <= countSteps; ++step)
    {
        const size_t offsetPrev = (step - 1UL) * countObjects;
        // Calculate acceleration
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                acceleration[offsetPrev + i] = calcAccelRK(i,
                                                           countObjects,
                                                           timeStep,
                                                           gravitationalConstant,
                                                           electrostaticConstant,
                                                           mass,
                                                           charge,
                                                           &position[offsetPrev],
                                                           &velocity[offsetPrev]);
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());

            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, this](Vec3<T> *_outAcc,
                              const Vec3<T> *_objPos,
                              const Vec3<T> *_objVel,
                              const T *_objMass,
                              const T *_objCharge) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            _outAcc[i] = calcAccelRK(i,
                                                     countObjects,
                                                     timeStep,
                                                     gravitationalConstant,
                                                     electrostaticConstant,
                                                     _objMass,
                                                     _objCharge,
                                                     _objPos,
                                                     _objVel);
                    },
                    &acceleration[offsetPrev],
                    &position[offsetPrev],
                    &velocity[offsetPrev],
                    mass,
                    charge));

            for (std::thread &t : threads)
                t.join();
        }

        if (step == countSteps)
            break;

        // Calculate new positions and velocities
        buildStep(step, ts2, pool);
    }
    Vec3<T>::minMaxLength(velocityMinimum, velocityMaximum, velocity, dataSize, pool2);
    Vec3<T>::minMaxLength(accelerationMinimum, accelerationMaximum, acceleration, dataSize, pool2);
    return true;
}

template <typename T>
bool PhysicsNewton<T>::buildRK(const size_t _dataHash,
                               const size_t _countObjects,
                               const size_t _countSteps,
                               const T *_mass,
                               const Vec3<T> *_position,
                               const Vec3<T> *_velocity,
                               const T _massTotal,
                               const T _timeStep,
                               const T _gravitationalConstant)
{
    if (_countObjects == 0UL || _countSteps == 0UL || !isPositive(_timeStep) || !isPositive(_gravitationalConstant) ||
        _mass == nullptr || _position == nullptr || _velocity == nullptr)
    {
        std::cerr << "PhysicsNewton::buildRK(): Invalid input data !\n";
        return false;
    }

    dataHash = _dataHash;
    countObjects = _countObjects;
    countSteps = _countSteps;
    timeStep = _timeStep;
    massTotal = _massTotal;
    gravitationalConstant = _gravitationalConstant;

    const T ts2 = timeStep * timeStep * T(0.5);
    const size_t dataSize = countSteps * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    const std::vector<std::pair<size_t, size_t>> pool2 = createPool(dataSize);

    mass = reinterpret_cast<T *>(std::malloc(countObjects * sizeof(T)));
    position = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    velocity = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));
    acceleration = reinterpret_cast<Vec3<T> *>(std::malloc(dataSize * sizeof(Vec3<T>)));

    copyData<T, size_t>(mass, _mass, countObjects, pool);
    copyData<Vec3<T>, size_t>(position, _position, countObjects, pool);
    copyData<Vec3<T>, size_t>(velocity, _velocity, countObjects, pool);

    minMaxData<T, size_t>(massMinimum, massMaximum, mass, countObjects, pool);

    for (size_t step = 1UL; step <= countSteps; ++step)
    {
        const size_t offsetPrev = (step - 1UL) * countObjects;
        // Calculate acceleration
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                acceleration[offsetPrev + i] = calcAccelRK(i,
                                                           countObjects,
                                                           timeStep,
                                                           gravitationalConstant,
                                                           mass,
                                                           &position[offsetPrev],
                                                           &velocity[offsetPrev]);
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());

            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, this](Vec3<T> *_outAcc, const Vec3<T> *_objPos, const Vec3<T> *_objVel, const T *_objMass) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            _outAcc[i] = calcAccelRK(
                                i, countObjects, timeStep, gravitationalConstant, _objMass, _objPos, _objVel);
                    },
                    &acceleration[offsetPrev],
                    &position[offsetPrev],
                    &velocity[offsetPrev],
                    mass));

            for (std::thread &t : threads)
                t.join();
        }

        if (step == countSteps)
            break;

        // Calculate new positions and velocities
        buildStep(step, ts2, pool);
    }

    Vec3<T>::minMaxLength(velocityMinimum, velocityMaximum, velocity, dataSize, pool2);
    Vec3<T>::minMaxLength(accelerationMinimum, accelerationMaximum, acceleration, dataSize, pool2);
    return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void PhysicsNewton<T>::buildStep(const size_t _step,
                                 const T _timeStep2,
                                 const std::vector<std::pair<size_t, size_t>> &_pool)
{
    const size_t offsetCur = _step * countObjects;
    const size_t offsetPrev = (_step - 1UL) * countObjects;
    if (_pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
        {
            const size_t ic = offsetCur + i;
            const size_t ip = offsetPrev + i;
            position[ic] = position[ip] + velocity[ip] * timeStep + acceleration[ip] * _timeStep2;
            velocity[ic] = velocity[ip] + acceleration[ip] * timeStep;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
            threads.push_back(std::thread(
                [t, _timeStep2, this](Vec3<T> *_outPos,
                                      Vec3<T> *_outVel,
                                      const Vec3<T> *_objPos,
                                      const Vec3<T> *_objVel,
                                      const Vec3<T> *_objAcc) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        _outPos[i] = _objPos[i] + _objVel[i] * timeStep + _objAcc[i] * _timeStep2;
                        _outVel[i] = _objVel[i] + _objAcc[i] * timeStep;
                    }
                },
                &position[offsetCur],
                &velocity[offsetCur],
                &position[offsetPrev],
                &velocity[offsetPrev],
                &acceleration[offsetPrev]));

        for (std::thread &t : threads)
            t.join();
    }
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Vec3<T> PhysicsNewton<T>::calcAccel(const size_t _i,
                                    const size_t _countObjects,
                                    const T _gravitationalConstant,
                                    const T *_objectMass,
                                    const Vec3<T> *_objectPosition)
{
    Vec3<T> result = {};
    for (size_t i = 0UL; i < _countObjects; ++i)
        if (_i != i)
        {
            const Vec3<T> dir = _objectPosition[i] - _objectPosition[_i];
            const T dist = dir.length();
            result += dir * (_gravitationalConstant * _objectMass[i] / (dist * dist * dist));
        }
    return result;
}

template <typename T>
Vec3<T> PhysicsNewton<T>::calcAccel(const size_t _i,
                                    const size_t _countObjects,
                                    const T _gravitationalConstant,
                                    const T _electrostaticConstant,
                                    const T *_objectMass,
                                    const T *_objectCharge,
                                    const Vec3<T> *_objectPosition)
{
    if (Math::isNull(_objectCharge[_i]))
        return calcAccel(_i, _countObjects, _gravitationalConstant, _objectMass, _objectPosition);

    const T tmpObj = -_electrostaticConstant * _objectCharge[_i] / _objectMass[_i];

    Vec3<T> result = {};
    for (size_t i = 0UL; i < _countObjects; ++i)
        if (_i != i)
        {
            const Vec3<T> dir = _objectPosition[i] - _objectPosition[_i];
            const T dist = dir.length();
            const T dist3 = dist * dist * dist;
            result += dir * (_gravitationalConstant * _objectMass[i] / dist3);
            if (!Math::isNull(_objectCharge[i]))
                result += dir * (tmpObj * _objectCharge[i] / dist3);
        }
    return result;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Vec3<T> PhysicsNewton<T>::calcAccelRK(const size_t _i,
                                      const size_t _countObjects,
                                      const T _timeDelta,
                                      const T _gravitationalConstant,
                                      const T *_objectMass,
                                      const Vec3<T> *_objectPosition,
                                      const Vec3<T> *_objectVelocity)
{
    Vec3<T> result = {};
    for (size_t i = 0UL; i < _countObjects; ++i)
    {
        if (_i == i)
            continue;

        const Vec3<T> dir = _objectPosition[i] - _objectPosition[_i];
        const T dist = dir.length();
        const T tmp = (_gravitationalConstant * _objectMass[i] / (dist * dist * dist));

        const Vec3<T> K1 = dir * tmp;

        Vec3<T> velocity_update = _objectVelocity[_i] + K1 * (_timeDelta * T(0.5));
        Vec3<T> location_update = _objectPosition[_i] + velocity_update * (_timeDelta * T(0.5));

        const Vec3<T> K2 = (_objectPosition[i] - location_update) * tmp;

        velocity_update = _objectVelocity[_i] + K2 * (_timeDelta * T(0.5));
        location_update = _objectPosition[_i] + velocity_update * (_timeDelta * T(0.5));

        const Vec3<T> K3 = (_objectPosition[i] - location_update) * tmp;

        velocity_update = _objectVelocity[_i] + K3 * _timeDelta;
        location_update = _objectPosition[_i] + velocity_update * _timeDelta;

        const Vec3<T> K4 = (_objectPosition[i] - location_update) * tmp;

        result += (K1 + K2 * T(2.0) + K3 * T(2.0) + K4) / T(6.0);
    }
    return result;
}

template <typename T>
Vec3<T> PhysicsNewton<T>::calcAccelRK(const size_t _i,
                                      const size_t _countObjects,
                                      const T _timeDelta,
                                      const T _gravitationalConstant,
                                      const T _electrostaticConstant,
                                      const T *_objectMass,
                                      const T *_objectCharge,
                                      const Vec3<T> *_objectPosition,
                                      const Vec3<T> *_objectVelocity)
{
    const T tmpObj = -_electrostaticConstant * _objectCharge[_i] / _objectMass[_i];

    Vec3<T> result = {};
    for (size_t i = 0UL; i < _countObjects; ++i)
        if (_i != i)
        {
            const Vec3<T> dir = _objectPosition[i] - _objectPosition[_i];
            const T dist = dir.length();
            const T dist3 = dist * dist * dist;
            T tmp = (_gravitationalConstant * _objectMass[i] / dist3);

            Vec3<T> K1 = dir * tmp;

            Vec3<T> velocity_update = _objectVelocity[_i] + K1 * (_timeDelta * T(0.5));
            Vec3<T> location_update = _objectPosition[_i] + velocity_update * (_timeDelta * T(0.5));

            Vec3<T> K2 = (_objectPosition[i] - location_update) * tmp;

            velocity_update = _objectVelocity[_i] + K2 * (_timeDelta * T(0.5));
            location_update = _objectPosition[_i] + velocity_update * (_timeDelta * T(0.5));

            Vec3<T> K3 = (_objectPosition[i] - location_update) * tmp;

            velocity_update = _objectVelocity[_i] + K3 * _timeDelta;
            location_update = _objectPosition[_i] + velocity_update * _timeDelta;

            Vec3<T> K4 = (_objectPosition[i] - location_update) * tmp;

            result += (K1 + K2 * T(2.0) + K3 * T(2.0) + K4) / T(6.0);

            if (!Math::isNull(_objectCharge[i]))
            {
                tmp = (tmpObj * _objectCharge[i] / dist3);

                K1 = dir * tmp;

                velocity_update = _objectVelocity[_i] + K1 * (_timeDelta * T(0.5));
                location_update = _objectPosition[_i] + velocity_update * (_timeDelta * T(0.5));

                K2 = (_objectPosition[i] - location_update) * tmp;

                velocity_update = _objectVelocity[_i] + K2 * (_timeDelta * T(0.5));
                location_update = _objectPosition[_i] + velocity_update * (_timeDelta * T(0.5));

                K3 = (_objectPosition[i] - location_update) * tmp;

                velocity_update = _objectVelocity[_i] + K3 * _timeDelta;
                location_update = _objectPosition[_i] + velocity_update * _timeDelta;

                K4 = (_objectPosition[i] - location_update) * tmp;

                result += (K1 + K2 * T(2.0) + K3 * T(2.0) + K4) / T(6.0);
            }
        }
    return result;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool PhysicsNewton<T>::getPositionsAtTimeStep(Vec3<T> *_out,
                                              const Orientation<T> &_orientation,
                                              const T _timeStep,
                                              const T _scale) const
{
    if (isNegative(_timeStep) || !isPositive(timeStep))
    {
        std::cerr << "PhysicsNewton<T>::getPositionsAtTimeStep(" << _timeStep << "): Invalid time-step!\n";
        return false;
    }

    const size_t stepIdx = size_t(_timeStep / timeStep);
    if (stepIdx >= countSteps)
    {
        std::cerr << "PhysicsNewton<T>::getPositionsAtTimeStep(" << _timeStep << "): Invalid time-step!\n";
        return false;
    }

    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);

    const T timeAdd = _timeStep - T(stepIdx) * timeStep;
    const T ta2 = timeAdd * timeAdd * T(0.5);
    const size_t offset = stepIdx * countObjects;

    if (isUnit(_scale))
    {
        if (_orientation.isUnit())
        {
            if (pool.empty())
            {
                for (size_t i = 0UL; i < countObjects; ++i)
                    _out[i] = position[offset + i] + velocity[offset + i] * timeAdd + acceleration[offset + i] * ta2;
            }
            else
            {
                std::vector<std::thread> threads;
                threads.reserve(pool.size());
                for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                    threads.push_back(std::thread(
                        [t, offset, timeAdd, ta2](
                            Vec3<T> *__out, const Vec3<T> *_p, const Vec3<T> *_v, const Vec3<T> *_a) {
                            const size_t end = t.first + t.second;
                            for (size_t i = t.first; i < end; ++i)
                                __out[i] = _p[offset + i] + _v[offset + i] * timeAdd + _a[offset + i] * ta2;
                        },
                        _out,
                        position,
                        velocity,
                        acceleration));
                for (std::thread &t : threads)
                    t.join();
            }
        }
        else
        {
            if (pool.empty())
            {
                for (size_t i = 0UL; i < countObjects; ++i)
                    _out[i] = _orientation.getPoint(position[offset + i] + velocity[offset + i] * timeAdd +
                                                    acceleration[offset + i] * ta2);
            }
            else
            {
                std::vector<std::thread> threads;
                threads.reserve(pool.size());
                for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                    threads.push_back(std::thread(
                        [t, offset, timeAdd, ta2, _orientation](
                            Vec3<T> *__out, const Vec3<T> *_p, const Vec3<T> *_v, const Vec3<T> *_a) {
                            const size_t end = t.first + t.second;
                            for (size_t i = t.first; i < end; ++i)
                                __out[i] = _orientation.getPoint(_p[offset + i] + _v[offset + i] * timeAdd +
                                                                 _a[offset + i] * ta2);
                        },
                        _out,
                        position,
                        velocity,
                        acceleration));
                for (std::thread &t : threads)
                    t.join();
            }
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                _out[i] = _orientation.getPoint(
                    position[offset + i] + velocity[offset + i] * timeAdd + acceleration[offset + i] * ta2, _scale);
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, timeAdd, ta2, _orientation, _scale](
                        Vec3<T> *__out, const Vec3<T> *_p, const Vec3<T> *_v, const Vec3<T> *_a) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] = _orientation.getPoint(
                                _p[offset + i] + _v[offset + i] * timeAdd + _a[offset + i] * ta2, _scale);
                    },
                    _out,
                    position,
                    velocity,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
    return true;
}

template <typename T>
template <typename T2>
bool PhysicsNewton<T>::getPositionsAtTimeStepT(Vec3<T2> *_out,
                                               const Orientation<T2> &_orientation,
                                               const T2 _timeStep,
                                               const T2 _scale) const
{
    if (isNegative(_timeStep) || !isPositive(timeStep))
    {
        std::cerr << "PhysicsNewton<T>::getPositionsAtTimeStepT(" << _timeStep << "): Invalid time-step!\n";
        return false;
    }

    const size_t stepIdx = size_t(_timeStep / timeStep);
    if (stepIdx >= countSteps)
    {
        std::cerr << "PhysicsNewton<T>::getPositionsAtTimeStepT(" << _timeStep << "): Invalid time-step!\n";
        return false;
    }

    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    const T timeAdd = T(_timeStep) - T(stepIdx) * timeStep;
    const T ta2 = timeAdd * timeAdd * T(0.5);
    const size_t offset = stepIdx * countObjects;

    if (isUnit(_scale))
    {
        if (_orientation.isUnit())
        {
            if (pool.empty())
            {
                for (size_t i = 0UL; i < countObjects; ++i)
                    _out[i] = (position[offset + i] + velocity[offset + i] * timeAdd + acceleration[offset + i] * ta2)
                                  .template converted<T2>();
            }
            else
            {
                std::vector<std::thread> threads;
                threads.reserve(pool.size());
                for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                    threads.push_back(std::thread(
                        [t, offset, timeAdd, ta2](
                            Vec3<T2> *__out, const Vec3<T> *_p, const Vec3<T> *_v, const Vec3<T> *_a) {
                            const size_t end = t.first + t.second;
                            for (size_t i = t.first; i < end; ++i)
                                __out[i] = (_p[offset + i] + _v[offset + i] * timeAdd + _a[offset + i] * ta2)
                                               .template converted<T2>();
                        },
                        _out,
                        position,
                        velocity,
                        acceleration));
                for (std::thread &t : threads)
                    t.join();
            }
        }
        else
        {
            if (pool.empty())
            {
                for (size_t i = 0UL; i < countObjects; ++i)
                    _out[i] = _orientation.getPoint(
                        (position[offset + i] + velocity[offset + i] * timeAdd + acceleration[offset + i] * ta2)
                            .template converted<T2>());
            }
            else
            {
                std::vector<std::thread> threads;
                threads.reserve(pool.size());
                for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                    threads.push_back(std::thread(
                        [t, offset, timeAdd, ta2, _orientation](
                            Vec3<T2> *__out, const Vec3<T> *_p, const Vec3<T> *_v, const Vec3<T> *_a) {
                            const size_t end = t.first + t.second;
                            for (size_t i = t.first; i < end; ++i)
                                __out[i] = _orientation.getPoint(
                                    (_p[offset + i] + _v[offset + i] * timeAdd + _a[offset + i] * ta2)
                                        .template converted<T2>());
                        },
                        _out,
                        position,
                        velocity,
                        acceleration));
                for (std::thread &t : threads)
                    t.join();
            }
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                _out[i] = _orientation.getPoint(
                    (position[offset + i] + velocity[offset + i] * timeAdd + acceleration[offset + i] * ta2)
                        .template converted<T2>(),
                    _scale);
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, offset, timeAdd, ta2, _orientation, _scale](
                        Vec3<T2> *__out, const Vec3<T> *_p, const Vec3<T> *_v, const Vec3<T> *_a) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] =
                                _orientation.getPoint((_p[offset + i] + _v[offset + i] * timeAdd + _a[offset + i] * ta2)
                                                          .template converted<T2>(),
                                                      _scale);
                    },
                    _out,
                    position,
                    velocity,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
    return true;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void PhysicsNewton<T>::getPointSizeByMass(float *_out, const float _maximumPointSize) const
{
    if (isLessOrEqual(_maximumPointSize, 1.0f))
    {
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const T dm = massMaximum - massMinimum;
    if (!isPositive(dm))
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByMass(): Invalid mass range:" << massMinimum << " - "
                  << massMaximum << "!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const float ds = _maximumPointSize - 1.0f;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
            _out[i] = 1.0f + ds * alignedTo0_1(float((mass[i] - massMinimum) / dm));
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, ds, dm, this](float *__out, const T *_mass) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __out[i] = 1.0f + ds * alignedTo0_1(float((_mass[i] - massMinimum) / dm));
                },
                _out,
                mass));
        for (std::thread &t : threads)
            t.join();
    }
}

template <typename T>
void PhysicsNewton<T>::getPointSizeByCharge(float *_out, const float _maximumPointSize) const
{
    if (charge == nullptr || isLessOrEqual(_maximumPointSize, 1.0f))
    {
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const T cm = chargeMaximum - chargeMinimum;
    if (!isPositive(cm))
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByCharge(): Invalid charge range:" << chargeMinimum << " - "
                  << chargeMaximum << "!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const T cx = std::max(std::abs(chargeMinimum), std::abs(chargeMaximum));

    const float ds = _maximumPointSize - 1.0f;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
            _out[i] = 1.0f + ds * alignedTo0_1(float(std::abs(charge[i]) / cx));
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, ds, cx](float *__out, const T *_charge) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __out[i] = 1.0f + ds * alignedTo0_1(float(std::abs(_charge[i]) / cx));
                },
                _out,
                charge));
        for (std::thread &t : threads)
            t.join();
    }
}

template <typename T>
void PhysicsNewton<T>::getPointSizeByVelocity(float *_out, const float _maximumPointSize, const T _timeStep) const
{
    if (velocity == nullptr || isLessOrEqual(_maximumPointSize, 1.0f))
    {
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    if (isNegative(_timeStep) || !isPositive(timeStep))
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByVelocity(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const size_t stepIdx = size_t(_timeStep / timeStep);
    if (stepIdx >= countSteps)
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByVelocity(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const T dv = velocityMaximum - velocityMinimum;
    if (!isPositive(dv))
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByVelocity(): Invalid velocity range:" << velocityMinimum << " - "
                  << velocityMaximum << "!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const float ds = _maximumPointSize - 1.0f;
    const T timeAdd = _timeStep - T(stepIdx) * timeStep;
    const size_t offset = stepIdx * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    if (Math::isNull(timeAdd))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                _out[i] = 1.0f + ds * alignedTo0_1(float((velocity[offset + i].length() - velocityMinimum) / dv));
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, ds, dv, offset, this](float *__out, const Vec3<T> *_velocity) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] = 1.0f +
                                ds * alignedTo0_1(float((_velocity[offset + i].length() - velocityMinimum) / dv));
                    },
                    _out,
                    velocity));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
            {
                const Vec3<T> v = velocity[offset + i] + acceleration[offset + i] * timeAdd;
                _out[i] = 1.0f + ds * alignedTo0_1(float((v.length() - velocityMinimum) / dv));
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, ds, dv, timeAdd, offset, this](
                        float *__out, const Vec3<T> *_velocity, const Vec3<T> *_acceleration) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec3<T> v = _velocity[offset + i] + _acceleration[offset + i] * timeAdd;
                            __out[i] = 1.0f + ds * alignedTo0_1(float((v.length() - velocityMinimum) / dv));
                        }
                    },
                    _out,
                    velocity,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
}

template <typename T>
void PhysicsNewton<T>::getPointSizeByAccel(float *_out, const float _maximumPointSize, const T _timeStep) const
{
    if (acceleration == nullptr || isLessOrEqual(_maximumPointSize, 1.0f))
    {
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    if (isNegative(_timeStep) || !isPositive(timeStep))
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByAccel(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const size_t stepIdx = size_t(_timeStep / timeStep);
    if (stepIdx >= countSteps)
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByAccel(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const T da = accelerationMaximum - accelerationMinimum;
    if (!isPositive(da))
    {
        std::cerr << "PhysicsNewton<T>::getPointSizeByAccel(): Invalid acceleration range:" << accelerationMinimum
                  << " - " << accelerationMaximum << "!\n";
        setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
        return;
    }

    const float ds = _maximumPointSize - 1.0f;
    const T timeAdd = _timeStep - T(stepIdx) * timeStep;
    const size_t offset = stepIdx * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    if (Math::isNull(timeAdd))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                _out[i] =
                    1.0f + ds * alignedTo0_1(float((acceleration[offset + i].length() - accelerationMinimum) / da));
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, ds, da, offset, this](float *__out, const Vec3<T> *_acceleration) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] = 1.0f +
                                ds *
                                    alignedTo0_1(
                                        float((_acceleration[offset + i].length() - accelerationMinimum) / da));
                    },
                    _out,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (stepIdx == (countSteps - 1UL))
        {
            std::cerr << "PhysicsNewton<T>::getPointSizeByAccel(" << _timeStep << "): Invalid time-step!\n";
            setConstantData(_out, 1.0f, countObjects, createPool(countObjects));
            return;
        }

        const T timeAddRatio = timeAdd / timeStep;
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
            {
                const T l1 = acceleration[offset + i].length();
                const T l2 = acceleration[offset + i + countObjects].length();
                const T l = l1 + (l2 - l1) * timeAddRatio;
                _out[i] = 1.0f + ds * alignedTo0_1(float((l - accelerationMinimum) / da));
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, ds, da, timeAddRatio, offset, this](float *__out, const Vec3<T> *_acceleration) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const T l1 = _acceleration[offset + i].length();
                            const T l2 = _acceleration[offset + i + countObjects].length();
                            const T l = l1 + (l2 - l1) * timeAddRatio;
                            __out[i] = 1.0f + ds * alignedTo0_1(float((l - accelerationMinimum) / da));
                        }
                    },
                    _out,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void PhysicsNewton<T>::getColorByCharge(Vec3F *_out,
                                        const ColorRGB &_colorNeutral,
                                        const ColorRGB &_colorPositive,
                                        const ColorRGB &_colorNegative) const
{
    const Vec3F c0 = _colorNeutral.toVec3F();

    if (charge == nullptr)
    {
        setConstantData(_out, c0, countObjects, createPool(countObjects));
        return;
    }

    const Vec3F cP = _colorPositive.toVec3F();
    const Vec3F cM = _colorNegative.toVec3F();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
        {
            if (isNull(charge[i]))
                _out[i] = c0;
            else if (charge[i] > T(0))
                _out[i] = cP;
            else
                _out[i] = cM;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, c0, cP, cM](Vec3F *__out, const T *_charge) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        if (isNull(_charge[i]))
                            __out[i] = c0;
                        else if (_charge[i] > T(0))
                            __out[i] = cP;
                        else
                            __out[i] = cM;
                    }
                },
                _out,
                charge));
        for (std::thread &t : threads)
            t.join();
    }
}

template <typename T>
void PhysicsNewton<T>::getColorByMassGrayscale(Vec3F *_out) const
{
    static const Vec3F cMax(1, 1, 1);
    static const float xMin = 0.3f;
    static const float xDif = 1.0f - xMin;

    const T dm = massMaximum - massMinimum;
    if (!isPositive(dm))
    {
        std::cerr << "PhysicsNewton<T>::getColorByMassGrayscale(): Invalid mass range:" << massMinimum << " - "
                  << massMaximum << "!\n";
        setConstantData(_out, cMax, countObjects, createPool(countObjects));
        return;
    }

    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    if (pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
            _out[i] = cMax * (xMin + xDif * alignedTo0_1(float((mass[i] - massMinimum) / dm)));
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, dm, this](Vec3F *__out, const T *_mass) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __out[i] = cMax * (xMin + xDif * alignedTo0_1(float((_mass[i] - massMinimum) / dm)));
                },
                _out,
                mass));
        for (std::thread &t : threads)
            t.join();
    }
}

template <typename T>
void PhysicsNewton<T>::getColorByMassRainbow(Vec3F *_out) const
{
    const T dm = massMaximum - massMinimum;
    if (!isPositive(dm))
    {
        std::cerr << "PhysicsNewton<T>::getColorByMassRainbow(): Invalid mass range:" << massMinimum << " - "
                  << massMaximum << "!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    if (pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
            _out[i] = ColorRGB::rainbow(alignedTo0_1(float((mass[i] - massMinimum) / dm))).toVec3F();
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, dm, this](Vec3F *__out, const T *_mass) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __out[i] = ColorRGB::rainbow(alignedTo0_1(float((_mass[i] - massMinimum) / dm))).toVec3F();
                },
                _out,
                mass));
        for (std::thread &t : threads)
            t.join();
    }
}

template <typename T>
void PhysicsNewton<T>::getColorByChargeRainbow(Vec3F *_out) const
{
    if (charge == nullptr)
    {
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const T dm = chargeMaximum - chargeMinimum;
    if (!isPositive(dm))
    {
        std::cerr << "PhysicsNewton<T>::getColorByChargeRainbow(): Invalid charge range:" << chargeMinimum << " - "
                  << chargeMaximum << "!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);
    if (pool.empty())
    {
        for (size_t i = 0UL; i < countObjects; ++i)
            _out[i] = ColorRGB::rainbow(alignedTo0_1(float((charge[i] - chargeMinimum) / dm))).toVec3F();
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, dm, this](Vec3F *__out, const T *_charge) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                        __out[i] = ColorRGB::rainbow(alignedTo0_1(float((_charge[i] - chargeMinimum) / dm))).toVec3F();
                },
                _out,
                charge));
        for (std::thread &t : threads)
            t.join();
    }
}

template <typename T>
void PhysicsNewton<T>::getColorByVelocityRainbow(Vec3F *_out, const T _timeStep) const
{
    if (velocity == nullptr)
    {
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    if (isNegative(_timeStep) || !isPositive(timeStep))
    {
        std::cerr << "PhysicsNewton<T>::getColorByVelocityRainbow(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const size_t stepIdx = size_t(_timeStep / timeStep);
    if (stepIdx >= countSteps)
    {
        std::cerr << "PhysicsNewton<T>::getColorByVelocityRainbow(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const T dm = velocityMaximum - velocityMinimum;
    if (!isPositive(dm))
    {
        std::cerr << "PhysicsNewton<T>::getColorByVelocityRainbow(): Invalid velocity range:" << velocityMinimum
                  << " - " << velocityMaximum << "!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const T timeAdd = _timeStep - T(stepIdx) * timeStep;
    const size_t offset = stepIdx * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);

    if (Math::isNull(timeAdd))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                _out[i] = ColorRGB::rainbow(alignedTo0_1(float((velocity[offset + i].length() - velocityMinimum) / dm)))
                              .toVec3F();
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, dm, offset, this](Vec3F *__out, const Vec3<T> *_velocity) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] = ColorRGB::rainbow(
                                           alignedTo0_1(float((_velocity[offset + i].length() - velocityMinimum) / dm)))
                                           .toVec3F();
                    },
                    _out,
                    velocity));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
            {
                const Vec3<T> v = velocity[offset + i] + acceleration[offset + i] * timeAdd;
                _out[i] = ColorRGB::rainbow(alignedTo0_1(float((v.length() - velocityMinimum) / dm))).toVec3F();
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, dm, timeAdd, offset, this](
                        Vec3F *__out, const Vec3<T> *_velocity, const Vec3<T> *_acceleration) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const Vec3<T> v = _velocity[offset + i] + _acceleration[offset + i] * timeAdd;
                            __out[i] =
                                ColorRGB::rainbow(alignedTo0_1(float((v.length() - velocityMinimum) / dm))).toVec3F();
                        }
                    },
                    _out,
                    velocity,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
}

template <typename T>
void PhysicsNewton<T>::getColorByAccelRainbow(Vec3F *_out, const T _timeStep) const
{
    if (acceleration == nullptr)
    {
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    if (isNegative(_timeStep) || !isPositive(timeStep))
    {
        std::cerr << "PhysicsNewton<T>::getColorByAccelRainbow(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const size_t stepIdx = size_t(_timeStep / timeStep);
    if (stepIdx >= countSteps)
    {
        std::cerr << "PhysicsNewton<T>::getColorByAccelRainbow(" << _timeStep << "): Invalid time-step!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const T dm = accelerationMaximum - accelerationMinimum;
    if (!isPositive(dm))
    {
        std::cerr << "PhysicsNewton<T>::getColorByAccelRainbow(): Invalid acceleration range:" << accelerationMinimum
                  << " - " << accelerationMaximum << "!\n";
        setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
        return;
    }

    const T timeAdd = _timeStep - T(stepIdx) * timeStep;
    const size_t offset = stepIdx * countObjects;
    const std::vector<std::pair<size_t, size_t>> pool = createPool(countObjects);

    if (Math::isNull(timeAdd))
    {
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
                _out[i] = ColorRGB::rainbow(
                              alignedTo0_1(float((acceleration[offset + i].length() - accelerationMinimum) / dm)))
                              .toVec3F();
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, dm, offset, this](Vec3F *__out, const Vec3<T> *_acceleration) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                            __out[i] =
                                ColorRGB::rainbow(alignedTo0_1(float(
                                                      (_acceleration[offset + i].length() - accelerationMinimum) / dm)))
                                    .toVec3F();
                    },
                    _out,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
    else
    {
        if (stepIdx == (countSteps - 1UL))
        {
            std::cerr << "PhysicsNewton<T>::getColorByAccelRainbow(" << _timeStep << "): Invalid time-step!\n";
            setConstantData(_out, Vec3F(1, 1, 1), countObjects, createPool(countObjects));
            return;
        }

        const T timeAddRatio = timeAdd / timeStep;
        if (pool.empty())
        {
            for (size_t i = 0UL; i < countObjects; ++i)
            {
                const T l1 = acceleration[offset + i].length();
                const T l2 = acceleration[offset + i + countObjects].length();
                const T l = l1 + (l2 - l1) * timeAddRatio;
                _out[i] = ColorRGB::rainbow(alignedTo0_1(float((l - accelerationMinimum) / dm))).toVec3F();
            }
        }
        else
        {
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, dm, timeAddRatio, offset, this](Vec3F *__out, const Vec3<T> *_acceleration) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const T l1 = _acceleration[offset + i].length();
                            const T l2 = _acceleration[offset + i + countObjects].length();
                            const T l = l1 + (l2 - l1) * timeAddRatio;
                            __out[i] = ColorRGB::rainbow(alignedTo0_1(float((l - accelerationMinimum) / dm))).toVec3F();
                        }
                    },
                    _out,
                    acceleration));
            for (std::thread &t : threads)
                t.join();
        }
    }
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T PhysicsNewton<T>::generateRandomObjects(Vec3<T> *_outPosition,
                                          T *_outMass,
                                          const T _radiusX,
                                          const T _radiusY,
                                          const T _radiusZ,
                                          const T _massMinimum,
                                          const T _massMaximum,
                                          const size_t _randomSeed,
                                          const size_t _countObjects,
                                          const std::vector<std::pair<size_t, size_t>> &_pool)
{
    static const T randomDistStdDev = T(0.25);

    const T mMin = std::min(_massMinimum, _massMaximum);
    const T mMax = std::max(_massMinimum, _massMaximum);

    T sumMass = T(0);
    Vec3<T> massCenterPos = {};
    if (_pool.empty())
    {
        std::mt19937_64 gen;
        std::normal_distribution<T> d1(T(0), randomDistStdDev);
        std::uniform_real_distribution<T> d2(mMin, mMax);
        gen.seed(_randomSeed);
        for (size_t i = 0UL; i < _countObjects; ++i)
        {
            _outPosition[i] = {d1(gen) * _radiusX, d1(gen) * _radiusY, d1(gen) * _radiusZ};
            _outMass[i] = d2(gen);
            massCenterPos += (_outPosition[i] * _outMass[i]);
            sumMass += _outMass[i];
        }
        massCenterPos /= sumMass;
    }
    else
    {
        size_t tt = 0U;
        std::vector<Vec3<T>> tData1(_pool.size(), Vec3<T>());
        std::vector<T> tData2(_pool.size(), T(0));
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
        {
            threads.push_back(std::thread(
                [t, tt, mMin, mMax, _radiusX, _radiusY, _radiusZ, _randomSeed](
                    Vec3<T> *__outPosition, T *__outMass, Vec3<T> &_outSum, T &_outMass) {
                    std::mt19937_64 gen;
                    std::normal_distribution<T> d1(T(0), randomDistStdDev);
                    std::uniform_real_distribution<T> d2(mMin, mMax);
                    gen.seed(_randomSeed + tt);

                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        __outPosition[i] = {d1(gen) * _radiusX, d1(gen) * _radiusY, d1(gen) * _radiusZ};
                        __outMass[i] = d2(gen);
                        _outSum += (__outPosition[i] * __outMass[i]);
                        _outMass += __outMass[i];
                    }
                },
                _outPosition,
                _outMass,
                std::ref(tData1[tt]),
                std::ref(tData2[tt])));
            tt++;
        }

        for (std::thread &t : threads)
            t.join();

        sumMass = std::accumulate(tData2.cbegin(), tData2.cend(), T(0));
        massCenterPos = std::accumulate(tData1.cbegin(), tData1.cend(), Vec3<T>()) / sumMass;
    }

    massCenterPos.invert();
    addConstantData(_outPosition, massCenterPos, _countObjects, _pool);
    return sumMass;
}

template <typename T>
void PhysicsNewton<T>::generateRandomCharge(T *_outCharge,
                                            const T _chargeQuantum,
                                            const uint _chargesMaximum,
                                            const size_t _randomSeed,
                                            const size_t _countObjects,
                                            const std::vector<std::pair<size_t, size_t>> &_pool)
{
    int sumCharge = 0;
    if (_pool.empty())
    {
        std::mt19937_64 gen;
        std::uniform_int_distribution<int> d(-int(_chargesMaximum), int(_chargesMaximum));
        gen.seed(_randomSeed + 100UL);
        for (size_t i = 0UL; i < _countObjects; ++i)
        {
            const int ch = d(gen);
            sumCharge += ch;
            _outCharge[i] = T(ch) * _chargeQuantum;
        }
    }
    else
    {
        size_t tt = 0U;
        std::vector<int> tData(_pool.size(), 0);
        std::vector<std::thread> threads;
        threads.reserve(_pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(_pool))
        {
            threads.push_back(std::thread(
                [t, tt, _chargeQuantum, _chargesMaximum, _randomSeed](T *__outCharge, int &_sumCharge) {
                    std::mt19937_64 gen;
                    std::uniform_int_distribution<int> d(-int(_chargesMaximum), int(_chargesMaximum));
                    gen.seed(_randomSeed + tt);

                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const int ch = d(gen);
                        _sumCharge += ch;
                        __outCharge[i] = T(ch) * _chargeQuantum;
                    }
                },
                _outCharge,
                std::ref(tData[tt])));
            tt++;
        }

        for (std::thread &t : threads)
            t.join();

        sumCharge = std::accumulate(tData.cbegin(), tData.cend(), 0);
    }

    const T cMax = T(_chargesMaximum) * _chargeQuantum;
    const T cMin = -cMax;

    size_t i = 0UL;
    while (sumCharge != 0)
    {
        if (sumCharge > 0)
        {
            if (!equals(_outCharge[i], cMin))
            {
                _outCharge[i] -= _chargeQuantum;
                sumCharge--;
            }
        }
        else
        {
            if (!equals(_outCharge[i], cMax))
            {
                _outCharge[i] += _chargeQuantum;
                sumCharge++;
            }
        }

        i++;
        if (i == _countObjects)
            i = 0UL;
    }
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
PhysicsNewton<T> *PhysicsNewton<T>::simulationCoulumb(const std::string &_fileName,
                                                      const size_t _randomSeed,
                                                      const size_t _countObjects,
                                                      const size_t _countSteps,
                                                      const bool _rungeKutta,
                                                      const T _timeStep,
                                                      const T _gravitationalConstant,
                                                      const T _electrostaticConstant,
                                                      const T _areaRadius,
                                                      const T _massMinimum,
                                                      const T _massMaximum,
                                                      const T _chargeQuantum,
                                                      const uint _chargesMaximum)
{
    if (_countObjects == 0UL || _countSteps == 0UL || !isPositive(_timeStep) || !isPositive(_gravitationalConstant) ||
        !isPositive(_areaRadius) || !isPositive(_massMinimum) || !isPositive(_massMaximum))
    {
        std::cerr << "PhysicsNewton::simulationCoulumb(): Invalid input data !\n";
        return false;
    }

    if (!isPositive(_electrostaticConstant) || !isPositive(_chargeQuantum) || _chargesMaximum == 0U)
    {
        std::cerr << "PhysicsNewton::simulationCoulumb(): Invalid electric settings, executing simulationNewton()!\n";
        return simulationNewton(_fileName,
                                _randomSeed,
                                _countObjects,
                                _countSteps,
                                _rungeKutta,
                                _timeStep,
                                _gravitationalConstant,
                                _areaRadius,
                                _areaRadius,
                                _massMinimum,
                                _massMaximum);
    }

    const size_t hash = mixHash(std::hash<int>{}(int(getFloatingPointType<T>())),
                                std::hash<uint>{}(std::thread::hardware_concurrency()),
                                std::hash<size_t>{}(_randomSeed),
                                std::hash<size_t>{}(_countObjects),
                                std::hash<size_t>{}(_countSteps),
                                std::hash<bool>{}(_rungeKutta),
                                std::hash<T>{}(_timeStep),
                                std::hash<T>{}(_gravitationalConstant),
                                std::hash<T>{}(_electrostaticConstant),
                                std::hash<T>{}(_areaRadius),
                                std::hash<T>{}(_massMinimum),
                                std::hash<T>{}(_massMaximum),
                                std::hash<T>{}(_chargeQuantum),
                                std::hash<uint>{}(_chargesMaximum));

    std::ifstream ifs(_fileName, std::ios::binary);
    if (ifs.is_open())
    {
        size_t hash2;
        ifs >> hash2;
        if (hash2 == hash)
        {
            ifs.seekg(0);
            return new PhysicsNewton<T>(_fileName);
        }
    }

    PhysicsNewton<T> *result = new PhysicsNewton<T>();
    const std::vector<std::pair<size_t, size_t>> pool = createPool(_countObjects);

    T *tmpMass = reinterpret_cast<T *>(std::malloc(_countObjects * sizeof(T)));
    T *tmpCharge = reinterpret_cast<T *>(std::malloc(_countObjects * sizeof(T)));
    Vec3<T> *tmpPosition = reinterpret_cast<Vec3<T> *>(std::malloc(_countObjects * sizeof(Vec3<T>)));
    Vec3<T> *tmpVelocity = reinterpret_cast<Vec3<T> *>(std::malloc(_countObjects * sizeof(Vec3<T>)));

    const T massTotal = generateRandomObjects(tmpPosition,
                                              tmpMass,
                                              _areaRadius,
                                              _areaRadius,
                                              _areaRadius,
                                              _massMinimum,
                                              _massMaximum,
                                              _randomSeed,
                                              _countObjects,
                                              pool);

    generateRandomCharge(tmpCharge, _chargeQuantum, _chargesMaximum, _randomSeed + 1000UL, _countObjects, pool);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < _countObjects; ++i)
        {
            const T R1 = tmpPosition[i].length();
            if (!isPositive(R1))
            {
                tmpVelocity[i] = {T(0), T(0), T(0)};
                continue;
            }
            const Vec3<T> A = calcAccel(
                i, _countObjects, _gravitationalConstant, _electrostaticConstant, tmpMass, tmpCharge, tmpPosition);
            const Vec3<T> N0 = -(tmpPosition[i]).normalized();
            const Vec3<T> A1 = A.projected(N0);
            const Vec3<T> A2 = A - A1;
            const T a1 = A1.length();
            const T a2 = A2.length();
            const T v1 = std::sqrt(a1 * R1);
            const T v2 = v1 * a2 / a1;
            const Vec3<T> N1 = Vec3<T>::cross(Vec3<T>::unitZ(), N0).normalized();
            const Vec3<T> N2 = Vec3<T>::cross(N0, N1).normalized();
            tmpVelocity[i] = N1 * v1 + N2 * v2;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _countObjects, _gravitationalConstant, _electrostaticConstant](
                    Vec3<T> *_outVel, const Vec3<T> *_objPos, const T *_objMass, const T *_objCharge) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T R1 = _objPos[i].length();
                        if (!isPositive(R1))
                        {
                            _outVel[i] = {T(0), T(0), T(0)};
                            continue;
                        }
                        const Vec3<T> A = calcAccel(i,
                                                    _countObjects,
                                                    _gravitationalConstant,
                                                    _electrostaticConstant,
                                                    _objMass,
                                                    _objCharge,
                                                    _objPos);
                        const Vec3<T> N0 = -(_objPos[i]).normalized();
                        const Vec3<T> A1 = A.projected(N0);
                        const Vec3<T> A2 = A - A1;
                        const T a1 = A1.length();
                        const T a2 = A2.length();
                        const T v1 = std::sqrt(a1 * R1);
                        const T v2 = v1 * a2 / a1;
                        const Vec3<T> N1 = Vec3<T>::cross(Vec3<T>::unitZ(), N0).normalized();
                        const Vec3<T> N2 = Vec3<T>::cross(N0, N1).normalized();
                        _outVel[i] = N1 * v1 + N2 * v2;
                    }
                },
                tmpVelocity,
                tmpPosition,
                tmpMass,
                tmpCharge));

        for (std::thread &t : threads)
            t.join();
    }

    if (_rungeKutta)
    {
        if (result->buildRK(hash,
                            _countObjects,
                            _countSteps,
                            tmpMass,
                            tmpCharge,
                            tmpPosition,
                            tmpVelocity,
                            massTotal,
                            _timeStep,
                            _gravitationalConstant,
                            _electrostaticConstant))
            result->save(_fileName);
    }
    else
    {
        if (result->build(hash,
                          _countObjects,
                          _countSteps,
                          tmpMass,
                          tmpCharge,
                          tmpPosition,
                          tmpVelocity,
                          massTotal,
                          _timeStep,
                          _gravitationalConstant,
                          _electrostaticConstant))
            result->save(_fileName);
    }

    std::free(tmpMass);
    std::free(tmpCharge);
    std::free(tmpPosition);
    std::free(tmpVelocity);

    return result;
}

template <typename T>
PhysicsNewton<T> *PhysicsNewton<T>::simulationNewton(const std::string &_fileName,
                                                     const size_t _randomSeed,
                                                     const size_t _countObjects,
                                                     const size_t _countSteps,
                                                     const bool _rungeKutta,
                                                     const T _timeStep,
                                                     const T _gravitationalConstant,
                                                     const T _areaRadiusXY,
                                                     const T _areaRadiusZ,
                                                     const T _massMinimum,
                                                     const T _massMaximum)
{
    if (_countObjects == 0UL || _countSteps == 0UL || !isPositive(_timeStep) || !isPositive(_gravitationalConstant) ||
        !isPositive(_areaRadiusXY) || !isPositive(_areaRadiusZ) || !isPositive(_massMinimum) ||
        !isPositive(_massMaximum))
    {
        std::cerr << "PhysicsNewton::simulationNewton(): Invalid input data !\n";
        return nullptr;
    }

    const size_t hash = mixHash(std::hash<int>{}(int(getFloatingPointType<T>())),
                                std::hash<uint>{}(std::thread::hardware_concurrency()),
                                std::hash<size_t>{}(_randomSeed),
                                std::hash<size_t>{}(_countObjects),
                                std::hash<size_t>{}(_countSteps),
                                std::hash<bool>{}(_rungeKutta),
                                std::hash<T>{}(_timeStep),
                                std::hash<T>{}(_gravitationalConstant),
                                std::hash<T>{}(_areaRadiusXY),
                                std::hash<T>{}(_areaRadiusZ),
                                std::hash<T>{}(_massMinimum),
                                std::hash<T>{}(_massMaximum));

    std::ifstream ifs(_fileName, std::ios::binary);
    if (ifs.is_open())
    {
        size_t hash2;
        ifs >> hash2;
        if (hash2 == hash)
        {
            ifs.seekg(0);
            return new PhysicsNewton<T>(_fileName);
        }
    }

    const std::vector<std::pair<size_t, size_t>> pool = createPool(_countObjects);

    PhysicsNewton<T> *result = new PhysicsNewton<T>();
    T *tmpMass = reinterpret_cast<T *>(std::malloc(_countObjects * sizeof(T)));
    Vec3<T> *tmpPosition = reinterpret_cast<Vec3<T> *>(std::malloc(_countObjects * sizeof(Vec3<T>)));
    Vec3<T> *tmpVelocity = reinterpret_cast<Vec3<T> *>(std::malloc(_countObjects * sizeof(Vec3<T>)));

    const T massTotal = generateRandomObjects(tmpPosition,
                                              tmpMass,
                                              _areaRadiusXY,
                                              _areaRadiusXY,
                                              _areaRadiusZ,
                                              _massMinimum,
                                              _massMaximum,
                                              _randomSeed,
                                              _countObjects,
                                              pool);

    if (pool.empty())
    {
        for (size_t i = 0UL; i < _countObjects; ++i)
        {
            const T R1 = tmpPosition[i].length();
            if (!isPositive(R1))
            {
                tmpVelocity[i] = {T(0), T(0), T(0)};
                continue;
            }
            const Vec3<T> A = calcAccel(i, _countObjects, _gravitationalConstant, tmpMass, tmpPosition);
            const Vec3<T> N0 = -(tmpPosition[i]).normalized();
            const Vec3<T> A1 = A.projected(N0);
            const Vec3<T> A2 = A - A1;
            const T a1 = A1.length();
            const T a2 = A2.length();
            const T v1 = std::sqrt(a1 * R1);
            const T v2 = v1 * a2 / a1;
            const Vec3<T> N1 = Vec3<T>::cross(Vec3<T>::unitZ(), N0).normalized();
            const Vec3<T> N2 = Vec3<T>::cross(N0, N1).normalized();
            tmpVelocity[i] = N1 * v1 + N2 * v2;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, _countObjects, _gravitationalConstant](
                    Vec3<T> *_outVel, const Vec3<T> *_objPos, const T *_objMass) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T R1 = _objPos[i].length();
                        if (!isPositive(R1))
                        {
                            _outVel[i] = {T(0), T(0), T(0)};
                            continue;
                        }
                        const Vec3<T> A = calcAccel(i, _countObjects, _gravitationalConstant, _objMass, _objPos);
                        const Vec3<T> N0 = -(_objPos[i]).normalized();
                        const Vec3<T> A1 = A.projected(N0);
                        const Vec3<T> A2 = A - A1;
                        const T a1 = A1.length();
                        const T a2 = A2.length();
                        const T v1 = std::sqrt(a1 * R1);
                        const T v2 = v1 * a2 / a1;
                        const Vec3<T> N1 = Vec3<T>::cross(Vec3<T>::unitZ(), N0).normalized();
                        const Vec3<T> N2 = Vec3<T>::cross(N0, N1).normalized();
                        _outVel[i] = N1 * v1 + N2 * v2;
                    }
                },
                tmpVelocity,
                tmpPosition,
                tmpMass));

        for (std::thread &t : threads)
            t.join();
    }

    if (_rungeKutta)
    {
        if (result->buildRK(hash,
                            _countObjects,
                            _countSteps,
                            tmpMass,
                            tmpPosition,
                            tmpVelocity,
                            massTotal,
                            _timeStep,
                            _gravitationalConstant))
            result->save(_fileName);
    }
    else
    {
        if (result->build(hash,
                          _countObjects,
                          _countSteps,
                          tmpMass,
                          tmpPosition,
                          tmpVelocity,
                          massTotal,
                          _timeStep,
                          _gravitationalConstant))
            result->save(_fileName);
    }

    std::free(tmpMass);
    std::free(tmpPosition);
    std::free(tmpVelocity);

    return result;
}

template <typename T>
PhysicsNewton<T> *PhysicsNewton<T>::simulationGalaxyNewton(const std::string &_fileName,
                                                           const size_t _randomSeed,
                                                           const size_t _countObjectsBulge,
                                                           const size_t _countObjectsDisc,
                                                           const size_t _countSteps,
                                                           const bool _rungeKutta,
                                                           const T _timeStep,
                                                           const T _gravitationalConstant,
                                                           const T _bulkRadius,
                                                           const T _discRadius,
                                                           const T _discHeight,
                                                           const T _massCenter,
                                                           const T _massMinimum,
                                                           const T _massMaximum)
{
    if (_countObjectsBulge == 0UL || _countObjectsDisc == 0UL || _countSteps == 0UL || !isPositive(_timeStep) ||
        !isPositive(_gravitationalConstant) || !isPositive(_discRadius) || !isPositive(_discHeight) ||
        !isPositive(_bulkRadius) || !isPositive(_massCenter) || !isPositive(_massMinimum) || !isPositive(_massMaximum))
    {
        std::cerr << "PhysicsNewton::simulationGalaxyNewton(): Invalid input data !\n";
        return nullptr;
    }

    const size_t N1 = ((_countObjectsBulge % 2UL) == 0UL) ? _countObjectsBulge : (_countObjectsBulge + 1UL);
    const size_t N2 = ((_countObjectsDisc % 2UL) == 0UL) ? _countObjectsDisc : (_countObjectsDisc + 1UL);

    if ((_countObjectsBulge % 2UL) == 1UL)
        std::cerr << "PhysicsNewton::simulationGalaxyNewton(): Need even count for bulge, using: " << N1 << "!\n";

    if ((_countObjectsDisc % 2UL) == 1UL)
        std::cerr << "PhysicsNewton::simulationGalaxyNewton(): Need even count for disc, using: " << N2 << "!\n";

    size_t hash = std::hash<int>{}(int(getFloatingPointType<T>())), o = 1UL;
    updateHash(hash, o, std::hash<uint>{}(std::thread::hardware_concurrency()));
    updateHash(hash, o, std::hash<size_t>{}(_randomSeed));
    updateHash(hash, o, std::hash<size_t>{}(N1));
    updateHash(hash, o, std::hash<size_t>{}(N2));
    updateHash(hash, o, std::hash<size_t>{}(_countSteps));
    updateHash(hash, o, std::hash<bool>{}(_rungeKutta));
    updateHash(hash, o, std::hash<T>{}(_timeStep));
    updateHash(hash, o, std::hash<T>{}(_gravitationalConstant));
    updateHash(hash, o, std::hash<T>{}(_discRadius));
    updateHash(hash, o, std::hash<T>{}(_discHeight));
    updateHash(hash, o, std::hash<T>{}(_bulkRadius));
    updateHash(hash, o, std::hash<T>{}(_massCenter));
    updateHash(hash, o, std::hash<T>{}(_massMinimum));
    updateHash(hash, o, std::hash<T>{}(_massMaximum));

    std::ifstream ifs(_fileName, std::ios::binary);
    if (ifs.is_open())
    {
        size_t hash2;
        ifs >> hash2;
        if (hash2 == hash)
        {
            ifs.seekg(0);
            return new PhysicsNewton<T>(_fileName);
        }
    }

    const size_t N = N1 + N2 + 1UL;
    const size_t N1_2 = N1 / 2UL;
    const size_t N2_2 = N2 / 2UL;
    static const T randomDistStdDev = T(0.25);

    PhysicsNewton<T> *result = new PhysicsNewton<T>();
    T *tmpMass = reinterpret_cast<T *>(std::malloc(N * sizeof(T)));
    Vec3<T> *tmpPosition = reinterpret_cast<Vec3<T> *>(std::malloc(N * sizeof(Vec3<T>)));
    Vec3<T> *tmpVelocity = reinterpret_cast<Vec3<T> *>(std::malloc(N * sizeof(Vec3<T>)));

    tmpMass[0UL] = _massCenter;
    tmpPosition[0UL] = {};
    tmpVelocity[0UL] = {};
    T sumMass = _massCenter;

    std::vector<std::pair<size_t, size_t>> pool = createPool(N1_2);
    if (pool.empty())
    {
        std::mt19937_64 gen;
        std::normal_distribution<T> d1(T(0), randomDistStdDev);
        std::uniform_real_distribution<T> d2(_massMinimum, _massMaximum);
        gen.seed(_randomSeed);
        for (size_t i = 1UL; i <= N1_2; ++i)
        {
            tmpPosition[i] = {d1(gen) * _bulkRadius, d1(gen) * _bulkRadius, d1(gen) * _bulkRadius};
            tmpMass[i] = d2(gen);
            sumMass += tmpMass[i];
        }
    }
    else
    {
        size_t tt = 0UL;
        std::vector<T> tData(pool.size(), T(0));
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
        {
            threads.push_back(std::thread(
                [t, tt, _randomSeed, _bulkRadius, _massMinimum, _massMaximum](
                    Vec3<T> *__outPosition, T *__outMass, T &_outSum) {
                    std::mt19937_64 gen;
                    std::normal_distribution<T> d1(T(0), randomDistStdDev);
                    std::uniform_real_distribution<T> d2(_massMinimum, _massMaximum);
                    gen.seed(_randomSeed + tt + 1UL);

                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        __outPosition[i] = {d1(gen) * _bulkRadius, d1(gen) * _bulkRadius, d1(gen) * _bulkRadius};
                        __outMass[i] = d2(gen);
                        _outSum += __outMass[i];
                    }
                },
                &tmpPosition[1UL],
                &tmpMass[1UL],
                std::ref(tData[tt])));
            tt++;
        }

        for (std::thread &t : threads)
            t.join();

        sumMass = std::accumulate(tData.cbegin(), tData.cend(), sumMass);
    }

    copyData(&tmpMass[N1_2 + 1UL], &tmpMass[1UL], N1_2, pool);
    copyInvertData(&tmpPosition[N1_2 + 1UL], &tmpPosition[1UL], N1_2, pool);

    pool = createPool(N2_2);
    if (pool.empty())
    {
        std::mt19937_64 gen;
        std::normal_distribution<T> d1(T(0), randomDistStdDev);
        std::uniform_real_distribution<T> d2(_massMinimum, _massMaximum);
        gen.seed(_randomSeed + N1 + 100UL);
        for (size_t i = 1UL; i <= N2_2; ++i)
        {
            tmpPosition[N1 + i] = {d1(gen) * _discRadius, d1(gen) * _discRadius, d1(gen) * _discHeight};
            tmpMass[N1 + i] = d2(gen);
            sumMass += tmpMass[N1 + i];
        }
    }
    else
    {
        size_t tt = 0UL;
        std::vector<T> tData(pool.size(), T(0));
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
        {
            threads.push_back(std::thread(
                [t, tt, N1, _randomSeed, _discRadius, _discHeight, _massMinimum, _massMaximum](
                    Vec3<T> *__outPosition, T *__outMass, T &_outSum) {
                    std::mt19937_64 gen;
                    std::normal_distribution<T> d1(T(0), randomDistStdDev);
                    std::uniform_real_distribution<T> d2(_massMinimum, _massMaximum);
                    gen.seed(_randomSeed + tt + N1 + 200UL);

                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        __outPosition[i] = {d1(gen) * _discRadius, d1(gen) * _discRadius, d1(gen) * _discHeight};
                        __outMass[i] = d2(gen);
                        _outSum += __outMass[i];
                    }
                },
                &tmpPosition[N1 + 1UL],
                &tmpMass[N1 + 1UL],
                std::ref(tData[tt])));
            tt++;
        }

        for (std::thread &t : threads)
            t.join();

        sumMass = std::accumulate(tData.cbegin(), tData.cend(), sumMass);
    }

    copyData(&tmpMass[N1 + N2_2 + 1UL], &tmpMass[N1 + 1UL], N2_2, pool);
    copyInvertData(&tmpPosition[N1 + N2_2 + 1UL], &tmpPosition[N1 + 1UL], N2_2, pool);

    pool = createPool(N);
    if (pool.empty())
    {
        for (size_t i = 0UL; i < N; ++i)
        {
            const T R1 = tmpPosition[i].length();
            if (!isPositive(R1))
            {
                tmpVelocity[i] = {T(0), T(0), T(0)};
                continue;
            }
            const Vec3<T> A = calcAccel(i, N, _gravitationalConstant, tmpMass, tmpPosition);
            const Vec3<T> N0 = -(tmpPosition[i]).normalized();
            const Vec3<T> A1 = A.projected(N0);
            const Vec3<T> A2 = A - A1;
            const T a1 = A1.length();
            const T a2 = A2.length();
            const T v1 = std::sqrt(a1 * R1);
            const T v2 = T(0.1) * v1 * a2 / a1;
            const Vec3<T> N1 = Vec3<T>::cross(Vec3<T>::unitZ(), N0).normalized();
            const Vec3<T> N2 = Vec3<T>::cross(N0, N1).normalized();
            tmpVelocity[i] = N1 * v1 + N2 * v2;
        }
    }
    else
    {
        std::vector<std::thread> threads;
        threads.reserve(pool.size());

        for (const std::pair<size_t, size_t> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, N, _gravitationalConstant](Vec3<T> *_outVel, const Vec3<T> *_objPos, const T *_objMass) {
                    const size_t end = t.first + t.second;
                    for (size_t i = t.first; i < end; ++i)
                    {
                        const T R1 = _objPos[i].length();
                        if (!isPositive(R1))
                        {
                            _outVel[i] = {T(0), T(0), T(0)};
                            continue;
                        }
                        const Vec3<T> A = calcAccel(i, N, _gravitationalConstant, _objMass, _objPos);
                        const Vec3<T> N0 = -(_objPos[i]).normalized();
                        const Vec3<T> A1 = A.projected(N0);
                        const Vec3<T> A2 = A - A1;
                        const T a1 = A1.length();
                        const T a2 = A2.length();
                        const T v1 = std::sqrt(a1 * R1);
                        const T v2 = T(0.1) * v1 * a2 / a1;
                        const Vec3<T> N1 = Vec3<T>::cross(Vec3<T>::unitZ(), N0).normalized();
                        const Vec3<T> N2 = Vec3<T>::cross(N0, N1).normalized();
                        _outVel[i] = N1 * v1 + N2 * v2;
                    }
                },
                tmpVelocity,
                tmpPosition,
                tmpMass));

        for (std::thread &t : threads)
            t.join();
    }

    if (_rungeKutta)
    {
        if (result->buildRK(
                hash, N, _countSteps, tmpMass, tmpPosition, tmpVelocity, sumMass, _timeStep, _gravitationalConstant))
            result->save(_fileName);
    }
    else
    {
        if (result->build(
                hash, N, _countSteps, tmpMass, tmpPosition, tmpVelocity, sumMass, _timeStep, _gravitationalConstant))
            result->save(_fileName);
    }

    std::free(tmpMass);
    std::free(tmpPosition);
    std::free(tmpVelocity);

    return result;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef PhysicsNewton<float> NewtonSimF;        //!< 32 bit floating point precision version
typedef PhysicsNewton<double> NewtonSimD;       //!< 64 bit floating point precision version
typedef PhysicsNewton<long double> NewtonSimL;  //!< 128 bit floating point precision version

}  // namespace Math
}  // namespace U1

#endif  // MATH_PHYSICSNEWTON_H
