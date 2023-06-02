#ifndef UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H
#define UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H

#include "dynamicstring.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Dynamic text related properties group
 */
struct DynamicTextGroup
{
    DynamicString text;            //!< Text property
    DynamicValue<float> sizeMult;  //!< Size multiplier
    DynamicAlign align;            //!< Align property

    /*!
     * \brief Constructor
     * \param _text Initial text
     * \param _sizeMult Initial size multiplier
     * \param _align Initial align
     * \param _itemName Item name
     * \param _props Output dynamic property collection
     */
    inline DynamicTextGroup(const QString &_text,
                            const float _sizeMult,
                            const Qt::Alignment &_align,
                            const std::string &_itemName,
                            std::list<DynamicProperty *> &_props)
        : text(_text, _itemName + ".text")
        , sizeMult(_sizeMult, _itemName + ".sizeMult")
        , align(_align, _itemName + ".align")
    {
        _props.push_back(&text);
        _props.push_back(&align);
        _props.push_back(&sizeMult);
    }

    /*!
     * \brief Add same value as last stored at time-step (\a sizeMult only)
     * \param _timeStep Time-step
     */
    inline void addSame(const uint64_t _timeStep)
    {
        sizeMult.addSame(_timeStep);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H
