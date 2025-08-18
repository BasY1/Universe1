/*!
 * \file src/Items/BodyParts/Hand/itemhand.h
 * \brief Dynamic hand video item
 */

#ifndef ITEMS_ITEMHAND_H
#define ITEMS_ITEMHAND_H

#include "../../item3d.h"

#include "../../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Props {

/*! \brief Data group for hand items */
class ItemGroupHand : public ItemPropertyGroup
{
 public:
    /*! \brief Hand data */
    struct Data
    {
        Math::OrientF orientation = {};                     //!< Hand orientation in the 3D space
        bool rightHand = true;                              //!< Right/left hand flag
        float size = 1.0f;                                  //!< Hand size
        float openFingerThumb = 1.0f;                       //!< Ratio open thumb finger (0 to 1)
        float openFingerIndex = 1.0f;                       //!< Ratio open index finger (0 to 1)
        float openFingerMiddle = 1.0f;                      //!< Ratio open middle fingers (0 to 1)
        float openFingerRing = 1.0f;                        //!< Ratio open fourth fingers (0 to 1)
        float openFingerLittle = 1.0f;                      //!< Ratio open fifth fingers (0 to 1)
        size_t quality = 15;                                //!< Hand circles quality
        Math::MaterialRGB materialBody = {Qt::white};       //!< Major hand material
        Math::MaterialRGB materialKnuckle = {Qt::darkRed};  //!< Material for knuckles and nails
    };

