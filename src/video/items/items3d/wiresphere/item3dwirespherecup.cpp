#include "item3dwirespherecup.h"

Universe1::Video::Item3DWireSphereCup::Item3DWireSphereCup(const QVector3D &_center,
                                                           const QVector3D &_normal,
                                                           const QVector3D &_arm,
                                                           const float _angleDeg,
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
    , angleDeg(_angleDeg, _name + ".angleDeg")
{
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DWireSphereCup::addData3D(std::list<Data3D> &_out,
                                                      const Shader *,  // _shader,
                                                      const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              radiusSphere.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityLatLong.getValue(_timeStep),
              qualitySphere.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DWireSphereCup::buildData(std::list<Data3D> &_out,
                                                      const QVector3D &_center,
                                                      const QVector3D &_normal,
                                                      const QVector3D &_arm,
                                                      const float _angleDeg,
                                                      const float _radiusSphere,
                                                      const float _radiusLine,
                                                      const uint _qualityLatLong,
                                                      const uint _qualitySphere,
                                                      const uint _qualityLine,
                                                      const Material &_material)
{
    if (qFuzzyIsNull(_angleDeg) || qFuzzyIsNull(_radiusSphere) || qFuzzyIsNull(_radiusLine) || _angleDeg < 0.0f ||
        _radiusSphere < 0.0f || _radiusLine < 0.0f)
        return;

    if (_angleDeg > 180.0f || qFuzzyCompare(_angleDeg, 180.0f))
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
                                    _material);
        return;
    }

    const uint qs = std::max(_qualityLatLong, _qualitySphere);
    const uint cntLa = _qualityLatLong * 2U + 1U;
    const uint cntLo = (_qualityLatLong + 1U) * 2U;
    const float stepLaDeg = 180.0 / static_cast<float>(cntLa + 1U);
    const float stepLaRad = M_PI / static_cast<float>(cntLa + 1U);
    const float af = 2.0f * _angleDeg;
    const QVector3D n = _normal.normalized();
    const QQuaternion rotLo = QQuaternion::fromAxisAndAngle(n, 180.0f / static_cast<float>(cntLo));

    float ad = 0.0, ar = 0.0;
    while (true)
    {
        const float nextAngle = ad + stepLaDeg;
        if (qFuzzyCompare(nextAngle, _angleDeg))
        {
            ar += stepLaRad;
            const float rc = std::sin(ar) * _radiusSphere;
            const QVector3D cc = _center + n * (std::cos(ar) * _radiusSphere);
            Item3DTorus::buildData(_out, cc, n, _arm, rc, _radiusLine, qs, _qualityLine, _material);
            break;
        }

        if (nextAngle < _angleDeg)
        {
            ad += stepLaDeg;
            ar += stepLaRad;
            const float rc = std::sin(ar) * _radiusSphere;
            const QVector3D cc = _center + n * (std::cos(ar) * _radiusSphere);
            Item3DTorus::buildData(_out, cc, n, _arm, rc, _radiusLine, qs, _qualityLine, _material);
            continue;
        }

        ar = Math::toRad<float>(_angleDeg);
        const float rc = std::sin(ar) * _radiusSphere;
        const QVector3D cc = _center + n * (std::cos(ar) * _radiusSphere);
        Item3DTorus::buildData(_out, cc, n, _arm, rc, _radiusLine, qs, _qualityLine, _material);
        break;
    }

    QVector3D aa = perpendicularArm(_arm, n);
    for (uint lo = 0U; lo < cntLo; lo++, aa = rotLo.rotatedVector(aa).normalized())
    {
        const QVector3D aaa = QQuaternion::fromAxisAndAngle(aa, -_angleDeg).rotatedVector(n).normalized();
        Item3DTorusArc::buildData(_out, _center, aa, aaa, af, _radiusSphere, _radiusLine, qs, _qualityLine, _material);
    }
}

Universe1::Video::DBItem3DWireSphereCup::DBItem3DWireSphereCup(const std::string &_footageName,

                                                               std::list<Item3D *> *_items)
    : DBItems3D("wireSphereCup", _footageName, _items)
{
}

Universe1::Video::Item3DWireSphereCup *Universe1::Video::DBItem3DWireSphereCup::add(const QVector3D &_center,
                                                                                    const QVector3D &_normal,
                                                                                    const QVector3D &_arm,
                                                                                    const float _angleDeg,
                                                                                    const float _radiusSphere,
                                                                                    const float _radiusLine,
                                                                                    const uint _qualityLatLong,
                                                                                    const uint _qualitySphere,
                                                                                    const uint _qualityLine,
                                                                                    const bool _visible,
                                                                                    const Material &_material)
{
    Item3DWireSphereCup *result = new Item3DWireSphereCup(_center,
                                                          _normal,
                                                          _arm,
                                                          _angleDeg,
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
