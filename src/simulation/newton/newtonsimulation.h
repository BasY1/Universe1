/*!
 * \file simulation/newton/newtonsimulation.h
 * \author Michal Steller
 * \brief Newton based simulations template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONSIMULATION_H
#define UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONSIMULATION_H

#include "newtonobjectbywave.h"
#include "newtonobjectcurrent.h"

#include "../simulation.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNewton {

/*!
 * \brief Simulation processor for \n classic newton based simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct SimulationNewtonCurrent : public Universe1::Simulation::Simulation<T, NewtonObjectCurrent<T>, NewtonTimeStamp<T>>
{
    /*!
     * \brief Constructor
     */
    inline SimulationNewtonCurrent()
        : Universe1::Simulation::Simulation<T, NewtonObjectCurrent<T>, NewtonTimeStamp<T>>()
    {
    }
};

/*!
 * \brief Simulation processor for \n newton based simulations with gravitational waves at speed of the universe
 * \tparam T Template floating point type
 */
template <typename T>
struct SimulationNewtonByWave : public Universe1::Simulation::Simulation<T, NewtonObjectByWave<T>, NewtonTimeStamp<T>>
{
    /*!
     * \brief Constructor
     */
    inline SimulationNewtonByWave()
        : Universe1::Simulation::Simulation<T, NewtonObjectByWave<T>, NewtonTimeStamp<T>>()
    {
    }
};

}  // namespace GravityNewton
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEWTON_NEWTONSIMULATION_H
