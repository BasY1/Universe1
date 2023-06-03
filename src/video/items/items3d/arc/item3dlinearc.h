#ifndef UNIVERSE1_VIDEO_ITEM3DLINEARC_H
#define UNIVERSE1_VIDEO_ITEM3DLINEARC_H

#include "item3dlinecircle.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Line arc item */
struct Item3DLineArc : public Item3DLineCircle
{
    DynamicVec3 arm;               //!< Arm direction
    DynamicValue<float> angleDeg;  //!< Arc angle in degrees

    /*!
     * \brief Constructor
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _arm Initial arm direction
     * \param _angleDeg Initial arc angle in degrees
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineArc(const QVector3D &_center,
                  const QVector3D &_normal,
                  const QVector3D &_arm,
                  const float _angleDeg,
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

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _center Center point
     * \param _normal Normal
     * \param _arm Arm direction
     * \param _angleDeg Arc angle in degrees
     * \param _radiusCircle Radius circle (torus)
     * \param _radiusLine Radius line (body)
     * \param _qualityCircle Circle quality circle
     * \param _qualityLine Circle quality line
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _angleDeg,
                          const float _radiusCircle,
                          const float _radiusLine,
                          const uint _qualityCircle,
                          const uint _qualityLine,
                          const Material &_material);
};

/*! \brief Footage 3D arc database */
struct DBItem3DLineArc : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLineArc(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D arc item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _arm Initial arm direction
     * \param _angleDeg Initial arc angle in degrees
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineArc *add(const QVector3D &_center,
                       const QVector3D &_normal,
                       const QVector3D &_arm,
                       const float _angleDeg,
                       const float _radiusCircle,
                       const float _radiusLine,
                       const uint _qualityCircle,
                       const uint _qualityLine,
                       const bool _visible,
                       const Material &_material);

    /*!
     * \brief Add visible 3D arc item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _arm Initial arm direction
     * \param _angleDeg Initial arc angle in degrees
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineArc *add(const QVector3D &_center,
                              const QVector3D &_normal,
                              const QVector3D &_arm,
                              const float _angleDeg,
                              const float _radiusCircle,
                              const float _radiusLine,
                              const uint _qualityCircle,
                              const uint _qualityLine,
                              const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleDeg,
                   _radiusCircle,
                   _radiusLine,
                   _qualityCircle,
                   _qualityLine,
                   true,
                   _material);
    }

    /*!
     * \brief Add visible 3D arc item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _arm Initial arm direction
     * \param _angleDeg Initial arc angle in degrees
     * \param _radiusCircle Initial radius circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineArc *add(const QVector3D &_center,
                              const QVector3D &_normal,
                              const QVector3D &_arm,
                              const float _angleDeg,
                              const float _radiusCircle,
                              const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleDeg,
                   _radiusCircle,
                   Config::cfg().lineRadius,
                   Config::cfg().qualitySphere,
                   Config::cfg().qualityLine,
                   _material);
    }

    //

    /*!
     * \brief Add hidden 3D arc item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _arm Initial arm direction
     * \param _angleDeg Initial arc angle in degrees
     * \param _radiusCircle Initial radius circle
     * \param _radiusLine Initial radius line
     * \param _qualityCircle Initial circle quality circle
     * \param _qualityLine Initial circle quality line
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineArc *addHidden(const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const QVector3D &_arm,
                                    const float _angleDeg,
                                    const float _radiusCircle,
                                    const float _radiusLine,
                                    const uint _qualityCircle,
                                    const uint _qualityLine,
                                    const Material &_material)
    {
        return add(_center,
                   _normal,
                   _arm,
                   _angleDeg,
                   _radiusCircle,
                   _radiusLine,
                   _qualityCircle,
                   _qualityLine,
                   false,
                   _material);
    }

    /*!
     * \brief Add hidden 3D arc item
     * \param _center Initial center point
     * \param _normal Initial normal
     * \param _arm Initial arm direction
     * \param _angleDeg Initial arc angle in degrees
     * \param _radiusCircle Initial radius circle
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineArc *addHidden(const QVector3D &_center,
                                    const QVector3D &_normal,
                                    const QVector3D &_arm,
                                    const float _angleDeg,
                                    const float _radiusCircle,
                                    const Material &_material)
    {
        return addHidden(_center,
                         _normal,
                         _arm,
                         _angleDeg,
                         _radiusCircle,
                         Config::cfg().lineRadius,
                         Config::cfg().qualitySphere,
                         Config::cfg().qualityLine,
                         _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINEARC_H
