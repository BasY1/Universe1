#include "item3dconeslice.h"

Universe1::Video::Item3DConeSlice::Item3DConeSlice(const bool _inner,
                                                   const QVector3D &_pointBottom,
                                                   const QVector3D &_pointTop,
                                                   const QVector3D &_arm,
                                                   const float _radius,
                                                   const float _angleDeg,
                                                   const uint _quality,
                                                   const bool _visible,
                                                   const Material &_material,
                                                   const std::string &_name)
    : Item3DCone(_inner, _pointBottom, _pointTop, _radius, _quality, _visible, _material, _name)
    , arm(_arm, _name + ".arm")
    , angleDeg(_angleDeg, _name + ".angleDeg")

{
    props.push_back(&arm);
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DConeSlice::addData3D(std::list<Data3D> &_out,
                                                  const Shader *,  // _shader,
                                                  const uint64_t _timeStep) const
{
    buildData(_out,
              pointBottom.getValue(_timeStep),
              pointTop.getValue(_timeStep),
              arm.getValue(_timeStep),
              radius.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DConeSlice::buildData(std::list<Data3D> &_out,
                                                  const QVector3D &_pointBottom,
                                                  const QVector3D &_pointTop,
                                                  const QVector3D &_arm,
                                                  const float _radius,
                                                  const float _angleDeg,
                                                  const uint _quality,
                                                  const Material &_material,
                                                  const bool _inner)
{
    if (qFuzzyIsNull(_angleDeg))
        return;

    const uint cntCircle = circlePointCount(_quality);
    const float sign = _angleDeg > 0.0f ? 1.0f : -1.0f;
    const float stepAngleDeg = sign * 360.0 / static_cast<float>(cntCircle);
    uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    if (!qFuzzyCompare(angleDegFromSteps, _angleDeg))
        steps++;

    uint idx = 0U;
    _out.push_back({_material, 2U * steps + 1U, steps * 3U});
    addConeSlice(_out.back(), idx, _pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, _inner);
}

void Universe1::Video::Item3DConeSlice::addConeSlice(Data3D &_data,
                                                     uint &_idx,
                                                     const QVector3D &_pointBottom,
                                                     const QVector3D &_pointTop,
                                                     const QVector3D &_arm,
                                                     const float _radius,
                                                     const float _angleDeg,
                                                     const uint _quality,
                                                     const bool _inner)
{
    if (qFuzzyIsNull(_angleDeg))
        return;

    const float angleCone = Math::toDeg<float>(std::atan2(_radius, _pointTop.distanceToPoint(_pointBottom)));
    const uint cntCircle = circlePointCount(_quality);
    const float sign = _angleDeg > 0.0f ? 1.0f : -1.0f;
    const float stepAngleDeg = sign * 360.0f / static_cast<float>(cntCircle);
    const uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    const bool addRest = !qFuzzyCompare(angleDegFromSteps, _angleDeg);
    const uint offsetIdx = steps + (addRest ? 2U : 1U);

    const QVector3D dir = (_pointTop - _pointBottom).normalized();
    const QVector3D aa = _arm.normalized();
    const QQuaternion rot = QQuaternion::fromAxisAndAngle(dir, stepAngleDeg);
    const QQuaternion rotSide = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(aa, dir).normalized(), angleCone);
    const QQuaternion rot3 = QQuaternion::fromAxisAndAngle(dir, stepAngleDeg * 0.5f);
    const QVector3D nn = rotSide.rotatedVector(aa).normalized();

    QVector3D a = aa;
    QVector3D n = nn;
    for (uint i = 0U; i <= steps; ++i, a = rot.rotatedVector(a).normalized(), n = rot.rotatedVector(n).normalized())
    {
        _data.points.push_back(_pointBottom + a * _radius);
        if (_inner)
            _data.normals.push_back(-n);
        else
            _data.normals.push_back(n);
    }

    if (addRest)
    {
        const QQuaternion rotLast = QQuaternion::fromAxisAndAngle(dir, _angleDeg);
        _data.points.push_back(_pointBottom + rotLast.rotatedVector(aa).normalized() * _radius);
        if (_inner)
            _data.normals.push_back(-rotLast.rotatedVector(nn).normalized());
        else
            _data.normals.push_back(rotLast.rotatedVector(nn).normalized());
    }

    n = rot3.rotatedVector(nn).normalized();
    for (uint i = 0U; i < steps; ++i, n = rot.rotatedVector(n).normalized())
    {
        _data.points.push_back(_pointTop);
        if (_inner)
            _data.normals.push_back(-n);
        else
            _data.normals.push_back(n);
    }

    if (addRest)
    {
        const QQuaternion rotLast = QQuaternion::fromAxisAndAngle(dir, (_angleDeg + angleDegFromSteps) * 0.5f);
        _data.points.push_back(_pointTop);
        if (_inner)
            _data.normals.push_back(-rotLast.rotatedVector(nn).normalized());
        else
            _data.normals.push_back(rotLast.rotatedVector(nn).normalized());
    }

    if (_inner == (_angleDeg < 0.0f))
    {
        for (uint i = 0U; i < steps; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + offsetIdx + i);
            _data.indexes.push_back(_idx + i + 1U);
        }
        if (addRest)
        {
            _data.indexes.push_back(_idx + steps);
            _data.indexes.push_back(_idx + offsetIdx + steps);
            _data.indexes.push_back(_idx + steps + 1U);
        }
    }
    else
    {
        for (uint i = 0U; i < steps; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + i + 1U);
            _data.indexes.push_back(_idx + offsetIdx + i);
        }
        if (addRest)
        {
            _data.indexes.push_back(_idx + steps);
            _data.indexes.push_back(_idx + steps + 1U);
            _data.indexes.push_back(_idx + offsetIdx + steps);
        }
    }

    _idx += 2U * (steps + (addRest ? 1U : 0U)) + 1U;
}

Universe1::Video::DBItem3DConeSlice::DBItem3DConeSlice(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("coneSlice", _footageName, _items)
{
}

Universe1::Video::Item3DConeSlice *Universe1::Video::DBItem3DConeSlice::add(const bool _inner,
                                                                            const QVector3D &_pointBottom,
                                                                            const QVector3D &_pointTop,
                                                                            const QVector3D &_arm,
                                                                            const float _radius,
                                                                            const float _angleDeg,
                                                                            const uint _quality,
                                                                            const bool _visible,
                                                                            const Material &_material)
{
    Item3DConeSlice *result = new Item3DConeSlice(
        _inner, _pointBottom, _pointTop, _arm, _radius, _angleDeg, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
