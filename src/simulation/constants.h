/*!
 * \file simulation/constants.h
 * \author Michal Steller
 * \brief Universe1 physics constants template implementation
 */

#ifndef UNIVERSE1_SIMULATION_CONSTANTS_H
#define UNIVERSE1_SIMULATION_CONSTANTS_H

#include "../math/vec3.h"

namespace Universe1 {
namespace Simulation {

/*!
 * \brief Constant names enumeration
 */
enum ConstantName : uint32_t
{
    Const_UniverseVelocity = 1U,  //!< Name for speed of the Universe constant
    Const_GravityConstant = 2U,   //!< Name for gravitational constant
    Const_ElementRadius = 4U,     //!< Name for gravitational constant
};

/*!
 * \brief Universe1 physics constants
 * \tparam T Template floating point type
 * \details Holds all Universe1 physics constants
 * | Property               | Unit                                   |
 * | :--------------------- | :------------------------------------- |
 * | Speed of the Universe  | [m/s]                                  |
 * | Gravitational constant | Various unit (current simulation type) |
 * | Element radius         | [m]                                    |
 */
template <typename T>
struct Constants
{
    T universeVelocity;  //!< Speed of the Universe [m/s]
    T gravityConstant;   //!< Gravitational constant
    T elementRadius;     //!< Elements radius [m]
    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Constants()
        : universeVelocity(Const::T_1<T>())
        , gravityConstant(Const::T_1<T>())
        , elementRadius(Const::T_1<T>())
    {
    }

    /*!
     * \brief Constructor with object components
     * \param _universeVelocity Speed of the Universe   [m/s]
     * \param _gravityConstant  Gravitational constant
     * \param _elementRadius    Elements radius         [m]
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Constants(const T _universeVelocity, const T _gravityConstant, const T _elementRadius)
        : universeVelocity(_universeVelocity)
        , gravityConstant(_gravityConstant)
        , elementRadius(_elementRadius)
    {
    }
};

}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_CONSTANTS_H
