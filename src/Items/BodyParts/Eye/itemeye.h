/*!
 * \file src/Items/BodyParts/Eye/itemeye.h
 * \brief Dynamic Head video item
 */

#ifndef ITEMS_ITEMEYE_H
#define ITEMS_ITEMEYE_H

#include "../../item3d.h"
#include "../../../ItemProps/itempropertymaterial.h"

namespace U1 {
namespace Props {

/*! \brief Data group for eye ball 3D items */
class ItemGroupEyeBall : public ItemPropertyGroup
{
 public:
    /*! \brief Eye ball data */
    struct Data
    {
        Math::OrientF orientation = {};  //!< Eye ball orientation in the 3D space

        float radius = 0.2f;  //!< Eye body radius

        float offsetPupil = 0.0f;  //!< Pupil rise offset ratio

        float anglePupil = Math::toRad(8.0f);  //!< Angle for pupil (in radians)
        float angleIris = Math::toRad(30.0f);  //!< Angle for iris outer scale (in radians)

        float angleLidBottom = M_PI_2;  //!< Angle for the bottom eyelid (in radians)
        float angleLidUp = M_PI_2;      //!< Angle for the top eyelid (in radians)

        float offsetLid = 0.04f;      //!< Offset ratio for eyelid body
        float offsetLidEdge = 0.04f;  //!< Offset ratio for eyelid edge

        size_t quality = 15UL;  //!< Eye ball sphere quality

        Math::MaterialRGB materialPupil = Math::MaterialRGB(Qt::black);       //!< Material for eye pupil
        Math::MaterialRGB materialIris = Math::MaterialRGB(Qt::cyan);         //!< Material for eye iris
        Math::MaterialRGB materialSclera = Math::MaterialRGB(Qt::white);      //!< Material for eye sclera
        Math::MaterialRGB materialLid = Math::MaterialRGB(Qt::gray);          //!< Material for eye lid body
        Math::MaterialRGB materialLidEdge = Math::MaterialRGB(Qt::darkGray);  //!< Material for eye lid edge
    };

    ItemPropertyFloat radius;  //!< Eye body radius

    ItemPropertyFloat offsetPupil;  //!< Pupil rise offset ratio

    ItemPropertyFloat anglePupil;  //!< Angle for pupil (in radians)
    ItemPropertyFloat angleIris;   //!< Angle for iris outer scale (in radians)

    ItemPropertyFloat angleLidUp;      //!< Angle for the top eyelid (in radians)
    ItemPropertyFloat angleLidBottom;  //!< Angle for the bottom eyelid (in radians)

    ItemPropertyFloat offsetLid;      //!< Offset ratio for eyelid body
    ItemPropertyFloat offsetLidEdge;  //!< Offset ratio for eyelid edge

    Props::ItemPropertyQuality quality;  //!< Sphere circle quality

    ItemPropertyMaterialRGB materialPupil;    //!< Material for eye pupil
    ItemPropertyMaterialRGB materialIris;     //!< Material for eye iris
    ItemPropertyMaterialRGB materialSclera;   //!< Material for eye sclera
    ItemPropertyMaterialRGB materialLid;      //!< Material for eye lid body
    ItemPropertyMaterialRGB materialLidEdge;  //!< Material for eye lid edge

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _data Initial eye ball data
     */
    inline ItemGroupEyeBall(const std::string &_name, const Data &_data)
        : ItemPropertyGroup(_name)
        , radius(_name + ".radius", _data.radius, 0.0f, std::numeric_limits<float>::max())
        , offsetPupil(_name + ".offsetPupil", _data.offsetPupil, 0.0f, 0.75f)
        , anglePupil(_name + ".anglePupil", _data.anglePupil, 0.0f, Math::toRad(45.0f))
        , angleIris(_name + ".angleIris", _data.angleIris, 0.0f, Math::toRad(90.0f))
        , angleLidUp(_name + ".angleLidUp", _data.angleLidUp, 0.0f, M_PI)
        , angleLidBottom(_name + ".angleLidBottom", _data.angleLidBottom, 0.0f, M_PI)
        , offsetLid(_name + ".offsetLid", _data.offsetLid, 0.01f, 0.1f)
        , offsetLidEdge(_name + ".offsetLidEdge", _data.offsetLidEdge, 0.01f, 0.2f)
        , quality(_name + ".quality", _data.quality)
        , materialPupil(_name + ".materialPupil", _data.materialPupil)
        , materialIris(_name + ".materialIris", _data.materialIris)
        , materialSclera(_name + ".materialSclera", _data.materialSclera)
        , materialLid(_name + ".materialLid", _data.materialLid)
        , materialLidEdge(_name + ".materialLidEdge", _data.materialLidEdge)
    {
        setupProperties({&radius,
                         &offsetPupil,
                         &anglePupil,
                         &angleIris,
                         &angleLidUp,
                         &angleLidBottom,
                         &offsetLid,
                         &offsetLidEdge,
                         &quality,
                         &materialPupil,
                         &materialIris,
                         &materialSclera,
                         &materialLid,
                         &materialLidEdge});
    }

