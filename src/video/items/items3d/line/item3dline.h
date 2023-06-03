#ifndef UNIVERSE1_VIDEO_ITEM3DLINE_H
#define UNIVERSE1_VIDEO_ITEM3DLINE_H

#include "../sphere/item3dsphereslice.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Line item */
struct Item3DLine : public Item3DBase
{
    DynamicVec3 point;           //!< Line start point
    DynamicVec3 normal;          //!< Line normal
    DynamicValue<float> length;  //!< Line length
    DynamicValue<float> radius;  //!< Line radius
    DynamicValue<uint> quality;  //!< Line circle quality

    /*!
     * \brief Constructor
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLine(const QVector3D &_point,
               const QVector3D &_normal,
               const float _length,
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
     * \param _point  Line start point
     * \param _normal Line normal
     * \param _arm Start arm direction
     * \param _length Line length
     * \param _radius Line radius
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_point,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _length,
                          const float _radius,
                          const uint _quality,
                          const Material &_material);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _point  Line start point
     * \param _normal Line normal
     * \param _length Line length
     * \param _radius Line radius
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_point,
                                 const QVector3D &_normal,
                                 const float _length,
                                 const float _radius,
                                 const uint _quality,
                                 const Material &_material)
    {
        buildData(_out, _point, _normal, perpendicularNormal(_normal), _length, _radius, _quality, _material);
    }
};

/*! \brief 3D Line segment item */
struct Item3DLineSegment : public Item3DBase
{
    DynamicVec3 point1;          //!< First point
    DynamicVec3 point2;          //!< Second point
    DynamicValue<float> radius;  //!< Line radius
    DynamicValue<uint> quality;  //!< Line circle quality

    /*!
     * \brief Constructor
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineSegment(const QVector3D &_point1,
                      const QVector3D &_point2,
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
     * \param _point1 First point
     * \param _point2 Second point
     * \param _arm Starting arm direction
     * \param _radius Line radius
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_point1,
                          const QVector3D &_point2,
                          const QVector3D &_arm,
                          const float _radius,
                          const uint _quality,
                          const Material &_material);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _point1 First point
     * \param _point2 Second point
     * \param _radius Line radius
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_point1,
                                 const QVector3D &_point2,
                                 const float _radius,
                                 const uint _quality,
                                 const Material &_material)
    {
        buildData(_out,
                  _point1,
                  _point2,
                  perpendicularNormal((_point2 - _point1).normalized()),
                  _radius,
                  _quality,
                  _material);
    }
};

/*! \brief Footage 3D line database */
struct DBItem3DLine : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLine(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLine *add(const QVector3D &_point,
                    const QVector3D &_normal,
                    const float _length,
                    const float _radius,
                    const uint _quality,
                    const bool _visible,
                    const Material &_material);

    /*!
     * \brief Add 3D visible line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLine *add(const QVector3D &_point,
                           const QVector3D &_normal,
                           const float _length,
                           const float _radius,
                           const uint _quality,
                           const Material &_material)
    {
        return add(_point, _normal, _length, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add 3D visible line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLine *add(const QVector3D &_point,
                           const QVector3D &_normal,
                           const float _length,
                           const float _radius,
                           const Material &_material)
    {
        return add(_point, _normal, _length, _radius, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add 3D visible line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLine *
    add(const QVector3D &_point, const QVector3D &_normal, const float _length, const Material &_material)
    {
        return add(_point, _normal, _length, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add 3D hidden line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLine *addHidden(const QVector3D &_point,
                                 const QVector3D &_normal,
                                 const float _length,
                                 const float _radius,
                                 const uint _quality,
                                 const Material &_material)
    {
        return add(_point, _normal, _length, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add 3D hidden line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLine *addHidden(const QVector3D &_point,
                                 const QVector3D &_normal,
                                 const float _length,
                                 const float _radius,
                                 const Material &_material)
    {
        return addHidden(_point, _normal, _length, _radius, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add 3D hidden line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLine *
    addHidden(const QVector3D &_point, const QVector3D &_normal, const float _length, const Material &_material)
    {
        return addHidden(_point, _normal, _length, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineSegment *addSegment(const QVector3D &_point1,
                                  const QVector3D &_point2,
                                  const float _radius,
                                  const uint _quality,
                                  const bool _visible,
                                  const Material &_material);

    /*!
     * \brief Add visible 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineSegment *addSegment(const QVector3D &_point1,
                                         const QVector3D &_point2,
                                         const float _radius,
                                         const uint _quality,
                                         const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, _quality, true, _material);
    }

    /*!
     * \brief Add visible 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineSegment *
    addSegment(const QVector3D &_point1, const QVector3D &_point2, const float _radius, const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add visible 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineSegment *addSegment(const QVector3D &_point1, const QVector3D &_point2, const Material &_material)
    {
        return addSegment(_point1, _point2, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add hidden 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineSegment *addSegmentHidden(const QVector3D &_point1,
                                               const QVector3D &_point2,
                                               const float _radius,
                                               const uint _quality,
                                               const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, _quality, false, _material);
    }

    /*!
     * \brief Add hidden 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineSegment *
    addSegmentHidden(const QVector3D &_point1, const QVector3D &_point2, const float _radius, const Material &_material)
    {
        return addSegmentHidden(_point1, _point2, _radius, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add hidden 3D line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineSegment *
    addSegmentHidden(const QVector3D &_point1, const QVector3D &_point2, const Material &_material)
    {
        return addSegmentHidden(_point1, _point2, Config::cfg().lineRadius, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINE_H
