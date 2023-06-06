#include "item3dwiresphereslice.h"

Universe1::Video::Item3DWireSphereSlice::Item3DWireSphereSlice(const QVector3D &_center,
                                                               const QVector3D &_normal,
                                                               const QVector3D &_arm,
                                                               const float _angleLatBeginDeg,
                                                               const float _angleLatEndDeg,
                                                               const float _angleLonBeginDeg,
                                                               const float _angleLonEndDeg,
                                                               const float _radiusSphere,
                                                               const float _radiusLine,
                                                               const uint _qualityLatLong,
                                                               const uint _qualitySphere,
                                                               const uint _qualityLine,
                                                               const bool _visible,
                                                               const Material &_material,
                                                               const std::string &_name)
    : Item3DWireSphere(_center,
                       _normal,
                       _arm,
                       _radiusSphere,
                       _radiusLine,
                       _qualityLatLong,
                       _qualitySphere,
                       _qualityLine,
                       _visible,
                       _material,
                       _name)
    , angleLatBeginDeg(_angleLatBeginDeg, _name + ".angleLatBeginDeg")
    , angleLatEndDeg(_angleLatEndDeg, _name + ".angleLatEndDeg")
    , angleLonBeginDeg(_angleLonBeginDeg, _name + ".angleLonBeginDeg")
    , angleLonEndDeg(_angleLonEndDeg, _name + ".angleLonEndDeg")
{
    props.push_back(&angleLatBeginDeg);
    props.push_back(&angleLatEndDeg);
    props.push_back(&angleLonBeginDeg);
    props.push_back(&angleLonEndDeg);
}

void Universe1::Video::Item3DWireSphereSlice::addData3D(std::list<Data3D> &_out,
                                                        const Shader *,  // _shader,
                                                        const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleLatBeginDeg.getValue(_timeStep),
              angleLatEndDeg.getValue(_timeStep),
              angleLonBeginDeg.getValue(_timeStep),
              angleLonEndDeg.getValue(_timeStep),
              radiusSphere.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityLatLong.getValue(_timeStep),
              qualitySphere.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DWireSphereSlice::buildData(std::list<Data3D> &_out,
                                                        const QVector3D &_center,
                                                        const QVector3D &_normal,
                                                        const QVector3D &_arm,
                                                        const float _angleLatBeginDeg,
                                                        const float _angleLatEndDeg,
                                                        const float _angleLonBeginDeg,
                                                        const float _angleLonEndDeg,
                                                        const float _radiusSphere,
                                                        const float _radiusLine,
                                                        const uint _qualityLatLong,
                                                        const uint _qualitySphere,
                                                        const uint _qualityLine,
                                                        const Material &_material)
{
    if (qFuzzyIsNull(_radiusSphere) || qFuzzyIsNull(_radiusLine) || _radiusSphere < 0.0f || _radiusLine < 0.0f)
        return;

    float lab = std::max(0.0f, _angleLatBeginDeg);
    float lae = std::min(180.0f, _angleLatEndDeg);
    float lob = std::max(0.0f, _angleLonBeginDeg);
    float loe = std::min(360.0f, _angleLonEndDeg);

    if (qFuzzyCompare(lab, lae) || qFuzzyCompare(lob, loe))
        return;

    if (lab > lae)
        std::swap(lab, lae);
    if (lob > loe)
        std::swap(lob, loe);

    const uint qs = std::max(_qualityLatLong, _qualitySphere);
    const std::pair<uint, uint> lola = loLaPointCount(_qualityLatLong);
    const float stepAngleLoDeg = 360.0f / static_cast<float>(lola.first);
    const float stepAngleLaDeg = 180.0f / static_cast<float>(lola.second + 1U);
    const float angleLaDeg = lae - lab;
    const float angleLoDeg = loe - lob;
    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);

    std::list<float> anglesLo, anglesLa;
    uint s = 1U + static_cast<uint>(lob / stepAngleLoDeg);
    float as = static_cast<float>(s) * stepAngleLoDeg;

    anglesLo.push_back(lob);
    while (!qFuzzyCompare(as, loe) && as < loe)
    {
        anglesLo.push_back(as);
        as += stepAngleLoDeg;
    }
    anglesLo.push_back(loe);

    s = 1U + static_cast<uint>(lab / stepAngleLaDeg);
    as = static_cast<float>(s) * stepAngleLaDeg;

    anglesLa.push_back(lab);
    while (!qFuzzyCompare(as, lae) && as < lae)
    {
        anglesLa.push_back(as);
        as += stepAngleLaDeg;
    }
    anglesLa.push_back(lae);

    for (const float lo : anglesLo)
    {
        const QVector3D an = QQuaternion::fromAxisAndAngle(n, lo).rotatedVector(a);
        const QVector3D nn = QVector3D::crossProduct(n, an);
        const QVector3D as = QQuaternion::fromAxisAndAngle(nn, lab).rotatedVector(n);
        Item3DTorusArc::buildData(
            _out, _center, nn, as, angleLaDeg, _radiusSphere, _radiusLine, qs, _qualityLine, _material);
    }

    const QVector3D aa = QQuaternion::fromAxisAndAngle(n, lob).rotatedVector(a).normalized();
    for (const float la : anglesLa)
    {
        const float ar = Math::toRad<float>(la);
        const QVector3D cc = _center + n * (std::cos(ar) * _radiusSphere);
        Item3DTorusArc::buildData(
            _out, cc, n, aa, angleLoDeg, std::sin(ar) * _radiusSphere, _radiusLine, qs, _qualityLine, _material);
    }
}

