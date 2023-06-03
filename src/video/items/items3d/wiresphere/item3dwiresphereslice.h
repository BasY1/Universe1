#ifndef UNIVERSE1_VIDEO_ITEM3DWIRESPHERESLICE_H
#define UNIVERSE1_VIDEO_ITEM3DWIRESPHERESLICE_H

#include "item3dwirespherecup.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D wire-frame sphere slice item */
struct Item3DWireSphereSlice : public Item3DWireSphere
{
    DynamicValue<float> angleLatBeginDeg;  //!< Begin angle latitude in degrees (0)
    DynamicValue<float> angleLatEndDeg;    //!< End angle latitude in degrees (180)
    DynamicValue<float> angleLonBeginDeg;  //!< Begin angle longitude in degrees (0)
    DynamicValue<float> angleLonEndDeg;    //!< End angle longitude in degrees (360)

    /*!
     * \brief Constructor
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _radiusLine Initial radius line
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DWireSphereSlice(const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _angleLatBeginDeg,
                          const float _angleLatEndDeg,
                          const float _angleLonBeginDeg,
                          const float _angleLonEndDeg,
                          const float _radiusSphere,
                          const float _radiusLine,
                          const uint _qualityLatLong,
                          const uint _qualitySphere,
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
     * \param _normal Normal direction
     * \param _arm Arm direction
     * \param _angleLatBeginDeg Begin angle latitude in degrees
     * \param _angleLatEndDeg End angle latitude in degrees
     * \param _angleLonBeginDeg Begin angle longitude in degrees
     * \param _angleLonEndDeg End angle longitude in degrees
     * \param _radiusSphere Radius sphere
     * \param _radiusLine Radius line
     * \param _qualityLatLong Quality latitude-longitude circle
     * \param _qualitySphere Quality sphere circle
     * \param _qualityLine Quality line circle
     * \param _material Material
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
                          const float _radiusSphere,
                          const float _radiusLine,
                          const uint _qualityLatLong,
                          const uint _qualitySphere,
                          const uint _qualityLine,
                          const Material &_material);
};

/*! \brief Footage 3D wire-sphere slice database */
struct DBItem3DWireSphereSlice : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DWireSphereSlice(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _radiusLine Initial radius line
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DWireSphereSlice *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _angleLatBeginDeg,
                               const float _angleLatEndDeg,
                               const float _angleLonBeginDeg,
                               const float _angleLonEndDeg,
                               const float _radiusSphere,
                               const float _radiusLine,
                               const uint _qualityLatLong,
                               const uint _qualitySphere,
                               const uint _qualityLine,
                               const bool _visible,
                               const Material &_material);

    /*!
     * \brief Add visible 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _radiusLine Initial radius line
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DWireSphereSlice *add(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _angleLatBeginDeg,
                                      const float _angleLatEndDeg,
                                      const float _angleLonBeginDeg,
                                      const float _angleLonEndDeg,
                                      const float _radiusSphere,
                                      const float _radiusLine,
                                      const uint _qualityLatLong,
                                      const uint _qualitySphere,
                                      const uint _qualityLine,
                                      const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radiusSphere,
                   _radiusLine,
                   _qualityLatLong,
                   _qualitySphere,
                   _qualityLine,
                   true,
                   _material);
    }

    /*!
     * \brief Add visible 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DWireSphereSlice *add(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _angleLatBeginDeg,
                                      const float _angleLatEndDeg,
                                      const float _angleLonBeginDeg,
                                      const float _angleLonEndDeg,
                                      const float _radiusSphere,
                                      const uint _qualityLatLong,
                                      const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radiusSphere,
                   Config::cfg().lineRadius,
                   _qualityLatLong,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _material);
    }

    /*!
     * \brief Add visible 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DWireSphereSlice *add(const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _angleLatBeginDeg,
                                      const float _angleLatEndDeg,
                                      const float _angleLonBeginDeg,
                                      const float _angleLonEndDeg,
                                      const float _radiusSphere,
                                      const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radiusSphere,
                   Config::cfg().qualityLatLong,
                   _material);
    }

    /*!
     * \brief Add hidden 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _radiusLine Initial radius line
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _qualitySphere Initial quality sphere circle
     * \param _qualityLine Initial quality line circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DWireSphereSlice *addHidden(const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const QVector3D &_arm,
                                            const float _angleLatBeginDeg,
                                            const float _angleLatEndDeg,
                                            const float _angleLonBeginDeg,
                                            const float _angleLonEndDeg,
                                            const float _radiusSphere,
                                            const float _radiusLine,
                                            const uint _qualityLatLong,
                                            const uint _qualitySphere,
                                            const uint _qualityLine,
                                            const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radiusSphere,
                   _radiusLine,
                   _qualityLatLong,
                   _qualitySphere,
                   _qualityLine,
                   false,
                   _material);
    }

    /*!
     * \brief Add hidden 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _qualityLatLong Initial quality latitude-longitude circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DWireSphereSlice *addHidden(const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const QVector3D &_arm,
                                            const float _angleLatBeginDeg,
                                            const float _angleLatEndDeg,
                                            const float _angleLonBeginDeg,
                                            const float _angleLonEndDeg,
                                            const float _radiusSphere,
                                            const uint _qualityLatLong,
                                            const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _arm,
                         _angleLatBeginDeg,
                         _angleLatEndDeg,
                         _angleLonBeginDeg,
                         _angleLonEndDeg,
                         _radiusSphere,
                         Config::cfg().lineRadius,
                         _qualityLatLong,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }

    /*!
     * \brief Add hidden 3D wire-sphere slice item
     * \param _center Initial center point
     * \param _normal Initial normal direction
     * \param _arm Initial arm direction
     * \param _angleLatBeginDeg Initial begin angle latitude in degrees
     * \param _angleLatEndDeg Initial end angle latitude in degrees
     * \param _angleLonBeginDeg Initial begin angle longitude in degrees
     * \param _angleLonEndDeg Initial end angle longitude in degrees
     * \param _radiusSphere Initial radius sphere
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DWireSphereSlice *addHidden(const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const QVector3D &_arm,
                                            const float _angleLatBeginDeg,
                                            const float _angleLatEndDeg,
                                            const float _angleLonBeginDeg,
                                            const float _angleLonEndDeg,
                                            const float _radiusSphere,
                                            const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _arm,
                         _angleLatBeginDeg,
                         _angleLatEndDeg,
                         _angleLonBeginDeg,
                         _angleLonEndDeg,
                         _radiusSphere,
                         Config::cfg().qualityLatLong,
                         _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DWIRESPHERESLICE_H
