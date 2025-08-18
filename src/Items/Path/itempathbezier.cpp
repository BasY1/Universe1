/*!
 * \file src/Items/Path/itempathbezier.cpp
 * \brief Dynamic 3D line - bezier curve path video item
 */

#include "itempathbezier.h"

#include "itempath.h"

namespace U1 {
namespace Items {

ItemPathBezier::ItemPathBezier(const std::string &_name,
                               const Math::Vec3F &_point1,
                               const Math::Vec3F &_point2,
                               const Math::Vec3F &_normal1,
                               const Math::Vec3F &_normal2,
                               const float _weight1,
                               const float _weight2,
                               const float _radius,
                               const uint16_t _segments,
                               const uint64_t _pattern,
                               const uint64_t _quality,
                               const Math::MaterialRGB &_material,
                               const uint8_t _alpha,
                               const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , point1(_name + ".point1", _point1)
    , point2(_name + ".point2", _point2)
    , normal1(_name + ".normal1", true, _normal1)
    , normal2(_name + ".normal2", true, _normal2)
    , weight1(_name + ".weight1", _weight1, 0.0f, std::numeric_limits<float>::max())
    , weight2(_name + ".weight2", _weight2, 0.0f, std::numeric_limits<float>::max())
    , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , segments(_name + ".segments", _segments, 1U, std::numeric_limits<uint16_t>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , material(_name + ".material", _material)
{
    addProperty(&point1);
    addProperty(&point2);
    addProperty(&normal1);
    addProperty(&normal2);
    addProperty(&weight1);
    addProperty(&weight2);
    addProperty(&radius);
    addProperty(&segments);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&material);
}

ItemPathBezier2Color::ItemPathBezier2Color(const std::string &_name,
                                           const Math::Vec3F &_point1,
                                           const Math::Vec3F &_point2,
                                           const Math::Vec3F &_normal1,
                                           const Math::Vec3F &_normal2,
                                           const float _weight1,
                                           const float _weight2,
                                           const float _radius,
                                           const uint16_t _segments,
                                           const uint64_t _pattern,
                                           const uint64_t _quality,
                                           const Math::ColorRGB &_color1,
                                           const Math::ColorRGB &_color2,
                                           const uint8_t _alpha,
                                           const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , point1(_name + ".point1", _point1)
    , point2(_name + ".point2", _point2)
    , normal1(_name + ".normal1", true, _normal1)
    , normal2(_name + ".normal2", true, _normal2)
    , weight1(_name + ".weight1", _weight1, 0.0f, std::numeric_limits<float>::max())
    , weight2(_name + ".weight2", _weight2, 0.0f, std::numeric_limits<float>::max())
    , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , segments(_name + ".segments", _segments, 1U, std::numeric_limits<uint16_t>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
    , color1(_name + ".color1", _color1)
    , color2(_name + ".color2", _color2)
{
    addProperty(&point1);
    addProperty(&point2);
    addProperty(&normal1);
    addProperty(&normal2);
    addProperty(&weight1);
    addProperty(&weight2);
    addProperty(&radius);
    addProperty(&segments);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&color1);
    addProperty(&color2);
}

ItemPathBezierRainbow::ItemPathBezierRainbow(const std::string &_name,
                                             const Math::Vec3F &_point1,
                                             const Math::Vec3F &_point2,
                                             const Math::Vec3F &_normal1,
                                             const Math::Vec3F &_normal2,
                                             const float _weight1,
                                             const float _weight2,
                                             const float _radius,
                                             const uint16_t _segments,
                                             const uint64_t _pattern,
                                             const uint64_t _quality,
                                             const uint8_t _alpha,
                                             const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , point1(_name + ".point1", _point1)
    , point2(_name + ".point2", _point2)
    , normal1(_name + ".normal1", true, _normal1)
    , normal2(_name + ".normal2", true, _normal2)
    , weight1(_name + ".weight1", _weight1, 0.0f, std::numeric_limits<float>::max())
    , weight2(_name + ".weight2", _weight2, 0.0f, std::numeric_limits<float>::max())
    , radius(_name + ".radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , segments(_name + ".segments", _segments, 1U, std::numeric_limits<uint16_t>::max())
    , pattern(_name + ".pattern", _pattern)
    , quality(_name + ".quality", _quality)
{
    addProperty(&point1);
    addProperty(&point2);
    addProperty(&normal1);
    addProperty(&normal2);
    addProperty(&weight1);
    addProperty(&weight2);
    addProperty(&radius);
    addProperty(&segments);
    addProperty(&pattern);
    addProperty(&quality);
}

void ItemPathBezier::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const float w1 = weight1.value(_timeStep);
    const float w2 = weight2.value(_timeStep);
    if (!Math::isPositive(w1) || !Math::isPositive(w2))
        return;

    const Math::Vec3F p1 = point1.value(_timeStep);
    const Math::Vec3F p4 = point2.value(_timeStep);

    const Math::Vec3F n1 = normal1.value(_timeStep);
    const Math::Vec3F n2 = normal2.value(_timeStep);

    const Math::Vec3F p2 = p1 + n1 * w1;
    const Math::Vec3F p3 = p4 - n2 * w2;

    const uint16_t sn = segments.value(_timeStep);
    const size_t q = quality.value(_timeStep);
    const Math::MaterialRGB m = material.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<Math::OrientF> path;

    Math::OrientF::createBezierPath(path, pathCenter, pathLength, p1, p2, p3, p4, sn);
    ItemPath::createPath(_data, path, pathCenter, pathLength, r, p, q, m, a);
}

void ItemPathBezier2Color::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const float w1 = weight1.value(_timeStep);
    const float w2 = weight2.value(_timeStep);
    if (!Math::isPositive(w1) || !Math::isPositive(w2))
        return;

    const Math::Vec3F p1 = point1.value(_timeStep);
    const Math::Vec3F p4 = point2.value(_timeStep);

    const Math::Vec3F n1 = normal1.value(_timeStep);
    const Math::Vec3F n2 = normal2.value(_timeStep);

    const Math::Vec3F p2 = p1 + n1 * w1;
    const Math::Vec3F p3 = p4 - n2 * w2;

    const uint16_t sn = segments.value(_timeStep);
    const size_t q = quality.value(_timeStep);
    const Math::ColorRGB c1 = color1.value(_timeStep);
    const Math::ColorRGB c2 = color2.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path;
    Math::OrientF::createBezierPath(path, pathCenter, pathLength, p1, p2, p3, p4, sn, c1, c2);
    ItemPathColor::createPath(_data, path, pathCenter, pathLength, r, p, q, a);
}

void ItemPathBezierRainbow::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    const float r = radius.value(_timeStep);
    if (!Math::isPositive(r))
        return;

    const size_t p = pattern.value(_timeStep);
    if (p == 0UL)
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    const float w1 = weight1.value(_timeStep);
    const float w2 = weight2.value(_timeStep);
    if (!Math::isPositive(w1) || !Math::isPositive(w2))
        return;

    const Math::Vec3F p1 = point1.value(_timeStep);
    const Math::Vec3F p4 = point2.value(_timeStep);

    const Math::Vec3F n1 = normal1.value(_timeStep);
    const Math::Vec3F n2 = normal2.value(_timeStep);

    const Math::Vec3F p2 = p1 + n1 * w1;
    const Math::Vec3F p3 = p4 - n2 * w2;

    const uint16_t sn = segments.value(_timeStep);
    const size_t q = quality.value(_timeStep);

    float pathLength;
    Math::Vec3F pathCenter;
    std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path;
    Math::OrientF::createBezierPathRainbow(path, pathCenter, pathLength, p1, p2, p3, p4, sn);
    ItemPathColor::createPath(_data, path, pathCenter, pathLength, r, p, q, a);
}

}  // namespace Items
}  // namespace U1
