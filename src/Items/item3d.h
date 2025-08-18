/*!
 * \file src/Items/item3d.h
 * \brief Basic 3D video item
 */

#ifndef ITEMS_ITEM3D_H
#define ITEMS_ITEM3D_H

#include "item.h"

#include "item.h"
#include "clipplane.h"

#include "../Math/orientation.h"
#include "../Math/camera.h"
#include "../Data3D/data3d.h"

namespace U1 {
namespace Items {

/*! \brief Basic 3D video item */
class Item3D : public Item
{
 protected:
    std::vector<ClipPlane *> m_clipPlanes = {};  //!< Clipping planes

    /*!
     * \brief Protected constructor
     * \param _name Item name
     * \param _alpha Initial alpha factor
     * \param _visible Initial visible flag
     */
    inline Item3D(const std::string &_name, const uint8_t _alpha = 255U, const bool _visible = true)
        : Item(_name, _alpha, _visible)
    {
    }

 public:
    /*!
     * \brief Object's clipping planes
     * \return Object's clipping planes
     */
    inline const std::vector<ClipPlane *> &clipPlanes() const
    {
        return m_clipPlanes;
    }

    /*!
     * \brief Maximum possible clipping planes
     * \return Maximum possible clipping planes
     */
    virtual size_t maxClipPlanes() const;

    /*!
     * \brief Add clip plane for this object
     * \param _center Plane central point
     * \param _normal Plane normal
     * \param _enabled Clipping plane enabled flag
     * \param _name Clipping plane name
     * \return Clip plane object
     */
    virtual ClipPlane *addClipPlane(const Math::Vec3F &_center,
                                    const Math::Vec3F &_normal,
                                    const bool _enabled = true,
                                    const std::string &_name = "Clip plane");

    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _cameraData Output data objects that are dependent on camera position
     * \param _clipPlanes Master clipping planes
     * \param _timeStep Time-step
     * \return
     */
    virtual void createData(std::list<OpenGL::Data3D *> &_data,
                            std::vector<std::pair<Math::CamF, std::list<OpenGL::Data3D *>>> &_cameraData,
                            const std::vector<QVector4D> &_clipPlanes,
                            const size_t _timeStep) const final;

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     * \return
     */
    virtual void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const;

    /*!
     * \brief Create 3D Open GL data objects that are dependent on camera position
     * \param _data Output data objects
     * \param _camera Camera data
     * \param _timeStep Time-step
     * \return
     */
    virtual void
    createDataImpl(std::list<OpenGL::Data3D *> &_data, const Math::CamF &_camera, const size_t _timeStep) const;
};

/*! \brief 3D video item with orientation */
class Item3DExt : public Item3D
{
 public:
    Props::ItemPropertyVec3F center;  //!< Central point
    Props::ItemPropertyVec3F normal;  //!< Major normal
    Props::ItemPropertyVec3F arm;     //!< Secondary normal (perpendicular to major normal)

 protected:
    /*!
     * \brief Protected constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major normal
     * \param _arm Initial secondary normal
     * \param _alpha Initial alpha factor
     * \param _visible Initial visible flag
     */
    inline Item3DExt(const std::string &_name,
                     const Math::Vec3F &_center,
                     const Math::Vec3F &_normal,
                     const Math::Vec3F &_arm,
                     const uint8_t _alpha = 255U,
                     const bool _visible = true)
        : Item3D(_name, _alpha, _visible)
        , center(_name + ".center", _center)
        , normal(_name + ".normal", true, _normal.normalized())
        , arm(_name + ".arm", true, _arm.normalized())
    {
        addProperty(&center);
        addProperty(&normal);
        addProperty(&arm);
    }

 public:
    /*!
     * \brief Orientation at given time-step
     * \param _timeStep Time-step
     * \return Orientation at given time-step
     */
    inline Math::OrientF valueOrientation(const size_t _timeStep) const
    {
        return Math::OrientF(center.value(_timeStep), normal.value(_timeStep), arm.value(_timeStep));
    }
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM3D_H
