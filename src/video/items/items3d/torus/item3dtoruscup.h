#ifndef UNIVERSE1_VIDEO_ITEM3DTORUSCUP_H
#define UNIVERSE1_VIDEO_ITEM3DTORUSCUP_H

#include "item3dtorus.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Torus cup item */
struct Item3DTorusCup : public Item3DTorus
{
    const bool insideCup;             //!< Start from inside flag
    DynamicValue<float> angleCupDeg;  //!< Cup angle in degrees

    /*!
     * \brief Constructor
     * \param _insideCup Start from inside flag
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DTorusCup(const bool _insideCup,
                   const bool _inner,
                   const QVector3D &_center,
                   const QVector3D &_normal,
                   const float _angleCupDeg,
                   const float _radiusRing,
                   const float _radiusLine,
                   const uint _qualityRing,
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
     * \param _center Center point
     * \param _normal Normal
     * \param _arm Arm direction
     * \param _angleCupDeg Cup angle in degrees
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _material Material
     * \param _insideCup Start from inside flag
     * \param _inner Is inner flag
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _angleCupDeg,
                          const float _radiusRing,
                          const float _radiusLine,
                          const uint _qualityRing,
                          const uint _qualityLine,
                          const Material &_material,
                          const bool _insideCup,
                          const bool _inner = false);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _center Center point
     * \param _normal Normal
     * \param _angleCupDeg Cup angle in degrees
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _material Material
     * \param _insideCup Start from inside flag
     * \param _inner Is inner flag
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _angleCupDeg,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const uint _qualityRing,
                                 const uint _qualityLine,
                                 const Material &_material,
                                 const bool _insideCup,
                                 const bool _inner = false)
    {
        buildData(_out,
                  _center,
                  _normal,
                  perpendicularNormal(_normal),
                  _angleCupDeg,
                  _radiusRing,
                  _radiusLine,
                  _qualityRing,
                  _qualityLine,
                  _material,
                  _insideCup,
                  _inner);
    }

    /*!
     * \brief Append torus cup into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Normal
     * \param _arm Arm direction
     * \param _angleCupDeg Cup angle in degrees
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _insideCup Start from inside flag
     * \param _inner Is inner flag
     * \return
     */
    static void addTorusCup(Data3D &_data,
                            uint &_idx,
                            const QVector3D &_center,
                            const QVector3D &_normal,
                            const QVector3D &_arm,
                            const float _angleCupDeg,
                            const float _radiusRing,
                            const float _radiusLine,
                            const uint _qualityRing,
                            const uint _qualityLine,
                            const bool _insideCup,
                            const bool _inner = false);

    /*!
     * \brief Append torus cup into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Normal
     * \param _angleCupDeg Cup angle in degrees
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _insideCup Start from inside flag
     * \param _inner Is inner flag
     * \return
     */
    inline static void addTorusCup(Data3D &_data,
                                   uint &_idx,
                                   const QVector3D &_center,
                                   const QVector3D &_normal,
                                   const float _angleCupDeg,
                                   const float _radiusRing,
                                   const float _radiusLine,
                                   const uint _qualityRing,
                                   const uint _qualityLine,
                                   const bool _insideCup,
                                   const bool _inner = false)
    {
        addTorusCup(_data,
                    _idx,
                    _center,
                    _normal,
                    perpendicularNormal(_normal),
                    _angleCupDeg,
                    _radiusRing,
                    _radiusLine,
                    _qualityRing,
                    _qualityLine,
                    _insideCup,
                    _inner);
    }
};

