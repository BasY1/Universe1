/*!
 * \file src/ItemProps/itempropertyvec3.h
 * \brief Base class for 3D vector properties
 */

#ifndef PROPS_ITEMPROPERTYVEC3_H
#define PROPS_ITEMPROPERTYVEC3_H

#include "../Math/vec3.h"
#include "itempropertynum.h"

#include <map>
#include <iostream>

namespace U1 {
namespace Props {

/*!
 * \brief Base class for 3D vector properties
 * \tparam T Floating point type
 */
template <typename T>
class ItemPropertyVec3
{
 public:
    /*! \brief Job name */
    enum JobType : int
    {
        _JobConstantValue,           //!< Keep constant value
        _JobLinearValue,             //!< Linear interpolate to value
        _JobAcceleratedValue,        //!< Accelerated - linear - decelerated interpolation to value
        _JobBezier,                  //!< Linear interpolation over Bezier curve
        _JobBezierAccelerated,       //!< Accelerated interpolation over Bezier curve
        _JobRotated,                 //!< Rotated value
        _JobRotatedAccelerated,      //!< Accelerated - Rotated value
        _JobRotatedMoved,            //!< Rotated and moved value
        _JobRotatedMovedAccelerated  //!< Accelerated - Rotated and moved value
    };

    /*! \brief 3D vector property job */
    struct Job
    {
        JobType type;                    //!< Job name
        Math::Vec3<T> value;             //!< Job final value
        Math::Vec3<T> rotationCenter;    //!< Rotation center
        Math::Vec3<T> rotationNormal;    //!< Rotation normal
        Math::Vec3<T> bezierDirection1;  //!< Bezier normal at start
        Math::Vec3<T> bezierDirection2;  //!< Bezier normal at end
        T rotationAngleRad = T(0);       //!< Rotation job angle
        T rotationMotion = T(0);         //!< Rotation-moved job: motion distance within the rotation normal
        double acceleration = 0.0;       //!< Acceleration duration as ratio to total job duration
        double deceleration = 0.0;       //!< Deceleration duration as ratio to total job duration
    };

 protected:
    std::map<size_t, Job> m_jobs;            //!< Property jobs
    const Math::Vec3<T> m_minimumValue = 0;  //!< Minimum possible value
    const Math::Vec3<T> m_maximumValue = 0;  //!< Maximum possible value
    const bool m_normal = false;             //!< Flag keep vector normalized

    /*!
     * \brief Constructor
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    ItemPropertyVec3(const bool _nornal,
                     const Math::Vec3<T> &_initialValue,
                     const Math::Vec3<T> &_minimumValue,
                     const Math::Vec3<T> &_maximumValue)
        : m_minimumValue(Math::Vec3<T>::minimum(_minimumValue, _maximumValue))
        , m_maximumValue(Math::Vec3<T>::maximum(_minimumValue, _maximumValue))
        , m_normal(_nornal)
    {
        if (!Math::Vec3<T>::isLessNotEqual(m_minimumValue, m_maximumValue))
            std::cerr << "Warning: ItemPropertyVec3(" << _initialValue << ", " << _minimumValue << ", " << _maximumValue
                      << ") Invalid range!\n";

        if (_initialValue.isAligned(m_minimumValue, m_maximumValue))
        {
            m_jobs[0UL] = {_JobConstantValue, _initialValue, {}, {}, {}, {}, T(0), 0.0, 0.0};
        }
        else
        {
            std::cerr << "Error: ItemPropertyVec3(" << _initialValue << ") Value out off range (" << m_minimumValue
                      << ", " << m_maximumValue << ")!\n";
            m_jobs[0UL] = {_JobConstantValue, m_minimumValue, {}, {}, {}, {}, T(0), 0.0, 0.0};
        }
    }

    /*!
     * \brief Constructor
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    ItemPropertyVec3(const Math::Vec3<T> &_initialValue,
                     const Math::Vec3<T> &_minimumValue,
                     const Math::Vec3<T> &_maximumValue)
        : ItemPropertyVec3(false, _initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     */
    ItemPropertyVec3(const bool _nornal, const Math::Vec3<T> &_initialValue)
        : ItemPropertyVec3(_nornal, _initialValue, Math::Vec3<T>::lowestValue(), Math::Vec3<T>::maximumValue())
    {
    }

    /*!
     * \brief Constructor
     * \param _initialValue Initial value
     */
    ItemPropertyVec3(const Math::Vec3<T> &_initialValue)
        : ItemPropertyVec3(false, _initialValue)
    {
    }