    Props::ItemPropertyBool rightHand;               //!< Right/left hand flag
    Props::ItemPropertyFloat size;                   //!< Hand size
    Props::ItemPropertyFloat openFingerThumb;        //!< Ratio open thumb finger (0 to 1)
    Props::ItemPropertyFloat openFingerIndex;        //!< Ratio open index finger (0 to 1)
    Props::ItemPropertyFloat openFingerMiddle;       //!< Ratio open middle fingers (0 to 1)
    Props::ItemPropertyFloat openFingerRing;         //!< Ratio open fourth fingers (0 to 1)
    Props::ItemPropertyFloat openFingerLittle;       //!< Ratio open fifth fingers (0 to 1)
    Props::ItemPropertyQuality quality;              //!< Hand circles quality
    Props::ItemPropertyMaterialRGB materialBody;     //!< Major hand material
    Props::ItemPropertyMaterialRGB materialKnuckle;  //!< Material for knuckles and nails

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _data Initial eye ball data
     */
    inline ItemGroupHand(const std::string &_name, const Data &_data)
        : ItemPropertyGroup(_name)
        , rightHand(_name + ".rightHand", _data.rightHand)
        , size(_name + ".size", _data.size, 0.0f, std::numeric_limits<float>::max())
        , openFingerThumb(_name + ".openFingerThumb", _data.openFingerThumb, 0.0f, 1.0f)
        , openFingerIndex(_name + ".openFingerIndex", _data.openFingerIndex, 0.0f, 1.0f)
        , openFingerMiddle(_name + ".openFingerMiddle", _data.openFingerMiddle, 0.0f, 1.0f)
        , openFingerRing(_name + ".openFingerRing", _data.openFingerRing, 0.0f, 1.0f)
        , openFingerLittle(_name + ".openFingerLittle", _data.openFingerLittle, 0.0f, 1.0f)
        , quality(_name + ".quality", _data.quality)
        , materialBody(_name + ".materialBody", _data.materialBody)
        , materialKnuckle(_name + ".materialKnuckle", _data.materialKnuckle)
    {
        setupProperties({&rightHand,
                         &size,
                         &openFingerThumb,
                         &openFingerIndex,
                         &openFingerMiddle,
                         &openFingerRing,
                         &openFingerLittle,
                         &quality,
                         &materialBody,
                         &materialKnuckle});
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _rightHand Initial right/left hand flag
     * \param _size Initial hand size
     * \param _openFingerThumb Initial open thumb finger ratio (0 to 1)
     * \param _openFingerIndex Initial open index finger ratio (0 to 1)
     * \param _openFingerMiddle Initial open middle finger ratio (0 to 1)
     * \param _openFingerRing Initial open ring finger ratio (0 to 1)
     * \param _openFingerLittle Initial open little finger ratio (0 to 1)
     * \param _quality Initial hand circles quality
     * \param _materialBody Initial major hand material
     * \param _materialKnuckle Initial material for knuckles and nails
     */
    inline ItemGroupHand(const std::string &_name,
                         const bool _rightHand = true,
                         const float _size = 1.0F,
                         const float _openFingerThumb = 1.0F,
                         const float _openFingerIndex = 1.0F,
                         const float _openFingerMiddle = 1.0F,
                         const float _openFingerRing = 1.0F,
                         const float _openFingerLittle = 1.0F,
                         const size_t _quality = Items::ItemDefaultValues::sphereQuality,
                         const Math::MaterialRGB &_materialBody = {Qt::white},
                         const Math::MaterialRGB &_materialKnuckle = {Qt::red})
        : ItemPropertyGroup(_name)
        , rightHand(_name + ".rightHand", _rightHand)
        , size(_name + ".size", _size, 0.0f, std::numeric_limits<float>::max())
        , openFingerThumb(_name + ".openFingerThumb", _openFingerThumb, 0.0f, 1.0f)
        , openFingerIndex(_name + ".openFingerIndex", _openFingerIndex, 0.0f, 1.0f)
        , openFingerMiddle(_name + ".openFingerMiddle", _openFingerMiddle, 0.0f, 1.0f)
        , openFingerRing(_name + ".openFingerRing", _openFingerRing, 0.0f, 1.0f)
        , openFingerLittle(_name + ".openFingerLittle", _openFingerLittle, 0.0f, 1.0f)
        , quality(_name + ".quality", _quality)
        , materialBody(_name + ".materialBody", _materialBody)
        , materialKnuckle(_name + ".materialKnuckle", _materialKnuckle)
    {
        setupProperties({&rightHand,
                         &size,
                         &openFingerThumb,
                         &openFingerIndex,
                         &openFingerMiddle,
                         &openFingerRing,
                         &openFingerLittle,
                         &quality,
                         &materialBody,
                         &materialKnuckle});
    }

    /*!
     * \brief Getter for eye data values at specific time step
     * \param _timeStep Time step
     * \param _orientation Initial (Current) eye ball position and orientation in space
     * \return Eye ball data
     */
    inline Data value(const size_t _timeStep, const Math::OrientF &_orientation = {}) const
    {
        Data out;
        out.orientation = _orientation;
        out.rightHand = rightHand.value(_timeStep);
        out.size = size.value(_timeStep);
        out.openFingerThumb = openFingerThumb.value(_timeStep);
        out.openFingerIndex = openFingerIndex.value(_timeStep);
        out.openFingerMiddle = openFingerMiddle.value(_timeStep);
        out.openFingerRing = openFingerRing.value(_timeStep);
        out.openFingerLittle = openFingerLittle.value(_timeStep);
        out.quality = quality.value(_timeStep);
        out.materialBody = materialBody.value(_timeStep);
        out.materialKnuckle = materialKnuckle.value(_timeStep);
        return out;
    }
};

}  // namespace Props

