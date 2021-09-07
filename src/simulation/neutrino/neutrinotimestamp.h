/*!
 * \file simulation/neutrino/neutrinotimestamp.h
 * \author Michal Steller
 * \brief Neutrino time-stamp template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOTIMESTAMP_H
#define UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOTIMESTAMP_H

#include "../../math/spherecrosssection.h"

#include "../timestamp.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNeutrino {

/*!
 * \brief Enumeration for three neutrino flags
 */
enum NeutrinoFlag : uint32_t
{
    NeutrinoNull = 0U,                                                   //!< Null neutrino state
    NeutrinoGeneration1 = 1U,                                            //!< Generation 1
    NeutrinoGeneration2 = 2U,                                            //!< Generation 2
    NeutrinoGeneration12 = (NeutrinoGeneration1 | NeutrinoGeneration2),  //!< Generation 1-2 border
    NeutrinoGeneration3 = 4U,                                            //!< Generation 3
    NeutrinoGeneration23 = (NeutrinoGeneration2 | NeutrinoGeneration3),  //!< Generation 2-3 border
    NeutrinoStraightMove = 8U,                                           //!< Last active generation move is not curving
    NeutrinoGeneration1StraightMove =
        (NeutrinoGeneration1 | NeutrinoStraightMove),  //!< Last active generation move is not curving
    NeutrinoGeneration2StraightMove =
        (NeutrinoGeneration2 | NeutrinoStraightMove),  //!< Last active generation move is not curving

    NeutrinoInvalidMove1 = 16U,            //!<
    NeutrinoNullSpin1 = 32U,               //!<
    NeutrinoErrorPolynom = 64U,            //!<
    NeutrinoErrorInitGeneration2 = 1228U,  //!<
};

/*!
 * \brief Time-stamp extension for neutrino-pure gravity based simulation
 * \tparam T Template floating point type
 */
template <typename T>
struct NeutrinoTimeStamp : public TimeStamp<T>
{
    uint32_t flags;  //!< Neutrino flags

    /*!
     * \brief Main velocity direction, used for moving under generation 1 state [\f$\frac{m}{s}\f$]
     * \note Length of this vector always equals Universe velocity constant \f$|\vec{V_1}| = C\f$
     * \note Used within generation 1 neutrino state
     */
    Math::Vec3<T> moveVelocity1;

    /*!
     * \brief Generation 2 velocity in main direction (Rest main velocity) \f$\vec{V_{21}}\f$ [\f$\frac{m}{s}\f$]
     * \note \f$\vec{V_{1}^2} = \vec{V_{21}^2} + \vec{V_{22}^2}\f$
     * \note Used within generation 2 neutrino state
     */
    Math::Vec3<T> moveVelocity21;

    /*!
     * \brief Generation 2 velocity parallel with direction of generation 2 spin \f$\vec{V_{22}}\f$ [\f$\frac{m}{s}\f$]
     * \note \f$\vec{V_{1}^2} = \vec{V_{21}^2} + \vec{V_{22}^2}\f$
     * \note Used within generation 2 neutrino state
     * \note Orientation keeps generation 1 order, so \f$V_{22}\f$ velocity direction orientation
     *       is in same direction (or opposite direction) like in generation 1 (Keep helicity)
     */
    Math::Vec3<T> moveVelocity22;

    /*!
     * \brief Generation 3 velocity in main direction (Rest main velocity) \f$\vec{V_{31}}\f$ [\f$\frac{m}{s}\f$]
     * \note \f$\vec{V_{1}^2} = \vec{V_{31}^2} + \vec{V_{32}^2} + \vec{V_{33}^2}\f$
     * \note Used within generation 3 neutrino state
     */
    Math::Vec3<T> moveVelocity31;

    /*!
     * \brief Generation 3 velocity in generation 2 direction (Rest generation 2 velocity) \f$\vec{V_{32}}\f$
     * [\f$\frac{m}{s}\f$] \note \f$\vec{V_{1}^2} = \vec{V_{31}^2} + \vec{V_{32}^2} + \vec{V_{33}^2}\f$ \note Used
     * within generation 3 neutrino state
     */
    Math::Vec3<T> moveVelocity32;

    /*!
     * \brief Generation 3 velocity parallel with direction of generation 3 spin \f$\vec{V_{33}}\f$ [\f$\frac{m}{s}\f$]
     * \note \f$\vec{V_{1}^2} = \vec{V_{31}^2} + \vec{V_{32}^2} + \vec{V_{33}^2}\f$
     * \note Used within generation 3 neutrino state
     * \note Orientation keeps previous generations order, so \f$V_{33}\f$ velocity direction orientation
     *       is in same direction (or opposite direction) like previous generations 1 and 2 (Keep helicity)
     */
    Math::Vec3<T> moveVelocity33;

    /*!
     * \brief Main spin angular velocity vector \f$\vec{\omega_1}\f$ [\f$\frac{rad}{s}\f$]
     * \note Orientation of this vector must be parallel to main velocity vector
     * \details
     * Neutrino "energy" holder.
     * | Orientation \f$\vec{V_1}\f$ against \f$\vec{\omega_1}\f$ | Helicity (chirality) |
     * | :------------------------------------------------------- | :------------------- |
     * | Same direction                                           | Right handed         |
     * | Opposite direction                                       | Left handed          |
     * Possible second and third generations (spins vs move direction) will always keep same helicity
     */
    Math::Vec3<T> spinVelocity1;

    /*!
     * \brief Generation 2 spin angular velocity vector \f$\vec{\omega_2}\f$ [\f$\frac{rad}{s}\f$]
     * \note \f$\vec{\omega_2} = \frac{\vec{V_{21}}}{R1_{curving}}\f$
     * \details Always comes as result of "too much curving" of main velocity direction move
     */
    Math::Vec3<T> spinVelocity2;

    /*!
     * \brief Generation 3 spin angular velocity vector \f$\vec{\omega_3}\f$ [\f$\frac{rad}{s}\f$]
     * \note \f$\vec{\omega_3} = \frac{\vec{V_{32}}}{R2_{curving}}\f$
     * \details Always comes as result of "too much curving" of generation 2 velocity direction move
     */
    Math::Vec3<T> spinVelocity3;

    Math::Vec3<T> phase1;  //!< Phase direction vector (spins with main spin)

    Math::Vec3<T> position2;  //!< Central position of generation 2 sphere [\f$m\f$]
    Math::Vec3<T> position3;  //!< Central position of generation 3 sphere [\f$m\f$]

