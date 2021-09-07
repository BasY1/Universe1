/*!
 * \file simulation/neutrino/neutrinoobject.h
 * \author Michal Steller
 * \brief Neutrino object template implementation
 */

#ifndef UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOOBJECT_H
#define UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOOBJECT_H

#include "../objecthistory.h"
#include "neutrinotimestamp.h"

namespace Universe1 {
namespace Simulation {
namespace GravityNeutrino {

/*!
 * \brief Neutrino object
 * \tparam T Template floating point type
 */
template <typename T>
struct NeutrinoObject : public ObjectHistory<T, NeutrinoTimeStamp<T>>
{
    static const bool usesHistory = true;  //!< Uses history
    static uint32_t testConstants(const Constants<T> &_physics);

    /*!
     * \brief Default constructor
     * \param _objectID Object's ID
     */
    inline NeutrinoObject(const size_t _objectID)
        : ObjectHistory<T, NeutrinoTimeStamp<T>>(_objectID)
    {
    }

    /*!
     * \brief Constructor
     * \param _objectID Object's ID
     * \param _size History buffer size
     */
    inline NeutrinoObject(const size_t _objectID, const size_t _size)
        : ObjectHistory<T, NeutrinoTimeStamp<T>>(_objectID, _size)
    {
    }

    inline T currentCurvingTimeDuration(const T _angleRad) const;

    inline NeutrinoObject<T> clone(const size_t _objectID, const size_t _size) const;

    bool initStep(const std::vector<NeutrinoObject<T>> &_objects, const Constants<T> &_physics);

    std::vector<std::pair<size_t, size_t>> stepsForSphereSource(const Constants<T> &_physics,
                                                                const T _eventTimeStamp,
                                                                const Math::Sphere<T> &_eventSphere) const;

    std::pair<std::vector<std::pair<size_t, size_t>>, Math::Vec3<T>> accelForSphereSource(
        const Constants<T> &_physics, const T _eventTimeStamp, const Math::Sphere<T> &_eventSphere) const;

    bool loadPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out) const;
    bool loadPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out) const;

