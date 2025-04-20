/*!
 * \file src/Items/Path/itempathspiral.cpp
 * \brief Dynamic 3D line spiral path video item
 */

#include "itempathspiral.h"

#include "itempath.h"

namespace U1 {
namespace Items {

ItemPathSpiral::ItemPathSpiral(const std::string &_name,
                               const Math::Vec3F &_center,
                               const Math::Vec3F &_normal,
                               const Math::Vec3F &_arm,
                               const bool _sign,
                               const float _angleStart,
                               const float _angleEnd,
                               const float _length,
                               const float _radius,
                               const float _radiusLine,
                               const uint64_t _pattern,
                               const uint64_t _quality,
                               const uint64_t _qualityLine,
                               const Math::MaterialRGB &_material,
                               const uint8_t _alpha,
                               const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , sign("sign", _sign)
    , angleStart("angleStart", _angleStart)
    , angleEnd("angleEnd  ", _angleEnd)
    , length("length", _length, 0.0f, std::numeric_limits<float>::max())
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , radiusLine("radiusLine", _radiusLine, 0.0f, std::numeric_limits<float>::max())
    , pattern("pattern", _pattern)
    , quality("quality", _quality)
    , qualityLine("qualityLine", _qualityLine)
    , material("material", _material)
{
    addProperty(&sign);
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&length);
    addProperty(&radius);
    addProperty(&radiusLine);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&qualityLine);
    addProperty(&material);
}

ItemPathSpiralRainbow::ItemPathSpiralRainbow(const std::string &_name,
                                             const Math::Vec3F &_center,
                                             const Math::Vec3F &_normal,
                                             const Math::Vec3F &_arm,
                                             const bool _sign,
                                             const float _angleStart,
                                             const float _angleEnd,
                                             const float _length,
                                             const float _radius,
                                             const float _radiusLine,
                                             const uint64_t _pattern,
                                             const uint64_t _quality,
                                             const uint64_t _qualityLine,
                                             const uint8_t _alpha,
                                             const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , sign("sign", _sign)
    , angleStart("angleStart", _angleStart)
    , angleEnd("angleEnd  ", _angleEnd)
    , length("length", _length, 0.0f, std::numeric_limits<float>::max())
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , radiusLine("radiusLine", _radiusLine, 0.0f, std::numeric_limits<float>::max())
    , pattern("pattern", _pattern)
    , quality("quality", _quality)
    , qualityLine("qualityLine", _qualityLine)
{
    addProperty(&sign);
    addProperty(&angleStart);
    addProperty(&angleEnd);
    addProperty(&length);
    addProperty(&radius);
    addProperty(&radiusLine);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&qualityLine);
}

void ItemPathSpiral::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
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

    const float as = angleStart.value(_timeStep);
    const float ae = angleEnd.value(_timeStep);
    if (Math::equals(as, ae))
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
    o.createSpiralPath(path, pathCenter, pathLength, s, l, r, as, ae, q);
    ItemPath::createPath(_data, path, pathCenter, pathLength, rl, p, ql, m, a);
}

void ItemPathSpiralRainbow::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
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

    const float as = angleStart.value(_timeStep);
    const float ae = angleEnd.value(_timeStep);
    if (Math::equals(as, ae))
        return;

    const Math::OrientF o = valueOrientation(_timeStep);
    const bool s = sign.value(_timeStep);
    const float l = length.value(_timeStep);
    const size_t q = quality.value(_timeStep);
    const size_t ql = qualityLine.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path;
    o.createSpiralPath(path, pathCenter, pathLength, s, l, r, as, ae, q);
    ItemPathColor::createPath(_data, path, pathCenter, pathLength, rl, p, ql, a);
}

}  // namespace Items
}  // namespace U1