void Universe1::Video::Item3DWireSphereSlice::buildMultiColor(std::list<Data3D> &_out,
                                                              const QVector3D &_center,
                                                              const QVector3D &_normal,
                                                              const QVector3D &_arm,
                                                              const float _radiusSphere,
                                                              const float _radiusLine,
                                                              const uint _qualityLatLong,
                                                              const uint _qualitySphere,
                                                              const uint _qualityLine,
                                                              const std::vector<Material> &_materials)
{
    if (_materials.empty())
        return;

    if (_materials.size() == 1UL)
    {
        Item3DWireSphere::buildData(_out,
                                    _center,
                                    _normal,
                                    _arm,
                                    _radiusSphere,
                                    _radiusLine,
                                    _qualityLatLong,
                                    _qualitySphere,
                                    _qualityLine,
                                    _materials.front());
        return;
    }

    if (qFuzzyIsNull(_radiusSphere) || qFuzzyIsNull(_radiusLine) || _radiusSphere < 0.0f || _radiusLine < 0.0f)
        return;

    const uint qs = std::max(_qualityLatLong, _qualitySphere);
    const uint cntStep = circlePointCount(_qualityLatLong);
    const uint cntLa = _qualityLatLong * 2U + 1U;
    const float angleColor = 360.0f / static_cast<float>(_materials.size());
    const float angleStepDeg = 360.0f / static_cast<float>(cntStep);
    const float angleStepRad = Math::toRad<float>(angleStepDeg);
    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);

    std::vector<std::list<float>> angles(_materials.size());
    {
        float a0 = 0.0f;
        for (size_t im = 0UL; im < _materials.size(); ++im, a0 += angleColor)
        {

            const float stop = a0 + angleColor;
            const float s1 = static_cast<float>(static_cast<uint>(a0 / angleStepDeg) * angleStepDeg);
            float a1 = qFuzzyCompare(s1, a0) ? (a0 + angleStepDeg) : a0;
            angles[im].push_back(a0);
            while (!qFuzzyCompare(a1, stop) && a1 < stop)
            {
                angles[im].push_back(a1);
                a1 += angleStepDeg;
            }
            angles[im].push_back(a0 + angleColor);
        }
    }

    for (size_t im = 0UL; im < _materials.size(); ++im)
    {
        QVector3D aa = QQuaternion::fromAxisAndAngle(n, angles[im].front()).rotatedVector(a);
        QVector3D nn = QVector3D ::crossProduct(n, aa).normalized();
        Item3DTorusArcSlice::buildData(_out,
                                       _center,
                                       nn,
                                       n,
                                       0.0f,
                                       180.0f,
                                       180.0f,
                                       360.0f,
                                       _radiusSphere,
                                       _radiusLine,
                                       qs,
                                       _qualityLine,
                                       _materials[im]);

        std::list<float>::const_iterator it1 = angles[im].cbegin();
        it1++;
        std::list<float>::const_iterator it2 = it1;
        it2++;
        while (it2 != angles[im].cend())
        {
            const float &curAngle = (*it1);
            aa = QQuaternion::fromAxisAndAngle(n, curAngle).rotatedVector(a);
            nn = QVector3D ::crossProduct(n, aa).normalized();
            Item3DTorusArc::buildData(
                _out, _center, nn, n, 180.0, _radiusSphere, _radiusLine, qs, _qualityLine, _materials[im]);
            it1++;
            it2++;
        }

        aa = QQuaternion::fromAxisAndAngle(n, angles[im].back()).rotatedVector(a);
        nn = QVector3D ::crossProduct(n, aa).normalized();
        Item3DTorusArcSlice::buildData(_out,
                                       _center,
                                       nn,
                                       n,
                                       0.0f,
                                       180.0f,
                                       0.0f,
                                       180.0f,
                                       _radiusSphere,
                                       _radiusLine,
                                       qs,
                                       _qualityLine,
                                       _materials[im]);

        aa = QQuaternion::fromAxisAndAngle(n, angles[im].front()).rotatedVector(a);
        float ang = angleStepRad;
        for (uint la = 0U; la < cntLa; ++la, ang += angleStepRad)
        {
            const QVector3D cc = _center + n * (std::cos(ang) * _radiusSphere);
            Item3DTorusArc::buildData(_out,
                                      cc,
                                      n,
                                      aa,
                                      angleColor,
                                      std::sin(ang) * _radiusSphere,
                                      _radiusLine,
                                      qs,
                                      _qualityLine,
                                      _materials[im]);
        }
    }
}

