#ifndef UNIVERSE1_VIDEO_ITEM3DANGLEDIM_H
#define UNIVERSE1_VIDEO_ITEM3DANGLEDIM_H

#include "../torus/item3dtorusarc.h"
#include "item3darcarrow.h"
#include "item3dlinearrow.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D angle dimension item */
struct Item3DAngleDim : public Item3DBase
{
    DynamicVec3 center;      //!< Main angle center point
    DynamicVec3 normal;      //!< Main angle normal
    DynamicVec3 normalFrom;  //!< Main angle direction from
    DynamicVec3 normalTo;    //!< Main angle direction to

    DynamicValue<float> radius;       //!< Angle arc radius
    DynamicValue<float> lineRadius;   //!< Line radius
    DynamicValue<float> arrowLength;  //!< Arrow length
    DynamicValue<float> arrowRadius;  //!< Arrow radius

    DynamicBool showArrowFrom;  //!< Show arrow at \b from direction
    DynamicBool showArrowTo;    //!< Show arrow at \b to direction

    DynamicBool showText;                                     //!< Show text flag
    DynamicEnum<Item3DLineArrow::TextPosition> textPosition;  //!< Text position over arc line
    DynamicTextGroup text;                                    //!< Text properties group

    DynamicValue<uint> qualityAngle;  //!< Quality main circle
    DynamicValue<uint> qualityLine;   //!< Quality line circle

