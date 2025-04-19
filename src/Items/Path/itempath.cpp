/*!
 * \file src/Items/Path/itempath.cpp
 * \brief Dynamic 3D line video item
 */

#include "itempath.h"

#include "../../Data3D/data3dmaterialbase.h"
#include "../../Data3D/data3dmaterialnormal.h"
#include "../../Data3D/data3dmaterialsnormal.h"

namespace U1 {
namespace Items {

ItemPath::ItemPath(const std::vector<Math::OrientF> &_path,
                   const std::string &_name,
                   const float _radius,
                   const uint64_t _pattern,
                   const uint64_t _quality,
                   const Math::MaterialRGB &_material,
                   const uint8_t _alpha,
                   const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , path(_path)
    , pathCenter(Math::OrientF::centerPoint(path.data(), path.size(), Math::createPool(path.size())))
    , pathLength(Math::OrientF::pathLength(path.data(), path.size(), Math::createPool(path.size())))
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , pattern("pattern", _pattern)
    , quality("quality", _quality)
    , material("material", _material)
{
    addProperty(&radius);
    addProperty(&pattern);
    addProperty(&quality);
    addProperty(&material);
}

ItemPathColor::ItemPathColor(const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                             const std::string &_name,
                             const float _radius,
                             const uint64_t _pattern,
                             const uint64_t _quality,
                             const uint8_t _alpha,
                             const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , path(_path)
    , pathCenter(Math::OrientF::centerPoint(path.data(), path.size(), Math::createPool(path.size())))
    , pathLength(Math::OrientF::pathLength(path.data(), path.size(), Math::createPool(path.size())))
    , radius("radius", _radius, 0.0f, std::numeric_limits<float>::max())
    , pattern("pattern", _pattern)
    , quality("quality", _quality)
{
    addProperty(&radius);
    addProperty(&pattern);
    addProperty(&quality);
}

void ItemPath::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    if (path.size() < 2UL)
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

    const size_t q = quality.value(_timeStep);
    const Math::MaterialRGB m1 = material.value(_timeStep);
    const Math::MaterialRGB m2 = m1.darker();

    if (p == PATTERN_SOLID)
    {
        _data.push_back(OpenGL::Data3DMaterialNormal::path(path, pathCenter, r, q, m1, a, true));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(path.front().toInvert12(), r, q, m2, a));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(path.back(), r, q, m2, a));
        return;
    }

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, p, 0.0f, pathLength, r);

