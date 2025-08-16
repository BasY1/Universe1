/*!
 * \file src/Items/BodyParts/Head/itemhead.cpp
 * \brief Dynamic Head video item
 */

#include "itemhead.h"

#include "../../../Math/circle.h"

#include "../../../Data3D/data3dmaterialbase.h"
#include "../../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

#define ItemHead_eyeAngleSide (Math::toRad(15.0f))      //!< Default value for eye angle side
#define ItemHead_eyeAngleUp (Math::toRad(20.0f))        //!< Default value for eye angle up
#define ItemHead_eyeAngleLobeSide (Math::toRad(10.0f))  //!< Default value for eye lobe angle side
#define ItemHead_eyeAngleLobeUp (Math::toRad(10.0f))    //!< Default value for eye lobe angle up
#define ItemHead_eyeAnglePupil (Math::toRad(8.0f))      //!< Default value for eye pupil
#define ItemHead_eyeAngleIris (Math::toRad(30.0f))      //!< Default value for eye iris
#define ItemHead_eyeAngleLid (Math::toRad(45.0f))       //!< Default value for eye lid
#define ItemHead_eyeRatioDepthEye (-0.03f)              //!< Default value for eye ball position depth
#define ItemHead_eyeRatioDepthLobe (-0.03f)             //!< Default value for eye lobe position depth
#define ItemHead_ratioLobeFront (0.05f)                 //!< Default value for eye lobe ellipsoid front
#define ItemHead_ratioLobeBack (0.6f)                   //!< Default value for eye lobe ellipsoid back
#define ItemHead_ratioLobeUp (0.2f)                     //!< Default value for eye lobe ellipsoid up
#define ItemHead_ratioLobeDown (0.2f)                   //!< Default value for eye lobe ellipsoid down
#define ItemHead_ratioLobeSideOut (0.3f)                //!< Default value for eye lobe ellipsoid side out
#define ItemHead_ratioLobeSideIn (0.2f)                 //!< Default value for eye lobe ellipsoid side in
#define ItemHead_ratioLidWidth (0.05f)                  //!< Default value for eye lid width
#define ItemHead_ratioEyeliner (0.075f)                 //!< Default value for eyeliner radius
#define ItemHead_maxEyeLookAngle float(M_PI * 0.25)     //!< Maximal eye ball turn angle

#define ItemHead_earPosSide (Math::toRad(85.0f))  //!< Default value for ear position angle
#define ItemHead_earPosUp (Math::toRad(20.0f))    //!< Default value for ear position angle upwards
#define ItemHead_earRotSide (Math::toRad(75.0f))  //!< Default value for ear rotation
#define ItemHead_earRotUp (Math::toRad(10.0f))    //!< Default value for ear rotation upwards
#define ItemHead_earRatioDepth (0.01f)            //!< Default value for ear position depth
#define ItemHead_earRatioWidth (0.03f)            //!< Default value for ear width radius
#define ItemHead_earRatioUp (0.15f)               //!< Default value for ear size in up direction
#define ItemHead_earRatioDown (0.3f)              //!< Default value for ear size in down direction
#define ItemHead_earRatioOut (0.15f)              //!< Default value for ear size in outwards direction
#define ItemHead_earRatioIn (0.05f)               //!< Default value for ear size in inwards direction

