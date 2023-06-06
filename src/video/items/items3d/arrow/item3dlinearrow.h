#ifndef UNIVERSE1_VIDEO_ITEM3DLINEARROW_H
#define UNIVERSE1_VIDEO_ITEM3DLINEARROW_H

#include "../wiresphere/item3dwiresphereslice.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D line arrow item */
struct Item3DLineArrow : public Item3DBase
{
    DynamicVec3 pointFrom;            //!< Point from
    DynamicVec3 pointTo;              //!< Point to
    DynamicValue<float> arrowLength;  //!< Arrow length
    DynamicValue<float> arrowRadius;  //!< Arrow header radius
    DynamicValue<float> lineRadius;   //!< Line radius
    DynamicValue<uint> quality;       //!< Circle quality

    DynamicTextGroupExt text;  //!< Text properties group

    /*!
     * \brief Constructor
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _showText Initial show text flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineArrow(const QVector3D &_pointFrom,
                    const QVector3D &_pointTo,
                    const float _arrowLength,
                    const float _arrowRadius,
                    const float _lineRadius,
                    const uint _quality,
                    const QString &_text,
                    const TextPosition _textPosition,
                    const float _textSize,
                    const Qt::Alignment _textAlign,
                    const bool _showText,
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
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arm Arm direction
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _text Text
     * \param _textPosition Text position over arrow line
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _showText Show text flag
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const Shader *_shader,
                          const QVector3D &_pointFrom,
                          const QVector3D &_pointTo,
                          const QVector3D &_arm,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const float _lineRadius,
                          const uint _quality,
                          const QString &_text,
                          const TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const bool _showText,
                          const Material &_material);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _text Text
     * \param _textPosition Text position over arrow line
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _showText Show text flag
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const Shader *_shader,
                                 const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const QString &_text,
                                 const TextPosition _textPosition,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const bool _showText,
                                 const Material &_material)
    {
        buildData(_out,
                  _shader,
                  _pointFrom,
                  _pointTo,
                  perpendicularNormal((_pointTo - _pointFrom).normalized()),
                  _arrowLength,
                  _arrowRadius,
                  _lineRadius,
                  _quality,
                  _text,
                  _textPosition,
                  _textSize,
                  _textAlign,
                  _showText,
                  _material);
    }

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arm Arm direction
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const QVector3D &_arm,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const Material &_material)
    {
        buildData(_out,
                  nullptr,
                  _pointFrom,
                  _pointTo,
                  _arm,
                  _arrowLength,
                  _arrowRadius,
                  _lineRadius,
                  _quality,
                  "",
                  _TextMiddle,
                  0.0f,
                  Qt::AlignHCenter | Qt::AlignTop,
                  false,
                  _material);
    }

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const Material &_material)
    {
        buildData(_out,
                  _pointFrom,
                  _pointTo,
                  perpendicularNormal((_pointTo - _pointFrom).normalized()),
                  _arrowLength,
                  _arrowRadius,
                  _lineRadius,
                  _quality,
                  _material);
    }

    /*!
     * \brief Build 3D text data
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _offsetUp Offset in up direction
     * \param _text Text
     * \param _textPosition Text position over arrow line
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _showText Show text flag
     * \param _material Material
     * \return
     */
    static void buildText(std::list<Data3D> &_out,
                          const Shader *_shader,
                          const QVector3D &_pointFrom,
                          const QVector3D &_pointTo,
                          const float _offsetUp,
                          const QString &_text,
                          const TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const bool _showText,
                          const Material &_material);
};

/*! \brief 3D line dimension arrows item */
struct Item3DLineDim : public Item3DLineArrow
{
    DynamicBool showArrowFrom;  //!< Show arrow at \b from point
    DynamicBool showArrowTo;    //!< Show arrow at \b to point

