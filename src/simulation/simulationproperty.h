/*!
 * \file simulation/simulationproperty.h
 * \author Michal Steller
 * \brief SimulationProperty enumeration and tools implementation
 */

#ifndef UNIVERSE1_SIMULATION_SIMULATIONPROPERTY_H
#define UNIVERSE1_SIMULATION_SIMULATIONPROPERTY_H

#include "../math/texttools.h"
#include "constants.h"

#include <list>

namespace Universe1 {
namespace Simulation {

/*!
 * \brief Simulation property names enumeration
 */
enum SimulationProperty : uint32_t
{
    Property_UniverseVelocity = Const_UniverseVelocity,  //!< Name for speed of the Universe constant
    Property_GravityConstant = Const_GravityConstant,    //!< Name for gravitational constant
    Property_ElementRadius = Const_ElementRadius,        //!< Name for element radius
    _Property_PhysicsLast = Property_ElementRadius,      //!< Name for last physics constant

    Property_MaximumStepTime = (uint32_t(_Property_PhysicsLast) << 1U),  //!< Name for maximum step time duration

    Validity_SameCurrentTime = (uint32_t(_Property_PhysicsLast)
                                << 2U),  //!< Name for validity test flag: Same current time within all defined objects

    Validity_ObjectsInitialized =
        (uint32_t(_Property_PhysicsLast) << 3U),  //!< Name for validity test flag: Defined objects are initialized

    Validity_ObjectsPath = (uint32_t(_Property_PhysicsLast)
                            << 4U),  //!< Name for validity test flag: Defined objects has valid continuous path

    Validity_HistoryVisibility =
        (uint32_t(_Property_PhysicsLast) << 5U),  //!< Name for validity test flag: All objects histories are filled
                                                  //!< enough that their gravitation waves can reach all other objects

    Validity_Started =
        (uint32_t(_Property_PhysicsLast) << 6U),  //!< Name for validity test flag: Calculation already started
    _SimulationPropertyLast = Validity_Started    //!< Name for last used property
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Helper function creates list of literals from flags buffer
 * \param flags Flags buffer
 * \returns List of \a SimulationProperty literals that are set
 */
inline std::list<SimulationProperty> readSimulationProperty(const uint32_t flags)
{
    std::list<SimulationProperty> result;
    if ((flags & Property_UniverseVelocity) != 0U)
        result.push_back(Property_UniverseVelocity);
    if ((flags & Property_GravityConstant) != 0U)
        result.push_back(Property_GravityConstant);
    if ((flags & Property_MaximumStepTime) != 0U)
        result.push_back(Property_MaximumStepTime);
    if ((flags & Validity_SameCurrentTime) != 0U)
        result.push_back(Validity_SameCurrentTime);
    if ((flags & Validity_ObjectsInitialized) != 0U)
        result.push_back(Validity_ObjectsInitialized);
    if ((flags & Validity_ObjectsPath) != 0U)
        result.push_back(Validity_ObjectsPath);
    if ((flags & Validity_HistoryVisibility) != 0U)
        result.push_back(Validity_HistoryVisibility);
    if ((flags & Validity_Started) != 0U)
        result.push_back(Validity_Started);
    return result;
}

/*!
 * \brief To \c string tool function for \a SimulationProperty enumeration
 * \param _prop Property to convert
 * \returns \a SimulationProperty as \c string
 */
inline std::string strSimulationProperty(const SimulationProperty _prop)
{
    switch (_prop)
    {
    case Property_UniverseVelocity: return "UniverseVelocity"; break;
    case Property_GravityConstant: return "GravityConstant"; break;
    case Property_ElementRadius: return "ElementRadius"; break;
    case Property_MaximumStepTime: return "MaximumStepTime"; break;
    case Validity_SameCurrentTime: return "SameCurrentTime"; break;
    case Validity_ObjectsInitialized: return "ObjectsInitialized"; break;
    case Validity_ObjectsPath: return "ObjectsPath"; break;
    case Validity_HistoryVisibility: return "HistoryVisibility"; break;
    case Validity_Started: return "Started"; break;
    }
    return "SimulationPropertyUnknown";
}

/*!
 * \brief To \c string tool function for \a SimulationProperty flags buffer
 * \param flags Flags buffer
 * \returns Empty string if no flag is set or connected flag names
 */
inline std::string strSimulationProperties(const uint32_t flags)
{
    const std::list<SimulationProperty> listFlags = readSimulationProperty(flags);
    if (listFlags.empty())
        return std::string();
    std::list<SimulationProperty>::const_iterator it = listFlags.cbegin();

    std::stringstream ss;
    ss << strSimulationProperty(*it);
    ++it;
    for (; it != listFlags.cend(); ++it)
        ss << '|' << strSimulationProperty(*it);
    return ss.str();
}

}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_SIMULATIONPROPERTY_H
