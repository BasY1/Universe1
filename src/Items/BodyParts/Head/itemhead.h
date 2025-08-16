/*!
 * \file src/Items/BodyParts/Head/itemhead.h
 * \brief Dynamic Head video item
 */

#ifndef ITEMS_ITEMHEAD_H
#define ITEMS_ITEMHEAD_H

#include "../../item3d.h"
#include "../../../ItemProps/itempropertymaterial.h"
#include "../../../ItemProps/itempropertyenum.h"

namespace U1 {
namespace Items {

/*!
 * \namespace U1::Items::BodyHead
 * \brief 3D Head item tools
 */
namespace BodyHead {
Q_NAMESPACE

/*! \brief Hair styles */
enum HairStyle : int
{
    _HairNone = 0,  //!< No hair
    _HairCylinder,  //!< Hair as single cylinders
    _HairCone,      //!< Hair as cones
    _HairEllipsoid  //!< Hair as ellipsoids
};
Q_ENUM_NS(HairStyle)
}  // namespace BodyHead

/*! \brief Dynamic Head video item */
class ItemHead : public Item3DExt
{
 public:
    /*! \brief The Head shape data */
    struct ShapeData
    {
        float radius = 0.0f;      //!< Head radius
        float ratioFront = 1.0f;  //!< Head size ratio: front in \a normal1
        float ratioBack = 1.0f;   //!< Head size ratio: back in -\a normal1
        float ratioUp = 1.0f;     //!< Head size ratio: up in \a normal2
        float ratioDown = 1.0f;   //!< Head size ratio: down in -\a normal2
        float ratioRight = 1.0f;  //!< Head size ratio: right in \a normal3
        float ratioLeft = 1.0f;   //!< Head size ratio: left in -\a normal3

        Math::MaterialRGB material = {Qt::white};  //!< Major head material

        Math::OrientF o = {};  //!< Current orientation
        size_t q = 0UL;        //!< Current quality
        uint8_t a = 0U;        //!< Current alpha

        float xP = 0.0f;  //!< Calculated irregular ellipse radius in plus \b X direction
        float xM = 0.0f;  //!< Calculated irregular ellipse radius in minus \b X direction
        float yP = 0.0f;  //!< Calculated irregular ellipse radius in plus \b Y direction
        float yM = 0.0f;  //!< Calculated irregular ellipse radius in minus \b Y direction
        float zP = 0.0f;  //!< Calculated irregular ellipse radius in plus \b Z direction
        float zM = 0.0f;  //!< Calculated irregular ellipse radius in minus \b Z direction

        /*!
         * \brief Test validity
         * \return Head data validity flag
         */
        inline bool isValid() const
        {
            return Math::isPositive(radius);
        }

        /*!
         * \brief Getter for point and normal on shape
         * \param _angleSide Position angle side
         * \param _angleUp Position angle up
         * \return Point and normal on shape
         */
        inline Math::OrientF getSurfacePoint(const float _angleSide, const float _angleUp) const
        {
            const float sau = std::sin(_angleUp);
            const float cau = std::cos(_angleUp);

            const Math::Vec3F N1 = Math::Vec3F::unitX().rotated(Math::Vec3F::unitZ(), sau, cau).normalized();
            const Math::Vec3F N2 = Math::Vec3F::unitY().rotated(Math::Vec3F::unitZ(), sau, cau).normalized();
            const Math::Vec3F N3 = N1.rotated(N2, _angleSide).normalized();

            const float R1 = Math::isNegative(N3.x) ? xM : xP;
            const float R2 = Math::isNegative(N3.y) ? yM : yP;
            const float R3 = Math::isNegative(N3.z) ? zM : zP;

            const Math::Vec3F N4 = (float(2) * Math::Vec3F(N3.x / R1, N3.y / R2, N3.z / R3)).normalized();

            Math::OrientF result;
            result.center = o.center + o.normal1 * (N3.x * R1) + o.normal2 * (N3.y * R2) + o.normal3 * (N3.z * R3);
            result.normal1 = (o.normal1 * N4.x + o.normal2 * N4.y + o.normal3 * N4.z).normalized();
            result.normal2 = result.normal1.perpendicularNormalUp();
            result.normal3 = Math::Vec3F::cross(result.normal1, result.normal2).normalized();
            return result;
        }
    };

    /*! \brief The Head shape dynamic properties group */
    struct ShapeProps
    {
        Props::ItemPropertyFloat radius;          //!< Head radius
        Props::ItemPropertyFloat ratioFront;      //!< Head size ratio: front in \a normal1
        Props::ItemPropertyFloat ratioBack;       //!< Head size ratio: back in -\a normal1
        Props::ItemPropertyFloat ratioUp;         //!< Head size ratio: up in \a normal2
        Props::ItemPropertyFloat ratioDown;       //!< Head size ratio: down in -\a normal2
        Props::ItemPropertyFloat ratioRight;      //!< Head size ratio: right in \a normal3
        Props::ItemPropertyFloat ratioLeft;       //!< Head size ratio: left in -\a normal3
        Props::ItemPropertyMaterialRGB material;  //!< Major head material

