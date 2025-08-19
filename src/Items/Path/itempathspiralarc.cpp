/*!
 * \file src/Items/Path/itempathspiralarc.cpp
 * \brief Dynamic 3D line arc spiral path video item
 */

#include "itempathspiralarc.h"

#include "itempath.h"

namespace U1 {
namespace Items {

ItemPathSpiralArc::ItemPathSpiralArc(const std::string &_name,
                                     const Math::Vec3F &_center,
                                     const Math::Vec3F &_normal,
                                     const Math::Vec3F &_arm,
                                     const bool _sign,
                                     const float _angleStart,
                                     const float _angleEnd,
                                     const float _length,
                                     const float _radiusArc,
                                     const float _radiusSpiral,
                                     const float _radiusLine,
                                     const uint64_t _pattern,
                                     const uint64_t _quality,
                                     const uint64_t _qualityLine,
                                     const Math::MaterialRGB &_material,
                                     const uint8_t _alpha,
                                     const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , sign(_name + ".sign", _sign)
    , angleStart(_name + ".angleStart", _angleStart)
    , angleEnd(_name + ".angleEnd", _angleEnd)
    , length(_name + ".length", _length, 0.0f, std::numeric_limits<float>::max())
    , radiusArc(_name + ".radiusArc", _radiusArc, 0.0f, std::numeric_limits<float>::max())
    , radiusSpiral(_name + ".radiusSpiral", _radiusSpiral, 0.0f, std::numeric_limits<float>::max())
    , radiusLine(_name + ".radiusLine", _radiusLine, 0.0f, std::numeric_limits<float>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , qualityLine(_name + ".qualityLine", _qualityLine)
    , material(_name + ".material", _material)
{
    addProperty(&sign);
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&length);
    addProperty(&radiusArc);
    addProperty(&radiusSpiral);
    addProperty(&radiusLine);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&qualityLine);
    addProperty(&material);
}

ItemPathSpiralArc2Color::ItemPathSpiralArc2Color(const std::string &_name,
                                                 const Math::Vec3F &_center,
                                                 const Math::Vec3F &_normal,
                                                 const Math::Vec3F &_arm,
                                                 const bool _sign,
                                                 const float _angleStart,
                                                 const float _angleEnd,
                                                 const float _length,
                                                 const float _radiusArc,
                                                 const float _radiusSpiral,
                                                 const float _radiusLine,
                                                 const uint64_t _pattern,
                                                 const uint64_t _quality,
                                                 const uint64_t _qualityLine,
                                                 const Math::ColorRGB &_colorStart,
                                                 const Math::ColorRGB &_colorEnd,
                                                 const uint8_t _alpha,
                                                 const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , sign(_name + ".sign", _sign)
    , angleStart(_name + ".angleStart", _angleStart)
    , angleEnd(_name + ".angleEnd", _angleEnd)
    , length(_name + ".length", _length, 0.0f, std::numeric_limits<float>::max())
    , radiusArc(_name + ".radiusArc", _radiusArc, 0.0f, std::numeric_limits<float>::max())
    , radiusSpiral(_name + ".radiusSpiral", _radiusSpiral, 0.0f, std::numeric_limits<float>::max())
    , radiusLine(_name + ".radiusLine", _radiusLine, 0.0f, std::numeric_limits<float>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , qualityLine(_name + ".qualityLine", _qualityLine)
    , colorStart(_name + ".colorStart", _colorStart)
    , colorEnd(_name + ".colorEnd", _colorEnd)
{
    addProperty(&sign);
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&length);
    addProperty(&radiusArc);
    addProperty(&radiusSpiral);
    addProperty(&radiusLine);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&qualityLine);
    addProperty(&colorStart);
    addProperty(&colorEnd);
}

ItemPathSpiralArcRainbow::ItemPathSpiralArcRainbow(const std::string &_name,
                                                   const Math::Vec3F &_center,
                                                   const Math::Vec3F &_normal,
                                                   const Math::Vec3F &_arm,
                                                   const bool _sign,
                                                   const float _angleStart,
                                                   const float _angleEnd,
                                                   const float _length,
                                                   const float _radiusArc,
                                                   const float _radiusSpiral,
                                                   const float _radiusLine,
                                                   const uint64_t _pattern,
                                                   const uint64_t _quality,
                                                   const uint64_t _qualityLine,
                                                   const uint8_t _alpha,
                                                   const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , sign(_name + ".sign", _sign)
    , angleStart(_name + ".angleStart", _angleStart)
    , angleEnd(_name + ".angleEnd", _angleEnd)
    , length(_name + ".length", _length, 0.0f, std::numeric_limits<float>::max())
    , radiusArc(_name + ".radiusArc", _radiusArc, 0.0f, std::numeric_limits<float>::max())
    , radiusSpiral(_name + ".radiusSpiral", _radiusSpiral, 0.0f, std::numeric_limits<float>::max())
    , radiusLine(_name + ".radiusLine", _radiusLine, 0.0f, std::numeric_limits<float>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , qualityLine(_name + ".qualityLine", _qualityLine)
{
    addProperty(&sign);
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&length);
    addProperty(&radiusArc);
    addProperty(&radiusSpiral);
    addProperty(&radiusLine);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&qualityLine);
}

void ItemPathSpiralArc::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float as = angleStart.value(_timeStep);
    const float ae = angleEnd.value(_timeStep);
    const float ra = radiusArc.value(_timeStep);
    const float rs = radiusSpiral.value(_timeStep);
    const float rl = radiusLine.value(_timeStep);
    if (Math::equals(as, ae) || !Math::isPositive(ra) || !Math::isPositive(rs) || !Math::isPositive(rl))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const bool s = sign.value(_timeStep);
    const float l = length.value(_timeStep);
    const size_t q = quality.value(_timeStep);
    const size_t ql = qualityLine.value(_timeStep);
    const Math::MaterialRGB m = material.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<Math::OrientF> path;
    o.createSpiralArcPath(path, pathCenter, pathLength, s, l, ra, rs, as, ae, q);
    ItemPath::createPath(_data, path, pathCenter, pathLength, rl, p, ql, m, a);
}

void ItemPathSpiralArc2Color::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float as = angleStart.value(_timeStep);
    const float ae = angleEnd.value(_timeStep);
    const float ra = radiusArc.value(_timeStep);
    const float rs = radiusSpiral.value(_timeStep);
    const float rl = radiusLine.value(_timeStep);
    if (Math::equals(as, ae) || !Math::isPositive(ra) || !Math::isPositive(rs) || !Math::isPositive(rl))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const bool s = sign.value(_timeStep);
    const float l = length.value(_timeStep);
    const size_t q = quality.value(_timeStep);
    const size_t ql = qualityLine.value(_timeStep);
    const Math::ColorRGB c1 = colorStart.value(_timeStep);
    const Math::ColorRGB c2 = colorEnd.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path;
    o.createSpiralArcPath(path, pathCenter, pathLength, s, l, ra, rs, as, ae, q, c1, c2);
    ItemPathColor::createPath(_data, path, pathCenter, pathLength, rl, p, ql, a);
}

void ItemPathSpiralArcRainbow::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float as = angleStart.value(_timeStep);
    const float ae = angleEnd.value(_timeStep);
    const float ra = radiusArc.value(_timeStep);
    const float rs = radiusSpiral.value(_timeStep);
    const float rl = radiusLine.value(_timeStep);
    if (Math::equals(as, ae) || !Math::isPositive(ra) || !Math::isPositive(rs) || !Math::isPositive(rl))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const bool s = sign.value(_timeStep);
    const float l = length.value(_timeStep);
    const size_t q = quality.value(_timeStep);
    const size_t ql = qualityLine.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path;
    o.createSpiralArcPathRainbow(path, pathCenter, pathLength, s, l, ra, rs, as, ae, q);
    ItemPathColor::createPath(_data, path, pathCenter, pathLength, rl, p, ql, a);
}

}  // namespace Items
}  // namespace U1
