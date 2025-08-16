/*!
 * \file src/Items/Line/itemarc.cpp
 * \brief Dynamic 3D line arc video item
 */

#include "itemarc.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialnormal.h"
#include "../Text/itemtext.h"

namespace U1 {
namespace Items {

ItemArc::ItemArc(const std::string &_name,
                 const Math::Vec3F &_center,
                 const Math::Vec3F &_normal,
                 const Math::Vec3F &_arm,
                 const float _angle,
                 const float _radiusArc,
                 const float _radiusLine,
                 const uint64_t _pattern,
                 const uint64_t _qualityArc,
                 const uint64_t _qualityLine,
                 const bool _arrowStart,
                 const bool _arrowEnd,
                 const float _arrowLength,
                 const float _arrowRadius,
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
    , angle("angle", _angle, 0.0f, std::numeric_limits<float>::max())
    , radiusArc("radiusArc", _radiusArc, 0.0f, std::numeric_limits<float>::max())
    , radiusLine("radiusLine", _radiusLine, 0.0f, std::numeric_limits<float>::max())
    , pattern("pattern", _pattern)
    , qualityArc("qualityArc ", _qualityArc)
    , qualityLine("qualityLine", _qualityLine)
    , arrowStart("arrowStart", _arrowStart)
    , arrowEnd("arrowEnd", _arrowEnd)
    , arrowLength("arrowLength", _arrowLength, 0.0f, std::numeric_limits<float>::max())
    , arrowRadius("arrowRadius", _arrowRadius, 0.0f, std::numeric_limits<float>::max())
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
    addProperty(&angle);
    addProperty(&radiusArc);
    addProperty(&radiusLine);
    addProperty(&pattern);
    addProperty(&qualityArc);
    addProperty(&qualityLine);
    addProperty(&arrowStart);
    addProperty(&arrowEnd);
    addProperty(&arrowLength);
    addProperty(&arrowRadius);
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

void ItemArc::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float aa = angle.value(_timeStep);
    if (!Math::isPositive(aa))
        return;

    const float ra = radiusArc.value(_timeStep);
    if (!Math::isPositive(ra))
        return;

    const float rl = radiusLine.value(_timeStep);
    if (!Math::isPositive(rl))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const size_t qa = qualityArc.value(_timeStep);
    const size_t ql = qualityLine.value(_timeStep);
    const bool as = arrowStart.value(_timeStep);
    const bool ae = arrowEnd.value(_timeStep);
    const float al = (as || ae) ? arrowLength.value(_timeStep) : 0.0f;
    const float ar = (as || ae) ? arrowRadius.value(_timeStep) : 0.0f;
    const bool canAddArrows = Math::isPositive(al) && Math::isPositive(ar);

    const Math::MaterialRGB m1 = material.value(_timeStep);
    const Math::MaterialRGB m2 = materialBack.value(_timeStep);
    const Math::MaterialRGB ma = (as || ae) ? materialArrow.value(_timeStep) : Math::MaterialRGB();
    const float l = aa * ra;

    bool asArrow = false, aeArrow = false;
    float os = 0.0f, ol = l;
    if (canAddArrows)
    {
        if (as && ae)
        {
            if (Math::isMoreNotEqual(l, al * 3.0f))
            {
                asArrow = true;
                aeArrow = true;
                os = al;
                ol = l - 2.0f * al;
            }
        }
        else if (as)
        {
            if (Math::isMoreNotEqual(l, al * 2.0f))
            {
                asArrow = true;
                os = al;
                ol = l - al;
            }
        }
        else if (ae)
        {
            if (Math::isMoreNotEqual(l, al * 2.0f))
            {
                aeArrow = true;
                ol = l - al;
            }
        }
    }

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, p, os, os + ol, rl);

    for (size_t i = 0UL; i < dp.size(); ++i)
    {
        _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(
            o, dp[i].second - dp[i].first, ra, rl, rl, qa, ql, m1, a, dp[i].first / ra));

        const float ias = dp[i].first / ra;
        const Math::Vec3F ns1 = o.normal2.rotated(o.normal1, ias).normalized();
        const Math::Vec3F ns2 = Math::Vec3F::cross(ns1, o.normal1).normalized();
        _data.push_back(OpenGL::Data3DMaterialBase::circle({o.center + ns1 * ra, ns2, ns1}, rl, ql, m2, a));

        const float iae = dp[i].second / ra;
        const Math::Vec3F ne1 = o.normal2.rotated(o.normal1, iae).normalized();
        const Math::Vec3F ne2 = -Math::Vec3F::cross(ne1, o.normal1).normalized();
        _data.push_back(OpenGL::Data3DMaterialBase::circle({o.center + ne1 * ra, ne2, ne1}, rl, ql, m2, a));
    }

