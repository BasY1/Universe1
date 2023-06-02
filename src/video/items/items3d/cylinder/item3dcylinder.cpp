#include "item3dcylinder.h"

Universe1::Video::Item3DCylinder::Item3DCylinder(const bool _inner,
                                                 const QVector3D &_point1,
                                                 const QVector3D &_point2,
                                                 const float _radius1,
                                                 const float _radius2,
                                                 const uint _quality,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , inner(_inner)
    , point1(_point1, _name + ".point1")
    , point2(_point2, _name + ".point2")
    , radius1(_radius1, _name + ".radius1")
    , radius2(_radius2, _name + ".radius2")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&point1);
    props.push_back(&point2);
    props.push_back(&radius1);
    props.push_back(&radius2);
    props.push_back(&quality);
}

void Universe1::Video::Item3DCylinder::addData3D(std::list<Data3D> &_out,
                                                 const Shader *,  // _shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              point1.getValue(_timeStep),
              point2.getValue(_timeStep),
              radius1.getValue(_timeStep),
              radius2.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DCylinder::buildData(std::list<Data3D> &_out,
                                                 const QVector3D &_point1,
                                                 const QVector3D &_point2,
                                                 const QVector3D &_arm,
                                                 const float _radius1,
                                                 const float _radius2,
                                                 const uint _quality,
                                                 const Material &_material,
                                                 const bool _inner)
{
    const uint cntCircle = circlePointCount(_quality);
    uint idx = 0U;
    _out.push_back({_material, cntCircle * 2U, cntCircle * 6U});
    addCylinder(_out.back(), idx, _point1, _point2, _arm, _radius1, _radius2, _quality, _inner);
}

void Universe1::Video::Item3DCylinder::addCylinder(Data3D &_data,
                                                   uint &_idx,
                                                   const QVector3D &_point1,
                                                   const QVector3D &_point2,
                                                   const QVector3D &_arm,
                                                   const float _radius1,
                                                   const float _radius2,
                                                   const uint _quality,
                                                   const bool _inner)
{
    const uint cntCircle = circlePointCount(_quality);
    const QVector3D dir = (_point2 - _point1).normalized();
    const QVector3D arm = _arm.normalized();
    const QQuaternion rot = QQuaternion::fromAxisAndAngle(dir, 360.0 / static_cast<float>(cntCircle));

    QVector3D a = arm;
    for (size_t i = 0UL; i < cntCircle; ++i, a = rot.rotatedVector(a).normalized())
    {
        _data.points.push_back(_point1 + a * _radius1);
        if (_inner)
            _data.normals.push_back(-a);
        else
            _data.normals.push_back(a);
    }

    a = arm;
    for (size_t i = 0UL; i < cntCircle; ++i, a = rot.rotatedVector(a).normalized())
    {
        _data.points.push_back(_point2 + a * _radius2);
        if (_inner)
            _data.normals.push_back(-a);
        else
            _data.normals.push_back(a);
    }

    if (_inner)
    {
        for (size_t i = 0UL; i < cntCircle - 1UL; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + cntCircle + i + 1U);
            _data.indexes.push_back(_idx + cntCircle + i);

            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + i + 1U);
            _data.indexes.push_back(_idx + cntCircle + i + 1U);
        }

        _data.indexes.push_back(_idx + cntCircle - 1UL);
        _data.indexes.push_back(_idx + cntCircle);
        _data.indexes.push_back(_idx + 2U * cntCircle - 1UL);

        _data.indexes.push_back(_idx + cntCircle - 1UL);
        _data.indexes.push_back(_idx);
        _data.indexes.push_back(_idx + cntCircle);
    }
    else
    {
        for (size_t i = 0UL; i < cntCircle - 1UL; ++i)
        {
            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + cntCircle + i);
            _data.indexes.push_back(_idx + cntCircle + i + 1U);

            _data.indexes.push_back(_idx + i);
            _data.indexes.push_back(_idx + cntCircle + i + 1U);
            _data.indexes.push_back(_idx + i + 1U);
        }

        _data.indexes.push_back(_idx + cntCircle - 1UL);
        _data.indexes.push_back(_idx + 2U * cntCircle - 1UL);
        _data.indexes.push_back(_idx + cntCircle);

        _data.indexes.push_back(_idx + cntCircle - 1UL);
        _data.indexes.push_back(_idx + cntCircle);
        _data.indexes.push_back(_idx);
    }
    _idx += cntCircle * 2UL;
}

Universe1::Video::DBItem3DCylinder::DBItem3DCylinder(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("cylinder", _footageName, _items)
{
}

Universe1::Video::Item3DCylinder *Universe1::Video::DBItem3DCylinder::add(const bool _inner,
                                                                          const QVector3D &_point1,
                                                                          const QVector3D &_point2,
                                                                          const float _radius1,
                                                                          const float _radius2,
                                                                          const uint _quality,
                                                                          const bool _visible,
                                                                          const Material &_material)
{
    Item3DCylinder *result =
        new Item3DCylinder(_inner, _point1, _point2, _radius1, _radius2, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
