#ifndef UNIVERSE1_VIDEO_ITEM3DLINECROSS_H
#define UNIVERSE1_VIDEO_ITEM3DLINECROSS_H

#include "item3dlinetwist.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Line cross item */
struct Item3DLineCross : public Item3DBase
{
    /*! \brief Supported cross type */
    enum CrossType
    {
        _Axis,       //!< Cross over axis (3 lines)
        _Planes,     //!< Cross over planes (6 lines)
        _Diagonals,  //!< Cross over diagonals (4 lines)
    };
    DynamicVec3 center;              //!< Center point
    DynamicVec3 normal;              //!< Main normal
    DynamicVec3 arm;                 //!< Arm direction
    DynamicEnum<CrossType> type;     //!< Cross type
    DynamicValue<float> radius;      //!< Cross radius
    DynamicValue<float> radiusLine;  //!< Line radius
    DynamicValue<uint> quality;      //!< Line circle quality
    DynamicBool showText;            //!< Show text flag
    DynamicTextGroup text;           //!< Text property group

    /*!
     * \brief Constructor
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _radiusLine Initial line radius
     * \param _quality Initial line circle quality
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineCross(const QVector3D &_center,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const CrossType _type,
                    const float _radius,
                    const float _radiusLine,
                    const uint _quality,
                    const bool _showText,
                    const QString &_text,
                    const float _textSize,
                    const Qt::Alignment _textAlign,
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
     * \param _center Center point
     * \param _normal Main normal
     * \param _arm Arm direction
     * \param _type Cross type
     * \param _radius Cross radius
     * \param _radiusLine Line radius
     * \param _quality Line circle quality
     * \param _showText Show text flag
     * \param _text Text
     * \param _textSize Text size multiplier
     * \param _textAlign Text alignment
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const Shader *_shader,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const CrossType _type,
                          const float _radius,
                          const float _radiusLine,
                          const uint _quality,
                          const bool _showText,
                          const QString &_text,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const Material &_material);
};

/*! \brief Footage 3D line cross database */
struct DBItem3DLineCross : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLineCross(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D line cross item
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _radiusLine Initial line radius
     * \param _quality Initial line circle quality
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineCross *add(const QVector3D &_center,
                         const QVector3D &_normal,
                         const QVector3D &_arm,
                         const Item3DLineCross::CrossType _type,
                         const float _radius,
                         const float _radiusLine,
                         const uint _quality,
                         const bool _showText,
                         const QString &_text,
                         const float _textSize,
                         const Qt::Alignment _textAlign,
                         const bool _visible,
                         const Material &_material);

    /*!
     * \brief Add visible 3D line cross item
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _radiusLine Initial line radius
     * \param _quality Initial line circle quality
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *add(const QVector3D &_center,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const Item3DLineCross::CrossType _type,
                                const float _radius,
                                const float _radiusLine,
                                const uint _quality,
                                const bool _showText,
                                const QString &_text,
                                const float _textSize,
                                const Qt::Alignment _textAlign,
                                const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _type,
                   _radius,
                   _radiusLine,
                   _quality,
                   _showText,
                   _text,
                   _textSize,
                   _textAlign,
                   true,
                   _material);
    }

    /*!
     * \brief Add visible 3D line cross item
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *add(const QVector3D &_center,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const Item3DLineCross::CrossType _type,
                                const float _radius,
                                const bool _showText,
                                const QString &_text,
                                const float _textSize,
                                const Qt::Alignment _textAlign,
                                const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _type,
                   _radius,
                   Config::cfg().lineRadius,
                   Config::cfg().qualityLine,
                   _showText,
                   _text,
                   _textSize,
                   _textAlign,
                   _material);
    }

    /*!
     * \brief Add visible 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *add(const QVector3D &_center,
                                const Item3DLineCross::CrossType _type,
                                const float _radius,
                                const bool _showText,
                                const QString &_text,
                                const float _textSize,
                                const Qt::Alignment _textAlign,
                                const Material &_material)
    {
        return add(_center, Item3D::nz, Item3D::nx, _type, _radius, _showText, _text, _textSize, _textAlign, _material);
    }

    /*!
     * \brief Add visible 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *add(const QVector3D &_center,
                                const Item3DLineCross::CrossType _type,
                                const float _radius,
                                const QString &_text,
                                const float _textSize,
                                const Qt::Alignment _textAlign,
                                const Material &_material)
    {
        return add(_center, Item3D::nz, Item3D::nx, _type, _radius, true, _text, _textSize, _textAlign, _material);
    }

    /*!
     * \brief Add visible 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _text Initial text
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *add(const QVector3D &_center,
                                const Item3DLineCross::CrossType _type,
                                const float _radius,
                                const QString &_text,
                                const Material &_material)
    {
        return add(_center, _type, _radius, _text, 1.0f, Qt::AlignHCenter | Qt::AlignBottom, _material);
    }

    /*!
     * \brief Add visible 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *add(const QVector3D &_center,
                                const Item3DLineCross::CrossType _type,
                                const float _radius,
                                const Material &_material)
    {
        return add(_center, _type, _radius, false, QString(), 1.0f, Qt::AlignHCenter | Qt::AlignBottom, _material);
    }

    //

    /*!
     * \brief Add hidden 3D line cross item
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _radiusLine Initial line radius
     * \param _quality Initial line circle quality
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *addHidden(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const Item3DLineCross::CrossType _type,
                                      const float _radius,
                                      const float _radiusLine,
                                      const uint _quality,
                                      const bool _showText,
                                      const QString &_text,
                                      const float _textSize,
                                      const Qt::Alignment _textAlign,
                                      const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _type,
                   _radius,
                   _radiusLine,
                   _quality,
                   _showText,
                   _text,
                   _textSize,
                   _textAlign,
                   false,
                   _material);
    }

    /*!
     * \brief Add hidden 3D line cross item
     * \param _center Initial center point
     * \param _normal Initial main normal
     * \param _arm Initial arm direction
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *addHidden(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const Item3DLineCross::CrossType _type,
                                      const float _radius,
                                      const bool _showText,
                                      const QString &_text,
                                      const float _textSize,
                                      const Qt::Alignment _textAlign,
                                      const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _arm,
                         _type,
                         _radius,
                         Config::cfg().lineRadius,
                         Config::cfg().qualityLine,
                         _showText,
                         _text,
                         _textSize,
                         _textAlign,
                         _material);
    }

    /*!
     * \brief Add hidden 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _showText Initial show text flag
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *addHidden(const QVector3D &_center,
                                      const Item3DLineCross::CrossType _type,
                                      const float _radius,
                                      const bool _showText,
                                      const QString &_text,
                                      const float _textSize,
                                      const Qt::Alignment _textAlign,
                                      const Material &_material)
    {
        return addHidden(
            _center, Item3D::nz, Item3D::nx, _type, _radius, _showText, _text, _textSize, _textAlign, _material);
    }

    /*!
     * \brief Add hidden 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _text Initial text
     * \param _textSize Initial text size
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *addHidden(const QVector3D &_center,
                                      const Item3DLineCross::CrossType _type,
                                      const float _radius,
                                      const QString &_text,
                                      const float _textSize,
                                      const Qt::Alignment _textAlign,
                                      const Material &_material)
    {
        return addHidden(
            _center, Item3D::nz, Item3D::nx, _type, _radius, true, _text, _textSize, _textAlign, _material);
    }

    /*!
     * \brief Add hidden 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _text Initial text
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *addHidden(const QVector3D &_center,
                                      const Item3DLineCross::CrossType _type,
                                      const float _radius,
                                      const QString &_text,
                                      const Material &_material)
    {
        return addHidden(_center, _type, _radius, _text, 1.0f, Qt::AlignHCenter | Qt::AlignBottom, _material);
    }

    /*!
     * \brief Add hidden 3D line cross item
     * \param _center Initial center point
     * \param _type Initial cross type
     * \param _radius Initial cross radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCross *addHidden(const QVector3D &_center,
                                      const Item3DLineCross::CrossType _type,
                                      const float _radius,
                                      const Material &_material)
    {
        return addHidden(
            _center, _type, _radius, false, QString(), 1.0f, Qt::AlignHCenter | Qt::AlignBottom, _material);
    }

};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINECROSS_H
