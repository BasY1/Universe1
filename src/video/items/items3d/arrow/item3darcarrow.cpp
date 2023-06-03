#include "item3darcarrow.h"

Universe1::Video::Item3DArcArrow::Item3DArcArrow(const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_arm,
                                                 const float _armRadius,
                                                 const float _arrowLength,
                                                 const float _arrowRadius,
                                                 const uint _quality,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")
    , armRadius(_armRadius, _name + ".armRadius")
    , arrowLength(_arrowLength, _name + ".arrowLength")
    , arrowRadius(_arrowRadius, _name + ".arrowRadius")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&armRadius);
    props.push_back(&arrowLength);
    props.push_back(&arrowRadius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DArcArrow::addData3D(std::list<Data3D> &_out,
                                                 const Shader *,  // _shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              armRadius.getValue(_timeStep),
              arrowLength.getValue(_timeStep),
              arrowRadius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DArcArrow::buildData(std::list<Data3D> &_out,
                                                 const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_arm,
                                                 const float _armRadius,
                                                 const float _arrowLength,
                                                 const float _arrowRadius,
                                                 const uint _quality,
                                                 const Material &_material,
                                                 const Material &_materialCircle)
{
    if (qFuzzyIsNull(_armRadius) || qFuzzyIsNull(_arrowRadius) || qFuzzyIsNull(_arrowRadius) || _armRadius < 0.0f ||
        _arrowLength < 0.0f || _arrowRadius < 0.0f)
        return;

    const uint cntCircle = circlePointCount(_quality);
    const uint cntPoint = cntCircle * (_quality + 2U);
    const uint cntIndex = cntCircle * 3U + cntCircle * _quality * 6U;

    static const float maxArrowAngle = 30.0f;
    const float angleExpected = Math::toDeg<float>(_arrowLength / _armRadius);
    float aa = angleExpected;
    float ar = _arrowRadius;
    float al = _arrowLength;
    if (angleExpected > maxArrowAngle)
    {
        aa = maxArrowAngle;
        ar = _arrowRadius * maxArrowAngle / angleExpected;
        al = _arrowLength * maxArrowAngle / angleExpected;
    }
    const float angleCone = Math::toDeg<float>(std::atan2(ar, al));
    const float stepRadius = ar / static_cast<float>(_quality + 1U);
    const float stepAngle = aa / static_cast<float>(_quality + 1U);
    const float stepRot = 360.0f / static_cast<float>(cntCircle);

    const QVector3D n = _normal.normalized();
    const QVector3D d = QVector3D::crossProduct(n, _arm).normalized();
    const QVector3D a = QVector3D::crossProduct(d, n).normalized();

    Item3DPlaneCircle::buildData(_out, _center + a * _armRadius, -d, ar, _quality, _materialCircle);

    _out.push_back({_material, cntPoint, cntIndex});
    Data3D &data = _out.back();

    float angleAdd = 0.0f;
    float curRadius = ar;
    for (uint i = 0U; i <= _quality; ++i)
    {
        const QVector3D caa = QQuaternion::fromAxisAndAngle(n, angleAdd).rotatedVector(a).normalized();
        const QVector3D cnn = QVector3D::crossProduct(n, caa).normalized();
        const QVector3D pp = _center + caa * _armRadius;
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(cnn, stepRot);
        QVector3D aaa = caa;
        QVector3D ann = QQuaternion::fromAxisAndAngle(n, angleAdd + angleCone).rotatedVector(a).normalized();
        for (uint j = 0U; j < cntCircle; ++j)
        {
            data.points.push_back(pp + aaa * curRadius);
            data.normals.push_back(ann);
            aaa = rot.rotatedVector(aaa).normalized();
            ann = rot.rotatedVector(ann).normalized();
        }

        angleAdd += stepAngle;
        curRadius -= stepRadius;
    }

    {
        const QVector3D caa = QQuaternion::fromAxisAndAngle(n, aa).rotatedVector(a).normalized();
        const QVector3D cnn = QVector3D::crossProduct(n, caa).normalized();
        const QVector3D pp = _center + caa * _armRadius;
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(cnn, stepRot);

        QVector3D aaa = caa;
        QVector3D ann = QQuaternion::fromAxisAndAngle(n, aa + angleCone).rotatedVector(a).normalized();
        ann = QQuaternion::fromAxisAndAngle(cnn, stepRot * 0.5f).rotatedVector(ann).normalized();

        for (uint j = 0U; j < cntCircle; ++j)
        {
            data.points.push_back(pp);
            data.normals.push_back(ann);
            aaa = rot.rotatedVector(aaa).normalized();
            ann = rot.rotatedVector(ann).normalized();
        }
    }

    uint idx = 0U;
    for (uint q = 0U; q < _quality; ++q)
    {
        for (uint i = 0U; i < cntCircle - 1U; ++i)
        {
            data.indexes.push_back(idx + i);
            data.indexes.push_back(idx + cntCircle + i + 1U);
            data.indexes.push_back(idx + i + 1U);

            data.indexes.push_back(idx + i);
            data.indexes.push_back(idx + cntCircle + i);
            data.indexes.push_back(idx + cntCircle + i + 1U);
        }

        data.indexes.push_back(idx + cntCircle - 1U);
        data.indexes.push_back(idx + 2U * cntCircle - 1U);
        data.indexes.push_back(idx);

        data.indexes.push_back(idx);
        data.indexes.push_back(idx + 2U * cntCircle - 1U);
        data.indexes.push_back(idx + cntCircle);

        idx += cntCircle;
    }

    for (uint i = 0U; i < cntCircle - 1U; ++i)
    {
        data.indexes.push_back(idx + i);
        data.indexes.push_back(idx + cntCircle + i);
        data.indexes.push_back(idx + i + 1U);
    }

    data.indexes.push_back(idx + cntCircle - 1U);
    data.indexes.push_back(idx + 2U * cntCircle - 1U);
    data.indexes.push_back(idx);
}

//

Universe1::Video::Item3DArcArrows::Item3DArcArrows(const uint _arrowCount,
                                                   const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
                                                   const float _armRadius,
                                                   const float _arrowLength,
                                                   const float _arrowRadius,
                                                   const uint _quality,
                                                   const bool _visible,
                                                   const Material &_material,
                                                   const std::string &_name)
    : Item3DArcArrow(
          _center, _normal, _arm, _armRadius, _arrowLength, _arrowRadius, _quality, _visible, _material, _name)
    , arrowCount(_arrowCount, _name + ".arrowCount")
{
    props.push_back(&arrowCount);
}

void Universe1::Video::Item3DArcArrows::addData3D(std::list<Data3D> &_out,
                                                  const Shader *,  // _shader,
                                                  const uint64_t _timeStep) const
{
    buildData(_out,
              arrowCount.getValue(_timeStep),
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              armRadius.getValue(_timeStep),
              arrowLength.getValue(_timeStep),
              arrowRadius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DArcArrows::buildData(std::list<Data3D> &_out,
                                                  const uint _arrowCount,
                                                  const QVector3D &_center,
                                                  const QVector3D &_normal,
                                                  const QVector3D &_arm,
                                                  const float _armRadius,
                                                  const float _arrowLength,
                                                  const float _arrowRadius,
                                                  const uint _quality,
                                                  const Material &_material,
                                                  const Material &_materialCircle)
{
    if (_arrowCount == 0U)
        return;
    const QVector3D n = _normal.normalized();
    const QQuaternion rot = QQuaternion::fromAxisAndAngle(n, 360.0f / static_cast<float>(_arrowCount));
    QVector3D aa = QVector3D::crossProduct(QVector3D::crossProduct(n, _arm).normalized(), n).normalized();
    for (uint i = 0U; i < _arrowCount; ++i, aa = rot.rotatedVector(aa).normalized())
        Item3DArcArrow::buildData(
            _out, _center, _normal, aa, _armRadius, _arrowLength, _arrowRadius, _quality, _material, _materialCircle);
}

//

Universe1::Video::DBItem3DArcArrow::DBItem3DArcArrow(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("arcArrow", _footageName, _items)
{
}

Universe1::Video::Item3DArcArrow *Universe1::Video::DBItem3DArcArrow::add(const QVector3D &_center,
                                                                          const QVector3D &_normal,
                                                                          const QVector3D &_arm,
                                                                          const float _armRadius,
                                                                          const float _arrowLength,
                                                                          const float _arrowRadius,
                                                                          const uint _quality,
                                                                          const bool _visible,
                                                                          const Material &_material)
{
    Item3DArcArrow *result = new Item3DArcArrow(
        _center, _normal, _arm, _armRadius, _arrowLength, _arrowRadius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}

Universe1::Video::Item3DArcArrows *Universe1::Video::DBItem3DArcArrow::addArrows(const uint _arrowCount,
                                                                                 const QVector3D &_center,
                                                                                 const QVector3D &_normal,
                                                                                 const QVector3D &_arm,
                                                                                 const float _armRadius,
                                                                                 const float _arrowLength,
                                                                                 const float _arrowRadius,
                                                                                 const uint _quality,
                                                                                 const bool _visible,
                                                                                 const Material &_material)
{
    Item3DArcArrows *result = new Item3DArcArrows(_arrowCount,
                                                  _center,
                                                  _normal,
                                                  _arm,
                                                  _armRadius,
                                                  _arrowLength,
                                                  _arrowRadius,
                                                  _quality,
                                                  _visible,
                                                  _material,
                                                  nextName());
    items->push_back(result);
    return result;
}
