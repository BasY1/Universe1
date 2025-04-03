/*!
 * \file src/ItemProps/itempropertymaterial.h
 * \brief Open GL dynamic material properties
 */

#ifndef PROPS_ITEMPROPERTYMATERIAL_H
#define PROPS_ITEMPROPERTYMATERIAL_H

#include "../Math/material.h"
#include "itempropertycolor.h"

namespace U1 {
namespace Props {

/*! \brief Material dynamic item property group */
class ItemPropertyMaterialRGB : public ItemPropertyGroup
{
 public:
    ItemPropertyColor ambient;   //!< Ambient dynamic color
    ItemPropertyColor diffuse;   //!< Diffuse dynamic color
    ItemPropertyColor specular;  //!< Specular dynamic color
    ItemPropertyFloat shine;     //!< Shine dynamic property

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial material
     */
    ItemPropertyMaterialRGB(const std::string &_name, const Math::MaterialRGB &_initialValue);

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialAmbient Initial ambient color
     * \param _initialDiffuse Initial diffuse color
     */
    inline ItemPropertyMaterialRGB(const std::string &_name,
                                   const Math::ColorRGB &_initialAmbient,
                                   const Math::ColorRGB &_initialDiffuse)
        : ItemPropertyMaterialRGB(_name, Math::MaterialRGB{_initialAmbient, _initialDiffuse, {255U, 255U, 255U}, 32.0f})
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialAmbient Initial ambient color
     * \param _initialDiffuse Initial diffuse color
     */
    inline ItemPropertyMaterialRGB(const std::string &_name,
                                   const QColor &_initialAmbient,
                                   const QColor &_initialDiffuse)
        : ItemPropertyMaterialRGB(
              _name,
              Math::MaterialRGB{
                  Math::ColorRGB(_initialAmbient), Math::ColorRGB(_initialDiffuse), {255U, 255U, 255U}, 32.0f})
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialColor Initial color
     */
    inline ItemPropertyMaterialRGB(const std::string &_name, const Math::ColorRGB &_initialColor)
        : ItemPropertyMaterialRGB(_name, _initialColor.darker(), _initialColor)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialColor Initial color
     */
    inline ItemPropertyMaterialRGB(const std::string &_name, const QColor &_initialColor)
        : ItemPropertyMaterialRGB(_name, _initialColor.darker(), _initialColor)
    {
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    inline Math::MaterialRGB value(const size_t _timeStep) const
    {
        return Math::MaterialRGB{
            ambient.value(_timeStep), diffuse.value(_timeStep), specular.value(_timeStep), shine.value(_timeStep)};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const Math::MaterialRGB &_initialValue)
    {
        ambient.initValue(_initialValue.ambient);
        diffuse.initValue(_initialValue.diffuse);
        specular.initValue(_initialValue.specular);
        shine.initValue(_initialValue.shine);
    }

    /*!
     * \brief Initialize with value
     * \param _initialAmbient Initial ambient color at time-step == 0
     * \param _initialDiffuse Initial diffuse color at time-step == 0
     */
    inline void initValue(const Math::ColorRGB &_initialAmbient, const Math::ColorRGB &_initialDiffuse)
    {
        initValue(Math::MaterialRGB{_initialAmbient, _initialDiffuse, {255, 255, 255}, 32.f});
    }

    /*!
     * \brief Initialize with value
     * \param _initialAmbient Initial ambient color at time-step == 0
     * \param _initialDiffuse Initial diffuse color at time-step == 0
     */
    inline void initValue(const QColor &_initialAmbient, const QColor &_initialDiffuse)
    {
        initValue(
            Math::MaterialRGB{Math::ColorRGB(_initialAmbient), Math::ColorRGB(_initialDiffuse), {255, 255, 255}, 32.f});
    }

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const Math::ColorRGB &_initialValue)
    {
        initValue(Math::MaterialRGB{_initialValue.darker(), _initialValue, {255, 255, 255}, 32.f});
    }

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const QColor &_initialValue)
    {
        initValue(Math::MaterialRGB{
            Math::ColorRGB(_initialValue.darker()), Math::ColorRGB(_initialValue), {255, 255, 255}, 32.f});
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::MaterialRGB &_value)
    {
        ambient.initValueUpTo(_timeStep, _value.ambient);
        diffuse.initValueUpTo(_timeStep, _value.diffuse);
        specular.initValueUpTo(_timeStep, _value.specular);
        shine.initValueUpTo(_timeStep, _value.shine);
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _ambient Initial ambient color at time-step == 0 up to given time-step
     * \param _diffuse Initial diffuse color at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::ColorRGB &_ambient, const Math::ColorRGB &_diffuse)
    {
        initValueUpTo(_timeStep, Math::MaterialRGB{_ambient, _diffuse, {255, 255, 255}, 32.0f});
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _ambient Initial ambient color at time-step == 0 up to given time-step
     * \param _diffuse Initial diffuse color at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const QColor &_ambient, const QColor &_diffuse)
    {
        initValueUpTo(_timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        initValueUpTo(_timeStep, Math::MaterialRGB{_value.darker(), _value, {255, 255, 255}, 32.0f});
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const QColor &_value)
    {
        initValueUpTo(_timeStep, Math::ColorRGB(_value));
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::MaterialRGB &_value)
    {
        ambient.addConstantValue(_timeStep, _value.ambient);
        diffuse.addConstantValue(_timeStep, _value.diffuse);
        specular.addConstantValue(_timeStep, _value.specular);
        shine.addConstantValue(_timeStep, _value.shine);
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::ColorRGB &_ambient, const Math::ColorRGB &_diffuse)
    {
        addConstantValue(_timeStep, Math::MaterialRGB{_ambient, _diffuse, {255, 255, 255}, 32.0f});
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const QColor &_ambient, const QColor &_diffuse)
    {
        addConstantValue(_timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        addConstantValue(_timeStep, _value.darker(), _value);
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const QColor &_value)
    {
        addConstantValue(_timeStep, _value.darker(), _value);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::MaterialRGB &_value)
    {
        ambient.addLinearValue(_timeStep, _value.ambient);
        diffuse.addLinearValue(_timeStep, _value.diffuse);
        specular.addLinearValue(_timeStep, _value.specular);
        shine.addLinearValue(_timeStep, _value.shine);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::ColorRGB &_ambient, const Math::ColorRGB &_diffuse)
    {
        addLinearValue(_timeStep, Math::MaterialRGB{_ambient, _diffuse, {255, 255, 255}, 32.0f});
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const QColor &_ambient, const QColor &_diffuse)
    {
        addLinearValue(_timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        addLinearValue(_timeStep, _value.darker(), _value);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const QColor &_value)
    {
        addLinearValue(_timeStep, _value.darker(), _value);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::MaterialRGB &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        ambient.addAcceleratedValue(_timeStep, _value.ambient, _acceleration, _deceleration);
        diffuse.addAcceleratedValue(_timeStep, _value.diffuse, _acceleration, _deceleration);
        specular.addAcceleratedValue(_timeStep, _value.specular, _acceleration, _deceleration);
        shine.addAcceleratedValue(_timeStep, _value.shine, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::ColorRGB &_ambient,
                                    const Math::ColorRGB &_diffuse,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(
            _timeStep, Math::MaterialRGB{_ambient, _diffuse, {255, 255, 255}, 32.0f}, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const QColor &_ambient,
                                    const QColor &_diffuse,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(
            _timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse), _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::ColorRGB &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(_timeStep, _value.darker(), _value, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const QColor &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(_timeStep, _value.darker(), _value, _acceleration, _deceleration);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const Math::MaterialRGB &_value)
    {
        ambient.addFromLinearValue(_timeStart, _timeStop, _value.ambient);
        diffuse.addFromLinearValue(_timeStart, _timeStop, _value.diffuse);
        specular.addFromLinearValue(_timeStart, _timeStop, _value.specular);
        shine.addFromLinearValue(_timeStart, _timeStop, _value.shine);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart,
                                   const size_t _timeStop,
                                   const Math::ColorRGB &_ambient,
                                   const Math::ColorRGB &_diffuse)
    {
        addFromLinearValue(_timeStart, _timeStop, Math::MaterialRGB{_ambient, _diffuse, {255, 255, 255}, 32.0f});
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     */
    inline void
    addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const QColor &_ambient, const QColor &_diffuse)
    {
        addFromLinearValue(_timeStart, _timeStop, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const Math::ColorRGB &_value)
    {
        addFromLinearValue(_timeStart, _timeStop, _value.darker(), _value);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const QColor &_value)
    {
        addFromLinearValue(_timeStart, _timeStop, _value.darker(), _value);
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
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::MaterialRGB &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        ambient.addFromAcceleratedValue(_timeStart, _timeStop, _value.ambient, _acceleration, _deceleration);
        diffuse.addFromAcceleratedValue(_timeStart, _timeStop, _value.diffuse, _acceleration, _deceleration);
        specular.addFromAcceleratedValue(_timeStart, _timeStop, _value.specular, _acceleration, _deceleration);
        shine.addFromAcceleratedValue(_timeStart, _timeStop, _value.shine, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::ColorRGB &_ambient,
                                        const Math::ColorRGB &_diffuse,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart,
                                _timeStop,
                                Math::MaterialRGB{_ambient, _diffuse, {255, 255, 255}, 32.0f},
                                _acceleration,
                                _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const QColor &_ambient,
                                        const QColor &_diffuse,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(
            _timeStart, _timeStop, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse), _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::ColorRGB &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart, _timeStop, _value.darker(), _value, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const QColor &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart, _timeStop, _value.darker(), _value, _acceleration, _deceleration);
    }
};

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*! \brief Material with alpha - dynamic item property group */
class ItemPropertyMaterialRGBA : public ItemPropertyGroup
{
 public:
    ItemPropertyColor ambient;   //!< Ambient dynamic color
    ItemPropertyColor diffuse;   //!< Diffuse dynamic color
    ItemPropertyColor specular;  //!< Specular dynamic color
    ItemPropertyFloat shine;     //!< Shine dynamic variable
    ItemPropertyUInt8 alpha;     //!< Alpha dynamic variable

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial material
     */
    ItemPropertyMaterialRGBA(const std::string &_name, const Math::MaterialRGBA &_initialValue);

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialValue Initial material
     */
    inline ItemPropertyMaterialRGBA(const std::string &_name, const Math::MaterialRGB &_initialValue)
        : ItemPropertyMaterialRGBA(
              _name,
              Math::MaterialRGBA{
                  _initialValue.ambient, _initialValue.diffuse, _initialValue.specular, _initialValue.shine, 255U})
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialAmbient Initial ambient color
     * \param _initialDiffuse Initial diffuse color
     */
    inline ItemPropertyMaterialRGBA(const std::string &_name,
                                    const Math::ColorRGB &_initialAmbient,
                                    const Math::ColorRGB &_initialDiffuse)
        : ItemPropertyMaterialRGBA(
              _name, Math::MaterialRGBA{_initialAmbient, _initialDiffuse, {255U, 255U, 255U}, 32.0f, 255U})
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialAmbient Initial ambient color
     * \param _initialDiffuse Initial diffuse color
     */
    inline ItemPropertyMaterialRGBA(const std::string &_name,
                                    const QColor &_initialAmbient,
                                    const QColor &_initialDiffuse)
        : ItemPropertyMaterialRGBA(
              _name,
              Math::MaterialRGBA{
                  Math::ColorRGB(_initialAmbient), Math::ColorRGB(_initialDiffuse), {255U, 255U, 255U}, 32.0f, 255U})
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialColor Initial color
     */
    inline ItemPropertyMaterialRGBA(const std::string &_name, const Math::ColorRGB &_initialColor)
        : ItemPropertyMaterialRGBA(_name, _initialColor.darker(), _initialColor)
    {
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _initialColor Initial color
     */
    inline ItemPropertyMaterialRGBA(const std::string &_name, const QColor &_initialColor)
        : ItemPropertyMaterialRGBA(_name, _initialColor.darker(), _initialColor)
    {
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Returns value at given time-step
     * \param _timeStep Time-step
     * \return Value at given time-step
     */
    inline Math::MaterialRGBA value(const size_t _timeStep) const
    {
        return Math::MaterialRGBA{ambient.value(_timeStep),
                                  diffuse.value(_timeStep),
                                  specular.value(_timeStep),
                                  shine.value(_timeStep),
                                  alpha.value(_timeStep)};
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const Math::MaterialRGBA &_initialValue)
    {
        ambient.initValue(_initialValue.ambient);
        diffuse.initValue(_initialValue.diffuse);
        specular.initValue(_initialValue.specular);
        shine.initValue(_initialValue.shine);
        alpha.initValue(_initialValue.alpha);
    }

    /*!
     * \brief Initialize with value
     * \param _initialAmbient Initial ambient color at time-step == 0
     * \param _initialDiffuse Initial diffuse color at time-step == 0
     */
    inline void initValue(const Math::ColorRGB &_initialAmbient, const Math::ColorRGB &_initialDiffuse)
    {
        initValue(Math::MaterialRGBA{_initialAmbient, _initialDiffuse, {255, 255, 255}, 32.f, 255U});
    }

    /*!
     * \brief Initialize with value
     * \param _initialAmbient Initial ambient color at time-step == 0
     * \param _initialDiffuse Initial diffuse color at time-step == 0
     */
    inline void initValue(const QColor &_initialAmbient, const QColor &_initialDiffuse)
    {
        initValue(Math::MaterialRGBA{
            Math::ColorRGB(_initialAmbient), Math::ColorRGB(_initialDiffuse), {255, 255, 255}, 32.f, 255U});
    }

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const Math::ColorRGB &_initialValue)
    {
        initValue(Math::MaterialRGBA{_initialValue.darker(), _initialValue, {255, 255, 255}, 32.f, 255U});
    }

    /*!
     * \brief Initialize with value
     * \param _initialValue Initial value at time-step == 0
     */
    inline void initValue(const QColor &_initialValue)
    {
        initValue(Math::MaterialRGBA{Math::ColorRGB(_initialValue.darker()),
                                     Math::ColorRGB(_initialValue),
                                     {255, 255, 255},
                                     32.f,
                                     uint8_t(_initialValue.alpha())});
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::MaterialRGBA &_value)
    {
        ambient.initValueUpTo(_timeStep, _value.ambient);
        diffuse.initValueUpTo(_timeStep, _value.diffuse);
        specular.initValueUpTo(_timeStep, _value.specular);
        shine.initValueUpTo(_timeStep, _value.shine);
        alpha.initValueUpTo(_timeStep, _value.alpha);
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _ambient Ambient color at time-step == 0 up to given time-step
     * \param _diffuse Diffuse color at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::ColorRGB &_ambient, const Math::ColorRGB &_diffuse)
    {
        initValueUpTo(_timeStep, Math::MaterialRGBA{_ambient, _diffuse, {255, 255, 255}, 32.0f, 255U});
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _ambient Ambient color at time-step == 0 up to given time-step
     * \param _diffuse Diffuse color at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const QColor &_ambient, const QColor &_diffuse)
    {
        initValueUpTo(_timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        initValueUpTo(_timeStep, Math::MaterialRGBA{_value.darker(), _value, {255, 255, 255}, 32.0f, 255U});
    }

    /*!
     * \brief Initialize with value up to given time-step
     * \param _timeStep Time-step to keep value up to
     * \param _value Initial value at time-step == 0 up to given time-step
     */
    inline void initValueUpTo(const size_t _timeStep, const QColor &_value)
    {
        initValueUpTo(_timeStep, Math::ColorRGB(_value));
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::MaterialRGBA &_value)
    {
        ambient.addConstantValue(_timeStep, _value.ambient);
        diffuse.addConstantValue(_timeStep, _value.diffuse);
        specular.addConstantValue(_timeStep, _value.specular);
        shine.addConstantValue(_timeStep, _value.shine);
        alpha.addConstantValue(_timeStep, _value.alpha);
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::ColorRGB &_ambient, const Math::ColorRGB &_diffuse)
    {
        addConstantValue(_timeStep, Math::MaterialRGBA{_ambient, _diffuse, {255, 255, 255}, 32.0f, 255U});
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const QColor &_ambient, const QColor &_diffuse)
    {
        addConstantValue(_timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        addConstantValue(_timeStep, _value.darker(), _value);
    }

    /*!
     * \brief Append constant value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addConstantValue(const size_t _timeStep, const QColor &_value)
    {
        addConstantValue(_timeStep, _value.darker(), _value);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::MaterialRGBA &_value)
    {
        ambient.addLinearValue(_timeStep, _value.ambient);
        diffuse.addLinearValue(_timeStep, _value.diffuse);
        specular.addLinearValue(_timeStep, _value.specular);
        shine.addLinearValue(_timeStep, _value.shine);
        alpha.addLinearValue(_timeStep, _value.alpha);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::ColorRGB &_ambient, const Math::ColorRGB &_diffuse)
    {
        addLinearValue(_timeStep, Math::MaterialRGBA{_ambient, _diffuse, {255, 255, 255}, 32.0f, 255U});
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const QColor &_ambient, const QColor &_diffuse)
    {
        addLinearValue(_timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const Math::ColorRGB &_value)
    {
        addLinearValue(_timeStep, _value.darker(), _value);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     */
    inline void addLinearValue(const size_t _timeStep, const QColor &_value)
    {
        addLinearValue(_timeStep, _value.darker(), _value);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::MaterialRGBA &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        ambient.addAcceleratedValue(_timeStep, _value.ambient, _acceleration, _deceleration);
        diffuse.addAcceleratedValue(_timeStep, _value.diffuse, _acceleration, _deceleration);
        specular.addAcceleratedValue(_timeStep, _value.specular, _acceleration, _deceleration);
        shine.addAcceleratedValue(_timeStep, _value.shine, _acceleration, _deceleration);
        alpha.addAcceleratedValue(_timeStep, _value.alpha, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::ColorRGB &_ambient,
                                    const Math::ColorRGB &_diffuse,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(_timeStep,
                            Math::MaterialRGBA{_ambient, _diffuse, {255, 255, 255}, 32.0f, 255U},
                            _acceleration,
                            _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _ambient Ambient color to set at given time-step
     * \param _diffuse Diffuse color to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const QColor &_ambient,
                                    const QColor &_diffuse,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(
            _timeStep, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse), _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const Math::ColorRGB &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(_timeStep, _value.darker(), _value, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStep Time-step for value
     * \param _value Value to set at given time-step
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addAcceleratedValue(const size_t _timeStep,
                                    const QColor &_value,
                                    const double _acceleration,
                                    const double _deceleration)
    {
        addAcceleratedValue(_timeStep, _value.darker(), _value, _acceleration, _deceleration);
    }

    // /////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const Math::MaterialRGBA &_value)
    {
        ambient.addFromLinearValue(_timeStart, _timeStop, _value.ambient);
        diffuse.addFromLinearValue(_timeStart, _timeStop, _value.diffuse);
        specular.addFromLinearValue(_timeStart, _timeStop, _value.specular);
        shine.addFromLinearValue(_timeStart, _timeStop, _value.shine);
        alpha.addFromLinearValue(_timeStart, _timeStop, _value.alpha);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart,
                                   const size_t _timeStop,
                                   const Math::ColorRGB &_ambient,
                                   const Math::ColorRGB &_diffuse)
    {
        addFromLinearValue(_timeStart, _timeStop, Math::MaterialRGBA{_ambient, _diffuse, {255, 255, 255}, 32.0f, 255U});
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     */
    inline void
    addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const QColor &_ambient, const QColor &_diffuse)
    {
        addFromLinearValue(_timeStart, _timeStop, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse));
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const Math::ColorRGB &_value)
    {
        addFromLinearValue(_timeStart, _timeStop, _value.darker(), _value);
    }

    /*!
     * \brief Append linearly distributed value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     */
    inline void addFromLinearValue(const size_t _timeStart, const size_t _timeStop, const QColor &_value)
    {
        addFromLinearValue(_timeStart, _timeStop, _value.darker(), _value);
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
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::MaterialRGBA &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        ambient.addFromAcceleratedValue(_timeStart, _timeStop, _value.ambient, _acceleration, _deceleration);
        diffuse.addFromAcceleratedValue(_timeStart, _timeStop, _value.diffuse, _acceleration, _deceleration);
        specular.addFromAcceleratedValue(_timeStart, _timeStop, _value.specular, _acceleration, _deceleration);
        shine.addFromAcceleratedValue(_timeStart, _timeStop, _value.shine, _acceleration, _deceleration);
        alpha.addFromAcceleratedValue(_timeStart, _timeStop, _value.alpha, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::ColorRGB &_ambient,
                                        const Math::ColorRGB &_diffuse,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart,
                                _timeStop,
                                Math::MaterialRGBA{_ambient, _diffuse, {255, 255, 255}, 32.0f, 255U},
                                _acceleration,
                                _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _ambient Ambient color to reach at time-step: \c _timeStop
     * \param _diffuse Diffuse color to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const QColor &_ambient,
                                        const QColor &_diffuse,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(
            _timeStart, _timeStop, Math::ColorRGB(_ambient), Math::ColorRGB(_diffuse), _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const Math::ColorRGB &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart, _timeStop, _value.darker(), _value, _acceleration, _deceleration);
    }

    /*!
     * \brief Append accelerated value to property jobs
     * \param _timeStart Starting time-step for linear distribution
     * \param _timeStop Finish time-step for linear distribution (time when \c _value is reached)
     * \param _value Value to reach at time-step: \c _timeStop
     * \param _acceleration Acceleration interval (0 to 1)
     * \param _deceleration Deceleration interval (0 to 1)
     */
    inline void addFromAcceleratedValue(const size_t _timeStart,
                                        const size_t _timeStop,
                                        const QColor &_value,
                                        const double _acceleration,
                                        const double _deceleration)
    {
        addFromAcceleratedValue(_timeStart, _timeStop, _value.darker(), _value, _acceleration, _deceleration);
    }

};

}  // namespace Props
}  // namespace U1

#endif  // PROPS_ITEMPROPERTYMATERIAL_H
