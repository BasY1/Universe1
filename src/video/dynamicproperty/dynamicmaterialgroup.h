#ifndef UNIVERSE1_VIDEO_DYNAMICMATERIALGROUP_H
#define UNIVERSE1_VIDEO_DYNAMICMATERIALGROUP_H

#include "dynamiccolor.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic color property
 */
struct DynamicMaterialGroup
{
    DynamicColor ambient;       //!< Ambient color property
    DynamicColor diffuse;       //!< Diffuse color property
    DynamicColor specular;      //!< Specular color property
    DynamicValue<float> shine;  //!< Shine factor property
    DynamicValue<float> alpha;  //!< Alpha factor property

    /*!
     * \brief Constructor
     * \param _value Initial color
     * \param _name Property name
     * \param _allProps All item properties
     * \param _allMaterials All item materials
     */
    DynamicMaterialGroup(const QColor _value,
                         const std::string &_name,
                         std::list<DynamicProperty *> &_allProps,
                         std::list<DynamicMaterialGroup *> _allMaterials);

    /*!
     * \brief Constructor
     * \param _material Initial color
     * \param _name Property name
     * \param _allProps All item properties
     * \param _allMaterials All item materials
     */
    DynamicMaterialGroup(const Material &_material,
                         const std::string &_name,
                         std::list<DynamicProperty *> &_allProps,
                         std::list<DynamicMaterialGroup *> _allMaterials);

 private:
    /*!
     * \brief Add properties into collection
     * \param _allProps All item properties
     * \param _allMaterials All item materials
     */
    inline void setupProps(std::list<DynamicProperty *> &_allProps, std::list<DynamicMaterialGroup *> _allMaterials)
    {
        _allProps.push_back(&ambient);
        _allProps.push_back(&diffuse);
        _allProps.push_back(&specular);
        _allProps.push_back(&shine);
        _allProps.push_back(&alpha);
        _allMaterials.push_back(this);
    }

 public:
    /*!
     * \brief Returns material value at specific time-step
     * \param _timeStep Time-step
     * \return Value at specific time-step
     */
    inline Material getValue(const uint64_t _timeStep) const
    {
        return Material(ambient.getValue(_timeStep),
                        diffuse.getValue(_timeStep),
                        specular.getValue(_timeStep),
                        shine.getValue(_timeStep),
                        alpha.getValue(_timeStep));
    }

    /*!
     * \brief Assign operator, setup value to last item in data list
     * \param _material Value to set
     * \return This object
     */
    inline DynamicMaterialGroup &operator=(const Material &_material)
    {
        ambient = _material.ambient;
        diffuse = _material.diffuse;
        specular = _material.specular;
        shine = _material.shine;
        alpha = _material.alpha;
        return *this;
    }

    /*!
     * \brief Assign operator, setup value to last item in data list
     * \param _color Value to set
     * \return This object
     */
    inline DynamicMaterialGroup &operator=(const QColor &_color)
    {
        ambient = _color.darker();
        diffuse = _color;
        return *this;
    }

    /*!
     * \brief Add same value as last stored at time-step
     * \param _timeStep Time-step
     */
    inline void addSame(const uint64_t _timeStep)
    {
        ambient.addSame(_timeStep);
        diffuse.addSame(_timeStep);
        specular.addSame(_timeStep);
        shine.addSame(_timeStep);
        alpha.addSame(_timeStep);
    }

    /*!
     * \brief Add new value at time-step
     * \param _timeStep Time-step
     * \param _material Value at time-step
     */
    inline void add(const uint64_t _timeStep, const Material &_material)
    {
        ambient.add(_timeStep, _material.ambient);
        diffuse.add(_timeStep, _material.diffuse);
        specular.add(_timeStep, _material.specular);
        shine.add(_timeStep, _material.shine);
        alpha.add(_timeStep, _material.alpha);
    }

    /*!
     * \brief Add new value at time-step
     * \param _timeStep Time-step
     * \param _color Value at time-step
     */
    inline void add(const uint64_t _timeStep, const QColor &_color)
    {
        ambient.add(_timeStep, _color.darker());
        diffuse.add(_timeStep, _color);
        specular.addSame(_timeStep);
        shine.addSame(_timeStep);
        alpha.addSame(_timeStep);
    }

