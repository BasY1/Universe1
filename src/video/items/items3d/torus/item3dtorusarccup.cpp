#include "item3dtorusarccup.h"

Universe1::Video::Item3DTorusArcCup::Item3DTorusArcCup(const bool _insideCup,
                                                       const bool _inner,
                                                       const QVector3D &_center,
                                                       const QVector3D &_normal,
                                                       const QVector3D &_arm,
                                                       const float _angleArcDeg,
                                                       const float _angleCupDeg,
                                                       const float _radiusRing,
                                                       const float _radiusLine,
                                                       const uint _qualityRing,
                                                       const uint _qualityLine,
                                                       const bool _visible,
                                                       const Material &_material,
                                                       const std::string &_name)
    : Item3DTorusCup(_insideCup,
                     _inner,
                     _center,
                     _normal,
                     _angleCupDeg,
                     _radiusRing,
                     _radiusLine,
                     _qualityRing,
                     _qualityLine,
                     _visible,
                     _material,
                     _name)
    , arm(_arm, _name + ".arm")
    , angleArcDeg(_angleArcDeg, _name + ".angleArcDeg")
{
    props.push_back(&angleCupDeg);
}

void Universe1::Video::Item3DTorusArcCup::addData3D(std::list<Data3D> &_out,
                                                    const Shader *,  // _shader,
                                                    const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleArcDeg.getValue(_timeStep),
              angleCupDeg.getValue(_timeStep),
              radiusRing.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityRing.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep),
              insideCup,
              inner);
}

void Universe1::Video::Item3DTorusArcCup::buildData(std::list<Data3D> &_out,
                                                    const QVector3D &_center,
                                                    const QVector3D &_normal,
                                                    const QVector3D &_arm,
                                                    const float _angleArcDeg,
                                                    const float _angleCupDeg,
                                                    const float _radiusRing,
                                                    const float _radiusLine,
                                                    const uint _qualityRing,
                                                    const uint _qualityLine,
                                                    const Material &_material,
                                                    const bool _insideCup,
                                                    const bool _inner)
{
    if (qFuzzyIsNull(_angleCupDeg) || _angleCupDeg < 0.0f || qFuzzyIsNull(_angleArcDeg) || _angleArcDeg < 0.0f)
        return;

    const bool notArc = qFuzzyCompare(_angleArcDeg, 360.0f) || _angleArcDeg > 360.0f;
    const bool notCup = qFuzzyCompare(_angleCupDeg, 180.0f) || _angleCupDeg > 180.0f;

    if (notArc && notCup)
    {
        Item3DTorus::buildData(
            _out, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _material, _inner);
        return;
    }

    if (notArc)
    {
        Item3DTorusCup::buildData(_out,
                                  _center,
                                  _normal,
                                  _arm,
                                  _angleCupDeg,
                                  _radiusRing,
                                  _radiusLine,
                                  _qualityRing,
                                  _qualityLine,
                                  _material,
                                  _inner);
        return;
    }

    if (notCup)
    {
        Item3DTorusArc::buildData(_out,
                                  _center,
                                  _normal,
                                  _arm,
                                  _angleArcDeg,
                                  _radiusRing,
                                  _radiusLine,
                                  _qualityRing,
                                  _qualityLine,
                                  _material,
                                  _inner);
        return;
    }

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepRing = 360.0 / static_cast<float>(cntRing);
    const float stepLine = 360.0 / static_cast<float>(cntLine);
    uint stepsRing = static_cast<uint>(_angleArcDeg / stepRing);
    uint stepsLine = static_cast<uint>(_angleCupDeg / stepLine);
    const float angleStepsRing = static_cast<float>(stepsRing) * stepRing;
    const float angleStepsLine = static_cast<float>(stepsLine) * stepLine;
    if (!qFuzzyCompare(angleStepsRing, _angleArcDeg))
        stepsRing++;
    if (!qFuzzyCompare(angleStepsLine, _angleCupDeg))
        stepsLine++;

    const uint cntLine2 = 1U + stepsLine * 2U;

    uint idx = 0U;
    _out.push_back({_material, stepsRing * cntLine2, (stepsRing - 1U) * (cntLine2 - 1U) * 6U});
    addTorusArcCup(_out.back(),
                   idx,
                   _center,
                   _normal,
                   _arm,
                   _angleArcDeg,
                   _angleCupDeg,
                   _radiusRing,
                   _radiusLine,
                   _qualityRing,
                   _qualityLine,
                   _insideCup,
                   _inner);
}

