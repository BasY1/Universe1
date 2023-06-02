#ifndef UNIVERSE1_VIDEO_ITEM3DCONESLICE_H
#define UNIVERSE1_VIDEO_ITEM3DCONESLICE_H

#include "item3dcone.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Cone slice item */
struct Item3DConeSlice : public Item3DCone
{
    DynamicVec3 arm;               //!< Slice arm direction
    DynamicValue<float> angleDeg;  //!< Slice angle in degrees

    /*!
     * \brief Constructor
     * \param _inner Inner flag
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DConeSlice(const bool _inner,
                    const QVector3D &_pointBottom,
                    const QVector3D &_pointTop,
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
     * \param _pointBottom Bottom point
     * \param _pointTop Top point
     * \param _arm Slice arm direction
     * \param _radius Bottom circle radius
     * \param _angleDeg Slice angle in degrees
     * \param _quality Circle quality
     * \param _material Material
     * \param _inner Inner cone flag
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_pointBottom,
                          const QVector3D &_pointTop,
                          const QVector3D &_arm,
                          const float _radius,
                          const float _angleDeg,
                          const uint _quality,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Append cone slice into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _pointBottom Bottom point
     * \param _pointTop Top point
     * \param _arm Start arm direction
     * \param _radius Bottom circle radius
     * \param _angleDeg Slice angle in degrees
     * \param _quality Circle quality
     * \param _inner Inner cone flag
     * \return
     */
    static void addConeSlice(Data3D &_data,
                             uint &_idx,
                             const QVector3D &_pointBottom,
                             const QVector3D &_pointTop,
                             const QVector3D &_arm,
                             const float _radius,
                             const float _angleDeg,
                             const uint _quality,
                             const bool _inner = false);
};

/*! \brief Footage 3D cone slice database */
struct DBItem3DConeSlice : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DConeSlice(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D cone slice item
     * \param _inner Inner flag
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *add(const bool _inner,
                         const QVector3D &_pointBottom,
                         const QVector3D &_pointTop,
                         const QVector3D &_arm,
                         const float _radius,
                         const float _angleDeg,
                         const uint _quality,
                         const bool _visible,
                         const Material &_material);

    //

    /*!
     * \brief Add 3D outer cone slice item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *add(const QVector3D &_pointBottom,
                         const QVector3D &_pointTop,
                         const QVector3D &_arm,
                         const float _radius,
                         const float _angleDeg,
                         const uint _quality,
                         const bool _visible,
                         const Material &_material)
    {
        return add(false, _pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, _visible, _material);
    }

    /*!
     * \brief Add 3D inner cone slice item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addInner(const QVector3D &_pointBottom,
                              const QVector3D &_pointTop,
                              const QVector3D &_arm,
                              const float _radius,
                              const float _angleDeg,
                              const uint _quality,
                              const bool _visible,
                              const Material &_material)
    {
        return add(true, _pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, _visible, _material);
    }

    //

    /*!
     * \brief Add 3D outer cone slice visible item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *add(const QVector3D &_pointBottom,
                         const QVector3D &_pointTop,
                         const QVector3D &_arm,
                         const float _radius,
                         const float _angleDeg,
                         const uint _quality,
                         const Material &_material)
    {
        return add(_pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, true, _material);
    }

    /*!
     * \brief Add 3D outer cone slice visible item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *add(const QVector3D &_pointBottom,
                         const QVector3D &_pointTop,
                         const QVector3D &_arm,
                         const float _radius,
                         const float _angleDeg,
                         const Material &_material)
    {
        return add(_pointBottom, _pointTop, _arm, _radius, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    /*!
     * \brief Add 3D outer cone slice hidden item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addHidden(const QVector3D &_pointBottom,
                               const QVector3D &_pointTop,
                               const QVector3D &_arm,
                               const float _radius,
                               const float _angleDeg,
                               const uint _quality,
                               const Material &_material)
    {
        return add(_pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, false, _material);
    }

    /*!
     * \brief Add 3D outer cone slice hidden item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addHidden(const QVector3D &_pointBottom,
                               const QVector3D &_pointTop,
                               const QVector3D &_arm,
                               const float _radius,
                               const float _angleDeg,
                               const Material &_material)
    {
        return addHidden(_pointBottom, _pointTop, _arm, _radius, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add 3D inner cone slice visible item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addInner(const QVector3D &_pointBottom,
                              const QVector3D &_pointTop,
                              const QVector3D &_arm,
                              const float _radius,
                              const float _angleDeg,
                              const uint _quality,
                              const Material &_material)
    {
        return addInner(_pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, true, _material);
    }

    /*!
     * \brief Add 3D inner cone slice visible item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addInner(const QVector3D &_pointBottom,
                              const QVector3D &_pointTop,
                              const QVector3D &_arm,
                              const float _radius,
                              const float _angleDeg,
                              const Material &_material)
    {
        return addInner(_pointBottom, _pointTop, _arm, _radius, _angleDeg, Config::cfg().qualitySphere, _material);
    }

    /*!
     * \brief Add 3D inner cone slice hidden item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addInnerHidden(const QVector3D &_pointBottom,
                                    const QVector3D &_pointTop,
                                    const QVector3D &_arm,
                                    const float _radius,
                                    const float _angleDeg,
                                    const uint _quality,
                                    const Material &_material)
    {
        return addInner(_pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, false, _material);
    }

    /*!
     * \brief Add 3D inner cone slice hidden item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _arm Initial arm direction
     * \param _radius Initial bottom circle radius
     * \param _angleDeg Initial slice angle in degrees
     * \param _material Initial material
     * \return Created item
     */
    Item3DConeSlice *addInnerHidden(const QVector3D &_pointBottom,
                                    const QVector3D &_pointTop,
                                    const QVector3D &_arm,
                                    const float _radius,
                                    const float _angleDeg,
                                    const Material &_material)
    {
        return addInnerHidden(
            _pointBottom, _pointTop, _arm, _radius, _angleDeg, Config::cfg().qualitySphere, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DCONESLICE_H
