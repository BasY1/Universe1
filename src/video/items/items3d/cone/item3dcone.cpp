#include "item3dcone.h"

Universe1::Video::Item3DCone::Item3DCone(const bool _inner,
                                         const QVector3D &_pointBottom,
                                         const QVector3D &_pointTop,
                                         const float _radius,
                                         const uint _quality,
                                         const bool _visible,
                                         const Material &_material,
                                         const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , inner(_inner)
    , pointBottom(_pointBottom, _name + ".pointBottom")
    , pointTop(_pointTop, _name + ".pointTop")
    , radius(_radius, _name + ".radius")
    , quality(_quality, _name + ".quality")

{
    props.push_back(&pointBottom);
    props.push_back(&pointTop);
    props.push_back(&radius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DCone::addData3D(std::list<Data3D> &_out,
                                             const Shader *,  // _shader,
                                             const uint64_t _timeStep) const
{
    buildData(_out,
              pointBottom.getValue(_timeStep),
              pointTop.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DCone::buildData(std::list<Data3D> &_out,
                                             const QVector3D &_pointBottom,
                                             const QVector3D &_pointTop,
                                             const QVector3D &_arm,
                                             const float _radius,
                                             const uint _quality,
                                             const Material &_material,
                                             const bool _inner)
{
    const uint cntCircle = circlePointCount(_quality);
    uint idx = 0U;
    _out.push_back({_material, cntCircle * 2U, cntCircle * 3U});
    addCone(_out.back(), idx, _pointBottom, _pointTop, _arm, _radius, _quality, _inner);
}

void Universe1::Video::Item3DCone::addCone(Data3D &_data,
                                           uint &_idx,
                                           const QVector3D &_pointBottom,
                                           const QVector3D &_pointTop,
                                           const QVector3D &_arm,
                                           const float _radius,
                                           const uint _quality,
                                           const bool _inner)
{
    const uint cntCircle = circlePointCount(_quality);
    const float angleCone = Math::toDeg<float>(std::atan2(_radius, _pointTop.distanceToPoint(_pointBottom)));
    const QVector3D dir = (_pointTop - _pointBottom).normalized();
    const QVector3D arm = _arm.normalized();
    const QQuaternion rot = QQuaternion::fromAxisAndAngle(dir, 360.0 / static_cast<float>(cntCircle));
    const QQuaternion rot2 = QQuaternion::fromAxisAndAngle(QVector3D::crossProduct(arm, dir).normalized(), angleCone);
    const QQuaternion rot3 = QQuaternion::fromAxisAndAngle(dir, 180.0 / static_cast<float>(cntCircle));
    const QVector3D armN = rot2.rotatedVector(arm).normalized();

    QVector3D a = arm;
    QVector3D n = armN;
    for (size_t i = 0UL; i < cntCircle; ++i)
    {
        _data.points.push_back(_pointBottom + a * _radius);
        if (_inner)
            _data.normals.push_back(-n);
        else
            _data.normals.push_back(n);
        a = rot.rotatedVector(a);
        n = rot.rotatedVector(n);
    }

    n = rot3.rotatedVector(armN).normalized();
    for (size_t i = 0UL; i < cntCircle; ++i)
    {
        _data.points.push_back(_pointTop);
        if (_inner)
            _data.normals.push_back(-n);
        else
            _data.normals.push_back(n);
        n = rot.rotatedVector(n);
    }

    if (_inner)
    {
        for (size_t i = 0UL; i < cntCircle - 1UL; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + i + 1U);
            _data.indexes.push_back(_idx + cntCircle + i);
        }

        _data.indexes.push_back(_idx + cntCircle - 1UL);
        _data.indexes.push_back(_idx);
        _data.indexes.push_back(_idx + 2U * cntCircle - 1UL);
    }
    else
    {
        for (size_t i = 0UL; i < cntCircle - 1UL; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + cntCircle + i);
            _data.indexes.push_back(_idx + i + 1U);
        }

        _data.indexes.push_back(_idx + cntCircle - 1UL);
        _data.indexes.push_back(_idx + 2U * cntCircle - 1UL);
        _data.indexes.push_back(_idx);
    }
    _idx += cntCircle * 2U;
}

Universe1::Video::DBItem3DCone::DBItem3DCone(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("cone", _footageName, _items)
{
}

Universe1::Video::Item3DCone *Universe1::Video::DBItem3DCone::add(const bool _inner,
                                                                  const QVector3D &_pointBottom,
                                                                  const QVector3D &_pointTop,
                                                                  const float _radius,
                                                                  const uint _quality,
                                                                  const bool _visible,
                                                                  const Material &_material)
{
    Item3DCone *result =
        new Item3DCone(_inner, _pointBottom, _pointTop, _radius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
