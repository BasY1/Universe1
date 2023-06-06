#ifndef UNIVERSE1_VIDEO_DYNAMICSPINGROUP_H
#define UNIVERSE1_VIDEO_DYNAMICSPINGROUP_H

#include "dynamicanglegroup.h"

namespace Universe1 {
namespace Video {

/*! \brief Dynamic property group for constellation spins */
struct DynamicSpinGroup
{
    DynamicBool show;        //!< Spin visible flag
    DynamicBool showVector;  //!< Show spin vector flag
    DynamicBool showAxis;    //!< Show spin axis flag
    DynamicBool showArrows;  //!< Show spin arrows flag
    DynamicBool showDots;    //!< Show spin dots flag
    DynamicBool showSphere;  //!< Show spin sphere flag
    DynamicBool showText;    //!< Show spin text flag

    DynamicValue<float> radiusVector;        //!< Radius spin line
    DynamicValue<float> radiusLineAxis;      //!< Radius axis line
    DynamicValue<float> radiusLineSphere;    //!< Radius sphere line
    DynamicValue<float> radiusDots;          //!< Radius dots
    DynamicValue<float> twistStep;           //!< Twist step
    DynamicValue<float> arrowDirOffset;      //!< Arrow offset over line for spin
    DynamicValue<float> arrowArmOffset;      //!< Arrow offset to side of line for spin
    DynamicValue<float> arrowLength;         //!< Arrow length
    DynamicValue<float> arrowRadius;         //!< Arrow header radius
    DynamicValue<float> textSize;            //!< Spin text size multiplier
    DynamicEnum<TextPosition> textPosition;  //!< Spin text position
    DynamicAlign textAlign;                  //!< Spin text align

    DynamicValue<uint> dotsCount;  //!< Dot count
    DynamicValue<uint> multAxis;   //!< Space multiplier for axis dash-dot profile

    DynamicMaterialGroup material;  //!< Main material

    /*!
     * \brief Constructor
     * \param _show Initial spin visible flag
     * \param _showVector Initial show spin vector flag
     * \param _showAxis Initial show spin axis flag
     * \param _showArrows Initial show spin arrows flag
     * \param _showDots Initial show spin dots flag
     * \param _showSphere Initial show spin sphere flag
     * \param _showText Initial show spin text flag
     * \param _radiusVector Initial radius spin line
     * \param _radiusLineAxis Initial radius axis line
     * \param _radiusLineSphere Initial radius sphere line
     * \param _radiusDots Initial radius dots
     * \param _twistStep Initial twist step
     * \param _arrowDirOffset Initial arrow offset over line for spin
     * \param _arrowArmOffset Initial arrow offset to side of line for spin
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _textSize Initial spin text size multiplier
     * \param _textPosition Initial spin text position
     * \param _textAlign Initial spin text align
     * \param _dotsCount  Initial dot count
     * \param _multAxis Initial space multiplier for axis dash-dot profile
     * \param _material Initial main material
     * \param _name Group name
     * \param _allProps All item properties
     * \param _allMaterials All item materials
     */
    DynamicSpinGroup(const bool _show,
                     const bool _showVector,
                     const bool _showAxis,
                     const bool _showArrows,
                     const bool _showDots,
                     const bool _showSphere,
                     const bool _showText,
                     const float _radiusVector,
                     const float _radiusLineAxis,
                     const float _radiusLineSphere,
                     const float _radiusDots,
                     const float _twistStep,
                     const float _arrowDirOffset,
                     const float _arrowArmOffset,
                     const float _arrowLength,
                     const float _arrowRadius,
                     const float _textSize,
                     const TextPosition _textPosition,
                     const Qt::Alignment _textAlign,
                     const uint _dotsCount,
                     const uint _multAxis,
                     const Material &_material,
                     const std::string &_name,
                     std::list<DynamicProperty *> &_allProps,
                     std::list<DynamicMaterialGroup *> &_allMaterials);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICSPINGROUP_H
