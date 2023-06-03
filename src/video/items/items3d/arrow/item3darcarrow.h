#ifndef UNIVERSE1_VIDEO_ITEM3DARCARROW_H
#define UNIVERSE1_VIDEO_ITEM3DARCARROW_H

#include "item3dlinearrow.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D single arrow over circle item */
struct Item3DArcArrow : public Item3DBase
{
    DynamicVec3 center;               //!< Main circle center point
    DynamicVec3 normal;               //!< Main circle normal
    DynamicVec3 arm;                  //!< Main circle arm direction (to arrow bottom)
    DynamicValue<float> armRadius;    //!< Arm radius (circle center to arrow bottom)
    DynamicValue<float> arrowLength;  //!< Arrow length
    DynamicValue<float> arrowRadius;  //!< Arrow radius
    DynamicValue<uint> quality;       //!< Arrow circle quality

    /*!
     * \brief Constructor
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DArcArrow(const QVector3D &_center,
                   const QVector3D &_normal,
                   const QVector3D &_arm,
                   const float _armRadius,
                   const float _arrowLength,
                   const float _arrowRadius,
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
     * \param _center Main circle center point
     * \param _normal Main circle normal
     * \param _arm Main circle arm direction
     * \param _armRadius Arm radius (circle center
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow radius
     * \param _quality Arrow circle quality
     * \param _material Material
     * \param _materialCircle Material arrow bottom
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _armRadius,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const uint _quality,
                          const Material &_material,
                          const Material &_materialCircle);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _center Main circle center point
     * \param _normal Main circle normal
     * \param _arm Main circle arm direction
     * \param _armRadius Arm radius (circle center
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow radius
     * \param _quality Arrow circle quality
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const QVector3D &_arm,
                                 const float _armRadius,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const uint _quality,
                                 const Material &_material)
    {
        buildData(_out,
                  _center,
                  _normal,
                  _arm,
                  _armRadius,
                  _arrowLength,
                  _arrowRadius,
                  _quality,
                  _material,
                  _material.darker());
    }
};

/*! \brief 3D arrow group over circle item */
struct Item3DArcArrows : public Item3DArcArrow
{
    DynamicValue<uint> arrowCount;  //!< Arrow count