    /*!
     * \brief Add same value as last stored at start time-step and new value at end time-step
     * \param _timeStepStart Jump start time
     * \param _timeStepEnd Jump end time
     * \param _material New value
     */
    inline void addJump(const uint64_t _timeStepStart, const uint64_t _timeStepEnd, const Material &_material)
    {
        ambient.addJump(_timeStepStart, _timeStepEnd, _material.ambient);
        diffuse.addJump(_timeStepStart, _timeStepEnd, _material.diffuse);
        specular.addJump(_timeStepStart, _timeStepEnd, _material.specular);
        shine.addJump(_timeStepStart, _timeStepEnd, _material.shine);
        alpha.addJump(_timeStepStart, _timeStepEnd, _material.alpha);
    }

    /*!
     * \brief Add same value as last stored at start time-step and new value at end time-step
     * \param _timeStepStart Jump start time
     * \param _timeStepEnd Jump end time
     * \param _color New value
     */
    inline void addJump(const uint64_t _timeStepStart, const uint64_t _timeStepEnd, const QColor &_color)
    {
        ambient.addJump(_timeStepStart, _timeStepEnd, _color.darker());
        diffuse.addJump(_timeStepStart, _timeStepEnd, _color);
        specular.addSame(_timeStepEnd);
        shine.addSame(_timeStepEnd);
        alpha.addSame(_timeStepEnd);
    }

    /*!
     * \brief Add loop values
     * \param _timeStepStart Start time ms
     * \param _timeStepEnd End time ms
     * \param _value1 First value
     * \param _value2 Second value
     * \param _durationValue1toValue2 Duration swap value1 to value2
     * \param _durationValue2toValue1 Duration swap value2 to value1
     */
    inline void addLoop(const uint64_t _timeStepStart,
                        const uint64_t _timeStepEnd,
                        const Material &_value1,
                        const Material &_value2,
                        const uint64_t _durationValue1toValue2 = 1000UL,
                        const uint64_t _durationValue2toValue1 = 1000UL)
    {
        ambient.addLoop(_timeStepStart,
                        _timeStepEnd,
                        _value1.ambient,
                        _value2.ambient,
                        _durationValue1toValue2,
                        _durationValue2toValue1);
        diffuse.addLoop(_timeStepStart,
                        _timeStepEnd,
                        _value1.diffuse,
                        _value2.diffuse,
                        _durationValue1toValue2,
                        _durationValue2toValue1);
        specular.addLoop(_timeStepStart,
                         _timeStepEnd,
                         _value1.specular,
                         _value2.specular,
                         _durationValue1toValue2,
                         _durationValue2toValue1);
        shine.addLoop(_timeStepStart,
                      _timeStepEnd,
                      _value1.shine,
                      _value2.shine,
                      _durationValue1toValue2,
                      _durationValue2toValue1);
        alpha.addLoop(_timeStepStart,
                      _timeStepEnd,
                      _value1.alpha,
                      _value2.alpha,
                      _durationValue1toValue2,
                      _durationValue2toValue1);
    }

    /*!
     * \brief Add loop values
     * \param _timeStepStart Start time ms
     * \param _timeStepEnd End time ms
     * \param _value Second value
     * \param _durationValue1toValue2 Duration swap value1 to value2
     * \param _durationValue2toValue1 Duration swap value2 to value1
     */
    inline void addLoop(const uint64_t _timeStepStart,
                        const uint64_t _timeStepEnd,
                        const Material &_value,
                        const uint64_t _durationValue1toValue2,
                        const uint64_t _durationValue2toValue1)
    {
        if (!ambient.values.empty() && !diffuse.values.empty() && !specular.values.empty() && !shine.values.empty() &&
            !alpha.values.empty())
            addLoop(_timeStepStart,
                    _timeStepEnd,
                    Material(ambient.values.back().second,
                             diffuse.values.back().second,
                             specular.values.back().second,
                             shine.values.back().second,
                             alpha.values.back().second),
                    _value,
                    _durationValue1toValue2,
                    _durationValue2toValue1);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICMATERIALGROUP_H