ItemHead::ItemHead(const std::string &_name,
                   const Math::Vec3F &_center,
                   const Math::Vec3F &_normal,
                   const Math::Vec3F &_upDir,
                   const Math::Vec3F &_eyeLookAt,
                   const float _radius,
                   const float _eyeRadiusRatio,
                   const float _mouthAngleOut,
                   const float _mouthAngleUp,
                   const size_t _quality,
                   const Math::MaterialRGB &_material,
                   const Math::MaterialRGB &_materialIris,
                   const Math::MaterialRGB &_materialHair,
                   const Math::MaterialRGB &_materialMouth,
                   const uint8_t _alpha,
                   const bool _visible)
    : Item3DExt(_name, _center, _normal, _upDir, _alpha, _visible)
    , quality("quality", _quality)
    , shape(_name, _radius, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, _material)
    , eyeRight(true,
               _name + ".eyeRight",
               _eyeLookAt,
               true,
               true,
               _eyeRadiusRatio,
               ItemHead_eyeAngleSide,
               ItemHead_eyeAngleUp,
               -ItemHead_eyeAngleLobeSide,
               ItemHead_eyeAngleLobeUp,
               ItemHead_eyeAnglePupil,
               ItemHead_eyeAngleIris,
               ItemHead_eyeAngleLid,
               ItemHead_eyeRatioDepthEye,
               ItemHead_eyeRatioDepthLobe,
               ItemHead_ratioLobeFront,
               ItemHead_ratioLobeBack,
               ItemHead_ratioLobeUp,
               ItemHead_ratioLobeDown,
               ItemHead_ratioLobeSideOut,
               ItemHead_ratioLobeSideIn,
               ItemHead_ratioLidWidth,
               ItemHead_ratioEyeliner,
               _material,
               {Qt::black},
               _materialIris,
               {Qt::white},
               _material,
               _material.darker())
    , eyeLeft(false,
              _name + ".eyeLeft",
              _eyeLookAt,
              true,
              true,
              _eyeRadiusRatio,
              ItemHead_eyeAngleSide,
              ItemHead_eyeAngleUp,
              ItemHead_eyeAngleLobeSide,
              ItemHead_eyeAngleLobeUp,
              ItemHead_eyeAnglePupil,
              ItemHead_eyeAngleIris,
              ItemHead_eyeAngleLid,
              ItemHead_eyeRatioDepthEye,
              ItemHead_eyeRatioDepthLobe,
              ItemHead_ratioLobeFront,
              ItemHead_ratioLobeBack,
              ItemHead_ratioLobeUp,
              ItemHead_ratioLobeDown,
              ItemHead_ratioLobeSideIn,
              ItemHead_ratioLobeSideOut,
              ItemHead_ratioLidWidth,
              ItemHead_ratioEyeliner,
              _material,
              {Qt::black},
              _materialIris,
              {Qt::white},
              _material,
              _material.darker())
    , nose(_name + ".nose",
           true,
           0.0f,
           Math::toRad(9.0f),
           0.0f,
           Math::toRad(2.0f),
           -0.05f,
           0.15f,
           0.3f,
           0.32f,
           0.03f,
           0.075f,
           0.075f,
           _material)
    , chin(_name + ".chin",
           true,
           0.0f,
           Math::toRad(-30.0f),
           0.0f,
           Math::toRad(5.0f),
           0.05f,
           0.05f,
           0.4f,
           0.3f,
           0.1f,
           0.3f,
           0.3f,
           _material)
    , forehead(_name + ".forehead",
               true,
               0.0f,
               Math::toRad(30.0f),
               0.0f,
               Math::toRad(23.0f),
               -0.07f,
               0.1f,
               0.5f,
               0.3f,
               0.08f,
               0.45f,
               0.45f,
               _material)
    , earRight(_name + ".earRight",
               true,
               ItemHead_earPosSide,
               ItemHead_earPosUp,
               -ItemHead_earRotSide,
               ItemHead_earRotUp,
               ItemHead_earRatioDepth,
               ItemHead_earRatioWidth,
               ItemHead_earRatioWidth,
               ItemHead_earRatioUp,
               ItemHead_earRatioDown,
               ItemHead_earRatioOut,
               ItemHead_earRatioIn,
               _material)
    , earLeft(_name + ".earLeft",
              true,
              -ItemHead_earPosSide,
              ItemHead_earPosUp,
              ItemHead_earRotSide,
              ItemHead_earRotUp,
              ItemHead_earRatioDepth,
              ItemHead_earRatioWidth,
              ItemHead_earRatioWidth,
              ItemHead_earRatioUp,
              ItemHead_earRatioDown,
              ItemHead_earRatioIn,
              ItemHead_earRatioOut,
              _material)
    , mouth(_name + ".mouth",
            _mouthAngleOut,
            _mouthAngleOut * 0.2f,
            _mouthAngleUp,
            _mouthAngleUp + Math::toRad(0.2f),
            _mouthAngleUp - Math::toRad(2.0f),
            _mouthAngleUp - Math::toRad(4.5f),
            0.02f,
            0.02f,
            0.05f,
            0.05f,
            _materialMouth,
            _materialMouth)
    , hair(_name + ".hair",
           BodyHead::_HairCone,
           0.1,
           0.3,
           0.5f,
           3UL,
           Math::toRad(50.0f),
           Math::toRad(60.0f),
           Math::toRad(63.0f),
           Math::toRad(63.0f),
           Math::toRad(60.0f),
           Math::toRad(70.0f),
           Math::toRad(65.0f),
           Math::toRad(60.0f),
           //
           Math::toRad(45.0f),
           Math::toRad(50.0f),
           Math::toRad(55.0f),
           Math::toRad(60.0f),
           Math::toRad(95.0f),
           Math::toRad(120.0f),
           Math::toRad(170.0f),
           Math::toRad(180.0f),
           //
           _materialHair)

