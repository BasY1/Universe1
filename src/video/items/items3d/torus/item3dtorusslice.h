#ifndef UNIVERSE1_VIDEO_ITEM3DTORUSSLICE_H
#define UNIVERSE1_VIDEO_ITEM3DTORUSSLICE_H

#include "item3dtoruscup.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Torus slice item */
struct Item3DTorusSlice : public Item3DTorus
{
    DynamicValue<float> angleSliceStartDeg;  //!< Starting slice angle in degrees
    DynamicValue<float> angleSliceEndDeg;    //!< Ending slice angle in degrees

    /*!
     * \brief Constructor
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DTorusSlice(const bool _inner,
                     const QVector3D &_center,
                     const QVector3D &_normal,
                     const float _angleSliceStartDeg,
                     const float _angleSliceEndDeg,
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
     * \param _angleSliceStartDeg Starting slice angle in degrees
     * \param _angleSliceEndDeg Ending slice angle in degrees
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _material Material
     * \param _inner Is inner flag
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _angleSliceStartDeg,
                          const float _angleSliceEndDeg,
                          const float _radiusRing,
                          const float _radiusLine,
                          const uint _qualityRing,
                          const uint _qualityLine,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _center Center point
     * \param _normal Normal
     * \param _angleSliceStartDeg Starting slice angle in degrees
     * \param _angleSliceEndDeg Ending slice angle in degrees
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _material Material
     * \param _inner Is inner flag
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _angleSliceStartDeg,
                                 const float _angleSliceEndDeg,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const uint _qualityRing,
                                 const uint _qualityLine,
                                 const Material &_material,
                                 const bool _inner = false)
    {
        buildData(_out,
                  _center,
                  _normal,
                  perpendicularNormal(_normal),
                  _angleSliceStartDeg,
                  _angleSliceEndDeg,
                  _radiusRing,
                  _radiusLine,
                  _qualityRing,
                  _qualityLine,
                  _material,
                  _inner);
    }
};

/*! \brief Footage 3D torus slice database */
struct DBItem3DTorusSlice : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DTorusSlice(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D torus slice item
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DTorusSlice *add(const bool _inner,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const float _angleSliceStartDeg,
                          const float _angleSliceEndDeg,
                          const float _radiusRing,
                          const float _radiusLine,
                          const uint _qualityRing,
                          const uint _qualityLine,
                          const bool _visible,
                          const Material &_material);

    //

    /*!
     * \brief Add outer 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *add(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _angleSliceStartDeg,
                                 const float _angleSliceEndDeg,
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
                   _angleSliceStartDeg,
                   _angleSliceEndDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _visible,
                   _material);
    }

    /*!
     * \brief Add outer visible 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *add(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _angleSliceStartDeg,
                                 const float _angleSliceEndDeg,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const uint _qualityRing,
                                 const uint _qualityLine,
                                 const Material &_material)
    {
        return add(_center,
                   _normal,
                   _angleSliceStartDeg,
                   _angleSliceEndDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   true,
                   _material);
    }

    /*!
     * \brief Add outer visible 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *add(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _angleSliceStartDeg,
                                 const float _angleSliceEndDeg,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const Material &_material)
    {
        return add(_center,
                   _normal,
                   _angleSliceStartDeg,
                   _angleSliceEndDeg,
                   _radiusRing,
                   _radiusLine,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _material);
    }

    /*!
     * \brief Add outer hidden 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addHidden(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const float _angleSliceStartDeg,
                                       const float _angleSliceEndDeg,
                                       const float _radiusRing,
                                       const float _radiusLine,
                                       const uint _qualityRing,
                                       const uint _qualityLine,
                                       const Material &_material)
    {
        return add(_center,
                   _normal,
                   _angleSliceStartDeg,
                   _angleSliceEndDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   false,
                   _material);
    }

    /*!
     * \brief Add outer hidden 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addHidden(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const float _angleSliceStartDeg,
                                       const float _angleSliceEndDeg,
                                       const float _radiusRing,
                                       const float _radiusLine,
                                       const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _angleSliceStartDeg,
                         _angleSliceEndDeg,
                         _radiusRing,
                         _radiusLine,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }

    /*!
     * \brief Add inner 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addInner(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const float _angleSliceStartDeg,
                                      const float _angleSliceEndDeg,
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
                   _angleSliceStartDeg,
                   _angleSliceEndDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _visible,
                   _material);
    }

    /*!
     * \brief Add inner visible 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addInner(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const float _angleSliceStartDeg,
                                      const float _angleSliceEndDeg,
                                      const float _radiusRing,
                                      const float _radiusLine,
                                      const uint _qualityRing,
                                      const uint _qualityLine,
                                      const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _angleSliceStartDeg,
                        _angleSliceEndDeg,
                        _radiusRing,
                        _radiusLine,
                        _qualityRing,
                        _qualityLine,
                        true,
                        _material);
    }

    /*!
     * \brief Add inner visible 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addInner(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const float _angleSliceStartDeg,
                                      const float _angleSliceEndDeg,
                                      const float _radiusRing,
                                      const float _radiusLine,
                                      const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _angleSliceStartDeg,
                        _angleSliceEndDeg,
                        _radiusRing,
                        _radiusLine,
                        Config::cfg().qualitySphere,
                        Config::cfg().qualityLine,
                        _material);
    }

    /*!
     * \brief Add inner hidden 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addInnerHidden(const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const float _angleSliceStartDeg,
                                            const float _angleSliceEndDeg,
                                            const float _radiusRing,
                                            const float _radiusLine,
                                            const uint _qualityRing,
                                            const uint _qualityLine,
                                            const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _angleSliceStartDeg,
                        _angleSliceEndDeg,
                        _radiusRing,
                        _radiusLine,
                        _qualityRing,
                        _qualityLine,
                        false,
                        _material);
    }

    /*!
     * \brief Add inner hidden 3D torus slice item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleSliceStartDeg Initial starting slice angle in degrees
     * \param _angleSliceEndDeg Initial ending slice angle in degrees
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorusSlice *addInnerHidden(const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const float _angleSliceStartDeg,
                                            const float _angleSliceEndDeg,
                                            const float _radiusRing,
                                            const float _radiusLine,
                                            const Material &_material)
    {
        return addInnerHidden(_center,
                              _normal,
                              _angleSliceStartDeg,
                              _angleSliceEndDeg,
                              _radiusRing,
                              _radiusLine,
                              Config::cfg().qualitySphere,
                              Config::cfg().qualityLine,
                              _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DTORUSSLICE_H
