/*!
 * \file src/Items/Clock/itemclock.cpp
 * \brief Dynamic clock video item
 */

#include "itemclock.h"
#include "../Line/itemline.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialnormal.h"

#include "../Text/itemtext.h"

#include <QTime>

namespace U1 {
namespace Items {

ItemClock::ItemClock(const std::string &_name,
                     const Math::Vec3F &_center,
                     const Math::Vec3F &_normal,
                     const Math::Vec3F &_upDir,
                     const float _time,
                     const float _radius,
                     const size_t _quality,
                     const bool _bodyFollowCamera,
                     const bool _textFollowCamera,
                     const QString &_text,
                     const QString &_fontFamily,
                     const uint32_t _fontHeight,
                     const uint32_t _borderOffset,
                     const float _pixelSize,
                     const Math::ColorRGB &_textColor,
                     const Math::MaterialRGB &_materialBody,
                     const Math::MaterialRGB &_materialPlane,
                     const Math::MaterialRGB &_materialTick,
                     const Math::MaterialRGB &_materialSec,
                     const Math::MaterialRGB &_materialMin,
                     const Math::MaterialRGB &_materialHour,
                     const uint8_t _alpha,
                     const bool _visible)
    : Item3DExt(_name, _center, _normal, _upDir, _alpha, _visible)
    , time(_name + ".time", _time)
    , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , quality(_name + ".quality", _quality)
    , bodyFollowCamera(_name + ".bodyFollowCamera", _bodyFollowCamera)
    , textFollowCamera(_name + ".textFollowCamera", _textFollowCamera)
    , text(_name + ".text", _text)
    , fontFamily(_name + ".fontFamily", _fontFamily)
    , fontHeight(_name + ".fontHeight", _fontHeight)
    , borderOffset(_name + ".borderOffset", _borderOffset)
    , pixelSize(_name + ".pixelSize", _pixelSize, 0.0f, std::numeric_limits<float>::max())
    , textColor(_name + ".textColor", _textColor)
    , materialBody(_name + ".materialBody", _materialBody)
    , materialPlane(_name + ".materialPlane", _materialPlane)
    , materialTick(_name + ".materialTick", _materialTick)
    , materialSec(_name + ".materialSec", _materialSec)
    , materialMin(_name + ".materialMin", _materialMin)
    , materialHour(_name + ".materialHour", _materialHour)
{
    addProperty(&time);
    addProperty(&radius);
    addProperty(&quality);
    addProperty(&bodyFollowCamera);
    addProperty(&textFollowCamera);
    addProperty(&text);
    addProperty(&fontFamily);
    addProperty(&fontHeight);
    addProperty(&borderOffset);
    addProperty(&pixelSize);
    addProperty(&textColor);
    addProperty(&materialBody);
    addProperty(&materialPlane);
    addProperty(&materialTick);
    addProperty(&materialSec);
    addProperty(&materialMin);
    addProperty(&materialHour);
}

void ItemClock::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    if (bodyFollowCamera.value(_timeStep))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const float t = time.value(_timeStep);
    const float r = radius.value(_timeStep);
    if (Math::isPositive(r))
        createClockBody(_data,
                        o,
                        t,
                        r,
                        quality.value(_timeStep),
                        materialBody.value(_timeStep),
                        materialPlane.value(_timeStep),
                        materialTick.value(_timeStep),
                        materialSec.value(_timeStep),
                        materialMin.value(_timeStep),
                        materialHour.value(_timeStep),
                        a);

    if (textFollowCamera.value(_timeStep))
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

    replaceText(txt, t);

    static const Math::AlignType at = Math::_AlignBottomCenter;
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = textColor.value(_timeStep);
    const Math::Vec3F pp = o.center + o.normal2 * (r * 1.2f);