    std::pair<bool, QVector3D> loadPosition2(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadPosition3(const T _timeStamp) const;

    std::pair<bool, QVector3D> loadVelocity1(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadVelocity2(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadVelocity3(const T _timeStamp) const;

    std::pair<bool, QVector3D> loadSpin1(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadSpin2(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadSpin3(const T _timeStamp) const;

    std::pair<bool, QVector3D> loadAccel1(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadAccel2(const T _timeStamp) const;

    std::pair<bool, QVector3D> loadCurving1(const T _timeStamp) const;
    std::pair<bool, QVector3D> loadCurving2(const T _timeStamp) const;

    /*!
     * \brief Create copy of this object in different precision
     * \tparam T2  Other simulation template floating point type
     * \returns Copy of this object in different precision
     */
    template <typename T2, typename = std::enable_if<std::is_floating_point<T2>::value>>
    NeutrinoObject<T2> createCopy() const
    {
        NeutrinoObject<T2> result(ObjectHistory<T, NeutrinoTimeStamp<T>>::m_objectID);
        result.initHistory(ObjectHistory<T, NeutrinoTimeStamp<T>>::m_filled,
                           ObjectHistory<T, NeutrinoTimeStamp<T>>::m_currentIdx,
                           ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.size());

        for (size_t i = 0; i < ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.size(); ++i)
            result.history()[i] = ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history[i].template createCopy<T2>();

        return result;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Test physics constants, returns \c true when gravitational constant and speed of the universe are positive
 * \tparam T Template floating point type
 * \param _physics Physics constants to test
 * \returns Zero when gravitational constant has positive value or error flags
 */
template <typename T>
uint32_t NeutrinoObject<T>::testConstants(const Constants<T> &_physics)
{
    return (Type::isPositive(_physics.universeVelocity) ? 0U : static_cast<uint32_t>(Const_UniverseVelocity)) |
        (Type::isPositive(_physics.gravityConstant) ? 0U : static_cast<uint32_t>(Const_GravityConstant)) |
        (Type::isPositive(_physics.elementRadius) ? 0U : static_cast<uint32_t>(Const_ElementRadius));
}

/*!
 * \brief Returns time duration that is needed to curve (turn) move direction by given angle
 * \tparam T Template floating point type
 * \param _angleRad Curving angle on radians
 * \returns Duration that is needed to curve (turn) move direction
 * \sa Universe1::Simulation::GravityNeutrino::NeutrinoTimeStamp::curvingTimeDuration(const T) const
 */
template <typename T>
inline T NeutrinoObject<T>::currentCurvingTimeDuration(const T _angleRad) const
{
    return ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.empty()
        ? -Const::T_1<T>()
        : ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.at(ObjectHistory<T, NeutrinoTimeStamp<T>>::m_currentIdx)
              .curvingTimeDuration(_angleRad);
}

/*!
 * \brief Create clone of this object with new ID and history size
 * \tparam T Template floating point type
 * \param _objectID New object ID
 * \param _size New object history size (if equals zero object keeps history size)
 * \returns Clone of this object
 */
template <typename T>
inline NeutrinoObject<T> NeutrinoObject<T>::clone(const size_t _objectID, const size_t _size) const
{
    NeutrinoObject<T> result(_objectID,
                             std::max(_size, ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.size()));
    ObjectHistory<T, NeutrinoTimeStamp<T>>::cloneHistory(result);
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Calculate current move acceleration, force direction points to current object position
 * \tparam T Template floating point type
 * \param _objects List of all simulated objects
 * \param _physics Physics constants
 * \returns Success flag
 */
template <typename T>
bool NeutrinoObject<T>::initStep(const std::vector<NeutrinoObject<T>> &_objects, const Constants<T> &_physics)
{
    NeutrinoTimeStamp<T> *curTS = ObjectHistory<T, NeutrinoTimeStamp<T>>::current();
    if (curTS == nullptr)
        return false;

    const Math::Sphere curG1Sphere(_physics.elementRadius, curTS->position);
    Math::Sphere<T> waveSphere;
    Math::Vec3<T> accel;

    for (const NeutrinoObject<T> &obj : _objects)
    {
        const std::pair<std::vector<std::pair<size_t, size_t>>, Math::Vec3<T>> tmp =
            obj.accelForSphereSource(_physics, curTS->timeStamp, curG1Sphere);
        if (tmp.first.empty())
            return false;
        accel += tmp.second;
    }

    const uint32_t init1Flags = curTS->initGeneration1(accel, _physics);
    if (init1Flags == NeutrinoGeneration1 || init1Flags == NeutrinoGeneration1StraightMove ||
        init1Flags == NeutrinoGeneration12)
        return true;

    if (init1Flags != NeutrinoGeneration2)
        return false;

    const Math::Sphere curG2Sphere(curTS->getRadius2(_physics.elementRadius), curTS->position2);

    accel.clear();
    for (const NeutrinoObject<T> &obj : _objects)
    {
        const std::pair<std::vector<std::pair<size_t, size_t>>, Math::Vec3<T>> tmp =
            obj.accelForSphereSource(_physics, curTS->timeStamp, curG2Sphere);
        if (tmp.first.empty())
            return false;
        accel += tmp.second;
    }

    const uint32_t init2Flags = curTS->initGeneration2(accel, _physics);
    return (init2Flags == NeutrinoGeneration2 || init2Flags == NeutrinoGeneration2StraightMove ||
            init2Flags == NeutrinoGeneration23 || init2Flags == NeutrinoGeneration3);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Prepare vector of offsets (pairs of start - end offset) from where waves covers event sphere
 * \tparam T Template floating point type
 * \param _physics Physics constants
 * \param _eventTimeStamp Event time
 * \param _eventSphere Event sphere
 * \returns Offsets (pairs of start - end offset) from where waves covers event sphere
 * \note Timestamps at offset needs to move forward in time to find exact matching spheres
 * \note Size of result vector is same as neutrino generations
 */
template <typename T>
std::vector<std::pair<size_t, size_t>> NeutrinoObject<T>::stepsForSphereSource(
    const Constants<T> &_physics, const T _eventTimeStamp, const Math::Sphere<T> &_eventSphere) const
{
    Math::Sphere<T> waveSphere;
    size_t gen1First = 0U;
    size_t gen1Last = 0U;
    size_t offset = 1U;
    const NeutrinoTimeStamp<T> *ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (ts == nullptr)
        return {};

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);
    const Math::SphereCrossSection<T> scs1(_eventSphere, waveSphere);

    switch (scs1.crossSectionType)
    {
    case Math::CROSS_INVALID:
    case Math::CROSS_WAVE_TOUCH_AFTER:
    case Math::CROSS_WAVE_MISS_AFTER:
        // Invalid states
        return {};

    case Math::CROSS_WAVE_TOUCH_BEFORE:  // gen1First = offset + 1U; break; // Maybe skip first touching ??
    case Math::CROSS_WAVE_CROSS_ELEMENT:
        // Starting offset is one (the first history time-stamp)
        gen1First = offset;
        break;

    case Math::CROSS_WAVE_MISS_BEFORE:
        if (scs1.waveInsideElement)
        {
            // Wave grows from inside element, searching for first crossing state
            while (true)
            {
                offset++;
                ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
                if (ts == nullptr)
                    return {};

                waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);
                switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
                {
                case Math::CROSS_INVALID:
                case Math::CROSS_WAVE_TOUCH_AFTER:
                case Math::CROSS_WAVE_MISS_AFTER:
                    // Invalid states
                    return {};
                case Math::CROSS_WAVE_TOUCH_BEFORE:  // gen1First = offset + 1U; break; // Maybe skip first touching ??
                case Math::CROSS_WAVE_CROSS_ELEMENT:
                    // Mark found starting offset
                    gen1First = offset;
                    break;
                case Math::CROSS_WAVE_MISS_BEFORE: break;
                }
                if (gen1First != 0U)
                    break;
            }
        }
        else
        {
            // Wave grows from outside element
            offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetForEventSource(
                _physics.universeVelocity, _eventTimeStamp, _eventSphere.position);

            if (offset == 0U)
                return {};

            while (true)
            {
                ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
                if (ts == nullptr)
                    return {};

                waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);
                switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
                {
                case Math::CROSS_INVALID:
                case Math::CROSS_WAVE_TOUCH_AFTER:
                case Math::CROSS_WAVE_MISS_AFTER:
                    // Invalid states
                    return {};
                case Math::CROSS_WAVE_CROSS_ELEMENT: break;
                case Math::CROSS_WAVE_TOUCH_BEFORE:
                    // gen1First = offset + 1U; Maybe skip first touching ??
                    gen1First = offset;
                    break;
                case Math::CROSS_WAVE_MISS_BEFORE:
                    // Found first missing, mark found
                    gen1First = offset + 1U;
                    break;
                }
                if (gen1First != 0U)
                    break;

                --offset;
                if (offset == 0U)
                    return {};

                if (offset == 1U)
                {
                    gen1First = 1U;
                    break;
                }
            }
        }

        break;
    }

    if (gen1First == 0U)
        return {};

    offset = gen1First;

    while (true)
    {
        offset++;

        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
        if (ts == nullptr)
            return {};
        waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);

        switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
        {
        case Math::CROSS_INVALID:
        case Math::CROSS_WAVE_TOUCH_BEFORE:
        case Math::CROSS_WAVE_MISS_BEFORE:
            // Invalid states
            return {};

        case Math::CROSS_WAVE_TOUCH_AFTER: gen1Last = offset; break;
        case Math::CROSS_WAVE_MISS_AFTER: gen1Last = offset - 1U; break;
        case Math::CROSS_WAVE_CROSS_ELEMENT: break;
        }

        if (gen1Last != 0U)
            break;
    }

    size_t totalFirst = 0U;
    size_t totalLast = 0U;

    offset = gen1First;
    while (true)
    {
        if (offset == 1U)
        {
            totalFirst = offset;
            break;
        }
        offset--;

        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
        if (ts == nullptr)
            return {};
        waveSphere.reset(_physics.elementRadius + (_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity,
                         ts->position);

        switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
        {
        case Math::CROSS_WAVE_TOUCH_BEFORE:
        case Math::CROSS_WAVE_MISS_BEFORE: totalFirst = offset; break;
        case Math::CROSS_WAVE_TOUCH_AFTER:
        case Math::CROSS_WAVE_MISS_AFTER:
        case Math::CROSS_WAVE_CROSS_ELEMENT: break;
        case Math::CROSS_INVALID: return {};
        }
        if (totalFirst != 0U)
            break;
    }

    offset = gen1Last;
    const size_t maxOffset = ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.size() - 2U;
    while (true)
    {
        if (offset == maxOffset)
        {
            totalLast = offset;
            break;
        }
        offset++;
        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
        if (ts == nullptr)
            return {};

        waveSphere.reset(_physics.elementRadius + (_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity,
                         ts->position);

        switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
        {
        case Math::CROSS_WAVE_TOUCH_AFTER:
        case Math::CROSS_WAVE_MISS_AFTER: totalLast = offset; break;
        case Math::CROSS_WAVE_TOUCH_BEFORE:
        case Math::CROSS_WAVE_MISS_BEFORE:
        case Math::CROSS_WAVE_CROSS_ELEMENT: break;
        case Math::CROSS_INVALID: return {};
        }
        if (totalLast != 0U)
            break;
    }

    size_t gen2First = 0U;
    size_t gen2Last = 0U;
    size_t gen3First = 0U;
    size_t gen3Last = 0U;

    for (offset = totalFirst; offset <= totalLast; ++offset)
    {
        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
        if (ts == nullptr)
            return {};

        if (ts->isGeneration2())
        {
            waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position2);

            switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
            {
            case Math::CROSS_WAVE_TOUCH_BEFORE:
            case Math::CROSS_WAVE_TOUCH_AFTER:
                if (gen2First == 0U)
                    gen2First = offset;
                gen2Last = offset;
                break;

            case Math::CROSS_WAVE_CROSS_ELEMENT:
                if (gen2First == 0U)
                    gen2First = offset;
                gen2Last = offset;
                break;

            case Math::CROSS_WAVE_MISS_AFTER:
            case Math::CROSS_WAVE_MISS_BEFORE: break;
            case Math::CROSS_INVALID: return {};
            }

            if (ts->isGeneration3())
            {
                waveSphere.position = ts->position3;
                switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
                {
                case Math::CROSS_WAVE_TOUCH_BEFORE:
                case Math::CROSS_WAVE_TOUCH_AFTER:
                    if (gen3First == 0U)
                        gen3First = offset;
                    gen3Last = offset;
                    break;

                case Math::CROSS_WAVE_CROSS_ELEMENT:
                    if (gen3First == 0U)
                        gen3First = offset;
                    gen3Last = offset;
                    break;

                case Math::CROSS_WAVE_MISS_AFTER:
                case Math::CROSS_WAVE_MISS_BEFORE: break;
                case Math::CROSS_INVALID: return {};
                }
            }
        }
    }

    if (gen3First != 0U)
        return {{gen1First, gen1Last}, {gen2First, gen2Last}, {gen3First, gen3Last}};
    else if (gen2First != 0U)
        return {{gen1First, gen1Last}, {gen2First, gen2Last}};
    else
        return {{gen1First, gen1Last}};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Prepare vector of offsets and total acceleration acting on given event sphere
 * \tparam T Template floating point type
 * \param _physics Physics constants
 * \param _eventTimeStamp Event time
 * \param _eventSphere Event sphere
 * \returns Total acceleration acting on given event sphere and offsets (pairs of start - end offset)
 */
template <typename T>
std::pair<std::vector<std::pair<size_t, size_t>>, Math::Vec3<T>> NeutrinoObject<T>::accelForSphereSource(
    const Constants<T> &_physics, const T _eventTimeStamp, const Math::Sphere<T> &_eventSphere) const
{
    const T volumeEvent = _eventSphere.volume();
    Math::Sphere<T> waveSphere;

    std::pair<std::vector<std::pair<size_t, size_t>>, Math::Vec3<T>> result;
    result.first = stepsForSphereSource(_physics, _eventTimeStamp, _eventSphere);

    if (result.first.empty())
        return {{}, Math::Vec3<T>()};

    size_t g1Step = result.first[0].first;
    const NeutrinoTimeStamp<T> *ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g1Step);
    if (ts == nullptr)
        return {{}, Math::Vec3<T>()};

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);
    switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
    {
    case Math::CROSS_WAVE_TOUCH_AFTER:
    case Math::CROSS_WAVE_MISS_AFTER:
    case Math::CROSS_WAVE_MISS_BEFORE:
    case Math::CROSS_INVALID: return {{}, Math::Vec3<T>()};  // Invalid states
    case Math::CROSS_WAVE_TOUCH_BEFORE: g1Step++; break;
    case Math::CROSS_WAVE_CROSS_ELEMENT: break;
    }

    ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g1Step);
    if (ts == nullptr)
        return {{}, Math::Vec3<T>()};
    T tsEnergy = ts->getEnergy(_physics.elementRadius).second.x;

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);
    const Math::SphereCrossSection<T> scs1(_eventSphere, waveSphere);
    if (scs1.crossSectionType != Math::CROSS_WAVE_CROSS_ELEMENT)
        return {{}, Math::Vec3<T>()};

    T lastVolume = scs1.crossSectionVolume();
    if (scs1.waveInsideElement)
    {
        const T ignoredVolume = Math::Sphere<T>(_eventSphere.radius * Const::T_05<T>(), Math::Vec3<T>()).volume();
        result.second += scs1.directionToWave() *
            (_physics.gravityConstant * tsEnergy * scs1.ratio() * (lastVolume - ignoredVolume) / volumeEvent);
    }
    else
    {
        result.second += (waveSphere.position - _eventSphere.position).normalized() *
            (_physics.gravityConstant * tsEnergy * scs1.ratio() * lastVolume / volumeEvent);
    }

    g1Step++;

    for (; g1Step <= result.first[0].second; ++g1Step)
    {
        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g1Step);
        if (ts == nullptr)
            return {{}, Math::Vec3<T>()};
        tsEnergy = ts->getEnergy(_physics.elementRadius).second.x;

        waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position);
        const Math::SphereCrossSection<T> scs12(_eventSphere, waveSphere);
        if (scs12.crossSectionType != Math::CROSS_WAVE_CROSS_ELEMENT)
            return {{}, Math::Vec3<T>()};

        const T nextVolume = scs12.crossSectionVolume();
        result.second += scs12.directionToWave() *
            (_physics.gravityConstant * tsEnergy * scs12.ratio() * (nextVolume - lastVolume) / volumeEvent);

        lastVolume = nextVolume;
        if (g1Step == result.first[0].second)
        {
            result.second += scs12.directionToWave() *
                (_physics.gravityConstant * tsEnergy * scs12.ratio() * (volumeEvent - nextVolume) / volumeEvent);
            break;
        }
    }

    if (result.first.size() == 1U)
        return result;

    size_t g2Step = result.first[1].first;
    ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g2Step);
    if (ts == nullptr || !ts->isGeneration2())
        return {{}, Math::Vec3<T>()};

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position2);
    switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
    {
    case Math::CROSS_WAVE_TOUCH_AFTER:
    case Math::CROSS_WAVE_MISS_AFTER:
    case Math::CROSS_WAVE_MISS_BEFORE:
    case Math::CROSS_INVALID: return {{}, Math::Vec3<T>()};  // Invalid states
    case Math::CROSS_WAVE_TOUCH_BEFORE: g2Step++; break;
    case Math::CROSS_WAVE_CROSS_ELEMENT: break;
    }

    ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g2Step);
    if (ts == nullptr || !ts->isGeneration2())
        return {{}, Math::Vec3<T>()};

