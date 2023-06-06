#ifndef UNIVERSE1_VIDEO_ITEM3DSPIN_H
#define UNIVERSE1_VIDEO_ITEM3DSPIN_H

#include "../hand/item3dhand.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D spinning item */
struct Item3DSpin : public Item3D
{
    // clang-format off
    static const uint8_t _SPIN_VECTOR = 0b00000001;  //!< Bit for show vector value
    static const uint8_t _SPIN_AXIS   = 0b00000010;  //!< Bit for show axis value
    static const uint8_t _SPIN_ARROWS = 0b00000100;  //!< Bit for show arrows value
    static const uint8_t _SPIN_DOTS   = 0b00001000;  //!< Bit for show dots value
    static const uint8_t _SPIN_SPHERE = 0b00010000;  //!< Bit for show sphere value
    static const uint8_t _SPIN_TEXT   = 0b00100000;  //!< Bit for show text value
    // clang-format on

    DynamicBool showVector;  //!< Show vector
    DynamicBool showAxis;    //!< Show axis
    DynamicBool showArrows;  //!< Show arrows
    DynamicBool showDots;    //!< Show dots
    DynamicBool showSphere;  //!< Show sphere

    DynamicVec3 center;  //!< Center point
    DynamicVec3 normal;  //!< Main normal
    DynamicVec3 arm;     //!< Arm direction

    DynamicValue<float> phaseDeg;          //!< Main rotation phase for spin
    DynamicValue<float> lengthVector;      //!< Vector length
    DynamicValue<float> radiusSphere;      //!< Sphere radius
    DynamicValue<float> radiusVector;      //!< Vector line radius
    DynamicValue<float> radiusLineAxis;    //!< Axis line radius
    DynamicValue<float> radiusLineSphere;  //!< Wire-sphere line radius
    DynamicValue<float> radiusDots;        //!< Dot points radius
    DynamicValue<float> twistStep;         //!< Twist step
    DynamicValue<float> arrowDirOffset;    //!< Arrow offset over line for spin
    DynamicValue<float> arrowArmOffset;    //!< Arrow offset to side of line for spin
    DynamicValue<float> arrowLength;       //!< Arrow length
    DynamicValue<float> arrowRadius;       //!< Arrow header radius
    DynamicValue<uint> arrowCount;         //!< Count of arrows
    DynamicValue<uint> dotsCount;          //!< Count of dots
    DynamicValue<uint> multAxis;           //!< Space multiplier for axis dash-dot profile
    DynamicValue<uint> qualityLatLong;     //!< Quality latitude-longitude circle
    DynamicValue<uint> qualitySphere;      //!< Quality sphere circle
    DynamicValue<uint> qualityLine;        //!< Quality line circle

    std::vector<DynamicMaterialGroup> spinMaterials;  //!< Used materials

    DynamicTextGroupExt text;  //!< Text properties group