    size_t idxBeg = 0UL;
    float passedLen = 0.0f;
    for (const std::pair<float, float> &d : std::as_const(dp))
    {
        while (Math::isLessNotEqual(passedLen, d.first) && idxBeg < path.size())
        {
            ++idxBeg;
            passedLen += path[idxBeg].center.distanceToPoint(path[idxBeg - 1UL].center);
        }

        if (idxBeg == path.size())
        {
            std::cerr << " ItemPath::createDataImpl(): Invalid data begin!\n";
            return;
        }

        size_t idxEnd = idxBeg;
        float passedLen2 = passedLen;
        while (Math::isLessNotEqual(passedLen2, d.second) && idxEnd < path.size())
        {
            ++idxEnd;
            passedLen2 += path[idxEnd].center.distanceToPoint(path[idxEnd - 1UL].center);
        }
        if (idxEnd == path.size())
        {
            std::cerr << " ItemPath::createDataImpl(): Invalid data end!\n";
            return;
        }

        const bool matchBeg = Math::equals(passedLen, d.first);
        const bool matchEnd = Math::equals(passedLen2, d.second);
        std::vector<Math::OrientF> path2;

        if (matchBeg && matchEnd)
        {
            const size_t N2 = idxEnd + 1UL - idxBeg;
            path2.resize(N2);
            Math::copyData<Math::OrientF, size_t>(path2.data(), &path.data()[idxBeg], N2, Math::createPool(N2));
            _data.push_back(OpenGL::Data3DMaterialNormal::path(path2, r, q, m1, a, true));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), r, q, m2, a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), r, q, m2, a));
            continue;
        }

        if (matchBeg && !matchEnd)
        {
            const size_t ie = idxEnd - 1UL;
            const size_t cnt = idxEnd - idxBeg;
            const float lastDist = path[idxEnd].center.distanceToPoint(path[ie].center);
            const float offsetPrev = passedLen2 - lastDist;
            const float ratio = (d.second - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<Math::OrientF, size_t>(path2.data(), &path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[cnt].center = path[ie].center + ratio * (path[idxEnd].center - path[ie].center);
            path2[cnt].normal1 = path[ie].normal1 + ratio * (path[idxEnd].normal1 - path[ie].normal1);
            path2[cnt].normal2 = path[ie].normal2 + ratio * (path[idxEnd].normal2 - path[ie].normal2);
            Math::Vec3F::makePerpendicularNormals(path2[cnt].normal1, path2[cnt].normal2);
            path2[cnt].normal3 = Math::Vec3F::cross(path2[cnt].normal1, path2[cnt].normal2).normalized();

            _data.push_back(OpenGL::Data3DMaterialNormal::path(path2, r, q, m1, a, true));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), r, q, m2, a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), r, q, m2, a));
            continue;
        }

        if (!matchBeg && matchEnd)
        {
            const size_t ib = idxBeg - 1UL;
            const size_t cnt = idxEnd + 1UL - idxBeg;
            const float lastDist = path[idxBeg].center.distanceToPoint(path[ib].center);
            const float offsetPrev = passedLen - lastDist;
            const float ratio = (d.first - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<Math::OrientF, size_t>(&path2.data()[1UL], &path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[0UL].center = path[ib].center + ratio * (path[idxBeg].center - path[ib].center);
            path2[0UL].normal1 = path[ib].normal1 + ratio * (path[idxBeg].normal1 - path[ib].normal1);
            path2[0UL].normal2 = path[ib].normal2 + ratio * (path[idxBeg].normal2 - path[ib].normal2);
            Math::Vec3F::makePerpendicularNormals(path2[0UL].normal1, path2[0UL].normal2);
            path2[0UL].normal3 = Math::Vec3F::cross(path2[0UL].normal1, path2[0UL].normal2).normalized();

            _data.push_back(OpenGL::Data3DMaterialNormal::path(path2, r, q, m1, a, true));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), r, q, m2, a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), r, q, m2, a));
            continue;
        }

        const size_t ib = idxBeg - 1UL;
        const size_t ie = idxEnd - 1UL;
        const float lastDistBeg = path[idxBeg].center.distanceToPoint(path[ib].center);
        const float lastDistEnd = path[idxEnd].center.distanceToPoint(path[ie].center);
        const float offsetPrevBeg = passedLen - lastDistBeg;
        const float offsetPrevEnd = passedLen2 - lastDistEnd;
        const float ratioBeg = (d.first - offsetPrevBeg) / lastDistBeg;
        const float ratioEnd = (d.second - offsetPrevEnd) / lastDistEnd;

        const size_t cnt = idxEnd - idxBeg;
        const size_t last = cnt + 1UL;

        path2.resize(cnt + 2UL);

        Math::copyData<Math::OrientF, size_t>(&path2.data()[1UL], &path.data()[idxBeg], cnt, Math::createPool(cnt));

        path2[0UL].center = path[ib].center + ratioBeg * (path[idxBeg].center - path[ib].center);
        path2[0UL].normal1 = path[ib].normal1 + ratioBeg * (path[idxBeg].normal1 - path[ib].normal1);
        path2[0UL].normal2 = path[ib].normal2 + ratioBeg * (path[idxBeg].normal2 - path[ib].normal2);
        Math::Vec3F::makePerpendicularNormals(path2[0UL].normal1, path2[0UL].normal2);
        path2[0UL].normal3 = Math::Vec3F::cross(path2[0UL].normal1, path2[0UL].normal2).normalized();

        path2[last].center = path[ie].center + ratioEnd * (path[idxEnd].center - path[ie].center);
        path2[last].normal1 = path[ie].normal1 + ratioEnd * (path[idxEnd].normal1 - path[ie].normal1);
        path2[last].normal2 = path[ie].normal2 + ratioEnd * (path[idxEnd].normal2 - path[ie].normal2);
        Math::Vec3F::makePerpendicularNormals(path2[last].normal1, path2[last].normal2);
        path2[last].normal3 = Math::Vec3F::cross(path2[last].normal1, path2[last].normal2).normalized();

        _data.push_back(OpenGL::Data3DMaterialNormal::path(path2, r, q, m1, a, true));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), r, q, m2, a));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), r, q, m2, a));
    }
}

