#include "item3dlinearcdash.h"

Universe1::Video::Item3DLineArcDash::Item3DLineArcDash(const QVector3D &_center,
                                                       const QVector3D &_normal,
                                                       const QVector3D &_arm,
                                                       const float _angleDeg,
                                                       const float _radiusCircle,
                                                       const float _radiusLine,
                                                       const uint _multDash,
                                                       const uint _multSpace,
                                                       const uint _countDot,
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
    , multDash(_multDash, _name + ".multDash")
    , multSpace(_multSpace, _name + ".multSpace")
    , countDot(_countDot, _name + ".countDot")
{
    props.push_back(&multDash);
    props.push_back(&multSpace);
    props.push_back(&countDot);
}

void Universe1::Video::Item3DLineArcDash::addData3D(std::list<Data3D> &_out,
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
              multDash.getValue(_timeStep),
              multSpace.getValue(_timeStep),
              countDot.getValue(_timeStep),
              qualityCircle.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineArcDash::buildData(std::list<Data3D> &_out,
                                                    const QVector3D &_center,
                                                    const QVector3D &_normal,
                                                    const QVector3D &_arm,
                                                    const float _angleDeg,
                                                    const float _radiusCircle,
                                                    const float _radiusLine,
                                                    const uint _multDash,
                                                    const uint _multSpace,
                                                    const uint _countDot,
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

    const uint md = std::max(1U, _multDash);
    const float angleRad = Math::toRad<float>(_angleDeg);
    const float len = angleRad * _radiusCircle;
    const float stepDash = _radiusLine * static_cast<float>(md);
    const float minLen = 2.0f * stepDash;
    if (qFuzzyCompare(len, minLen) || len < minLen)
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

    const QVector3D n = _normal.normalized();
    const QVector3D a1 = perpendicularArm(_arm, n);

    const float stepAngleRad = _radiusLine / _radiusCircle;
    const float stepAngle = Math::toDeg<float>(stepAngleRad);
    const float dashAngle = stepAngle * static_cast<float>(md);
    const float spaceAngle = stepAngle * static_cast<float>(_multSpace);
    const float stepFullAngle = dashAngle + spaceAngle + static_cast<float>(_countDot) * spaceAngle;

    QVector3D a2;
    float t = 0.0f;
    while (t + stepFullAngle < _angleDeg && !qFuzzyCompare(t + stepFullAngle, _angleDeg))
    {
        a2 = QQuaternion::fromAxisAndAngle(n, t).rotatedVector(a1).normalized();
        Item3DLineArc::buildData(
            _out, _center, n, a2, dashAngle, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, _material);

        for (uint i = 0U; i < _countDot; ++i)
        {
            a2 = QQuaternion::fromAxisAndAngle(n, t + dashAngle + spaceAngle + static_cast<float>(i) * spaceAngle)
                     .rotatedVector(a1)
                     .normalized();
            Item3DSphere::buildData(_out, _center + a2 * _radiusCircle, _radiusLine, _qualityLine, _material);
        }

        t += stepFullAngle;
    }

    a2 = QQuaternion::fromAxisAndAngle(n, t).rotatedVector(a1).normalized();
    Item3DLineArc::buildData(
        _out, _center, n, a2, _angleDeg - t, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, _material);
}

//

Universe1::Video::DBItem3DLineArcDash::DBItem3DLineArcDash(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineArcDash", _footageName, _items)
{
}

Universe1::Video::Item3DLineArcDash *Universe1::Video::DBItem3DLineArcDash::add(const QVector3D &_center,
                                                                                const QVector3D &_normal,
                                                                                const QVector3D &_arm,
                                                                                const float _angleDeg,
                                                                                const float _radiusCircle,
                                                                                const float _radiusLine,
                                                                                const uint _multDash,
                                                                                const uint _multSpace,
                                                                                const uint _countDot,
                                                                                const uint _qualityCircle,
                                                                                const uint _qualityLine,
                                                                                const bool _visible,
                                                                                const Material &_material)
{
    Item3DLineArcDash *result = new Item3DLineArcDash(_center,
                                                      _normal,
                                                      _arm,
                                                      _angleDeg,
                                                      _radiusCircle,
                                                      _radiusLine,
                                                      _multDash,
                                                      _multSpace,
                                                      _countDot,
                                                      _qualityCircle,
                                                      _qualityLine,
                                                      _visible,
                                                      _material,
                                                      nextName());
    items->push_back(result);
    return result;
}
