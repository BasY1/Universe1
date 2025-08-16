/*!
 * \file src/Items/Clock/itemclock.h
 * \brief Dynamic clock video item
 */

#ifndef ITEMS_ITEMCLOCK_H
#define ITEMS_ITEMCLOCK_H

#include "../item3d.h"

#include "../../ItemProps/itempropertytext.h"
#include "../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Items {

/*! \brief Dynamic clock video item */
class ItemClock : public Item3DExt
{
 public:
    Props::ItemPropertyFloat time;  //!< Clock time

    Props::ItemPropertyFloat radius;     //!< Clock radius
    Props::ItemPropertyQuality quality;  //!< Clock circle quality

    Props::ItemPropertyBool bodyFollowCamera;  //!< Clock body camera mode
    Props::ItemPropertyBool textFollowCamera;  //!< Clock text camera mode

    Props::ItemPropertyText text;            //!< Attached text
    Props::ItemPropertyText fontFamily;      //!< Text font name
    Props::ItemPropertyUInt32 fontHeight;    //!< Font height
    Props::ItemPropertyUInt32 borderOffset;  //!< Border offset distance
    Props::ItemPropertyFloat pixelSize;      //!< Pixel size
    Props::ItemPropertyColor textColor;      //!< Text color

    Props::ItemPropertyMaterialRGB materialBody;   //!< Clock body material
    Props::ItemPropertyMaterialRGB materialPlane;  //!< Clock plane material
    Props::ItemPropertyMaterialRGB materialTick;   //!< Clock number material
    Props::ItemPropertyMaterialRGB materialSec;    //!< Second hand material
    Props::ItemPropertyMaterialRGB materialMin;    //!< Minute hand material
    Props::ItemPropertyMaterialRGB materialHour;   //!< Hour hand material

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major clock plane normal
     * \param _upDir Initial secondary normal - clock up direction
     * \param _time Initial clock time
     * \param _radius Initial clock radius
     * \param _quality Initial clock circle quality
     * \param _bodyFollowCamera Initial value for clock body camera mode
     * \param _textFollowCamera Initial value for clock text camera mode
     * \param _text Initial text
     * \param _fontFamily Initial text font name
     * \param _fontHeight Initial font height
     * \param _borderOffset Initial border offset distance
     * \param _pixelSize Initial pixel size
     * \param _textColor Initial text color
     * \param _materialBody Initial clock body material
     * \param _materialPlane Initial clock plane material
     * \param _materialTick Initial clock number material
     * \param _materialSec Initial second hand material
     * \param _materialMin Initial minute hand material
     * \param _materialHour Initial hour hand material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemClock(const std::string &_name = "Clock",
              const Math::Vec3F &_center = {},
              const Math::Vec3F &_normal = Math::Vec3F::unitX(),
              const Math::Vec3F &_upDir = Math::Vec3F::unitZ(),
              const float _time = 0.0f,
              const float _radius = 0.5f,
              const size_t _quality = ItemDefaultValues::sphereQuality,
              const bool _bodyFollowCamera = false,
              const bool _textFollowCamera = true,
              const QString &_text = "$$$TIME$$$",
              const QString &_fontFamily = ItemDefaultValues::textFont,
              const uint32_t _fontHeight = ItemDefaultValues::fontHeight,
              const uint32_t _borderOffset = 0U,
              const float _pixelSize = ItemDefaultValues::textPixelSize,
              const Math::ColorRGB &_textColor = {Qt::white},
              const Math::MaterialRGB &_materialBody = {Qt::yellow},
              const Math::MaterialRGB &_materialPlane = {Qt::white},
              const Math::MaterialRGB &_materialTick = {Qt::black},
              const Math::MaterialRGB &_materialSec = {Qt::black},
              const Math::MaterialRGB &_materialMin = {Qt::black},
              const Math::MaterialRGB &_materialHour = {Qt::black},
              const uint8_t _alpha = 255U,
              const bool _visible = true);

 protected:
    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const override;

    /*!
     * \brief Create 3D Open GL data objects
     * \param _data Output data objects
     * \param _camera Camera data
     * \param _timeStep Time-step
     */
    void createDataImpl(std::list<OpenGL::Data3D *> &_data,
                        const Math::CamF &_camera,
                        const size_t _timeStep) const override;

 public:
    /*!
     * \brief Replace text values
     * \param _txt Text
     * \param _time Time
     * \return
     * \details Uses tags: $$$CLOCK$$$, $$$TIME$$$, $$$TIME$0$, $$$TIME$1$, ..., $$$TIME$6$
     */
    static void replaceText(QString &_txt, const float _time);

    /*!
     * \brief Create clock body Open GL data objects
     * \param _data Output data objects
     * \param _orientation Clock orientation
     * \param _time Time
     * \param _radius Clock radius
     * \param _quality Clock circle quality
     * \param _materialBody Clock body material
     * \param _materialPlane Clock plane material
     * \param _materialTick Clock number material
     * \param _materialSec Second hand material
     * \param _materialMin Minute hand material
     * \param _materialHour Hour hand material
     * \param _alpha Alpha
     * \return
     */
    static void createClockBody(std::list<OpenGL::Data3D *> &_data,
                                const Math::OrientF &_orientation,
                                const float _time,
                                const float _radius,
                                const size_t _quality,
                                const Math::MaterialRGB &_materialBody,
                                const Math::MaterialRGB &_materialPlane,
                                const Math::MaterialRGB &_materialTick,
                                const Math::MaterialRGB &_materialSec,
                                const Math::MaterialRGB &_materialMin,
                                const Math::MaterialRGB &_materialHour,
                                const uint8_t _alpha);
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMCLOCK_H
