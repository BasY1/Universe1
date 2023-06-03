#ifndef UNIVERSE1_VIDEO_ITEM3DLINEDOTS_H
#define UNIVERSE1_VIDEO_ITEM3DLINEDOTS_H

#include "item3dline.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Line dots item */
struct Item3DLineDots : public Item3DLine
{
    DynamicValue<uint> multSpace;  //!< Space between dots length multiplier

    /*!
     * \brief Constructor
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineDots(const QVector3D &_point,
                   const QVector3D &_normal,
                   const float _length,
                   const float _radius,
                   const uint _multSpace,
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
     * \param _point Line start point
     * \param _normal Line normal
     * \param _length Line length
     * \param _radius Line radius
     * \param _multSpace Space between dash length multiplier
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_point,
                          const QVector3D &_normal,
                          const float _length,
                          const float _radius,
                          const uint _multSpace,
                          const uint _quality,
                          const Material &_material);
};

/*! \brief 3D Line dot segment item */
struct Item3DLineDotsSegment : public Item3DLineSegment
{
    DynamicValue<uint> multSpace;  //!< Space between dots length multiplier

    /*!
     * \brief Constructor
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DLineDotsSegment(const QVector3D &_point1,
                          const QVector3D &_point2,
                          const float _radius,
                          const uint _multSpace,
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
     * \param _radius Line radius
     * \param _multSpace Space between dots length multiplier
     * \param _quality Line circle quality
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_point1,
                          const QVector3D &_point2,
                          const float _radius,
                          const uint _multSpace,
                          const uint _quality,
                          const Material &_material);
};

/*! \brief Footage 3D dot line database */
struct DBItem3DLineDots : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLineDots(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineDots *add(const QVector3D &_point,
                        const QVector3D &_normal,
                        const float _length,
                        const float _radius,
                        const uint _multSpace,
                        const uint _quality,
                        const bool _visible,
                        const Material &_material);

    /*!
     * \brief Add visible 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *add(const QVector3D &_point,
                               const QVector3D &_normal,
                               const float _length,
                               const float _radius,
                               const uint _multSpace,
                               const uint _quality,
                               const Material &_material)
    {
        return add(_point, _normal, _length, _radius, _multSpace, _quality, true, _material);
    }

    /*!
     * \brief Add visible 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *add(const QVector3D &_point,
                               const QVector3D &_normal,
                               const float _length,
                               const float _radius,
                               const uint _multSpace,
                               const Material &_material)
    {
        return add(_point, _normal, _length, _radius, _multSpace, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add visible 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *add(const QVector3D &_point,
                               const QVector3D &_normal,
                               const float _length,
                               const float _radius,
                               const Material &_material)
    {
        return add(_point, _normal, _length, _radius, Config::cfg().lineMultSpace, _material);
    }

    /*!
     * \brief Add visible 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *
    add(const QVector3D &_point, const QVector3D &_normal, const float _length, const Material &_material)
    {
        return add(_point, _normal, _length, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add hidden 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *addHidden(const QVector3D &_point,
                                     const QVector3D &_normal,
                                     const float _length,
                                     const float _radius,
                                     const uint _multSpace,
                                     const uint _quality,
                                     const Material &_material)
    {
        return add(_point, _normal, _length, _radius, _multSpace, _quality, false, _material);
    }

    /*!
     * \brief Add hidden 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *addHidden(const QVector3D &_point,
                                     const QVector3D &_normal,
                                     const float _length,
                                     const float _radius,
                                     const uint _multSpace,
                                     const Material &_material)
    {
        return addHidden(_point, _normal, _length, _radius, _multSpace, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add hidden 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *addHidden(const QVector3D &_point,
                                     const QVector3D &_normal,
                                     const float _length,
                                     const float _radius,
                                     const Material &_material)
    {
        return addHidden(_point, _normal, _length, _radius, Config::cfg().lineMultSpace, _material);
    }

    /*!
     * \brief Add hidden 3D dot line item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _length Initial line length
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDots *
    addHidden(const QVector3D &_point, const QVector3D &_normal, const float _length, const Material &_material)
    {
        return addHidden(_point, _normal, _length, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DLineDotsSegment *addSegment(const QVector3D &_point1,
                                      const QVector3D &_point2,
                                      const float _radius,
                                      const uint _multSpace,
                                      const uint _quality,
                                      const bool _visible,
                                      const Material &_material);

    /*!
     * \brief Add visible 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *addSegment(const QVector3D &_point1,
                                             const QVector3D &_point2,
                                             const float _radius,
                                             const uint _multSpace,
                                             const uint _quality,
                                             const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, _multSpace, _quality, true, _material);
    }

    /*!
     * \brief Add visible 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *addSegment(const QVector3D &_point1,
                                             const QVector3D &_point2,
                                             const float _radius,
                                             const uint _multSpace,
                                             const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, _multSpace, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add visible 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *
    addSegment(const QVector3D &_point1, const QVector3D &_point2, const float _radius, const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, Config::cfg().lineMultSpace, _material);
    }

    /*!
     * \brief Add visible 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *
    addSegment(const QVector3D &_point1, const QVector3D &_point2, const Material &_material)
    {
        return addSegment(_point1, _point2, Config::cfg().lineRadius, _material);
    }

    //

    /*!
     * \brief Add hidden 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _quality Initial line circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *addSegmentHidden(const QVector3D &_point1,
                                                   const QVector3D &_point2,
                                                   const float _radius,
                                                   const uint _multSpace,
                                                   const uint _quality,
                                                   const Material &_material)
    {
        return addSegment(_point1, _point2, _radius, _multSpace, _quality, false, _material);
    }

    /*!
     * \brief Add hidden 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _multSpace Initial space between doth length multiplier
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *addSegmentHidden(const QVector3D &_point1,
                                                   const QVector3D &_point2,
                                                   const float _radius,
                                                   const uint _multSpace,
                                                   const Material &_material)
    {
        return addSegmentHidden(_point1, _point2, _radius, _multSpace, Config::cfg().qualityLine, _material);
    }

    /*!
     * \brief Add hidden 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _radius Initial line radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *
    addSegmentHidden(const QVector3D &_point1, const QVector3D &_point2, const float _radius, const Material &_material)
    {
        return addSegmentHidden(_point1, _point2, _radius, Config::cfg().lineMultSpace, _material);
    }

    /*!
     * \brief Add hidden 3D dot line segment item
     * \param _point1 Initial first point
     * \param _point2 Initial second point
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DLineDotsSegment *
    addSegmentHidden(const QVector3D &_point1, const QVector3D &_point2, const Material &_material)
    {
        return addSegmentHidden(_point1, _point2, Config::cfg().lineRadius, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINEDOTS_H
