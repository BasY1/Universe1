#include "item3dhand.h"

const Universe1::Video::Material Universe1::Video::Item3DHand::defMat(QColor(255, 168, 198), 64, 1);
const float Universe1::Video::Item3DHand::defSize(0.4f);
const float Universe1::Video::Item3DHand::defLine(0.04f);

Universe1::Video::Item3DHand::Item3DHand(const bool _rightHand,
                                         const QVector3D &_center,
                                         const QVector3D &_normal,
                                         const QVector3D &_arm,
                                         const float _distance,
                                         const float _handSize,
                                         const float _lineRadius,
                                         const uint _qualityHand,
                                         const uint _qualityLine,
                                         const bool _visible,
                                         const Material &_material,
                                         const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , rightHand(_rightHand)
    , center(_center, name + ".center")
    , normal(_normal, name + ".normal")
    , arm(_arm, name + ".arm")
    , distance(_distance, name + ".distance")
    , handSize(_handSize, name + ".handSize")
    , lineRadius(_lineRadius, name + ".lineRadius")
    , qualityHand(_qualityHand, name + ".qualityHand")
    , qualityLine(_qualityLine, name + ".qualityLine")
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&distance);
    props.push_back(&handSize);
    props.push_back(&lineRadius);
    props.push_back(&qualityHand);
    props.push_back(&qualityLine);
}

void Universe1::Video::Item3DHand::addData3D(std::list<Data3D> &_out,
                                             const Shader *,  // _shader,
                                             const uint64_t _timeStep) const
{
    buildData(_out,
              rightHand,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              distance.getValue(_timeStep),
              handSize.getValue(_timeStep),
              lineRadius.getValue(_timeStep),
              qualityHand.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DHand::buildData(std::list<Data3D> &_out,
                                             const bool _rightHand,
                                             const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _distance,
                                             const float _handSize,
                                             const float _lineRadius,
                                             const uint _qualityHand,
                                             const uint _qualityLine,
                                             const Material &_material)
{
    if (qFuzzyIsNull(_distance) || _distance < 0.0f || qFuzzyIsNull(_handSize) || _handSize < 0.0f ||
        qFuzzyIsNull(_lineRadius) || _lineRadius < 0.0f)
        return;

    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);

    const float handAngleRad = _handSize / _distance;
    const float handAngleDeg = Math::toDeg<float>((_rightHand ? 1.0f : -1.0f) * handAngleRad);
    const std::array<float, 4> fingersAngleDeg = {
        0.9f * handAngleDeg, handAngleDeg, 0.9f * handAngleDeg, 0.7f * handAngleDeg};
    const std::array<float, 4> fingersUp = {_handSize * 0.7f, _handSize * 0.5f, _handSize * 0.3f, _handSize * 0.1f};

    if (_rightHand)
        Item3DTorusArc::buildData(
            _out, _center, n, a, handAngleDeg, _distance, _lineRadius, _qualityHand, _qualityLine, _material);
    else
        Item3DTorusArc::buildData(
            _out, _center, -n, a, -handAngleDeg, _distance, _lineRadius, _qualityHand, _qualityLine, _material);

    if (_rightHand)
        Item3DTorusArc::buildData(_out,
                                  _center + n * _handSize * 0.8F,
                                  n,
                                  a,
                                  handAngleDeg,
                                  _distance,
                                  _lineRadius,
                                  _qualityHand,
                                  _qualityLine,
                                  _material);
    else
        Item3DTorusArc::buildData(_out,
                                  _center + n * _handSize * 0.8F,
                                  -n,
                                  a,
                                  -handAngleDeg,
                                  _distance,
                                  _lineRadius,
                                  _qualityHand,
                                  _qualityLine,
                                  _material);

    Item3DCylinder::buildData(_out,
                              _center + a * _distance,
                              _center + a * _distance + n * _handSize * 0.8F,
                              _lineRadius,
                              _lineRadius,
                              _qualityLine,
                              _material);

    Item3DCylinder::buildData(_out,
                              _center + a * _distance + n * _handSize * 0.9f,
                              _center + a * _distance + n * _handSize * 1.5f,
                              _lineRadius,
                              _lineRadius,
                              _qualityLine,
                              _material);

    Item3DPlaneCircle::buildData(
        _out, _center + a * _distance + n * _handSize * 1.5f, n, _lineRadius, _qualityLine, _material);

    const QVector3D aa = QQuaternion::fromAxisAndAngle(n, handAngleDeg).rotatedVector(a).normalized();
    for (uint8_t i = 0U; i < 4U; ++i)
    {
        if (_rightHand)
            Item3DTorusArc::buildData(_out,
                                      _center + n * fingersUp[i],
                                      n,
                                      aa,
                                      fingersAngleDeg[i],
                                      _distance,
                                      _lineRadius,
                                      _qualityHand,
                                      _qualityLine,
                                      _material);
        else
            Item3DTorusArc::buildData(_out,
                                      _center + n * fingersUp[i],
                                      -n,
                                      aa,
                                      -fingersAngleDeg[i],
                                      _distance,
                                      _lineRadius,
                                      _qualityHand,
                                      _qualityLine,
                                      _material);

        const QVector3D aaa = _rightHand
            ? QQuaternion::fromAxisAndAngle(n, fingersAngleDeg[i]).rotatedVector(aa).normalized()
            : QQuaternion::fromAxisAndAngle(-n, -fingersAngleDeg[i]).rotatedVector(aa).normalized();
        if (_rightHand)
            Item3DPlaneCircle::buildData(_out,
                                         _center + n * fingersUp[i] + aaa * _distance,
                                         QVector3D::crossProduct(n, aaa).normalized(),
                                         _lineRadius,
                                         _qualityLine,
                                         _material);
        else
            Item3DPlaneCircle::buildData(_out,
                                         _center + n * fingersUp[i] + aaa * _distance,
                                         QVector3D::crossProduct(-n, aaa).normalized(),
                                         _lineRadius,
                                         _qualityLine,
                                         _material);
    }
}

Universe1::Video::DBItem3DHand::DBItem3DHand(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("hand", _footageName, _items)
{
}

Universe1::Video::Item3DHand *Universe1::Video::DBItem3DHand::add(const bool _rightHand,
                                                                  const QVector3D &_center,
                                                                  const QVector3D &_normal,
                                                                  const QVector3D &_arm,
                                                                  const float _distance,
                                                                  const float _handSize,
                                                                  const float _lineRadius,
                                                                  const uint _qualityHand,
                                                                  const uint _qualityLine,
                                                                  const bool _visible,
                                                                  const Material &_material)
{
    Item3DHand *result = new Item3DHand(_rightHand,
                                        _center,
                                        _normal,
                                        _arm,
                                        _distance,
                                        _handSize,
                                        _lineRadius,
                                        _qualityHand,
                                        _qualityLine,
                                        _visible,
                                        _material,
                                        nextName());
    items->push_back(result);
    return result;
}