        /*!
         * \brief Constructor
         * \param _name Major item name
         * \param _radius Initial head radius
         * \param _ratioFront Initial head size ratio: front in \a normal1
         * \param _ratioBack Initial head size ratio: back in -\a normal1
         * \param _ratioUp Initial head size ratio: up in \a normal2
         * \param _ratioDown Initial head size ratio: down in -\a normal2
         * \param _ratioRight Initial head size ratio: right in \a normal3
         * \param _ratioLeft Initial head size ratio: left in -\a normal3
         * \param _material Initial major head material
         */
        inline ShapeProps(const std::string &_name,
                          const float _radius,
                          const float _ratioFront,
                          const float _ratioBack,
                          const float _ratioUp,
                          const float _ratioDown,
                          const float _ratioRight,
                          const float _ratioLeft,
                          const Math::MaterialRGB &_material)
            : radius(_name + ".radius", _radius, 0.0, std::numeric_limits<float>::max())
            , ratioFront(_name + ".ratioFront", _ratioFront, 0.5f, 2.0f)
            , ratioBack(_name + ".ratioBack ", _ratioBack, 0.5f, 2.0f)
            , ratioUp(_name + ".ratioUp   ", _ratioUp, 0.5f, 2.0f)
            , ratioDown(_name + ".ratioDown ", _ratioDown, 0.5f, 2.0f)
            , ratioRight(_name + ".ratioRight", _ratioRight, 0.5f, 2.0f)
            , ratioLeft(_name + ".ratioLeft ", _ratioLeft, 0.5f, 2.0f)
            , material(_name + ".material ", _material)
        {
        }

        /*!
         * \brief Getter for major head properties at given time-step
         * \param _timeStep Time-step
         * \param _orientation Orientation at given time-step
         * \param _quality Sphere circle quality
         * \param _alpha Alpha
         * \return Values for the major head properties at given time-step
         */
        inline ShapeData value(const float _timeStep,
                               const Math::OrientF &_orientation,
                               const size_t _quality,
                               const uint8_t _alpha) const
        {
            ShapeData result;
            result.radius = radius.value(_timeStep);
            if (!result.isValid())
                return result;

            result.ratioFront = ratioFront.value(_timeStep);
            result.ratioBack = ratioBack.value(_timeStep);
            result.ratioUp = ratioUp.value(_timeStep);
            result.ratioDown = ratioDown.value(_timeStep);
            result.ratioRight = ratioRight.value(_timeStep);
            result.ratioLeft = ratioLeft.value(_timeStep);
            result.material = material.value(_timeStep);

            result.o = _orientation;
            result.q = _quality;
            result.a = _alpha;
            result.xP = result.radius * 0.5f * result.ratioFront;
            result.xM = result.radius * 0.75f * result.ratioBack;
            result.yP = result.radius * result.ratioUp;
            result.yM = result.radius * 0.75f * result.ratioDown;
            result.zP = result.radius * 0.75f * result.ratioRight;
            result.zM = result.radius * 0.75f * result.ratioLeft;
            return result;
        }
    };

    /*! \brief Single eye properties group */
    struct HeadCenterPartProps
    {
        Props::ItemPropertyBool show;  //!< Show head part

        Props::ItemPropertyFloat anglePosSide;  //!< Angle for head part position towards ears (in radians)
        Props::ItemPropertyFloat anglePosUp;    //!< Angle for head part position upwards (in radians)
        Props::ItemPropertyFloat angleRotSide;  //!< Angle for head part ellipsoid towards ears (in radians)
        Props::ItemPropertyFloat angleRotUp;    //!< Angle for head part ellipsoid upwards (in radians)

        Props::ItemPropertyFloat ratioDepth;  //!< Head part position depth ratio (-1 to 1) to shape radius
        Props::ItemPropertyFloat ratioFront;  //!< Head part shape size ratio (0.01 to 1): front in \a normal1
        Props::ItemPropertyFloat ratioBack;   //!< Head part shape size ratio (0.01 to 1): back in -\a normal1
        Props::ItemPropertyFloat ratioUp;     //!< Head part shape size ratio (0.01 to 1): up in \a normal2
        Props::ItemPropertyFloat ratioDown;   //!< Head part shape size ratio (0.01 to 1): down in -\a normal2
        Props::ItemPropertyFloat ratioRight;  //!< Head part shape size ratio (0.01 to 1): right in \a normal3
        Props::ItemPropertyFloat ratioLeft;   //!< Head part shape size ratio (0.01 to 1): left in -\a normal3

        Props::ItemPropertyMaterialRGB material;  //!< Material for head part

