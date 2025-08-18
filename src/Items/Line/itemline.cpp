/*!
 * \file src/Items/Line/itemline.cpp
 * \brief Dynamic 3D line video item
 */

#include "itemline.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialnormal.h"
#include "../Text/itemtext.h"

namespace U1 {
namespace Items {

bool ItemLine::replaceTextValue(
    QString &_txt, const qsizetype _from, const qsizetype _count, const QString &_keyEnd, const float _value)
{
    if (_keyEnd == "$$$")
        _txt.replace(_from, _count, QString::number(_value));
    else if (_keyEnd == "$0$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 0));
    else if (_keyEnd == "$1$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 1));
    else if (_keyEnd == "$2$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 2));
    else if (_keyEnd == "$3$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 3));
    else if (_keyEnd == "$4$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 4));
    else if (_keyEnd == "$5$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 5));
    else if (_keyEnd == "$6$")
        _txt.replace(_from, _count, QString::number(_value, 'f', 6));
    else
        return false;

    return true;
}

bool ItemLine::replaceTextValue(
    QString &_txt, const qsizetype _from, const qsizetype _count, const QString &_keyEnd, const Math::Vec3F &_value)
{
    if (_keyEnd == "$$$")
        _txt.replace(_from, _count, _value.toQString());
    else if (_keyEnd == "$0$")
        _txt.replace(_from, _count, _value.toQString(0));
    else if (_keyEnd == "$1$")
        _txt.replace(_from, _count, _value.toQString(1));
    else if (_keyEnd == "$2$")
        _txt.replace(_from, _count, _value.toQString(2));
    else if (_keyEnd == "$3$")
        _txt.replace(_from, _count, _value.toQString(3));
    else if (_keyEnd == "$4$")
        _txt.replace(_from, _count, _value.toQString(4));
    else if (_keyEnd == "$5$")
        _txt.replace(_from, _count, _value.toQString(5));
    else if (_keyEnd == "$6$")
        _txt.replace(_from, _count, _value.toQString(6));
    else
        return false;

    return true;
}

void ItemLine::replaceText(QString &txt, const Math::OrientF &o, const float l)
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
            std::cerr << "Error: ItemLine::replaceText(): Missing key end [$$$]!\n";
            return;
        }

        const QString key = txt.mid(idxBeg + 3, idxEnd - idxBeg - 3);
        const QString keyEnd = txt.mid(idxEnd, 3);
        const qsizetype keyLen = idxEnd + 3 - idxBeg;

        if (key == "P1")
        {
            if (!replaceTextValue(txt, idxBeg, keyLen, keyEnd, o.center))
            {
                std::cerr << "Error: ItemLine::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else if (key == "P2")
        {
            if (!replaceTextValue(txt, idxBeg, keyLen, keyEnd, o.center + o.normal1 * l))
            {
                std::cerr << "Error: ItemLine::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else if (key == "NORMAL")
        {
            if (!replaceTextValue(txt, idxBeg, keyLen, keyEnd, o.normal1))
            {
                std::cerr << "Error: ItemLine::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else if (key == "LENGTH")
        {
            if (!replaceTextValue(txt, idxBeg, keyLen, keyEnd, l))
            {
                std::cerr << "Error: ItemLine::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else
        {
            std::cerr << "Error: ItemLine::replaceText(): Unknown key $$$" << key.toStdString() << keyEnd.toStdString()
                      << "!\n";
            return;
        }

        idxStart = idxBeg;
    }
}

ItemLine::ItemLine(const std::string &_name,
                   const Math::Vec3F &_center,
                   const Math::Vec3F &_normal,
                   const Math::Vec3F &_arm,
                   const float _length,
                   const float _radius,
                   const uint64_t _pattern,
                   const uint64_t _quality,
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
    , length(_name + ".length", _length, 0.0f, std::numeric_limits<float>::max())
    , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , arrowStart(_name + ".arrowStart", _arrowStart)
    , arrowEnd(_name + ".arrowEnd", _arrowEnd)
    , arrowLength(_name + ".arrowLength", _arrowLength, 0.0f, std::numeric_limits<float>::max())
    , arrowRadius(_name + ".arrowRadius", _arrowRadius, 0.0f, std::numeric_limits<float>::max())
    , material(_name + ".material", _material)
    , materialBack(_name + ".materialBack", _materialBack)
    , materialArrow(_name + ".materialArrow", _materialArrow)
    , text(_name + ".text", _text)
    , textColor(_name + ".textColor", _textColor)
    , fontFamily(_name + ".fontFamily", _fontFamily)
    , fontHeight(_name + ".fontHeight", _fontHeight)
    , borderOffset(_name + ".borderOffset", _borderOffset)
    , pixelSize(_name + ".pixelSize", _pixelSize, 0.0f, std::numeric_limits<float>::max())
    , textPosition(_name + ".textPosition", QMetaEnum::fromType<Line::LineTextPosition>(), _textPosition)
    , textAlign(_name + ".textAlign", QMetaEnum::fromType<Math::AlignType>(), _textAlign)
    , textAutoAlign(_name + ".textAutoAlign", _textAutoAlign)
    , textFollowCamera(_name + ".textFollowCamera", _textFollowCamera)
{
    addProperty(&length);
    addProperty(&radius);
    addProperty(&pattern);
    addProperty(&quality);
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

void ItemLine::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
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
    const size_t q = quality.value(_timeStep);
    const bool as = arrowStart.value(_timeStep);
    const bool ae = arrowEnd.value(_timeStep);
    const float al = (as || ae) ? arrowLength.value(_timeStep) : 0.0f;
    const float ar = (as || ae) ? arrowRadius.value(_timeStep) : 0.0f;
    const bool canAddArrows = Math::isPositive(al) && Math::isPositive(ar);

    const Math::MaterialRGB m1 = material.value(_timeStep);
    const Math::MaterialRGB m2 = materialBack.value(_timeStep);
    const Math::MaterialRGB ma = (as || ae) ? materialArrow.value(_timeStep) : Math::MaterialRGB();

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
    Math::fillDashPattern(dp, p, os, os + ol, r);

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

    if (canAddArrows)
    {
        if (as)
        {
            if (asArrow)
            {
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(o, al, 0.0f, ar, q, ma, a));
                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {o.center + o.normal1 * al, o.normal1, o.normal2, o.normal3}, ar, q, m2, a));
            }
            else
            {
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                    {o.center - o.normal2 * (ar * 0.5f), o.normal2, o.normal1}, ar, r, r, q, ma, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {o.center - o.normal2 * (ar * 0.5f), -o.normal2, o.normal1}, r, q, m2, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {o.center + o.normal2 * (ar * 0.5f), o.normal2, o.normal1}, r, q, m2, a));

                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                    {o.center - o.normal3 * (ar * 0.5f), o.normal3, o.normal1}, ar, r, r, q, ma, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {o.center - o.normal3 * (ar * 0.5f), -o.normal3, o.normal1}, r, q, m2, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {o.center + o.normal3 * (ar * 0.5f), o.normal3, o.normal1}, r, q, m2, a));
            }
        }

        if (ae)
        {
            if (aeArrow)
            {
                const Math::Vec3F pp = o.center + o.normal1 * (l - al);
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                    {pp, o.normal1, o.normal2, o.normal3}, al, ar, 0.0f, q, ma, a));
                _data.push_back(
                    OpenGL::Data3DMaterialBase::circle({pp, -o.normal1, -o.normal2, o.normal3}, ar, q, m2, a));
            }
            else
            {
                const Math::Vec3F pp = o.center + o.normal1 * l;
                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                    {pp - o.normal2 * (ar * 0.5f), o.normal2, o.normal1}, ar, r, r, q, ma, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {pp - o.normal2 * (ar * 0.5f), -o.normal2, o.normal1}, r, q, m2, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {pp + o.normal2 * (ar * 0.5f), o.normal2, o.normal1}, r, q, m2, a));

                _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                    {pp - o.normal3 * (ar * 0.5f), o.normal3, o.normal1}, ar, r, r, q, ma, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {pp - o.normal3 * (ar * 0.5f), -o.normal3, o.normal1}, r, q, m2, a));

                _data.push_back(OpenGL::Data3DMaterialBase::circle(
                    {pp + o.normal3 * (ar * 0.5f), o.normal3, o.normal1}, r, q, m2, a));
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

    replaceText(txt, o, l);

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

void ItemLine::createDataImpl(std::list<OpenGL::Data3D *> &_data,
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
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = textColor.value(_timeStep);
    const Math::Vec3F P1 = o1.center;
    const Math::Vec3F P2 = o1.center + o1.normal1 * l;
    Math::Vec3F PP = {};

    replaceText(txt, o1, l);

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

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ItemCoordAxis::ItemCoordAxis(const std::string &_name,
                             const Math::Vec3F &_center,
                             const Math::Vec3F &_normal,
                             const Math::Vec3F &_arm,
                             const float _length,
                             const float _radius,
                             const float _arrowLength,
                             const float _arrowRadius,
                             const uint64_t _pattern,
                             const uint64_t _quality,
                             const bool _arrowShow,
                             const bool _textShow,
                             const Math::MaterialRGB &_materialX,
                             const Math::MaterialRGB &_materialY,
                             const Math::MaterialRGB &_materialZ,
                             const Math::ColorRGB &_textColorX,
                             const Math::ColorRGB &_textColorY,
                             const Math::ColorRGB &_textColorZ,
                             const QString &_fontFamily,
                             const uint32_t _fontHeight,
                             const uint32_t _borderOffset,
                             const float _pixelSize,
                             const uint8_t _alpha,
                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , length(_name + ".length", _length, 0.0f, std::numeric_limits<float>::max())
    , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , arrowLength(_name + ".arrowLength", _arrowLength, 0.0f, std::numeric_limits<float>::max())
    , arrowRadius(_name + ".arrowRadius", _arrowRadius, 0.0f, std::numeric_limits<float>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , arrowShow(_name + ".arrowShow", _arrowShow)
    , textShow(_name + ".textShow", _textShow)
    , materialX(_name + ".materialX", _materialX)
    , materialY(_name + ".materialY", _materialY)
    , materialZ(_name + ".materialZ", _materialZ)
    , textColorX(_name + ".textColorX", _textColorX)
    , textColorY(_name + ".textColorY", _textColorY)
    , textColorZ(_name + ".textColorZ", _textColorZ)
    , fontFamily(_name + ".fontFamily", _fontFamily)
    , fontHeight(_name + ".fontHeight", _fontHeight)
    , borderOffset(_name + ".borderOffset", _borderOffset)
    , pixelSize(_name + ".pixelSize", _pixelSize, 0.0f, std::numeric_limits<float>::max())
{
    addProperty(&length);
    addProperty(&radius);
    addProperty(&arrowLength);
    addProperty(&arrowRadius);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&arrowShow);
    addProperty(&textShow);
    addProperty(&materialX);
    addProperty(&materialY);
    addProperty(&materialZ);
    addProperty(&textColorX);
    addProperty(&textColorY);
    addProperty(&textColorZ);
    addProperty(&fontFamily);
    addProperty(&fontHeight);
    addProperty(&borderOffset);
    addProperty(&pixelSize);
}

void ItemCoordAxis::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float l = length.value(_timeStep);
    if (!Math::isPositive(l))
        return;

    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    struct TmpArrowData
    {
        const Math::MaterialRGB material1;
        const Math::MaterialRGB material2;
        const Math::Vec3F normal1;
        const Math::Vec3F normal2;
        const Math::Vec3F normal3;
        inline TmpArrowData(const Math::MaterialRGB &_material,
                            const Math::Vec3F &_normal1,
                            const Math::Vec3F &_normal2)
            : material1(_material)
            , material2(_material.darker())
            , normal1(_normal1)
            , normal2(_normal2)
            , normal3(Math::Vec3F::cross(_normal1, _normal2).normalized())
        {
        }
    };

    const Math::OrientF o = valueOrientation(_timeStep);
    const std::vector<TmpArrowData> tmpArrows = {
        {materialX.value(_timeStep), o.normal1, o.normal2},
        {materialY.value(_timeStep), o.normal2, o.normal3},
        {materialZ.value(_timeStep), o.normal3, o.normal1},
    };

    const size_t q = quality.value(_timeStep);
    const float al = arrowLength.value(_timeStep);
    const float ar = arrowRadius.value(_timeStep);

    const bool useArrows = arrowShow.value(_timeStep) && Math::isPositive(al) && Math::isPositive(ar);

    const float ll = useArrows ? (std::max(0.0f, l - al)) : l;
    if (Math::isNull(ll))
    {
        for (const TmpArrowData &td : std::as_const(tmpArrows))
        {
            _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                {o.center, td.normal1, td.normal2, td.normal3}, l, ar, 0.0f, q, td.material1, a));

            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                {o.center, -td.normal1, -td.normal2, td.normal3}, ar, q, td.material2, a));
        }
        // Arrows only
        return;
    }

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, p, 0.0f, ll, r);