{
    addProperty(&quality);
    addProperty(&shape.radius);
    addProperty(&shape.ratioFront);
    addProperty(&shape.ratioBack);
    addProperty(&shape.ratioUp);
    addProperty(&shape.ratioDown);
    addProperty(&shape.ratioRight);
    addProperty(&shape.ratioLeft);
    addProperty(&shape.material);
    addProperties(eyeRight.itemProperties());
    addProperties(eyeLeft.itemProperties());
    addProperties(nose.itemProperties());
    addProperties(chin.itemProperties());
    addProperties(forehead.itemProperties());
    addProperties(earRight.itemProperties());
    addProperties(earLeft.itemProperties());
    addProperties(mouth.itemProperties());
    addProperties(hair.itemProperties());
}

void ItemHead::HeadCenterPartProps::createData(std::list<OpenGL::Data3D *> &_data,
                                               const ShapeData &_shape,
                                               const size_t _timeStep) const
{
    if (!show.value(_timeStep))
        return;

    const float o1p = _shape.radius * ratioFront.value(_timeStep);
    const float o1m = _shape.radius * ratioBack.value(_timeStep);
    const float o2p = _shape.radius * ratioUp.value(_timeStep);
    const float o2m = _shape.radius * ratioDown.value(_timeStep);
    const float o3p = _shape.radius * ratioRight.value(_timeStep);
    const float o3m = _shape.radius * ratioLeft.value(_timeStep);

    const Math::Vec3F N1 = _shape.o.normal1.rotated(_shape.o.normal3, anglePosSide.value(_timeStep)).normalized();
    const Math::Vec3F N2 =
        N1.rotated(Math::Vec3F::cross(N1, -_shape.o.normal3).normalized(), anglePosUp.value(_timeStep)).normalized();
    const float R1 = Math::isNegative(N2.x) ? _shape.xM : _shape.xP;
    const float R2 = Math::isNegative(N2.y) ? _shape.yM : _shape.yP;
    const float R3 = Math::isNegative(N2.z) ? _shape.zM : _shape.zP;
    const Math::Vec3F N3 = (float(2) * Math::Vec3F(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();

    Math::OrientF o;

    o.center = _shape.o.center + _shape.o.normal1 * (N2.x * R1) + _shape.o.normal2 * (N2.y * R2) +
        _shape.o.normal3 * (N2.z * R3);

    o.center += ((_shape.o.normal1 * N3.x + _shape.o.normal2 * N3.y + _shape.o.normal3 * N3.z).normalized() *
                 (ratioDepth.value(_timeStep) * _shape.radius));

    const Math::Vec3F N4 = _shape.o.normal1.rotated(_shape.o.normal2, angleRotSide.value(_timeStep)).normalized();
    o.normal3 = Math::Vec3F::cross(N4, _shape.o.normal2).normalized();
    o.normal1 = N4.rotated(o.normal3, angleRotUp.value(_timeStep)).normalized();
    o.normal2 = Math::Vec3F::cross(o.normal3, o.normal1).normalized();

    _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
        o, o1p, o1m, o2p, o2m, o3p, o3m, _shape.q, material.value(_timeStep), _shape.a));
}

