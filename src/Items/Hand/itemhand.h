/*!
 * \file src/Items/Hand/itemhand.h
 * \brief Dynamic hand video item
 */

#ifndef ITEMS_ITEMHAND_H
#define ITEMS_ITEMHAND_H

#include "../item3d.h"

#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic hand video item */
class ItemHand : public Item3DExt
{
 public:
    Props::ItemPropertyBool rightHand;   //!< Right/left hand flag
    Props::ItemPropertyFloat size;       //!< Hand size
    Props::ItemPropertyFloat openThumb;  //!< Ratio open thumb finger (0 to 1)
    Props::ItemPropertyFloat openIndex;  //!< Ratio open index finger (0 to 1)
    Props::ItemPropertyFloat open345;    //!< Ratio open other fingers (0 to 1)
    Props::ItemPropertyQuality quality;  //!< Hand circles quality

    Props::ItemPropertyMaterialRGB materialBody;     //!< Major hand material
    Props::ItemPropertyMaterialRGB materialKnuckle;  //!< Material for knuckles and nails

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial hand central position
     * \param _normal Initial major hand axis
     * \param _arm Initial secondary hand axis
     * \param _rightHand Initial right/left hand flag
     * \param _size Initial hand size
     * \param _openThumb Initial open thumb finger ratio (0 to 1)
     * \param _openIndex Initial open index finger ratio (0 to 1)
     * \param _open345 2open other fingers ratio (0 to 1)
     * \param _quality Initial hand circles quality
     * \param _materialBody Initial major hand material
     * \param _materialKnuckle Initial material for knuckles and nails
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    ItemHand(const std::string &_name = "Hand",
             const Math::Vec3F &_center = {},
             const Math::Vec3F &_normal = Math::Vec3F::unitX(),
             const Math::Vec3F &_arm = Math::Vec3F::unitZ(),
             const bool _rightHand = true,
             const float _size = 1.0F,
             const float _openThumb = 1.0F,
             const float _openIndex = 1.0F,
             const float _open345 = 1.0F,
             const size_t _quality = ItemDefaultValues::sphereQuality,
             const Math::MaterialRGB &_materialBody = {Qt::white},
             const Math::MaterialRGB &_materialKnuckle = {Qt::red},
             const uint8_t _alpha = 255U,
             const bool _visible = true);

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMHAND_H