    tsEnergy = ts->getEnergy(_physics.elementRadius).second.y;

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position2);

    const Math::SphereCrossSection<T> scs2(_eventSphere, waveSphere);
    if (scs2.crossSectionType != Math::CROSS_WAVE_CROSS_ELEMENT)
        return {{}, Math::Vec3<T>()};

    lastVolume = scs2.crossSectionVolume();
    if (scs2.waveInsideElement)
    {
        const T ignoredVolume = Math::Sphere<T>(_eventSphere.radius * Const::T_05<T>(), Math::Vec3<T>()).volume();
        result.second += scs2.directionToWave() *
            (_physics.gravityConstant * tsEnergy * scs2.ratio() * (lastVolume - ignoredVolume) / volumeEvent);
    }
    else
    {
        result.second += (waveSphere.position - _eventSphere.position).normalized() *
            (_physics.gravityConstant * tsEnergy * scs2.ratio() * lastVolume / volumeEvent);
    }

    g2Step++;
    for (; g2Step <= result.first[1].second; ++g2Step)
    {
        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g2Step);
        if (ts == nullptr || !ts->isGeneration2())
            return {{}, Math::Vec3<T>()};
        tsEnergy = ts->getEnergy(_physics.elementRadius).second.y;

        waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position2);
        const Math::SphereCrossSection<T> scs22(_eventSphere, waveSphere);
        if (scs22.crossSectionType != Math::CROSS_WAVE_CROSS_ELEMENT)
            return {{}, Math::Vec3<T>()};

        const T nextVolume = scs22.crossSectionVolume();
        result.second += scs22.directionToWave() *
            (_physics.gravityConstant * tsEnergy * scs22.ratio() * (nextVolume - lastVolume) / volumeEvent);

        lastVolume = nextVolume;
        if (g2Step == result.first[0].second)
        {
            result.second += scs22.directionToWave() *
                (_physics.gravityConstant * tsEnergy * scs22.ratio() * (volumeEvent - nextVolume) / volumeEvent);
            break;
        }
    }

    if (result.first.size() == 2U)
        return result;
    if (result.first.size() != 3U)
        return {{}, Math::Vec3<T>()};

    size_t g3Step = result.first[2].first;
    ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g3Step);
    if (ts == nullptr || !ts->isGeneration3())
        return {{}, Math::Vec3<T>()};

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position3);
    switch (Math::SphereCrossSection<T>(_eventSphere, waveSphere).crossSectionType)
    {
    case Math::CROSS_WAVE_TOUCH_AFTER:
    case Math::CROSS_WAVE_MISS_AFTER:
    case Math::CROSS_WAVE_MISS_BEFORE:
    case Math::CROSS_INVALID: return {{}, Math::Vec3<T>()};  // Invalid states
    case Math::CROSS_WAVE_TOUCH_BEFORE: g3Step++; break;
    case Math::CROSS_WAVE_CROSS_ELEMENT: break;
    }

    ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g3Step);
    if (ts == nullptr || !ts->isGeneration3())
        return {{}, Math::Vec3<T>()};

    tsEnergy = ts->getEnergy(_physics.elementRadius).second.z;

    waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position3);

    const Math::SphereCrossSection<T> scs3(_eventSphere, waveSphere);
    if (scs3.crossSectionType != Math::CROSS_WAVE_CROSS_ELEMENT)
        return {{}, Math::Vec3<T>()};

    lastVolume = scs3.crossSectionVolume();
    if (scs3.waveInsideElement)
    {
        const T ignoredVolume = Math::Sphere<T>(_eventSphere.radius * Const::T_05<T>(), Math::Vec3<T>()).volume();
        result.second += scs3.directionToWave() *
            (_physics.gravityConstant * tsEnergy * scs3.ratio() * (lastVolume - ignoredVolume) / volumeEvent);
    }
    else
    {
        result.second += (waveSphere.position - _eventSphere.position).normalized() *
            (_physics.gravityConstant * tsEnergy * scs3.ratio() * lastVolume / volumeEvent);
    }

    g3Step++;
    for (; g3Step <= result.first[2].second; ++g3Step)
    {
        ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(g3Step);
        if (ts == nullptr || !ts->isGeneration3())
            return {{}, Math::Vec3<T>()};
        tsEnergy = ts->getEnergy(_physics.elementRadius).second.z;

        waveSphere.reset((_eventTimeStamp - ts->timeStamp) * _physics.universeVelocity, ts->position3);
        const Math::SphereCrossSection<T> scs32(_eventSphere, waveSphere);
        if (scs32.crossSectionType != Math::CROSS_WAVE_CROSS_ELEMENT)
            return {{}, Math::Vec3<T>()};

        const T nextVolume = scs32.crossSectionVolume();
        result.second += scs32.directionToWave() *
            (_physics.gravityConstant * tsEnergy * scs32.ratio() * (nextVolume - lastVolume) / volumeEvent);

        lastVolume = nextVolume;
        if (g3Step == result.first[0].second)
        {
            result.second += scs32.directionToWave() *
                (_physics.gravityConstant * tsEnergy * scs32.ratio() * (volumeEvent - nextVolume) / volumeEvent);
            break;
        }
    }
    return result;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Loads neutrino generation 2 existence path segments
 * \param _out Output collection
 * \return Success flag
 */