void ItemHead::EyeProps::createData(std::list<OpenGL::Data3D *> &_data,
                                    const ShapeData &_shape,
                                    const size_t _timeStep) const
{
    const float r0 = radius.value(_timeStep) * _shape.radius;
    if (!Math::isPositive(r0))
        return;

    const float a1 = angleSide.value(_timeStep) * (rightEye ? 1.0f : -1.0f);
    const float a2 = angleUp.value(_timeStep);

    const Math::Vec3F N1 = _shape.o.normal1.rotated(_shape.o.normal3, a1).normalized();
    const Math::Vec3F N2 = N1.rotated(Math::Vec3F::cross(N1, -_shape.o.normal3).normalized(), a2).normalized();
    const float R1 = Math::isNegative(N2.x) ? _shape.xM : _shape.xP;
    const float R2 = Math::isNegative(N2.y) ? _shape.yM : _shape.yP;
    const float R3 = Math::isNegative(N2.z) ? _shape.zM : _shape.zP;
    const Math::Vec3F N3 = (float(2) * Math::Vec3F(N2.x / R1, N2.y / R2, N2.z / R3)).normalized();

    Math::Vec3F EP = _shape.o.center + _shape.o.normal1 * (N2.x * R1) + _shape.o.normal2 * (N2.y * R2) +
        _shape.o.normal3 * (N2.z * R3);
    Math::Vec3F EN1 = (_shape.o.normal1 * N3.x + _shape.o.normal2 * N3.y + _shape.o.normal3 * N3.z).normalized();
    Math::Vec3F EN3 = Math::Vec3F::cross(EN1, _shape.o.normal2).normalized();
    Math::Vec3F EN2 = Math::Vec3F::cross(EN3, EN1).normalized();

    if (showLobe.value(_timeStep))
    {
        EP += EN1 * (_shape.radius * ratioDepthLobe.value(_timeStep));

        const Math::Vec3F NL0 = _shape.o.normal1.rotated(_shape.o.normal2, angleLobeSide.value(_timeStep)).normalized();
        const Math::Vec3F NL3 = Math::Vec3F::cross(NL0, _shape.o.normal2).normalized();
        const Math::Vec3F NL1 = NL0.rotated(NL3, angleLobeUp.value(_timeStep)).normalized();
        const Math::Vec3F NL2 = Math::Vec3F::cross(NL3, NL1).normalized();
        const float o1p = _shape.radius * ratioLobeFront.value(_timeStep);

        _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(Math::OrientF(EP, NL1, NL2, NL3),
                                                                     o1p,
                                                                     _shape.radius * ratioLobeBack.value(_timeStep),
                                                                     _shape.radius * ratioLobeUp.value(_timeStep),
                                                                     _shape.radius * ratioLobeDown.value(_timeStep),
                                                                     _shape.radius * ratioLobeRight.value(_timeStep),
                                                                     _shape.radius * ratioLobeLeft.value(_timeStep),
                                                                     _shape.q,
                                                                     materialLobe.value(_timeStep),
                                                                     _shape.a));

        EP += NL1 * o1p;
        EN1 = NL1;
        EN2 = NL2;
        EN3 = NL3;
    }

    EP += EN1 * (_shape.radius * ratioDepthEye.value(_timeStep));

    const Math::Vec3F lp =
        eyeLookAtExternal == nullptr ? eyeLookAt.value(_timeStep) : eyeLookAtExternal->value(_timeStep);

    Math::Vec3F LN1 = (lp - EP).normalized();
    if (Math::isMoreNotEqual(LN1.angleRad(EN1), ItemHead_maxEyeLookAngle))
        LN1 = EN1.rotated(Math::Vec3F::cross(EN1, LN1).normalized(), ItemHead_maxEyeLookAngle).normalized();
    const Math::Vec3F LN3 = Math::Vec3F::cross(LN1, EN2).normalized();
    const Math::Vec3F LN2 = Math::Vec3F::cross(LN3, LN1).normalized();

    const float ap = anglePupil.value(_timeStep);
    const float ai = angleIris.value(_timeStep);
    const float ae1 = std::min(ap, ai);
    const float ae2 = std::max(ap, ai);

    Math::OrientF oe = Math::OrientF(EP, LN1, LN2, LN3);

    if (Math::isPositive(ae1))
        _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
            oe, 0.0f, 2.0f * M_PI, 0.0f, ae1, r0, _shape.q, materialPupil.value(_timeStep), _shape.a));

    if (Math::isMoreNotEqual(ae2, ae1))
        _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
            oe, 0.0f, 2.0f * M_PI, ae1, ae2, r0, _shape.q, materialIris.value(_timeStep), _shape.a));

    _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(
        oe, 0.0f, 2.0f * M_PI, a2, M_PI, r0, _shape.q, materialSclera.value(_timeStep), _shape.a));

    if (!showLid.value(_timeStep))
        return;

    const Math::MaterialRGB mel = materialEyeliner.value(_timeStep);
    const float oer = ratioEyeliner.value(_timeStep) * r0;
    const float al1 = angleLid.value(_timeStep);
    const float al2 = 2.0f * (M_PI - al1);

    _data.push_back(OpenGL::Data3DMaterialNormal::sphereArc(Math::OrientF(EP, EN3, EN1, EN2),
                                                            al1,
                                                            al1 + al2,
                                                            0.0f,
                                                            M_PI,
                                                            r0 + ratioLidWidth.value(_timeStep) * r0,
                                                            _shape.q,
                                                            materialLid.value(_timeStep),
                                                            _shape.a));

    Math::OrientF o2 = oe;

    o2.normal1 = EN2.rotated(EN3, al1).normalized();
    o2.normal2 = EN3;
    o2.normal3 = Math::Vec3F::cross(o2.normal1, o2.normal2).normalized();
    _data.push_back(
        OpenGL::Data3DMaterialNormal::cylinderArc(o2, r0 * M_PI, r0, oer, oer, _shape.q, _shape.q, mel, _shape.a));

    o2.normal1 = EN2.rotated(EN3, -al1).normalized();
    o2.normal2 = EN3;
    o2.normal3 = Math::Vec3F::cross(o2.normal1, o2.normal2).normalized();
    _data.push_back(
        OpenGL::Data3DMaterialNormal::cylinderArc(o2, r0 * M_PI, r0, oer, oer, _shape.q, _shape.q, mel, _shape.a));
}

