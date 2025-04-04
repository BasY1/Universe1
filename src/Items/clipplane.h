/*!
 * \file src/Items/clipplane.h
 * \brief Dynamic clipping plane tools
 */

#ifndef ITEMS_CLIPPLANE_H
#define ITEMS_CLIPPLANE_H

#include "../ItemProps/itempropertygroup.h"
#include "../ItemProps/itempropertybool.h"
#include "../ItemProps/itempropertyvec3.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic clipping plane */
class ClipPlane : public Props::ItemPropertyGroup
{
 public:
    Props::ItemPropertyBool enabled;  //!< Dynamic enabled flag
    Props::ItemPropertyVec3F center;  //!< Plane central point
    Props::ItemPropertyVec3F normal;  //!< Plane normal

    /*!
     * \brief Constructor
     * \param _name Clipping plane name
     * \param _center Plane central point
     * \param _normal Plane normal
     * \param _enabled Clipping plane enabled flag
     */
    inline ClipPlane(const std::string &_name,
                     const Math::Vec3F &_center,
                     const Math::Vec3F &_normal,
                     const bool _enabled = true)
        : Props::ItemPropertyGroup(_name)
        , enabled("enabled", _enabled)
        , center("center", _center)
        , normal("normal", _normal)
    {
        setupProperties({&enabled, &center, &normal});
    }

    /*!
     * \brief Constructor with default object name
     * \param _center Plane central point
     * \param _normal Plane normal
     * \param _enabled Clipping plane enabled flag
     */
    inline ClipPlane(const Math::Vec3F &_center, const Math::Vec3F &_normal, const bool _enabled = true)
        : ClipPlane("Clip plane", _center, _normal, _enabled)
    {
    }

    /*!
     * \brief Standard components of plane equation \f$A \times x + B \times y + C \times z + D = 0\f$
     * \param _timeStep Time-step
     * \return Plane equation at given time-step
     */
    inline QVector4D equation(const size_t _timeStep) const
    {
        const Math::Vec3F c = center.value(_timeStep);
        const Math::Vec3F n = normal.value(_timeStep);
        return QVector4D(n.x, n.y, n.z, Math::Vec3F().distanceToPlane(c, n));
    }
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_CLIPPLANE_H