    Math::Vec3<T> accelGravity1;  //!< Acceleration acting on generation 1 sphere [\f$\frac{rad}{s}\f$]
    Math::Vec3<T> accelGravity2;  //!< Acceleration acting on generation 2 sphere [\f$\frac{rad}{s}\f$]

    /*!
     * \brief Angular velocity of changing direction (curving) of main move [\f$\frac{rad}{s}\f$]
     * \note Used within generation 1 neutrino state only
     */
    Math::Vec3<T> curvingVelocity1;

    /*!
     * \brief Angular velocity of changing direction (curving) of main move [\f$\frac{rad}{s}\f$]
     * \note Used within generation 2 or 3 neutrino state
     * \note Acts only on velocity 1 direction
     */
    Math::Vec3<T> curvingVelocity21;

    /*!
     * \brief Angular velocity of changing direction (curving) of main move [\f$\frac{rad}{s}\f$]
     * \note Used within generation 2 or 3 neutrino state
     * \note Acts only on both, velocity 1 and velocity 2 directions
     */
    Math::Vec3<T> curvingVelocity22;

    /*!
     * \brief Default constructor
     */
    template <typename = std::enable_if_t<std::is_floating_point<T>::value>>
    inline NeutrinoTimeStamp()
        : TimeStamp<T>()
        , flags(0U)
        , moveVelocity1()
        , moveVelocity21()
        , moveVelocity22()
        , moveVelocity31()
        , moveVelocity32()
        , moveVelocity33()
        , spinVelocity1()
        , spinVelocity2()
        , spinVelocity3()
        , phase1()
        , position2()
        , position3()
        , accelGravity1()
        , accelGravity2()
        , curvingVelocity1()
        , curvingVelocity21()
        , curvingVelocity22()
    {
    }

    uint32_t initGeneration1(const Math::Vec3<T> &_accelGravity1, const Constants<T> &_physics);
    uint32_t initGeneration2(const Math::Vec3<T> &_accelGravity2, const Constants<T> &_physics);

    std::list<std::pair<std::string, std::string>> getDetails(const T _elementRadius) const;

    inline bool isGeneration2() const;
    inline bool isGeneration3() const;

    inline T getRadius2(const T _elementRadius) const;
    inline T getRadius3(const T _elementRadius) const;

    static T getArea1(const T _elementRadius);
    inline T getArea2(const T _elementRadius) const;
    inline T getArea3(const T _elementRadius) const;

    std::pair<uint32_t, Math::Vec3<T>> getEnergy(const T _elementRadius) const;
    T getTotalEnergy(const T _elementRadius) const;

    Math::Vec3<T> getCurvingHook1() const;
    Math::Vec3<T> getCurvingHook2() const;
    Math::Vec3<T> getCurvingHook21() const;

    T getCurvingRadius1() const;
    T getCurvingRadius2() const;

    NeutrinoTimeStamp<T> moved(const T _timeDelta) const;

    T curvingAngleRad(const T _timeDelta) const;
    T curvingTimeDuration(const T _angleRad) const;

    std::pair<NeutrinoTimeStamp<T>, bool>
    movedToEventSource(const T _universeVelocity, const T _eventTimeStamp, const Math::Vec3<T> &_eventPosition) const;

    static bool compareMoved(const NeutrinoTimeStamp<T> &_previous, const NeutrinoTimeStamp<T> &_next);

