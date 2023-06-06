#ifndef UNIVERSE1_VIDEO_DYNAMICANGLEGROUP_H
#define UNIVERSE1_VIDEO_DYNAMICANGLEGROUP_H

#include "dynamictextgroup.h"

namespace Universe1 {
namespace Video {

/*! \brief Dynamic property group for constellation angles */
struct DynamicAngleGroup
{
    DynamicBool show;                        //!< Angle visible flag
    DynamicBool showText;                    //!< Angle text visible flag
    DynamicValue<float> angleOffset;         //!< Angle offset
    DynamicValue<float> radiusLine;          //!< Angle line radius
    DynamicValue<float> arrowLength;         //!< Arrow length
    DynamicValue<float> arrowRadius;         //!< Arrow header radius
    DynamicValue<float> textSize;            //!< Angle text size multiplier
    DynamicEnum<TextPosition> textPosition;  //!< Angle text position
    DynamicAlign textAlign;                  //!< Angle text align
    DynamicMaterialGroup material;           //!< Angle material

    /*!
     * \brief Constructor
     * \param _show Initial visible flag
     * \param _showText Initial text visible flag
     * \param _angleOffset Initial offset
     * \param _radiusLine Initial line radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _textSize Initial text size multiplier
     * \param _textPosition Initial text position
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \param _name Group name
     * \param _allProps All item properties
     * \param _allMaterials All item materials
     */
    DynamicAngleGroup(const bool _show,
                      const bool _showText,
                      const float _angleOffset,
                      const float _radiusLine,
                      const float _arrowLength,
                      const float _arrowRadius,
                      const float _textSize,
                      const TextPosition _textPosition,
                      const Qt::Alignment _textAlign,
                      const Material &_material,
                      const std::string &_name,
                      std::list<DynamicProperty *> &_allProps,
                      std::list<DynamicMaterialGroup *> &_allMaterials);
};


}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICANGLEGROUP_H