        /*!
         * \brief Constructor
         * \param _name Major head center part item name
         * \param _show Initial show head part flag
         * \param _anglePosSide Initial angle for head part position towards ears (in radians)
         * \param _anglePosUp Initial angle for head part position upwards (in radians)
         * \param _angleRotSide Initial angle for head part ellipsoid towards ears (in radians)
         * \param _angleRotUp Initial angle for head part ellipsoid upwards (in radians)
         * \param _ratioDepth Initial head part position depth ratio (-1 to 1) to shape radius
         * \param _ratioFront Initial head part shape size ratio (0.01 to 1): front in \a normal1
         * \param _ratioBack Initial head part shape size ratio (0.01 to 1): back in -\a normal1
         * \param _ratioUp Initial head part shape size ratio (0.01 to 1): up in \a normal2
         * \param _ratioDown Initial head part shape size ratio (0.01 to 1): down in -\a normal2
         * \param _ratioRight Initial head part shape size ratio (0.01 to 1): right in \a normal3
         * \param _ratioLeft Initial head part shape size ratio (0.01 to 1): left in -\a normal3
         * \param _material Initial material for head part
         */
        inline HeadCenterPartProps(const std::string &_name,
                                   const bool _show,
                                   const float _anglePosSide,
                                   const float _anglePosUp,
                                   const float _angleRotSide,
                                   const float _angleRotUp,
                                   const float _ratioDepth,
                                   const float _ratioFront,
                                   const float _ratioBack,
                                   const float _ratioUp,
                                   const float _ratioDown,
                                   const float _ratioRight,
                                   const float _ratioLeft,
                                   const Math::MaterialRGB &_material)
            : show(_name + ".show", _show)
            , anglePosSide(_name + ".anglePosSide", _anglePosSide, -M_PI, M_PI)
            , anglePosUp(_name + ".anglePosUp  ", _anglePosUp, -M_PI_2, M_PI_2)
            , angleRotSide(_name + ".angleRotSide", _angleRotSide, -M_PI, M_PI)
            , angleRotUp(_name + ".angleRotUp  ", _angleRotUp, -M_PI_2, M_PI_2)
            , ratioDepth(_name + ".ratioDepth", _ratioDepth, -1.0f, 1.0f)
            , ratioFront(_name + ".ratioFront", _ratioFront, 0.0f, std::numeric_limits<float>::max())
            , ratioBack(_name + ".ratioBack", _ratioBack, 0.0f, std::numeric_limits<float>::max())
            , ratioUp(_name + ".ratioUp", _ratioUp, 0.0f, std::numeric_limits<float>::max())
            , ratioDown(_name + ".ratioDown", _ratioDown, 0.0f, std::numeric_limits<float>::max())
            , ratioRight(_name + ".ratioRight", _ratioRight, 0.0f, std::numeric_limits<float>::max())
            , ratioLeft(_name + ".ratioLeft", _ratioLeft, 0.0f, std::numeric_limits<float>::max())
            , material(_name + ".material", _material)
        {
        }

        /*!
         * \brief Getter for item properties collection
         * \return An item properties collection
         */
        inline std::vector<ItemProperty *> itemProperties()
        {
            return {&show,
                    &anglePosSide,
                    &anglePosUp,
                    &angleRotSide,
                    &angleRotUp,
                    &ratioDepth,
                    &ratioFront,
                    &ratioBack,
                    &ratioUp,
                    &ratioDown,
                    &ratioRight,
                    &ratioLeft,
                    &material};
        }

        /*!
         * \brief Create 3D Open GL data objects
         * \param _data Output data objects
         * \param _shape Head shape
         * \param _timeStep Time-step
         */
        void createData(std::list<OpenGL::Data3D *> &_data, const ShapeData &_shape, const size_t _timeStep) const;
    };

    /*! \brief Single eye properties group */
    struct EyeProps
    {
        const bool rightEye;  //!< Right/left eye flag

        const Props::ItemPropertyVec3F *eyeLookAtExternal;  //!< External look at position

        Props::ItemPropertyBool showLobe;         //!< Show eye lobe
        Props::ItemPropertyBool showLid;          //!< Show eye lid and eyeliner
        Props::ItemPropertyVec3F eyeLookAt;       //!< Eye look at position
        Props::ItemPropertyFloat radius;          //!< Eye ball radius
        Props::ItemPropertyFloat angleSide;       //!< Angle for eye position towards ear (in radians)
        Props::ItemPropertyFloat angleUp;         //!< Angle for eye position upwards (in radians)
        Props::ItemPropertyFloat angleLobeSide;   //!< Angle for eye lobe ellipsoid towards ear (in radians)
        Props::ItemPropertyFloat angleLobeUp;     //!< Angle for eye lobe ellipsoid upwards (in radians)
        Props::ItemPropertyFloat anglePupil;      //!< Angle for pupil (in radians)
        Props::ItemPropertyFloat angleIris;       //!< Angle for iris outer scale (in radians)
        Props::ItemPropertyFloat angleLid;        //!< Angle for how open are lids, (0 = closed eye to PI) (in radians)
        Props::ItemPropertyFloat ratioDepthEye;   //!< Eye ball position depth ratio (-1 to 1) to shape radius
        Props::ItemPropertyFloat ratioDepthLobe;  //!< Eye lobe depth ratio (-1 to 1) to shape radius
        Props::ItemPropertyFloat ratioLobeFront;  //!< Eye lobe shape size ratio (0.01 to 1): front in \a normal1
        Props::ItemPropertyFloat ratioLobeBack;   //!< Eye lobe shape size ratio (0.01 to 1): back in -\a normal1
        Props::ItemPropertyFloat ratioLobeUp;     //!< Eye lobe shape size ratio (0.01 to 1): up in \a normal2
        Props::ItemPropertyFloat ratioLobeDown;   //!< Eye lobe shape size ratio (0.01 to 1): down in -\a normal2
        Props::ItemPropertyFloat ratioLobeRight;  //!< Eye lobe shape size ratio (0.01 to 1): right in \a normal3
        Props::ItemPropertyFloat ratioLobeLeft;   //!< Eye lobe shape size ratio (0.01 to 1): left in -\a normal3
        Props::ItemPropertyFloat ratioLidWidth;   //!< Lid with as ratio (0 to 0.5) to eye ball radius
        Props::ItemPropertyFloat ratioEyeliner;   //!< Eyeliner size as ratio (0 to 0.75) to eye ball radius

