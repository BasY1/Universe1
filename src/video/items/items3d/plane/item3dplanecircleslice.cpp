#include "item3dplanecircleslice.h"

Universe1::Video::Item3DPlaneCircleSlice::Item3DPlaneCircleSlice(const QVector3D &_center,
                                                                 const QVector3D &_normal,
                                                                 const QVector3D &_arm,
                                                                 const float _radius,
                                                                 const float _angleDeg,
                                                                 const uint _quality,
                                                                 const bool _visible,
                                                                 const Material &_material,
                                                                 const std::string &_name)
    : Item3DPlaneCircle(_center, _normal, _radius, _quality, _visible, _material, _name)
    , arm(_arm, _name + ".arm")
    , angleDeg(_angleDeg, _name + ".angleDeg")
{
    props.push_back(&arm);
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DPlaneCircleSlice::addData3D(std::list<Data3D> &_out,
                                                         const Shader *,  // _shader,
                                                         const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              radius.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DPlaneCircleSlice::buildData(std::list<Data3D> &_out,
                                                         const QVector3D &_center,
                                                         const QVector3D &_normal,
                                                         const QVector3D &_arm,
                                                         const float _radius,
                                                         const float _angleDeg,
                                                         const uint _quality,
                                                         const Material &_material)
{
    if (qFuzzyIsNull(_angleDeg))
        return;

    const uint cntCircle = circlePointCount(_quality);
    const float sign = _angleDeg > 0.0f ? 1.0f : -1.0f;
    const float stepAngleDeg = sign * 360.0f / static_cast<float>(cntCircle);
    uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    if (!qFuzzyCompare(angleDegFromSteps, _angleDeg))
        steps++;

    uint idx = 0U;
    _out.push_back({_material, steps + 2U, steps * 3U});
    addCircleSlice(_out.back(), idx, _center, _normal, _arm, _radius, _angleDeg, _quality);
}

void Universe1::Video::Item3DPlaneCircleSlice::addCircleSlice(Data3D &_data,
                                                              uint &_idx,
                                                              const QVector3D &_center,
                                                              const QVector3D &_normal,
                                                              const QVector3D &_arm,
                                                              const float _radius,
                                                              const float _angleDeg,
                                                              const uint _quality)
{
    if (qFuzzyIsNull(_angleDeg))
        return;

    const uint cntCircle = circlePointCount(_quality);
    const float sign = _angleDeg > 0.0f ? 1.0f : -1.0f;
    const float stepAngleDeg = sign * 360.0f / static_cast<float>(cntCircle);
    const uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    const bool addRest = !qFuzzyCompare(angleDegFromSteps, _angleDeg);

    const QVector3D n = _normal.normalized();
    const QQuaternion rotStep = QQuaternion::fromAxisAndAngle(n, stepAngleDeg);
    const QVector3D aa = _arm.normalized();
    QVector3D a = aa;

    _data.points.push_back(_center);
    _data.normals.push_back(n);

    for (uint i = 0U; i <= steps; ++i, a = rotStep.rotatedVector(a).normalized())
    {
        _data.points.push_back(_center + a * _radius);
        _data.normals.push_back(n);
    }

    if (addRest)
    {
        _data.points.push_back(_center +
                               QQuaternion::fromAxisAndAngle(n, _angleDeg).rotatedVector(aa).normalized() * _radius);
        _data.normals.push_back(n);
    }

    if (_angleDeg < 0.0f)
    {
        for (uint i = 0U; i < steps; ++i)
        {
            _data.indexes.push_back(_idx);
            _data.indexes.push_back(_idx + 1U + i);
            _data.indexes.push_back(_idx + 2U + i);
        }
        if (addRest)
        {
            _data.indexes.push_back(_idx);
            _data.indexes.push_back(_idx + steps + 1U);
            _data.indexes.push_back(_idx + steps + 2U);
        }
    }
    else
    {
        for (uint i = 0U; i < steps; ++i)
        {
            _data.indexes.push_back(_idx);
            _data.indexes.push_back(_idx + 2U + i);
            _data.indexes.push_back(_idx + 1U + i);
        }
        if (addRest)
        {
            _data.indexes.push_back(_idx);
            _data.indexes.push_back(_idx + steps + 2U);
            _data.indexes.push_back(_idx + steps + 1U);
        }
    }

    _idx += steps + 2U;
    if (addRest)
        ++_idx;
}

Universe1::Video::DBItem3DPlaneCircleSlice::DBItem3DPlaneCircleSlice(const std::string &_footageName,
                                                                     std::list<Item3D *> *_items)
    : DBItems3D("planeCircleSlice", _footageName, _items)
{
}

Universe1::Video::Item3DPlaneCircleSlice *Universe1::Video::DBItem3DPlaneCircleSlice::add(const QVector3D &_center,
                                                                                          const QVector3D &_normal,
                                                                                          const QVector3D &_arm,
                                                                                          const float _radius,
                                                                                          const float _angleDeg,
                                                                                          const uint _quality,
                                                                                          const bool _visible,
                                                                                          const Material &_material)
{
    Item3DPlaneCircleSlice *result = new Item3DPlaneCircleSlice(
        _center, _normal, _arm, _radius, _angleDeg, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