    /*!
     * \brief Constructor
     * \param _showFlags Initial show flags as bit buffer
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _phaseDeg Initial main rotation phase for spin
     * \param _lengthVector Initial vector length
     * \param _radiusSphere Initial sphere radius
     * \param _radiusVector Initial vector line radius
     * \param _radiusLineAxis Initial axis line radius
     * \param _radiusLineSphere Initial wire-sphere line radius
     * \param _radiusDots Initial dot points radius
     * \param _twistStep Initial twist step
     * \param _arrowDirOffset Initial arrow offset over line for spin
     * \param _arrowArmOffset Initial arrow offset to side of line for spin
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _arrowCount Initial count of arrows
     * \param _dotsCount Initial count of dots
     * \param _multAxis Initial space multiplier for axis dash-dot profile
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _text Initial text
     * \param _textPosition Initial text position over spin vector line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _visible Initial visible flag
     * \param _materials Initial materials
     * \param _name Item name
     */
    Item3DSpin(const uint8_t _showFlags,
               const QVector3D &_center,
               const QVector3D &_normal,
               const QVector3D &_arm,
               const float _phaseDeg,
               const float _lengthVector,
               const float _radiusSphere,
               const float _radiusVector,
               const float _radiusLineAxis,
               const float _radiusLineSphere,
               const float _radiusDots,
               const float _twistStep,
               const float _arrowDirOffset,
               const float _arrowArmOffset,
               const float _arrowLength,
               const float _arrowRadius,
               const uint _arrowCount,
               const uint _dotsCount,
               const uint _multAxis,
               const uint _qualityLatLong,
               const uint _qualitySphere,
               const uint _qualityLine,
               const QString &_text,
               const TextPosition _textPosition,
               const float _textSize,
               const Qt::Alignment _textAlign,
               const bool _visible,
               const std::vector<Material> &_materials,
               const std::string &_name);

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const;

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _showVector Show vector
     * \param _showAxis Show axis
     * \param _showArrows Show arrows
     * \param _showDots Show dots
     * \param _showSphere Show sphere
     * \param _showText Show text
     * \param _center Center point
     * \param _normal Main normal
     * \param _arm Arm direction
     * \param _phaseDeg Main rotation phase for spin
     * \param _lengthVector Vector length
     * \param _radiusSphere Sphere radius
     * \param _radiusVector Vector line radius
     * \param _radiusLineAxis Axis line radius
     * \param _radiusLineSphere Wire-sphere line radius
     * \param _radiusDots Dot points radius
     * \param _twistStep Twist step
     * \param _arrowDirOffset Arrow offset over line for spin
     * \param _arrowArmOffset Arrow offset to side of line for spin
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _arrowCount Count of arrows
     * \param _dotsCount Count of dots
     * \param _multAxis Space multiplier for axis dash-dot profile
     * \param _qualityLatLong Quality latitude-longitude circle
     * \param _qualitySphere Quality sphere circle
     * \param _qualityLine  Quality line circle
     * \param _text Text
     * \param _textPosition Text position over spin vector line
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _materials Materials
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const Shader *_shader,
                          const bool _showVector,
                          const bool _showAxis,
                          const bool _showArrows,
                          const bool _showDots,
                          const bool _showSphere,
                          const bool _showText,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _phaseDeg,
                          const float _lengthVector,
                          const float _radiusSphere,
                          const float _radiusVector,
                          const float _radiusLineAxis,
                          const float _radiusLineSphere,
                          const float _radiusDots,
                          const float _twistStep,
                          const float _arrowDirOffset,
                          const float _arrowArmOffset,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const uint _arrowCount,
                          const uint _dotsCount,
                          const uint _multAxis,
                          const uint _qualityLatLong,
                          const uint _qualitySphere,
                          const uint _qualityLine,
                          const QString &_text,
                          const TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const std::vector<Material> &_materials);
};