template <typename T>
bool NeutrinoObject<T>::loadPath2(std::vector<std::vector<std::pair<double, QVector3D>>> &_out) const
{
    if (ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.empty())
        return false;

    std::list<std::list<std::pair<double, QVector3D>>> tmp;
    std::list<std::pair<double, QVector3D>> *currentPath = nullptr;
    size_t offset = 1U;

    while (true)
    {
        const NeutrinoTimeStamp<T> *ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
        if (ts == nullptr)
            break;

        if (ts->isGeneration2())
        {
            if (currentPath == nullptr)
            {
                tmp.push_back({});
                currentPath = &tmp.back();
            }

            currentPath->push_back({ts->timeStamp, ts->position2.toQVector3D()});
        }
        else
        {
            if (currentPath != nullptr)
                currentPath = nullptr;
        }
        ++offset;
    }

    if (!tmp.empty())
    {
        _out.resize(tmp.size());
        std::list<std::list<std::pair<double, QVector3D>>>::const_iterator itIn = tmp.cbegin();
        std::vector<std::vector<std::pair<double, QVector3D>>>::iterator itOut = _out.begin();
        for (; itIn != tmp.cend(); ++itIn, ++itOut)
        {

            std::list<std::pair<double, QVector3D>>::const_iterator itIn2 = (*itIn).cbegin();
            (*itOut).reserve((*itIn).size());
            for (; itIn2 != (*itIn).cend(); ++itIn2)
                (*itOut).push_back(*itIn2);
        }
    }

    return true;
}

