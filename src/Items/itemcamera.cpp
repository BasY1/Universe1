/*!
 * \file src/Items/itemcamera.h
 * \brief Video camera item
 */

#include "itemcamera.h"

#include "../Data3D/data3dmaterialbase.h"
#include "../Data3D/data3dmaterialnormal.h"
#include "../Data3D/data3dtexture.h"

namespace U1 {
namespace Items {

ItemCamera::ItemCamera(const std::string &_name,
                       const Math::Vec3F &_position,
                       const Math::Vec3F &_lookAt,
                       const Math::Vec3F &_up,
                       const float _fieldOfView,
                       const float _nearPlane,
                       const float _farPlane,
                       const uint32_t _imageWidth,
                       const uint32_t _imageHeight,
                       const float _imagePixelSize,
                       const bool _imagePositionDynamic,
                       const float _bodySize,
                       const float _radiusWire,
                       const size_t _quality,
                       const size_t _qualityWire,
                       const bool _showImage,
                       const bool _showBody,
                       const bool _showViewArrow,
                       const bool _showViewPyramid,
                       const Math::MaterialRGB &_materialBody1,
                       const Math::MaterialRGB &_materialBody2,
                       const Math::MaterialRGB &_materialWire,
                       const uint8_t _alpha,
                       const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , position("position", _position)
    , lookAt("lookAt", _lookAt)
    , up("up", true, _up)
    , fieldOfView("fieldOfView", _fieldOfView, 5.0, 175.0f)
    , nearPlane("nearPlane", _nearPlane, 0.00001f, std::numeric_limits<float>::max())
    , farPlane("farPlane", _farPlane, 0.1f, std::numeric_limits<float>::max())
    , imageWidth("imageWidth", _imageWidth, 640U, 7680U)
    , imageHeight("imageHeight", _imageHeight, 480U, 4320U)
    , imagePixelSize("imagePixelSize", _imagePixelSize, 0.0f, std::numeric_limits<float>::max())
    , imagePositionDynamic("imagePositionDynamic", _imagePositionDynamic)
    , bodySize("bodySize", _bodySize, 0.0f, std::numeric_limits<float>::max())
    , radiusWire("radiusWire", _radiusWire, 0.0f, std::numeric_limits<float>::max())
    , quality("quality", _quality)
    , qualityWire("qualityWire", _qualityWire)
    , showImage("showImage", _showImage)
    , showBody("showBody", _showBody)
    , showViewArrow("showViewArrow", _showViewArrow)
    , showViewPyramid("showViewPyramid", _showViewPyramid)
    , materialBody1("materialBody1", _materialBody1)
    , materialBody2("materialBody2", _materialBody2)
    , materialWire("materialWire", _materialWire)
{
    addProperty(&position);
    addProperty(&lookAt);
    addProperty(&up);
    addProperty(&fieldOfView);
    addProperty(&nearPlane);
    addProperty(&farPlane);
    addProperty(&imageWidth);
    addProperty(&imageHeight);
    addProperty(&imagePixelSize);
    addProperty(&imagePositionDynamic);
    addProperty(&bodySize);
    addProperty(&radiusWire);
    addProperty(&quality);
    addProperty(&qualityWire);
    addProperty(&showImage);
    addProperty(&showBody);
    addProperty(&showViewArrow);
    addProperty(&showViewPyramid);
    addProperty(&materialBody1);
    addProperty(&materialBody2);
    addProperty(&materialWire);
}

void ItemCamera::createDataImpl(std::list<OpenGL::Data3D *> &_out, const size_t _timeStep) const
{
    static const float _2PI = 2.0f * M_PI;
    const uint8_t a = alpha.value(_timeStep);
    if (a == 0UL)
        return;

    bool sb = showBody.value(_timeStep);
    bool sa = showViewArrow.value(_timeStep);
    bool sp = showViewPyramid.value(_timeStep);
    if (!sb && !sa && !sp)
        return;

    const Math::CamF c = getCamera(_timeStep);
    const Math::Vec3F cf = (c.lookAt - c.position).normalized();
    const Math::Vec3F cr = Math::Vec3F::cross(cf, c.up).normalized();
    const Math::Vec3F cu = Math::Vec3F::cross(cr, cf).normalized();
    const float mwh = float(std::max(c.screenWidth, c.screenHeight));
    if (sb)
    {
        const float r = bodySize.value(_timeStep);
        if (Math::isPositive(r))
        {
            const Math::MaterialRGB m1 = materialBody1.value(_timeStep);
            const Math::MaterialRGB m2 = materialBody2.value(_timeStep);
            const size_t q = quality.value(_timeStep);
            const float w2 = r * 0.5f * float(c.screenWidth) / mwh;
            const float h2 = r * 0.5f * float(c.screenHeight) / mwh;
            const float zz = r * 0.2f;
            const float ro = std::min(r * 0.3f, std::min(w2, h2) * 0.9f);
            const float hl = std::min(r * 0.1f, std::min(w2, h2) * 0.2f);
            const float rl = (ro * ro + hl * hl) / (2.0f * hl);
            const float al = std::atan2(ro, rl - hl);
            const float z2 = hl + zz * 0.5f;
            const Math::OrientF o1(c.position - cf * hl, cf, cr);
            const Math::OrientF o2(c.position - cf * (hl + zz), -cf, cr);
            const Math::OrientF o3(c.position - cf * z2 + cr * w2, cr, cf);
            const Math::OrientF o4(c.position - cf * z2 - cr * w2, -cr, cf);
            const Math::OrientF o5(c.position - cf * z2 + cu * h2, cu, cr);
            const Math::OrientF o6(c.position - cf * z2 - cu * h2, -cu, cr);
            const Math::OrientF os(c.position - cf * rl, cf, cu);
            _out.push_back(OpenGL::Data3DMaterialBase::rectangle(o1, w2, h2, m1, a));
            _out.push_back(OpenGL::Data3DMaterialBase::rectangle(o2, w2, h2, m1, a));
            _out.push_back(OpenGL::Data3DMaterialBase::rectangle(o3, z2, h2, m1, a));
            _out.push_back(OpenGL::Data3DMaterialBase::rectangle(o4, z2, h2, m1, a));
            _out.push_back(OpenGL::Data3DMaterialBase::rectangle(o5, w2, z2, m1, a));
            _out.push_back(OpenGL::Data3DMaterialBase::rectangle(o6, w2, z2, m1, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::sphereArc(os, 0, _2PI, 0, al, rl, q, m2, a));
        }
    }

    if (!sa && !sp)
        return;

    const float r = radiusWire.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const size_t q = qualityWire.value(_timeStep);
    const Math::MaterialRGB ml = materialWire.value(_timeStep);

    if (sa)
        _out.push_back(OpenGL::Data3DMaterialNormal::line(c.position, c.lookAt, r, r, q, ml, a));

    if (sp)
    {

        const float fov = fieldOfView.value(_timeStep);
        const float pn = nearPlane.value(_timeStep);
        const float pf = farPlane.value(_timeStep);

        const float aw = Math::toRad(fov * 0.5f * float(c.screenWidth) / mwh);
        const float ah = Math::toRad(fov * 0.5f * float(c.screenHeight) / mwh);
        const float dnw = pn / std::cos(aw);
        const float dnh = pn / std::cos(ah);
        const float dfw = pf / std::cos(aw);
        const float dfh = pf / std::cos(ah);

        const Math::Vec3F nw1 = cf.rotated(cu, -aw).normalized();
        const Math::Vec3F nw2 = cf.rotated(cu, aw).normalized();
        const Math::Vec3F nh1 = cf.rotated(cr, ah).normalized();
        const Math::Vec3F nh2 = cf.rotated(cr, -ah).normalized();

        const Math::Vec3F pnw1 = c.position + nw1 * dnw;
        const Math::Vec3F pnw2 = c.position + nw2 * dnw;
        const Math::Vec3F pnh1 = c.position + nh1 * dnh;
        const Math::Vec3F pnh2 = c.position + nh2 * dnh;

        const Math::Vec3F pfw1 = c.position + nw1 * dfw;
        const Math::Vec3F pfw2 = c.position + nw2 * dfw;
        const Math::Vec3F pfh1 = c.position + nh1 * dfh;
        const Math::Vec3F pfh2 = c.position + nh2 * dfh;

        const Math::Vec3F nnn = (pnw2 - pnw1) * 0.5f;
        const Math::Vec3F nnf = (pfw2 - pfw1) * 0.5f;

        const Math::Vec3F pn1 = pnh1 + nnn;
        const Math::Vec3F pn2 = pnh2 + nnn;
        const Math::Vec3F pn3 = pnh2 - nnn;
        const Math::Vec3F pn4 = pnh1 - nnn;

        const Math::Vec3F pf1 = pfh1 + nnf;
        const Math::Vec3F pf2 = pfh2 + nnf;
        const Math::Vec3F pf3 = pfh2 - nnf;
        const Math::Vec3F pf4 = pfh1 - nnf;

        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn1, pf1, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn2, pf2, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn3, pf3, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn4, pf4, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn1, pn2, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn2, pn3, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn3, pn4, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pn4, pn1, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pf1, pf2, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pf2, pf3, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pf3, pf4, r, r, q, ml, a));
        _out.push_back(OpenGL::Data3DMaterialNormal::line(pf4, pf1, r, r, q, ml, a));
    }
}

void ItemCamera::createTexture(std::list<OpenGL::Data3D *> &_out,
                               QOpenGLTexture *_texture,
                               const Math::CamF &_mainViewCamera,
                               const size_t _timeStep)
{
    if (!showImage.value(_timeStep))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0UL)
        return;

