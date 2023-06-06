#ifndef UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H
#define UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H

#include "dynamicmaterialgroup.h"

namespace Universe1 {
namespace Video {

/*! \brief Supported text position over arrow line */
enum TextPosition
{
    _TextAtPointFrom,  //!< Draw text near point \b from
    _TextMiddle,       //!< Draw text in the middle of the arrow line
    _TextAtPointTo     //!< Draw text near point \b to
};

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

/*!
 * \brief Dynamic text related properties group
 */
struct DynamicTextGroupExt : public DynamicTextGroup
{
    DynamicBool show;                    //!< Show text flag
    DynamicEnum<TextPosition> position;  //!< Text position over arrow line

    /*!
     * \brief Constructor
     * \param _text Initial text
     * \param _sizeMult Initial size multiplier
     * \param _align Initial align
     * \param _show Initial show text flag
     * \param _position Initial text position over arrow line
     * \param _itemName Item name
     * \param _props Output dynamic property collection
     */
    inline DynamicTextGroupExt(const QString &_text,
                               const float _sizeMult,
                               const Qt::Alignment &_align,
                               const TextPosition &_position,
                               const bool &_show,
                               const std::string &_itemName,
                               std::list<DynamicProperty *> &_props)
        : DynamicTextGroup(_text, _sizeMult, _align, _itemName, _props)
        , show(_show, _itemName + ".show")
        , position(_position, _itemName + ".position")
    {
        _props.push_back(&show);
        _props.push_back(&position);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICTEXTGROUP_H
