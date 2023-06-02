#include "item3dplanecircle.h"

Universe1::Video::Item3DPlaneCircle::Item3DPlaneCircle(const QVector3D &_center,
                                                       const QVector3D &_normal,
                                                       const float _radius,
                                                       const uint _quality,
                                                       const bool _visible,
                                                       const Material &_material,
                                                       const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , radius(_radius, _name + ".radius")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&radius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DPlaneCircle::addData3D(std::list<Data3D> &_out,
                                                    const Shader *,  // _shader,
                                                    const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DPlaneCircle::buildData(std::list<Data3D> &_out,
                                                    const QVector3D &_center,
                                                    const QVector3D &_normal,
                                                    const QVector3D &_arm,
                                                    const float _radius,
                                                    const uint _quality,
                                                    const Material &_material)
{
    const uint cntCircle = circlePointCount(_quality);
    uint idx = 0U;
    _out.push_back({_material, cntCircle + 1U, cntCircle * 3U});
    addCirclePlane(_out.back(), idx, _center, _normal, _arm, _radius, _quality);
}

void Universe1::Video::Item3DPlaneCircle::addCirclePlane(Data3D &_data,
                                                         uint &_idx,
                                                         const QVector3D &_center,
                                                         const QVector3D &_normal,
                                                         const QVector3D &_arm,
                                                         const float _radius,
                                                         const uint _quality)
{
    const uint cntCircle = circlePointCount(_quality);
    const QQuaternion rot = QQuaternion::fromAxisAndAngle(_normal, 360.0 / static_cast<float>(cntCircle));

    _data.points.push_back(_center);
    _data.normals.push_back(_normal);

    QVector3D a = _arm.normalized();
    for (size_t i = 0UL; i < cntCircle; ++i, a = rot.rotatedVector(a).normalized())
    {
        _data.points.push_back(_center + a * _radius);
        _data.normals.push_back(_normal);
    }

    for (size_t i = 0UL; i < cntCircle - 1UL; ++i)
    {
        _data.indexes.push_back(_idx);
        _data.indexes.push_back(_idx + 2U + i);
        _data.indexes.push_back(_idx + 1U + i);
    }
    _data.indexes.push_back(_idx);
    _data.indexes.push_back(_idx + 1UL);
    _data.indexes.push_back(_idx + cntCircle);

    _idx += cntCircle + 1UL;
}

Universe1::Video::DBItem3DPlaneCircle::DBItem3DPlaneCircle(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("planeCircle", _footageName, _items)
{
}

Universe1::Video::Item3DPlaneCircle *Universe1::Video::DBItem3DPlaneCircle::add(const QVector3D &_center,
                                                                                const QVector3D &_normal,
                                                                                const float _radius,
                                                                                const uint _quality,
                                                                                const bool _visible,
                                                                                const Material &_material)
{
    Item3DPlaneCircle *result =
        new Item3DPlaneCircle(_center, _normal, _radius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
