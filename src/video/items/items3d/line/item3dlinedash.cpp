#include "item3dlinedash.h"

Universe1::Video::Item3DLineDash::Item3DLineDash(const QVector3D &_point,
                                                 const QVector3D &_normal,
                                                 const float _length,
                                                 const float _radius,
                                                 const uint _multDash,
                                                 const uint _multSpace,
                                                 const uint _countDot,
                                                 const uint _quality,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DLine(_point, _normal, _length, _radius, _quality, _visible, _material, _name)
    , multDash(_multDash, _name + ".multDash")
    , multSpace(_multSpace, _name + ".multSpace")
    , countDot(_countDot, _name + ".countDot")
{
    props.push_back(&multDash);
    props.push_back(&multSpace);
    props.push_back(&countDot);
}

void Universe1::Video::Item3DLineDash::addData3D(std::list<Data3D> &_out,
                                                 const Shader *,  // _shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              point.getValue(_timeStep),
              normal.getValue(_timeStep),
              length.getValue(_timeStep),
              radius.getValue(_timeStep),
              multDash.getValue(_timeStep),
              multSpace.getValue(_timeStep),
              countDot.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineDash::buildData(std::list<Data3D> &_out,
                                                 const QVector3D &_point,
                                                 const QVector3D &_normal,
                                                 const float _length,
                                                 const float _radius,
                                                 const uint _multDash,
                                                 const uint _multSpace,
                                                 const uint _countDot,
                                                 const uint _quality,
                                                 const Material &_material)
{
    if (qFuzzyIsNull(_length) || _length < 0.0f || qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;

    Item3DLineDashSegment::buildData(_out,
                                     _point,
                                     _point + _normal.normalized() * _length,
                                     _radius,
                                     _multDash,
                                     _multSpace,
                                     _countDot,
                                     _quality,
                                     _material);
}

//

Universe1::Video::Item3DLineDashSegment::Item3DLineDashSegment(const QVector3D &_point1,
                                                               const QVector3D &_point2,
                                                               const float _radius,
                                                               const uint _multDash,
                                                               const uint _multSpace,
                                                               const uint _countDot,
                                                               const uint _quality,
                                                               const bool _visible,
                                                               const Material &_material,
                                                               const std::string &_name)
    : Item3DLineSegment(_point1, _point2, _radius, _quality, _visible, _material, _name)
    , multDash(_multDash, _name + ".multDash")
    , multSpace(_multSpace, _name + ".multSpace")
    , countDot(_countDot, _name + ".countDot")
{
    props.push_back(&multDash);
    props.push_back(&multSpace);
    props.push_back(&countDot);
}

void Universe1::Video::Item3DLineDashSegment::addData3D(std::list<Data3D> &_out,
                                                        const Shader *,  // _shader,
                                                        const uint64_t _timeStep) const
{
    buildData(_out,
              point1.getValue(_timeStep),
              point2.getValue(_timeStep),
              radius.getValue(_timeStep),
              multDash.getValue(_timeStep),
              multSpace.getValue(_timeStep),
              countDot.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineDashSegment::buildData(std::list<Data3D> &_out,
                                                        const QVector3D &_point1,
                                                        const QVector3D &_point2,
                                                        const float _radius,
                                                        const uint _multDash,
                                                        const uint _multSpace,
                                                        const uint _countDot,
                                                        const uint _quality,
                                                        const Material &_material)
{
    const float len = _point1.distanceToPoint(_point2);
    if (qFuzzyIsNull(len) || qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;

    const QVector3D n = (_point2 - _point1).normalized();

    const float lenDash = _radius * static_cast<float>(std::max(1U, _multDash));
    const float lenSpace = _radius * static_cast<float>(std::max(1U, _multSpace));

    float t = 0.0f;

    while (!qFuzzyCompare(t, len) && t < len)
    {
        float nextT = t + lenDash;
        if (qFuzzyCompare(nextT, len) || nextT > len)
        {
            Item3DLineSegment::buildData(_out, _point1 + n * t, _point2, _radius, _quality, _material);
            return;
        }

        Item3DLineSegment::buildData(_out, _point1 + n * t, _point1 + n * nextT, _radius, _quality, _material);

        t = nextT + lenSpace;

        for (uint d = 0U; d < _countDot; ++d)
        {
            if (qFuzzyCompare(t, len))
            {
                Item3DSphere::buildData(_out, _point2, _radius, _quality, _material);
                return;
            }

            if (t > len)
                return;

            Item3DSphere::buildData(_out, _point1 + n * t, _radius, _quality, _material);
            t += lenSpace;
        }
    }
}

//

Universe1::Video::DBItem3DLineDash::DBItem3DLineDash(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineDash", _footageName, _items)
{
}

Universe1::Video::Item3DLineDash *Universe1::Video::DBItem3DLineDash::add(const QVector3D &_point,
                                                                          const QVector3D &_normal,
                                                                          const float _length,
                                                                          const float _radius,
                                                                          const uint _multDash,
                                                                          const uint _multSpace,
                                                                          const uint _countDot,
                                                                          const uint _quality,
                                                                          const bool _visible,
                                                                          const Material &_material)
{
    Item3DLineDash *result = new Item3DLineDash(
        _point, _normal, _length, _radius, _multDash, _multSpace, _countDot, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}

Universe1::Video::Item3DLineDashSegment *Universe1::Video::DBItem3DLineDash::addSegment(const QVector3D &_point1,
                                                                                        const QVector3D &_point2,
                                                                                        const float _radius,
                                                                                        const uint _multDash,
                                                                                        const uint _multSpace,
                                                                                        const uint _countDot,
                                                                                        const uint _quality,
                                                                                        const bool _visible,
                                                                                        const Material &_material)
{
    Item3DLineDashSegment *result = new Item3DLineDashSegment(
        _point1, _point2, _radius, _multDash, _multSpace, _countDot, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