/*!
 * \brief Tool function - create lips 3D data
 * \param _data Output data objects
 * \param _shape Head shape
 * \param _p1 Circle point 1
 * \param _p2 Circle point 2
 * \param _p3 Circle point 3
 * \param _r1 Lips width radius at point 1
 * \param _r2 Lips width radius at point 2
 * \param _r3 Lips width radius at point 3
 * \param _m Material
 * \return
 */
inline static void createLipsData(std::list<OpenGL::Data3D *> &_data,
                                  const ItemHead::ShapeData &_shape,
                                  const Math::Vec3F &_p1,
                                  const Math::Vec3F &_p2,
                                  const Math::Vec3F &_p3,
                                  const float _r1,
                                  const float _r2,
                                  const float _r3,
                                  const Math::MaterialRGB &_m)
{
    const Math::Circle3F c(_p1, _p2, _p3);
    const Math::Vec3F n1 = (_p1 - c.center).normalized();
    const Math::Vec3F n2 = (_p2 - c.center).normalized();
    const Math::Vec3F n3 = (_p3 - c.center).normalized();
    const float a12 = n1.angleRad(n2);
    const float a23 = n2.angleRad(n3);

    _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(
        Math::OrientF(c.center, c.normal, n1), c.radius * a12, c.radius, _r1, _r2, _shape.q, _shape.q, _m, _shape.a));
    _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(
        Math::OrientF(c.center, c.normal, n2), c.radius * a23, c.radius, _r2, _r3, _shape.q, _shape.q, _m, _shape.a));
}

