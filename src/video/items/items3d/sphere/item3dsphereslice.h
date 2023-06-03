#ifndef UNIVERSE1_VIDEO_ITEM3DSPHERESLICE_H
#define UNIVERSE1_VIDEO_ITEM3DSPHERESLICE_H

#include "item3dspherecup.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Sphere slice item */
struct Item3DSphereSlice : public Item3DSphere
{
    DynamicVec3 normal;                    //!< Sphere normal direction
    DynamicVec3 arm;                       //!< Sphere arm direction
    DynamicValue<float> angleLatBeginDeg;  //!< Begin angle latitude in degrees
    DynamicValue<float> angleLatEndDeg;    //!< End angle latitude in degrees
    DynamicValue<float> angleLonBeginDeg;  //!< Begin angle longitude in degrees
    DynamicValue<float> angleLonEndDeg;    //!< End angle longitude in degrees

    /*!
     * \brief Constructor
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DSphereSlice(const bool _inner,
                      const QVector3D &_center,
                      const QVector3D &_normal,
                      const QVector3D &_arm,
                      const float _angleLatBeginDeg,
                      const float _angleLatEndDeg,
                      const float _angleLonBeginDeg,
                      const float _angleLonEndDeg,
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
     * \param _angleLatBeginDeg Begin angle latitude in degrees
     * \param _angleLatEndDeg End angle latitude in degrees
     * \param _angleLonBeginDeg Begin angle longitude in degrees
     * \param _angleLonEndDeg End angle longitude in degrees
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
                          const float _angleLatBeginDeg,
                          const float _angleLatEndDeg,
                          const float _angleLonBeginDeg,
                          const float _angleLonEndDeg,
                          const float _radius,
                          const uint _quality,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Append sphere slice into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Sphere normal direction
     * \param _arm Sphere arm direction
     * \param _angleLatBeginDeg Begin angle latitude in degrees
     * \param _angleLatEndDeg End angle latitude in degrees
     * \param _angleLonBeginDeg Begin angle longitude in degrees
     * \param _angleLonEndDeg End angle longitude in degrees
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _inner Is inner flag
     * \return
     */
    static void addSphereSlice(Data3D &_data,
                               uint &_idx,
                               const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _angleLatBeginDeg,
                               const float _angleLatEndDeg,
                               const float _angleLonBeginDeg,
                               const float _angleLonEndDeg,
                               const float _radius,
                               const uint _quality,
                               const bool _inner = false);
};

