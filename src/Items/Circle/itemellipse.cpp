/*!
 * \file src/Items/Circle/itemellipse.cpp
 * \brief Dynamic ellipse video item
 */

#include "itemellipse.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialsalpha.h"
#include "../../Data3D/data3dmaterialnormal.h"

namespace U1 {
namespace Items {

ItemEllipse::ItemEllipse(const std::string &_name,
                         const Math::Vec3F &_center,
                         const Math::Vec3F &_normal,
                         const Math::Vec3F &_arm,
                         const float _radius1,
                         const float _radius2,
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
    , radius1("radius1", _radius1, 0.0f, std::numeric_limits<float>::max())
    , radius2("radius2", _radius2, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Ellipse::ShowEllipseType>(), _show)
    , materialFront("materialFront", _materialFront)
    , materialBack("materialBack", _materialBack)
    , materialCenterFront("materialCenterFront", _materialCenterFront)
    , materialBorderFront("materialBorderFront", _materialBorderFront)
    , materialCenterBack("materialCenterBack ", _materialCenterBack)
    , materialBorderBack("materialBorderBack ", _materialBorderBack)
{
    addProperty(&radius1);
    addProperty(&radius2);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&materialFront);
    addProperty(&materialBack);
    addProperty(&materialCenterFront);
    addProperty(&materialBorderFront);
    addProperty(&materialCenterBack);
    addProperty(&materialBorderBack);
}

void ItemEllipse::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r1 = radius1.value(_timeStep);
    if (!Math::isPositive(r1))
        return;

    const float r2 = radius2.value(_timeStep);
    if (!Math::isPositive(r2))
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
            _data.push_back(OpenGL::Data3DMaterialBase::ellipse(o, r1, r2, q, materialFront.value(_timeStep), a));
            _data.push_back(
                OpenGL::Data3DMaterialBase::ellipse(o.invert12(), r1, r2, q, materialBack.value(_timeStep), a));
        }
    }
    break;

    case Ellipse::EllipseFront: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::ellipse(o, r1, r2, q, materialFront.value(_timeStep), a));
    }
    break;

    case Ellipse::EllipseBack: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(
                OpenGL::Data3DMaterialBase::ellipse(o.invert12(), r1, r2, q, materialBack.value(_timeStep), a));
    }
    break;

    case Ellipse::EllipseBorderFrontBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::ellipse(
            o, r1, r2, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        _data.push_back(OpenGL::Data3DMaterialsAlpha::ellipse(
            o.invert12(), r1, r2, q, materialCenterBack.value(_timeStep), materialBorderBack.value(_timeStep)));
        break;

    case Ellipse::EllipseBorderFront:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::ellipse(
            o, r1, r2, q, materialCenterFront.value(_timeStep), materialBorderFront.value(_timeStep)));
        break;

    case Ellipse::EllipseBorderBack:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::ellipse(
            o.invert12(), r1, r2, q, materialCenterBack.value(_timeStep), materialBorderBack.value(_timeStep)));
        break;
    }

}

ItemEllipseCamera::ItemEllipseCamera(const std::string &_name,
                                     const Math::Vec3F &_center,
                                     const float _radius1,
                                     const float _radius2,
                                     const size_t _quality,
                                     const Ellipse::ShowEllipseCameraType _show,
                                     const Math::MaterialRGB &_material,
                                     const Math::MaterialRGBA &_materialCenter,
                                     const Math::MaterialRGBA &_materialBorder,
                                     const uint8_t _alpha,
                                     const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , center("center", _center)
    , radius1("radius1", _radius1, 0.0f, std::numeric_limits<float>::max())
    , radius2("radius2", _radius2, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , show("show", QMetaEnum::fromType<Ellipse::ShowEllipseCameraType>(), _show)
    , material("material", _material)
    , materialCenter("materialCenter", _materialCenter)
    , materialBorder("materialBorder", _materialBorder)
{
    addProperty(&center);
    addProperty(&radius1);
    addProperty(&radius2);
    addProperty(&quality);
    addProperty(&show);
    addProperty(&material);
    addProperty(&materialCenter);
    addProperty(&materialBorder);
}

void ItemEllipseCamera::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                       const Math::CamF &_camera,
                                       const size_t _timeStep) const
{
    const float r1 = radius1.value(_timeStep);
    if (!Math::isPositive(r1))
        return;

    const float r2 = radius2.value(_timeStep);
    if (!Math::isPositive(r2))
        return;

    const Math::OrientF o(_camera, center.value(_timeStep));
    const size_t q = quality.value(_timeStep);
    const Ellipse::ShowEllipseCameraType st = show.valueEnum<Ellipse::ShowEllipseCameraType>(_timeStep);

    switch (st)
    {
    case Ellipse::EllipseCameraSingle: {
        const uint8_t a = alpha.value(_timeStep);
        if (a > 0U)
            _data.push_back(OpenGL::Data3DMaterialBase::ellipse(o, r1, r2, q, material.value(_timeStep), a));
    }
    break;

    case Ellipse::EllipseCameraBorder:
        _data.push_back(OpenGL::Data3DMaterialsAlpha::ellipse(
            o, r1, r2, q, materialCenter.value(_timeStep), materialBorder.value(_timeStep)));
        break;
    }

}

}  // namespace Items
}  // namespace U1