    if (canAddArrows)
    {
        if (as)
        {
            if (asArrow)
            {
                const float ia = al / ra;
                const Math::Vec3F ne1 = o.normal2.rotated(o.normal1, ia).normalized();
                const Math::Vec3F ne2 = Math::Vec3F::cross(ne1, o.normal1).normalized();
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(o, al, ra, 0.0f, ar, qa, ql, ma, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({o.center + ne1 * ra, -ne2, ne1}, ar, ql, m2, a));
            }
            else
            {
                const Math::Vec3F p1 = o.center + o.normal2 * ra - o.normal1 * (ar * 0.5f);
                const Math::Vec3F p2 = o.center + o.normal2 * ra + o.normal1 * (ar * 0.5f);
                const Math::Vec3F p3 = o.center + o.normal2 * (ra - ar * 0.5f);
                const Math::Vec3F p4 = o.center + o.normal2 * (ra + ar * 0.5f);
                _data.push_back(
                    OpenGL::Data3DMaterialNormal::cylinder({p1, o.normal1, o.normal2}, ar, rl, rl, ql, ma, a));
                _data.push_back(
                    OpenGL::Data3DMaterialNormal::cylinder({p3, o.normal2, o.normal1}, ar, rl, rl, ql, ma, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p1, -o.normal1, o.normal2}, rl, ql, m2, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p2, o.normal1, o.normal2}, rl, ql, m2, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p3, -o.normal2, o.normal1}, rl, ql, m2, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p4, o.normal2, o.normal1}, rl, ql, m2, a));
            }
        }

        if (ae)
        {
            if (aeArrow)
            {
                const float ia = (l - al) / ra;
                const Math::Vec3F ne1 = o.normal2.rotated(o.normal1, ia).normalized();
                const Math::Vec3F ne2 = -Math::Vec3F::cross(ne1, o.normal1).normalized();
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinderArc(o, al, ra, ar, 0.0f, qa, ql, ma, a, ia));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({o.center + ne1 * ra, -ne2, ne1}, ar, ql, m2, a));
            }
            else
            {
                const Math::Vec3F ne2 = o.normal2.rotated(o.normal1, aa).normalized();
                const Math::Vec3F p1 = o.center + ne2 * ra - o.normal1 * (ar * 0.5f);
                const Math::Vec3F p2 = o.center + ne2 * ra + o.normal1 * (ar * 0.5f);
                const Math::Vec3F p3 = o.center + ne2 * (ra - ar * 0.5f);
                const Math::Vec3F p4 = o.center + ne2 * (ra + ar * 0.5f);
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder({p1, o.normal1, ne2}, ar, rl, rl, ql, ma, a));
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder({p3, ne2, o.normal1}, ar, rl, rl, ql, ma, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p1, -o.normal1, ne2}, rl, ql, m2, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p2, o.normal1, ne2}, rl, ql, m2, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p3, -ne2, o.normal1}, rl, ql, m2, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle({p4, ne2, o.normal1}, rl, ql, m2, a));
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

    Math::Vec3F pp;
    Math::Vec3F nn;
    switch (tp)
    {
    case Line::LineTextHidden: break;
    case Line::LineTextStart:
        pp = o.center + o.normal2 * ra;
        nn = -o.normal2;
        break;
    case Line::LineTextCenter:
        nn = -o.normal2.rotated(o.normal1, aa * 0.5f);
        pp = o.center - nn * ra;
        break;
    case Line::LineTextEnd:
        nn = -o.normal2.rotated(o.normal1, aa);
        pp = o.center - nn * ra;
        break;
    }

    const Math::Vec3F nn2 = Math::Vec3F::cross(o.normal1, nn);

    ItemText::createText(_data, {pp, nn, nn2}, txt, c, a, ff, fh, bo, ps, at, true);
    ItemText::createText(_data, {pp, nn, nn2}, txt, c, a, ff, fh, bo, ps, at, false);
}

