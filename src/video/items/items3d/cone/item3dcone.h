#ifndef UNIVERSE1_VIDEO_ITEM3DCONE_H
#define UNIVERSE1_VIDEO_ITEM3DCONE_H

#include "../plane/item3dplanecircleslice.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Cone item */
struct Item3DCone : public Item3DBase
{
    const bool inner;            //!< Is inner flag
    DynamicVec3 pointBottom;     //!< Bottom point (center of circular plane)
    DynamicVec3 pointTop;        //!< Top (arrow) point
    DynamicValue<float> radius;  //!< Bottom circle radius
    DynamicValue<uint> quality;  //!< Circle quality

    /*!
     * \brief Constructor
     * \param _inner Inner flag
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DCone(const bool _inner,
               const QVector3D &_pointBottom,
               const QVector3D &_pointTop,
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
     * \param _pointBottom Bottom point
     * \param _pointTop Top point
     * \param _arm Start arm direction
     * \param _radius Bottom circle radius
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
                          const uint _quality,
                          const Material &_material,
                          const bool _inner = false);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _pointBottom Bottom point
     * \param _pointTop Top point
     * \param _radius Bottom circle radius
     * \param _quality Circle quality
     * \param _material Material
     * \param _inner Inner cone flag
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_pointBottom,
                                 const QVector3D &_pointTop,
                                 const float _radius,
                                 const uint _quality,
                                 const Material &_material,
                                 const bool _inner = false)
    {
        buildData(_out,
                  _pointBottom,
                  _pointTop,
                  perpendicularNormal(_pointTop - _pointBottom),
                  _radius,
                  _quality,
                  _material,
                  _inner);
    }

    /*!
     * \brief Append cone into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _pointBottom Bottom point
     * \param _pointTop Top point
     * \param _arm Start arm direction
     * \param _radius Bottom circle radius
     * \param _quality Circle quality
     * \param _inner Inner cone flag
     * \return
     */
    static void addCone(Data3D &_data,
                        uint &_idx,
                        const QVector3D &_pointBottom,
                        const QVector3D &_pointTop,
                        const QVector3D &_arm,
                        const float _radius,
                        const uint _quality,
                        const bool _inner = false);

    /*!
     * \brief Append cone into 3D data object
     * \param _data 3D data object
     * \param _idx Current indices cursor
     * \param _pointBottom Bottom point
     * \param _pointTop Top point
     * \param _radius Bottom circle radius
     * \param _quality Circle quality
     * \param _inner Inner cone flag
     * \return
     */
    inline static void addCone(Data3D &_data,
                               uint &_idx,
                               const QVector3D &_pointBottom,
                               const QVector3D &_pointTop,
                               const float _radius,
                               const uint _quality,
                               const bool _inner = false)
    {
        addCone(_data,
                _idx,
                _pointBottom,
                _pointTop,
                perpendicularNormal(_pointTop - _pointBottom),
                _radius,
                _quality,
                _inner);
    }
};

/*! \brief Footage 3D cone database */
struct DBItem3DCone : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DCone(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D cone item
     * \param _inner Inner flag
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *add(const bool _inner,
                    const QVector3D &_pointBottom,
                    const QVector3D &_pointTop,
                    const float _radius,
                    const uint _quality,
                    const bool _visible,
                    const Material &_material);

    //

    /*!
     * \brief Add 3D outer cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *add(const QVector3D &_pointBottom,
                    const QVector3D &_pointTop,
                    const float _radius,
                    const uint _quality,
                    const bool _visible,
                    const Material &_material)
    {
        return add(false, _pointBottom, _pointTop, _radius, _quality, _visible, _material);
    }

    /*!
     * \brief Add 3D inner cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *addInner(const QVector3D &_pointBottom,
                         const QVector3D &_pointTop,
                         const float _radius,
                         const uint _quality,
                         const bool _visible,
                         const Material &_material)
    {
        return add(true, _pointBottom, _pointTop, _radius, _quality, _visible, _material);
    }

    //

    /*!
     * \brief Add 3D outer visible cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *add(const QVector3D &_pointBottom,
                    const QVector3D &_pointTop,
                    const float _radius,
                    const uint _quality,
                    const Material &_material)
    {
        return add(_pointBottom, _pointTop, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add 3D outer visible cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *
    add(const QVector3D &_pointBottom, const QVector3D &_pointTop, const float _radius, const Material &_material)
    {
        return add(_pointBottom, _pointTop, _radius, Config::cfg().qualitySphere, _material);
    }

    /*!
     * \brief Add 3D outer hidden cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *addHidden(const QVector3D &_pointBottom,
                          const QVector3D &_pointTop,
                          const float _radius,
                          const uint _quality,
                          const Material &_material)
    {
        return add(_pointBottom, _pointTop, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add 3D outer hidden cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *
    addHidden(const QVector3D &_pointBottom, const QVector3D &_pointTop, const float _radius, const Material &_material)
    {
        return addHidden(_pointBottom, _pointTop, _radius, Config::cfg().qualitySphere, _material);
    }

    //

    /*!
     * \brief Add 3D inner visible cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *addInner(const QVector3D &_pointBottom,
                         const QVector3D &_pointTop,
                         const float _radius,
                         const uint _quality,
                         const Material &_material)
    {
        return addInner(_pointBottom, _pointTop, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add 3D inner visible cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *
    addInner(const QVector3D &_pointBottom, const QVector3D &_pointTop, const float _radius, const Material &_material)
    {
        return addInner(_pointBottom, _pointTop, _radius, Config::cfg().qualitySphere, _material);
    }

    /*!
     * \brief Add 3D inner hidden cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _quality Initial circle quality
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *addInnerHidden(const QVector3D &_pointBottom,
                               const QVector3D &_pointTop,
                               const float _radius,
                               const uint _quality,
                               const Material &_material)
    {
        return addInner(_pointBottom, _pointTop, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add 3D inner hidden cone item
     * \param _pointBottom Initial bottom point
     * \param _pointTop Initial top point
     * \param _radius Initial bottom circle radius
     * \param _material Initial material
     * \return Created item
     */
    Item3DCone *addInnerHidden(const QVector3D &_pointBottom,
                               const QVector3D &_pointTop,
                               const float _radius,
                               const Material &_material)
    {
        return addInnerHidden(_pointBottom, _pointTop, _radius, Config::cfg().qualitySphere, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DCONE_H
