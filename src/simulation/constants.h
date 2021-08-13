/*!
 * \file simulation/constants.h
 * \author Michal Steller
 * \brief Universe1 physics constants template implementation
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

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
};

/*!
 * \brief Universe1 physics constants
 * \tparam T Template floating point type
 * \details Holds all Universe1 physics constants
 * | Property               | Unit                                   |
 * | :--------------------- | :------------------------------------- |
 * | Speed of the Universe  | [m/s]                                  |
 * | Gravitational constant | Various unit (current simulation type) |
 */
template <typename T>
struct Constants
{
    T universeVelocity;  //!< Speed of the Universe [m/s]
    T gravityConstant;   //!< Gravitational constant

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Constants()
        : universeVelocity(Const::T_1<T>())
        , gravityConstant(Const::T_1<T>())
    {
    }

    /*!
     * \brief Constructor with object components
     * \param _universeVelocity Speed of the Universe    [m/s]
     * \param _gravityConstant  Gravitational constant
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline Constants(const T _universeVelocity, const T _gravityConstant)
        : universeVelocity(_universeVelocity)
        , gravityConstant(_gravityConstant)
    {
    }
};

}  // namespace Simulation
}  // namespace Universe1

#endif  // CONSTANTS_H