    /*!
     * \brief Constructor
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _showText Initial show text flag
     * \param _showArrowFrom Initial show arrow from flag
     * \param _showArrowTo Initial show arrow to flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineDim(const QVector3D &_pointFrom,
                  const QVector3D &_pointTo,
                  const float _arrowLength,
                  const float _arrowRadius,
                  const float _lineRadius,
                  const uint _quality,
                  const QString &_text,
                  const TextPosition _textPosition,
                  const float _textSize,
                  const Qt::Alignment _textAlign,
                  const bool _showText,
                  const bool _showArrowFrom,
                  const bool _showArrowTo,
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
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arm Arm direction
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _text Text
     * \param _textPosition Text position over arrow line
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _showText Show text flag
     * \param _showArrowFrom Show arrow from flag
     * \param _showArrowTo Show arrow to flag
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const Shader *_shader,
                          const QVector3D &_pointFrom,
                          const QVector3D &_pointTo,
                          const QVector3D &_arm,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const float _lineRadius,
                          const uint _quality,
                          const QString &_text,
                          const TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const bool _showText,
                          const bool _showArrowFrom,
                          const bool _showArrowTo,
                          const Material &_material);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _text Text
     * \param _textPosition Text position over arrow line
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _showText Show text flag
     * \param _showArrowFrom Show arrow from flag
     * \param _showArrowTo Show arrow to flag
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const Shader *_shader,
                                 const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const QString &_text,
                                 const TextPosition _textPosition,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const bool _showText,
                                 const bool _showArrowFrom,
                                 const bool _showArrowTo,
                                 const Material &_material)
    {
        buildData(_out,
                  _shader,
                  _pointFrom,
                  _pointTo,
                  perpendicularNormal((_pointTo - _pointFrom).normalized()),
                  _arrowLength,
                  _arrowRadius,
                  _lineRadius,
                  _quality,
                  _text,
                  _textPosition,
                  _textSize,
                  _textAlign,
                  _showText,
                  _showArrowFrom,
                  _showArrowTo,
                  _material);
    }

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arm Arm direction
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _showArrowFrom Show arrow from flag
     * \param _showArrowTo Show arrow to flag
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const QVector3D &_arm,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const bool _showArrowFrom,
                                 const bool _showArrowTo,
                                 const Material &_material)
    {
        buildData(_out,
                  nullptr,
                  _pointFrom,
                  _pointTo,
                  _arm,
                  _arrowLength,
                  _arrowRadius,
                  _lineRadius,
                  _quality,
                  "",
                  _TextMiddle,
                  0.0f,
                  Qt::AlignHCenter | Qt::AlignTop,
                  false,
                  _showArrowFrom,
                  _showArrowTo,
                  _material);
    }

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _pointFrom Point from
     * \param _pointTo Point to
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow header radius
     * \param _lineRadius Line radius
     * \param _quality Circle quality
     * \param _showArrowFrom Show arrow from flag
     * \param _showArrowTo Show arrow to flag
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const bool _showArrowFrom,
                                 const bool _showArrowTo,
                                 const Material &_material)
    {
        buildData(_out,
                  _pointFrom,
                  _pointTo,
                  perpendicularNormal((_pointTo - _pointFrom).normalized()),
                  _arrowLength,
                  _arrowRadius,
                  _lineRadius,
                  _quality,
                  _showArrowFrom,
                  _showArrowTo,
                  _material);
    }
};

/*! \brief Footage 3D line arrow and dimension database */
struct DBItem3DLineArrow : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLineArrow(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _showText Initial show text flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineArrow *add(const QVector3D &_pointFrom,
                         const QVector3D &_pointTo,
                         const float _arrowLength,
                         const float _arrowRadius,
                         const float _lineRadius,
                         const uint _quality,
                         const QString &_text,
                         const TextPosition _textPosition,
                         const float _textSize,
                         const Qt::Alignment _textAlign,
                         const bool _showText,
                         const bool _visible,
                         const Material &_material);

    /*!
     * \brief Add visible 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineArrow *add(const QVector3D &_pointFrom,
                                const QVector3D &_pointTo,
                                const float _arrowLength,
                                const float _arrowRadius,
                                const float _lineRadius,
                                const uint _quality,
                                const QString &_text,
                                const TextPosition _textPosition,
                                const float _textSize,
                                const Qt::Alignment _textAlign,
                                const Material &_material)
    {
        return add(_pointFrom,
                   _pointTo,
                   _arrowLength,
                   _arrowRadius,
                   _lineRadius,
                   _quality,
                   _text,
                   _textPosition,
                   _textSize,
                   _textAlign,
                   true,
                   true,
                   _material);
    }

    /*!
     * \brief Add visible 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineArrow *add(const QVector3D &_pointFrom,
                                const QVector3D &_pointTo,
                                const float _arrowLength,
                                const float _arrowRadius,
                                const float _lineRadius,
                                const Material &_material,
                                const QString &_text = QString())
    {
        return add(_pointFrom,
                   _pointTo,
                   _arrowLength,
                   _arrowRadius,
                   _lineRadius,
                   Config::cfg().qualityLine,
                   _text,
                   _TextAtPointTo,
                   1.0f,
                   Qt::AlignHCenter | Qt::AlignTop,
                   _material);
    }

    /*!
     * \brief Add visible 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineArrow *add(const QVector3D &_pointFrom,
                                const QVector3D &_pointTo,
                                const Material &_material,
                                const QString &_text = QString())
    {
        const Config &c = Config::cfg();
        return add(_pointFrom, _pointTo, c.arrowLength, c.arrowRadius, c.lineRadius, _material, _text);
    }

    //

    /*!
     * \brief Add hidden 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineArrow *addHidden(const QVector3D &_pointFrom,
                                      const QVector3D &_pointTo,
                                      const float _arrowLength,
                                      const float _arrowRadius,
                                      const float _lineRadius,
                                      const uint _quality,
                                      const QString &_text,
                                      const TextPosition _textPosition,
                                      const float _textSize,
                                      const Qt::Alignment _textAlign,
                                      const Material &_material)
    {
        return add(_pointFrom,
                   _pointTo,
                   _arrowLength,
                   _arrowRadius,
                   _lineRadius,
                   _quality,
                   _text,
                   _textPosition,
                   _textSize,
                   _textAlign,
                   true,
                   false,
                   _material);
    }

    /*!
     * \brief Add hidden 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineArrow *addHidden(const QVector3D &_pointFrom,
                                      const QVector3D &_pointTo,
                                      const float _arrowLength,
                                      const float _arrowRadius,
                                      const float _lineRadius,
                                      const Material &_material,
                                      const QString &_text = QString())
    {
        return addHidden(_pointFrom,
                         _pointTo,
                         _arrowLength,
                         _arrowRadius,
                         _lineRadius,
                         Config::cfg().qualityLine,
                         _text,
                         _TextAtPointTo,
                         1.0f,
                         Qt::AlignHCenter | Qt::AlignTop,
                         _material);
    }

    /*!
     * \brief Add hidden 3D line arrow item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineArrow *addHidden(const QVector3D &_pointFrom,
                                      const QVector3D &_pointTo,
                                      const Material &_material,
                                      const QString &_text = QString())
    {
        const Config &c = Config::cfg();
        return addHidden(_pointFrom, _pointTo, c.arrowLength, c.arrowRadius, c.lineRadius, _material, _text);
    }

    // // // // // // // // // // // // // // // // //

    /*!
     * \brief Add 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _showText Initial show text flag
     * \param _showArrowFrom Initial show arrow from flag
     * \param _showArrowTo Initial show arrow to flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineDim *addDim(const QVector3D &_pointFrom,
                          const QVector3D &_pointTo,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const float _lineRadius,
                          const uint _quality,
                          const QString &_text,
                          const TextPosition _textPosition,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const bool _showText,
                          const bool _showArrowFrom,
                          const bool _showArrowTo,
                          const bool _visible,
                          const Material &_material);

    /*!
     * \brief Add visible 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDim *addDim(const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const uint _quality,
                                 const QString &_text,
                                 const TextPosition _textPosition,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const Material &_material)
    {
        return addDim(_pointFrom,
                      _pointTo,
                      _arrowLength,
                      _arrowRadius,
                      _lineRadius,
                      _quality,
                      _text,
                      _textPosition,
                      _textSize,
                      _textAlign,
                      true,
                      true,
                      true,
                      true,
                      _material);
    }

    /*!
     * \brief Add visible 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineDim *addDim(const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const float _lineRadius,
                                 const Material &_material,
                                 const QString &_text = QString())
    {
        return addDim(_pointFrom,
                      _pointTo,
                      _arrowLength,
                      _arrowRadius,
                      _lineRadius,
                      Config::cfg().qualityLine,
                      _text,
                      _TextMiddle,
                      1.0f,
                      Qt::AlignHCenter | Qt::AlignTop,
                      _material);
    }

    /*!
     * \brief Add visible 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineDim *addDim(const QVector3D &_pointFrom,
                                 const QVector3D &_pointTo,
                                 const Material &_material,
                                 const QString &_text = QString())
    {
        const Config &c = Config::cfg();
        return addDim(_pointFrom, _pointTo, c.arrowLength, c.arrowRadius, c.lineRadius, _material, _text);
    }

    //

    /*!
     * \brief Add hidden 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _quality Initial circle quality
     * \param _text Initial text
     * \param _textPosition Initial text position over arrow line
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDim *addDimHidden(const QVector3D &_pointFrom,
                                       const QVector3D &_pointTo,
                                       const float _arrowLength,
                                       const float _arrowRadius,
                                       const float _lineRadius,
                                       const uint _quality,
                                       const QString &_text,
                                       const TextPosition _textPosition,
                                       const float _textSize,
                                       const Qt::Alignment _textAlign,
                                       const Material &_material)
    {
        return addDim(_pointFrom,
                      _pointTo,
                      _arrowLength,
                      _arrowRadius,
                      _lineRadius,
                      _quality,
                      _text,
                      _textPosition,
                      _textSize,
                      _textAlign,
                      true,
                      true,
                      true,
                      false,
                      _material);
    }

    /*!
     * \brief Add hidden 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow header radius
     * \param _lineRadius Initial line radius
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineDim *addDimHidden(const QVector3D &_pointFrom,
                                       const QVector3D &_pointTo,
                                       const float _arrowLength,
                                       const float _arrowRadius,
                                       const float _lineRadius,
                                       const Material &_material,
                                       const QString &_text = QString())
    {
        return addDimHidden(_pointFrom,
                            _pointTo,
                            _arrowLength,
                            _arrowRadius,
                            _lineRadius,
                            Config::cfg().qualityLine,
                            _text,
                            _TextMiddle,
                            1.0f,
                            Qt::AlignHCenter | Qt::AlignTop,
                            _material);
    }

    /*!
     * \brief Add hidden 3D line dimension item
     * \param _pointFrom Initial point from
     * \param _pointTo Initial point to
     * \param _material Initial material
     * \param _text Initial text
     * \return Created item
     */
    inline Item3DLineDim *addDimHidden(const QVector3D &_pointFrom,
                                       const QVector3D &_pointTo,
                                       const Material &_material,
                                       const QString &_text = QString())
    {
        const Config &c = Config::cfg();
        return addDimHidden(_pointFrom, _pointTo, c.arrowLength, c.arrowRadius, c.lineRadius, _material, _text);
    }

};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINEARROW_H