/*!
 * \brief Loads neutrino generation 3 existence path segments
 * \param _out Output collection
 * \return Success flag
 */
template <typename T>
bool NeutrinoObject<T>::loadPath3(std::vector<std::vector<std::pair<double, QVector3D>>> &_out) const
{
    if (ObjectHistory<T, NeutrinoTimeStamp<T>>::m_history.empty())
        return false;

    std::list<std::list<std::pair<double, QVector3D>>> tmp;
    std::list<std::pair<double, QVector3D>> *currentPath = nullptr;
    size_t offset = 1U;

    while (true)
    {
        const NeutrinoTimeStamp<T> *ts = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
        if (ts == nullptr)
            break;

        if (ts->isGeneration3())
        {
            if (currentPath == nullptr)
            {
                tmp.push_back({});
                currentPath = &tmp.back();
            }

            currentPath->push_back({ts->timeStamp, ts->position3.toQVector3D()});
        }
        else
        {
            if (currentPath != nullptr)
                currentPath = nullptr;
        }
        ++offset;
    }

    if (!tmp.empty())
    {
        _out.resize(tmp.size());
        std::list<std::list<std::pair<double, QVector3D>>>::const_iterator itIn = tmp.cbegin();
        std::vector<std::vector<std::pair<double, QVector3D>>>::iterator itOut = _out.begin();
        for (; itIn != tmp.cend(); ++itIn, ++itOut)
        {

            std::list<std::pair<double, QVector3D>>::const_iterator itIn2 = (*itIn).cbegin();
            (*itOut).reserve((*itIn).size());
            for (; itIn2 != (*itIn).cend(); ++itIn2)
                (*itOut).push_back(*itIn2);
        }
    }

    return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for object's generation 2 position
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 2 position
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadPosition2(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr || !result->isGeneration2())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;
    if (Type::isNull(timeDelta))
        return {true, result->position2.toQVector3D()};

    return {true, result->moved(timeDelta).position2.toQVector3D()};
}

