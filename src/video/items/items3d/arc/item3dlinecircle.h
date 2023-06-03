#ifndef UNIVERSE1_VIDEO_ITEM3DLINECIRCLE_H
#define UNIVERSE1_VIDEO_ITEM3DLINECIRCLE_H

#include "../line/item3dlinecross.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Line circle item */
struct Item3DLineCircle : public Item3DBase
{
    DynamicVec3 center;                //!< Center point
    DynamicVec3 normal;                //!< Normal
    DynamicValue<float> radiusCircle;  //!< Radius circle (torus)
    DynamicValue<float> radiusLine;    //!< Radius line (body)
    DynamicValue<uint> qualityCircle;  //!< Circle quality circle
    DynamicValue<uint> qualityLine;    //!< Circle quality line

    /*!
     * \brief Constructor
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineCircle(const QVector3D &_center,
                     const QVector3D &_normal,
                     const float _radiusCircle,
                     const float _radiusLine,
                     const uint _qualityCircle,
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
};

/*! \brief Footage 3D circle database */
struct DBItem3DLineCircle : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLineCircle(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineCircle *add(const QVector3D &_center,
                          const QVector3D &_normal,
                          const float _radiusCircle,
                          const float _radiusLine,
                          const uint _qualityCircle,
                          const uint _qualityLine,
                          const bool _visible,
                          const Material &_material);

    //

    /*!
     * \brief Add visible 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCircle *add(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _radiusCircle,
                                 const float _radiusLine,
                                 const uint _qualityCircle,
                                 const uint _qualityLine,
                                 const Material &_material)
    {
        return add(_center, _normal, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, true, _material);
    }

    /*!
     * \brief Add visible 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCircle *add(const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const float _radiusCircle,
                                 const float _radiusLine,
                                 const Material &_material)
    {
        return add(_center,
                   _normal,
                   _radiusCircle,
                   _radiusLine,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _material);
    }

    /*!
     * \brief Add visible 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCircle *
    add(const QVector3D &_center, const QVector3D &_normal, const float _radiusCircle, const Material &_material)
    {
        return add(_center, _normal, _radiusCircle, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add hidden 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCircle *addHidden(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const float _radiusCircle,
                                       const float _radiusLine,
                                       const uint _qualityCircle,
                                       const uint _qualityLine,
                                       const Material &_material)
    {
        return add(_center, _normal, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, false, _material);
    }

    /*!
     * \brief Add hidden 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCircle *addHidden(const QVector3D &_center,
                                       const QVector3D &_normal,
                                       const float _radiusCircle,
                                       const float _radiusLine,
                                       const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _radiusCircle,
                         _radiusLine,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }

    /*!
     * \brief Add hidden 3D circle item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _radiusCircle Initial radius circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineCircle *
    addHidden(const QVector3D &_center, const QVector3D &_normal, const float _radiusCircle, const Material &_material)
    {
        return addHidden(_center, _normal, _radiusCircle, Config::cfg().lineRadius, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINECIRCLE_H