        Props::ItemPropertyMaterialRGB materialLobe;      //!< Material for eye lobe
        Props::ItemPropertyMaterialRGB materialPupil;     //!< Material for eye pupil
        Props::ItemPropertyMaterialRGB materialIris;      //!< Material for eye iris
        Props::ItemPropertyMaterialRGB materialSclera;    //!< Material for eye sclera
        Props::ItemPropertyMaterialRGB materialLid;       //!< Material for eye lid
        Props::ItemPropertyMaterialRGB materialEyeliner;  //!< Material for eyeliner

        /*!
         * \brief Constructor
         * \param _rightEye Right/left eye flag
         * \param _name Major item name
         * \param _eyeLookAt Initial eye look at position
         * \param _showLobe Initial show eye lobe flag
         * \param _showLid Initial show eye lid flag
         * \param _radius Initial eye ball radius
         * \param _angleSide Initial angle for eye position towards ear (in radians)
         * \param _angleUp Initial angle for eye position upwards (in radians)
         * \param _angleLobeSide Initial angle for eye lobe ellipsoid towards ear (in radians)
         * \param _angleLobeUp Initial angle for eye lobe ellipsoid upwards (in radians)
         * \param _anglePupil Initial angle for pupil (in radians)
         * \param _angleIris Initial angle for iris outer scale (in radians)
         * \param _angleLid Initial angle for how open are lids, (0 = closed eye to PI) (in radians)
         * \param _ratioDepthEye Initial eye ball position depth ratio (-1 to 1) shape radius
         * \param _ratioDepthLobe Initial eye lobe depth ratio (-1 to 1) to shape radius
         * \param _ratioLobeFront Initial eye lobe size ratio (0.01 to 1): front in \a normal1
         * \param _ratioLobeBack Initial eye lobe size ratio (0.01 to 1): back in -\a normal1
         * \param _ratioLobeUp Initial eye lobe size ratio (0.01 to 1): up in \a normal2
         * \param _ratioLobeDown Initial eye lobe size ratio (0.01 to 1): down in -\a normal2
         * \param _ratioLobeRight Initial eye lobe size ratio (0.01 to 1): right in \a normal3
         * \param _ratioLobeLeft Initial eye lobe size ratio (0.01 to 1): left in -\a normal3
         * \param _ratioLidWidth Initial lid with as ratio (0 to 0.5) to eye ball radius
         * \param _ratioEyeliner Initial eyeliner size as ratio (0 to 0.75) to eye ball radius
         * \param _materialLobe Initial material for eye lobe
         * \param _materialPupil Initial material for eye pupil
         * \param _materialIris Initial material for eye iris
         * \param _materialSclera Initial material for eye sclera
         * \param _materialLid Initial material for eye lid
         * \param _materialEyeliner Initial Material for eyeliner
         */
        inline EyeProps(const bool _rightEye,
                        const std::string &_name,
                        const Math::Vec3F &_eyeLookAt,
                        const bool _showLobe,
                        const bool _showLid,
                        const float _radius,
                        const float _angleSide,
                        const float _angleUp,
                        const float _angleLobeSide,
                        const float _angleLobeUp,
                        const float _anglePupil,
                        const float _angleIris,
                        const float _angleLid,
                        const float _ratioDepthEye,
                        const float _ratioDepthLobe,
                        const float _ratioLobeFront,
                        const float _ratioLobeBack,
                        const float _ratioLobeUp,
                        const float _ratioLobeDown,
                        const float _ratioLobeRight,
                        const float _ratioLobeLeft,
                        const float _ratioLidWidth,
                        const float _ratioEyeliner,
                        const Math::MaterialRGB &_materialLobe,
                        const Math::MaterialRGB &_materialPupil,
                        const Math::MaterialRGB &_materialIris,
                        const Math::MaterialRGB &_materialSclera,
                        const Math::MaterialRGB &_materialLid,
                        const Math::MaterialRGB &_materialEyeliner)
            : rightEye(_rightEye)
            , eyeLookAtExternal(nullptr)
            , showLobe(_name + ".showLobe", _showLobe)
            , showLid(_name + ".showLid", _showLid)
            , eyeLookAt(_name + ".eyeLookAt", _eyeLookAt)
            , radius(_name + ".radius", _radius, 0.0, std::numeric_limits<float>::max())
            , angleSide(_name + ".angleSide", _angleSide, 0.0f, M_PI_4)
            , angleUp(_name + ".angleUp", _angleUp, 0.0f, M_PI_4)
            , angleLobeSide(_name + ".angleLobeSide", _angleLobeSide, -M_PI, M_PI)
            , angleLobeUp(_name + ".angleLobeUp", _angleLobeUp, -M_PI_2, M_PI_2)
            , anglePupil(_name + ".anglePupil", _anglePupil, 0.0f, Math::toRad(45.0f))
            , angleIris(_name + ".angleIris", _angleIris, 0.0f, M_PI_2)
            , angleLid(_name + ".angleLid", _angleLid, 0.0f, M_PI_2)
            , ratioDepthEye(_name + ".ratioDepthEye", _ratioDepthEye, -1.0f, 1.0)
            , ratioDepthLobe(_name + ".ratioDepthLobe", _ratioDepthLobe, -1.0f, 1.0)
            , ratioLobeFront(_name + ".ratioLobeFront", _ratioLobeFront, 0.01f, 1.0)
            , ratioLobeBack(_name + ".ratioLobeBack", _ratioLobeBack, 0.01f, 2.0)
            , ratioLobeUp(_name + ".ratioLobeUp", _ratioLobeUp, 0.01f, 1.0)
            , ratioLobeDown(_name + ".ratioLobeDown", _ratioLobeDown, 0.01f, 1.0)
            , ratioLobeRight(_name + ".ratioLobeRight", _ratioLobeRight, 0.01f, 1.0)
            , ratioLobeLeft(_name + ".ratioLobeLeft", _ratioLobeLeft, 0.01f, 1.0)
            , ratioLidWidth(_name + ".ratioLidWidth", _ratioLidWidth, 0.0f, 0.5f)
            , ratioEyeliner(_name + ".ratioEyeliner", _ratioEyeliner, 0.0f, 0.75f)
            , materialLobe(_name + ".materialLobe", _materialLobe)
            , materialPupil(_name + ".materialPupil", _materialPupil)
            , materialIris(_name + ".materialIris", _materialIris)
            , materialSclera(_name + ".materialSclera", _materialSclera)
            , materialLid(_name + ".materialLid", _materialLid)
            , materialEyeliner(_name + ".materialEyeliner", _materialEyeliner)
        {
        }