/*!
 * \brief Getter for object's generation 3 position
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 3 position
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadPosition3(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr || !result->isGeneration3())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;
    if (Type::isNull(timeDelta))
        return {true, result->position3.toQVector3D()};

    return {true, result->moved(timeDelta).position3.toQVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for object's generation 1 velocity
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 1 velocity
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadVelocity1(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;

    if (result->isGeneration3())
    {
        if (Type::isNull(timeDelta))
            return {true, result->moveVelocity31.toQVector3D()};
        return {true, result->moved(timeDelta).moveVelocity31.toQVector3D()};
    }
    if (result->isGeneration2())
    {
        if (Type::isNull(timeDelta))
            return {true, result->moveVelocity21.toQVector3D()};
        return {true, result->moved(timeDelta).moveVelocity21.toQVector3D()};
    }

    if (Type::isNull(timeDelta))
        return {true, result->moveVelocity1.toQVector3D()};

    return {true, result->moved(timeDelta).moveVelocity1.toQVector3D()};
}

/*!
 * \brief Getter for object's generation 2 velocity
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 2 velocity
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadVelocity2(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr || !result->isGeneration2())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;

    if (result->isGeneration3())
    {
        if (Type::isNull(timeDelta))
            return {true, result->moveVelocity32.toQVector3D()};
        return {true, result->moved(timeDelta).moveVelocity32.toQVector3D()};
    }

    if (Type::isNull(timeDelta))
        return {true, result->moveVelocity22.toQVector3D()};
    return {true, result->moved(timeDelta).moveVelocity22.toQVector3D()};
}

/*!
 * \brief Getter for object's generation 3 velocity
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 3 velocity
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadVelocity3(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr || !result->isGeneration3())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;

    if (Type::isNull(timeDelta))
        return {true, result->moveVelocity33.toQVector3D()};
    return {true, result->moved(timeDelta).moveVelocity33.toQVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for object's generation 1 spin
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 1 spin
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadSpin1(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;
    if (Type::isNull(timeDelta))
        return {true, result->spinVelocity1.toQVector3D()};

    return {true, result->moved(timeDelta).spinVelocity1.toQVector3D()};
}

/*!
 * \brief Getter for object's generation 2 spin
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 2 spin
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadSpin2(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr || !result->isGeneration2())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;

    if (Type::isNull(timeDelta))
        return {true, result->spinVelocity2.toQVector3D()};
    return {true, result->moved(timeDelta).spinVelocity2.toQVector3D()};
}

/*!
 * \brief Getter for object's generation 3 spin
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 3 spin
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadSpin3(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result == nullptr || !result->isGeneration3())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result->timeStamp;

    if (Type::isNull(timeDelta))
        return {true, result->spinVelocity3.toQVector3D()};
    return {true, result->moved(timeDelta).spinVelocity3.toQVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for object's generation 1 acceleration
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 1 acceleration
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadAccel1(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result1 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result1 == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result1->timeStamp;

    if (Type::isNull(timeDelta) || offset == 1U)
        return {true, result1->accelGravity1.toQVector3D()};

    const NeutrinoTimeStamp<T> *result2 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset - 1U);
    if (result2 == nullptr)
        return {false, QVector3D()};

    return {true,
            Math::Vec3<T>::ratio(
                result1->accelGravity1, result2->accelGravity1, result1->timeStamp, result2->timeStamp, _timeStamp)
                .toQVector3D()};
}

/*!
 * \brief Getter for object's generation 2 acceleration
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 2 acceleration
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadAccel2(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result1 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result1 == nullptr && !result1->isGeneration2())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result1->timeStamp;

    if (Type::isNull(timeDelta) || offset == 1U)
        return {true, result1->accelGravity2.toQVector3D()};

    const NeutrinoTimeStamp<T> *result2 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset - 1U);
    if (result2 == nullptr)
        return {false, QVector3D()};

    if (result2->isGeneration2())
        return {true,
                Math::Vec3<T>::ratio(
                    result1->accelGravity2, result2->accelGravity2, result1->timeStamp, result2->timeStamp, _timeStamp)
                    .toQVector3D()};

    return {true, result1->accelGravity2.toQVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for object's generation 1 curving
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 1 curving
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadCurving1(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result1 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result1 == nullptr)
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result1->timeStamp;

    if (result1->isGeneration2())
    {
        if (Type::isNull(timeDelta) || offset == 1U)
            return {true, result1->curvingVelocity21.toQVector3D()};

        const NeutrinoTimeStamp<T> *result2 =
            ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset - 1U);
        if (result2 == nullptr)
            return {false, QVector3D()};

        if (result2->isGeneration2())
            return {true,
                    Math::Vec3<T>::ratio(result1->curvingVelocity21,
                                         result2->curvingVelocity21,
                                         result1->timeStamp,
                                         result2->timeStamp,
                                         _timeStamp)
                        .toQVector3D()};

        return {true, result1->curvingVelocity21.toQVector3D()};
    }

    if (Type::isNull(timeDelta) || offset == 1U)
        return {true, result1->curvingVelocity1.toQVector3D()};

    const NeutrinoTimeStamp<T> *result2 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset - 1U);
    if (result2 == nullptr)
        return {false, QVector3D()};

    return {
        true,
        Math::Vec3<T>::ratio(
            result1->curvingVelocity1, result2->curvingVelocity1, result1->timeStamp, result2->timeStamp, _timeStamp)
            .toQVector3D()};
}

/*!
 * \brief Getter for object's generation 2 curving
 * \tparam T Template floating point type
 * \param _timeStamp Time-stamp of required position
 * \returns Pair, where \c first item is success flag, and \c second item is object's generation 2 curving
 */
