#ifndef UNIVERSE1_VIDEO_ITEM3DPLANE_H
#define UNIVERSE1_VIDEO_ITEM3DPLANE_H

#include "../text3d/item3dtext.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Plane item */
struct Item3DPlane : public Item3DBase
{
    DynamicVec3 center;  //!< Center position
    DynamicVec3 arm1;    //!< First plane arm
    DynamicVec3 arm2;    //!< Second plane arm

    /*!
     * \brief Constructor
     * \param _center Initial center position
     * \param _arm1 Initial first plane arm
     * \param _arm2 Initial second plane arm
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DPlane(const QVector3D &_center,
                const QVector3D &_arm1,
                const QVector3D &_arm2,
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
     * \param _center Center position
     * \param _arm1 First plane arm
     * \param _arm2 Second plane arm
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_arm1,
                          const QVector3D &_arm2,
                          const Material &_material);
};

/*! \brief Footage 3D plane database */
struct DBItem3DPlane : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DPlane(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D plane item
     * \param _center Initial center position
     * \param _arm1 Initial first plane arm
     * \param _arm2 Initial second plane arm
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DPlane *add(const QVector3D &_center,
                     const QVector3D &_arm1,
                     const QVector3D &_arm2,
                     const bool _visible,
                     const Material &_material);

    /*!
     * \brief Add visible 3D plane item
     * \param _center Initial center position
     * \param _arm1 Initial first plane arm
     * \param _arm2 Initial second plane arm
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPlane *
    add(const QVector3D &_center, const QVector3D &_arm1, const QVector3D &_arm2, const Material &_material)
    {
        return add(_center, _arm1, _arm2, true, _material);
    }

    /*!
     * \brief Add hidden 3D plane item
     * \param _center Initial center position
     * \param _arm1 Initial first plane arm
     * \param _arm2 Initial second plane arm
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DPlane *
    addHidden(const QVector3D &_center, const QVector3D &_arm1, const QVector3D &_arm2, const Material &_material)
    {
        return add(_center, _arm1, _arm2, false, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DPLANE_H