    /*!
     * \brief Constructor
     * \param _center Initial main angle center point
     * \param _normal Initial main angle normal
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _lineRadius Initial line radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _showArrowFrom Initial show arrow at \b from direction
     * \param _showArrowTo Initial show arrow at \b to direction
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textPosition Initial text position over arc line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _qualityAngle Initial quality main circle
     * \param _qualityLine Initial quality line circle
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DAngleDim(const QVector3D &_center,
                   const QVector3D &_normal,
                   const QVector3D &_normalFrom,
                   const QVector3D &_normalTo,
                   const float _radius,
                   const float _lineRadius,
                   const float _arrowLength,
                   const float _arrowRadius,
                   const bool _showArrowFrom,
                   const bool _showArrowTo,
                   const bool _showText,
                   const QString &_text,
                   const Item3DLineArrow::TextPosition _textPosition,
                   const float _textSize,
                   const Qt::Alignment _textAlign,
                   const uint _qualityAngle,
                   const uint _qualityLine,
                   const bool _visible,
                   const Material &_material,
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
     * \param _center Main angle center point
     * \param _normal Main angle normal
     * \param _normalFrom Main angle direction from
     * \param _normalTo Main angle direction to
     * \param _radius Angle arc radius
     * \param _lineRadius Line radius
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow radius
     * \param _showArrowFrom Show arrow at from direction
     * \param _showArrowTo Show arrow at to direction
     * \param _showText Show text flag
     * \param _text Text
     * \param _textPosition Text position
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _qualityAngle Quality main circle
     * \param _qualityLine Quality line circle
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const Shader *_shader,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_normalFrom,
                          const QVector3D &_normalTo,
                          const float _radius,
                          const float _lineRadius,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const bool _showArrowFrom,
                          const bool _showArrowTo,
                          const bool _showText,
                          const QString &_text,
                          const Item3DLineArrow::TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const uint _qualityAngle,
                          const uint _qualityLine,
                          const Material &_material);
};

/*! \brief Footage 3D angle dimension database */
struct DBItem3DAngleDim : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DAngleDim(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normal Initial main angle normal
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _lineRadius Initial line radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _showArrowFrom Initial show arrow at \b from direction
     * \param _showArrowTo Initial show arrow at \b to direction
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textPosition Initial text position over arc line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _qualityAngle Initial quality main circle
     * \param _qualityLine Initial quality line circle
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DAngleDim *add(const QVector3D &_center,
                        const QVector3D &_normal,
                        const QVector3D &_normalFrom,
                        const QVector3D &_normalTo,
                        const float _radius,
                        const float _lineRadius,
                        const float _arrowLength,
                        const float _arrowRadius,
                        const bool _showArrowFrom,
                        const bool _showArrowTo,
                        const bool _showText,
                        const QString &_text,
                        const Item3DLineArrow::TextPosition _textPosition,
                        const float _textSize,
                        const Qt::Alignment _textAlign,
                        const uint _qualityAngle,
                        const uint _qualityLine,
                        const bool _visible,
                        const Material &_material);

    /*!
     * \brief Add visible 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normal Initial main angle normal
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _lineRadius Initial line radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _showArrowFrom Initial show arrow at \b from direction
     * \param _showArrowTo Initial show arrow at \b to direction
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textPosition Initial text position over arc line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _qualityAngle Initial quality main circle
     * \param _qualityLine Initial quality line circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DAngleDim *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_normalFrom,
                               const QVector3D &_normalTo,
                               const float _radius,
                               const float _lineRadius,
                               const float _arrowLength,
                               const float _arrowRadius,
                               const bool _showArrowFrom,
                               const bool _showArrowTo,
                               const bool _showText,
                               const QString &_text,
                               const Item3DLineArrow::TextPosition _textPosition,
                               const float _textSize,
                               const Qt::Alignment _textAlign,
                               const uint _qualityAngle,
                               const uint _qualityLine,
                               const Material &_material)
    {
        return add(_center,
                   _normal,
                   _normalFrom,
                   _normalTo,
                   _radius,
                   _lineRadius,
                   _arrowLength,
                   _arrowRadius,
                   _showArrowFrom,
                   _showArrowTo,
                   _showText,
                   _text,
                   _textPosition,
                   _textSize,
                   _textAlign,
                   _qualityAngle,
                   _qualityLine,
                   true,
                   _material);
    }

    /*!
     * \brief Add visible 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normal Initial main angle normal
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _material Initial material
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DAngleDim *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_normalFrom,
                               const QVector3D &_normalTo,
                               const float _radius,
                               const Material &_material,
                               const bool _showText = true,
                               const QString &_text = "")
    {
        const Config &c = Config::cfg();
        return add(_center,
                   _normal,
                   _normalFrom,
                   _normalTo,
                   _radius,
                   c.lineRadius,
                   c.arrowLength,
                   c.arrowRadius,
                   true,
                   true,
                   _showText,
                   _text,
                   Item3DLineArrow::_TextMiddle,
                   1.0f,
                   Qt::AlignHCenter | Qt::AlignTop,
                   c.qualitySphere,
                   c.qualityLine,
                   _material);
    }

    /*!
     * \brief Add visible 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _material Initial material
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DAngleDim *add(const QVector3D &_center,
                               const QVector3D &_normalFrom,
                               const QVector3D &_normalTo,
                               const float _radius,
                               const Material &_material,
                               const bool _showText = true,
                               const QString &_text = "")
    {
        return add(_center,
                   QVector3D::crossProduct(_normalFrom, _normalTo).normalized(),
                   _normalFrom,
                   _normalTo,
                   _radius,
                   _material,
                   _showText,
                   _text);
    }

    /*!
     * \brief Add hidden 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normal Initial main angle normal
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _lineRadius Initial line radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _showArrowFrom Initial show arrow at \b from direction
     * \param _showArrowTo Initial show arrow at \b to direction
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textPosition Initial text position over arc line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _qualityAngle Initial quality main circle
     * \param _qualityLine Initial quality line circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DAngleDim *addHidden(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const QVector3D &_normalFrom,
                                     const QVector3D &_normalTo,
                                     const float _radius,
                                     const float _lineRadius,
                                     const float _arrowLength,
                                     const float _arrowRadius,
                                     const bool _showArrowFrom,
                                     const bool _showArrowTo,
                                     const bool _showText,
                                     const QString &_text,
                                     const Item3DLineArrow::TextPosition _textPosition,
                                     const float _textSize,
                                     const Qt::Alignment _textAlign,
                                     const uint _qualityAngle,
                                     const uint _qualityLine,
                                     const Material &_material)
    {
        return add(_center,
                   _normal,
                   _normalFrom,
                   _normalTo,
                   _radius,
                   _lineRadius,
                   _arrowLength,
                   _arrowRadius,
                   _showArrowFrom,
                   _showArrowTo,
                   _showText,
                   _text,
                   _textPosition,
                   _textSize,
                   _textAlign,
                   _qualityAngle,
                   _qualityLine,
                   false,
                   _material);
    }

    /*!
     * \brief Add hidden 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normal Initial main angle normal
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _material Initial material
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DAngleDim *addHidden(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const QVector3D &_normalFrom,
                                     const QVector3D &_normalTo,
                                     const float _radius,
                                     const Material &_material,
                                     const bool _showText = true,
                                     const QString &_text = "")
    {
        const Config &c = Config::cfg();
        return addHidden(_center,
                         _normal,
                         _normalFrom,
                         _normalTo,
                         _radius,
                         c.lineRadius,
                         c.arrowLength,
                         c.arrowRadius,
                         true,
                         true,
                         _showText,
                         _text,
                         Item3DLineArrow::_TextMiddle,
                         1.0f,
                         Qt::AlignHCenter | Qt::AlignTop,
                         c.qualitySphere,
                         c.qualityLine,
                         _material);
    }

    /*!
     * \brief Add hidden 3D angle dimension item
     * \param _center Initial main angle center point
     * \param _normalFrom Initial main angle direction from
     * \param _normalTo Initial main angle direction to
     * \param _radius Initial angle arc radius
     * \param _material Initial material
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DAngleDim *addHidden(const QVector3D &_center,
                                     const QVector3D &_normalFrom,
                                     const QVector3D &_normalTo,
                                     const float _radius,
                                     const Material &_material,
                                     const bool _showText = true,
                                     const QString &_text = "")
    {
        return addHidden(_center,
                         QVector3D::crossProduct(_normalFrom, _normalTo).normalized(),
                         _normalFrom,
                         _normalTo,
                         _radius,
                         _material,
                         _showText,
                         _text);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DANGLEDIM_H
