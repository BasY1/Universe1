#include "item3dwiresphere.h"

Universe1::Video::Item3DWireSphere::Item3DWireSphere(const QVector3D &_center,
                                                     const QVector3D &_normal,
                                                     const QVector3D &_arm,
                                                     const float _radiusSphere,
                                                     const float _radiusLine,
                                                     const uint _qualityLatLong,
                                                     const uint _qualitySphere,
                                                     const uint _qualityLine,
                                                     const bool _visible,
                                                     const Material &_material,
                                                     const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")
    , radiusSphere(_radiusSphere, _name + ".radiusSphere")
    , radiusLine(_radiusLine, _name + ".radiusLine")
    , qualityLatLong(_qualityLatLong, _name + ".qualityLatLong")
    , qualitySphere(_qualitySphere, _name + ".qualitySphere")
    , qualityLine(_qualityLine, _name + ".qualityLine")
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&radiusSphere);
    props.push_back(&radiusLine);
    props.push_back(&qualityLatLong);
    props.push_back(&qualitySphere);
    props.push_back(&qualityLine);
}

void Universe1::Video::Item3DWireSphere::addData3D(std::list<Data3D> &_out,
                                                   const Shader *,  // _shader,
                                                   const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              radiusSphere.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityLatLong.getValue(_timeStep),
              qualitySphere.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DWireSphere::buildData(std::list<Data3D> &_out,
                                                   const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
                                                   const float _radiusSphere,
                                                   const float _radiusLine,
                                                   const uint _qualityLatLong,
                                                   const uint _qualitySphere,
                                                   const uint _qualityLine,
                                                   const Material &_material)
{
    if (qFuzzyIsNull(_radiusSphere) || qFuzzyIsNull(_radiusLine) || _radiusSphere < 0.0f || _radiusLine < 0.0f)
        return;

    const uint qs = std::max(_qualityLatLong, _qualitySphere);
    const uint cntLa = _qualityLatLong * 2U + 1U;
    const uint cntLo = (_qualityLatLong + 1U) * 2U;
    const float stepLaRad = M_PI / static_cast<float>(cntLa + 1U);
    const QVector3D n = _normal.normalized();
    const QQuaternion rotLo = QQuaternion::fromAxisAndAngle(n, 180.0f / static_cast<float>(cntLo));
    float angle = stepLaRad;
    for (uint la = 0U; la < cntLa; la++, angle += stepLaRad)
    {
        const float rc = std::sin(angle) * _radiusSphere;
        const QVector3D cc = _center + n * (std::cos(angle) * _radiusSphere);
        Item3DTorus::buildData(_out, cc, n, _arm, rc, _radiusLine, qs, _qualityLine, _material);
    }

    QVector3D aa = perpendicularArm(_arm, n);
    for (uint lo = 0U; lo < cntLo; lo++, aa = rotLo.rotatedVector(aa).normalized())
        Item3DTorus::buildData(_out, _center, aa, _radiusSphere, _radiusLine, qs, _qualityLine, _material);
}

Universe1::Video::DBItem3DWireSphere::DBItem3DWireSphere(const std::string &_footageName,

                                                         std::list<Item3D *> *_items)
    : DBItems3D("wireSphere", _footageName, _items)
{
}

Universe1::Video::Item3DWireSphere *Universe1::Video::DBItem3DWireSphere::add(const QVector3D &_center,
                                                                              const QVector3D &_normal,
                                                                              const QVector3D &_arm,
                                                                              const float _radiusSphere,
                                                                              const float _radiusLine,
                                                                              const uint _qualityLatLong,
                                                                              const uint _qualitySphere,
                                                                              const uint _qualityLine,
                                                                              const bool _visible,
                                                                              const Material &_material)
{
    Item3DWireSphere *result = new Item3DWireSphere(_center,
                                                    _normal,
                                                    _arm,
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
