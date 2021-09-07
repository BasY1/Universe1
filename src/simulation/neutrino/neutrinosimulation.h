/*!
 * \file simulation/neutrino/neutrinosimulation.h
 * \author Michal Steller
 * \brief Neutrino simulations template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOSIMULATION_H
#define UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOSIMULATION_H

#include "neutrinoobject.h"

#include "../simulation.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNeutrino {

/*!
 * \brief Simulation processor for neutrino simulations
 * \tparam T Template floating point type
 */
template <typename T>
struct SimulationNeutrino : public Universe1::Simulation::Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>
{
    /*!
     * \brief Constructor
     */
    inline SimulationNeutrino()
        : Universe1::Simulation::Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>()
    {
    }

    /*!
     * \brief Getter for initialization object's mass
     * \param _objectID Object's index
     * \returns Pair, where \c first item is success flag, and \c second item is initialization object's mass
     *          (as \c QVector3D(mass, 0, 0))
     */
    std::pair<bool, QVector3D> loadInitMass(const size_t _objectID) const;

    /*!
     * \brief Getter for calculation object's mass
     * \param _objectID Object's index
     * \returns Pair, where \c first item is success flag, and \c second item is calculation object's mass
     *          (as \c QVector3D(mass, 0, 0))
     */
    std::pair<bool, QVector3D> loadCalcMass(const size_t _objectID) const;

    /*!
     * \brief Getter for initialization object's velocity
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is initialization object's velocity
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadInitVelocity(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for calculation object's velocity
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is calculation object's velocity
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadCalcVelocity(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for initialization object's acceleration
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is initialization object's acceleration
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadInitAccel(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for calculation object's acceleration
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is calculation object's acceleration
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadCalcAccel(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for initialization object's force (acceleration x mass)
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is initialization object's acceleration
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadInitForce(const size_t _objectID, const double _timeStamp) const;

    /*!
     * \brief Getter for calculation object's force (acceleration x mass)
     * \param _objectID Object's index
     * \param _timeStamp Time-stamp of required value
     * \returns Pair, where \c first item is success flag, and \c second item is calculation object's acceleration
     *          (as \c QVector3D)
     */
    std::pair<bool, QVector3D> loadCalcForce(const size_t _objectID, const double _timeStamp) const;
};
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadInitMass(const size_t _objectID) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.size())
//         return {
//             true,
//             QVector3D(Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.at(_objectID).mass(), 0.0F,
//             0.0F)};
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadCalcMass(const size_t _objectID) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.size())
//         return {true,
//                 QVector3D(Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.at(_objectID).mass(), 0.0F,
//                 0.0F)};
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadInitVelocity(const size_t _objectID,
//                                                                               const double _timeStamp) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.size())
//         return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.at(_objectID).loadVelocity(_timeStamp);
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadCalcVelocity(const size_t _objectID,
//                                                                               const double _timeStamp) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.size())
//         return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.at(_objectID).loadVelocity(_timeStamp);
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadInitAccel(const size_t _objectID,
//                                                                            const double _timeStamp) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.size())
//         return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.at(_objectID).loadAccel(_timeStamp);
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadCalcAccel(const size_t _objectID,
//                                                                            const double _timeStamp) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.size())
//         return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.at(_objectID).loadAccel(_timeStamp);
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadInitForce(const size_t _objectID,
//                                                                            const double _timeStamp) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.size())
//         return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_initObjects.at(_objectID).loadForce(_timeStamp);
//     return {false, QVector3D()};
// }
//
// template <typename T, typename ObjectClass>
// std::pair<bool, QVector3D> SimulationNewton<T, ObjectClass>::loadCalcForce(const size_t _objectID,
//                                                                            const double _timeStamp) const
// {
//     if (_objectID < Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.size())
//         return Simulation<T, ObjectClass, NewtonTimeStamp<T>>::m_objects.at(_objectID).loadForce(_timeStamp);
//     return {false, QVector3D()};
// }
//
}  // namespace GravityNeutrino
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOSIMULATION_H
