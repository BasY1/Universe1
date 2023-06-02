#include "item3dplane.h"

Universe1::Video::Item3DPlane::Item3DPlane(const QVector3D &_center,
                                           const QVector3D &_arm1,
                                           const QVector3D &_arm2,
                                           const bool _visible,
                                           const Material &_material,
                                           const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , arm1(_arm1, _name + ".arm1")
    , arm2(_arm2, _name + ".arm2")
{
    props.push_back(&center);
    props.push_back(&arm1);
    props.push_back(&arm2);
}

void Universe1::Video::Item3DPlane::addData3D(std::list<Data3D> &_out,
                                              const Shader *,  //_shader,
                                              const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              arm1.getValue(_timeStep),
              arm2.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DPlane::buildData(std::list<Data3D> &_out,
                                              const QVector3D &_center,
                                              const QVector3D &_arm1,
                                              const QVector3D &_arm2,
                                              const Material &_material)
{
    const QVector3D n = QVector3D::crossProduct(_arm1, _arm2).normalized();
    const std::array<QVector3D, 4> p = {
        _center - _arm1 - _arm2, _center + _arm1 - _arm2, _center + _arm1 + _arm2, _center - _arm1 + _arm2};

    _out.push_back({});
    Data3D &out = _out.back();
    out.material = _material;
    out.points = {p[0], p[1], p[2], p[3]};
    out.normals = {n, n, n, n};
    out.indexes = {0U, 2U, 1U, 0U, 3U, 2U};
}

Universe1::Video::DBItem3DPlane::DBItem3DPlane(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("plane", _footageName, _items)
{
}

Universe1::Video::Item3DPlane *Universe1::Video::DBItem3DPlane::add(const QVector3D &_center,
                                                                    const QVector3D &_arm1,
                                                                    const QVector3D &_arm2,
                                                                    const bool _visible,
                                                                    const Material &_material)
{
    Item3DPlane *result = new Item3DPlane(_center, _arm1, _arm2, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
