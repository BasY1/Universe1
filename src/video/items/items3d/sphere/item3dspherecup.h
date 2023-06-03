#ifndef UNIVERSE1_VIDEO_ITEM3DSPHERECUP_H
#define UNIVERSE1_VIDEO_ITEM3DSPHERECUP_H

#include "item3dsphere.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Sphere cup item */
struct Item3DSphereCup : public Item3DSphere
{
    DynamicVec3 normal;            //!< Sphere normal direction
    DynamicValue<float> angleDeg;  //!< Cup angle in degrees

    /*!
     * \brief Constructor
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DSphereCup(const bool _inner,
                    const QVector3D &_center,
                    const QVector3D &_normal,
                    const float _angleDeg,
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
     * \param _angleDeg Cup angle in degrees
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
                          const float _angleDeg,
                          const float _radius,
                          const uint _quality,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _center Center point
     * \param _normal Sphere normal direction
     * \param _angleDeg Cup angle in degrees
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _material Material
     * \param _inner Is inner flag
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _angleDeg,
                                 const float _radius,
                                 const uint _quality,
                                 const Material &_material,
                                 const bool _inner = false)
    {
        buildData(
            _out, _center, _normal, perpendicularNormal(_normal), _angleDeg, _radius, _quality, _material, _inner);
    }

    /*!
     * \brief Append sphere cup into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Sphere normal direction
     * \param _arm Sphere arm direction
     * \param _angleDeg Cup angle in degrees
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _inner Is inner flag
     * \return
     */
    static void addSphereCup(Data3D &_data,
                             uint &_idx,
                             const QVector3D &_center,
                             const QVector3D &_normal,
                             const QVector3D &_arm,
                             const float _angleDeg,
                             const float _radius,
                             const uint _quality,
                             const bool _inner = false);

    /*!
     * \brief Append sphere cup into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Center point
     * \param _normal Sphere normal direction
     * \param _angleDeg Cup angle in degrees
     * \param _radius Sphere radius
     * \param _quality Sphere circle quality
     * \param _inner Is inner flag
     * \return
     */
    inline static void addSphereCup(Data3D &_data,
                                    uint &_idx,
                                    const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const float _angleDeg,
                                    const float _radius,
                                    const uint _quality,
                                    const bool _inner = false)
    {
        addSphereCup(_data, _idx, _center, _normal, perpendicularNormal(_normal), _angleDeg, _radius, _quality, _inner);
    }
};

/*! \brief Footage 3D sphere cup database */
struct DBItem3DSphereCup : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DSphereCup(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D sphere cup item
     * \param _inner Is inner flag
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DSphereCup *add(const bool _inner,
                         const QVector3D &_center,
                         const QVector3D &_normal,
                         const float _angleDeg,
                         const float _radius,
                         const uint _quality,
                         const bool _visible,
                         const Material &_material);
    //

    /*!
     * \brief Add outer 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *add(const QVector3D &_center,
                                const QVector3D &_normal,
                                const float _angleDeg,
                                const float _radius,
                                const uint _quality,
                                const bool _visible,
                                const Material &_material)
    {
        return add(false, _center, _normal, _angleDeg, _radius, _quality, _visible, _material);
    }

    /*!
     * \brief Add inner 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addInner(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleDeg,
                                     const float _radius,
                                     const uint _quality,
                                     const bool _visible,
                                     const Material &_material)
    {
        return add(true, _center, _normal, _angleDeg, _radius, _quality, _visible, _material);
    }

    //

    /*!
     * \brief Add outer visible 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *add(const QVector3D &_center,
                                const QVector3D &_normal,
                                const float _angleDeg,
                                const float _radius,
                                const uint _quality,
                                const Material &_material)
    {
        return add(_center, _normal, _angleDeg, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add outer visible 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *add(const QVector3D &_center,
                                const QVector3D &_normal,
                                const float _angleDeg,
                                const float _radius,
                                const Material &_material)
    {
        return add(_center, _normal, _angleDeg, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add outer hidden 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addHidden(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const float _angleDeg,
                                      const float _radius,
                                      const uint _quality,
                                      const Material &_material)
    {
        return add(_center, _normal, _angleDeg, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add outer hidden 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addHidden(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const float _angleDeg,
                                      const float _radius,
                                      const Material &_material)
    {
        return addHidden(_center, _normal, _angleDeg, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add inner visible 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addInner(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleDeg,
                                     const float _radius,
                                     const uint _quality,
                                     const Material &_material)
    {
        return addInner(_center, _normal, _angleDeg, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add inner visible 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addInner(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const float _angleDeg,
                                     const float _radius,
                                     const Material &_material)
    {
        return addInner(_center, _normal, _angleDeg, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add inner hidden 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _quality Initial sphere circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addInnerHidden(const QVector3D &_center,
                                           const QVector3D &_normal,
                                           const float _angleDeg,
                                           const float _radius,
                                           const uint _quality,
                                           const Material &_material)
    {
        return addInner(_center, _normal, _angleDeg, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add inner hidden 3D sphere cup item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _angleDeg Initial cup angle in degrees
     * \param _radius Initial sphere radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DSphereCup *addInnerHidden(const QVector3D &_center,
                                           const QVector3D &_normal,
                                           const float _angleDeg,
                                           const float _radius,
                                           const Material &_material)
    {
        return addInnerHidden(_center, _normal, _angleDeg, _radius, Config::cfg().qualitySphere, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DSPHERECUP_H