void ItemHead::MouthProps::createData(std::list<OpenGL::Data3D *> &_data,
                                      const ShapeData &_shape,
                                      const size_t _timeStep) const
{
    const MouthPointData pR = pointRight.value(_timeStep, _shape);
    const MouthPointData pL = pointLeft.value(_timeStep, _shape);
    const MouthPointData pD = pointDownCenter.value(_timeStep, _shape);
    const MouthPointData pU = pointUpCenter.value(_timeStep, _shape);
    const MouthPointData pUR = pointUpRight.value(_timeStep, _shape);
    const MouthPointData pUL = pointUpLeft.value(_timeStep, _shape);
    const float ru = radiusLipsUp.value(_timeStep) * _shape.radius;
    const float rd = radiusLipsDown.value(_timeStep) * _shape.radius;
    const Math::MaterialRGB mu = materialUp.value(_timeStep);
    const Math::MaterialRGB md = materialDown.value(_timeStep);

    createLipsData(_data, _shape, pR.position, pD.position, pL.position, 0.0f, rd, 0.0f, md);
    createLipsData(_data, _shape, pR.position, pUR.position, pU.position, 0.0f, ru, ru * 0.5f, mu);
    createLipsData(_data, _shape, pU.position, pUL.position, pL.position, ru * 0.5f, ru, 0.0f, mu);
}

/*!
 * \brief Tool function - find side angle
 * \param _areaAngles Area angles - sorted collection
 * \param _angleUp Angle up
 * \return Side angle for given up angle
 */
inline float findAngleSide(std::vector<std::pair<float, float>> &_areaAngles, const float _angleUp)
{
    for (size_t i = 0UL, j = 1UL; j < _areaAngles.size(); ++i, ++j)
    {
        if (Math::isLessOrEqual(_angleUp, _areaAngles[i].first))
            return _areaAngles[i].second;

        if (Math::equals(_angleUp, _areaAngles[j].first))
            return _areaAngles[j].second;

        if (_angleUp < _areaAngles[j].first)
        {
            const float ratio = (_angleUp - _areaAngles[i].first) / (_areaAngles[j].first - _areaAngles[i].first);
            return _areaAngles[i].second + (ratio * (_areaAngles[j].second - _areaAngles[i].second));
        }
    }
    return _areaAngles.back().second;
}