void ItemPathColor::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    if (path.size() < 2UL)
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

    const size_t q = quality.value(_timeStep);

    if (p == PATTERN_SOLID)
    {
        _data.push_back(OpenGL::Data3DMaterialsNormal::path(path, pathCenter, r, q, a, true));

        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            path.front().first.toInvert12(), r, q, Math::MaterialRGB(path.front().second.darker()), a));

        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            path.back().first, r, q, Math::MaterialRGB(path.back().second.darker()), a));
        return;
    }

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, p, 0.0f, pathLength, r);

    size_t idxBeg = 0UL;
    float passedLen = 0.0f;
    for (const std::pair<float, float> &d : std::as_const(dp))
    {
        while (Math::isLessNotEqual(passedLen, d.first) && idxBeg < path.size())
        {
            ++idxBeg;
            passedLen += path[idxBeg].first.center.distanceToPoint(path[idxBeg - 1UL].first.center);
        }

        if (idxBeg == path.size())
        {
            std::cerr << " ItemPath::createDataImpl(): Invalid data begin!\n";
            return;
        }

        size_t idxEnd = idxBeg;
        float passedLen2 = passedLen;
        while (Math::isLessNotEqual(passedLen2, d.second) && idxEnd < path.size())
        {
            ++idxEnd;
            passedLen2 += path[idxEnd].first.center.distanceToPoint(path[idxEnd - 1UL].first.center);
        }
        if (idxEnd == path.size())
        {
            std::cerr << " ItemPath::createDataImpl(): Invalid data end!\n";
            return;
        }

        const bool matchBeg = Math::equals(passedLen, d.first);
        const bool matchEnd = Math::equals(passedLen2, d.second);

        std::vector<std::pair<Math::OrientF, Math::ColorRGB>> path2;
        if (matchBeg && matchEnd)
        {
            const size_t N2 = idxEnd + 1UL - idxBeg;
            path2.resize(N2);
            Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
                path2.data(), &path.data()[idxBeg], N2, Math::createPool(N2));
            _data.push_back(OpenGL::Data3DMaterialsNormal::path(path2, r, q, a, true));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.front().first.toInvert12(), r, q, Math::MaterialRGB(path2.front().second.darker()), a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.back().first, r, q, Math::MaterialRGB(path2.back().second.darker()), a));
            continue;
        }

        if (matchBeg && !matchEnd)
        {
            const size_t ie = idxEnd - 1UL;
            const size_t cnt = idxEnd - idxBeg;
            const float lastDist = path[idxEnd].first.center.distanceToPoint(path[ie].first.center);
            const float offsetPrev = passedLen2 - lastDist;
            const float ratio = (d.second - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
                path2.data(), &path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[cnt].second = Math::ColorRGB::ratio(ratio, path[ie].second, path[idxEnd].second);

            path2[cnt].first.center =
                path[ie].first.center + ratio * (path[idxEnd].first.center - path[ie].first.center);
            path2[cnt].first.normal1 =
                path[ie].first.normal1 + ratio * (path[idxEnd].first.normal1 - path[ie].first.normal1);
            path2[cnt].first.normal2 =
                path[ie].first.normal2 + ratio * (path[idxEnd].first.normal2 - path[ie].first.normal2);
            Math::Vec3F::makePerpendicularNormals(path2[cnt].first.normal1, path2[cnt].first.normal2);
            path2[cnt].first.normal3 =
                Math::Vec3F::cross(path2[cnt].first.normal1, path2[cnt].first.normal2).normalized();

            _data.push_back(OpenGL::Data3DMaterialsNormal::path(path2, r, q, a, true));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.front().first.toInvert12(), r, q, Math::MaterialRGB(path2.front().second.darker()), a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.back().first, r, q, Math::MaterialRGB(path2.back().second.darker()), a));
            continue;
        }

        if (!matchBeg && matchEnd)
        {
            const size_t ib = idxBeg - 1UL;
            const size_t cnt = idxEnd + 1UL - idxBeg;
            const float lastDist = path[idxBeg].first.center.distanceToPoint(path[ib].first.center);
            const float offsetPrev = passedLen - lastDist;
            const float ratio = (d.first - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
                &path2.data()[1UL], &path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[0UL].second = Math::ColorRGB::ratio(ratio, path[ib].second, path[idxBeg].second);
            path2[0UL].first.center =
                path[ib].first.center + ratio * (path[idxBeg].first.center - path[ib].first.center);
            path2[0UL].first.normal1 =
                path[ib].first.normal1 + ratio * (path[idxBeg].first.normal1 - path[ib].first.normal1);
            path2[0UL].first.normal2 =
                path[ib].first.normal2 + ratio * (path[idxBeg].first.normal2 - path[ib].first.normal2);
            Math::Vec3F::makePerpendicularNormals(path2[0UL].first.normal1, path2[0UL].first.normal2);
            path2[0UL].first.normal3 =
                Math::Vec3F::cross(path2[0UL].first.normal1, path2[0UL].first.normal2).normalized();

            _data.push_back(OpenGL::Data3DMaterialsNormal::path(path2, r, q, a, true));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.front().first.toInvert12(), r, q, Math::MaterialRGB(path2.front().second.darker()), a));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.back().first, r, q, Math::MaterialRGB(path2.back().second.darker()), a));
            continue;
        }

        const size_t ib = idxBeg - 1UL;
        const size_t ie = idxEnd - 1UL;
        const float lastDistBeg = path[idxBeg].first.center.distanceToPoint(path[ib].first.center);
        const float lastDistEnd = path[idxEnd].first.center.distanceToPoint(path[ie].first.center);
        const float offsetPrevBeg = passedLen - lastDistBeg;
        const float offsetPrevEnd = passedLen2 - lastDistEnd;
        const float ratioBeg = (d.first - offsetPrevBeg) / lastDistBeg;
        const float ratioEnd = (d.second - offsetPrevEnd) / lastDistEnd;

        const size_t cnt = idxEnd - idxBeg;
        const size_t last = cnt + 1UL;

        path2.resize(cnt + 2UL);

        Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
            &path2.data()[1UL], &path.data()[idxBeg], cnt, Math::createPool(cnt));

        path2[0UL].second = Math::ColorRGB::ratio(ratioBeg, path[ib].second, path[idxBeg].second);
        path2[0UL].first.center =
            path[ib].first.center + ratioBeg * (path[idxBeg].first.center - path[ib].first.center);
        path2[0UL].first.normal1 =
            path[ib].first.normal1 + ratioBeg * (path[idxBeg].first.normal1 - path[ib].first.normal1);
        path2[0UL].first.normal2 =
            path[ib].first.normal2 + ratioBeg * (path[idxBeg].first.normal2 - path[ib].first.normal2);
        Math::Vec3F::makePerpendicularNormals(path2[0UL].first.normal1, path2[0UL].first.normal2);
        path2[0UL].first.normal3 = Math::Vec3F::cross(path2[0UL].first.normal1, path2[0UL].first.normal2).normalized();

        path2[last].second = Math::ColorRGB::ratio(ratioEnd, path[ie].second, path[idxEnd].second);
        path2[last].first.center =
            path[ie].first.center + ratioEnd * (path[idxEnd].first.center - path[ie].first.center);
        path2[last].first.normal1 =
            path[ie].first.normal1 + ratioEnd * (path[idxEnd].first.normal1 - path[ie].first.normal1);
        path2[last].first.normal2 =
            path[ie].first.normal2 + ratioEnd * (path[idxEnd].first.normal2 - path[ie].first.normal2);
        Math::Vec3F::makePerpendicularNormals(path2[last].first.normal1, path2[last].first.normal2);
        path2[last].first.normal3 =
            Math::Vec3F::cross(path2[last].first.normal1, path2[last].first.normal2).normalized();

        _data.push_back(OpenGL::Data3DMaterialsNormal::path(path2, r, q, a, true));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            path2.front().first.toInvert12(), r, q, Math::MaterialRGB(path2.front().second.darker()), a));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            path2.back().first, r, q, Math::MaterialRGB(path2.back().second.darker()), a));
    }
}

}  // namespace Items
}  // namespace U1
