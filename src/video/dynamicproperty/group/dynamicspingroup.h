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
     * \param _material Initial main material
     * \param _name Group name
     * \param _allProps All item properties
     * \param _allMaterials All item materials
     */
    DynamicSpinGroup(const Material &_material,
                     const std::string &_name,
                     std::list<DynamicProperty *> &_allProps,
                     std::list<DynamicMaterialGroup *> &_allMaterials);
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_DYNAMICSPINGROUP_H
