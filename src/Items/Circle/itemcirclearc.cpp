/*!
 * \file src/Items/Circle/itemcirclearc.cpp
 * \brief Dynamic circle video item
 */

#include "itemcirclearc.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialsalpha.h"

namespace U1 {
namespace Items {

ItemCircleArc::ItemCircleArc(const std::string &_name,
                             const Math::Vec3F &_center,
                             const Math::Vec3F &_normal,
                             const Math::Vec3F &_arm,
                             const float _angleStart,
                             const float _angleEnd,
                             const float _radius,
                             const size_t _quality,
                             const CircleArc::ShowCircleArcType _show,
                             const Math::MaterialRGB &_materialFront,
                             const Math::MaterialRGB &_materialBack,
                             const Math::MaterialRGBA &_materialCenterFront,
                             const Math::MaterialRGBA &_materialBorderFront,
                             const Math::MaterialRGBA &_materialCenterBack,
                             const Math::MaterialRGBA &_materialBorderBack,
                             const uint8_t _alpha,
                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , angleStart("angleStart", _angleStart)
    , angleEnd("angleEnd", _angleEnd)
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<CircleArc::ShowCircleArcType>(), _show)
    , materialFront("materialFront", _materialFront)
    , materialBack("materialBack", _materialBack)
    , materialCenterFront("materialCenterFront", _materialCenterFront)
    , materialBorderFront("materialBorderFront", _materialBorderFront)
    , materialCenterBack("materialCenterBack ", _materialCenterBack)
    , materialBorderBack("materialBorderBack ", _materialBorderBack)
{
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&radius);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialFront);
    addProperty(&materialBack);
    addProperty(&materialCenterFront);
    addProperty(&materialBorderFront);
    addProperty(&materialCenterBack);
    addProperty(&materialBorderBack);
}

void ItemCircleArc::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    static const float _2PI = float(2.0 * M_PI);
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    float as = angleStart.value(_timeStep);
    float ae = angleEnd.value(_timeStep);
    if (Math::equals(as, ae))
        return;

    if (Math::isMoreOrEqual(std::abs(ae - as), _2PI))
    {
        as = 0.0f;
        ae = _2PI;
    }

    Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);
    const CircleArc::ShowCircleArcType st = show.valueEnum<CircleArc::ShowCircleArcType>(_timeStep);

    switch (st)
    {
    case CircleArc::CircleArcFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(OpenGL::Data3DMaterialBase::circleArc(o, as, ae, r, q, materialFront.value(_timeStep), a));
            _data.push_back(
                OpenGL::Data3DMaterialBase::circleArc(o.invert12(), -as, -ae, r, q, materialBack.value(_timeStep), a));
        }
    }
    break;
    case CircleArc::CircleArcFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::circleArc(o, as, ae, r, q, materialFront.value(_timeStep), a));
    }
    break;
    case CircleArc::CircleArcBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(
                OpenGL::Data3DMaterialBase::circleArc(o.invert12(), -as, -ae, r, q, materialBack.value(_timeStep), a));
    }
    break;

    case CircleArc::CircleArcBorderFrontBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circleArc(
            o, as, ae, r, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circleArc(
            o.invert12(), -as, -ae, r, q, materialCenterBack.value(_timeStep), materialBorderBack.value(_timeStep)));
        break;

    case CircleArc::CircleArcBorderFront:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circleArc(
            o, as, ae, r, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        break;

    case CircleArc::CircleArcBorderBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circleArc(
            o.invert12(), -as, -ae, r, q, materialCenterBack.value(_timeStep), materialBorderBack.value(_timeStep)));
        break;
    }
}

ItemCircleArcCamera::ItemCircleArcCamera(const std::string &_name,
                                         const Math::Vec3F &_center,
                                         const float _angleStart,
                                         const float _angleEnd,
                                         const float _radius,
                                         const size_t _quality,
                                         const CircleArc::ShowCircleArcCameraType _show,
                                         const Math::MaterialRGB &_material,
                                         const Math::MaterialRGBA &_materialCenter,
                                         const Math::MaterialRGBA &_materialBorder,
                                         const uint8_t _alpha,
                                         const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , center("center", _center)
    , angleStart("angleStart", _angleStart)
    , angleEnd("angleEnd", _angleEnd)
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<CircleArc::ShowCircleArcCameraType>(), _show)
    , material("material", _material)
    , materialCenter("materialCenter", _materialCenter)
    , materialBorder("materialBorder", _materialBorder)
{
    addProperty(&center);
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&radius);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&material);
    addProperty(&materialCenter);
    addProperty(&materialBorder);
}

void ItemCircleArcCamera::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                         const Math::CamF &_camera,
                                         const size_t _timeStep) const
{
    static const float _2PI = float(2.0 * M_PI);
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    float as = angleStart.value(_timeStep);
    float ae = angleEnd.value(_timeStep);
    if (Math::equals(as, ae))
        return;

    if (Math::isMoreOrEqual(std::abs(ae - as), _2PI))
    {
        as = 0.0f;
        ae = _2PI;
    }

    Math::OrientF o(_camera, center.value(_timeStep));
    o.normal2.invert();
    const size_t q = quality.value(_timeStep);
    const CircleArc::ShowCircleArcCameraType st = show.valueEnum<CircleArc::ShowCircleArcCameraType>(_timeStep);

    switch (st)
    {
    case CircleArc::CircleArcCameraSingle: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::circleArc(o, as, ae, r, q, material.value(_timeStep), a));
    }
    break;

    case CircleArc::CircleArcCameraBorder:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::circleArc(
            o, as, ae, r, q, materialCenter.value(_timeStep), materialBorder.value(_timeStep)));
        break;
    }
}

}  // namespace Items
}  // namespace U1