template <typename T>
std::pair<bool, QVector3D> NeutrinoObject<T>::loadCurving2(const T _timeStamp) const
{
    const size_t offset = ObjectHistory<T, NeutrinoTimeStamp<T>>::offsetAtTime(_timeStamp);
    if (offset == 0U)
        return {false, QVector3D()};

    const NeutrinoTimeStamp<T> *result1 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset);
    if (result1 == nullptr || !result1->isGeneration2())
        return {false, QVector3D()};

    const T timeDelta = _timeStamp - result1->timeStamp;
    if (Type::isNull(timeDelta) || offset == 1U)
        return {true, result1->curvingVelocity22.toQVector3D()};

    const NeutrinoTimeStamp<T> *result2 = ObjectHistory<T, NeutrinoTimeStamp<T>>::historyTimeStampByOffset(offset - 1U);
    if (result2 == nullptr)
        return {false, QVector3D()};

    if (!result2->isGeneration2())
        return {true, result1->curvingVelocity22.toQVector3D()};

    return {
        true,
        Math::Vec3<T>::ratio(
            result1->curvingVelocity22, result2->curvingVelocity22, result1->timeStamp, result2->timeStamp, _timeStamp)
            .toQVector3D()};
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}  // namespace GravityNeutrino
}  // namespace Simulation
}  // namespace Universe1

#endif  // UNIVERSE1_SIMULATION_GRAVITYNEUTRINO_NEUTRINOOBJECT_H
