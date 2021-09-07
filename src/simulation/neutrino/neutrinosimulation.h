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

    bool loadInitPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const;
    bool loadCalcPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const;

    bool loadInitPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const;
    bool loadCalcPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out, const size_t _objectID) const;

    std::pair<bool, QVector3D> loadInitPosition2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcPosition2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitPosition3(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcPosition3(const size_t _objectID, const double _timeStamp) const;

    std::pair<bool, QVector3D> loadInitVelocity1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcVelocity1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitVelocity2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcVelocity2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitVelocity3(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcVelocity3(const size_t _objectID, const double _timeStamp) const;

    std::pair<bool, QVector3D> loadInitSpin1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcSpin1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitSpin2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcSpin2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitSpin3(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcSpin3(const size_t _objectID, const double _timeStamp) const;

    std::pair<bool, QVector3D> loadInitAccel1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcAccel1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitAccel2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcAccel2(const size_t _objectID, const double _timeStamp) const;

    std::pair<bool, QVector3D> loadInitCurving1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcCurving1(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadInitCurving2(const size_t _objectID, const double _timeStamp) const;
    std::pair<bool, QVector3D> loadCalcCurving2(const size_t _objectID, const double _timeStamp) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Fill output vector with initialization object time-stamps and positions of second generation
 * \param _out Output vector
 * \param _objectID Object ID
 * \returns \c true if success
 */
template <typename T>
bool SimulationNeutrino<T>::loadInitPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                                          const size_t _objectID) const
{
    return _objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size() &&
        Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadPath2(_out);
}

/*!
 * \brief Fill output vector with calculation object time-stamps and positions of second generation
 * \param _out Output vector
 * \param _objectID Object ID
 * \returns \c true if success
 */
template <typename T>
bool SimulationNeutrino<T>::loadCalcPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                                          const size_t _objectID) const
{
    return _objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size() &&
        Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadPath2(_out);
}

/*!
 * \brief Fill output vector with initialization object time-stamps and positions of third generation
 * \param _out Output vector
 * \param _objectID Object ID
 * \returns \c true if success
 */
template <typename T>
bool SimulationNeutrino<T>::loadInitPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                                          const size_t _objectID) const
{
    return _objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size() &&
        Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadPath3(_out);
}

/*!
 * \brief Fill output vector with calculation object time-stamps and positions of third generation
 * \param _out Output vector
 * \param _objectID Object ID
 * \returns \c true if success
 */
template <typename T>
bool SimulationNeutrino<T>::loadCalcPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out,
                                          const size_t _objectID) const
{
    return _objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size() &&
        Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadPath3(_out);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 2 position
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 2 position
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitPosition2(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadPosition2(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 2 position
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 2 position
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcPosition2(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadPosition2(
            _timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 3 position
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 3 position
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitPosition3(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadPosition3(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 3 position
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 3 position
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcPosition3(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadPosition3(
            _timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 1 velocity
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 1 velocity
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitVelocity1(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadVelocity1(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 1 velocity
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 1 velocity
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcVelocity1(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadVelocity1(
            _timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 2 velocity
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 2 velocity
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitVelocity2(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadVelocity2(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 2 velocity
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 2 velocity
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcVelocity2(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadVelocity2(
            _timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 3 velocity
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 3 velocity
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitVelocity3(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadVelocity3(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 3 velocity
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 3 velocity
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcVelocity3(const size_t _objectID,
                                                                    const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadVelocity3(
            _timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 1 spin
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 1 spin
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitSpin1(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadSpin1(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 1 spin
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 1 spin
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcSpin1(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadSpin1(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 2 spin
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 2 spin
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitSpin2(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadSpin2(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 2 spin
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 2 spin
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcSpin2(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadSpin2(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 3 spin
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 3 spin
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitSpin3(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadSpin3(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 3 spin
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 3 spin
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcSpin3(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadSpin3(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 1 acceleration
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 1 acceleration
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitAccel1(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadAccel1(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 1 acceleration
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 1 acceleration
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcAccel1(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadAccel1(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 2 acceleration
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 2 acceleration
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitAccel2(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadAccel2(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 2 acceleration
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 2 acceleration
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcAccel2(const size_t _objectID, const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadAccel2(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 1 curving
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 1 curving
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitCurving1(const size_t _objectID,
                                                                   const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadCurving1(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 1 curving
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 1 curving
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcCurving1(const size_t _objectID,
                                                                   const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadCurving1(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for initialization object's generation 2 curving
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and initialization object's generation 2 curving
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadInitCurving2(const size_t _objectID,
                                                                   const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_initObjects.at(_objectID).loadCurving2(
            _timeStamp);
    return {false, QVector3D()};
}

/*!
 * \brief Getter for calculation object's generation 2 curving
 * \tparam T Template floating point type
 * \param _objectID Object's index
 * \param _timeStamp Time-stamp of required value
 * \returns Pair, success flag and calculation object's generation 2 curving
 */
template <typename T>
std::pair<bool, QVector3D> SimulationNeutrino<T>::loadCalcCurving2(const size_t _objectID,
                                                                   const double _timeStamp) const
{
    if (_objectID < Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.size())
        return Simulation<T, NeutrinoObject<T>, NeutrinoTimeStamp<T>>::m_objects.at(_objectID).loadCurving2(_timeStamp);
    return {false, QVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace GravityNeutrino
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOSIMULATION_H