void ItemHead::HairProps::createData(std::list<OpenGL::Data3D *> &_data,
                                     const ShapeData &_shape,
                                     const size_t _timeStep) const
{
    const float r = _shape.radius * hairRadius.value(_timeStep);
    const float l = _shape.radius * hairLength.value(_timeStep);
    const BodyHead::HairStyle s = hairStyle.valueEnum<BodyHead::HairStyle>(_timeStep);

    if (!Math::isPositive(r) || !Math::isPositive(l) || s == BodyHead::_HairNone)
        return;

    const Math::MaterialRGB m = material.value(_timeStep);
    const size_t q = hairQuality.value(_timeStep);
    const float sr = r * hairStepRatio.value(_timeStep);
    const float ar1 = sr / _shape.radius;
    const float ar2 = 2.0f * ar1;

    std::vector<std::pair<float, float>> areaAngles;
    areaAngles.reserve(8);
    areaAngles.push_back({angle1Up.value(_timeStep), angle1Side.value(_timeStep)});
    areaAngles.push_back({angle2Up.value(_timeStep), angle2Side.value(_timeStep)});
    areaAngles.push_back({angle3Up.value(_timeStep), angle3Side.value(_timeStep)});
    areaAngles.push_back({angle4Up.value(_timeStep), angle4Side.value(_timeStep)});
    areaAngles.push_back({angle5Up.value(_timeStep), angle5Side.value(_timeStep)});
    areaAngles.push_back({angle6Up.value(_timeStep), angle6Side.value(_timeStep)});
    areaAngles.push_back({angle7Up.value(_timeStep), angle7Side.value(_timeStep)});
    areaAngles.push_back({angle8Up.value(_timeStep), angle8Side.value(_timeStep)});

    std::sort(areaAngles.begin(),
              areaAngles.end(),
              [](const std::pair<float, float> &_1, const std::pair<float, float> &_2) { return _1.first < _2.first; });

    std::list<Math::OrientF> hairs;

    const float auEnd = areaAngles.back().first;
    for (float au = areaAngles.front().first; Math::isLessOrEqual(au, auEnd); au += ar2)
    {
        const float as = findAngleSide(areaAngles, au);
        if (Math::isLessNotEqual(as, ar1))
            continue;

        if (Math::isLessNotEqual(as, ar2))
        {
            hairs.push_back({_shape.getSurfacePoint(0.0f, au)});
            continue;
        }

        float as1 = -ar1;
        while (true)
        {
            const float prev = as1 - ar2;
            if (Math::equals(prev, -as))
            {
                as1 = prev;
                break;
            }
            if (prev < (-as))
                break;
            as1 = prev;
        }

        for (; Math::isLessOrEqual(as1, as); as1 += ar2)
            hairs.push_back({_shape.getSurfacePoint(as1, au)});
    }

    switch (s)
    {
    case BodyHead::_HairNone: break;

    case BodyHead::_HairCylinder:
        for (const Math::OrientF &h : std::as_const(hairs))
        {
            _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(h, l, r, r, q, m, _shape.a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                Math::OrientF(h.center + h.normal1 * l, h.normal1, h.normal2, h.normal3), r, q, m, _shape.a));
        }
        break;

    case BodyHead::_HairCone:
        for (const Math::OrientF &h : std::as_const(hairs))
            _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(h, l, r, 0.0f, q, m, _shape.a));
        break;

    case BodyHead::_HairEllipsoid:
        for (const Math::OrientF &h : std::as_const(hairs))
            _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(h, l, r, r, r, r, r, q, m, _shape.a));
        break;
    }
}

void ItemHead::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    ShapeData sd = shape.value(_timeStep, valueOrientation(_timeStep), quality.value(_timeStep), a);
    if (!sd.isValid())
        return;

    _data.push_back(OpenGL::Data3DMaterialNormal::irregEllipsoid(
        sd.o, sd.xP, sd.xM, sd.yP, sd.yM, sd.zP, sd.zM, sd.q, sd.material, sd.a));

    eyeRight.createData(_data, sd, _timeStep);
    eyeLeft.createData(_data, sd, _timeStep);
    nose.createData(_data, sd, _timeStep);
    chin.createData(_data, sd, _timeStep);
    forehead.createData(_data, sd, _timeStep);
    earRight.createData(_data, sd, _timeStep);
    earLeft.createData(_data, sd, _timeStep);
    mouth.createData(_data, sd, _timeStep);
    hair.createData(_data, sd, _timeStep);
}

}  // namespace Items
}  // namespace U1