    ItemText::createText(_data, {pp, o.normal1, -o.normal3, o.normal2}, txt, c, a, ff, fh, bo, ps, at, true);
}

void ItemClock::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                               const Math::CamF &_camera,
                               const size_t _timeStep) const
{
    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    if (bodyFollowCamera.value(_timeStep))
    {
        const Math::OrientF o2 = Math::OrientF(_camera, center.value(_timeStep));
        const float t = time.value(_timeStep);
        const float r = radius.value(_timeStep);
        if (Math::isPositive(r))
            createClockBody(_data,
                            {o2.center, o2.normal1, o2.normal3, o2.normal2},
                            t,
                            r,
                            quality.value(_timeStep),
                            materialBody.value(_timeStep),
                            materialPlane.value(_timeStep),
                            materialTick.value(_timeStep),
                            materialSec.value(_timeStep),
                            materialMin.value(_timeStep),
                            materialHour.value(_timeStep),
                            a);

        const uint32_t fh = fontHeight.value(_timeStep);
        if (fh == 0U)
            return;

        const float ps = pixelSize.value(_timeStep);
        if (!Math::isPositive(ps))
            return;

        QString txt = text.value(_timeStep);
        if (txt.isEmpty())
            return;

        replaceText(txt, time.value(_timeStep));

        static const Math::AlignType at = Math::_AlignBottomCenter;
        const QString ff = fontFamily.value(_timeStep);
        const uint32_t bo = borderOffset.value(_timeStep);
        const Math::ColorRGB c = textColor.value(_timeStep);
        const Math::Vec3F pp = o2.center + o2.normal3 * (r * 1.2f);

        ItemText::createText(_data, {pp, o2.normal1, -o2.normal3, o2.normal2}, txt, c, a, ff, fh, bo, ps, at, true);
    }
    else if (textFollowCamera.value(_timeStep))
    {
        const uint32_t fh = fontHeight.value(_timeStep);
        if (fh == 0U)
            return;

        const float ps = pixelSize.value(_timeStep);
        if (!Math::isPositive(ps))
            return;

        QString txt = text.value(_timeStep);
        if (txt.isEmpty())
            return;

        replaceText(txt, time.value(_timeStep));

        const Math::OrientF o1 = valueOrientation(_timeStep);
        const float r = radius.value(_timeStep);
        const Math::Vec3F pp = o1.center + o1.normal2 * (r * 1.2f);
        const Math::OrientF o2 = Math::OrientF(_camera, pp);
        const QString ff = fontFamily.value(_timeStep);
        const uint32_t bo = borderOffset.value(_timeStep);
        const Math::ColorRGB c = textColor.value(_timeStep);
        static const Math::AlignType at = Math::_AlignBottomCenter;
        ItemText::createText(_data, o2, txt, c, a, ff, fh, bo, ps, at, true);
    }
}