    /*!
     * \brief Create copy of this object in different precision
     * \tparam T2  Other simulation template floating point type
     * \returns Copy of this object in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    NeutrinoTimeStamp<T2> createCopy() const
    {
        NeutrinoTimeStamp<T2> result;
        result.flags = flags;
        result.timeStamp = TimeStamp<T>::timeStamp;
        result.position = TimeStamp<T>::position.template converted<T2>();
        result.moveVelocity1 = moveVelocity1.template converted<T2>();
        result.moveVelocity21 = moveVelocity21.template converted<T2>();
        result.moveVelocity22 = moveVelocity22.template converted<T2>();
        result.moveVelocity31 = moveVelocity31.template converted<T2>();
        result.moveVelocity32 = moveVelocity32.template converted<T2>();
        result.moveVelocity33 = moveVelocity33.template converted<T2>();
        result.spinVelocity1 = spinVelocity1.template converted<T2>();
        result.spinVelocity2 = spinVelocity2.template converted<T2>();
        result.spinVelocity3 = spinVelocity3.template converted<T2>();
        result.phase1 = phase1.template converted<T2>();
        result.position2 = position2.template converted<T2>();
        result.position3 = position3.template converted<T2>();
        result.accelGravity1 = accelGravity1.template converted<T2>();
        result.accelGravity2 = accelGravity2.template converted<T2>();
        result.curvingVelocity1 = curvingVelocity1.template converted<T2>();
        result.curvingVelocity21 = curvingVelocity21.template converted<T2>();
        result.curvingVelocity22 = curvingVelocity22.template converted<T2>();
        return result;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Initialize generation 1
 * \tparam T Template floating point type
 * \param _accelGravity1 Acceleration acting on generation 1 sphere [\f$\frac{rad}{s}\f$]
 * \param _physics Universe constants
 * \returns Flags buffer
 * \sa Universe1::Simulation::GravityNeutrino::NeutrinoFlag
 */
template <typename T>
uint32_t NeutrinoTimeStamp<T>::initGeneration1(const Math::Vec3<T> &_accelGravity1, const Constants<T> &_physics)
{
    flags = 0U;
    spinVelocity2.clear();
    spinVelocity3.clear();
    accelGravity1.clear();
    accelGravity2.clear();
    curvingVelocity1.clear();
    curvingVelocity21.clear();
    curvingVelocity22.clear();
    position2.clear();
    position3.clear();
    moveVelocity21.clear();
    moveVelocity22.clear();
    moveVelocity31.clear();
    moveVelocity32.clear();
    moveVelocity33.clear();

    if (spinVelocity1.isNull())
        flags |= NeutrinoNullSpin1;

    if (!Type::equals<T>(moveVelocity1.length(), _physics.universeVelocity) ||
        (!spinVelocity1.isNull() && !moveVelocity1.isParallel(spinVelocity1)))
        flags |= NeutrinoInvalidMove1;

    if (flags != 0U)
        return flags;

    accelGravity1 = _accelGravity1;

    const Math::Vec3<T> accelGravity1Dir = accelGravity1.projected(moveVelocity1);
    const Math::Vec3<T> accelGravity1Side = accelGravity1 - accelGravity1Dir;
    const T accelGravity1SideSize = accelGravity1Side.length();
    if (Type::isNull<T>(accelGravity1SideSize))
    {
        // Generation 1 straight move
        flags = NeutrinoGeneration1StraightMove;
        return flags;
    }

    const T curvingRadius = _physics.universeVelocity * _physics.universeVelocity / accelGravity1SideSize;

    const Math::Vec3<T> normalCurvingVelocity1 = Math::Vec3<T>::cross(moveVelocity1, accelGravity1Side).normalized();

    curvingVelocity1 = normalCurvingVelocity1 * (_physics.universeVelocity / curvingRadius);

    if (Type::equals<T>(_physics.elementRadius, curvingRadius))  // Generation 1/2 border
    {
        flags = NeutrinoGeneration12;
        position2 = TimeStamp<T>::position + accelGravity1Side.normalized() * curvingRadius;
        moveVelocity21 = moveVelocity1;
        return flags;
    }
    else if (_physics.elementRadius < curvingRadius)  // Generation 1
    {
        flags = NeutrinoGeneration1;
        return flags;
    }

    // Generation 2

    position2 = TimeStamp<T>::position + accelGravity1Side.normalized() * curvingRadius;

    const T radius2 = _physics.elementRadius - curvingRadius;
    const T tmpA = (radius2 * radius2) /
        (_physics.elementRadius * _physics.elementRadius * curvingRadius * spinVelocity1.length());
    const T tmpB = Const::T_1<T>() / (tmpA * tmpA);

    T root[3];
    int foundIdx = -1;

    const int equationRoots = Type::solvePolynom3(
        root[0], root[1], root[2], _physics.universeVelocity, tmpB, -_physics.universeVelocity * tmpB);
    for (int i = 0; i < equationRoots; ++i)
    {
        if (Type::isPositive<T>(root[i]) && root[i] < _physics.universeVelocity)
        {
            if (foundIdx == -1 || root[i] > root[foundIdx])
                foundIdx = i;
        }
    }

    if (foundIdx == -1)
    {
        flags = (NeutrinoGeneration12 | NeutrinoErrorPolynom);
        return flags;
    }

    flags = NeutrinoGeneration2;
    moveVelocity21 = moveVelocity1.normalized() * root[foundIdx];
    moveVelocity22 = normalCurvingVelocity1 *
        (moveVelocity1.cosAngle(spinVelocity1) *
         std::sqrt(_physics.universeVelocity * _physics.universeVelocity - root[foundIdx] * root[foundIdx]));

    spinVelocity2 = normalCurvingVelocity1 * (root[foundIdx] / curvingRadius);

    curvingVelocity21 = normalCurvingVelocity1 * (root[foundIdx] / curvingRadius);
    return flags;
}

/*!
 * \brief Initialize generation 2
 * \tparam T Template floating point type
 * \param _accelGravity2 Acceleration acting on generation 2 sphere [\f$\frac{rad}{s}\f$]
 * \param _physics Universe constants
 * \returns Flags buffer
 * \sa Universe1::Simulation::GravityNeutrino::NeutrinoFlag
 */
template <typename T>
uint32_t NeutrinoTimeStamp<T>::initGeneration2(const Math::Vec3<T> &_accelGravity2, const Constants<T> &_physics)
{
    if (flags != NeutrinoGeneration2)
        return NeutrinoErrorInitGeneration2;

    accelGravity2 = _accelGravity2;

    const Math::Vec3<T> accelGravity2Side = accelGravity2.projected(moveVelocity21);
    const T accelGravity2SideSize = accelGravity2Side.length();

    if (Type::isNull<T>(accelGravity2SideSize))
    {
        flags |= NeutrinoStraightMove;
        return flags;
    }

    const T radius2 = _physics.elementRadius - position2.distanceToPoint(TimeStamp<T>::position);
    const T curvingRadius2 = moveVelocity22.lengthSquared() / accelGravity2SideSize;

    const Math::Vec3<T> normalCurvingVelocity2 = Math::Vec3<T>::cross(moveVelocity22, accelGravity2Side).normalized();

    const T moveVelocity22Size = moveVelocity22.length();

    curvingVelocity22 = normalCurvingVelocity2 * (moveVelocity22Size / curvingRadius2);

    if (Type::equals<T>(radius2, curvingRadius2))  // Generation 2/3 border
    {
        flags |= NeutrinoGeneration23;
        position3 = position2 + accelGravity2Side.normalized() * curvingRadius2;
        moveVelocity31 = moveVelocity21;
        moveVelocity32 = moveVelocity22;
        return flags;
    }
    else if (radius2 < curvingRadius2)  // Generation 2
        return flags;

    // Generation 3
    position3 = position2 + accelGravity2Side.normalized() * curvingRadius2;

    const T radius3 = radius2 - curvingRadius2;
    const T tmpA = (radius3 * radius3) / (radius2 * radius2 * curvingRadius2 * spinVelocity2.length());
    const T tmpB = Const::T_1<T>() / (tmpA * tmpA);

    T root[3];
    int foundIdx = -1;

    const int equationRoots =
        Type::solvePolynom3(root[0], root[1], root[2], moveVelocity22Size, tmpB, -moveVelocity22Size * tmpB);
    for (int i = 0; i < equationRoots; ++i)
    {
        if (Type::isPositive<T>(root[i]) && root[i] < moveVelocity22Size)
        {
            if (foundIdx == -1 || root[i] > root[foundIdx])
                foundIdx = i;
        }
    }

    if (foundIdx == -1)
    {
        flags = (NeutrinoGeneration23 | NeutrinoErrorPolynom);
        return flags;
    }

    flags = NeutrinoGeneration3;

    moveVelocity31 = moveVelocity21;
    moveVelocity32 = moveVelocity22.normalized() * root[foundIdx];
    moveVelocity33 = normalCurvingVelocity2 *
        (moveVelocity22.cosAngle(spinVelocity2) *
         std::sqrt(moveVelocity22Size * moveVelocity22Size - root[foundIdx] * root[foundIdx]));

    spinVelocity3 = normalCurvingVelocity2 * (root[foundIdx] / curvingRadius2);

    return flags;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef DOXYGEN_SKIP

inline void testNeutrinoFlag(
    uint32_t &_flags, bool &_isEmpty, std::stringstream &_ss, const uint32_t _flag, const std::string &_text)
{
    if ((_flags & _flag) != 0U)
    {
        if (_isEmpty)
            _isEmpty = false;
        else
            _ss << " | ";
        _flags &= (~_flag);
        _ss << _text;
    }
}

template <typename T>
std::pair<std::string, std::string> makeDetail(const std::string &_name, const T &_value, const std::string &_unit = "")
{
    std::stringstream ss;
    ss << _value;
    if (!_unit.empty())
        ss << " [" << _unit << ']';
    return {_name, ss.str()};
}

template <typename T>
std::pair<std::string, std::string>
makeDetail(const std::string &_name, const Math::Vec3<T> &_vec, const std::string &_unit = "")
{
    std::stringstream ss;
    ss << _vec;
    if (!_unit.empty())
        ss << " [" << _unit << ']';
    return {_name, ss.str()};
}

template <typename T>
std::pair<std::string, std::string>
makeLengthDetail(const std::string &_name, const Math::Vec3<T> &_vec, const std::string &_unit = "")
{
    std::stringstream ss;
    ss << _vec << " |" << _vec.length() << "|";
    if (!_unit.empty())
        ss << " [" << _unit << ']';
    return {_name, ss.str()};
}

#endif  // DOXYGEN_SKIP

/*!
 * \brief Getter for neutrino text details
 * \param _elementRadius Generation 1 sphere radius (Universe constant) [\f$m\f$]
 * \return
 */
template <typename T>
std::list<std::pair<std::string, std::string>> NeutrinoTimeStamp<T>::getDetails(const T _elementRadius) const
{
    std::string stateName;
    switch (flags)
    {
    case NeutrinoGeneration1: stateName = "Generation 1"; break;
    case NeutrinoGeneration1StraightMove: stateName = "Generation 1 - straight move"; break;
    case NeutrinoGeneration12: stateName = "Generation 1-2 border"; break;
    case NeutrinoGeneration2: stateName = "Generation 2"; break;
    case NeutrinoGeneration2StraightMove: stateName = "Generation 2 - straight move"; break;
    case NeutrinoGeneration23: stateName = "Generation 2-3 border"; break;
    case NeutrinoGeneration3: stateName = "Generation 3"; break;
    default:
        if (flags == 0U)
        {
            return {{"Error state", "NULL"}};
        }
        else
        {
            uint32_t tmp = flags;
            bool emptyState = true;
            bool emptyError = true;
            std::stringstream ssState;
            std::stringstream ssError;

            testNeutrinoFlag(tmp, emptyState, ssState, NeutrinoStraightMove, "Straight move");
            testNeutrinoFlag(tmp, emptyState, ssState, NeutrinoGeneration1, "Generation 1");
            testNeutrinoFlag(tmp, emptyState, ssState, NeutrinoGeneration2, "Generation 2");
            testNeutrinoFlag(tmp, emptyState, ssState, NeutrinoGeneration3, "Generation 3");

            testNeutrinoFlag(tmp, emptyError, ssError, NeutrinoInvalidMove1, "Invalid generation 1 move");
            testNeutrinoFlag(tmp, emptyError, ssError, NeutrinoNullSpin1, "Null generation 1 spin");
            testNeutrinoFlag(tmp, emptyError, ssError, NeutrinoErrorPolynom, "Polynom root calculation problem");
            testNeutrinoFlag(tmp, emptyError, ssError, NeutrinoErrorInitGeneration2, "Initialize generation 2");

            if (tmp != 0U)
            {
                if (emptyError)
                    emptyError = false;
                else
                    ssError << " | ";
                ssError << "Flags [" << flags << "], unknown flags [" << tmp << "]";
            }

            std::list<std::pair<std::string, std::string>> result;
            if (emptyState && emptyError)
            {
                std::stringstream ss;
                ss << "Invalid flag [" << flags << ']';
                result.push_back({"Error state", ss.str()});
            }
            else if (emptyState && !emptyError)
                result.push_back({"Error state", ssError.str()});
            if (!emptyState && emptyError)
                result.push_back({"Error state", ssState.str()});
            else
            {
                result.push_back({"State", ssState.str()});
                result.push_back({"Error", ssError.str()});
            }
            return result;
        }
    }

    std::list<std::pair<std::string, std::string>> result;
    result.push_back({"State", stateName});
    result.push_back(makeDetail("Time-stamp", TimeStamp<T>::timeStamp, "s"));

    result.push_back(makeDetail("Position 1", TimeStamp<T>::position));
    if (isGeneration2())
        result.push_back(makeDetail("Position 2", position2));
    if (isGeneration3())
        result.push_back(makeDetail("Position 3", position3));

    result.push_back(makeDetail("Radius 1", _elementRadius, "m"));
    if (isGeneration2())
        result.push_back(makeDetail("Radius 2", getRadius2(_elementRadius), "m"));
    if (isGeneration3())
        result.push_back(makeDetail("Radius 3", getRadius3(_elementRadius), "m"));

    if (isGeneration3())
    {
        result.push_back(makeLengthDetail("Velocity 1 - start", moveVelocity1, "m/s"));
        result.push_back(makeLengthDetail("Velocity 1", moveVelocity31, "m/s"));
        result.push_back(makeLengthDetail("Velocity 2", moveVelocity32, "m/s"));
        result.push_back(makeLengthDetail("Velocity 3", moveVelocity33, "m/s"));
        result.push_back(makeLengthDetail("Velocity Main", (moveVelocity31 + moveVelocity32 + moveVelocity33), "m/s"));
    }
    else if (isGeneration2())
    {
        result.push_back(makeLengthDetail("Velocity 1 - start", moveVelocity1, "m/s"));
        result.push_back(makeLengthDetail("Velocity 1", moveVelocity21, "m/s"));
        result.push_back(makeLengthDetail("Velocity 2", moveVelocity22, "m/s"));
        result.push_back(makeLengthDetail("Velocity Main", (moveVelocity21 + moveVelocity22), "m/s"));
    }
    else
    {
        result.push_back(makeLengthDetail("Velocity 1", moveVelocity1, "m/s"));
    }

    result.push_back(makeDetail("Phase 1", phase1));
    result.push_back(makeLengthDetail("Spin 1", spinVelocity1, "rad/s"));
    if (isGeneration2())
        result.push_back(makeLengthDetail("Spin 2", spinVelocity2, "rad/s"));
    if (isGeneration3())
        result.push_back(makeLengthDetail("Spin 3", spinVelocity3, "rad/s"));

    const std::pair<uint32_t, Math::Vec3<T>> energy = getEnergy(_elementRadius);
    result.push_back(makeDetail("Energy 1", energy.second.x, "(rad*m^3)/s"));
    if (isGeneration2())
    {
        result.push_back(makeDetail("Energy 2", energy.second.y, "(rad*m^3)/s"));

        if (isGeneration3())
            result.push_back(makeDetail("Energy 3", energy.second.z, "(rad*m^3)/s"));

        result.push_back(makeDetail("Total energy", energy.second.sum(), "(rad*m^3)/s"));
    }

    result.push_back(makeLengthDetail("Acceleration 1", accelGravity1, "m/s^2"));
    result.push_back(makeLengthDetail("Acceleration 1 - lost", accelGravity1.projected(moveVelocity1), "m/s^2"));
    result.push_back(
        makeLengthDetail("Acceleration 1 - apply", (accelGravity1 - accelGravity1.projected(moveVelocity1)), "m/s^2"));

    if (isGeneration2())
    {
        result.push_back(makeLengthDetail("Acceleration 2", accelGravity2, "m/s^2"));
        result.push_back(makeLengthDetail("Acceleration 2 - lost 1", accelGravity2.projected(moveVelocity21), "m/s^2"));
        result.push_back(makeLengthDetail("Acceleration 2 - lost 2", accelGravity2.projected(moveVelocity22), "m/s^2"));
        result.push_back(makeLengthDetail(
            "Acceleration 2 - apply",
            (accelGravity2 - accelGravity2.projected(moveVelocity21 - accelGravity2.projected(moveVelocity22))),
            "m/s^2"));
    }

    if (isGeneration2())
    {
        result.push_back(makeLengthDetail("Curving 1 spin - start", curvingVelocity1, "rad/s"));
        result.push_back(makeLengthDetail("Curving 1 spin", curvingVelocity21, "rad/s"));
        result.push_back(makeLengthDetail("Curving 2 spin", curvingVelocity22, "rad/s"));
        result.push_back(makeDetail("Curving 1 radius", getCurvingRadius1(), "m"));
        result.push_back(makeDetail("Curving 2 radius", getCurvingRadius2(), "m"));
        result.push_back(makeDetail("Curving 1 hook 1", getCurvingHook1()));
        result.push_back(makeDetail("Curving 2 hook 1", getCurvingHook21()));
        result.push_back(makeDetail("Curving 2 hook 2", getCurvingHook2()));
    }
    else
    {
        result.push_back(makeLengthDetail("Curving 1 spin", curvingVelocity1, "rad/s"));
        result.push_back(makeDetail("Curving 1 radius", getCurvingRadius1(), "m"));
        result.push_back(makeDetail("Curving 1 hook point", getCurvingHook1()));
    }

    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns flag is time-stamp is in generation 2
 * \tparam T Template floating point type
 * \returns \c true when time-stamp is in generation 2
 */
template <typename T>
inline bool NeutrinoTimeStamp<T>::isGeneration2() const
{
    switch (flags)
    {
    case NeutrinoGeneration12:
    case NeutrinoGeneration2:
    case NeutrinoGeneration2StraightMove:
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return true;
    default: break;
    }
    return false;
}

/*!
 * \brief Returns flag is time-stamp is in generation 3
 * \tparam T Template floating point type
 * \returns \c true when time-stamp is in generation 3
 */
template <typename T>
inline bool NeutrinoTimeStamp<T>::isGeneration3() const
{
    switch (flags)
    {
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return true;
    default: break;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Radius of second generation sphere
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Radius of second generation sphere
 */
template <typename T>
inline T NeutrinoTimeStamp<T>::getRadius2(const T _elementRadius) const
{
    switch (flags)
    {
    case NeutrinoGeneration2:
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return _elementRadius - position2.distanceToPoint(TimeStamp<T>::position);
    default: break;
    }
    return Const::T_0<T>();
}

/*!
 * \brief Radius of third generation sphere
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Radius of third generation sphere
 */
template <typename T>
inline T NeutrinoTimeStamp<T>::getRadius3(const T _elementRadius) const
{
    if (flags == NeutrinoGeneration3)
        return (_elementRadius - position2.distanceToPoint(TimeStamp<T>::position)) -  // radius 2
            position3.distanceToPoint(position2);
    return Const::T_0<T>();
}

/*!
 * \brief Area of generation 1 circle
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Area of generation 1 circle
 */
template <typename T>
T NeutrinoTimeStamp<T>::getArea1(const T _elementRadius)
{
    return Const::T_PI<T>() * _elementRadius * _elementRadius;
}

/*!
 * \brief Area of generation 2 circle
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Area of generation 2 circle
 */
template <typename T>
inline T NeutrinoTimeStamp<T>::getArea2(const T _elementRadius) const
{
    return getArea1(getRadius2(_elementRadius));
}

/*!
 * \brief Area of generation 3 circle
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Area of generation 3 circle
 */
template <typename T>
inline T NeutrinoTimeStamp<T>::getArea3(const T _elementRadius) const
{
    return getArea1(getRadius3(_elementRadius));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Raw energy of neutrino
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Pair of flags and generations energies
 */
template <typename T>
std::pair<uint32_t, Math::Vec3<T>> NeutrinoTimeStamp<T>::getEnergy(const T _elementRadius) const
{
    std::pair<uint32_t, Math::Vec3<T>> result = {flags, Math::Vec3<T>()};
    switch (flags)
    {
    case NeutrinoGeneration1:
    case NeutrinoGeneration12:
    case NeutrinoGeneration1StraightMove:
        result.second.x = getArea1(_elementRadius) * moveVelocity1.length() * spinVelocity1.length();
        break;
    case NeutrinoGeneration2:
    case NeutrinoGeneration23:
    case NeutrinoGeneration2StraightMove:
        result.second.x = getArea1(_elementRadius) * moveVelocity21.length() * spinVelocity1.length();
        result.second.y = getArea2(_elementRadius) * moveVelocity22.length() * spinVelocity2.length();
        break;
    case NeutrinoGeneration3:
        result.second.x = getArea1(_elementRadius) * moveVelocity31.length() * spinVelocity1.length();
        result.second.y = getArea2(_elementRadius) * moveVelocity32.length() * spinVelocity2.length();
        result.second.z = getArea3(_elementRadius) * moveVelocity33.length() * spinVelocity3.length();
        break;
    default: break;
    }
    return result;
}

/*!
 * \brief Raw total energy of neutrino
 * \tparam T Template floating point type
 * \param _elementRadius Main generation sphere radius
 * \returns Total neutrino energy
 */
template <typename T>
T NeutrinoTimeStamp<T>::getTotalEnergy(const T _elementRadius) const
{
    // return getArea1(_elementRadius) * moveVelocity1.length() * spinVelocity1.length();
    switch (flags)
    {
    case NeutrinoGeneration1:
    case NeutrinoGeneration12:
    case NeutrinoGeneration1StraightMove:
        return getArea1(_elementRadius) * moveVelocity1.length() * spinVelocity1.length();

    case NeutrinoGeneration2:
    case NeutrinoGeneration23:
    case NeutrinoGeneration2StraightMove:
        return getArea1(_elementRadius) * moveVelocity21.length() * spinVelocity1.length() +
            getArea2(_elementRadius) * moveVelocity22.length() * spinVelocity2.length();

    case NeutrinoGeneration3:
        return getArea1(_elementRadius) * moveVelocity31.length() * spinVelocity1.length() +
            getArea2(_elementRadius) * moveVelocity32.length() * spinVelocity2.length() +
            getArea3(_elementRadius) * moveVelocity33.length() * spinVelocity3.length();
    default: break;
    }
    return Const::T_0<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns imaginary hook position for curving of generation 1 move velocity
 * \tparam T Template floating point type
 * \returns Imaginary hook position for curving of generation 1 move velocity
 */
template <typename T>
Math::Vec3<T> NeutrinoTimeStamp<T>::getCurvingHook1() const
{
    switch (flags)
    {
    case NeutrinoGeneration1: {
        const Math::Vec3<T> moveNormal = moveVelocity1.normalized();
        const Math::Vec3<T> curvNormal = curvingVelocity1.normalized();
        const T moveSize = moveVelocity1.length();
        const T curvSize = curvingVelocity1.length();
        const T curvingRadius = moveSize / curvSize;
        const Math::Vec3<T> toHook = Math::Vec3<T>::cross(curvNormal, moveNormal).normalized();
        return TimeStamp<T>::position + toHook * curvingRadius;
    }
    case NeutrinoGeneration12:
    case NeutrinoGeneration2:
    case NeutrinoGeneration2StraightMove:
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return position2;
    }
    return Math::Vec3<T>();
}

/*!
 * \brief Returns imaginary hook position for curving of generation 2 move velocity velocity generation 2
 * \tparam T Template floating point type
 * \returns Imaginary hook position for curving of generation 2 move velocity
 */
template <typename T>
Math::Vec3<T> NeutrinoTimeStamp<T>::getCurvingHook2() const
{
    switch (flags)
    {
    case NeutrinoGeneration2: {
        const Math::Vec3<T> move2Normal = moveVelocity22.normalized();
        const Math::Vec3<T> curv2Normal = curvingVelocity22.normalized();
        const T move2Size = moveVelocity22.length();
        const T curv2Size = curvingVelocity22.length();
        const T curvingRadius2 = move2Size / curv2Size;
        const Math::Vec3<T> toHook2 = Math::Vec3<T>::cross(curv2Normal, move2Normal).normalized();
        return position2 + toHook2 * curvingRadius2;
    }
    break;
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return position3;
    }
    return Math::Vec3<T>();
}

/*!
 * \brief Returns imaginary hook position for curving of generation 2 move velocity generation 1
 * \tparam T Template floating point type
 * \returns Imaginary hook position for curving of generation 2 move velocity
 */
template <typename T>
Math::Vec3<T> NeutrinoTimeStamp<T>::getCurvingHook21() const
{
    switch (flags)
    {
    case NeutrinoGeneration2: {
        const Math::Vec3<T> move2Normal = moveVelocity22.normalized();
        const Math::Vec3<T> curv2Normal = curvingVelocity22.normalized();
        const T move2Size = moveVelocity22.length();
        const T curv2Size = curvingVelocity22.length();
        const T curvingRadius2 = move2Size / curv2Size;
        const Math::Vec3<T> toHook2 = Math::Vec3<T>::cross(curv2Normal, move2Normal).normalized();
        return TimeStamp<T>::position + toHook2 * curvingRadius2;
    }
    break;
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return TimeStamp<T>::position + (position3 - position2);
    }
    return Math::Vec3<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns curving radius (curving of generation 1 move velocity direction)
 * \tparam T Template floating point type
 * \returns Curving radius of generation 1 move
 */
template <typename T>
T NeutrinoTimeStamp<T>::getCurvingRadius1() const
{
    switch (flags)
    {
    case NeutrinoGeneration1: return moveVelocity1.length() / curvingVelocity1.length();
    case NeutrinoGeneration12:
    case NeutrinoGeneration2:
    case NeutrinoGeneration2StraightMove:
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return TimeStamp<T>::position.distanceToPoint(position2);
    }
    return Const::T_0<T>();
}

/*!
 * \brief Returns curving radius (curving of generation 2 move velocity direction)
 * \tparam T Template floating point type
 * \returns Curving radius of generation 2 move
 */
template <typename T>
T NeutrinoTimeStamp<T>::getCurvingRadius2() const
{
    switch (flags)
    {
    case NeutrinoGeneration2: return moveVelocity22.length() / curvingVelocity22.length();
    case NeutrinoGeneration23:
    case NeutrinoGeneration3: return position2.distanceToPoint(position3);
    }
    return Const::T_0<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns this object moved in time
 * \tparam T Template floating point type
 * \param _timeDelta Time duration of move \f$\Delta t\f$
 * \returns This object moved in time
 * \note Moved object lose values of acceleration and curving properties
 * \note Neutrinos on generation border (1-2 or 2-3) can't be moved, null object is returned
 */
template <typename T>
NeutrinoTimeStamp<T> NeutrinoTimeStamp<T>::moved(const T _timeDelta) const
{
    NeutrinoTimeStamp<T> result;
    switch (flags)
    {
    case NeutrinoGeneration1StraightMove: {
        // curvingVelocity1 == null and accelGravity1 == null
        const T spinAngleRad = spinVelocity1.length() * _timeDelta;
        const Math::Vec3<T> spinNormal = spinVelocity1.normalized();
        result.flags = flags;
        result.timeStamp = TimeStamp<T>::timeStamp + _timeDelta;
        result.position = TimeStamp<T>::position + _timeDelta * moveVelocity1;
        result.moveVelocity1 = moveVelocity1;
        result.spinVelocity1 = spinVelocity1;
        result.phase1 = phase1.rotated(spinNormal, spinAngleRad);
    }
    break;
    case NeutrinoGeneration1: {
        const Math::Vec3<T> moveNormal = moveVelocity1.normalized();
        const Math::Vec3<T> spinNormal = spinVelocity1.normalized();
        const Math::Vec3<T> curvNormal = curvingVelocity1.normalized();

        const T moveSize = moveVelocity1.length();
        const T spinSize = spinVelocity1.length();
        const T curvSize = curvingVelocity1.length();

        const T curvingRadius = moveSize / curvSize;
        const Math::Vec3<T> toHook = Math::Vec3<T>::cross(curvNormal, moveNormal).normalized();
        const Math::Vec3<T> hookPos = TimeStamp<T>::position + toHook * curvingRadius;
        const Math::Vec3<T> rotArm = TimeStamp<T>::position - hookPos;

        const T spinAngleRad = spinSize * _timeDelta;
        const T curvAngleRad = (moveSize * _timeDelta) / (Const::T_2PI<T>() * curvingRadius);

        result.flags = flags;
        result.timeStamp = TimeStamp<T>::timeStamp + _timeDelta;
        result.position = hookPos + rotArm.rotated(curvNormal, curvAngleRad);
        result.moveVelocity1 = moveVelocity1.rotated(curvNormal, curvAngleRad);
        result.spinVelocity1 = spinVelocity1.rotated(curvNormal, curvAngleRad);
        result.phase1 = ((phase1.rotated(spinNormal, spinAngleRad)).rotated(curvNormal, curvAngleRad)).normalized();

        // Maybe repair size of vector, length offset may come form rotation
        // result.moveVelocity1 = (moveVelocity1.rotated(curvNormal, curvAngleRad)).normalized() * moveSize;
        // result.spinVelocity1 = (spinVelocity1.rotated(curvNormal, curvAngleRad)).normalized() * spinSize;
    }
    break;

    case NeutrinoGeneration2StraightMove: {
        // curvingVelocity22 == null
        const Math::Vec3<T> spin1Normal = spinVelocity1.normalized();
        const Math::Vec3<T> curv1Normal = curvingVelocity21.normalized();

        const T move1Size = moveVelocity21.length();
        const T spin1Size = spinVelocity1.length();

        const T curvingRadius1 = position2.distanceToPoint(TimeStamp<T>::position);
        const Math::Vec3<T> rotArm1 = TimeStamp<T>::position - position2;

        const T spinAngleRad = spin1Size * _timeDelta;
        const T curvAngleRad = (move1Size * _timeDelta) / (Const::T_2PI<T>() * curvingRadius1);

        result.flags = flags;
        result.timeStamp = TimeStamp<T>::timeStamp + _timeDelta;
        result.position = position2 + rotArm1.rotated(curv1Normal, curvAngleRad) + moveVelocity22 * _timeDelta;

        result.moveVelocity1 = moveVelocity1.rotated(curv1Normal, curvAngleRad);
        result.moveVelocity21 = moveVelocity21.rotated(curv1Normal, curvAngleRad);
        result.moveVelocity22 = moveVelocity22;

        result.spinVelocity1 = spinVelocity1.rotated(curv1Normal, curvAngleRad);
        result.spinVelocity2 = spinVelocity2;

        result.phase1 = ((phase1.rotated(spin1Normal, spinAngleRad)).rotated(curv1Normal, curvAngleRad)).normalized();

        result.position2 = position2 + moveVelocity22 * _timeDelta;
    }
    break;

    case NeutrinoGeneration2: {
        const Math::Vec3<T> move2Normal = moveVelocity22.normalized();
        const Math::Vec3<T> spin1Normal = spinVelocity1.normalized();
        const Math::Vec3<T> curv1Normal = curvingVelocity21.normalized();
        const Math::Vec3<T> curv2Normal = curvingVelocity22.normalized();

        const T move1Size = moveVelocity21.length();
        const T move2Size = moveVelocity22.length();
        const T spin1Size = spinVelocity1.length();
        const T curv2Size = curvingVelocity22.length();

        const T curvingRadius1 = position2.distanceToPoint(TimeStamp<T>::position);
        const T curvingRadius2 = move2Size / curv2Size;

        const Math::Vec3<T> toHook2 = Math::Vec3<T>::cross(curv2Normal, move2Normal).normalized();
        const Math::Vec3<T> hookPos2 = position2 + toHook2 * curvingRadius2;

        const Math::Vec3<T> rotArm1 = TimeStamp<T>::position - position2;
        const Math::Vec3<T> rotArm2 = position2 - hookPos2;

        const T spinAngleRad = spin1Size * _timeDelta;
        const T curv1AngleRad = (move1Size * _timeDelta) / (Const::T_2PI<T>() * curvingRadius1);
        const T curv2AngleRad = (move2Size * _timeDelta) / (Const::T_2PI<T>() * curvingRadius2);

        result.flags = flags;
        result.timeStamp = TimeStamp<T>::timeStamp + _timeDelta;

        result.position2 = hookPos2 + rotArm2.rotated(curv2Normal, curv2AngleRad);
        result.position = result.position2 + rotArm1.rotated(curv1Normal, curv1AngleRad);  // using calculated 2

        result.moveVelocity1 = moveVelocity1.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);

        result.moveVelocity21 = moveVelocity21.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);

        result.moveVelocity22 = moveVelocity22.rotated(curv2Normal, curv2AngleRad);

        result.spinVelocity1 = spinVelocity1.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);

        result.spinVelocity2 = spinVelocity2.rotated(curv2Normal, curv2AngleRad);

        result.phase1 = phase1.rotated(spin1Normal, spinAngleRad)
                            .rotated(curv1Normal, curv1AngleRad)
                            .rotated(curv2Normal, curv2AngleRad)
                            .normalized();
    }
    break;

    case NeutrinoGeneration3: {
        // const Math::Vec3<T> move1Normal = moveVelocity31.normalized();
        // const Math::Vec3<T> move2Normal = moveVelocity32.normalized();
        // const Math::Vec3<T> move3Normal = moveVelocity33.normalized();
        const Math::Vec3<T> spin1Normal = spinVelocity1.normalized();
        const Math::Vec3<T> curv1Normal = curvingVelocity21.normalized();
        const Math::Vec3<T> curv2Normal = curvingVelocity22.normalized();

        const T move1Size = moveVelocity31.length();
        const T move2Size = moveVelocity32.length();
        // const T move3Size = moveVelocity33.length();
        const T spin1Size = spinVelocity1.length();
        // const T curv1Size = curvingVelocity21.length();
        // const T curv2Size = curvingVelocity22.length();

        // const T curvingRadius1 = move1Size / curv1Size;
        const T curvingRadius1 = position2.distanceToPoint(TimeStamp<T>::position);
        const T curvingRadius2 = position3.distanceToPoint(position2);

        const Math::Vec3<T> rotArm1 = TimeStamp<T>::position - position2;
        const Math::Vec3<T> rotArm2 = position2 - position3;

        const T spinAngleRad = spin1Size * _timeDelta;
        const T curv1AngleRad = (move1Size * _timeDelta) / (Const::T_2PI<T>() * curvingRadius1);
        const T curv2AngleRad = (move2Size * _timeDelta) / (Const::T_2PI<T>() * curvingRadius2);

        // const Math::Vec3<T> rotArm22 = rotArm2.rotated(curv1Normal, curv1AngleRad);

        result.flags = flags;
        result.timeStamp = TimeStamp<T>::timeStamp + _timeDelta;

        // Ugly approximation of new position
        result.position3 = position3 + moveVelocity33 * _timeDelta;
        result.position2 = position3 + rotArm2.rotated(curv2Normal, curv2AngleRad) + moveVelocity33 * _timeDelta;
        result.position = result.position2 + rotArm1.rotated(curv1Normal, curv1AngleRad) + moveVelocity33 * _timeDelta;

        result.moveVelocity1 = moveVelocity1.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);
        result.moveVelocity21 = moveVelocity21.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);
        result.moveVelocity22 = moveVelocity22.rotated(curv2Normal, curv2AngleRad);
        result.moveVelocity31 = moveVelocity31.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);
        result.moveVelocity32 = moveVelocity32.rotated(curv2Normal, curv2AngleRad);
        result.moveVelocity33 = moveVelocity33;

        result.spinVelocity1 = spinVelocity1.rotated(curv1Normal, curv1AngleRad).rotated(curv2Normal, curv2AngleRad);
        result.spinVelocity2 = spinVelocity2.rotated(curv2Normal, curv2AngleRad);
        result.spinVelocity3 = spinVelocity3;

        result.phase1 = phase1.rotated(spin1Normal, spinAngleRad)
                            .rotated(curv1Normal, curv1AngleRad)
                            .rotated(curv2Normal, curv2AngleRad)
                            .normalized();
    }
    break;
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns maximum angle done by curving direction of move during given time
 * \tparam T Template floating point type
 * \param _timeDelta Time duration of move
 * \returns Maximum angle done by curving direction of move
 */
template <typename T>
T NeutrinoTimeStamp<T>::curvingAngleRad(const T _timeDelta) const
{
    if (Type::isNull(_timeDelta))
        return Const::T_0<T>();
    switch (flags)
    {
    case NeutrinoGeneration1:
    case NeutrinoGeneration12:
    case NeutrinoGeneration2StraightMove: return curvingVelocity1.length() / _timeDelta;
    case NeutrinoGeneration2:
    case NeutrinoGeneration23:
    case NeutrinoGeneration3:
        return std::max(curvingVelocity21.length() / _timeDelta, curvingVelocity22.length() / _timeDelta);
    default: break;
    }
    return Const::T_0<T>();
}
/*!
 * \brief Returns time duration that is needed to curve (turn) move direction by given angle
 * \tparam T Template floating point type
 * \param _angleRad Curving angle on radians
 * \returns Time duration that is needed to curve move direction by given angle
 * \note For second and third generation will be lower (minimum) time duration returned
 */
template <typename T>
T NeutrinoTimeStamp<T>::curvingTimeDuration(const T _angleRad) const
{
    switch (flags)
    {
    case NeutrinoGeneration1:
    case NeutrinoGeneration12:
    case NeutrinoGeneration2StraightMove: return _angleRad / curvingVelocity1.length();
    case NeutrinoGeneration2:
    case NeutrinoGeneration23:
    case NeutrinoGeneration3:
        return std::min(_angleRad / curvingVelocity21.length(), _angleRad / curvingVelocity22.length());
    default: break;
    }
    return Const::T_0<T>();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Returns this object moved in time to position from where gravitation wave hits event
 * \tparam T Template floating point type
 * \param _universeVelocity Speed of the Universe
 * \param _eventTimeStamp Time-stamp of event
 * \param _eventPosition Event location
 * \returns Pair of this object moved in time to position from where gravitation wave hits event and success flag
 */
template <typename T>
std::pair<NeutrinoTimeStamp<T>, bool> NeutrinoTimeStamp<T>::movedToEventSource(
    const T _universeVelocity, const T _eventTimeStamp, const Math::Vec3<T> &_eventPosition) const
{
    T time1Add = Const::T_0<T>();
    T timeHit = TimeStamp<T>::getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);
    if (Type::equals<T>(timeHit, _eventTimeStamp))
        return {NeutrinoTimeStamp<T>(*this), true};

    T time1Diff = _eventTimeStamp - timeHit;

    T time2Add = time1Diff;
    NeutrinoTimeStamp<T> tmpObject = moved(time2Add);
    timeHit = tmpObject.getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);

    if (Type::equals<T>(timeHit, _eventTimeStamp))
        return {tmpObject, true};

    T time2Diff = _eventTimeStamp - timeHit;

    for (int step = 3; step < 20; ++step)
    {
        const T time3Add = time1Add - (time1Add - time2Add) * time1Diff / (time1Diff - time2Diff);

        tmpObject = moved(time3Add);
        timeHit = tmpObject.getTimeWhenWaveHitEvent(_universeVelocity, _eventPosition);

        if (Type::equals<T>(timeHit, _eventTimeStamp))
            return {tmpObject, true};

        time1Add = time2Add;
        time2Add = time3Add;
        time1Diff = time2Diff;
        time2Diff = (_eventTimeStamp - timeHit);
    }
    return {NeutrinoTimeStamp<T>(), false};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Compare previous and moved object
 * \tparam T Template floating point type
 * \param _previous First object
 * \param _next Second object
 * \returns \c true when time-stamp and position are equal
 * \note All other properties ignored (TODO)
 */
template <typename T>
bool NeutrinoTimeStamp<T>::compareMoved(const NeutrinoTimeStamp<T> &_previous, const NeutrinoTimeStamp<T> &_next)
{
    const T stepDuration = _next.timeStamp - _previous.timeStamp;
    const NeutrinoTimeStamp<T> movedObject = _previous.moved(stepDuration);
    return Type::equals(_next.timeStamp, movedObject.timeStamp) && _next.position == movedObject.position;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace GravityNeutrino
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOTIMESTAMP_H