    /*!
     * \brief Constructor
     * \param _name Item property name
     * \param _radius Initial eye body radius
     * \param _offsetPupil Initial pupil rise offset ratio
     * \param _anglePupil Initial angle for pupil (in radians)
     * \param _angleIris Initial angle for iris outer scale (in radians)
     * \param _angleLidBottom Initial angle for the top eyelid (in radians)
     * \param _angleLidUp Initial angle for the bottom eyelid (in radians)
     * \param _offsetLid Initial offset ratio for eyelid body
     * \param _offsetLidEdge Initial offset ratio for eyelid edge
     * \param _quality Initial sphere circle quality
     * \param _materialPupil Initial material for eye pupil
     * \param _materialIris Initial material for eye iris
     * \param _materialSclera Initial material for eye sclera
     * \param _materialLid Initial material for eye lid body
     * \param _materialLidEdge Initial material for eye lid edge
     */
    inline ItemGroupEyeBall(const std::string &_name,
                            const float _radius = 0.2f,
                            const float _offsetPupil = 0.0f,
                            const float _anglePupil = Math::toRad(8.0f),
                            const float _angleIris = Math::toRad(30.0f),
                            const float _angleLidBottom = M_PI_2,
                            const float _angleLidUp = M_PI_2,
                            const float _offsetLid = 0.04f,
                            const float _offsetLidEdge = 0.04f,
                            const size_t _quality = Items::ItemDefaultValues::sphereQuality,
                            const Math::MaterialRGB &_materialPupil = Math::MaterialRGB(Qt::black),
                            const Math::MaterialRGB &_materialIris = Math::MaterialRGB(Qt::cyan),
                            const Math::MaterialRGB &_materialSclera = Math::MaterialRGB(Qt::white),
                            const Math::MaterialRGB &_materialLid = Math::MaterialRGB(Qt::gray),
                            const Math::MaterialRGB &_materialLidEdge = Math::MaterialRGB(Qt::darkGray))
        : ItemPropertyGroup(_name)
        , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
        , offsetPupil(_name + ".offsetPupil", _offsetPupil, 0.0f, 0.75f)
        , anglePupil(_name + ".anglePupil", _anglePupil, 0.0f, Math::toRad(45.0f))
        , angleIris(_name + ".angleIris", _angleIris, 0.0f, Math::toRad(90.0f))
        , angleLidUp(_name + ".angleLidUp", _angleLidUp, 0.0f, M_PI)
        , angleLidBottom(_name + ".angleLidBottom", _angleLidBottom, 0.0f, M_PI)
        , offsetLid(_name + ".offsetLid", _offsetLid, 0.01f, 0.1f)
        , offsetLidEdge(_name + ".offsetLidEdge", _offsetLidEdge, 0.01f, 0.2f)
        , quality(_name + ".quality", _quality)
        , materialPupil(_name + ".materialPupil", _materialPupil)
        , materialIris(_name + ".materialIris", _materialIris)
        , materialSclera(_name + ".materialSclera", _materialSclera)
        , materialLid(_name + ".materialLid", _materialLid)
        , materialLidEdge(_name + ".materialLidEdge", _materialLidEdge)
    {
        setupProperties({&radius,
                         &offsetPupil,
                         &anglePupil,
                         &angleIris,
                         &angleLidUp,
                         &angleLidBottom,
                         &offsetLid,
                         &offsetLidEdge,
                         &quality,
                         &materialPupil,
                         &materialIris,
                         &materialSclera,
                         &materialLid,
                         &materialLidEdge});
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
        out.quality = quality.value(_timeStep);
        out.radius = radius.value(_timeStep);
        out.offsetPupil = offsetPupil.value(_timeStep);
        out.anglePupil = anglePupil.value(_timeStep);
        out.angleIris = angleIris.value(_timeStep);
        out.angleLidBottom = angleLidBottom.value(_timeStep);
        out.angleLidUp = angleLidUp.value(_timeStep);
        out.offsetLid = offsetLid.value(_timeStep);
        out.offsetLidEdge = offsetLidEdge.value(_timeStep);
        out.materialPupil = materialPupil.value(_timeStep);
        out.materialIris = materialIris.value(_timeStep);
        out.materialSclera = materialSclera.value(_timeStep);
        out.materialLid = materialLid.value(_timeStep);
        out.materialLidEdge = materialLidEdge.value(_timeStep);
        return out;
    }
};

}  // namespace Props

namespace Items {

/*!
 * \brief Dynamic Eye video item
 * \note Property \a normal is look direction
 * \note Property \a arm is up vector
 */
class ItemEye : public Item3DExt
{
 public:
    Props::ItemGroupEyeBall eyeBall;  //!< Eye body data

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial eye normal - look direction
     * \param _upDir Initial secondary normal - eye up direction
     * \param _radius Initial eye body radius
     * \param _offsetPupil Initial pupil rise offset ratio
     * \param _anglePupil Initial angle for pupil (in radians)
     * \param _angleIris Initial angle for iris outer scale (in radians)
     * \param _angleLidBottom Initial angle for the top eyelid (in radians)
     * \param _angleLidUp Initial angle for the bottom eyelid (in radians)
     * \param _offsetLid Initial offset ratio for eyelid body
     * \param _offsetLidEdge Initial offset ratio for eyelid edge
     * \param _quality Initial sphere circle quality
     * \param _materialPupil Initial material for eye pupil
     * \param _materialIris Initial material for eye iris
     * \param _materialSclera Initial material for eye sclera
     * \param _materialLid Initial material for eye lid body
     * \param _materialLidEdge Initial material for eye lid edge
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    inline ItemEye(const std::string &_name = "Eye",
                   const Math::Vec3F &_center = {},
                   const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                   const Math::Vec3F &_upDir = Math::Vec3F::unitZ(),
                   const float _radius = 0.2f,
                   const float _offsetPupil = 0.0f,
                   const float _anglePupil = Math::toRad(8.0f),
                   const float _angleIris = Math::toRad(30.0f),
                   const float _angleLidBottom = M_PI_2,
                   const float _angleLidUp = M_PI_2,
                   const float _offsetLid = 0.04f,
                   const float _offsetLidEdge = 0.04f,
                   const size_t _quality = Items::ItemDefaultValues::sphereQuality,
                   const Math::MaterialRGB &_materialPupil = Math::MaterialRGB(Qt::black),
                   const Math::MaterialRGB &_materialIris = Math::MaterialRGB(Qt::cyan),
                   const Math::MaterialRGB &_materialSclera = Math::MaterialRGB(Qt::white),
                   const Math::MaterialRGB &_materialLid = Math::MaterialRGB(Qt::gray),
                   const Math::MaterialRGB &_materialLidEdge = Math::MaterialRGB(Qt::darkGray),
                   const uint8_t _alpha = 255U,
                   const bool _visible = true)
        : Item3DExt(_name, _center, _normal, _upDir, _alpha, _visible)
        , eyeBall(_name + ".eyeBall",
                  _radius,
                  _offsetPupil,
                  _anglePupil,
                  _angleIris,
                  _angleLidBottom,
                  _angleLidUp,
                  _offsetLid,
                  _offsetLidEdge,
                  _quality,
                  _materialPupil,
                  _materialIris,
                  _materialSclera,
                  _materialLid,
                  _materialLidEdge)
    {
        addProperty(&eyeBall);
    }

    /*!
     * \brief Constructor
     * \param _data Initial eye body data
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial eye normal - look direction
     * \param _upDir Initial secondary normal - eye up direction
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    inline ItemEye(const Props::ItemGroupEyeBall::Data &_data,
                   const std::string &_name = "Eye",
                   const Math::Vec3F &_center = {},
                   const Math::Vec3F &_normal = Math::Vec3F::unitX(),
                   const Math::Vec3F &_upDir = Math::Vec3F::unitZ(),
                   const uint8_t _alpha = 255U,
                   const bool _visible = true)
        : Item3DExt(_name, _center, _normal, _upDir, _alpha, _visible)
        , eyeBall(_name + ".eyeBall", _data)
    {
        addProperty(&eyeBall);
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
     * \brief Create 3D Open GL data
     * \param _data Output data objects
     * \param _eye Eye ball object data
     * \param _alpha Alpha
     * \return
     */
    static void
    createEye(std::list<OpenGL::Data3D *> &_data, const Props::ItemGroupEyeBall::Data &_eye, const uint8_t _alpha);
};

}  // namespace Items
}  // namespace U1

#endif  // ITEMS_ITEMEYE_H
