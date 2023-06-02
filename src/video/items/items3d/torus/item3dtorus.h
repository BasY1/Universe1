#ifndef UNIVERSE1_VIDEO_ITEM3DTORUS_H
#define UNIVERSE1_VIDEO_ITEM3DTORUS_H

#include "../cylinder/item3dcylinderslice.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Torus item */
struct Item3DTorus : public Item3DBase
{
    const bool inner;                //!< Is inner flag
    DynamicVec3 center;              //!< Center point
    DynamicVec3 normal;              //!< Normal
    DynamicValue<float> radiusRing;  //!< Radius ring (torus)
    DynamicValue<float> radiusLine;  //!< Radius line (body)
    DynamicValue<uint> qualityRing;  //!< Circle quality ring
    DynamicValue<uint> qualityLine;  //!< Circle quality line

    /*!
     * \brief Constructor
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DTorus(const bool _inner,
                const QVector3D &_center,
                const QVector3D &_normal,
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
                  _radiusRing,
                  _radiusLine,
                  _qualityRing,
                  _qualityLine,
                  _material,
                  _inner);
    }

    /*!
     * \brief Append torus into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Normal
     * \param _arm Arm direction
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _inner Is inner flag
     * \return
     */
    static void addTorus(Data3D &_data,
                         uint &_idx,
                         const QVector3D &_center,
                         const QVector3D &_normal,
                         const QVector3D &_arm,
                         const float _radiusRing,
                         const float _radiusLine,
                         const uint _qualityRing,
                         const uint _qualityLine,
                         const bool _inner = false);

    /*!
     * \brief Append torus into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Normal
     * \param _radiusRing Radius ring
     * \param _radiusLine Radius line
     * \param _qualityRing Circle quality ring
     * \param _qualityLine Circle quality line
     * \param _inner Is inner flag
     * \return
     */
    inline static void addTorus(Data3D &_data,
                                uint &_idx,
                                const QVector3D &_center,
                                const QVector3D &_normal,
                                const float _radiusRing,
                                const float _radiusLine,
                                const uint _qualityRing,
                                const uint _qualityLine,
                                const bool _inner = false)
    {
        addTorus(_data,
                 _idx,
                 _center,
                 _normal,
                 perpendicularNormal(_normal),
                 _radiusRing,
                 _radiusLine,
                 _qualityRing,
                 _qualityLine,
                 _inner);
    }
};

/*! \brief Footage 3D torus database */
struct DBItem3DTorus : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DTorus(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D torus item
     * \param _inner Inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DTorus *add(const bool _inner,
                     const QVector3D &_center,
                     const QVector3D &_normal,
                     const float _radiusRing,
                     const float _radiusLine,
                     const uint _qualityRing,
                     const uint _qualityLine,
                     const bool _visible,
                     const Material &_material);

    //

    /*!
     * \brief Add outer 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *add(const QVector3D &_center,
                            const QVector3D &_normal,
                            const float _radiusRing,
                            const float _radiusLine,
                            const uint _qualityRing,
                            const uint _qualityLine,
                            const bool _visible,
                            const Material &_material)
    {
        return add(false, _center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _visible, _material);
    }

    /*!
     * \brief Add inner 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addInner(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const uint _qualityRing,
                                 const uint _qualityLine,
                                 const bool _visible,
                                 const Material &_material)
    {
        return add(true, _center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _visible, _material);
    }

    //

    /*!
     * \brief Add outer visible 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *add(const QVector3D &_center,
                            const QVector3D &_normal,
                            const float _radiusRing,
                            const float _radiusLine,
                            const uint _qualityRing,
                            const uint _qualityLine,
                            const Material &_material)
    {
        return add(_center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, true, _material);
    }

    /*!
     * \brief Add outer visible 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *add(const QVector3D &_center,
                            const QVector3D &_normal,
                            const float _radiusRing,
                            const float _radiusLine,
                            const Material &_material)
    {
        return add(_center,
                   _normal,
                   _radiusRing,
                   _radiusLine,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _material);
    }

    //

    /*!
     * \brief Add outer hidden 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addHidden(const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const float _radiusRing,
                                  const float _radiusLine,
                                  const uint _qualityRing,
                                  const uint _qualityLine,
                                  const Material &_material)
    {
        return add(_center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, false, _material);
    }

    /*!
     * \brief Add outer hidden 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addHidden(const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const float _radiusRing,
                                  const float _radiusLine,
                                  const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _radiusRing,
                         _radiusLine,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }

    //

    /*!
     * \brief Add inner visible 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addInner(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const uint _qualityRing,
                                 const uint _qualityLine,
                                 const Material &_material)
    {
        return addInner(_center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, true, _material);
    }

    /*!
     * \brief Add inner visible 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addInner(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _radiusRing,
                                 const float _radiusLine,
                                 const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _radiusRing,
                        _radiusLine,
                        Config::cfg().qualitySphere,
                        Config::cfg().qualityLine,
                        _material);
    }

    //

    /*!
     * \brief Add inner hidden 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _qualityRing Initial circle quality ring
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addInnerHidden(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const float _radiusRing,
                                       const float _radiusLine,
                                       const uint _qualityRing,
                                       const uint _qualityLine,
                                       const Material &_material)
    {
        return addInner(_center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, false, _material);
    }

    /*!
     * \brief Add inner hidden 3D torus item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusRing Initial radius ring
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DTorus *addInnerHidden(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const float _radiusRing,
                                       const float _radiusLine,
                                       const Material &_material)
    {
        return addInnerHidden(_center,
                              _normal,
                              _radiusRing,
                              _radiusLine,
                              Config::cfg().qualitySphere,
                              Config::cfg().qualityLine,
                              _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DTORUS_H
