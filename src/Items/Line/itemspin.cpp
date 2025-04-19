/*!
 * \file src/Items/Line/itemspin.cpp
 * \brief Dynamic 3D line spin video item
 */

#include "itemspin.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialnormal.h"
#include "../Text/itemtext.h"

namespace U1 {
namespace Items {

ItemSpin::ItemSpin(const std::string &_name,
                   const Math::Vec3F &_center,
                   const Math::Vec3F &_normal,
                   const Math::Vec3F &_arm,
                   const float _phase,
                   const float _length,
                   const float _radius,
                   const uint64_t _pattern,
                   const uint64_t _quality,
                   const uint8_t _arrowCount,
                   const float _arrowLength,
                   const float _arrowRadius,
                   const float _arrowOffsetLength,
                   const float _arrowOffsetAxis,
                   const uint64_t _arrowQuality,
                   const Math::MaterialRGB &_material,
                   const Math::MaterialRGB &_materialBack,
                   const Math::MaterialRGB &_materialArrow,
                   const QString &_text,
                   const Math::ColorRGB &_textColor,
                   const QString &_fontFamily,
                   const uint32_t _fontHeight,
                   const uint32_t _borderOffset,
                   const float _pixelSize,
                   const Line::LineTextPosition _textPosition,
                   const Math::AlignType _textAlign,
                   const bool _textAutoAlign,
                   const bool _textFollowCamera,
                   const uint8_t _alpha,
                   const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , phase("phase", _phase)
    , length("length", _length, 0.0f, std::numeric_limits<float>::max())
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , pattern("pattern", _pattern)
    , quality("quality", _quality)
    , arrowCount("arrowCount", _arrowCount)
    , arrowLength("arrowLength", _arrowLength, 0.0f, std::numeric_limits<float>::max())
    , arrowRadius("arrowRadius", _arrowRadius, 0.0f, std::numeric_limits<float>::max())
    , arrowOffsetLength("arrowOffsetLength", _arrowOffsetLength)
    , arrowOffsetAxis("arrowOffsetAxis", _arrowOffsetAxis, 0.0f, std::numeric_limits<float>::max())
    , arrowQuality("arrowQuality", _arrowQuality)
    , material("material", _material)
    , materialBack("materialBack", _materialBack)
    , materialArrow("materialArrow", _materialArrow)
    , text("text", _text)
    , textColor("textColor", _textColor)
    , fontFamily("fontFamily", _fontFamily)
    , fontHeight("fontHeight", _fontHeight)
    , borderOffset("borderOffset", _borderOffset)
    , pixelSize("pixelSize", _pixelSize, 0.0f, std::numeric_limits<float>::max())
    , textPosition("textPosition", QMetaEnum::fromType<Line::LineTextPosition>(), _textPosition)
    , textAlign("textAlign", QMetaEnum::fromType<Math::AlignType>(), _textAlign)
    , textAutoAlign("textAutoAlign", _textAutoAlign)
    , textFollowCamera("textFollowCamera", _textFollowCamera)
{
    addProperty(&phase);
    addProperty(&length);
    addProperty(&radius);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&arrowCount);
    addProperty(&arrowLength);
    addProperty(&arrowRadius);
    addProperty(&arrowOffsetLength);
    addProperty(&arrowOffsetAxis);
    addProperty(&arrowQuality);
    addProperty(&material);
    addProperty(&materialBack);
    addProperty(&materialArrow);
    addProperty(&text);
    addProperty(&textColor);
    addProperty(&fontFamily);
    addProperty(&fontHeight);
    addProperty(&borderOffset);
    addProperty(&pixelSize);
    addProperty(&textPosition);
    addProperty(&textAlign);
    addProperty(&textAutoAlign);
    addProperty(&textFollowCamera);
}

void ItemSpin::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    static const float _2PI = float(2.0 * M_PI);

    const float l = length.value(_timeStep);
    if (!Math::isPositive(l))
        return;

    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const float aa = phase.value(_timeStep);
    const size_t q = quality.value(_timeStep);

    const Math::MaterialRGB m1 = material.value(_timeStep);
    const Math::MaterialRGB m2 = materialBack.value(_timeStep);

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, p, 0.0f, l, r);