namespace Items {
/*! \brief Dynamic hand video item */
class ItemHand : public Item3DExt
{
 public:
    Props::ItemGroupHand hand;  //!< Hand properties

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial hand central position
     * \param _normal Initial major hand axis
     * \param _arm Initial secondary hand axis
     * \param _rightHand Initial right/left hand flag
     * \param _size Initial hand size
     * \param _openFingerThumb Initial open thumb finger ratio (0 to 1)
     * \param _openFingerIndex Initial open index finger ratio (0 to 1)
     * \param _openFingerMiddle Initial open middle finger ratio (0 to 1)
     * \param _openFingerRing Initial open ring finger ratio (0 to 1)
     * \param _openFingerLittle Initial open little finger ratio (0 to 1)
     * \param _quality Initial hand circles quality
     * \param _materialBody Initial major hand material
     * \param _materialKnuckle Initial material for knuckles and nails
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    inline ItemHand(const std::string &_name = "Hand",
                    const Math::Vec3F &_center = {},
                    const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                    const Math::Vec3F &_arm = Math::Vec3F::unitZ(),
                    const bool _rightHand = true,
                    const float _size = 1.0F,
                    const float _openFingerThumb = 1.0F,
                    const float _openFingerIndex = 1.0F,
                    const float _openFingerMiddle = 1.0F,
                    const float _openFingerRing = 1.0F,
                    const float _openFingerLittle = 1.0F,
                    const size_t _quality = ItemDefaultValues::sphereQuality,
                    const Math::MaterialRGB &_materialBody = {Qt::white},
                    const Math::MaterialRGB &_materialKnuckle = {Qt::red},
                    const uint8_t _alpha = 255U,
                    const bool _visible = true)
        : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
        , hand(_name + ".hand",
               _rightHand,
               _size,
               _openFingerThumb,
               _openFingerIndex,
               _openFingerMiddle,
               _openFingerRing,
               _openFingerLittle,
               _quality,
               _materialBody,
               _materialKnuckle)
    {
        addProperty(&hand);
    }

    /*!
     * \brief Constructor
     * \param _data Initial hand data
     * \param _name Item name
     * \param _center Initial hand central position
     * \param _normal Initial major hand axis
     * \param _arm Initial secondary hand axis
     * \param _alpha Initial alpha
     * \param _visible Initial visible flag
     */
    inline ItemHand(const Props::ItemGroupHand::Data &_data,
                    const std::string &_name = "Hand",
                    const Math::Vec3F &_center = {},
                    const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                    const Math::Vec3F &_arm = Math::Vec3F::unitZ(),
                    const uint8_t _alpha = 255U,
                    const bool _visible = true)
        : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
        , hand(_name + ".hand", _data)
    {
        addProperty(&hand);
    }

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;

 public:
    /*!
     * \brief Create Hand 3D data
     * \param _out Output data objects
     * \param _orientation Orientation
     * \param _rightHand Right/left hand flag
     * \param _size Hand size
     * \param _openFingerThumb Open thumb finger ratio (0 to 1)
     * \param _openFingerIndex Open index finger ratio (0 to 1)
     * \param _openFingerMiddle Open middle finger ratio (0 to 1)
     * \param _openFingerRing Open ring finger ratio (0 to 1)
     * \param _openFingerLittle Open little finger ratio (0 to 1)
     * \param _quality Hand circles quality
     * \param _materialBody Major hand material
     * \param _materialKnuckle Material for knuckles and nails
     * \param _alpha Alpha
     * \return
     */
    static void createHand(std::list<OpenGL::Data3D *> &_out,
                           const Math::OrientF &_orientation,
                           const bool _rightHand,
                           const float _size,
                           const float _openFingerThumb,
                           const float _openFingerIndex,
                           const float _openFingerMiddle,
                           const float _openFingerRing,
                           const float _openFingerLittle,
                           const size_t _quality,
                           const Math::MaterialRGB &_materialBody,
                           const Math::MaterialRGB &_materialKnuckle,
                           const uint8_t _alpha);

    /*!
     * \brief Create Hand 3D data
     * \param _out Output data objects
     * \param _hand Hand properties
     * \param _alpha Alpha
     * \return
     */
    inline static void
    createHand(std::list<OpenGL::Data3D *> &_out, const Props::ItemGroupHand::Data &_hand, const uint8_t _alpha)
    {
        createHand(_out,
                   _hand.orientation,
                   _hand.rightHand,
                   _hand.size,
                   _hand.openFingerThumb,
                   _hand.openFingerIndex,
                   _hand.openFingerMiddle,
                   _hand.openFingerRing,
                   _hand.openFingerLittle,
                   _hand.quality,
                   _hand.materialBody,
                   _hand.materialKnuckle,
                   _alpha);
    }
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMHAND_H