Universe1::Video::DBItem3DWireSphereSlice::DBItem3DWireSphereSlice(const std::string &_footageName,

                                                                   std::list<Item3D *> *_items)
    : DBItems3D("wireSphereSlice", _footageName, _items)
{
}

Universe1::Video::Item3DWireSphereSlice *Universe1::Video::DBItem3DWireSphereSlice::add(const QVector3D &_center,
                                                                                        const QVector3D &_normal,
                                                                                        const QVector3D &_arm,
                                                                                        const float _angleLatBeginDeg,
                                                                                        const float _angleLatEndDeg,
                                                                                        const float _angleLonBeginDeg,
                                                                                        const float _angleLonEndDeg,
                                                                                        const float _radiusSphere,
                                                                                        const float _radiusLine,
                                                                                        const uint _qualityLatLong,
                                                                                        const uint _qualitySphere,
                                                                                        const uint _qualityLine,
                                                                                        const bool _visible,
                                                                                        const Material &_material)
{
    Item3DWireSphereSlice *result = new Item3DWireSphereSlice(_center,
                                                              _normal,
                                                              _arm,
                                                              _angleLatBeginDeg,
                                                              _angleLatEndDeg,
                                                              _angleLonBeginDeg,
                                                              _angleLonEndDeg,
                                                              _radiusSphere,
                                                              _radiusLine,
                                                              _qualityLatLong,
                                                              _qualitySphere,
                                                              _qualityLine,
                                                              _visible,
                                                              _material,
                                                              nextName());
    items->push_back(result);
    return result;
}