void Universe1::Video::Item3DTorusArcCup::addTorusArcCup(Data3D &_data,
                                                         uint &_idx,
                                                         const QVector3D &_center,
                                                         const QVector3D &_normal,
                                                         const QVector3D &_arm,
                                                         const float _angleArcDeg,
                                                         const float _angleCupDeg,
                                                         const float _radiusRing,
                                                         const float _radiusLine,
                                                         const uint _qualityRing,
                                                         const uint _qualityLine,
                                                         const bool _insideCup,
                                                         const bool _inner)
{
    if (qFuzzyIsNull(_angleCupDeg) || _angleCupDeg < 0.0f || qFuzzyIsNull(_angleArcDeg) || _angleArcDeg < 0.0f)
        return;

    const bool notArc = qFuzzyCompare(_angleArcDeg, 360.0f) || _angleArcDeg > 360.0f;
    const bool notCup = qFuzzyCompare(_angleCupDeg, 180.0f) || _angleCupDeg > 180.0f;

    if (notArc && notCup)
    {
        Item3DTorus::addTorus(
            _data, _idx, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _inner);
        return;
    }

    if (notArc)
    {
        Item3DTorusCup::addTorusCup(_data,
                                    _idx,
                                    _center,
                                    _normal,
                                    _arm,
                                    _angleCupDeg,
                                    _radiusRing,
                                    _radiusLine,
                                    _qualityRing,
                                    _qualityLine,
                                    _inner);
        return;
    }

    if (notCup)
    {
        Item3DTorusArc::addTorusArc(_data,
                                    _idx,
                                    _center,
                                    _normal,
                                    _arm,
                                    _angleArcDeg,
                                    _radiusRing,
                                    _radiusLine,
                                    _qualityRing,
                                    _qualityLine,
                                    _inner);
        return;
    }

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepRing = 360.0 / static_cast<float>(cntRing);
    const float stepLine = 360.0 / static_cast<float>(cntLine);
    uint stepsRing1 = static_cast<uint>(_angleArcDeg / stepRing);
    uint stepsLine1 = static_cast<uint>(_angleCupDeg / stepLine);
    const float angleStepsRing = static_cast<float>(stepsRing1) * stepRing;
    const float angleStepsLine = static_cast<float>(stepsLine1) * stepLine;
    const bool addRestRing = !qFuzzyCompare(angleStepsRing, _angleArcDeg);
    const bool addRestLine = !qFuzzyCompare(angleStepsLine, _angleCupDeg);

    const uint stepsLine2 = stepsLine1 * 2U + 1U;
    const uint cntLine2 = 1U + (addRestLine ? ((stepsLine1 + 1U) * 2U) : (stepsLine1 * 2U));
    const uint cntRing2 = stepsRing1 + (addRestRing ? 1U : 0U);

    const QVector3D n = _normal.normalized();
    const QVector3D a = _arm.normalized();
    const QQuaternion rotRing = QQuaternion::fromAxisAndAngle(n, stepRing);
    QVector3D ar = a;
    for (uint r = 0U; r < stepsRing1; ++r)
    {
        const QVector3D nLine = QVector3D::crossProduct(n, ar).normalized();
        const QVector3D cr = _center + ar * _radiusRing;
        const QVector3D a0 = _insideCup ? -ar : ar;

        if (addRestLine)
        {
            const QVector3D al = QQuaternion::fromAxisAndAngle(nLine, -_angleCupDeg).rotatedVector(a0).normalized();
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
        }

        const QQuaternion rotLine = QQuaternion::fromAxisAndAngle(nLine, stepLine);
        QVector3D a1 = QQuaternion::fromAxisAndAngle(nLine, -angleStepsLine).rotatedVector(a0).normalized();
        for (uint i = 0U; i < stepsLine2; ++i)
        {
            _data.points.push_back(cr + a1 * _radiusLine);
            if (_inner)
                _data.normals.push_back(-a1);
            else
                _data.normals.push_back(a1);

            a1 = rotLine.rotatedVector(a1).normalized();
        }

        if (addRestLine)
        {
            const QVector3D al = QQuaternion::fromAxisAndAngle(nLine, _angleCupDeg).rotatedVector(a0).normalized();
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
        }

        ar = rotRing.rotatedVector(ar).normalized();
    }

    if (addRestRing)
    {
        ar = QQuaternion::fromAxisAndAngle(n, _angleArcDeg).rotatedVector(a).normalized();
        const QVector3D nLine = QVector3D::crossProduct(n, ar).normalized();
        const QVector3D cr = _center + ar * _radiusRing;
        const QVector3D a0 = _insideCup ? -ar : ar;

        if (addRestLine)
        {
            const QVector3D al = QQuaternion::fromAxisAndAngle(nLine, -_angleCupDeg).rotatedVector(a0).normalized();
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
        }

        const QQuaternion rotLine = QQuaternion::fromAxisAndAngle(nLine, stepLine);
        QVector3D a1 = QQuaternion::fromAxisAndAngle(nLine, -angleStepsLine).rotatedVector(a0).normalized();
        for (uint i = 0U; i < stepsLine2; ++i)
        {
            _data.points.push_back(cr + a1 * _radiusLine);
            if (_inner)
                _data.normals.push_back(-a1);
            else
                _data.normals.push_back(a1);

            a1 = rotLine.rotatedVector(a1).normalized();
        }

        if (addRestLine)
        {
            const QVector3D al = QQuaternion::fromAxisAndAngle(nLine, _angleCupDeg).rotatedVector(a0).normalized();
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
        }
    }

    if (_inner)
    {
        for (uint la = 0U; la < cntRing2 - 1U; ++la)
        {
            const uint laa = _idx + la * cntLine2;
            for (uint lo = 0U; lo < cntLine2 - 1U; ++lo)
            {
                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + lo + 1U);
                _data.indexes.push_back(laa + cntLine2 + lo + 1U);

                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + cntLine2 + lo + 1U);
                _data.indexes.push_back(laa + cntLine2 + lo);
            }
        }
    }
    else
    {
        for (uint la = 0U; la < cntRing2 - 1U; ++la)
        {
            const uint laa = _idx + la * cntLine2;
            for (uint lo = 0U; lo < cntLine2 - 1U; ++lo)
            {
                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + cntLine2 + lo + 1U);
                _data.indexes.push_back(laa + lo + 1U);

                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + cntLine2 + lo);
                _data.indexes.push_back(laa + cntLine2 + lo + 1U);
            }
        }
    }

    _idx += cntLine2 * cntRing2;
}

Universe1::Video::DBItem3DTorusArcCup::DBItem3DTorusArcCup(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("torusArcCup", _footageName, _items)
{
}

Universe1::Video::Item3DTorusArcCup *Universe1::Video::DBItem3DTorusArcCup::add(const bool _inside,
                                                                                const bool _inner,
                                                                                const QVector3D &_center,
                                                                                const QVector3D &_normal,
                                                                                const QVector3D &_arm,
                                                                                const float _angleArcDeg,
                                                                                const float _angleCupDeg,
                                                                                const float _radiusRing,
                                                                                const float _radiusLine,
                                                                                const uint _qualityRing,
                                                                                const uint _qualityLine,
                                                                                const bool _visible,
                                                                                const Material &_material)
{
    Item3DTorusArcCup *result = new Item3DTorusArcCup(_inside,
                                                      _inner,
                                                      _center,
                                                      _normal,
                                                      _arm,
                                                      _angleArcDeg,
                                                      _angleCupDeg,
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
