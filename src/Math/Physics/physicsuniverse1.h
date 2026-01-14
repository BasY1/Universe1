/*!
 * \file src/Math/physicsuniverse1.h
 * \brief The Universe1 simulation processor
 */

#ifndef MATH_PHYSICSUNIVERSE1_H
#define MATH_PHYSICSUNIVERSE1_H

#include "physicsuniverse1calculus.h"

namespace U1 {
namespace Math {
namespace Universe1 {

/*!
 * \brief Universe 1 physics simulation processor
 * \tparam T Template floating point type
 */
template <typename T>
class PhysicsUniverse1
{
    Particle<T> *m_db = nullptr;  //!< Particle database
    size_t m_dbSize = 0UL;        //!< Total possible number of particles in the database

    size_t m_offsetCurrent = 0UL;  //!< Offset to current time-step particles in the database
    size_t m_offsetTotal = 0UL;    //!< Number of used particles in the database

    T m_time = T(0);  //!< Current time-step (latest processed time)

    std::list<std::tuple<T, size_t, size_t>> m_timeSteps;  //!< Indexes of particles that are in the same time-step

    std::list<std::pair<const Particle<T> *, const Particle<T> *>> m_histories;  //!< Dead particle trajectories
    std::list<std::pair<const Particle<T> *, const Particle<T> *>> m_particles;  //!< Living particle trajectories

 public:
    PhysicsUniverse1() = default;
    ~PhysicsUniverse1();

    inline const Particle<T> *db() const;
    inline size_t dbSize() const;
    inline size_t offsetCurrent() const;
    inline size_t offsetTotal() const;

    inline const std::list<std::tuple<T, size_t, size_t>> &timeSteps() const;
    inline const std::list<std::pair<const Particle<T> *, const Particle<T> *>> &histories() const;
    inline const std::list<std::pair<const Particle<T> *, const Particle<T> *>> &particles() const;

    inline T time() const;

