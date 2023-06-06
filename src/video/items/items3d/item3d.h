#ifndef UNIVERSE1_VIDEO_ITEM3D_H
#define UNIVERSE1_VIDEO_ITEM3D_H

#include "../items2d/item2d.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Item base structure */
struct Item3D : public Item
{
 protected:
    std::list<DynamicMaterialGroup *> materials;  //!< All materials

 public:
    static const QVector3D nx;  //!< Unit vector in \b X direction
    static const QVector3D ny;  //!< Unit vector in \b Y direction
    static const QVector3D nz;  //!< Unit vector in \b Z direction

    DynamicBool visible;  //!< Visible flag

 protected:
    /*!
     * \brief Constructor
     * \param _visible Visible flag
     * \param _name Item name
     */
    Item3D(const bool _visible, const std::string &_name);

 public:
    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     * \return
     */
    virtual void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const = 0;

    /*!
     * \brief Add hiding process, lowering alpha and shine, at ending time visible goes off and material is restored
     * \param _startHidingTime Start hiding time-step in ms
     * \param _endHidingTime End hiding time-step in ms
     */
    void addHide(const uint64_t _startHidingTime, const uint64_t _endHidingTime);

    /*!
     * \brief Add showing process, growing alpha and shine, visible goes on at start time and material is growing
     * \param _startShowingTime Start showing time-step in ms
     * \param _endShowingTime End showing time-step in ms
     */
    void addShow(const uint64_t _startShowingTime, const uint64_t _endShowingTime);

    /*!
     * \brief Create perpendicular normal to input normal
     * \param _normal Input normal
     * \return Perpendicular normal
     */
    static inline QVector3D perpendicularNormal(const QVector3D &_normal)
    {
        if (qFuzzyCompare(std::abs(_normal.x()), 1.0f))
            return QVector3D::crossProduct(_normal, QVector3D(0, 1, 0)).normalized();
        return QVector3D::crossProduct(_normal, QVector3D(1, 0, 0)).normalized();
    }

    /*!
     * \brief Repair arm to be perpendicular to normal
     * \param _arm Base arm direction
     * \param _normal Input normal
     * \return Repaired arm to be perpendicular to normal
     */
    static inline QVector3D perpendicularArm(const QVector3D &_arm, const QVector3D &_normal)
    {
        return QVector3D::crossProduct(QVector3D::crossProduct(_normal, _arm).normalized(), _normal).normalized();
    }

    /*!
     * \brief Returns circle point count base on quality index
     * \param _quality Quality index
     * \return Circle point count base on quality index
     */
    static inline uint circlePointCount(const uint _quality)
    {
        return std::min(2048U, (_quality + 1U) * 4U);
    }

    /*!
     * \brief Returns latitude-longitude lines count within sphere base on quality index
     * \param _quality Quality index
     * \return Latitude-longitude lines count base on quality index
     */
    static inline std::pair<uint, uint> loLaPointCount(const uint _quality)
    {
        return {(_quality + 1U) * 4U, _quality * 2U + 1U};
    }

    /*!
     * \brief Returns sphere vertex and indices count base on quality index
     * \param _quality Quality index
     * \return Sphere vertex and indices count base on quality index
     */
    static inline std::pair<uint, uint> spherePointCount(const uint _quality)
    {
        const std::pair<uint, uint> lola = loLaPointCount(_quality);
        return {lola.first * lola.second + 2UL, lola.first * lola.second * 6UL};
    }

    /*!
     * \brief Convert 3D vector to text
     * \param _vec 3D vector
     * \return 3D vector as text
     */
    static inline QString vecText(const QVector3D &_vec)
    {
        return QString("[%1 × %2 × %3]").arg(_vec.x(), 0, 'f', 0).arg(_vec.y(), 0, 'f', 0).arg(_vec.z(), 0, 'f', 0);
    }
};

/*! \brief Single material base 3D Item structure */
struct Item3DBase : public Item3D
{
 public:
    DynamicMaterialGroup material;  //!< Material property

    /*!
     * \brief Constructor
     * \param _visible Visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DBase(const bool _visible, const Material &_material, const std::string &_name);
};

/*!
 * \brief Footage 3D item database base structure
 */
struct DBItems3D
{
    const std::string propertyName;  //!< Object database name
    const std::string &footageName;  //!< Footage name

    std::list<Item3D *> *items;  //!< Pointer to all 3D items collection

    uint count = 0U;  //!< Count of this 3D object type within 3D items database

    /*!
     * \brief Constructor
     * \param _propertyName Object database name
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItems3D(const std::string &_propertyName,
              const std::string &_footageName,
              std::list<Item3D *> *_items);

    virtual ~DBItems3D() = default;  //!< Destructor

    /*!
     * \brief Create next object name
     * \return Next object name
     */
    virtual std::string nextName();
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3D_H