    for (size_t i = 0UL; i < dp.size(); ++i)
    {
        _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
            {o.center + o.normal1 * dp[i].first, o.normal1, o.normal2, o.normal3},
            dp[i].second - dp[i].first,
            r,
            r,
            q,
            m1,
            a));

        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            {o.center + o.normal1 * dp[i].first, -o.normal1, -o.normal2, o.normal3}, r, q, m2, a));

        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            {o.center + o.normal1 * dp[i].second, o.normal1, o.normal2, o.normal3}, r, q, m2, a));
    }

    const uint8_t na = arrowCount.value(_timeStep);
    if (na > 0UL)
    {
        const float al = arrowLength.value(_timeStep);
        if (Math::isPositive(al))
        {
            const float ar = arrowRadius.value(_timeStep);
            if (Math::isPositive(ar))
            {
                const float aax = _2PI / float(na);
                const float aoa = r + ar + arrowOffsetAxis.value(_timeStep);
                const float aol = arrowOffsetLength.value(_timeStep);
                const size_t aq = arrowQuality.value(_timeStep);

                const Math::MaterialRGB ma = materialArrow.value(_timeStep);
                Math::OrientF o2(o.center + o.normal1 * aol, o.normal1, o.normal2, o.normal3);
                for (uint8_t ai = 0U; ai < na; ai++)
                {
                    const float aix = aa + aax * float(ai);
                    const float saix = std::sin(aix);
                    const float caix = std::cos(aix);
                    o2.normal2 = o.normal2.rotated(o.normal1, saix, caix);
                    o2.normal3 = o.normal3.rotated(o.normal1, saix, caix);
                    _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(o2, al, aoa, ar, 0.0f, aq, q, ma, a));

                    _data.push_back(
                        OpenGL::Data3DMaterialBase::circle({o2.center + o2.normal2 * aoa,
                                                            Math::Vec3F::cross(o2.normal2, o2.normal1).normalized(),
                                                            o2.normal2},
                                                           ar,
                                                           q,
                                                           m2,
                                                           a));
                }
            }
        }
    }

    if (textFollowCamera.value(_timeStep))
        return;

    const Line::LineTextPosition tp = textPosition.valueEnum<Line::LineTextPosition>(_timeStep);
    if (tp == Line::LineTextHidden)
        return;

    const float ps = pixelSize.value(_timeStep);
    if (!Math::isPositive(ps))
        return;

    const uint32_t fh = fontHeight.value(_timeStep);
    if (fh == 0U)
        return;

    QString txt = text.value(_timeStep);
    if (txt.isEmpty())
        return;

    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = textColor.value(_timeStep);
    const Math::AlignType at = textAlign.valueEnum<Math::AlignType>(_timeStep);

    replaceText(txt, aa);

    Math::Vec3F pp = {};
    switch (tp)
    {
    case Line::LineTextHidden: break;
    case Line::LineTextStart: pp = o.center; break;
    case Line::LineTextCenter: pp = o.center + o.normal1 * (l * 0.5f); break;
    case Line::LineTextEnd: pp = o.center + o.normal1 * l; break;
    }

    ItemText::createText(_data, {pp, o.normal1, o.normal2}, txt, c, a, ff, fh, bo, ps, at, true);
    ItemText::createText(_data, {pp, o.normal1, o.normal2}, txt, c, a, ff, fh, bo, ps, at, false);
}

void ItemSpin::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                              const Math::CamF &_camera,
                              const size_t _timeStep) const
{
    if (!textFollowCamera.value(_timeStep))
        return;

    const float l = length.value(_timeStep);
    if (!Math::isPositive(l))
        return;

    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Line::LineTextPosition tp = textPosition.valueEnum<Line::LineTextPosition>(_timeStep);
    if (tp == Line::LineTextHidden)
        return;

    const float ps = pixelSize.value(_timeStep);
    if (!Math::isPositive(ps))
        return;

    const uint32_t fh = fontHeight.value(_timeStep);
    if (fh == 0U)
        return;

    QString txt = text.value(_timeStep);
    if (txt.isEmpty())
        return;

    const Math::OrientF o1 = valueOrientation(_timeStep);
    const float aa = phase.value(_timeStep);
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = textColor.value(_timeStep);
    const Math::Vec3F P1 = o1.center;
    const Math::Vec3F P2 = o1.center + o1.normal1 * l;
    Math::Vec3F PP = {};

    replaceText(txt, aa);

    switch (tp)
    {
    case Line::LineTextHidden: break;
    case Line::LineTextStart: PP = P1; break;
    case Line::LineTextCenter: PP = (P1 + P2) * 0.5f; break;
    case Line::LineTextEnd: PP = P2; break;
    }

    const Math::OrientF o2 = Math::OrientF(_camera, PP);

    Math::AlignType at = Math::_AlignBottomCenter;

    if (textAutoAlign.value(_timeStep))
    {
        if (tp == Line::LineTextCenter)
        {
            at = Math::_AlignBottomCenter;
        }
        else
        {
            const Math::Vec3F cp = _camera.position;
            const Math::Vec3F cf = (_camera.lookAt - cp).normalized();
            const Math::Vec3F cr = Math::Vec3F::cross(cf, _camera.up).normalized();
            const Math::Vec3F cu = Math::Vec3F::cross(cr, cf).normalized();
            const Math::Vec2F p1 = {P1.distanceToPlane(cp, cr), P1.distanceToPlane(cp, cu)};
            const Math::Vec2F p2 = {P2.distanceToPlane(cp, cr), P2.distanceToPlane(cp, cu)};
            const Math::Vec2F pn = (p2 - p1).normalized() * ((tp == Line::LineTextStart) ? -1.0f : 1.0f);
            const bool sx = !Math::isNegative(pn.x), sy = !Math::isNegative(pn.y);
            if (Math::isMoreOrEqual(std::abs(pn.x), 0.5f) && Math::isMoreOrEqual(std::abs(pn.y), 0.5f))
            {
                if (sx && sy)
                    at = Math::_AlignBottomLeft;
                else if (sx && !sy)
                    at = Math::_AlignTopLeft;
                else if (!sx && sy)
                    at = Math::_AlignBottomRight;
                else
                    at = Math::_AlignTopRight;
            }
            else if (std::abs(pn.x) > std::abs(pn.y))
            {
                at = sx ? Math::_AlignCenterLeft : Math::_AlignCenterRight;
            }
            else
            {
                at = sy ? Math::_AlignBottomCenter : Math::_AlignTopCenter;
            }
        }
    }
    else
    {
        at = textAlign.valueEnum<Math::AlignType>(_timeStep);
    }

    ItemText::createText(_data, o2, txt, c, a, ff, fh, bo, ps, at, true);
}

}  // namespace Items
}  // namespace U1
