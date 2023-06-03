#ifndef UNIVERSE1_VIDEO_ITEM3DLINETWIST_H
#define UNIVERSE1_VIDEO_ITEM3DLINETWIST_H

#include "item3dlinedash.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Line twist item */
struct Item3DLineTwist : public Item3D
{
    DynamicVec3 point;              //!< Line start point
    DynamicVec3 normal;             //!< Line normal
    DynamicVec3 arm;                //!< Starting arm direction
    DynamicValue<float> length;     //!< Line length
    DynamicValue<float> twistStep;  //!< Line twist step
    DynamicValue<float> radius;     //!< Line radius
    DynamicValue<uint> quality;     //!< Line circle quality

    std::vector<DynamicMaterialGroup> materialProps;  //!< Group of materials

    /*!
     * \brief Constructor
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _materials Initial material collection
     * \param _name Item name
     */
    Item3DLineTwist(const QVector3D &_point,
                    const QVector3D &_normal,
                    const QVector3D &_arm,
                    const float _length,
                    const float _twistStep,
                    const float _radius,
                    const uint _quality,
                    const bool _visible,
                    const std::vector<Material> &_materials,
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
     * \param _arm Starting arm direction
     * \param _length Line length
     * \param _twistStep Twist step
     * \param _radius Line radius
     * \param _quality Line circle quality
     * \param _materials Materials collection
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QVector3D &_point,
                          const QVector3D &_normal,
                          const QVector3D &_arm,
                          const float _length,
                          const float _twistStep,
                          const float _radius,
                          const uint _quality,
                          const std::vector<Material> &_materials);
};

/*! \brief Footage 3D line twist database */
struct DBItem3DLineTwist : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DLineTwist(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _visible Initial visible flag
     * \param _materials Initial material collection
     * \return Created item
     */
    Item3DLineTwist *add(const QVector3D &_point,
                         const QVector3D &_normal,
                         const QVector3D &_arm,
                         const float _length,
                         const float _twistStep,
                         const float _radius,
                         const uint _quality,
                         const bool _visible,
                         const std::vector<Material> &_materials);

    /*!
     * \brief Add visible 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _materials Initial material collection
     * \return Created item
     */
    inline Item3DLineTwist *add(const QVector3D &_point,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const float _length,
                                const float _twistStep,
                                const float _radius,
                                const uint _quality,
                                const std::vector<Material> &_materials)
    {
        return add(_point, _normal, _arm, _length, _twistStep, _radius, _quality, true, _materials);
    }

    /*!
     * \brief Add visible 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _radius Initial line radius
     * \param _materials Initial material collection
     * \return Created item
     */
    inline Item3DLineTwist *add(const QVector3D &_point,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const float _length,
                                const float _twistStep,
                                const float _radius,
                                const std::vector<Material> &_materials)
    {
        return add(_point, _normal, _arm, _length, _twistStep, _radius, Config::cfg().qualityLine, _materials);
    }

    /*!
     * \brief Add visible 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _materials Initial material collection
     * \return Created item
     */
    inline Item3DLineTwist *add(const QVector3D &_point,
                                const QVector3D &_normal,
                                const QVector3D &_arm,
                                const float _length,
                                const float _twistStep,
                                const std::vector<Material> &_materials)
    {
        return add(_point, _normal, _arm, _length, _twistStep, Config::cfg().lineRadius, _materials);
    }

    /*!
     * \brief Add hidden 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _radius Initial line radius
     * \param _quality Initial line circle quality
     * \param _materials Initial material collection
     * \return Created item
     */
    inline Item3DLineTwist *addHidden(const QVector3D &_point,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _length,
                                      const float _twistStep,
                                      const float _radius,
                                      const uint _quality,
                                      const std::vector<Material> &_materials)
    {
        return add(_point, _normal, _arm, _length, _twistStep, _radius, _quality, false, _materials);
    }

    /*!
     * \brief Add hidden 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _radius Initial line radius
     * \param _materials Initial material collection
     * \return Created item
     */
    inline Item3DLineTwist *addHidden(const QVector3D &_point,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _length,
                                      const float _twistStep,
                                      const float _radius,
                                      const std::vector<Material> &_materials)
    {
        return addHidden(_point, _normal, _arm, _length, _twistStep, _radius, Config::cfg().qualityLine, _materials);
    }

    /*!
     * \brief Add hidden 3D line twist item
     * \param _point Initial line start point
     * \param _normal Initial line normal
     * \param _arm Initial arm direction
     * \param _length Initial line length
     * \param _twistStep Initial twist step
     * \param _materials Initial material collection
     * \return Created item
     */
    inline Item3DLineTwist *addHidden(const QVector3D &_point,
                                      const QVector3D &_normal,
                                      const QVector3D &_arm,
                                      const float _length,
                                      const float _twistStep,
                                      const std::vector<Material> &_materials)
    {
        return addHidden(_point, _normal, _arm, _length, _twistStep, Config::cfg().lineRadius, _materials);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DLINETWIST_H
