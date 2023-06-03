#include "item3dlinearc.h"

Universe1::Video::Item3DLineArc::Item3DLineArc(const QVector3D &_center,
                                               const QVector3D &_normal,
                                               const QVector3D &_arm,
                                               const float _angleDeg,
                                               const float _radiusCircle,
                                               const float _radiusLine,
                                               const uint _qualityCircle,
                                               const uint _qualityLine,
                                               const bool _visible,
                                               const Material &_material,
                                               const std::string &_name)
    : Item3DLineCircle(
          _center, _normal, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, _visible, _material, _name)
    , arm(_arm, _name + ".arm")
    , angleDeg(_angleDeg, _name + ".angleDeg")
{
    props.push_back(&arm);
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DLineArc::addData3D(std::list<Data3D> &_out,
                                                const Shader *,  // _shader,
                                                const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              radiusCircle.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityCircle.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineArc::buildData(std::list<Data3D> &_out,
                                                const QVector3D &_center,
                                                const QVector3D &_normal,
                                                const QVector3D &_arm,
                                                const float _angleDeg,
                                                const float _radiusCircle,
                                                const float _radiusLine,
                                                const uint _qualityCircle,
                                                const uint _qualityLine,
                                                const Material &_material)
{
    if (qFuzzyIsNull(_angleDeg) || qFuzzyIsNull(_radiusCircle) || qFuzzyIsNull(_radiusLine) || _angleDeg < 0.0f ||
        _radiusCircle < 0.0f || _radiusLine < 0.0f)
        return;

    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);
    const QVector3D a2 = QQuaternion::fromAxisAndAngle(n, _angleDeg).rotatedVector(a).normalized();

    Item3DTorusArc::buildData(
        _out, _center, n, a, _angleDeg, _radiusCircle, _radiusLine, _qualityCircle, _qualityLine, _material);

    Item3DPlaneCircle::buildData(_out,
                                 _center + a * _radiusCircle,
                                 QVector3D::crossProduct(a, n).normalized(),
                                 _radiusLine,
                                 _qualityLine,
                                 _material);

    Item3DPlaneCircle::buildData(_out,
                                 _center + a2 * _radiusCircle,
                                 QVector3D::crossProduct(n, a2).normalized(),
                                 _radiusLine,
                                 _qualityLine,
                                 _material);
}

//

Universe1::Video::DBItem3DLineArc::DBItem3DLineArc(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineArc", _footageName, _items)
{
}

Universe1::Video::Item3DLineArc *Universe1::Video::DBItem3DLineArc::add(const QVector3D &_center,
                                                                        const QVector3D &_normal,
                                                                        const QVector3D &_arm,
                                                                        const float _angleDeg,
                                                                        const float _radiusCircle,
                                                                        const float _radiusLine,
                                                                        const uint _qualityCircle,
                                                                        const uint _qualityLine,
                                                                        const bool _visible,
                                                                        const Material &_material)
{
    Item3DLineArc *result = new Item3DLineArc(_center,
                                              _normal,
                                              _arm,
                                              _angleDeg,
                                              _radiusCircle,
                                              _radiusLine,
                                              _qualityCircle,
                                              _qualityLine,
                                              _visible,
                                              _material,
                                              nextName());
    items->push_back(result);
    return result;
}
