#ifndef UNIVERSE1_VIDEO_ITEM3DSPHERE_H
#define UNIVERSE1_VIDEO_ITEM3DSPHERE_H

#include "../torus/item3dtorusarcslice.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Sphere item */
struct Item3DSphere : public Item3DBase
{
    const bool inner;            //!< Is inner flag
    DynamicVec3 center;          //!< Center point
    DynamicValue<float> radius;  //!< Sphere radius
    DynamicValue<uint> quality;  //!< Sphere circle quality

    /*!
     * \brief Constructor
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DSphere(const bool _inner,
                 const QVector3D &_center,
                 const float _radius,
                 const uint _quality,
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
     * \param _normal Sphere normal direction
     * \param _arm Sphere arm direction
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _material Material
     * \param _inner Is inner flag
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _radius,
                          const uint _quality,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _center Center point
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _material Material
     * \param _inner Is inner flag
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_center,
                                 const float _radius,
                                 const uint _quality,
                                 const Material &_material,
                                 const bool _inner = false)
    {
        buildData(_out, _center, nz, ny, _radius, _quality, _material, _inner);
    }

    /*!
     * \brief Append sphere into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Sphere normal direction
     * \param _arm Sphere arm direction
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _inner Is inner flag
     * \return
     */
    static void addSphere(Data3D &_data,
                          uint &_idx,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _radius,
                          const uint _quality,
                          const bool _inner = false);

    /*!
     * \brief Append sphere into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _inner Is inner flag
     * \return
     */
    inline static void addSphere(Data3D &_data,
                                 uint &_idx,
                                 const QVector3D &_center,
                                 const float _radius,
                                 const uint _quality,
                                 const bool _inner = false)
    {
        addSphere(_data, _idx, _center, nz, ny, _radius, _quality, _inner);
    }
};

/*! \brief Footage 3D sphere database */
struct DBItem3DSphere : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DSphere(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D sphere item
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DSphere *add(const bool _inner,
                      const QVector3D &_center,
                      const float _radius,
                      const uint _quality,
                      const bool _visible,
                      const Material &_material);
    //

    /*!
     * \brief Add outer 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *add(const QVector3D &_center,
                             const float _radius,
                             const uint _quality,
                             const bool _visible,
                             const Material &_material)
    {
        return add(false, _center, _radius, _quality, _visible, _material);
    }

    /*!
     * \brief Add inner 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *addInner(const QVector3D &_center,
                                  const float _radius,
                                  const uint _quality,
                                  const bool _visible,
                                  const Material &_material)
    {
        return add(true, _center, _radius, _quality, _visible, _material);
    }

    //

    /*!
     * \brief Add outer visible 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *
    add(const QVector3D &_center, const float _radius, const uint _quality, const Material &_material)
    {
        return add(_center, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add outer visible 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *add(const QVector3D &_center, const float _radius, const Material &_material)
    {
        return add(_center, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add outer hidden 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *
    addHidden(const QVector3D &_center, const float _radius, const uint _quality, const Material &_material)
    {
        return add(_center, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add outer hidden 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *addHidden(const QVector3D &_center, const float _radius, const Material &_material)
    {
        return addHidden(_center, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add inner visible 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *
    addInner(const QVector3D &_center, const float _radius, const uint _quality, const Material &_material)
    {
        return addInner(_center, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add inner visible 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *addInner(const QVector3D &_center, const float _radius, const Material &_material)
    {
        return addInner(_center, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add inner hidden 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *
    addInnerHidden(const QVector3D &_center, const float _radius, const uint _quality, const Material &_material)
    {
        return addInner(_center, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add inner hidden 3D sphere item
     * \param _center Initial center point
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphere *addInnerHidden(const QVector3D &_center, const float _radius, const Material &_material)
    {
        return addInnerHidden(_center, _radius, Config::cfg().qualitySphere, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DSPHERE_H
