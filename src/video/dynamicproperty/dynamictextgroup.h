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
    DynamicAlign align;            //!< Align property
    DynamicValue<float> sizeMult;  //!< Size multiplier

    /*!
     * \brief Constructor
     * \param _text Initial text
     * \param _align Initial align
     * \param _sizeMult Initial size multiplier
     * \param _itemName Item name
     * \param _props Output dynamic property collection
     */
    inline DynamicTextGroup(const QString &_text,
                            const Qt::Alignment &_align,
                            const float _sizeMult,
                            const std::string &_itemName,
                            std::list<DynamicProperty *> &_props)
        : text(_text, _itemName + ".text")
        , align(_align, _itemName + ".align")
        , sizeMult(_sizeMult, _itemName + ".sizeMult")
    {
        _props.push_back(&text);
        _props.push_back(&align);
        _props.push_back(&sizeMult);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H
