#include "item3dtorusarc.h"

Universe1::Video::Item3DTorusArc::Item3DTorusArc(const bool _inner,
                                                 const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_arm,
                                                 const float _angleDeg,
                                                 const float _radiusRing,
                                                 const float _radiusLine,
                                                 const uint _qualityRing,
                                                 const uint _qualityLine,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DTorus(
          _inner, _center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _visible, _material, _name)
    , arm(_arm, _name + ".arm")
    , angleDeg(_angleDeg, _name + ".angleDeg")
{
    props.push_back(&arm);
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DTorusArc::addData3D(std::list<Data3D> &_out,
                                                 const Shader *,  // _shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              radiusRing.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityRing.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DTorusArc::buildData(std::list<Data3D> &_out,
                                                 const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_arm,
                                                 const float _angleDeg,
                                                 const float _radiusRing,
                                                 const float _radiusLine,
                                                 const uint _qualityRing,
                                                 const uint _qualityLine,
                                                 const Material &_material,
                                                 const bool _inner)
{
    if (qFuzzyIsNull(_angleDeg) || _angleDeg < 0.0f)
        return;

    if (qFuzzyCompare(_angleDeg, 360.0f) || _angleDeg > 360.0f)
    {
        Item3DTorus::buildData(
            _out, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _material, _inner);
        return;
    }

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepRing = 360.0 / static_cast<float>(cntRing);
    uint steps = static_cast<uint>(_angleDeg / stepRing);
    const float angleSteps = static_cast<float>(steps) * stepRing;
    if (!qFuzzyCompare(angleSteps, _angleDeg))
        steps++;

    uint idx = 0U;
    _out.push_back({_material, cntLine * (steps + 1U), cntLine * steps * 6UL});
    addTorusArc(_out.back(),
                idx,
                _center,
                _normal,
                _arm,
                _angleDeg,
                _radiusRing,
                _radiusLine,
                _qualityRing,
                _qualityLine,
                _inner);
}

void Universe1::Video::Item3DTorusArc::addTorusArc(Data3D &_data,
                                                   uint &_idx,
                                                   const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
                                                   const float _angleDeg,
                                                   const float _radiusRing,
                                                   const float _radiusLine,
                                                   const uint _qualityRing,
                                                   const uint _qualityLine,
                                                   const bool _inner)
{
    if (qFuzzyIsNull(_angleDeg) || _angleDeg < 0.0f)
        return;

    if (qFuzzyCompare(_angleDeg, 360.0f) || _angleDeg > 360.0f)
    {
        Item3DTorus::addTorus(
            _data, _idx, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _inner);
        return;
    }

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepRing = 360.0 / static_cast<float>(cntRing);
    uint steps = static_cast<uint>(_angleDeg / stepRing);
    const float angleSteps = static_cast<float>(steps) * stepRing;
    const bool addRest = !qFuzzyCompare(angleSteps, _angleDeg);

    const QVector3D n = _normal.normalized();
    const QVector3D a = _arm.normalized();
    const QQuaternion rotRing = QQuaternion::fromAxisAndAngle(n, stepRing);
    QVector3D ar = a;
    for (uint r = 0U; r <= steps; ++r)
    {
        const QVector3D nLine = QVector3D::crossProduct(n, ar).normalized();
        const QQuaternion rotLine = QQuaternion::fromAxisAndAngle(nLine, 360.0 / static_cast<float>(cntLine));
        const QVector3D cr = _center + ar * _radiusRing;
        QVector3D al = ar;
        for (uint l = 0U; l < cntLine; ++l)
        {
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
            al = rotLine.rotatedVector(al).normalized();
        }
        ar = rotRing.rotatedVector(ar).normalized();
    }

    if (addRest)
    {
        ar = QQuaternion::fromAxisAndAngle(n, _angleDeg).rotatedVector(a).normalized();
        const QVector3D nLine = QVector3D::crossProduct(n, ar).normalized();
        const QQuaternion rotLine = QQuaternion::fromAxisAndAngle(nLine, 360.0 / static_cast<float>(cntLine));
        const QVector3D cr = _center + ar * _radiusRing;
        QVector3D al = ar;
        for (uint l = 0U; l < cntLine; ++l)
        {
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
            al = rotLine.rotatedVector(al).normalized();
        }
        ++steps;
    }

    if (_inner)
    {
        for (uint r = 0U; r < steps; ++r)
        {
            for (uint l = 0U; l < cntLine - 1U; ++l)
            {
                _data.indexes.push_back(_idx + r * cntLine + l);
                _data.indexes.push_back(_idx + r * cntLine + l + 1U);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine + l + 1U);

                _data.indexes.push_back(_idx + r * cntLine + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine + l + 1U);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine + l);
            }

            _data.indexes.push_back(_idx + (r + 1U) * cntLine - 1U);
            _data.indexes.push_back(_idx + r * cntLine);
            _data.indexes.push_back(_idx + (r + 1U) * cntLine);

            _data.indexes.push_back(_idx + (r + 1U) * cntLine - 1U);
            _data.indexes.push_back(_idx + (r + 1U) * cntLine);
            _data.indexes.push_back(_idx + (r + 2U) * cntLine - 1U);
        }
    }
    else
    {
        for (uint r = 0U; r < steps; ++r)
        {
            for (uint l = 0U; l < cntLine - 1U; ++l)
            {
                _data.indexes.push_back(_idx + r * cntLine + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine + l + 1U);
                _data.indexes.push_back(_idx + r * cntLine + l + 1U);

                _data.indexes.push_back(_idx + r * cntLine + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine + l + 1U);
            }

            _data.indexes.push_back(_idx + (r + 1U) * cntLine - 1U);
            _data.indexes.push_back(_idx + (r + 1U) * cntLine);
            _data.indexes.push_back(_idx + r * cntLine);

            _data.indexes.push_back(_idx + (r + 1U) * cntLine - 1U);
            _data.indexes.push_back(_idx + (r + 2U) * cntLine - 1U);
            _data.indexes.push_back(_idx + (r + 1U) * cntLine);
        }
    }

    _idx += cntLine * (steps + 1U);
}

Universe1::Video::DBItem3DTorusArc::DBItem3DTorusArc(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("torusArc", _footageName, _items)
{
}

Universe1::Video::Item3DTorusArc *Universe1::Video::DBItem3DTorusArc::add(const bool _inner,
                                                                          const QVector3D &_center,
                                                                          const QVector3D &_normal,
                                                                          const QVector3D &_arm,
                                                                          const float _angleDeg,
                                                                          const float _radiusRing,
                                                                          const float _radiusLine,
                                                                          const uint _qualityRing,
                                                                          const uint _qualityLine,
                                                                          const bool _visible,
                                                                          const Material &_material)
{
    Item3DTorusArc *result = new Item3DTorusArc(_inner,
                                                _center,
                                                _normal,
                                                _arm,
                                                _angleDeg,
                                                _radiusRing,
                                                _radiusLine,
                                                _qualityRing,
                                                _qualityLine,
                                                _visible,
                                                _material,
                                                nextName());
    items->push_back(result);
    return result;
}