/*! \brief Footage 3D torus cup database */
struct DBItem3DTorusCup : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DTorusCup(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D torus cup item
     * \param _insideCup Start from inside flag
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DTorusCup *add(const bool _insideCup,
                        const bool _inner,
                        const QVector3D &_center,
                        const QVector3D &_normal,
                        const float _angleCupDeg,
                        const float _radiusRing,
                        const float _radiusLine,
                        const uint _qualityRing,
                        const uint _qualityLine,
                        const bool _visible,
                        const Material &_material);

    /*!
     * \brief Add outside 3D torus cup item
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *add(const bool _inner,
                               const QVector3D &_center,
                               const QVector3D &_normal,
                               const float _angleCupDeg,
                               const float _radiusRing,
                               const float _radiusLine,
                               const uint _qualityRing,
                               const uint _qualityLine,
                               const bool _visible,
                               const Material &_material)
    {
        return add(false,
                   _inner,
                   _center,
                   _normal,
                   _angleCupDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _visible,
                   _material);
    }

    //

    /*!
     * \brief Add outside outer 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const float _angleCupDeg,
                               const float _radiusRing,
                               const float _radiusLine,
                               const uint _qualityRing,
                               const uint _qualityLine,
                               const bool _visible,
                               const Material &_material)
    {
        return add(false,
                   _center,
                   _normal,
                   _angleCupDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _visible,
                   _material);
    }

    /*!
     * \brief Add outside inner 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInner(const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const float _angleCupDeg,
                                    const float _radiusRing,
                                    const float _radiusLine,
                                    const uint _qualityRing,
                                    const uint _qualityLine,
                                    const bool _visible,
                                    const Material &_material)
    {
        return add(true,
                   _center,
                   _normal,
                   _angleCupDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _visible,
                   _material);
    }

    //

    /*!
     * \brief Add outside outer visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const float _angleCupDeg,
                               const float _radiusRing,
                               const float _radiusLine,
                               const uint _qualityRing,
                               const uint _qualityLine,
                               const Material &_material)
    {
        return add(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, true, _material);
    }

    /*!
     * \brief Add outside outer visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const float _angleCupDeg,
                               const float _radiusRing,
                               const float _radiusLine,
                               const Material &_material)
    {
        return add(_center,
                   _normal,
                   _angleCupDeg,
                   _radiusRing,
                   _radiusLine,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _material);
    }

    //

    /*!
     * \brief Add outside outer hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addHidden(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleCupDeg,
                                     const float _radiusRing,
                                     const float _radiusLine,
                                     const uint _qualityRing,
                                     const uint _qualityLine,
                                     const Material &_material)
    {
        return add(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, false, _material);
    }

    /*!
     * \brief Add outside outer hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addHidden(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleCupDeg,
                                     const float _radiusRing,
                                     const float _radiusLine,
                                     const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _angleCupDeg,
                         _radiusRing,
                         _radiusLine,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }

    //

    /*!
     * \brief Add outside inner visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInner(const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const float _angleCupDeg,
                                    const float _radiusRing,
                                    const float _radiusLine,
                                    const uint _qualityRing,
                                    const uint _qualityLine,
                                    const Material &_material)
    {
        return addInner(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, true, _material);
    }

    /*!
     * \brief Add outside inner visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInner(const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const float _angleCupDeg,
                                    const float _radiusRing,
                                    const float _radiusLine,
                                    const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _angleCupDeg,
                        _radiusRing,
                        _radiusLine,
                        Config::cfg().qualitySphere,
                        Config::cfg().qualityLine,
                        _material);
    }

    //

    /*!
     * \brief Add outside inner hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInnerHidden(const QVector3D &_center,
                                          const QVector3D &_normal,
                                          const float _angleCupDeg,
                                          const float _radiusRing,
                                          const float _radiusLine,
                                          const uint _qualityRing,
                                          const uint _qualityLine,
                                          const Material &_material)
    {
        return addInner(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, false, _material);
    }

    /*!
     * \brief Add outside inner hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInnerHidden(const QVector3D &_center,
                                          const QVector3D &_normal,
                                          const float _angleCupDeg,
                                          const float _radiusRing,
                                          const float _radiusLine,
                                          const Material &_material)
    {
        return addInnerHidden(_center,
                              _normal,
                              _angleCupDeg,
                              _radiusRing,
                              _radiusLine,
                              Config::cfg().qualitySphere,
                              Config::cfg().qualityLine,
                              _material);
    }

    //

    /*!
     * \brief Add inside 3D torus cup item
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInside(const bool _inner,
                                     const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleCupDeg,
                                     const float _radiusRing,
                                     const float _radiusLine,
                                     const uint _qualityRing,
                                     const uint _qualityLine,
                                     const bool _visible,
                                     const Material &_material)
    {
        return add(true,
                   _inner,
                   _center,
                   _normal,
                   _angleCupDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _visible,
                   _material);
    }

    //

    /*!
     * \brief Add inside outer 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInside(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleCupDeg,
                                     const float _radiusRing,
                                     const float _radiusLine,
                                     const uint _qualityRing,
                                     const uint _qualityLine,
                                     const bool _visible,
                                     const Material &_material)
    {
        return addInside(false,
                         _center,
                         _normal,
                         _angleCupDeg,
                         _radiusRing,
                         _radiusLine,
                         _qualityRing,
                         _qualityLine,
                         _visible,
                         _material);
    }

    /*!
     * \brief Add inside inner 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideInner(const QVector3D &_center,
                                          const QVector3D &_normal,
                                          const float _angleCupDeg,
                                          const float _radiusRing,
                                          const float _radiusLine,
                                          const uint _qualityRing,
                                          const uint _qualityLine,
                                          const bool _visible,
                                          const Material &_material)
    {
        return addInside(true,
                         _center,
                         _normal,
                         _angleCupDeg,
                         _radiusRing,
                         _radiusLine,
                         _qualityRing,
                         _qualityLine,
                         _visible,
                         _material);
    }

    //

    /*!
     * \brief Add inside outer visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInside(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleCupDeg,
                                     const float _radiusRing,
                                     const float _radiusLine,
                                     const uint _qualityRing,
                                     const uint _qualityLine,
                                     const Material &_material)
    {
        return addInside(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, true, _material);
    }

    /*!
     * \brief Add inside outer visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInside(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleCupDeg,
                                     const float _radiusRing,
                                     const float _radiusLine,
                                     const Material &_material)
    {
        return addInside(_center,
                         _normal,
                         _angleCupDeg,
                         _radiusRing,
                         _radiusLine,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }

    //

    /*!
     * \brief Add inside outer hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideHidden(const QVector3D &_center,
                                           const QVector3D &_normal,
                                           const float _angleCupDeg,
                                           const float _radiusRing,
                                           const float _radiusLine,
                                           const uint _qualityRing,
                                           const uint _qualityLine,
                                           const Material &_material)
    {
        return addInside(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, false, _material);
    }

    /*!
     * \brief Add inside outer hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideHidden(const QVector3D &_center,
                                           const QVector3D &_normal,
                                           const float _angleCupDeg,
                                           const float _radiusRing,
                                           const float _radiusLine,
                                           const Material &_material)
    {
        return addInsideHidden(_center,
                               _normal,
                               _angleCupDeg,
                               _radiusRing,
                               _radiusLine,
                               Config::cfg().qualitySphere,
                               Config::cfg().qualityLine,
                               _material);
    }

    //

    /*!
     * \brief Add inside inner visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideInner(const QVector3D &_center,
                                          const QVector3D &_normal,
                                          const float _angleCupDeg,
                                          const float _radiusRing,
                                          const float _radiusLine,
                                          const uint _qualityRing,
                                          const uint _qualityLine,
                                          const Material &_material)
    {
        return addInsideInner(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, true, _material);
    }

    /*!
     * \brief Add inside inner visible 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideInner(const QVector3D &_center,
                                          const QVector3D &_normal,
                                          const float _angleCupDeg,
                                          const float _radiusRing,
                                          const float _radiusLine,
                                          const Material &_material)
    {
        return addInsideInner(_center,
                              _normal,
                              _angleCupDeg,
                              _radiusRing,
                              _radiusLine,
                              Config::cfg().qualitySphere,
                              Config::cfg().qualityLine,
                              _material);
    }

    //

    /*!
     * \brief Add inside inner hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideInnerHidden(const QVector3D &_center,
                                                const QVector3D &_normal,
                                                const float _angleCupDeg,
                                                const float _radiusRing,
                                                const float _radiusLine,
                                                const uint _qualityRing,
                                                const uint _qualityLine,
                                                const Material &_material)
    {
        return addInsideInner(
            _center, _normal, _angleCupDeg, _radiusRing, _radiusLine, _qualityRing, _qualityLine, false, _material);
    }

    /*!
     * \brief Add inside inner hidden 3D torus cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleCupDeg Initial cup angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusCup *addInsideInnerHidden(const QVector3D &_center,
                                                const QVector3D &_normal,
                                                const float _angleCupDeg,
                                                const float _radiusRing,
                                                const float _radiusLine,
                                                const Material &_material)
    {
        return addInsideInnerHidden(_center,
                                    _normal,
                                    _angleCupDeg,
                                    _radiusRing,
                                    _radiusLine,
                                    Config::cfg().qualitySphere,
                                    Config::cfg().qualityLine,
                                    _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DTORUSCUP_H
