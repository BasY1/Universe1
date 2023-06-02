#include "item3dtoruscup.h"

Universe1::Video::Item3DTorusCup::Item3DTorusCup(const bool _insideCup,
                                                 const bool _inner,
                                                 const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const float _angleCupDeg,
                                                 const float _radiusRing,
                                                 const float _radiusLine,
                                                 const uint _qualityRing,
                                                 const uint _qualityLine,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DTorus(
          _inner, _center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _visible, _material, _name)
    , insideCup(_insideCup)
    , angleCupDeg(_angleCupDeg, _name + ".angleCupDeg")
{
    props.push_back(&angleCupDeg);
}

void Universe1::Video::Item3DTorusCup::addData3D(std::list<Data3D> &_out,
                                                 const Shader *,  // _shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              angleCupDeg.getValue(_timeStep),
              radiusRing.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityRing.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep),
              insideCup,
              inner);
}

void Universe1::Video::Item3DTorusCup::buildData(std::list<Data3D> &_out,
                                                 const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_arm,
                                                 const float _angleCupDeg,
                                                 const float _radiusRing,
                                                 const float _radiusLine,
                                                 const uint _qualityRing,
                                                 const uint _qualityLine,
                                                 const Material &_material,
                                                 const bool _insideCup,
                                                 const bool _inner)
{
    if (qFuzzyIsNull(_angleCupDeg) || _angleCupDeg < 0.0f)
        return;

    if (qFuzzyCompare(_angleCupDeg, 180.0f) || _angleCupDeg > 180.0f)
    {
        Item3DTorus::buildData(
            _out, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _material, _inner);
        return;
    }

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepLine = 360.0 / static_cast<float>(cntLine);
    uint steps = static_cast<uint>(_angleCupDeg / stepLine);
    const float angleSteps = static_cast<float>(steps) * stepLine;
    if (!qFuzzyCompare(angleSteps, _angleCupDeg))
        steps++;
    const uint cntLine2 = 1U + steps * 2U;
    uint idx = 0U;
    _out.push_back({_material, cntLine2 * cntRing, (cntLine2 - 1U) * cntRing * 6U});
    addTorusCup(_out.back(),
                idx,
                _center,
                _normal,
                _arm,
                _angleCupDeg,
                _radiusRing,
                _radiusLine,
                _qualityRing,
                _qualityLine,
                _insideCup,
                _inner);
}

void Universe1::Video::Item3DTorusCup::addTorusCup(Data3D &_data,
                                                   uint &_idx,
                                                   const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
                                                   const float _angleCupDeg,
                                                   const float _radiusRing,
                                                   const float _radiusLine,
                                                   const uint _qualityRing,
                                                   const uint _qualityLine,
                                                   const bool _insideCup,
                                                   const bool _inner)
{
    if (qFuzzyIsNull(_angleCupDeg) || _angleCupDeg < 0.0f)
        return;

    if (qFuzzyCompare(_angleCupDeg, 180.0f) || _angleCupDeg > 180.0f)
    {
        Item3DTorus::addTorus(
            _data, _idx, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _inner);
        return;
    }

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepLine = 360.0 / static_cast<float>(cntLine);
    const uint steps = static_cast<uint>(_angleCupDeg / stepLine);
    const float angleSteps = static_cast<float>(steps) * stepLine;
    const bool addRest = !qFuzzyCompare(angleSteps, _angleCupDeg);

    const uint stepsLine = steps * 2U + 1U;
    const uint cntLine2 = 1U + (addRest ? ((steps + 1U) * 2U) : (steps * 2U));

    const QVector3D n = _normal.normalized();

    const QQuaternion rotRing = QQuaternion::fromAxisAndAngle(n, 360.0 / static_cast<float>(cntRing));
    QVector3D ar = _arm.normalized();

    for (uint r = 0U; r < cntRing; ++r)
    {
        const QVector3D nLine = QVector3D::crossProduct(n, ar).normalized();
        const QVector3D cr = _center + ar * _radiusRing;
        const QVector3D a0 = _insideCup ? -ar : ar;

        if (addRest)
        {
            const QVector3D al = QQuaternion::fromAxisAndAngle(nLine, -_angleCupDeg).rotatedVector(a0).normalized();
            _data.points.push_back(cr + al * _radiusLine);
            if (_inner)
                _data.normals.push_back(-al);
            else
                _data.normals.push_back(al);
        }

        const QQuaternion rotLine = QQuaternion::fromAxisAndAngle(nLine, stepLine);
        QVector3D a1 = QQuaternion::fromAxisAndAngle(nLine, -angleSteps).rotatedVector(a0).normalized();
        for (uint i = 0U; i < stepsLine; ++i)
        {
            _data.points.push_back(cr + a1 * _radiusLine);
            if (_inner)
                _data.normals.push_back(-a1);
            else
                _data.normals.push_back(a1);

            a1 = rotLine.rotatedVector(a1).normalized();
        }

        if (addRest)
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

    if (_inner)
    {
        for (uint r = 0U; r < cntRing - 1U; ++r)
        {
            for (uint l = 0U; l < cntLine2 - 1U; ++l)
            {
                _data.indexes.push_back(_idx + r * cntLine2 + l);
                _data.indexes.push_back(_idx + r * cntLine2 + l + 1U);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine2 + l + 1U);

                _data.indexes.push_back(_idx + r * cntLine2 + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine2 + l + 1U);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine2 + l);
            }
        }

        for (uint l = 0U; l < cntLine2 - 1U; ++l)
        {
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine2 + l);
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine2 + l + 1U);
            _data.indexes.push_back(_idx + l + 1U);

            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine2 + l);
            _data.indexes.push_back(_idx + l + 1U);
            _data.indexes.push_back(_idx + l);
        }
    }
    else
    {
        for (uint r = 0U; r < cntRing - 1U; ++r)
        {
            for (uint l = 0U; l < cntLine2 - 1U; ++l)
            {
                _data.indexes.push_back(_idx + r * cntLine2 + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine2 + l + 1U);
                _data.indexes.push_back(_idx + r * cntLine2 + l + 1U);

                _data.indexes.push_back(_idx + r * cntLine2 + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine2 + l);
                _data.indexes.push_back(_idx + (r + 1U) * cntLine2 + l + 1U);
            }
        }

        for (uint l = 0U; l < cntLine2 - 1U; ++l)
        {
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine2 + l);
            _data.indexes.push_back(_idx + l + 1U);
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine2 + l + 1U);

            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine2 + l);
            _data.indexes.push_back(_idx + l);
            _data.indexes.push_back(_idx + l + 1U);
        }
    }

    _idx += cntRing * cntLine2;
}

Universe1::Video::DBItem3DTorusCup::DBItem3DTorusCup(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("torusCup", _footageName, _items)
{
}

Universe1::Video::Item3DTorusCup *Universe1::Video::DBItem3DTorusCup::add(const bool _inside,
                                                                          const bool _inner,
                                                                          const QVector3D &_center,
                                                                          const QVector3D &_normal,
                                                                          const float _angleCupDeg,
                                                                          const float _radiusRing,
                                                                          const float _radiusLine,
                                                                          const uint _qualityRing,
                                                                          const uint _qualityLine,
                                                                          const bool _visible,
                                                                          const Material &_material)
{
    Item3DTorusCup *result = new Item3DTorusCup(_inside,
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
                                                nextName());
    items->push_back(result);
    return result;
}