    for (const TmpArrowData &td : std::as_const(tmpArrows))
    {
        for (size_t i = 0UL; i < dp.size(); ++i)
        {
            _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                {o.center + td.normal1 * dp[i].first, td.normal1, td.normal2, td.normal3},
                dp[i].second - dp[i].first,
                r,
                r,
                q,
                td.material1,
                a));

            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                {o.center + td.normal1 * dp[i].first, -td.normal1, -td.normal2, td.normal3}, r, q, td.material2, a));

            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                {o.center + td.normal1 * dp[i].second, td.normal1, td.normal2, td.normal3}, r, q, td.material2, a));
        }

        if (useArrows)
        {
            const Math::Vec3F pp = o.center + td.normal1 * ll;
            _data.push_back(OpenGL::Data3DMaterialNormal::cylinder(
                {pp, td.normal1, td.normal2, td.normal3}, al, ar, 0.0f, q, td.material1, a));
            _data.push_back(
                OpenGL::Data3DMaterialBase::circle({pp, -td.normal1, -td.normal2, td.normal3}, ar, q, td.material2, a));
        }
    }
}

void ItemCoordAxis::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                   const Math::CamF &_camera,
                                   const size_t _timeStep) const
{
    if (!textShow.value(_timeStep))
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

    const float ps = pixelSize.value(_timeStep);
    if (!Math::isPositive(ps))
        return;

    const uint32_t fh = fontHeight.value(_timeStep);
    if (fh == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);

    struct TmpArrowData
    {
        const QString text;
        const Math::ColorRGB color;
        const Math::Vec3F center;
    };

    const std::vector<TmpArrowData> tmpArrows = {
        {"X", textColorX.value(_timeStep), o.center + o.normal1 * l},
        {"Y", textColorY.value(_timeStep), o.center + o.normal2 * l},
        {"Z", textColorZ.value(_timeStep), o.center + o.normal3 * l},
    };

    Math::AlignType at = Math::_AlignBottomCenter;

    for (const TmpArrowData &td : std::as_const(tmpArrows))
    {
        const Math::Vec3F cf = (_camera.lookAt - _camera.position).normalized();
        const Math::Vec3F cr = Math::Vec3F::cross(cf, _camera.up).normalized();
        const Math::Vec3F cu = Math::Vec3F::cross(cr, cf).normalized();
        const Math::Vec2F p1 = {o.center.distanceToPlane(_camera.position, cr),
                                o.center.distanceToPlane(_camera.position, cu)};
        const Math::Vec2F p2 = {td.center.distanceToPlane(_camera.position, cr),
                                td.center.distanceToPlane(_camera.position, cu)};
        const Math::Vec2F pn = (p2 - p1).normalized();
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

        const Math::OrientF o2 = Math::OrientF(_camera, td.center);
        ItemText::createText(_data, o2, td.text, td.color, a, ff, fh, bo, ps, at, true);
    }
}

}  // namespace Items
}  // namespace U1