        /*!
         * \brief Getter for item properties collection
         * \return An item properties collection
         */
        inline std::vector<ItemProperty *> itemProperties()
        {
            return {&showLobe,       &showLid,        &eyeLookAt,       &radius,       &angleSide,     &angleUp,
                    &angleLobeSide,  &angleLobeUp,    &anglePupil,      &angleIris,    &angleLid,      &ratioDepthEye,
                    &ratioDepthLobe, &ratioLobeFront, &ratioLobeBack,   &ratioLobeUp,  &ratioLobeDown, &ratioLobeRight,
                    &ratioLobeLeft,  &ratioLidWidth,  &ratioEyeliner,   &materialLobe, &materialPupil, &materialIris,
                    &materialSclera, &materialLid,    &materialEyeliner};
        }

        /*!
         * \brief Create 3D Open GL data objects
         * \param _data Output data objects
         * \param _shape Head shape
         * \param _timeStep Time-step
         */
        void createData(std::list<OpenGL::Data3D *> &_data, const ShapeData &_shape, const size_t _timeStep) const;
    };

    /*! \brief The Head mouth point data */
    struct MouthPointData
    {
        float angleSide = 0.0f;   //!< Angle for mouth point - towards ear (in radians)
        float angleUp = 0.0f;     //!< Angle for mouth point - upwards (in radians)
        float ratioDepth = 0.0f;  //!< Mouth point position depth ratio (-1 to 1) to shape radius

        Math::Vec3F position = {};  //!< Position within the major head shape
    };

    /*! \brief Mouth properties group */
    struct MouthPointProps
    {
        Props::ItemPropertyFloat angleSide;   //!< Angle for mouth point - towards ear (in radians)
        Props::ItemPropertyFloat angleUp;     //!< Angle for mouth point - upwards (in radians)
        Props::ItemPropertyFloat ratioDepth;  //!< Mouth point position depth ratio (-1 to 1) to shape radius

        /*!
         * \brief Constructor
         * \param _name Major item name
         * \param _angleSide  Initial angle for mouth point - towards ear (in radians)
         * \param _angleUp Initial angle for mouth point - upwards (in radians)
         * \param _ratioDepth Initial mouth point position depth ratio (-1 to 1) to shape radius
         */
        inline MouthPointProps(const std::string &_name,
                               const float _angleSide,
                               const float _angleUp,
                               const float _ratioDepth)
            : angleSide(_name + ".angleSide", _angleSide, -M_PI, M_PI)
            , angleUp(_name + ".angleUp", _angleUp, -M_PI_2, M_PI_2)
            , ratioDepth(_name + ".ratioDepth", _ratioDepth, -1.0f, 1.0)
        {
        }