/*! \brief Footage 3D spin database */
struct DBItem3DSpin : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DSpin(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D spin item
     * \param _showFlags Initial show flags as bit buffer
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _phaseDeg Initial main rotation phase for spin
     * \param _lengthVector Initial vector length
     * \param _radiusSphere Initial sphere radius
     * \param _radiusVector Initial vector line radius
     * \param _radiusLineAxis Initial axis line radius
     * \param _radiusLineSphere Initial wire-sphere line radius
     * \param _radiusDots Initial dot points radius
     * \param _twistStep Initial twist step
     * \param _arrowDirOffset Initial arrow offset over line for spin
     * \param _arrowArmOffset Initial arrow offset to side of line for spin
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _arrowCount Initial count of arrows
     * \param _dotsCount Initial count of dots
     * \param _multAxis Initial space multiplier for axis dash-dot profile
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _text Initial text
     * \param _textPosition Initial text position over spin vector line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _visible Initial visible flag
     * \param _materials Initial materials
     * \return Created item
     */
    Item3DSpin *add(const uint8_t _showFlags,
                    const QVector3D &_center,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const float _phaseDeg,
                    const float _lengthVector,
                    const float _radiusSphere,
                    const float _radiusVector,
                    const float _radiusLineAxis,
                    const float _radiusLineSphere,
                    const float _radiusDots,
                    const float _twistStep,
                    const float _arrowDirOffset,
                    const float _arrowArmOffset,
                    const float _arrowLength,
                    const float _arrowRadius,
                    const uint _arrowCount,
                    const uint _dotsCount,
                    const uint _multAxis,
                    const uint _qualityLatLong,
                    const uint _qualitySphere,
                    const uint _qualityLine,
                    const QString &_text,
                    const TextPosition _textPosition,
                    const float _textSize,
                    const Qt::Alignment _textAlign,
                    const bool _visible,
                    const std::vector<Material> &_materials);

    /*!
     * \brief Add visible 3D spin item
     * \param _showFlags Initial show flags as bit buffer
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _phaseDeg Initial main rotation phase for spin
     * \param _lengthVector Initial vector length
     * \param _radiusSphere Initial sphere radius
     * \param _radiusVector Initial vector line radius
     * \param _radiusLineAxis Initial axis line radius
     * \param _radiusLineSphere Initial wire-sphere line radius
     * \param _radiusDots Initial dot points radius
     * \param _twistStep Initial twist step
     * \param _arrowDirOffset Initial arrow offset over line for spin
     * \param _arrowArmOffset Initial arrow offset to side of line for spin
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _arrowCount Initial count of arrows
     * \param _dotsCount Initial count of dots
     * \param _multAxis Initial space multiplier for axis dash-dot profile
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _text Initial text
     * \param _textPosition Initial text position over spin vector line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _materials Initial materials
     * \return Created item
     */
    Item3DSpin *add(const uint8_t _showFlags,
                    const QVector3D &_center,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const float _phaseDeg,
                    const float _lengthVector,
                    const float _radiusSphere,
                    const float _radiusVector,
                    const float _radiusLineAxis,
                    const float _radiusLineSphere,
                    const float _radiusDots,
                    const float _twistStep,
                    const float _arrowDirOffset,
                    const float _arrowArmOffset,
                    const float _arrowLength,
                    const float _arrowRadius,
                    const uint _arrowCount,
                    const uint _dotsCount,
                    const uint _multAxis,
                    const uint _qualityLatLong,
                    const uint _qualitySphere,
                    const uint _qualityLine,
                    const QString &_text,
                    const TextPosition _textPosition,
                    const float _textSize,
                    const Qt::Alignment _textAlign,
                    const std::vector<Material> &_materials)
    {
        return add(_showFlags,
                   _center,
                   _normal,
                   _arm,
                   _phaseDeg,
                   _lengthVector,
                   _radiusSphere,
                   _radiusVector,
                   _radiusLineAxis,
                   _radiusLineSphere,
                   _radiusDots,
                   _twistStep,
                   _arrowDirOffset,
                   _arrowArmOffset,
                   _arrowLength,
                   _arrowRadius,
                   _arrowCount,
                   _dotsCount,
                   _multAxis,
                   _qualityLatLong,
                   _qualitySphere,
                   _qualityLine,
                   _text,
                   _textPosition,
                   _textSize,
                   _textAlign,
                   true,
                   _materials);
    }

    /*!
     * \brief Add visible 3D spin item
     * \param _showFlags Initial show flags as bit buffer
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _materials Initial materials
     * \param _text Initial Text
     * \return Created item
     */
    Item3DSpin *add(const uint8_t _showFlags,
                    const QVector3D &_center,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const std::vector<Material> &_materials,
                    const QString &_text = QString())
    {
        return add(_showFlags,
                   _center,
                   _normal,
                   _arm,
                   0.0f,
                   1.0f,
                   1.0f,
                   Config::cfg().lineRadiusSpin,
                   Config::cfg().lineRadius,
                   Config::cfg().lineRadius,
                   Config::cfg().lineRadius * 3.0f,
                   1.0f / static_cast<float>(std::max(_materials.size(), 1UL)),
                   Config::cfg().spinOffsetDir,
                   Config::cfg().spinOffsetSide,
                   Config::cfg().arrowLength,
                   Config::cfg().arrowRadius,
                   3U,
                   1U,
                   10U,
                   Config::cfg().qualityLatLong,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _text,
                   _TextAtPointTo,
                   1.0f,
                   Qt::AlignHCenter | Qt::AlignBottom,
                   _materials);
    }

    /*!
     * \brief Add hidden 3D spin item
     * \param _showFlags Initial show flags as bit buffer
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _phaseDeg Initial main rotation phase for spin
     * \param _lengthVector Initial vector length
     * \param _radiusSphere Initial sphere radius
     * \param _radiusVector Initial vector line radius
     * \param _radiusLineAxis Initial axis line radius
     * \param _radiusLineSphere Initial wire-sphere line radius
     * \param _radiusDots Initial dot points radius
     * \param _twistStep Initial twist step
     * \param _arrowDirOffset Initial arrow offset over line for spin
     * \param _arrowArmOffset Initial arrow offset to side of line for spin
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _arrowCount Initial count of arrows
     * \param _dotsCount Initial count of dots
     * \param _multAxis Initial space multiplier for axis dash-dot profile
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _text Initial text
     * \param _textPosition Initial text position over spin vector line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _materials Initial materials
     * \return Created item
     */
    Item3DSpin *addHidden(const uint8_t _showFlags,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _phaseDeg,
                          const float _lengthVector,
                          const float _radiusSphere,
                          const float _radiusVector,
                          const float _radiusLineAxis,
                          const float _radiusLineSphere,
                          const float _radiusDots,
                          const float _twistStep,
                          const float _arrowDirOffset,
                          const float _arrowArmOffset,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const uint _arrowCount,
                          const uint _dotsCount,
                          const uint _multAxis,
                          const uint _qualityLatLong,
                          const uint _qualitySphere,
                          const uint _qualityLine,
                          const QString &_text,
                          const TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const std::vector<Material> &_materials)
    {
        return add(_showFlags,
                   _center,
                   _normal,
                   _arm,
                   _phaseDeg,
                   _lengthVector,
                   _radiusSphere,
                   _radiusVector,
                   _radiusLineAxis,
                   _radiusLineSphere,
                   _radiusDots,
                   _twistStep,
                   _arrowDirOffset,
                   _arrowArmOffset,
                   _arrowLength,
                   _arrowRadius,
                   _arrowCount,
                   _dotsCount,
                   _multAxis,
                   _qualityLatLong,
                   _qualitySphere,
                   _qualityLine,
                   _text,
                   _textPosition,
                   _textSize,
                   _textAlign,
                   false,
                   _materials);
    }

    /*!
     * \brief Add hidden 3D spin item
     * \param _showFlags Initial show flags as bit buffer
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _materials Initial materials
     * \param _text Initial text
     * \return Created item
     */
    Item3DSpin *addHidden(const uint8_t _showFlags,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const std::vector<Material> &_materials,
                          const QString &_text = QString())
    {
        return addHidden(_showFlags,
                         _center,
                         _normal,
                         _arm,
                         0.0f,
                         1.0f,
                         1.0f,
                         Config::cfg().lineRadiusSpin,
                         Config::cfg().lineRadius,
                         Config::cfg().lineRadius,
                         Config::cfg().lineRadius * 3.0f,
                         1.0f / static_cast<float>(std::max(_materials.size(), 1UL)),
                         Config::cfg().spinOffsetDir,
                         Config::cfg().spinOffsetSide,
                         Config::cfg().arrowLength,
                         Config::cfg().arrowRadius,
                         3U,
                         1U,
                         10U,
                         Config::cfg().qualityLatLong,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _text,
                         _TextAtPointTo,
                         1.0f,
                         Qt::AlignHCenter | Qt::AlignBottom,
                         _materials);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DSPIN_H
