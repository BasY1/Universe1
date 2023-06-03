#include "item3dlinearcdots.h"

Universe1::Video::Item3DLineArcDots::Item3DLineArcDots(const QVector3D &_center,
                                                       const QVector3D &_normal,
                                                       const QVector3D &_arm,
                                                       const float _angleDeg,
                                                       const float _radiusCircle,
                                                       const float _radiusLine,
                                                       const uint _multSpace,
                                                       const uint _qualityCircle,
                                                       const uint _qualityLine,
                                                       const bool _visible,
                                                       const Material &_material,
                                                       const std::string &_name)
    : Item3DLineArc(_center,
                    _normal,
                    _arm,
                    _angleDeg,
                    _radiusCircle,
                    _radiusLine,
                    _qualityCircle,
                    _qualityLine,
                    _visible,
                    _material,
                    _name)
    , multSpace(_multSpace, _name + ".multSpace")
{
    props.push_back(&multSpace);
}

void Universe1::Video::Item3DLineArcDots::addData3D(std::list<Data3D> &_out,
                                                    const Shader *,  // _shader,
                                                    const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              radiusCircle.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              multSpace.getValue(_timeStep),
              qualityCircle.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineArcDots::buildData(std::list<Data3D> &_out,
                                                    const QVector3D &_center,
                                                    const QVector3D &_normal,
                                                    const QVector3D &_arm,
                                                    const float _angleDeg,
                                                    const float _radiusCircle,
                                                    const float _radiusLine,
                                                    const uint _multSpace,
                                                    const uint _qualityCircle,
                                                    const uint _qualityLine,
                                                    const Material &_material)
{
    if (qFuzzyIsNull(_angleDeg) || _angleDeg < 0.0f || qFuzzyIsNull(_radiusCircle) || _radiusCircle < 0.0f ||
        qFuzzyIsNull(_radiusLine) || _radiusLine < 0.0f)
        return;

    if (_multSpace == 0U)
    {
        Item3DLineArc::buildData(_out,
                                 _center,
                                 _normal,
                                 _arm,
                                 _angleDeg,
                                 _radiusCircle,
                                 _radiusLine,
                                 _qualityCircle,
                                 _qualityLine,
                                 _material);
        return;
    }

    const float angleRad = Math::toRad<float>(_angleDeg);
    const float len = angleRad * _radiusCircle;
    const float step = _radiusLine * static_cast<float>(_multSpace);
    const QVector3D n = _normal.normalized();
    const QVector3D a1 = perpendicularArm(_arm, n);
    const QVector3D a2 = QQuaternion::fromAxisAndAngle(n, _angleDeg).rotatedVector(a1).normalized();

    if (qFuzzyCompare(len, step) || len < step)
    {
        Item3DSphere::buildData(_out, _center + a1 * _radiusCircle, _radiusLine, _qualityLine, _material);
        Item3DSphere::buildData(_out, _center + a2 * _radiusCircle, _radiusLine, _qualityLine, _material);
        return;
    }

    const float stepAngleRad = step / _radiusCircle;
    const float stepAngle = Math::toDeg<float>(stepAngleRad);
    float t = 0.0f;
    while (t < _angleDeg && !qFuzzyCompare(t, _angleDeg))
    {
        const QVector3D a3 = QQuaternion::fromAxisAndAngle(n, t).rotatedVector(a1).normalized();
        Item3DSphere::buildData(_out, _center + a3 * _radiusCircle, _radiusLine, _qualityLine, _material);
        t += stepAngle;
    }

    Item3DSphere::buildData(_out, _center + a2 * _radiusCircle, _radiusLine, _qualityLine, _material);
}

//

Universe1::Video::DBItem3DLineArcDots::DBItem3DLineArcDots(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineArcDots", _footageName, _items)
{
}

Universe1::Video::Item3DLineArcDots *Universe1::Video::DBItem3DLineArcDots::add(const QVector3D &_center,
                                                                                const QVector3D &_normal,
                                                                                const QVector3D &_arm,
                                                                                const float _angleDeg,
                                                                                const float _radiusCircle,
                                                                                const float _radiusLine,
                                                                                const uint _multSpace,
                                                                                const uint _qualityCircle,
                                                                                const uint _qualityLine,
                                                                                const bool _visible,
                                                                                const Material &_material)
{
    Item3DLineArcDots *result = new Item3DLineArcDots(_center,
                                                      _normal,
                                                      _arm,
                                                      _angleDeg,
                                                      _radiusCircle,
                                                      _radiusLine,
                                                      _multSpace,
                                                      _qualityCircle,
                                                      _qualityLine,
                                                      _visible,
                                                      _material,
                                                      nextName());
    items->push_back(result);
    return result;
}
