#include "item3dlinedots.h"

Universe1::Video::Item3DLineDots::Item3DLineDots(const QVector3D &_point,
                                                 const QVector3D &_normal,
                                                 const float _length,
                                                 const float _radius,
                                                 const uint _multSpace,
                                                 const uint _quality,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DLine(_point, _normal, _length, _radius, _quality, _visible, _material, _name)
    , multSpace(_multSpace, _name + ".multSpace")
{
    props.push_back(&multSpace);
}

void Universe1::Video::Item3DLineDots::addData3D(std::list<Data3D> &_out,
                                                 const Shader *,  // _shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              point.getValue(_timeStep),
              normal.getValue(_timeStep),
              length.getValue(_timeStep),
              radius.getValue(_timeStep),
              multSpace.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineDots::buildData(std::list<Data3D> &_out,
                                                 const QVector3D &_point,
                                                 const QVector3D &_normal,
                                                 const float _length,
                                                 const float _radius,
                                                 const uint _multSpace,
                                                 const uint _quality,
                                                 const Material &_material)
{
    if (qFuzzyIsNull(_length) || _length < 0.0f || qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;
    Item3DLineDotsSegment::buildData(
        _out, _point, _point + _normal.normalized() * _length, _radius, _multSpace, _quality, _material);
}

//

Universe1::Video::Item3DLineDotsSegment::Item3DLineDotsSegment(const QVector3D &_point1,
                                                               const QVector3D &_point2,
                                                               const float _radius,
                                                               const uint _multSpace,
                                                               const uint _quality,
                                                               const bool _visible,
                                                               const Material &_material,
                                                               const std::string &_name)
    : Item3DLineSegment(_point1, _point2, _radius, _quality, _visible, _material, _name)
    , multSpace(_multSpace, _name + ".multSpace")
{
    props.push_back(&multSpace);
}

void Universe1::Video::Item3DLineDotsSegment::addData3D(std::list<Data3D> &_out,
                                                        const Shader *,  // _shader,
                                                        const uint64_t _timeStep) const
{
    buildData(_out,
              point1.getValue(_timeStep),
              point2.getValue(_timeStep),
              radius.getValue(_timeStep),
              multSpace.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineDotsSegment::buildData(std::list<Data3D> &_out,
                                                        const QVector3D &_point1,
                                                        const QVector3D &_point2,
                                                        const float _radius,
                                                        const uint _multSpace,
                                                        const uint _quality,
                                                        const Material &_material)
{
    const float len = _point1.distanceToPoint(_point2);
    if (qFuzzyIsNull(len) || qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;

    if (_multSpace == 0U)
    {
        Item3DLineSegment::buildData(_out, _point1, _point2, _radius, _quality, _material);
        return;
    }

    const QVector3D n = (_point2 - _point1).normalized();
    const float step = _radius * static_cast<float>(_multSpace);
    float t = 0.0f;
    while (t < len || qFuzzyCompare(t, len))
    {
        Item3DSphere::buildData(_out, _point1 + n * t, _radius, _quality, _material);
        t += step;
    }
}

//

Universe1::Video::DBItem3DLineDots::DBItem3DLineDots(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineDots", _footageName, _items)
{
}

Universe1::Video::Item3DLineDots *Universe1::Video::DBItem3DLineDots::add(const QVector3D &_point,
                                                                          const QVector3D &_normal,
                                                                          const float _length,
                                                                          const float _radius,
                                                                          const uint _multSpace,
                                                                          const uint _quality,
                                                                          const bool _visible,
                                                                          const Material &_material)
{
    Item3DLineDots *result =
        new Item3DLineDots(_point, _normal, _length, _radius, _multSpace, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}

Universe1::Video::Item3DLineDotsSegment *Universe1::Video::DBItem3DLineDots::addSegment(const QVector3D &_point1,
                                                                                        const QVector3D &_point2,
                                                                                        const float _radius,
                                                                                        const uint _multSpace,
                                                                                        const uint _quality,
                                                                                        const bool _visible,
                                                                                        const Material &_material)
{
    Item3DLineDotsSegment *result =
        new Item3DLineDotsSegment(_point1, _point2, _radius, _multSpace, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
