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

    createPath(_data, path, pathCenter, pathLength, r, p, q, m1, a);
}

void ItemPath::createPath(std::list<OpenGL::Data3D *> &_data,
                          const std::vector<Math::OrientF> &_path,
                          const Math::Vec3F &_pathCenter,
                          const float _pathLength,
                          const float _pathRadius,
                          const size_t _pattern,
                          const size_t _quality,
                          const Math::MaterialRGB &_material,
                          const uint8_t _alpha,
                          const bool _invertedIndices)
{
    const Math::MaterialRGB m2 = _material.darker();

    if (_pattern == PATTERN_SOLID)
    {
        _data.push_back(OpenGL::Data3DMaterialNormal::path(
            _path, _pathCenter, _pathRadius, _quality, _material, _alpha, _invertedIndices));
        _data.push_back(
            OpenGL::Data3DMaterialBase::circle(_path.front().toInvert12(), _pathRadius, _quality, m2, _alpha));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(_path.back(), _pathRadius, _quality, m2, _alpha));
        return;
    }

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, _pattern, 0.0f, _pathLength, _pathRadius);

    size_t idxBeg = 0UL;
    float passedLen = 0.0f;
    for (const std::pair<float, float> &d : std::as_const(dp))
    {
        while (Math::isLessNotEqual(passedLen, d.first) && idxBeg < _path.size())
        {
            ++idxBeg;
            passedLen += _path[idxBeg].center.distanceToPoint(_path[idxBeg - 1UL].center);
        }

        if (idxBeg == _path.size())
        {
            std::cerr << " ItemPath::createDataImpl(): Invalid data begin!\n";
            return;
        }

        size_t idxEnd = idxBeg;
        float passedLen2 = passedLen;
        while (Math::isLessNotEqual(passedLen2, d.second) && idxEnd < (_path.size() - 1UL))
        {
            ++idxEnd;
            passedLen2 += _path[idxEnd].center.distanceToPoint(_path[idxEnd - 1UL].center);
        }
        if (idxEnd == _path.size())
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
            Math::copyData<Math::OrientF, size_t>(path2.data(), &_path.data()[idxBeg], N2, Math::createPool(N2));
            _data.push_back(
                OpenGL::Data3DMaterialNormal::path(path2, _pathRadius, _quality, _material, _alpha, _invertedIndices));
            _data.push_back(
                OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), _pathRadius, _quality, m2, _alpha));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), _pathRadius, _quality, m2, _alpha));
            continue;
        }

        if (matchBeg && !matchEnd)
        {
            const size_t ie = idxEnd - 1UL;
            const size_t cnt = idxEnd - idxBeg;
            const float lastDist = _path[idxEnd].center.distanceToPoint(_path[ie].center);
            const float offsetPrev = passedLen2 - lastDist;
            const float ratio = (d.second - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<Math::OrientF, size_t>(path2.data(), &_path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[cnt].center = _path[ie].center + ratio * (_path[idxEnd].center - _path[ie].center);
            path2[cnt].normal1 = _path[ie].normal1 + ratio * (_path[idxEnd].normal1 - _path[ie].normal1);
            path2[cnt].normal2 = _path[ie].normal2 + ratio * (_path[idxEnd].normal2 - _path[ie].normal2);
            Math::Vec3F::makePerpendicularNormals(path2[cnt].normal1, path2[cnt].normal2);
            path2[cnt].normal3 = Math::Vec3F::cross(path2[cnt].normal1, path2[cnt].normal2).normalized();

            _data.push_back(
                OpenGL::Data3DMaterialNormal::path(path2, _pathRadius, _quality, _material, _alpha, _invertedIndices));
            _data.push_back(
                OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), _pathRadius, _quality, m2, _alpha));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), _pathRadius, _quality, m2, _alpha));
            continue;
        }

        if (!matchBeg && matchEnd)
        {
            const size_t ib = idxBeg - 1UL;
            const size_t cnt = idxEnd + 1UL - idxBeg;
            const float lastDist = _path[idxBeg].center.distanceToPoint(_path[ib].center);
            const float offsetPrev = passedLen - lastDist;
            const float ratio = (d.first - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<Math::OrientF, size_t>(
                &path2.data()[1UL], &_path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[0UL].center = _path[ib].center + ratio * (_path[idxBeg].center - _path[ib].center);
            path2[0UL].normal1 = _path[ib].normal1 + ratio * (_path[idxBeg].normal1 - _path[ib].normal1);
            path2[0UL].normal2 = _path[ib].normal2 + ratio * (_path[idxBeg].normal2 - _path[ib].normal2);
            Math::Vec3F::makePerpendicularNormals(path2[0UL].normal1, path2[0UL].normal2);
            path2[0UL].normal3 = Math::Vec3F::cross(path2[0UL].normal1, path2[0UL].normal2).normalized();

            _data.push_back(
                OpenGL::Data3DMaterialNormal::path(path2, _pathRadius, _quality, _material, _alpha, _invertedIndices));
            _data.push_back(
                OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), _pathRadius, _quality, m2, _alpha));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), _pathRadius, _quality, m2, _alpha));
            continue;
        }

        const size_t ib = idxBeg - 1UL;
        const size_t ie = idxEnd - 1UL;
        const float lastDistBeg = _path[idxBeg].center.distanceToPoint(_path[ib].center);
        const float lastDistEnd = _path[idxEnd].center.distanceToPoint(_path[ie].center);
        const float offsetPrevBeg = passedLen - lastDistBeg;
        const float offsetPrevEnd = passedLen2 - lastDistEnd;
        const float ratioBeg = (d.first - offsetPrevBeg) / lastDistBeg;
        const float ratioEnd = (d.second - offsetPrevEnd) / lastDistEnd;

        const size_t cnt = idxEnd - idxBeg;
        const size_t last = cnt + 1UL;

        path2.resize(cnt + 2UL);

        Math::copyData<Math::OrientF, size_t>(&path2.data()[1UL], &_path.data()[idxBeg], cnt, Math::createPool(cnt));

        path2[0UL].center = _path[ib].center + ratioBeg * (_path[idxBeg].center - _path[ib].center);
        path2[0UL].normal1 = _path[ib].normal1 + ratioBeg * (_path[idxBeg].normal1 - _path[ib].normal1);
        path2[0UL].normal2 = _path[ib].normal2 + ratioBeg * (_path[idxBeg].normal2 - _path[ib].normal2);
        Math::Vec3F::makePerpendicularNormals(path2[0UL].normal1, path2[0UL].normal2);
        path2[0UL].normal3 = Math::Vec3F::cross(path2[0UL].normal1, path2[0UL].normal2).normalized();

        path2[last].center = _path[ie].center + ratioEnd * (_path[idxEnd].center - _path[ie].center);
        path2[last].normal1 = _path[ie].normal1 + ratioEnd * (_path[idxEnd].normal1 - _path[ie].normal1);
        path2[last].normal2 = _path[ie].normal2 + ratioEnd * (_path[idxEnd].normal2 - _path[ie].normal2);
        Math::Vec3F::makePerpendicularNormals(path2[last].normal1, path2[last].normal2);
        path2[last].normal3 = Math::Vec3F::cross(path2[last].normal1, path2[last].normal2).normalized();

        _data.push_back(
            OpenGL::Data3DMaterialNormal::path(path2, _pathRadius, _quality, _material, _alpha, _invertedIndices));
        _data.push_back(
            OpenGL::Data3DMaterialBase::circle(path2.front().toInvert12(), _pathRadius, _quality, m2, _alpha));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.back(), _pathRadius, _quality, m2, _alpha));
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
    createPath(_data, path, pathCenter, pathLength, r, p, q, a);
}