    bool
    build(std::vector<std::list<Particle<T>>> &_particles, const size_t _dbSize, const T _timeEnd, const T _timeDelta);
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Destructor
 * \tparam T Template floating point type
 */
template <typename T>
PhysicsUniverse1<T>::~PhysicsUniverse1()
{
    if (m_db != nullptr)
        std::free(m_db);
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for particle database
 * \tparam T Template floating point type
 * \return Particle database
 */
template <typename T>
inline const Particle<T> *PhysicsUniverse1<T>::db() const
{
    return m_db;
}

/*!
 * \brief Getter for particle database size
 * \tparam T Template floating point type
 * \return Particle database size
 */
template <typename T>
inline size_t PhysicsUniverse1<T>::dbSize() const
{
    return m_dbSize;
}

/*!
 * \brief Getter for ID offset in particle database where current-time particles begins
 * \tparam T Template floating point type
 * \return ID offset in particle database where current-time particles begins
 */
template <typename T>
inline size_t PhysicsUniverse1<T>::offsetCurrent() const
{
    return m_offsetCurrent;
}

/*!
 * \brief Getter for number of used particles in database
 * \tparam T Template floating point type
 * \return Number of used particles in database
 */
template <typename T>
inline size_t PhysicsUniverse1<T>::offsetTotal() const
{
    return m_offsetTotal;
}

/*!
 * \brief Getter for indexes of particles that are in the same time-step
 * \tparam T Template floating point type
 * \return Indexes of particles that are in the same time-step
 */
template <typename T>
inline const std::list<std::tuple<T, size_t, size_t>> &PhysicsUniverse1<T>::timeSteps() const
{
    return m_timeSteps;
}

/*!
 * \brief Getter for dead particle historical trajectories
 * \tparam T Template floating point type
 * \return Dead particle trajectories
 */
template <typename T>
inline const std::list<std::pair<const Particle<T> *, const Particle<T> *>> &PhysicsUniverse1<T>::histories() const
{
    return m_histories;
}

/*!
 * \brief Getter for current living particle trajectories
 * \tparam T Template floating point type
 * \return Living particle trajectories
 */
template <typename T>
inline const std::list<std::pair<const Particle<T> *, const Particle<T> *>> &PhysicsUniverse1<T>::particles() const
{
    return m_particles;
}

/*!
 * \brief Getter for current resp. latest-processed time in the system
 * \tparam T Template floating point type
 * \return Current resp. latest-processed time in the system
 */
template <typename T>
inline T PhysicsUniverse1<T>::time() const
{
    return m_time;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Build the simulation database
 * \tparam T Template floating point type
 * \param _particles Initial particles and their histories (all particles must end their path at exactly the same time)
 * \param _dbSize Total particle database size
 * \param _timeEnd Final time in calculation
 * \param _timeDelta General time-step duration
 * \return Success flag
 */
template <typename T>
bool PhysicsUniverse1<T>::build(std::vector<std::list<Particle<T>>> &_particles,
                                const size_t _dbSize,
                                const T _timeEnd,
                                const T _timeDelta)
{
    using namespace Calculus;

    if (_dbSize == 0UL || _particles.empty() || !isPositive(_timeEnd) || !isPositive(_timeDelta))
        return failBuild(_dbSize, _particles.size(), _timeEnd, _timeDelta, "Invalid arguments!\n");

    if (_particles.front().size() < 2UL)
        return failBuild(_dbSize, _particles.size(), _timeEnd, _timeDelta, "Initial particle[0] - path too short!\n");

    T startTime = _particles.front().back().time;
    for (size_t N = 0UL; N < _particles.size(); ++N)
    {
        const std::list<Particle<T>> &p = _particles.at(N);
        if (p.size() < 2UL)
            return failBuild(_dbSize,
                             _particles.size(),
                             _timeEnd,
                             _timeDelta,
                             "Initial particle[" + std::to_string(N) + "] - path too short!\n");

        if (!equals(p.back().time, startTime))
            return failBuild(_dbSize,
                             _particles.size(),
                             _timeEnd,
                             _timeDelta,
                             "Initial particle[" + std::to_string(N) + "] - invalid path end time!\n");

        if (!testInitParticle(p.front()))
            return failBuild(_dbSize,
                             _particles.size(),
                             _timeEnd,
                             _timeDelta,
                             "Invalid initial particle[" + std::to_string(N) + "]!\n");

        typename std::list<Particle<T>>::const_iterator i1 = p.cbegin();
        typename std::list<Particle<T>>::const_iterator i2 = i1;
        i2++;

        for (; i2 != p.cend(); ++i1, ++i2)
        {
            if (isMoreOrEqual((*i1).time, (*i2).time))
                return failBuild(_dbSize,
                                 _particles.size(),
                                 _timeEnd,
                                 _timeDelta,
                                 "Initial particle[" + std::to_string(N) + "] - invalid path time order!\n");

            if (!compareInit((*i1), (*i2)))
                return failBuild(_dbSize,
                                 _particles.size(),
                                 _timeEnd,
                                 _timeDelta,
                                 "Initial particle[" + std::to_string(N) + "] - invalid path trajectory!\n");
        }
    }

    if (m_db != nullptr)
    {
        std::cerr << "Warning: PhysicsUniverse1::build(" << _dbSize << ", " << _particles.size() << ", " << _timeEnd
                  << ", " << _timeDelta << "): Destructing old database(" << m_dbSize << ")!\n";
        std::free(m_db);
        m_db = nullptr;
        m_dbSize = 0UL;
        m_offsetCurrent = 0UL;
        m_offsetTotal = 0UL;
        m_time = T(0);
        m_timeSteps.clear();
        m_histories.clear();
        m_particles.clear();
    }

    m_db = reinterpret_cast<Particle<T> *>(std::calloc(_dbSize, sizeof(Particle<T>)));
    if (m_db == nullptr)
    {
        std::cerr << "Error: PhysicsUniverse1::build(" << _dbSize << ", " << _particles.size() << ", " << _timeEnd
                  << ", " << _timeDelta << "): Out of memory!\n";
        return false;
    }

    m_dbSize = _dbSize;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef PhysicsUniverse1<float> U1SimF;        //!< 32 bit floating point precision version
typedef PhysicsUniverse1<double> U1SimD;       //!< 64 bit floating point precision version
typedef PhysicsUniverse1<long double> U1SimL;  //!< 128 bit floating point precision version

}  // namespace Universe1

}  // namespace Math
}  // namespace U1

#endif  // MATH_PHYSICSUNIVERSE1_H
