/*!
 * \file src/Items/Circle/itemirregellipse.cpp
 * \brief Dynamic ellipse video item
 */

#include "itemirregellipse.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialsalpha.h"
#include "../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

ItemIrregEllipse::ItemIrregEllipse(const std::string &_name,
                                   const Math::Vec3F &_center,
                                   const Math::Vec3F &_normal,
                                   const Math::Vec3F &_arm,
                                   const float _radius1P,
                                   const float _radius1M,
                                   const float _radius2P,
                                   const float _radius2M,
                                   const size_t _quality,
                                   const Ellipse::ShowEllipseType _show,
                                   const Math::MaterialRGB &_materialFront,
                                   const Math::MaterialRGB &_materialBack,
                                   const Math::MaterialRGBA &_materialCenterFront,
                                   const Math::MaterialRGBA &_materialBorderFront,
                                   const Math::MaterialRGBA &_materialCenterBack,
                                   const Math::MaterialRGBA &_materialBorderBack,
                                   const uint8_t _alpha,
                                   const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , radius1P("radius1P", _radius1P, 0.0f, std::numeric_limits<float>::max())
    , radius1M("radius1M", _radius1M, 0.0f, std::numeric_limits<float>::max())
    , radius2P("radius2P", _radius2P, 0.0f, std::numeric_limits<float>::max())
    , radius2M("radius2M", _radius2M, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Ellipse::ShowEllipseType>(), _show)
    , materialFront("materialFront", _materialFront)
    , materialBack("materialBack", _materialBack)
    , materialCenterFront("materialCenterFront", _materialCenterFront)
    , materialBorderFront("materialBorderFront", _materialBorderFront)
    , materialCenterBack("materialCenterBack ", _materialCenterBack)
    , materialBorderBack("materialBorderBack ", _materialBorderBack)
{
    addProperty(&radius1P);
    addProperty(&radius1M);
    addProperty(&radius2P);
    addProperty(&radius2M);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialFront);
    addProperty(&materialBack);
    addProperty(&materialCenterFront);
    addProperty(&materialBorderFront);
    addProperty(&materialCenterBack);
    addProperty(&materialBorderBack);
}

void ItemIrregEllipse::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r1p = radius1P.value(_timeStep);
    if (!Math::isPositive(r1p))
        return;

    const float r1m = radius1M.value(_timeStep);
    if (!Math::isPositive(r1m))
        return;

    const float r2p = radius2P.value(_timeStep);
    if (!Math::isPositive(r2p))
        return;

    const float r2m = radius2M.value(_timeStep);
    if (!Math::isPositive(r2m))
        return;

    Math::OrientF o = valueOrientation(_timeStep);
    const size_t q = quality.value(_timeStep);

    const Ellipse::ShowEllipseType st = show.valueEnum<Ellipse::ShowEllipseType>(_timeStep);

    switch (st)
    {
    case Ellipse::EllipseFrontBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
        {
            _data.push_back(
                OpenGL::Data3DMaterialBase::irregEllipse(o, r1p, r1m, r2p, r2m, q, materialFront.value(_timeStep), a));
            _data.push_back(OpenGL::Data3DMaterialBase::irregEllipse(
                o.invert12(), r1p, r1m, r2p, r2m, q, materialBack.value(_timeStep), a));
        }
    }
    break;

    case Ellipse::EllipseFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(
                OpenGL::Data3DMaterialBase::irregEllipse(o, r1p, r1m, r2p, r2m, q, materialFront.value(_timeStep), a));
    }
    break;

    case Ellipse::EllipseBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::irregEllipse(
                o.invert12(), r1p, r1m, r2p, r2m, q, materialBack.value(_timeStep), a));
    }
    break;

    case Ellipse::EllipseBorderFrontBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::irregEllipse(
            o, r1p, r1m, r2p, r2m, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        _data.push_back(OpenGL::Data3DMaterialsAlpha::irregEllipse(o.invert12(),
                                                                   r1p,
                                                                   r1m,
                                                                   r2p,
                                                                   r2m,
                                                                   q,
                                                                   materialCenterBack.value(_timeStep),
                                                                   materialBorderBack.value(_timeStep)));
        break;

    case Ellipse::EllipseBorderFront:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::irregEllipse(
            o, r1p, r1m, r2p, r2m, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        break;

    case Ellipse::EllipseBorderBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::irregEllipse(o.invert12(),
                                                                   r1p,
                                                                   r1m,
                                                                   r2p,
                                                                   r2m,
                                                                   q,
                                                                   materialCenterBack.value(_timeStep),
                                                                   materialBorderBack.value(_timeStep)));
        break;
    }

}

ItemIrregEllipseCamera::ItemIrregEllipseCamera(const std::string &_name,
                                               const Math::Vec3F &_center,
                                               const float _radius1P,
                                               const float _radius1M,
                                               const float _radius2P,
                                               const float _radius2M,
                                               const size_t _quality,
                                               const Ellipse::ShowEllipseCameraType _show,
                                               const Math::MaterialRGB &_material,
                                               const Math::MaterialRGBA &_materialCenter,
                                               const Math::MaterialRGBA &_materialBorder,
                                               const uint8_t _alpha,
                                               const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , center("center", _center)
    , radius1P("radius1P", _radius1P, 0.0f, std::numeric_limits<float>::max())
    , radius1M("radius1M", _radius1M, 0.0f, std::numeric_limits<float>::max())
    , radius2P("radius2P", _radius2P, 0.0f, std::numeric_limits<float>::max())
    , radius2M("radius2M", _radius2M, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Ellipse::ShowEllipseCameraType>(), _show)
    , material("material", _material)
    , materialCenter("materialCenter", _materialCenter)
    , materialBorder("materialBorder", _materialBorder)
{
    addProperty(&center);
    addProperty(&radius1P);
    addProperty(&radius1M);
    addProperty(&radius2P);
    addProperty(&radius2M);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&material);
    addProperty(&materialCenter);
    addProperty(&materialBorder);
}

void ItemIrregEllipseCamera::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                            const Math::CamF &_camera,
                                            const size_t _timeStep) const
{
    const float r1p = radius1P.value(_timeStep);
    if (!Math::isPositive(r1p))
        return;

    const float r1m = radius1M.value(_timeStep);
    if (!Math::isPositive(r1m))
        return;

    const float r2p = radius2P.value(_timeStep);
    if (!Math::isPositive(r2p))
        return;

    const float r2m = radius2M.value(_timeStep);
    if (!Math::isPositive(r2m))
        return;

    const Math::OrientF o(_camera, center.value(_timeStep));
    const size_t q = quality.value(_timeStep);
    const Ellipse::ShowEllipseCameraType st = show.valueEnum<Ellipse::ShowEllipseCameraType>(_timeStep);

    switch (st)
    {
    case Ellipse::EllipseCameraSingle: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(
                OpenGL::Data3DMaterialBase::irregEllipse(o, r1p, r1m, r2p, r2m, q, material.value(_timeStep), a));
    }
    break;

    case Ellipse::EllipseCameraBorder:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::irregEllipse(
            o, r1p, r1m, r2p, r2m, q, materialCenter.value(_timeStep), materialBorder.value(_timeStep)));
        break;
    }

}

}  // namespace Items
}  // namespace U1
