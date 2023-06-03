#include "item3dlinecircle.h"

Universe1::Video::Item3DLineCircle::Item3DLineCircle(const QVector3D &_center,
                                                     const QVector3D &_normal,
                                                     const float _radiusCircle,
                                                     const float _radiusLine,
                                                     const uint _qualityCircle,
                                                     const uint _qualityLine,
                                                     const bool _visible,
                                                     const Material &_material,
                                                     const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , radiusCircle(_radiusCircle, _name + ".radiusCircle")
    , radiusLine(_radiusLine, _name + ".radiusLine")
    , qualityCircle(_qualityCircle, _name + ".qualityCircle")
    , qualityLine(_qualityLine, _name + ".qualityLine")
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&radiusCircle);
    props.push_back(&radiusLine);
    props.push_back(&qualityCircle);
    props.push_back(&qualityLine);
}

void Universe1::Video::Item3DLineCircle::addData3D(std::list<Data3D> &_out,
                                                   const Shader *,  // _shader,
                                                   const uint64_t _timeStep) const
{
    Item3DTorus::buildData(_out,
                           center.getValue(_timeStep),
                           normal.getValue(_timeStep),
                           radiusCircle.getValue(_timeStep),
                           radiusLine.getValue(_timeStep),
                           qualityCircle.getValue(_timeStep),
                           qualityLine.getValue(_timeStep),
                           material.getValue(_timeStep));
}

Universe1::Video::DBItem3DLineCircle::DBItem3DLineCircle(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineCircle", _footageName, _items)
{
}

Universe1::Video::Item3DLineCircle *Universe1::Video::DBItem3DLineCircle::add(const QVector3D &_center,
                                                                              const QVector3D &_normal,
                                                                              const float _radiusCircle,
                                                                              const float _radiusLine,
                                                                              const uint _qualityCircle,
                                                                              const uint _qualityLine,
                                                                              const bool _visible,
                                                                              const Material &_material)
{
    Item3DLineCircle *result = new Item3DLineCircle(
        _center, _normal, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