void ItemArc::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                             const Math::CamF &_camera,
                             const size_t _timeStep) const
{
    if (!textFollowCamera.value(_timeStep))
        return;

    const float aa = angle.value(_timeStep);
    if (!Math::isPositive(aa))
        return;

    const float ra = radiusArc.value(_timeStep);
    if (!Math::isPositive(ra))
        return;

    const float rl = radiusLine.value(_timeStep);
    if (!Math::isPositive(rl))
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
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = textColor.value(_timeStep);

    replaceText(txt, aa);

    Math::Vec3F PP = {};
    switch (tp)
    {
    case Line::LineTextHidden: break;
    case Line::LineTextStart: PP = o1.center + o1.normal2 * ra; break;
    case Line::LineTextCenter: PP = o1.center + o1.normal2.rotated(o1.normal1, aa * 0.5f).normalized() * ra; break;
    case Line::LineTextEnd: PP = o1.center + o1.normal2.rotated(o1.normal1, aa).normalized() * ra; break;
    }

    const Math::OrientF o2 = Math::OrientF(_camera, PP);

    Math::AlignType at = Math::_AlignBottomCenter;
    if (textAutoAlign.value(_timeStep))
    {
        static const float detRot = M_PI / 36.0f;
        switch (tp)
        {
        case Line::LineTextHidden: break;
        case Line::LineTextStart: {
            // const Math::Vec3F P1 = o1.center + o1.arm1 * r;
            const Math::Vec3F P2 = o1.center + o1.normal2.rotated(o1.normal1, detRot) * ra;
            const Math::Vec2F p1 = {PP.distanceToPlane(_camera.position, o2.normal2),
                                    PP.distanceToPlane(_camera.position, o2.normal3)};
            const Math::Vec2F p2 = {P2.distanceToPlane(_camera.position, o2.normal2),
                                    P2.distanceToPlane(_camera.position, o2.normal3)};
            const Math::Vec2F pn = -(p2 - p1).normalized();
            const bool sx = !Math::isNegative(pn.x), sy = !Math::isNegative(pn.y);
            if (sx && sy)
                at = Math::_AlignBottomLeft;
            else if (sx && !sy)
                at = Math::_AlignTopLeft;
            else if (!sx && sy)
                at = Math::_AlignBottomRight;
            else
                at = Math::_AlignTopRight;
        }
        break;

        case Line::LineTextCenter: {
            const Math::Vec3F P1 = o1.center + o1.normal2.rotated(o1.normal1, aa * 0.5 - detRot) * ra;
            const Math::Vec3F P2 = o1.center + o1.normal2.rotated(o1.normal1, aa * 0.5 + detRot) * ra;
            const Math::Vec2F p1 = {P1.distanceToPlane(_camera.position, o2.normal2),
                                    P1.distanceToPlane(_camera.position, o2.normal3)};
            const Math::Vec2F p2 = {P2.distanceToPlane(_camera.position, o2.normal2),
                                    P2.distanceToPlane(_camera.position, o2.normal3)};
            const Math::Vec2F pn = (p2 - p1).normalized();
            const bool sx = !Math::isNegative(pn.x), sy = !Math::isNegative(pn.y);
            if (sx && sy)
                at = Math::_AlignBottomRight;
            else if (sx && !sy)
                at = Math::_AlignBottomRight;
            else if (!sx && sy)
                at = Math::_AlignBottomLeft;
            else
                at = Math::_AlignBottomLeft;
        }
        break;
        case Line::LineTextEnd: {
            // const Math::Vec3F P1 = o1.center + o1.arm1.rotated(o1.normal, aa) * r;
            const Math::Vec3F P2 = o1.center + o1.normal2.rotated(o1.normal1, aa - detRot) * ra;
            const Math::Vec2F p1 = {PP.distanceToPlane(_camera.position, o2.normal2),
                                    PP.distanceToPlane(_camera.position, o2.normal3)};
            const Math::Vec2F p2 = {P2.distanceToPlane(_camera.position, o2.normal2),
                                    P2.distanceToPlane(_camera.position, o2.normal3)};
            const Math::Vec2F pn = (p2 - p1).normalized();
            const bool sx = !Math::isNegative(pn.x), sy = !Math::isNegative(pn.y);
            if (!sx && !sy)
                at = Math::_AlignBottomLeft;
            else if (!sx && sy)
                at = Math::_AlignTopLeft;
            else if (sx && !sy)
                at = Math::_AlignBottomRight;
            else
                at = Math::_AlignTopRight;
        }
        break;
        }
    }
    else
    {
        at = textAlign.valueEnum<Math::AlignType>(_timeStep);
    }

    ItemText::createText(_data, o2, txt, c, a, ff, fh, bo, ps, at, true);
}

void ItemArc::replaceText(QString &txt, const float a)
{
    qsizetype idxStart = 0;
    while (true)
    {
        const qsizetype idxBeg = txt.indexOf("$$$", idxStart);
        if (idxBeg < 0)
            return;

        const qsizetype idxEnd = txt.indexOf("$", idxBeg + 3);
        if (idxEnd < 0)
        {
            std::cerr << "Error: ItemArc::replaceText(): Missing key end [$$$]!\n";
            return;
        }

        const QString key = txt.mid(idxBeg + 3, idxEnd - idxBeg - 3);
        const QString keyEnd = txt.mid(idxEnd, 3);
        const qsizetype keyLen = idxEnd + 3 - idxBeg;

        if (key == "ANGLE_RAD")
        {
            if (!ItemLine::replaceTextValue(txt, idxBeg, keyLen, keyEnd, a))
            {
                std::cerr << "Error: ItemArc::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else if (key == "ANGLE_DEG")
        {
            if (!ItemLine::replaceTextValue(txt, idxBeg, keyLen, keyEnd, Math::toDeg(a)))
            {
                std::cerr << "Error: ItemArc::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else
        {
            std::cerr << "Error: ItemArc::replaceText(): Unknown key $$$" << key.toStdString() << keyEnd.toStdString()
                      << "!\n";
            return;
        }

        idxStart = idxBeg;
    }
}

}  // namespace Items
}  // namespace U1