void ItemPathColor::createPath(std::list<OpenGL::Data3D *> &_data,
                               const std::vector<std::pair<Math::OrientF, Math::ColorRGB>> &_path,
                               const Math::Vec3F &_pathCenter,
                               const float _pathLength,
                               const float _pathRadius,
                               const size_t _pattern,
                               const size_t _quality,
                               const uint8_t _alpha,
                               const bool _invertedIndices)
{

    if (_pattern == PATTERN_SOLID)
    {
        _data.push_back(
            OpenGL::Data3DMaterialsNormal::path(_path, _pathCenter, _pathRadius, _quality, _alpha, _invertedIndices));

        _data.push_back(OpenGL::Data3DMaterialBase::circle(_path.front().first.toInvert12(),
                                                           _pathRadius,
                                                           _quality,
                                                           Math::MaterialRGB(_path.front().second.darker()),
                                                           _alpha));

        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            _path.back().first, _pathRadius, _quality, Math::MaterialRGB(_path.back().second.darker()), _alpha));
        return;
    }

    std::vector<std::pair<float, float>> dp;
    Math::fillDashPattern(dp, _pattern, 0.0f, _pathLength, _pathRadius);

    size_t idxBeg = 0UL;
    float passedLen = 0.0f;
    for (const std::pair<float, float> &d : std::as_const(dp))
    {
        while (Math::isLessNotEqual(passedLen, d.first) && idxBeg < _path.size())
        {
            ++idxBeg;
            passedLen += _path[idxBeg].first.center.distanceToPoint(_path[idxBeg - 1UL].first.center);
        }

        if (idxBeg == _path.size())
        {
            std::cerr << " ItemPathColor::createDataImpl(): Invalid data begin!\n";
            return;
        }

        size_t idxEnd = idxBeg;
        float passedLen2 = passedLen;
        while (Math::isLessNotEqual(passedLen2, d.second) && idxEnd < (_path.size() - 1UL))
        {
            ++idxEnd;
            passedLen2 += _path[idxEnd].first.center.distanceToPoint(_path[idxEnd - 1UL].first.center);
        }
        if (idxEnd == _path.size())
        {
            std::cerr << " ItemPathColor::createDataImpl(): Invalid data end!\n";
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
                path2.data(), &_path.data()[idxBeg], N2, Math::createPool(N2));
            _data.push_back(
                OpenGL::Data3DMaterialsNormal::path(path2, _pathRadius, _quality, _alpha, _invertedIndices));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().first.toInvert12(),
                                                               _pathRadius,
                                                               _quality,
                                                               Math::MaterialRGB(path2.front().second.darker()),
                                                               _alpha));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.back().first, _pathRadius, _quality, Math::MaterialRGB(path2.back().second.darker()), _alpha));
            continue;
        }

        if (matchBeg && !matchEnd)
        {
            const size_t ie = idxEnd - 1UL;
            const size_t cnt = idxEnd - idxBeg;
            const float lastDist = _path[idxEnd].first.center.distanceToPoint(_path[ie].first.center);
            const float offsetPrev = passedLen2 - lastDist;
            const float ratio = (d.second - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
                path2.data(), &_path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[cnt].second = Math::ColorRGB::ratio(ratio, _path[ie].second, _path[idxEnd].second);

            path2[cnt].first.center =
                _path[ie].first.center + ratio * (_path[idxEnd].first.center - _path[ie].first.center);
            path2[cnt].first.normal1 =
                _path[ie].first.normal1 + ratio * (_path[idxEnd].first.normal1 - _path[ie].first.normal1);
            path2[cnt].first.normal2 =
                _path[ie].first.normal2 + ratio * (_path[idxEnd].first.normal2 - _path[ie].first.normal2);
            Math::Vec3F::makePerpendicularNormals(path2[cnt].first.normal1, path2[cnt].first.normal2);
            path2[cnt].first.normal3 =
                Math::Vec3F::cross(path2[cnt].first.normal1, path2[cnt].first.normal2).normalized();

            _data.push_back(
                OpenGL::Data3DMaterialsNormal::path(path2, _pathRadius, _quality, _alpha, _invertedIndices));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().first.toInvert12(),
                                                               _pathRadius,
                                                               _quality,
                                                               Math::MaterialRGB(path2.front().second.darker()),
                                                               _alpha));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.back().first, _pathRadius, _quality, Math::MaterialRGB(path2.back().second.darker()), _alpha));
            continue;
        }

        if (!matchBeg && matchEnd)
        {
            const size_t ib = idxBeg - 1UL;
            const size_t cnt = idxEnd + 1UL - idxBeg;
            const float lastDist = _path[idxBeg].first.center.distanceToPoint(_path[ib].first.center);
            const float offsetPrev = passedLen - lastDist;
            const float ratio = (d.first - offsetPrev) / lastDist;

            path2.resize(cnt + 1UL);
            Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
                &path2.data()[1UL], &_path.data()[idxBeg], cnt, Math::createPool(cnt));

            path2[0UL].second = Math::ColorRGB::ratio(ratio, _path[ib].second, _path[idxBeg].second);
            path2[0UL].first.center =
                _path[ib].first.center + ratio * (_path[idxBeg].first.center - _path[ib].first.center);
            path2[0UL].first.normal1 =
                _path[ib].first.normal1 + ratio * (_path[idxBeg].first.normal1 - _path[ib].first.normal1);
            path2[0UL].first.normal2 =
                _path[ib].first.normal2 + ratio * (_path[idxBeg].first.normal2 - _path[ib].first.normal2);
            Math::Vec3F::makePerpendicularNormals(path2[0UL].first.normal1, path2[0UL].first.normal2);
            path2[0UL].first.normal3 =
                Math::Vec3F::cross(path2[0UL].first.normal1, path2[0UL].first.normal2).normalized();

            _data.push_back(
                OpenGL::Data3DMaterialsNormal::path(path2, _pathRadius, _quality, _alpha, _invertedIndices));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().first.toInvert12(),
                                                               _pathRadius,
                                                               _quality,
                                                               Math::MaterialRGB(path2.front().second.darker()),
                                                               _alpha));
            _data.push_back(OpenGL::Data3DMaterialBase::circle(
                path2.back().first, _pathRadius, _quality, Math::MaterialRGB(path2.back().second.darker()), _alpha));
            continue;
        }

        const size_t ib = idxBeg - 1UL;
        const size_t ie = idxEnd - 1UL;
        const float lastDistBeg = _path[idxBeg].first.center.distanceToPoint(_path[ib].first.center);
        const float lastDistEnd = _path[idxEnd].first.center.distanceToPoint(_path[ie].first.center);
        const float offsetPrevBeg = passedLen - lastDistBeg;
        const float offsetPrevEnd = passedLen2 - lastDistEnd;
        const float ratioBeg = (d.first - offsetPrevBeg) / lastDistBeg;
        const float ratioEnd = (d.second - offsetPrevEnd) / lastDistEnd;

        const size_t cnt = idxEnd - idxBeg;
        const size_t last = cnt + 1UL;

        path2.resize(cnt + 2UL);

        Math::copyData<std::pair<Math::OrientF, Math::ColorRGB>, size_t>(
            &path2.data()[1UL], &_path.data()[idxBeg], cnt, Math::createPool(cnt));

        path2[0UL].second = Math::ColorRGB::ratio(ratioBeg, _path[ib].second, _path[idxBeg].second);
        path2[0UL].first.center =
            _path[ib].first.center + ratioBeg * (_path[idxBeg].first.center - _path[ib].first.center);
        path2[0UL].first.normal1 =
            _path[ib].first.normal1 + ratioBeg * (_path[idxBeg].first.normal1 - _path[ib].first.normal1);
        path2[0UL].first.normal2 =
            _path[ib].first.normal2 + ratioBeg * (_path[idxBeg].first.normal2 - _path[ib].first.normal2);
        Math::Vec3F::makePerpendicularNormals(path2[0UL].first.normal1, path2[0UL].first.normal2);
        path2[0UL].first.normal3 = Math::Vec3F::cross(path2[0UL].first.normal1, path2[0UL].first.normal2).normalized();

        path2[last].second = Math::ColorRGB::ratio(ratioEnd, _path[ie].second, _path[idxEnd].second);
        path2[last].first.center =
            _path[ie].first.center + ratioEnd * (_path[idxEnd].first.center - _path[ie].first.center);
        path2[last].first.normal1 =
            _path[ie].first.normal1 + ratioEnd * (_path[idxEnd].first.normal1 - _path[ie].first.normal1);
        path2[last].first.normal2 =
            _path[ie].first.normal2 + ratioEnd * (_path[idxEnd].first.normal2 - _path[ie].first.normal2);
        Math::Vec3F::makePerpendicularNormals(path2[last].first.normal1, path2[last].first.normal2);
        path2[last].first.normal3 =
            Math::Vec3F::cross(path2[last].first.normal1, path2[last].first.normal2).normalized();

        _data.push_back(OpenGL::Data3DMaterialsNormal::path(path2, _pathRadius, _quality, _alpha, _invertedIndices));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(path2.front().first.toInvert12(),
                                                           _pathRadius,
                                                           _quality,
                                                           Math::MaterialRGB(path2.front().second.darker()),
                                                           _alpha));
        _data.push_back(OpenGL::Data3DMaterialBase::circle(
            path2.back().first, _pathRadius, _quality, Math::MaterialRGB(path2.back().second.darker()), _alpha));
    }
}

}  // namespace Items
}  // namespace U1