    const float ps = imagePixelSize.value(_timeStep);
    if (!Math::isPositive(ps))
        return;

    const Math::CamF c = getCamera(_timeStep);
    const Math::Vec3F cf = (c.lookAt - c.position).normalized();
    const Math::Vec3F cr = Math::Vec3F::cross(cf, c.up).normalized();
    const Math::Vec3F cu = Math::Vec3F::cross(cr, cf).normalized();
    const bool dyn = imagePositionDynamic.value(_timeStep);
    const bool sb = showBody.value(_timeStep);
    const float rb = bodySize.value(_timeStep);
    const bool isBody = sb && Math::isPositive(rb);
    const float mwh = float(std::max(c.screenWidth, c.screenHeight));
    const float w2 = rb * 0.5f * float(c.screenWidth) / mwh;
    const float h2 = rb * 0.5f * float(c.screenHeight) / mwh;
    const float zz = rb * 0.2f;
    const float hl = std::min(rb * 0.1f, std::min(w2, h2) * 0.2f);

    const float uw = float(c.screenWidth) * ps;
    const float uh = float(c.screenHeight) * ps;

    if (isBody)
    {
        static const float angleLook = Math::toRad(80.0f);
        const bool showOnBody = !dyn ||
            Math::isLessOrEqual((-cf).angleRad(_mainViewCamera.position - (c.position - cf * (hl + zz)).normalized()),
                                angleLook);

        if (showOnBody)
        {
            const float w22 = w2 * 0.98f;
            const float h22 = h2 * 0.98f;
            const Math::OrientF o(c.position - cf * (hl + zz + rb * 0.01f), -cf, cr);
            _out.push_back(OpenGL::Data3DTexture::rectangle(_texture, o, w22, h22, a));
        }
        else
        {
            const Math::Vec3F pp = c.position + cu * (rb * 0.55f);
            const Math::Vec3F cf2 = (_mainViewCamera.position - pp).normalized();
            const Math::Vec3F cr2 = Math::Vec3F::cross(cf2, _mainViewCamera.up).normalized();
            const Math::Vec3F cu2 = Math::Vec3F::cross(cr2, cf2).normalized();
            const Math::OrientF o(pp, cf2, -cr2);

            _out.push_back(OpenGL::Data3DTexture::rectangle(_texture, o, (uw * 0.5f), (uh * 0.5f), a));

            const float lr = radiusWire.value(_timeStep);
            if (Math::isPositive(lr))
            {
                const size_t q = qualityWire.value(_timeStep);
                const Math::MaterialRGB ml = materialWire.value(_timeStep);
                const Math::Vec3F p1 = pp + cr2 * (uw * 0.5f) + cu2 * uh;
                const Math::Vec3F p2 = pp + cr2 * (uw * 0.5f);
                const Math::Vec3F p3 = pp - cr2 * (uw * 0.5f);
                const Math::Vec3F p4 = pp - cr2 * (uw * 0.5f) + cu2 * uh;
                _out.push_back(OpenGL::Data3DMaterialNormal::line(p1, p2, lr, lr, q, ml, a));
                _out.push_back(OpenGL::Data3DMaterialNormal::line(p2, p3, lr, lr, q, ml, a));
                _out.push_back(OpenGL::Data3DMaterialNormal::line(p3, p4, lr, lr, q, ml, a));
                _out.push_back(OpenGL::Data3DMaterialNormal::line(p4, p1, lr, lr, q, ml, a));
            }
        }
    }
    else if (dyn)
    {
        const Math::Vec3F pp = c.position;
        const Math::Vec3F cf2 = (_mainViewCamera.position - pp).normalized();
        const Math::Vec3F cr2 = Math::Vec3F::cross(cf2, _mainViewCamera.up).normalized();
        const Math::Vec3F cu2 = Math::Vec3F::cross(cr2, cf2).normalized();
        const Math::OrientF o(pp, cf2, -cr2);
        _out.push_back(OpenGL::Data3DTexture::rectangle(_texture, o, (uw * 0.5f), (uh * 0.5f), a));

        const float lr = radiusWire.value(_timeStep);
        if (Math::isPositive(lr))
        {
            const size_t q = qualityWire.value(_timeStep);
            const Math::MaterialRGB ml = materialWire.value(_timeStep);
            const Math::Vec3F p1 = pp + cr2 * (uw * 0.5f) + cu2 * uh;
            const Math::Vec3F p2 = pp + cr2 * (uw * 0.5f);
            const Math::Vec3F p3 = pp - cr2 * (uw * 0.5f);
            const Math::Vec3F p4 = pp - cr2 * (uw * 0.5f) + cu2 * uh;
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p1, p2, lr, lr, q, ml, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p2, p3, lr, lr, q, ml, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p3, p4, lr, lr, q, ml, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p4, p1, lr, lr, q, ml, a));
        }
    }
    else
    {
        const Math::OrientF o(c.position, -cf, cr);
        _out.push_back(OpenGL::Data3DTexture::rectangle(_texture, o, (uw * 0.5f), (uh * 0.5f), a));

        const float lr = radiusWire.value(_timeStep);
        if (Math::isPositive(lr))
        {
            const size_t q = qualityWire.value(_timeStep);
            const Math::MaterialRGB ml = materialWire.value(_timeStep);
            const Math::Vec3F p1 = c.position + cr * (uw * 0.5f) + cu * uh;
            const Math::Vec3F p2 = c.position + cr * (uw * 0.5f);
            const Math::Vec3F p3 = c.position - cr * (uw * 0.5f);
            const Math::Vec3F p4 = c.position - cr * (uw * 0.5f) + cu * uh;
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p1, p2, lr, lr, q, ml, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p2, p3, lr, lr, q, ml, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p3, p4, lr, lr, q, ml, a));
            _out.push_back(OpenGL::Data3DMaterialNormal::line(p4, p1, lr, lr, q, ml, a));
        }
    }
}

}  // namespace Items
}  // namespace U1
