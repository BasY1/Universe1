#ifndef UNIVERSE1_VIDEO_DYNAMICPROPERTY_H
#define UNIVERSE1_VIDEO_DYNAMICPROPERTY_H

#include "../config.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic property base structure
 */
struct DynamicProperty
{
    /*! \brief Property types */
    enum Type
    {
        _BOOL,   //!< Boolean property
        _VALUE,  //!< Numeric property
        _ENUM,   //!< Enumeration property
        _TEXT,   //!< Text property
        _VEC3,   //!< 3D vector property
        _COLOR,  //!< Color property
    };

    const Type type;         //!< Property type
    const std::string name;  //!< Property name

    /*!
     * \brief DynamicProperty
     * \param _type Property type
     * \param _name Property name
     */
    inline DynamicProperty(const Type _type, const std::string &_name)
        : type(_type)
        , name(_name)
    {
    }

    virtual ~DynamicProperty() = default;  //!< Default destructor

    /*!
     * \brief Initialize property
     * \param _duration Footage duration
     * \return Success flag
     */
    virtual bool initialize(const uint64_t _duration) = 0;

    /*!
     * \brief Returns value at specific time-step as string
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    virtual QString getValueText(const uint64_t _timeStep) const = 0;

 protected:
    /*!
     * \brief initializeImpl
     * \tparam T Numeric template type
     * \param _values List of values at time step
     * \param _duration Footage duration
     * \return Success flag
     */
    template <typename T>
    bool initializeImpl(std::list<std::pair<uint64_t, T>> &_values, const uint64_t _duration)
    {
        if (_values.empty())
        {
            std::cerr << "Error[" << name << "]: Values not initialized !" << std::endl;
            return false;
        }

        bool needSort = false;
        if (_values.size() > 1UL)
        {
            typename std::list<std::pair<uint64_t, T>>::const_iterator it1 = _values.cbegin();
            typename std::list<std::pair<uint64_t, T>>::const_iterator it2 = it1;
            ++it2;
            for (; it2 != _values.cend(); ++it1, ++it2)
                if ((*it2).first < (*it1).first)
                    needSort = true;
            if (needSort)
                std::cerr << "Warning[" << name << "]: Unsorted time order !" << std::endl;
        }

        if (needSort)
            _values.sort(
                [](const std::pair<uint64_t, T> &_1, const std::pair<uint64_t, T> &_2) { return _1.first < _2.first; });

        bool result = true;
        if (_values.back().first > _duration)
        {
            std::cerr << "Error[" << name << "]: Last value at " << _values.back().first
                      << "ms overflows footage duration " << _duration << "ms !" << std::endl;
            result = false;
        }

        typename std::list<std::pair<uint64_t, T>>::const_iterator itPrev = _values.cbegin();
        typename std::list<std::pair<uint64_t, T>>::const_iterator itNext = itPrev;
        itNext++;

        for (; itNext != _values.cend(); ++itPrev, ++itNext)
        {
            if ((*itPrev).first == (*itNext).first)
            {
                std::cerr << "Error[" << name << "]: More values at time " << (*itPrev).first << "ms !" << std::endl;
                result = false;
            }
        }

        const uint64_t fd = Config::cfg().frameDuration;
        itPrev = _values.cbegin();
        for (; itPrev != _values.cend(); ++itPrev)
            if (((*itPrev).first % fd) != 0UL)
                std::cerr << "Warning[" << name << "]: Unsynchronized time " << (*itPrev).first << "ms with FPS !"
                          << std::endl;

        return result;
    }

    /*!
     * \brief Get value at specific time from sorted list, interpolates to exact value
     * \tparam T Numeric template type
     * \param _values List of values at time step
     * \param _timeStep Time-step for value
     * \return Interpolated value at given time
     */
    template <typename T>
    static T getValueInterpolated(const std::list<std::pair<uint64_t, T>> &_values, const uint64_t _timeStep)
    {
        if (_values.empty())
            return T(0);

        if (_values.front().first >= _timeStep)
            return _values.front().second;

        typename std::list<std::pair<uint64_t, T>>::const_iterator itPrev = _values.cbegin();
        typename std::list<std::pair<uint64_t, T>>::const_iterator itNext = itPrev;
        itNext++;

        for (; itNext != _values.cend(); ++itPrev, ++itNext)
        {
            const std::pair<uint64_t, T> &prev = *itPrev;
            if (prev.first == _timeStep)
                return prev.second;

            const std::pair<uint64_t, T> &next = *itNext;
            if (next.first == _timeStep)
                return next.second;

            if (next.first > _timeStep)
                return prev.second +
                    static_cast<T>((static_cast<double>(next.second) - static_cast<double>(prev.second)) *
                                   (static_cast<double>(_timeStep - prev.first) /
                                    static_cast<double>(next.first - prev.first)));
        }

        return (*itPrev).second;
    }

    /*!
     * \brief Get value at specific time from sorted list
     * \tparam T Numeric template type
     * \param _values List of values at time step
     * \param _timeStep Time-step for value
     * \return Value at given time
     */
    template <typename T>
    static T getValueConstant(const std::list<std::pair<uint64_t, T>> &_values, const uint64_t _timeStep)
    {
        if (_values.empty())
            return T();

        if (_values.front().first >= _timeStep)
            return _values.front().second;

        typename std::list<std::pair<uint64_t, T>>::const_iterator itPrev = _values.cbegin();
        typename std::list<std::pair<uint64_t, T>>::const_iterator itNext = itPrev;
        itNext++;

        for (; itNext != _values.cend(); ++itPrev, ++itNext)
        {
            const std::pair<uint64_t, T> &prev = *itPrev;
            if (prev.first == _timeStep)
                return prev.second;

            const std::pair<uint64_t, T> &next = *itNext;
            if (next.first == _timeStep)
                return next.second;

            if (next.first > _timeStep)
                return prev.second;
        }

        return (*itPrev).second;
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICPROPERTY_H
