#include "item3dline.h"

Universe1::Video::Item3DLine::Item3DLine(const QVector3D &_point,
                                         const QVector3D &_normal,
                                         const float _length,
                                         const float _radius,
                                         const uint _quality,
                                         const bool _visible,
                                         const Material &_material,
                                         const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , point(_point, _name + ".point")
    , normal(_normal, _name + ".normal")
    , length(_length, _name + ".length")
    , radius(_radius, _name + ".radius")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&point);
    props.push_back(&normal);
    props.push_back(&length);
    props.push_back(&radius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DLine::addData3D(std::list<Data3D> &_out,
                                             const Shader *,  // _shader,
                                             const uint64_t _timeStep) const
{
    buildData(_out,
              point.getValue(_timeStep),
              normal.getValue(_timeStep),
              length.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLine::buildData(std::list<Data3D> &_out,
                                             const QVector3D &_point,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _length,
                                             const float _radius,
                                             const uint _quality,
                                             const Material &_material)
{
    if (qFuzzyIsNull(_length) || qFuzzyIsNull(_radius) || _length < 0.0f || _radius < 0.0f)
        return;

    const QVector3D p2 = _point + _normal * _length;
    Item3DCylinder::buildData(_out, _point, p2, _arm, _radius, _radius, _quality, _material, false);
    Item3DPlaneCircle::buildData(_out, _point, -_normal, _arm, _radius, _quality, _material);
    Item3DPlaneCircle::buildData(_out, p2, _normal, _arm, _radius, _quality, _material);
}

//

Universe1::Video::Item3DLineSegment::Item3DLineSegment(const QVector3D &_point1,
                                                       const QVector3D &_point2,
                                                       const float _radius,
                                                       const uint _quality,
                                                       const bool _visible,
                                                       const Material &_material,
                                                       const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , point1(_point1, _name + ".point1")
    , point2(_point2, _name + ".point2")
    , radius(_radius, _name + ".radius")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&point1);
    props.push_back(&point2);
    props.push_back(&radius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DLineSegment::addData3D(std::list<Data3D> &_out,
                                                    const Shader *,  // _shader,
                                                    const uint64_t _timeStep) const
{
    buildData(_out,
              point1.getValue(_timeStep),
              point2.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineSegment::buildData(std::list<Data3D> &_out,
                                                    const QVector3D &_point1,
                                                    const QVector3D &_point2,
                                                    const QVector3D &_arm,
                                                    const float _radius,
                                                    const uint _quality,
                                                    const Material &_material)
{
    if (qFuzzyIsNull(_radius) || _radius < 0.0f || qFuzzyCompare(_point1, _point2))
        return;
    const QVector3D n = (_point2 - _point1).normalized();
    Item3DCylinder::buildData(_out, _point1, _point2, _arm, _radius, _radius, _quality, _material, false);
    Item3DPlaneCircle::buildData(_out, _point1, -n, _arm, _radius, _quality, _material);
    Item3DPlaneCircle::buildData(_out, _point2, n, _arm, _radius, _quality, _material);
}

//

Universe1::Video::DBItem3DLine::DBItem3DLine(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("line", _footageName, _items)
{
}

Universe1::Video::Item3DLine *Universe1::Video::DBItem3DLine::add(const QVector3D &_point,
                                                                  const QVector3D &_normal,
                                                                  const float _length,
                                                                  const float _radius,
                                                                  const uint _quality,
                                                                  const bool _visible,
                                                                  const Material &_material)
{
    Item3DLine *result = new Item3DLine(_point, _normal, _length, _radius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}

Universe1::Video::Item3DLineSegment *Universe1::Video::DBItem3DLine::addSegment(const QVector3D &_point1,
                                                                                const QVector3D &_point2,
                                                                                const float _radius,
                                                                                const uint _quality,
                                                                                const bool _visible,
                                                                                const Material &_material)
{
    Item3DLineSegment *result =
        new Item3DLineSegment(_point1, _point2, _radius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