        /*!
         * \brief Getter for head point at given time-step
         * \param _timeStep Time-step
         * \param _shape Major shape of a head
         * \return Head point at given time-step
         */
        inline MouthPointData value(const float _timeStep, const ShapeData &_shape) const
        {
            MouthPointData result;
            result.angleSide = angleSide.value(_timeStep);
            result.angleUp = angleUp.value(_timeStep);
            result.ratioDepth = ratioDepth.value(_timeStep) * _shape.radius;

            const Math::Vec3F N1 = _shape.o.normal1.rotated(_shape.o.normal3, result.angleSide).normalized();
            const Math::Vec3F N2 =
                N1.rotated(Math::Vec3F::cross(N1, -_shape.o.normal3).normalized(), result.angleUp).normalized();
            const float R1 = Math::isNegative(N2.x) ? _shape.xM : _shape.xP;
            const float R2 = Math::isNegative(N2.y) ? _shape.yM : _shape.yP;
            const float R3 = Math::isNegative(N2.z) ? _shape.zM : _shape.zP;
            const Math::Vec3F N3 = (float(2) * Math::Vec3F(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();

            result.position = _shape.o.center + _shape.o.normal1 * (N2.x * R1) + _shape.o.normal2 * (N2.y * R2) +
                _shape.o.normal3 * (N2.z * R3);

            result.position += N3 * result.ratioDepth;

            return result;
        }
    };

    /*! \brief Mouth properties group */
    struct MouthProps
    {
        MouthPointProps pointRight;       //!< Right outer point properties
        MouthPointProps pointLeft;        //!< Left outer point properties
        MouthPointProps pointDownCenter;  //!< Down central point properties
        MouthPointProps pointUpCenter;    //!< Up central point properties
        MouthPointProps pointUpRight;     //!< Up right point properties
        MouthPointProps pointUpLeft;      //!< Up left point properties

        Props::ItemPropertyFloat radiusLipsUp;    //!< Mouth up lips radius
        Props::ItemPropertyFloat radiusLipsDown;  //!< Mouth down lips radius

        Props::ItemPropertyMaterialRGB materialUp;    //!< Material for up lips
        Props::ItemPropertyMaterialRGB materialDown;  //!< Material for down lips

        /*!
         * \brief Constructor
         * \param _name Major item name
         * \param _angleSideOut Side angle for outer points (\a pointRight and \a pointLeft)
         * \param _angleSideUpIn Side angle for inner upper lips points (\a pointUpRight and \a pointUpLeft)
         * \param _angleUpCenter Up angle for up center point (\a pointUpCenter)
         * \param _angleUpRightLeft Up angle for up inner points (\a pointUpRight and \a pointUpLeft)
         * \param _angleUpOut Up angle for outer points (\a pointRight and \a pointLeft)
         * \param _angleUpDown Up angle for down center point (\a pointDownCenter)
         * \param _ratioDepthRightLeft Up inner points position depth ratio (-1 to 1) to shape radius
         * \param _ratioDepthDown Down center point position depth ratio (-1 to 1) to shape radius
         * \param _radiusLipsUp Up lips radius
         * \param _radiusLipsDown Down lips radius
         * \param _materialUp Material for up lips
         * \param _materialDown Material for down lips
         */
        inline MouthProps(const std::string &_name,
                          const float _angleSideOut,
                          const float _angleSideUpIn,
                          const float _angleUpCenter,
                          const float _angleUpRightLeft,
                          const float _angleUpOut,
                          const float _angleUpDown,
                          const float _ratioDepthRightLeft,
                          const float _ratioDepthDown,
                          const float _radiusLipsUp,
                          const float _radiusLipsDown,
                          const Math::MaterialRGB &_materialUp,
                          const Math::MaterialRGB &_materialDown)
            : pointRight(_name + ".pointRight", _angleSideOut, _angleUpOut, 0.0f)
            , pointLeft(_name + ".pointLeft", -_angleSideOut, _angleUpOut, 0.0f)
            , pointDownCenter(_name + ".pointDownCenter", 0.0, _angleUpDown, _ratioDepthDown)
            , pointUpCenter(_name + ".pointUpCenter", 0.0, _angleUpCenter, 0.0f)
            , pointUpRight(_name + ".pointUpRight", _angleSideUpIn, _angleUpRightLeft, _ratioDepthRightLeft)
            , pointUpLeft(_name + ".pointUpLeft", -_angleSideUpIn, _angleUpRightLeft, _ratioDepthRightLeft)
            , radiusLipsUp(_name + ".radiusLipsUp", _radiusLipsUp, 0.0f, std::numeric_limits<float>::max())
            , radiusLipsDown(_name + ".radiusLipsDown", _radiusLipsDown, 0.0f, std::numeric_limits<float>::max())
            , materialUp(_name + ".materialUp", _materialUp)
            , materialDown(_name + ".materialDown", _materialDown)
        {
        }

        /*!
         * \brief Getter for item properties collection
         * \return An item properties collection
         */
        inline std::vector<ItemProperty *> itemProperties()
        {
            return {&pointRight.angleSide,
                    &pointRight.angleUp,
                    &pointRight.ratioDepth,
                    &pointLeft.angleSide,
                    &pointLeft.angleUp,
                    &pointLeft.ratioDepth,
                    &pointDownCenter.angleSide,
                    &pointDownCenter.angleUp,
                    &pointDownCenter.ratioDepth,
                    &pointUpCenter.angleSide,
                    &pointUpCenter.angleUp,
                    &pointUpCenter.ratioDepth,
                    &pointUpRight.angleSide,
                    &pointUpRight.angleUp,
                    &pointUpRight.ratioDepth,
                    &pointUpLeft.angleSide,
                    &pointUpLeft.angleUp,
                    &pointUpLeft.ratioDepth,
                    &radiusLipsUp,
                    &radiusLipsDown,
                    &materialUp,
                    &materialDown};
        }

        /*!
         * \brief Create 3D Open GL data objects
         * \param _data Output data objects
         * \param _shape Head shape
         * \param _timeStep Time-step
         */
        void createData(std::list<OpenGL::Data3D *> &_data, const ShapeData &_shape, const size_t _timeStep) const;
    };

    /*! \brief Hair properties group */
    struct HairProps
    {
        Props::ItemPropertyEnum hairStyle;  //!< Hair length

        Props::ItemPropertyFloat hairRadius;     //!< Hair radius
        Props::ItemPropertyFloat hairLength;     //!< Hair length
        Props::ItemPropertyFloat hairStepRatio;  //!< Hair step ratio

        Props::ItemPropertyQuality hairQuality;  //!< Hair length

        Props::ItemPropertyFloat angle1Side;  //!< Angle for hair point 1 - towards ear (in radians)
        Props::ItemPropertyFloat angle2Side;  //!< Angle for hair point 2 - towards ear (in radians)
        Props::ItemPropertyFloat angle3Side;  //!< Angle for hair point 3 - towards ear (in radians)
        Props::ItemPropertyFloat angle4Side;  //!< Angle for hair point 4 - towards ear (in radians)
        Props::ItemPropertyFloat angle5Side;  //!< Angle for hair point 5 - towards ear (in radians)
        Props::ItemPropertyFloat angle6Side;  //!< Angle for hair point 6 - towards ear (in radians)
        Props::ItemPropertyFloat angle7Side;  //!< Angle for hair point 7 - towards ear (in radians)
        Props::ItemPropertyFloat angle8Side;  //!< Angle for hair point 8 - towards ear (in radians)

        Props::ItemPropertyFloat angle1Up;  //!< Angle for hair point 1 - upwards (in radians)
        Props::ItemPropertyFloat angle2Up;  //!< Angle for hair point 2 - upwards (in radians)
        Props::ItemPropertyFloat angle3Up;  //!< Angle for hair point 3 - upwards (in radians)
        Props::ItemPropertyFloat angle4Up;  //!< Angle for hair point 4 - upwards (in radians)
        Props::ItemPropertyFloat angle5Up;  //!< Angle for hair point 5 - upwards (in radians)
        Props::ItemPropertyFloat angle6Up;  //!< Angle for hair point 6 - upwards (in radians)
        Props::ItemPropertyFloat angle7Up;  //!< Angle for hair point 7 - upwards (in radians)
        Props::ItemPropertyFloat angle8Up;  //!< Angle for hair point 8 - upwards (in radians)

        Props::ItemPropertyMaterialRGB material;  //!< Material for hair

        /*!
         * \brief Constructor
         * \param _name Major item name
         * \param _style Initial Hair length
         * \param _hairRadius Initial hair radius
         * \param _hairLength Initial hair length
         * \param _hairStepRatio Initial hair step ratio
         * \param _hairQuality Initial hair circle quality
         * \param _angle1Side Initial angle for hair point 1 - towards ear (in radians)
         * \param _angle2Side Initial angle for hair point 2 - towards ear (in radians)
         * \param _angle3Side Initial angle for hair point 3 - towards ear (in radians)
         * \param _angle4Side Initial angle for hair point 4 - towards ear (in radians)
         * \param _angle5Side Initial angle for hair point 5 - towards ear (in radians)
         * \param _angle6Side Initial angle for hair point 6 - towards ear (in radians)
         * \param _angle7Side Initial angle for hair point 7 - towards ear (in radians)
         * \param _angle8Side Initial angle for hair point 8 - towards ear (in radians)
         * \param _angle1Up Initial angle for hair point 1 - upwards (in radians)
         * \param _angle2Up Initial angle for hair point 2 - upwards (in radians)
         * \param _angle3Up Initial angle for hair point 3 - upwards (in radians)
         * \param _angle4Up Initial angle for hair point 4 - upwards (in radians)
         * \param _angle5Up Initial angle for hair point 5 - upwards (in radians)
         * \param _angle6Up Initial angle for hair point 6 - upwards (in radians)
         * \param _angle7Up Initial angle for hair point 7 - upwards (in radians)
         * \param _angle8Up Initial angle for hair point 8 - upwards (in radians)
         * \param _material Initial hair material
         */
        inline HairProps(const std::string &_name,
                         const BodyHead::HairStyle _style,
                         const float _hairRadius,
                         const float _hairLength,
                         const float _hairStepRatio,
                         const float _hairQuality,
                         const float _angle1Side,
                         const float _angle2Side,
                         const float _angle3Side,
                         const float _angle4Side,
                         const float _angle5Side,
                         const float _angle6Side,
                         const float _angle7Side,
                         const float _angle8Side,
                         const float _angle1Up,
                         const float _angle2Up,
                         const float _angle3Up,
                         const float _angle4Up,
                         const float _angle5Up,
                         const float _angle6Up,
                         const float _angle7Up,
                         const float _angle8Up,
                         const Math::MaterialRGB &_material)
            : hairStyle(_name + ".hairStyle", QMetaEnum::fromType<BodyHead::HairStyle>(), _style)
            , hairRadius(_name + ".hairRadius", _hairRadius, 0.0f, 1.0f)
            , hairLength(_name + ".hairLength", _hairLength, 0.0f, std::numeric_limits<float>::max())
            , hairStepRatio(_name + ".hairStepRatio", _hairStepRatio, 0.5f, 20.0f)
            , hairQuality(_name + ".hairQuality", _hairQuality)
            , angle1Side(_name + ".angle1Side", _angle1Side, 0.0f, M_PI)
            , angle2Side(_name + ".angle2Side", _angle2Side, 0.0f, M_PI)
            , angle3Side(_name + ".angle3Side", _angle3Side, 0.0f, M_PI)
            , angle4Side(_name + ".angle4Side", _angle4Side, 0.0f, M_PI)
            , angle5Side(_name + ".angle5Side", _angle5Side, 0.0f, M_PI)
            , angle6Side(_name + ".angle6Side", _angle6Side, 0.0f, M_PI)
            , angle7Side(_name + ".angle7Side", _angle7Side, 0.0f, M_PI)
            , angle8Side(_name + ".angle8Side", _angle8Side, 0.0f, M_PI)
            , angle1Up(_name + ".angle1Up", _angle1Up, 0.0f, 2.0f * M_PI)
            , angle2Up(_name + ".angle2Up", _angle2Up, 0.0f, 2.0f * M_PI)
            , angle3Up(_name + ".angle3Up", _angle3Up, 0.0f, 2.0f * M_PI)
            , angle4Up(_name + ".angle4Up", _angle4Up, 0.0f, 2.0f * M_PI)
            , angle5Up(_name + ".angle5Up", _angle5Up, 0.0f, 2.0f * M_PI)
            , angle6Up(_name + ".angle6Up", _angle6Up, 0.0f, 2.0f * M_PI)
            , angle7Up(_name + ".angle7Up", _angle7Up, 0.0f, 2.0f * M_PI)
            , angle8Up(_name + ".angle8Up", _angle8Up, 0.0f, 2.0f * M_PI)
            , material(_name + ".material", _material)
        {
        }

        /*!
         * \brief Getter for item properties collection
         * \return An item properties collection
         */
        inline std::vector<ItemProperty *> itemProperties()
        {
            return {&hairStyle,  &hairRadius, &hairLength, &hairStepRatio, &hairQuality, &angle1Side,
                    &angle2Side, &angle3Side, &angle4Side, &angle5Side,    &angle6Side,  &angle7Side,
                    &angle8Side, &angle1Up,   &angle2Up,   &angle3Up,      &angle4Up,    &angle5Up,
                    &angle6Up,   &angle7Up,   &angle8Up,   &material};
        }

        /*!
         * \brief Create 3D Open GL data objects
         * \param _data Output data objects
         * \param _shape Head shape
         * \param _timeStep Time-step
         */
        void createData(std::list<OpenGL::Data3D *> &_data, const ShapeData &_shape, const size_t _timeStep) const;
    };

    Props::ItemPropertyQuality quality;  //!< Sphere circle quality

    ShapeProps shape;              //!< Head body shape properties
    EyeProps eyeRight;             //!< Right eye properties
    EyeProps eyeLeft;              //!< Left eye properties
    HeadCenterPartProps nose;      //!< Nose properties
    HeadCenterPartProps chin;      //!< Chin properties
    HeadCenterPartProps forehead;  //!< Forehead properties
    HeadCenterPartProps earRight;  //!< Right ear properties
    HeadCenterPartProps earLeft;   //!< Left ear properties
    MouthProps mouth;              //!< Mouth properties
    HairProps hair;                //!< Hair properties

    /*!
     * \brief Constructor
     * \param _name Item name
     * \param _center Initial center point
     * \param _normal Initial major front face direction
     * \param _upDir Initial secondary normal - up direction
     * \param _eyeLookAt Initial look at position
     * \param _radius Initial head radius
     * \param _eyeRadiusRatio Initial eye ball radius as a ratio to major head radius
     * \param _mouthAngleOut Initial angle for mouth outer points
     * \param _mouthAngleUp Initial angle for mouth position
     * \param _quality Initial sphere quality
     * \param _material Initial major head material
     * \param _materialIris Initial eye iris material
     * \param _materialHair Initial hair material
     * \param _materialMouth Initial mouth material
     * \param _alpha Initial value for general alpha
     * \param _visible Initial value for visible flag
     */
    ItemHead(const std::string &_name = "Head",
             const Math::Vec3F &_center = {},
             const Math::Vec3F &_normal = Math::Vec3F::unitX(),
             const Math::Vec3F &_upDir = Math::Vec3F::unitZ(),
             const Math::Vec3F &_eyeLookAt = Math::Vec3F::unitX() * 10.0f,
             const float _radius = 1.0f,
             const float _eyeRadiusRatio = 0.1f,
             const float _mouthAngleOut = Math::toRad(15.0f),
             const float _mouthAngleUp = Math::toRad(1.0f),
             const size_t _quality = ItemDefaultValues::sphereQuality,
             const Math::MaterialRGB &_material = {QColor(255, 205, 205)},
             const Math::MaterialRGB &_materialIris = {Qt::cyan},
             const Math::MaterialRGB &_materialHair = {Qt::darkYellow},
             const Math::MaterialRGB &_materialMouth = {Qt::darkRed},
             const uint8_t _alpha = 255U,
             const bool _visible = true);

    /*!
     * \brief Setup look at property
     * \param _externalLookAtProp New external property for eyes to look at
     */
    inline void setLookAtProperty(const Props::ItemPropertyVec3F *_externalLookAtProp)
    {
        eyeRight.eyeLookAtExternal = _externalLookAtProp;
        eyeLeft.eyeLookAtExternal = _externalLookAtProp;
    }

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

#endif  // ITEMS_ITEMHEAD_H
