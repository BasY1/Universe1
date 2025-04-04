/*!
 * \file src/Items/item3d.h
 * \brief Basic 3D video item
 */

#ifndef ITEMS_ITEM3D_H
#define ITEMS_ITEM3D_H

#include "item.h"

#include "item.h"
#include "clipplane.h"

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
    inline Item3D(const std::string &_name, const uint8_t _initialApha = 255U, const bool _initialVisible = true)
        : Item(_name, _initialApha, _initialVisible)
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
     * \return Success flag
     */
    virtual ClipPlane *addClipPlane(const Math::Vec3F &_center,
                                    const Math::Vec3F &_normal,
                                    const bool _enabled = true,
                                    const std::string &_name = "Clip plane");

    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _cameraData Output data objects that are dependent on camera position
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
    virtual void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const = 0;

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

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEM3D_H