/*! \brief Footage 3D sphere slice database */
struct DBItem3DSphereSlice : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DSphereSlice(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D sphere slice item
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DSphereSlice *add(const bool _inner,
                           const QVector3D &_center,
                           const QVector3D &_normal,
                           const QVector3D &_arm,
                           const float _angleLatBeginDeg,
                           const float _angleLatEndDeg,
                           const float _angleLonBeginDeg,
                           const float _angleLonEndDeg,
                           const float _radius,
                           const uint _quality,
                           const bool _visible,
                           const Material &_material);
    //

    /*!
     * \brief Add outer 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *add(const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const QVector3D &_arm,
                                  const float _angleLatBeginDeg,
                                  const float _angleLatEndDeg,
                                  const float _angleLonBeginDeg,
                                  const float _angleLonEndDeg,
                                  const float _radius,
                                  const uint _quality,
                                  const bool _visible,
                                  const Material &_material)
    {
        return add(false,
                   _center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radius,
                   _quality,
                   _visible,
                   _material);
    }

    /*!
     * \brief Add inner 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addInner(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const QVector3D &_arm,
                                       const float _angleLatBeginDeg,
                                       const float _angleLatEndDeg,
                                       const float _angleLonBeginDeg,
                                       const float _angleLonEndDeg,
                                       const float _radius,
                                       const uint _quality,
                                       const bool _visible,
                                       const Material &_material)
    {
        return add(true,
                   _center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radius,
                   _quality,
                   _visible,
                   _material);
    }

    //

    /*!
     * \brief Add outer visible 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *add(const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const QVector3D &_arm,
                                  const float _angleLatBeginDeg,
                                  const float _angleLatEndDeg,
                                  const float _angleLonBeginDeg,
                                  const float _angleLonEndDeg,
                                  const float _radius,
                                  const uint _quality,
                                  const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radius,
                   _quality,
                   true,
                   _material);
    }

    /*!
     * \brief Add outer visible 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *add(const QVector3D &_center,
                                  const QVector3D &_normal,
                                  const QVector3D &_arm,
                                  const float _angleLatBeginDeg,
                                  const float _angleLatEndDeg,
                                  const float _angleLonBeginDeg,
                                  const float _angleLonEndDeg,
                                  const float _radius,
                                  const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radius,
                   Config::cfg().qualitySphere,
                   _material);
    }

    //

    /*!
     * \brief Add outer hidden 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addHidden(const QVector3D &_center,
                                        const QVector3D &_normal,
                                        const QVector3D &_arm,
                                        const float _angleLatBeginDeg,
                                        const float _angleLatEndDeg,
                                        const float _angleLonBeginDeg,
                                        const float _angleLonEndDeg,
                                        const float _radius,
                                        const uint _quality,
                                        const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radius,
                   _quality,
                   false,
                   _material);
    }

    /*!
     * \brief Add outer hidden 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addHidden(const QVector3D &_center,
                                        const QVector3D &_normal,
                                        const QVector3D &_arm,
                                        const float _angleLatBeginDeg,
                                        const float _angleLatEndDeg,
                                        const float _angleLonBeginDeg,
                                        const float _angleLonEndDeg,
                                        const float _radius,
                                        const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _arm,
                         _angleLatBeginDeg,
                         _angleLatEndDeg,
                         _angleLonBeginDeg,
                         _angleLonEndDeg,
                         _radius,
                         Config::cfg().qualitySphere,
                         _material);
    }

    //

    /*!
     * \brief Add inner visible 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addInner(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const QVector3D &_arm,
                                       const float _angleLatBeginDeg,
                                       const float _angleLatEndDeg,
                                       const float _angleLonBeginDeg,
                                       const float _angleLonEndDeg,
                                       const float _radius,
                                       const uint _quality,
                                       const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _arm,
                        _angleLatBeginDeg,
                        _angleLatEndDeg,
                        _angleLonBeginDeg,
                        _angleLonEndDeg,
                        _radius,
                        _quality,
                        true,
                        _material);
    }

    /*!
     * \brief Add inner visible 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addInner(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const QVector3D &_arm,
                                       const float _angleLatBeginDeg,
                                       const float _angleLatEndDeg,
                                       const float _angleLonBeginDeg,
                                       const float _angleLonEndDeg,
                                       const float _radius,
                                       const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _arm,
                        _angleLatBeginDeg,
                        _angleLatEndDeg,
                        _angleLonBeginDeg,
                        _angleLonEndDeg,
                        _radius,
                        Config::cfg().qualitySphere,
                        _material);
    }

    //

    /*!
     * \brief Add inner hidden 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addInnerHidden(const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _angleLatBeginDeg,
                                             const float _angleLatEndDeg,
                                             const float _angleLonBeginDeg,
                                             const float _angleLonEndDeg,
                                             const float _radius,
                                             const uint _quality,
                                             const Material &_material)
    {
        return addInner(_center,
                        _normal,
                        _arm,
                        _angleLatBeginDeg,
                        _angleLatEndDeg,
                        _angleLonBeginDeg,
                        _angleLonEndDeg,
                        _radius,
                        _quality,
                        false,
                        _material);
    }

    /*!
     * \brief Add inner hidden 3D sphere slice item
     * \param _center Initial center point
     * \param _normal Initial sphere normal direction
     * \param _arm Initial sphere arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereSlice *addInnerHidden(const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _angleLatBeginDeg,
                                             const float _angleLatEndDeg,
                                             const float _angleLonBeginDeg,
                                             const float _angleLonEndDeg,
                                             const float _radius,
                                             const Material &_material)
    {
        return addInnerHidden(_center,
                              _normal,
                              _arm,
                              _angleLatBeginDeg,
                              _angleLatEndDeg,
                              _angleLonBeginDeg,
                              _angleLonEndDeg,
                              _radius,
                              Config::cfg().qualitySphere,
                              _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DSPHERESLICE_H