    /*!
     * \brief Constructor
     * \param _arrowCount Initial arrow count
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DArcArrows(const uint _arrowCount,
                    const QVector3D &_center,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const float _armRadius,
                    const float _arrowLength,
                    const float _arrowRadius,
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
     * \param _arrowCount Arrow count
     * \param _center Main circle center point
     * \param _normal Main circle normal
     * \param _arm Main circle arm direction
     * \param _armRadius Arm radius (circle center
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow radius
     * \param _quality Arrow circle quality
     * \param _material Material
     * \param _materialCircle Material arrow bottom
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const uint _arrowCount,
                          const QVector3D &_center,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _armRadius,
                          const float _arrowLength,
                          const float _arrowRadius,
                          const uint _quality,
                          const Material &_material,
                          const Material &_materialCircle);

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _arrowCount Arrow count
     * \param _center Main circle center point
     * \param _normal Main circle normal
     * \param _arm Main circle arm direction
     * \param _armRadius Arm radius (circle center
     * \param _arrowLength Arrow length
     * \param _arrowRadius Arrow radius
     * \param _quality Arrow circle quality
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const uint _arrowCount,
                                 const QVector3D &_center,
                                 const QVector3D &_normal,
                                 const QVector3D &_arm,
                                 const float _armRadius,
                                 const float _arrowLength,
                                 const float _arrowRadius,
                                 const uint _quality,
                                 const Material &_material)
    {
        buildData(_out,
                  _arrowCount,
                  _center,
                  _normal,
                  _arm,
                  _armRadius,
                  _arrowLength,
                  _arrowRadius,
                  _quality,
                  _material,
                  _material.darker());
    }
};

/*! \brief Footage 3D arrow over circle database */
struct DBItem3DArcArrow : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DArcArrow(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D arc arrow item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DArcArrow *add(const QVector3D &_center,
                        const QVector3D &_normal,
                        const QVector3D &_arm,
                        const float _armRadius,
                        const float _arrowLength,
                        const float _arrowRadius,
                        const uint _quality,
                        const bool _visible,
                        const Material &_material);

    /*!
     * \brief Add visible 3D arc arrow item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrow *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _armRadius,
                               const float _arrowLength,
                               const float _arrowRadius,
                               const uint _quality,
                               const Material &_material)
    {
        return add(_center, _normal, _arm, _armRadius, _arrowLength, _arrowRadius, _quality, true, _material);
    }

    /*!
     * \brief Add visible 3D arc arrow item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrow *add(const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _armRadius,
                               const Material &_material)
    {
        const Config &c = Config::cfg();
        return add(_center, _normal, _arm, _armRadius, c.arrowLength, c.arrowRadius, c.qualityLine, _material);
    }

    //

    /*!
     * \brief Add hidden 3D arc arrow item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrow *addHidden(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const QVector3D &_arm,
                                     const float _armRadius,
                                     const float _arrowLength,
                                     const float _arrowRadius,
                                     const uint _quality,
                                     const Material &_material)
    {
        return add(_center, _normal, _arm, _armRadius, _arrowLength, _arrowRadius, _quality, false, _material);
    }

    /*!
     * \brief Add hidden 3D arc arrow item
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrow *addHidden(const QVector3D &_center,
                                     const QVector3D &_normal,
                                     const QVector3D &_arm,
                                     const float _armRadius,
                                     const Material &_material)
    {
        const Config &c = Config::cfg();
        return addHidden(_center, _normal, _arm, _armRadius, c.arrowLength, c.arrowRadius, c.qualityLine, _material);
    }

    //
    //
    //

    /*!
     * \brief Add 3D arc arrows item
     * \param _arrowCount Initial arrow count
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DArcArrows *addArrows(const uint _arrowCount,
                               const QVector3D &_center,
                               const QVector3D &_normal,
                               const QVector3D &_arm,
                               const float _armRadius,
                               const float _arrowLength,
                               const float _arrowRadius,
                               const uint _quality,
                               const bool _visible,
                               const Material &_material);

    /*!
     * \brief Add visible 3D arc arrows item
     * \param _arrowCount Initial arrow count
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrows *addArrows(const uint _arrowCount,
                                      const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _armRadius,
                                      const float _arrowLength,
                                      const float _arrowRadius,
                                      const uint _quality,
                                      const Material &_material)
    {
        return addArrows(
            _arrowCount, _center, _normal, _arm, _armRadius, _arrowLength, _arrowRadius, _quality, true, _material);
    }

    /*!
     * \brief Add visible 3D arc arrows item
     * \param _arrowCount Initial arrow count
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrows *addArrows(const uint _arrowCount,
                                      const QVector3D &_center,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _armRadius,
                                      const Material &_material)
    {
        const Config &c = Config::cfg();
        return addArrows(
            _arrowCount, _center, _normal, _arm, _armRadius, c.arrowLength, c.arrowRadius, c.qualityLine, _material);
    }

    //

    /*!
     * \brief Add hidden 3D arc arrows item
     * \param _arrowCount Initial arrow count
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _arrowLength Initial arrow length
     * \param _arrowRadius Initial arrow radius
     * \param _quality Initial arrow circle quality
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrows *addArrowsHidden(const uint _arrowCount,
                                            const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const QVector3D &_arm,
                                            const float _armRadius,
                                            const float _arrowLength,
                                            const float _arrowRadius,
                                            const uint _quality,
                                            const Material &_material)
    {
        return addArrows(
            _arrowCount, _center, _normal, _arm, _armRadius, _arrowLength, _arrowRadius, _quality, false, _material);
    }

    /*!
     * \brief Add hidden 3D arc arrows item
     * \param _arrowCount Initial arrow count
     * \param _center Initial main circle center point
     * \param _normal Initial main circle normal
     * \param _arm Initial main circle arm direction
     * \param _armRadius Initial arm radius
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DArcArrows *addArrowsHidden(const uint _arrowCount,
                                            const QVector3D &_center,
                                            const QVector3D &_normal,
                                            const QVector3D &_arm,
                                            const float _armRadius,
                                            const Material &_material)
    {
        const Config &c = Config::cfg();
        return addArrowsHidden(
            _arrowCount, _center, _normal, _arm, _armRadius, c.arrowLength, c.arrowRadius, c.qualityLine, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DARCARROW_H
