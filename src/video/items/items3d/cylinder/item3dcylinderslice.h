#ifndef UNIVERSE1_VIDEO_ITEM3DCYLINDERSLICE_H
#define UNIVERSE1_VIDEO_ITEM3DCYLINDERSLICE_H

#include "item3dcylinder.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Cylinder item */
struct Item3DCylinderSlice : public Item3DCylinder
{
    DynamicVec3 arm;               //!< Slice arm direction
    DynamicValue<float> angleDeg;  //!< Slice angle in degrees

    /*!
     * \brief Constructor
     * \param _inner Is inner - flag
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DCylinderSlice(const bool _inner,
                        const QVector3D &_point1,
                        const QVector3D &_point2,
                        const QVector3D &_arm,
                        const float _radius1,
                        const float _radius2,
                        const float _angleDeg,
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
     * \param _point1 First point
     * \param _point2 Second point
     * \param _arm Arm direction
     * \param _radius1 Circle radius at first point
     * \param _radius2 Circle radius at second point
     * \param _angleDeg Slice angle in degrees
     * \param _quality Circle quality
     * \param _material Material
     * \param _inner Is inner flag
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_point1,
                          const QVector3D &_point2,
                          const QVector3D &_arm,
                          const float _radius1,
                          const float _radius2,
                          const float _angleDeg,
                          const uint _quality,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Append cylinder slice into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _point1 First point
     * \param _point2 Second point
     * \param _arm Arm direction
     * \param _radius1 Circle radius at first point
     * \param _radius2 Circle radius at second point
     * \param _angleDeg Slice angle in degrees
     * \param _quality Circle quality
     * \param _inner Is inner flag
     * \return
     */
    static void addCylinderSlice(Data3D &_data,
                                 uint &_idx,
                                 const QVector3D &_point1,
                                 const QVector3D &_point2,
                                 const QVector3D &_arm,
                                 const float _radius1,
                                 const float _radius2,
                                 const float _angleDeg,
                                 const uint _quality,
                                 const bool _inner = false);
};

/*! \brief Footage 3D cylinder slice database */
struct DBItem3DCylinderSlice : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DCylinderSlice(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D cylinder slice item
     * \param _inner Inner flag
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DCylinderSlice *add(const bool _inner,
                             const QVector3D &_point1,
                             const QVector3D &_point2,
                             const QVector3D &_arm,
                             const float _radius1,
                             const float _radius2,
                             const float _angleDeg,
                             const uint _quality,
                             const bool _visible,
                             const Material &_material);
    //

    /*!
     * \brief Add outer 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *add(const QVector3D &_point1,
                                    const QVector3D &_point2,
                                    const QVector3D &_arm,
                                    const float _radius1,
                                    const float _radius2,
                                    const float _angleDeg,
                                    const uint _quality,
                                    const bool _visible,
                                    const Material &_material)
    {
        return add(false, _point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, _visible, _material);
    }

    /*!
     * \brief Add inner 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addInner(const QVector3D &_point1,
                                         const QVector3D &_point2,
                                         const QVector3D &_arm,
                                         const float _radius1,
                                         const float _radius2,
                                         const float _angleDeg,
                                         const uint _quality,
                                         const bool _visible,
                                         const Material &_material)
    {
        return add(true, _point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, _visible, _material);
    }

    //

    /*!
     * \brief Add outer visible 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *add(const QVector3D &_point1,
                                    const QVector3D &_point2,
                                    const QVector3D &_arm,
                                    const float _radius1,
                                    const float _radius2,
                                    const float _angleDeg,
                                    const uint _quality,
                                    const Material &_material)
    {
        return add(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, true, _material);
    }

    /*!
     * \brief Add outer visible 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *add(const QVector3D &_point1,
                                    const QVector3D &_point2,
                                    const QVector3D &_arm,
                                    const float _radius1,
                                    const float _radius2,
                                    const float _angleDeg,
                                    const Material &_material)
    {
        return add(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    /*!
     * \brief Add outer hidden 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addHidden(const QVector3D &_point1,
                                          const QVector3D &_point2,
                                          const QVector3D &_arm,
                                          const float _radius1,
                                          const float _radius2,
                                          const float _angleDeg,
                                          const uint _quality,
                                          const Material &_material)
    {
        return add(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, false, _material);
    }

    /*!
     * \brief Add outer hidden 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addHidden(const QVector3D &_point1,
                                          const QVector3D &_point2,
                                          const QVector3D &_arm,
                                          const float _radius1,
                                          const float _radius2,
                                          const float _angleDeg,
                                          const Material &_material)
    {
        return addHidden(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add inner visible 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addInner(const QVector3D &_point1,
                                         const QVector3D &_point2,
                                         const QVector3D &_arm,
                                         const float _radius1,
                                         const float _radius2,
                                         const float _angleDeg,
                                         const uint _quality,
                                         const Material &_material)
    {
        return addInner(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, true, _material);
    }

    /*!
     * \brief Add inner visible 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addInner(const QVector3D &_point1,
                                         const QVector3D &_point2,
                                         const QVector3D &_arm,
                                         const float _radius1,
                                         const float _radius2,
                                         const float _angleDeg,
                                         const Material &_material)
    {
        return addInner(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    /*!
     * \brief Add inner hidden 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addInnerHidden(const QVector3D &_point1,
                                               const QVector3D &_point2,
                                               const QVector3D &_arm,
                                               const float _radius1,
                                               const float _radius2,
                                               const float _angleDeg,
                                               const uint _quality,
                                               const Material &_material)
    {
        return addInner(_point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, false, _material);
    }

    /*!
     * \brief Add inner hidden 3D cylinder slice item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _arm Initial arm direction
     * \param _radius1 Initial circle radius at first point
     * \param _radius2 Initial circle radius at second point
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DCylinderSlice *addInnerHidden(const QVector3D &_point1,
                                               const QVector3D &_point2,
                                               const QVector3D &_arm,
                                               const float _radius1,
                                               const float _radius2,
                                               const float _angleDeg,
                                               const Material &_material)
    {
        return addInnerHidden(
            _point1, _point2, _arm, _radius1, _radius2, _angleDeg, Config::cfg().qualitySphere, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DCYLINDERSLICE_H