 public:
    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    Math::Vec3<T> value(const size_t _timeStep) const
    {
        if (m_jobs.empty())
        {
            if (m_normal)
                return m_minimumValue.normalized();
            return m_minimumValue;
        }
        typename std::map<size_t, Job>::const_iterator it = m_jobs.lower_bound(_timeStep);
        if (it == m_jobs.cend())
        {
            if (m_normal)
                return (*m_jobs.crbegin()).second.value.normalized();
            return (*m_jobs.crbegin()).second.value;
        }

        if (it == m_jobs.cbegin() || (*it).first == _timeStep)
        {
            if (m_normal)
                return (*it).second.value.normalized();
            return (*it).second.value;
        }

        typename std::map<size_t, Job>::const_iterator itPrev = it;
        --itPrev;

        T tmp = T(0);
        Math::Vec3<T> result;
        switch ((*it).second.type)
        {
        case _JobConstantValue: result = (*itPrev).second.value; break;

        case _JobLinearValue:
            tmp = (static_cast<T>(_timeStep - (*itPrev).first) / static_cast<T>((*it).first - (*itPrev).first));
            result = (*itPrev).second.value + ((*it).second.value - (*itPrev).second.value) * tmp;
            break;

        case _JobAcceleratedValue:
            tmp = ItemPropertyNum<T>::getAcceleratedValue(_timeStep,
                                                          (*itPrev).first,
                                                          (*it).first,
                                                          (*it).second.acceleration,
                                                          (*it).second.deceleration,
                                                          T(0),
                                                          T(1));
            result = (*itPrev).second.value + ((*it).second.value - (*itPrev).second.value) * tmp;
            break;

        case _JobBezier:
            tmp = (static_cast<T>(_timeStep - (*itPrev).first) / static_cast<T>((*it).first - (*itPrev).first));
            result = Math::Vec3<T>::bezier(tmp,
                                           (*itPrev).second.value,
                                           (*it).second.bezierDirection1,
                                           (*it).second.value,
                                           (*it).second.bezierDirection2);
            break;

        case _JobBezierAccelerated:
            tmp = ItemPropertyNum<T>::getAcceleratedValue(_timeStep,
                                                          (*itPrev).first,
                                                          (*it).first,
                                                          (*it).second.acceleration,
                                                          (*it).second.deceleration,
                                                          T(0),
                                                          T(1));
            result = Math::Vec3<T>::bezier(tmp,
                                           (*itPrev).second.value,
                                           (*it).second.bezierDirection1,
                                           (*it).second.value,
                                           (*it).second.bezierDirection2);
            break;

        case _JobRotated:
            tmp = (static_cast<T>(_timeStep - (*itPrev).first) / static_cast<T>((*it).first - (*itPrev).first));
            result = (*it).second.rotationCenter +
                Math::Vec3<T>::rotate((*itPrev).second.value - (*it).second.rotationCenter,
                                      (*it).second.rotationNormal,
                                      (*it).second.rotationAngleRad * tmp);
            break;

        case _JobRotatedAccelerated:
            tmp = ItemPropertyNum<T>::getAcceleratedValue(_timeStep,
                                                          (*itPrev).first,
                                                          (*it).first,
                                                          (*it).second.acceleration,
                                                          (*it).second.deceleration,
                                                          T(0),
                                                          T(1));
            result = (*it).second.rotationCenter +
                Math::Vec3<T>::rotate((*itPrev).second.value - (*it).second.rotationCenter,
                                      (*it).second.rotationNormal,
                                      (*it).second.rotationAngleRad * tmp);
            break;

        case _JobRotatedMoved:
            tmp = (static_cast<T>(_timeStep - (*itPrev).first) / static_cast<T>((*it).first - (*itPrev).first));
            result = (*it).second.rotationCenter +
                Math::Vec3<T>::rotate((*itPrev).second.value - (*it).second.rotationCenter,
                                      (*it).second.rotationNormal,
                                      (*it).second.rotationAngleRad * tmp) +
                (*it).second.rotationNormal * ((*it).second.rotationMotion * tmp);
            break;

        case _JobRotatedMovedAccelerated:
            tmp = ItemPropertyNum<T>::getAcceleratedValue(_timeStep,
                                                          (*itPrev).first,
                                                          (*it).first,
                                                          (*it).second.acceleration,
                                                          (*it).second.deceleration,
                                                          T(0),
                                                          T(1));
            result = (*it).second.rotationCenter +
                Math::Vec3<T>::rotate((*itPrev).second.value - (*it).second.rotationCenter,
                                      (*it).second.rotationNormal,
                                      (*it).second.rotationAngleRad * tmp) +
                (*it).second.rotationNormal * ((*it).second.rotationMotion * tmp);
            break;
        }

        if (m_normal)
            return result.normalized();

        return result;
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    void initValue(const Math::Vec3<T> &_initialValue)
    {
        if (!Math::Vec3<T>::isAligned(_initialValue, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::initValue(" << _initialValue << ") Value out off range ("
                      << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: ItemPropertyVec3::initValue(" << _initialValue
                      << ") Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }

        m_jobs[0UL] = {_JobConstantValue, _initialValue, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    void initValueUpTo(const size_t _timeStep, const Math::Vec3<T> &_value)
    {
        if (_timeStep == 0UL)
        {
            std::cerr << "Warning: ItemPropertyVec3::initValueUpTo(" << _timeStep << ", " << _value
                      << ") Initial time == 0, using ItemPropertyVec3::initValue(" << _value << ")!\n";
            initValue(_value);
            return;
        }

        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::initValueUpTo(" << _timeStep << ", " << _value
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (!m_jobs.empty() && (m_jobs.size() != 1UL || (*m_jobs.cbegin()).first != 0UL))
        {
            std::cerr << "Warning: ItemPropertyVec3::initValueUpTo(" << _timeStep << ", " << _value
                      << ") Secondary initialization, clearing all jobs!\n";
            m_jobs.clear();
        }

        m_jobs[0UL] = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStep] = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    void addConstantValue(const size_t _timeStep, const Math::Vec3<T> &_value)
    {
        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addConstantValue(" << _timeStep << ", " << _value
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            m_jobs[0UL] = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
            if (_timeStep != 0UL)
                m_jobs[_timeStep] = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
            return;
        }

        if (_timeStep == 0UL)
        {
            if ((*m_jobs.cbegin()).first == _timeStep)
                std::cerr << "Warning: ItemPropertyVec3::addConstantValue(" << _timeStep << ", " << _value
                          << ") time-step[" << _timeStep << "] already in use, overwriting with new job!\n";
            m_jobs[_timeStep] = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobConstantValue && (*it).second.value == _value)
                return;

            std::cerr << "Warning: ItemPropertyVec3::addConstantValue(" << _timeStep << ", " << _value << ") time-step["
                      << _timeStep << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addConstantValue(" << _timeStep << ", " << _value
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobConstantValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to reach at given time-step
     */
    void addLinearValue(const size_t _timeStep, const Math::Vec3<T> &_value)
    {
        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addLinearValue(" << _timeStep << ", " << _value
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addLinearValue(" << _timeStep << ", " << _value
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addLinearValue(0, " << _value
                      << ") Job at time-step[0] cannot be linear, it must be constant!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobLinearValue && (*it).second.value == _value)
                return;

            std::cerr << "Warning: ItemPropertyVec3::addLinearValue(" << _timeStep << ", " << _value << ") time-step["
                      << _timeStep << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobLinearValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addLinearValue(" << _timeStep << ", " << _value
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobLinearValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to reach at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addAcceleratedValue(const size_t _timeStep,
                             const Math::Vec3<T> &_value,
                             const double _acceleration,
                             const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Value out off range (" << m_minimumValue << ", "
                      << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addAcceleratedValue(0, " << _value << ", " << _acceleration << ", "
                      << _deceleration << ") Job at time-step[0] cannot be accelerated, it must be constant!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobAcceleratedValue && (*it).second.value == _value &&
                Math::equals<double>((*it).second.acceleration, _acceleration) &&
                Math::equals<double>((*it).second.deceleration, _deceleration))
                return;
            std::cerr << "Warning: ItemPropertyVec3::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") time-step[" << _timeStep
                      << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobAcceleratedValue, _value, {}, {}, {}, {}, T(0), T(0), _acceleration, _deceleration};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addAcceleratedValue(" << _timeStep << ", " << _value << ", "
                      << _acceleration << ", " << _deceleration << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobAcceleratedValue, _value, {}, {}, {}, {}, T(0), T(0), _acceleration, _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append bezier distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to reach at given time-step
     * \param _bezier1 Bezier normal at start
     * \param _bezier2 Bezier normal at end
     */
    void addBezier(const size_t _timeStep,
                   const Math::Vec3<T> &_value,
                   const Math::Vec3<T> &_bezier1,
                   const Math::Vec3<T> &_bezier2)
    {

        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addBezier(" << _timeStep << ", " << _value << ", " << _bezier1
                      << ", " << _bezier2 << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue
                      << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addBezier(" << _timeStep << ", " << _value << ", " << _bezier1
                      << ", " << _bezier2 << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addBezier(0, " << _value << ", " << _bezier1 << ", " << _bezier2
                      << ") Job at time-step[0] cannot be bezier, it must be constant!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobBezier && (*it).second.value == _value &&
                (*it).second.bezierDirection1 == _bezier1 && (*it).second.bezierDirection2 == _bezier2)
                return;
            std::cerr << "Warning: ItemPropertyVec3::addBezier(" << _timeStep << ", " << _value << ", " << _bezier1
                      << ", " << _bezier2 << ") time-step[" << _timeStep
                      << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobBezier, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), 0.0, 0.0};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addBezier(" << _timeStep << ", " << _value << ", " << _bezier1
                      << ", " << _bezier2 << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobBezier, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append bezier distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to reach at given time-step
     * \param _bezier1 Bezier normal at start
     * \param _bezier2 Bezier normal at end
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addBezierAccelerated(const size_t _timeStep,
                              const Math::Vec3<T> &_value,
                              const Math::Vec3<T> &_bezier1,
                              const Math::Vec3<T> &_bezier2,
                              const double _acceleration,
                              const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addBezierAccelerated(" << _timeStep << ", " << _value << ", "
                      << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", " << _deceleration
                      << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addBezierAccelerated(" << _timeStep << ", " << _value << ", "
                      << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", " << _deceleration
                      << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addBezierAccelerated(" << _timeStep << ", " << _value << ", "
                      << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addBezierAccelerated(" << _timeStep << ", " << _value << ", "
                      << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", " << _deceleration
                      << ") Job at time-step[0] cannot be bezier accelerated, it must be constant!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobBezierAccelerated && (*it).second.value == _value &&
                (*it).second.bezierDirection1 == _bezier1 && (*it).second.bezierDirection2 == _bezier2 &&
                Math::equals<double>((*it).second.acceleration, _acceleration) &&
                Math::equals<double>((*it).second.deceleration, _deceleration))
                return;
            std::cerr << "Warning: ItemPropertyVec3::addBezierAccelerated(" << _timeStep << ", " << _value << ", "
                      << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", " << _deceleration
                      << ") time-step[" << _timeStep << "] already in use, overwriting with new job!\n";
            (*it).second = {
                _JobBezierAccelerated, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), _acceleration, _deceleration};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addBezierAccelerated(" << _timeStep << ", " << _value << ", "
                      << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", " << _deceleration
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {
            _JobBezierAccelerated, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), _acceleration, _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStep Time-step for value
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     */
    void addRotated(const size_t _timeStep,
                    const Math::Vec3<T> &_rotationCenter,
                    const Math::Vec3<T> &_rotationNormal,
                    const T _rotationAngleRad)
    {
        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad
                      << ") Job at time-step[0] cannot be rotated, it must be constant!\n";
            return;
        }

        Math::Vec3<T> lastValue;
        {
            typename std::map<size_t, Job>::const_iterator it = m_jobs.lower_bound(_timeStep);
            if (it == m_jobs.cbegin())
            {
                std::cerr << "Error: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                          << _rotationNormal << ", " << _rotationAngleRad << ") Can't add as first job!\n";
                return;
            }

            if (it == m_jobs.cend())
            {
                lastValue = (*m_jobs.crbegin()).second.value;
            }
            else
            {
                --it;
                lastValue = (*it).second.value;
            }
        }

        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad
                      << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd =
            _rotationCenter + Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad);

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ") After rotation the final value(" << jobEnd
                      << ") is out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobRotated && (*it).second.value == jobEnd &&
                (*it).second.rotationCenter == _rotationCenter && (*it).second.rotationNormal == _rotationNormal &&
                Math::equals<T>((*it).second.rotationAngleRad, _rotationAngleRad))
                return;

            std::cerr << "Warning: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ") time-step[" << _timeStep
                      << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobRotated,
                            jobEnd,
                            _rotationCenter,
                            _rotationNormal.normalized(),
                            {},
                            {},
                            _rotationAngleRad,
                            T(0),
                            0.0,
                            0.0};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addRotated(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobRotated,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             T(0),
                             0.0,
                             0.0};
    }

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStep Time-step for value
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addRotatedAccelerated(const size_t _timeStep,
                               const Math::Vec3<T> &_rotationCenter,
                               const Math::Vec3<T> &_rotationNormal,
                               const T _rotationAngleRad,
                               const double _acceleration,
                               const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") Job at time-step[0] cannot be rotated, it must be constant!\n";
            return;
        }

        Math::Vec3<T> lastValue;
        {
            typename std::map<size_t, Job>::const_iterator it = m_jobs.lower_bound(_timeStep);
            if (it == m_jobs.cbegin())
            {
                std::cerr << "Error: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                          << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                          << _deceleration << ") Can't add as first job!\n";
                return;
            }

            if (it == m_jobs.cend())
            {
                lastValue = (*m_jobs.crbegin()).second.value;
            }
            else
            {
                --it;
                lastValue = (*it).second.value;
            }
        }

        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd =
            _rotationCenter + Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad);

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") After rotation the final value(" << jobEnd << ") is out off range ("
                      << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobRotatedAccelerated && (*it).second.value == jobEnd &&
                (*it).second.rotationCenter == _rotationCenter && (*it).second.rotationNormal == _rotationNormal &&
                Math::equals<T>((*it).second.rotationAngleRad, _rotationAngleRad) &&
                Math::equals<double>((*it).second.acceleration, _acceleration) &&
                Math::equals<double>((*it).second.deceleration, _deceleration))
                return;

            std::cerr << "Warning: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") time-step[" << _timeStep
                      << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobRotatedAccelerated,
                            jobEnd,
                            _rotationCenter,
                            _rotationNormal.normalized(),
                            {},
                            {},
                            _rotationAngleRad,
                            T(0),
                            _acceleration,
                            _deceleration};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addRotatedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _acceleration << ", "
                      << _deceleration << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobRotatedAccelerated,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             T(0),
                             _acceleration,
                             _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append rotated and moved value to property jobs
     * \param _timeStep Time-step for value
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     * \param _moveInNormal Rotation motion along a rotation normal
     */
    void addRotatedMoved(const size_t _timeStep,
                         const Math::Vec3<T> &_rotationCenter,
                         const Math::Vec3<T> &_rotationNormal,
                         const T _rotationAngleRad,
                         const T _moveInNormal)
    {
        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal
                      << ") Job at time-step[0] cannot be rotated, it must be constant!\n";
            return;
        }

        Math::Vec3<T> lastValue;
        {
            typename std::map<size_t, Job>::const_iterator it = m_jobs.lower_bound(_timeStep);
            if (it == m_jobs.cbegin())
            {
                std::cerr << "Error: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                          << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal
                          << ") Can't add as first job!\n";
                return;
            }

            if (it == m_jobs.cend())
            {
                lastValue = (*m_jobs.crbegin()).second.value;
            }
            else
            {
                --it;
                lastValue = (*it).second.value;
            }
        }

        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal
                      << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd = _rotationCenter +
            Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad) +
            _rotationNormal * _moveInNormal;

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal
                      << ") After rotation the final value(" << jobEnd << ") is out off range (" << m_minimumValue
                      << ", " << m_maximumValue << ")!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobRotatedMoved && (*it).second.value == jobEnd &&
                (*it).second.rotationCenter == _rotationCenter && (*it).second.rotationNormal == _rotationNormal &&
                Math::equals<T>((*it).second.rotationAngleRad, _rotationAngleRad))
                return;

            std::cerr << "Warning: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal << ") time-step["
                      << _timeStep << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobRotatedMoved,
                            jobEnd,
                            _rotationCenter,
                            _rotationNormal.normalized(),
                            {},
                            {},
                            _rotationAngleRad,
                            _moveInNormal,
                            0.0,
                            0.0};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addRotatedMoved(" << _timeStep << ", " << _rotationCenter << ", "
                      << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobRotatedMoved,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             _moveInNormal,
                             0.0,
                             0.0};
    }

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStep Time-step for value
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     * \param _moveInNormal Rotation motion along a rotation normal
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addRotatedMovedAccelerated(const size_t _timeStep,
                                    const Math::Vec3<T> &_rotationCenter,
                                    const Math::Vec3<T> &_rotationNormal,
                                    const T _rotationAngleRad,
                                    const T _moveInNormal,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal << ", "
                      << _acceleration << ", " << _deceleration << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal << ", "
                      << _acceleration << ", " << _deceleration << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStep == 0UL)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal << ", "
                      << _acceleration << ", " << _deceleration
                      << ") Job at time-step[0] cannot be rotated, it must be constant!\n";
            return;
        }

        Math::Vec3<T> lastValue;
        {
            typename std::map<size_t, Job>::const_iterator it = m_jobs.lower_bound(_timeStep);
            if (it == m_jobs.cbegin())
            {
                std::cerr << "Error: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", "
                          << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                          << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                          << ") Can't add as first job!\n";
                return;
            }

            if (it == m_jobs.cend())
            {
                lastValue = (*m_jobs.crbegin()).second.value;
            }
            else
            {
                --it;
                lastValue = (*it).second.value;
            }
        }

        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal << ", "
                      << _acceleration << ", " << _deceleration
                      << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd = _rotationCenter +
            Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad) +
            _rotationNormal * _moveInNormal;

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", " << _rotationCenter
                      << ", " << _rotationNormal << ", " << _rotationAngleRad << ", " << _moveInNormal << ", "
                      << _acceleration << ", " << _deceleration << ") After rotation the final value(" << jobEnd
                      << ") is out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        typename std::map<size_t, Job>::iterator it = m_jobs.find(_timeStep);
        if (it != m_jobs.end())
        {
            if ((*it).second.type == _JobRotatedMovedAccelerated && (*it).second.value == jobEnd &&
                (*it).second.rotationCenter == _rotationCenter && (*it).second.rotationNormal == _rotationNormal &&
                Math::equals<T>((*it).second.rotationAngleRad, _rotationAngleRad) &&
                Math::equals<double>((*it).second.acceleration, _acceleration) &&
                Math::equals<double>((*it).second.deceleration, _deceleration))
                return;

            std::cerr << "Warning: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration << ") time-step[" << _timeStep
                      << "] already in use, overwriting with new job!\n";
            (*it).second = {_JobRotatedMovedAccelerated,
                            jobEnd,
                            _rotationCenter,
                            _rotationNormal.normalized(),
                            {},
                            {},
                            _rotationAngleRad,
                            _moveInNormal,
                            _acceleration,
                            _deceleration};

            return;
        }

        if ((*m_jobs.crbegin()).first >= _timeStep)
            std::cerr << "Warning: ItemPropertyVec3::addRotatedMovedAccelerated(" << _timeStep << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") Adding job inside the job stack!\n";

        m_jobs[_timeStep] = {_JobRotatedMovedAccelerated,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             _moveInNormal,
                             _acceleration,
                             _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const Math::Vec3<T> &_value)
    {
        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromLinearValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobLinearValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobLinearValue, _value, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addFromAcceleratedValue(const size_t _timeStart,
                                 const size_t _timeStop,
                                 const Math::Vec3<T> &_value,
                                 const double _acceleration,
                                 const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration
                      << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration << ") Value out off range ("
                      << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromAcceleratedValue(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {
                _JobAcceleratedValue, _value, {}, {}, {}, {}, T(0), T(0), _acceleration, _deceleration};
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobAcceleratedValue, _value, {}, {}, {}, {}, T(0), T(0), _acceleration, _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append bezier distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _bezier1 Bezier normal at start
     * \param _bezier2 Bezier normal at end
     */
    void addFromBezier(const size_t _timeStart,
                       const size_t _timeStop,
                       const Math::Vec3<T> &_value,
                       const Math::Vec3<T> &_bezier1,
                       const Math::Vec3<T> &_bezier2)
    {
        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezier(" << _timeStart << ", " << _timeStop << ", " << _value
                      << ", " << _bezier1 << ", " << _bezier2 << ") Value out off range (" << m_minimumValue << ", "
                      << m_maximumValue << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezier(" << _timeStart << ", " << _timeStop << ", " << _value
                      << ", " << _bezier1 << ", " << _bezier2 << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezier(" << _timeStart << ", " << _timeStop << ", " << _value
                      << ", " << _bezier1 << ", " << _bezier2 << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezier(" << _timeStart << ", " << _timeStop << ", " << _value
                      << ", " << _bezier1 << ", " << _bezier2 << ") Can't add inner job, latest time-step["
                      << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobBezier, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), 0.0, 0.0};
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobBezier, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), 0.0, 0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated bezier distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _bezier1 Bezier normal at start
     * \param _bezier2 Bezier normal at end
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addFromBezierAccelerated(const size_t _timeStart,
                                  const size_t _timeStop,
                                  const Math::Vec3<T> &_value,
                                  const Math::Vec3<T> &_bezier1,
                                  const Math::Vec3<T> &_bezier2,
                                  const double _acceleration,
                                  const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezierAccelerated(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", "
                      << _deceleration << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (!Math::Vec3<T>::isAligned(_value, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezierAccelerated(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", "
                      << _deceleration << ") Value out off range (" << m_minimumValue << ", " << m_maximumValue
                      << ")!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezierAccelerated(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", "
                      << _deceleration << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezierAccelerated(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", "
                      << _deceleration << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromBezierAccelerated(" << _timeStart << ", " << _timeStop << ", "
                      << _value << ", " << _bezier1 << ", " << _bezier2 << ", " << _acceleration << ", "
                      << _deceleration << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first
                      << "]!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {
                _JobBezierAccelerated, _value, {}, {}, {}, {}, T(0), T(0), _acceleration, _deceleration};
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, _bezier1, _bezier2, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {
            _JobBezierAccelerated, _value, {}, {}, _bezier1, _bezier2, T(0), T(0), _acceleration, _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     */
    void addFromRotated(const size_t _timeStart,
                        const size_t _timeStop,
                        const Math::Vec3<T> &_rotationCenter,
                        const Math::Vec3<T> &_rotationNormal,
                        const T _rotationAngleRad)
    {
        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotated(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotated(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad
                      << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotated(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad
                      << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotated(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad
                      << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd =
            _rotationCenter + Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad);

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotated(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad
                      << ") After rotation the final value(" << jobEnd << ") is out off range (" << m_minimumValue
                      << ", " << m_maximumValue << ")!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobRotated,
                                 jobEnd,
                                 _rotationCenter,
                                 _rotationNormal.normalized(),
                                 {},
                                 {},
                                 _rotationAngleRad,
                                 T(0),
                                 0.0,
                                 0.0};
            return;
        }

        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobRotated,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             T(0),
                             0.0,
                             0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addFromRotatedAccelerated(const size_t _timeStart,
                                   const size_t _timeStop,
                                   const Math::Vec3<T> &_rotationCenter,
                                   const Math::Vec3<T> &_rotationNormal,
                                   const T _rotationAngleRad,
                                   const double _acceleration,
                                   const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _acceleration << ", " << _deceleration << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _acceleration << ", " << _deceleration << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _acceleration << ", " << _deceleration << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _acceleration << ", " << _deceleration << ") Can't add inner job, latest time-step["
                      << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _acceleration << ", " << _deceleration
                      << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd =
            _rotationCenter + Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad);

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _acceleration << ", " << _deceleration << ") After rotation the final value(" << jobEnd
                      << ") is out off range (" << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobRotatedAccelerated,
                                 jobEnd,
                                 _rotationCenter,
                                 _rotationNormal.normalized(),
                                 {},
                                 {},
                                 _rotationAngleRad,
                                 T(0),
                                 _acceleration,
                                 _deceleration};
            return;
        }

        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobRotatedAccelerated,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             T(0),
                             _acceleration,
                             _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     * \param _moveInNormal Rotation motion along a rotation normal
     */
    void addFromRotatedMoved(const size_t _timeStart,
                             const size_t _timeStop,
                             const Math::Vec3<T> &_rotationCenter,
                             const Math::Vec3<T> &_rotationNormal,
                             const T _rotationAngleRad,
                             const T _moveInNormal)
    {
        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMoved(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMoved(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMoved(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first
                      << "]!\n";
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMoved(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd = _rotationCenter +
            Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad) +
            _rotationNormal * _moveInNormal;

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMoved(" << _timeStart << ", " << _timeStop << ", "
                      << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ") After rotation the final value(" << jobEnd << ") is out off range ("
                      << m_minimumValue << ", " << m_maximumValue << ")!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobRotatedMoved,
                                 jobEnd,
                                 _rotationCenter,
                                 _rotationNormal.normalized(),
                                 {},
                                 {},
                                 _rotationAngleRad,
                                 _moveInNormal,
                                 0.0,
                                 0.0};
            return;
        }

        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobRotatedMoved,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             _moveInNormal,
                             0.0,
                             0.0};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append rotated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _rotationCenter Rotation center
     * \param _rotationNormal Rotation normal
     * \param _rotationAngleRad Rotation angle in radians
     * \param _moveInNormal Rotation motion along a rotation normal
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    void addFromRotatedMovedAccelerated(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::Vec3<T> &_rotationCenter,
                                        const Math::Vec3<T> &_rotationNormal,
                                        const T _rotationAngleRad,
                                        const T _moveInNormal,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        if (!Math::isAlignedTo0_1(_acceleration) ||  //
            !Math::isAlignedTo0_1(_deceleration) ||  //
            !Math::isAlignedTo0_1(_acceleration + _deceleration))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMovedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") Invalid acceleration/deceleration values!\n";
            return;
        }

        if (m_jobs.empty())
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMovedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add, jobs are not initialized!\n";
            return;
        }

        if (_timeStart >= _timeStop)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMovedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") Invalid time-step order!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first > _timeStart)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMovedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") Can't add inner job, latest time-step[" << (*m_jobs.crbegin()).first << "]!\n";
            return;
        }

        const Math::Vec3<T> lastValue = (*m_jobs.crbegin()).second.value;
        if (lastValue == _rotationCenter)
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMovedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") Cannot add job rotated job (rotationCenter == startingPointPosition)!\n";
            return;
        }

        const Math::Vec3<T> jobEnd = _rotationCenter +
            Math::Vec3<T>::rotate(lastValue - _rotationCenter, _rotationNormal, _rotationAngleRad) +
            _rotationNormal * _moveInNormal;

        if (!Math::Vec3<T>::isAligned(jobEnd, m_minimumValue, m_maximumValue))
        {
            std::cerr << "Error: ItemPropertyVec3::addFromRotatedMovedAccelerated(" << _timeStart << ", " << _timeStop
                      << ", " << _rotationCenter << ", " << _rotationNormal << ", " << _rotationAngleRad << ", "
                      << _moveInNormal << ", " << _acceleration << ", " << _deceleration
                      << ") After rotation the final value(" << jobEnd << ") is out off range (" << m_minimumValue
                      << ", " << m_maximumValue << ")!\n";
            return;
        }

        if ((*m_jobs.crbegin()).first == _timeStart)
        {
            m_jobs[_timeStop] = {_JobRotatedMovedAccelerated,
                                 jobEnd,
                                 _rotationCenter,
                                 _rotationNormal.normalized(),
                                 {},
                                 {},
                                 _rotationAngleRad,
                                 _moveInNormal,
                                 _acceleration,
                                 _deceleration};
            return;
        }

        m_jobs[_timeStart] = {_JobConstantValue, lastValue, {}, {}, {}, {}, T(0), 0.0, 0.0};
        m_jobs[_timeStop] = {_JobRotatedMovedAccelerated,
                             jobEnd,
                             _rotationCenter,
                             _rotationNormal.normalized(),
                             {},
                             {},
                             _rotationAngleRad,
                             _moveInNormal,
                             _acceleration,
                             _deceleration};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Getter for the initial value
     * \return Initial value
     */
    inline Math::Vec3<T> getInitValue() const
    {
        return m_jobs.empty() ? Math::Vec3<T>() : (*m_jobs.cbegin()).second.value;
    }

    /*!
     * \brief Last value at last time-step
     * \return Value stored at latest time-step
     */
    inline Math::Vec3<T> latestValue() const
    {
        return m_jobs.empty() ? Math::Vec3<T>() : (*m_jobs.crbegin()).second.value;
    }

    /*!
     * \brief Jobs getter
     * \return Jobs map
     */
    inline const std::map<size_t, Job> &jobs() const
    {
        return m_jobs;
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 32 bit 3D vector dynamic property */
class ItemPropertyVec3F : public ItemProperty, public ItemPropertyVec3<float>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyVec3F(const std::string &_name,
                             const bool _nornal,
                             const Math::Vec3<float> &_initialValue,
                             const Math::Vec3<float> &_minimumValue,
                             const Math::Vec3<float> &_maximumValue)
        : ItemProperty(_name)
        , ItemPropertyVec3<float>(_nornal, _initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     */
    inline ItemPropertyVec3F(const std::string &_name, const bool _nornal, const Math::Vec3<float> &_initialValue = {})
        : ItemProperty(_name)
        , ItemPropertyVec3<float>(_nornal, _initialValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyVec3F(const std::string &_name,
                             const Math::Vec3<float> &_initialValue,
                             const Math::Vec3<float> &_minimumValue,
                             const Math::Vec3<float> &_maximumValue)
        : ItemProperty(_name)
        , ItemPropertyVec3<float>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyVec3F(const std::string &_name, const Math::Vec3<float> &_initialValue = {})
        : ItemProperty(_name)
        , ItemPropertyVec3<float>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;

    /*!
     * \brief Returns value at given time-step as text
     * \param _timeStep Time-step
     * \return Value at given time-step as text
     */
    QString textValue(const size_t _timeStep) const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 64 bit 3D vector dynamic property */
class ItemPropertyVec3D : public ItemProperty, public ItemPropertyVec3<double>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyVec3D(const std::string &_name,
                             const bool _nornal,
                             const Math::Vec3<double> &_initialValue,
                             const Math::Vec3<double> &_minimumValue,
                             const Math::Vec3<double> &_maximumValue)
        : ItemProperty(_name)
        , ItemPropertyVec3<double>(_nornal, _initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     */
    inline ItemPropertyVec3D(const std::string &_name, const bool _nornal, const Math::Vec3<double> &_initialValue = {})
        : ItemProperty(_name)
        , ItemPropertyVec3<double>(_nornal, _initialValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyVec3D(const std::string &_name,
                             const Math::Vec3<double> &_initialValue,
                             const Math::Vec3<double> &_minimumValue,
                             const Math::Vec3<double> &_maximumValue)
        : ItemProperty(_name)
        , ItemPropertyVec3<double>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyVec3D(const std::string &_name, const Math::Vec3<double> &_initialValue = {})
        : ItemProperty(_name)
        , ItemPropertyVec3<double>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;

    /*!
     * \brief Returns value at given time-step as text
     * \param _timeStep Time-step
     * \return Value at given time-step as text
     */
    QString textValue(const size_t _timeStep) const override;
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief 128 bit 3D vector dynamic property */
class ItemPropertyVec3L : public ItemProperty, public ItemPropertyVec3<long double>
{
 public:
    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyVec3L(const std::string &_name,
                             const bool _nornal,
                             const Math::Vec3<long double> &_initialValue,
                             const Math::Vec3<long double> &_minimumValue,
                             const Math::Vec3<long double> &_maximumValue)
        : ItemProperty(_name)
        , ItemPropertyVec3<long double>(_nornal, _initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _nornal Flag keep vector normalized
     * \param _initialValue Initial value
     */
    inline ItemPropertyVec3L(const std::string &_name,
                             const bool _nornal,
                             const Math::Vec3<long double> &_initialValue = {})
        : ItemProperty(_name)
        , ItemPropertyVec3<long double>(_nornal, _initialValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     * \param _minimumValue Minimum possible value
     * \param _maximumValue Maximum possible value
     */
    inline ItemPropertyVec3L(const std::string &_name,
                             const Math::Vec3<long double> &_initialValue,
                             const Math::Vec3<long double> &_minimumValue,
                             const Math::Vec3<long double> &_maximumValue)
        : ItemProperty(_name)
        , ItemPropertyVec3<long double>(_initialValue, _minimumValue, _maximumValue)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial value
     */
    inline ItemPropertyVec3L(const std::string &_name, const Math::Vec3<long double> &_initialValue = {})
        : ItemProperty(_name)
        , ItemPropertyVec3<long double>(_initialValue)
    {
    }

    /*!
     * \brief Getter for item property type
     * \return Item property type
     */
    PropertyType type() const override;

    /*!
     * \brief Returns latest stored time step
     * \return Latest stored time step
     */
    size_t latestTimeStep() const override;

    /*!
     * \brief Returns value at given time-step as text
     * \param _timeStep Time-step
     * \return Value at given time-step as text
     */
    QString textValue(const size_t _timeStep) const override;
};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYVEC3_H
