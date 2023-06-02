#include "item3dcylinderslice.h"

Universe1::Video::Item3DCylinderSlice::Item3DCylinderSlice(const bool _inner,
                                                           const QVector3D &_point1,
                                                           const QVector3D &_point2,
                                                           const QVector3D &_arm,
                                                           const float _radius1,
                                                           const float _radius2,
                                                           const float _angleDeg,
                                                           const uint _quality,
                                                           const bool _visible,
                                                           const Material &_material,
                                                           const std::string &_name)
    : Item3DCylinder(_inner, _point1, _point2, _radius1, _radius2, _quality, _visible, _material, _name)
    , arm(_arm, _name + ".arm")
    , angleDeg(_angleDeg, _name + ".angleDeg")
{
    props.push_back(&arm);
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DCylinderSlice::addData3D(std::list<Data3D> &_out,
                                                      const Shader *,  // _shader,
                                                      const uint64_t _timeStep) const
{
    buildData(_out,
              point1.getValue(_timeStep),
              point2.getValue(_timeStep),
              arm.getValue(_timeStep),
              radius1.getValue(_timeStep),
              radius2.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DCylinderSlice::buildData(std::list<Data3D> &_out,
                                                      const QVector3D &_point1,
                                                      const QVector3D &_point2,
                                                      const QVector3D &_arm,
                                                      const float _radius1,
                                                      const float _radius2,
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
    _out.push_back({_material, (steps + 1U) * 2U, steps * 6U});
    addCylinderSlice(_out.back(), idx, _point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, _inner);
}

void Universe1::Video::Item3DCylinderSlice::addCylinderSlice(Data3D &_data,
                                                             uint &_idx,
                                                             const QVector3D &_point1,
                                                             const QVector3D &_point2,
                                                             const QVector3D &_arm,
                                                             const float _radius1,
                                                             const float _radius2,
                                                             const float _angleDeg,
                                                             const uint _quality,
                                                             const bool _inner)
{
    const uint cntCircle = circlePointCount(_quality);
    const float sign = _angleDeg > 0.0f ? 1.0f : -1.0f;
    const float stepAngleDeg = sign * 360.0f / static_cast<float>(cntCircle);
    const uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    const bool addRest = !qFuzzyCompare(angleDegFromSteps, _angleDeg);
    const uint offsetIdx = steps + (addRest ? 2U : 1U);

    const QVector3D dir = (_point2 - _point1).normalized();
    const QQuaternion rotStep = QQuaternion::fromAxisAndAngle(dir, stepAngleDeg);
    const QVector3D aa = _arm.normalized();
    QVector3D a = aa;

    for (uint i = 0U; i <= steps; ++i, a = rotStep.rotatedVector(a).normalized())
    {
        _data.points.push_back(_point1 + a * _radius1);
        if (_inner)
            _data.normals.push_back(-a);
        else
            _data.normals.push_back(a);
    }

    if (addRest)
    {
        a = QQuaternion::fromAxisAndAngle(dir, _angleDeg).rotatedVector(aa).normalized();
        _data.points.push_back(_point1 + a * _radius1);
        if (_inner)
            _data.normals.push_back(-a);
        else
            _data.normals.push_back(a);
    }

    a = aa;
    for (uint i = 0U; i <= steps; ++i, a = rotStep.rotatedVector(a).normalized())
    {
        _data.points.push_back(_point2 + a * _radius2);
        if (_inner)
            _data.normals.push_back(-a);
        else
            _data.normals.push_back(a);
    }

    if (addRest)
    {
        a = QQuaternion::fromAxisAndAngle(dir, _angleDeg).rotatedVector(aa).normalized();
        _data.points.push_back(_point2 + a * _radius2);
        if (_inner)
            _data.normals.push_back(-a);
        else
            _data.normals.push_back(a);
    }

    if (_inner == (_angleDeg < 0.0f))
    {
        for (uint i = 0U; i < steps; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + offsetIdx + i);
            _data.indexes.push_back(_idx + offsetIdx + i + 1U);

            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + offsetIdx + i + 1U);
            _data.indexes.push_back(_idx + i + 1U);
        }

        if (addRest)
        {
            _data.indexes.push_back(_idx + steps);
            _data.indexes.push_back(_idx + offsetIdx + steps);
            _data.indexes.push_back(_idx + offsetIdx + steps + 1U);

            _data.indexes.push_back(_idx + steps);
            _data.indexes.push_back(_idx + offsetIdx + steps + 1U);
            _data.indexes.push_back(_idx + steps + 1U);
        }
    }
    else
    {
        for (uint i = 0U; i < steps; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + offsetIdx + i + 1U);
            _data.indexes.push_back(_idx + offsetIdx + i);

            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + i + 1U);
            _data.indexes.push_back(_idx + offsetIdx + i + 1U);
        }

        if (addRest)
        {
            _data.indexes.push_back(_idx + steps);
            _data.indexes.push_back(_idx + offsetIdx + steps + 1U);
            _data.indexes.push_back(_idx + offsetIdx + steps);

            _data.indexes.push_back(_idx + steps);
            _data.indexes.push_back(_idx + steps + 1U);
            _data.indexes.push_back(_idx + offsetIdx + steps + 1U);
        }
    }
    _idx += 2U * offsetIdx;
}

Universe1::Video::DBItem3DCylinderSlice::DBItem3DCylinderSlice(const std::string &_footageName,
                                                               std::list<Item3D *> *_items)
    : DBItems3D("cylinderSlice", _footageName, _items)
{
}

Universe1::Video::Item3DCylinderSlice *Universe1::Video::DBItem3DCylinderSlice::add(const bool _inner,
                                                                                    const QVector3D &_point1,
                                                                                    const QVector3D &_point2,
                                                                                    const QVector3D &_arm,
                                                                                    const float _radius1,
                                                                                    const float _radius2,
                                                                                    const float _angleDeg,
                                                                                    const uint _quality,
                                                                                    const bool _visible,
                                                                                    const Material &_material)
{
    Item3DCylinderSlice *result = new Item3DCylinderSlice(
        _inner, _point1, _point2, _arm, _radius1, _radius2, _angleDeg, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
