#ifndef UNIVERSE1_VIDEO_ITEM3DPLANECIRCLESLICE_H
#define UNIVERSE1_VIDEO_ITEM3DPLANECIRCLESLICE_H

#include "item3dplanecircle.h"

namespace Universe1 {
namespace Video {

/*! \brief Slice of 3D Circle plane item */
struct Item3DPlaneCircleSlice : public Item3DPlaneCircle
{
    DynamicVec3 arm;               //!< Arm direction
    DynamicValue<float> angleDeg;  //!< Slice angle in degrees

    /*!
     * \brief Constructor
     * \param _center Initial center position
     * \param _normal Initial plane normal
     * \param _arm Initial arm direction
     * \param _radius Initial circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DPlaneCircleSlice(const QVector3D &_center,
                           const QVector3D &_normal,
                           const QVector3D &_arm,
                           const float _radius,
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
     * \param _center Central point
     * \param _normal Plane normal
     * \param _arm Staring arm
     * \param _radius Circle radius
     * \param _angleDeg Slice angle in degrees
     * \param _quality Circle quality
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _radius,
                          const float _angleDeg,
                          const uint _quality,
                          const Material &_material);

    /*!
     * \brief Append circle plane slice into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _center Central point
     * \param _normal Plane normal
     * \param _arm Staring arm
     * \param _radius Circle radius
     * \param _angleDeg Slice angle in degrees
     * \param _quality Circle quality
     * \return
     */
    static void addCircleSlice(Data3D &_data,
                               uint &_idx,
                               const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _radius,
                               const float _angleDeg,
                               const uint _quality);
};

/*! \brief Footage slice of 3D circle plane database */
struct DBItem3DPlaneCircleSlice : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DPlaneCircleSlice(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D circle plane slice item
     * \param _center Initial center position
     * \param _normal Initial plane normal
     * \param _arm Initial arm direction
     * \param _radius Initial circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DPlaneCircleSlice *add(const QVector3D &_center,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const float _radius,
                                const float _angleDeg,
                                const uint _quality,
                                const bool _visible,
                                const Material &_material);

    /*!
     * \brief Add visible 3D circle plane slice item
     * \param _center Initial center position
     * \param _normal Initial plane normal
     * \param _arm Initial arm direction
     * \param _radius Initial circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPlaneCircleSlice *add(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const QVector3D &_arm,
                                       const float _radius,
                                       const float _angleDeg,
                                       const uint _quality,
                                       const Material &_material)
    {
        return add(_center, _normal, _arm, _radius, _angleDeg, _quality, true, _material);
    }

    /*!
     * \brief Add visible 3D circle plane slice item
     * \param _center Initial center position
     * \param _normal Initial plane normal
     * \param _arm Initial arm direction
     * \param _radius Initial circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPlaneCircleSlice *add(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const QVector3D &_arm,
                                       const float _radius,
                                       const float _angleDeg,
                                       const Material &_material)
    {
        return add(_center, _normal, _arm, _radius, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add hidden 3D circle plane slice item
     * \param _center Initial center position
     * \param _normal Initial plane normal
     * \param _arm Initial arm direction
     * \param _radius Initial circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPlaneCircleSlice *addHidden(const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _radius,
                                             const float _angleDeg,
                                             const uint _quality,
                                             const Material &_material)
    {
        return add(_center, _normal, _arm, _radius, _angleDeg, _quality, true, _material);
    }

    /*!
     * \brief Add hidden 3D circle plane slice item
     * \param _center Initial center position
     * \param _normal Initial plane normal
     * \param _arm Initial arm direction
     * \param _radius Initial circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPlaneCircleSlice *addHidden(const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _radius,
                                             const float _angleDeg,
                                             const Material &_material)
    {
        return addHidden(_center, _normal, _arm, _radius, _angleDeg, Config::cfg().qualitySphere, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DPLANECIRCLESLICE_H