void ItemClock::replaceText(QString &txt, const float _time)
{
    if (txt.isEmpty())
        return;

    qsizetype idxStart = 0;
    while (true)
    {
        const qsizetype idxBeg = txt.indexOf("$$$", idxStart);
        if (idxBeg < 0)
            return;

        const qsizetype idxEnd = txt.indexOf("$", idxBeg + 3);
        if (idxEnd < 0)
        {
            std::cerr << "Error: ItemClock::replaceText(): Missing key end [$$$]!\n";
            return;
        }

        const QString key = txt.mid(idxBeg + 3, idxEnd - idxBeg - 3);
        const QString keyEnd = txt.mid(idxEnd, 3);
        const qsizetype keyLen = idxEnd + 3 - idxBeg;

        if (key == "TIME")
        {
            if (!ItemLine::replaceTextValue(txt, idxBeg, keyLen, keyEnd, _time))
            {
                std::cerr << "Error: ItemClock::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else if (key == "CLOCK")
        {
            if (keyEnd == "$$$")
                txt.replace(
                    idxBeg,
                    keyLen,
                    (Math::isNegative(_time) ? "-" : "") +
                        QTime::fromMSecsSinceStartOfDay((int)(std::abs(_time) * 1000.0f)).toString("hh:mm:ss.zzz"));
            else
            {
                std::cerr << "Error: ItemClock::replaceText(): Unknown key end $$$" << key.toStdString()
                          << keyEnd.toStdString() << "!\n";
                return;
            }
        }
        else
        {
            std::cerr << "Error: ItemClock::replaceText(): Unknown key $$$" << key.toStdString() << keyEnd.toStdString()
                      << "!\n";
            return;
        }

        idxStart = idxBeg;
    }
}

void ItemClock::createClockBody(std::list<OpenGL::Data3D *> &_data,
                                const Math::OrientF &_orientation,
                                const float _time,
                                const float _radius,
                                const size_t _quality,
                                const Math::MaterialRGB &_materialBody,
                                const Math::MaterialRGB &_materialPlane,
                                const Math::MaterialRGB &_materialTick,
                                const Math::MaterialRGB &_materialSec,
                                const Math::MaterialRGB &_materialMin,
                                const Math::MaterialRGB &_materialHour,
                                const uint8_t _alpha)
{
    static const float _2PI = 2.0f * M_PI;
    static const float ANG = _2PI / 60.0f;

    const float ro1 = _radius * 0.95f;
    const float ro2 = _radius * 0.05f;
    const float ri1 = ro1 - ro2;
    const float ri2 = ri1 - _radius * 0.02f;
    const float hh = _radius * 0.12f;
    const float hm = _radius * 0.06f;
    const float wh = _radius * 0.025;
    const float wm = _radius * 0.011;
    const float o1 = _radius * 0.01;
    const float os = _radius * 0.02;
    const float om = _radius * 0.03;
    const float oh = _radius * 0.04;
    const float ls = _radius * 0.85;
    const float lm = _radius * 0.80;
    const float lh = _radius * 0.60;
    const float rs = _radius * 0.01;
    const float rm = _radius * 0.015;
    const float rh = _radius * 0.02;

    _data.push_back(
        OpenGL::Data3DMaterialNormal::torus(_orientation, ro1, ro2, _quality, _quality, _materialBody, _alpha));

    _data.push_back(OpenGL::Data3DMaterialBase::circle(
        {_orientation.center - _orientation.normal1 * ro2, -_orientation.normal1, _orientation.normal2},
        ro1,
        _quality,
        _materialBody,
        _alpha));

    _data.push_back(OpenGL::Data3DMaterialBase::circle(_orientation, ri1, _quality, _materialPlane, _alpha));

    Math::Vec3F a1, a2, p0, p1, p2, p3;

    for (uint i = 0U; i < 60U; ++i)
    {
        a1 = _orientation.normal2.rotated(_orientation.normal1, ANG * float(i)).normalized();
        a2 = Math::Vec3F::cross(_orientation.normal1, a1);
        const bool isHour = ((i % 5U) == 0U);
        const float w = isHour ? wh : wm;
        const float l = isHour ? hh : hm;
        p0 = _orientation.center + _orientation.normal1 * o1 + a1 * ri2 - a2 * (w * 0.5f);
        p1 = p0 + a2 * w;
        p2 = p1 - a1 * l;
        p3 = p0 - a1 * l;
        _data.push_back(OpenGL::Data3DMaterialBase::rectangle(p0, p1, p2, p3, _materialTick, _alpha));
    }

    a1 = _orientation.normal2.rotated(_orientation.normal1, -ANG * _time).normalized();
    a2 = Math::Vec3F::cross(_orientation.normal1, a1);
    p0 = _orientation.center + _orientation.normal1 * os + a1 * ls;
    p1 = _orientation.center + _orientation.normal1 * os + a1 * (ls * 0.5f) - a2 * rs;
    p2 = _orientation.center + _orientation.normal1 * os;
    p3 = _orientation.center + _orientation.normal1 * os + a1 * (ls * 0.5f) + a2 * rs;
    _data.push_back(OpenGL::Data3DMaterialBase::rectangle(p0, p3, p2, p1, _materialSec, _alpha));

    a1 = _orientation.normal2.rotated(_orientation.normal1, -ANG * _time / 60.0f).normalized();
    a2 = Math::Vec3F::cross(_orientation.normal1, a1);
    p0 = _orientation.center + _orientation.normal1 * om + a1 * lm;
    p1 = _orientation.center + _orientation.normal1 * om + a1 * (lm * 0.5f) - a2 * rm;
    p2 = _orientation.center + _orientation.normal1 * om;
    p3 = _orientation.center + _orientation.normal1 * om + a1 * (lm * 0.5f) + a2 * rm;
    _data.push_back(OpenGL::Data3DMaterialBase::rectangle(p0, p3, p2, p1, _materialMin, _alpha));

    a1 = _orientation.normal2.rotated(_orientation.normal1, -ANG * _time * 5.0f / 3600.0f).normalized();
    a2 = Math::Vec3F::cross(_orientation.normal1, a1);
    p0 = _orientation.center + _orientation.normal1 * oh + a1 * lh;
    p1 = _orientation.center + _orientation.normal1 * oh + a1 * (lh * 0.5f) - a2 * rh;
    p2 = _orientation.center + _orientation.normal1 * oh;
    p3 = _orientation.center + _orientation.normal1 * oh + a1 * (lh * 0.5f) + a2 * rh;
    _data.push_back(OpenGL::Data3DMaterialBase::rectangle(p0, p3, p2, p1, _materialHour, _alpha));
}

}  // namespace Items
}  // namespace U1
