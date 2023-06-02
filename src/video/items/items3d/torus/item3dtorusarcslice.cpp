#include "item3dtorusarcslice.h"

Universe1::Video::Item3DTorusArcSlice::Item3DTorusArcSlice(const bool _inner,
                                                           const QVector3D &_center,
                                                           const QVector3D &_normal,
                                                           const QVector3D &_arm,
                                                           const float _angleArcStartDeg,
                                                           const float _angleArcEndDeg,
                                                           const float _angleSliceStartDeg,
                                                           const float _angleSliceEndDeg,
                                                           const float _radiusRing,
                                                           const float _radiusLine,
                                                           const uint _qualityRing,
                                                           const uint _qualityLine,
                                                           const bool _visible,
                                                           const Material &_material,
                                                           const std::string &_name)
    : Item3DTorusSlice(_inner,
                       _center,
                       _normal,
                       _angleSliceStartDeg,
                       _angleSliceEndDeg,
                       _radiusRing,
                       _radiusLine,
                       _qualityRing,
                       _qualityLine,
                       _visible,
                       _material,
                       _name)
    , arm(_arm, _name + ".arm")
    , angleArcStartDeg(_angleArcStartDeg, _name + ".angleArcStartDeg")
    , angleArcEndDeg(_angleArcEndDeg, _name + ".angleArcEndDeg")
{
    props.push_back(&arm);
    props.push_back(&angleArcStartDeg);
    props.push_back(&angleArcEndDeg);
}

void Universe1::Video::Item3DTorusArcSlice::addData3D(std::list<Data3D> &_out,
                                                      const Shader *,  // _shader,
                                                      const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleArcStartDeg.getValue(_timeStep),
              angleArcEndDeg.getValue(_timeStep),
              angleSliceStartDeg.getValue(_timeStep),
              angleSliceEndDeg.getValue(_timeStep),
              radiusRing.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityRing.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DTorusArcSlice::buildData(std::list<Data3D> &_out,
                                                      const QVector3D &_center,
                                                      const QVector3D &_normal,
                                                      const QVector3D &_arm,
                                                      const float _angleArcStartDeg,
                                                      const float _angleArcEndDeg,
                                                      const float _angleSliceStartDeg,
                                                      const float _angleSliceEndDeg,
                                                      const float _radiusRing,
                                                      const float _radiusLine,
                                                      const uint _qualityRing,
                                                      const uint _qualityLine,
                                                      const Material &_material,
                                                      const bool _inner)
{
    if (qFuzzyIsNull(_radiusRing) || qFuzzyIsNull(_radiusLine) || _radiusRing < 0.0f || _radiusLine < 0.0f)
        return;

    float aas = std::max(0.0f, _angleArcStartDeg);
    float aae = std::min(360.0f, _angleArcEndDeg);
    float ass = std::max(0.0f, _angleSliceStartDeg);
    float ase = std::min(360.0f, _angleSliceEndDeg);
    if (qFuzzyCompare(ass, ase) || qFuzzyCompare(aas, aae))
        return;
    if (ass > ase)
        std::swap(ass, ase);
    if (aas > aae)
        std::swap(aas, aae);

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepAngleRing = 360.0f / static_cast<float>(cntRing);
    const float stepAngleLine = 360.0f / static_cast<float>(cntLine);
    float ang = static_cast<float>(1U + static_cast<uint>(aas / stepAngleRing)) * stepAngleRing;
    std::list<float> anglesLine, anglesRing;

    anglesRing.push_back(aas);
    while (!qFuzzyCompare(ang, aae) && ang < aae)
    {
        anglesRing.push_back(ang);
        ang += stepAngleRing;
    }
    anglesRing.push_back(aae);

    ang = static_cast<float>(1U + static_cast<uint>(ass / stepAngleLine)) * stepAngleLine;
    anglesLine.push_back(ass);
    while (!qFuzzyCompare(ang, ase) && ang < ase)
    {
        anglesLine.push_back(ang);
        ang += stepAngleLine;
    }
    anglesLine.push_back(ase);

    const uint cntRing2 = anglesRing.size();
    const uint cntLine2 = anglesLine.size();
    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);

    _out.push_back({_material, cntLine2 * cntRing2, (cntLine2 - 1U) * (cntRing2 - 1U) * 6U});
    Data3D &data = _out.back();

    for (const float &curAngleRing : anglesRing)
    {
        const QVector3D aa = QQuaternion::fromAxisAndAngle(n, curAngleRing).rotatedVector(a).normalized();
        const QVector3D nLine = QVector3D::crossProduct(n, aa).normalized();
        const QVector3D cr = _center + aa * _radiusRing;
        for (const float &curAngleLine : anglesLine)
        {
            const QVector3D a0 = QQuaternion::fromAxisAndAngle(nLine, curAngleLine).rotatedVector(aa).normalized();
            data.points.push_back(cr + a0 * _radiusLine);
            if (_inner)
                data.normals.push_back(-a0);
            else
                data.normals.push_back(a0);
        }
    }

    uint idx = 0U;
    if (_inner)
    {
        for (uint la = 0U; la < cntRing2 - 1U; ++la)
        {
            const uint laa = idx + la * cntLine2;
            for (uint lo = 0U; lo < cntLine2 - 1U; ++lo)
            {
                data.indexes.push_back(laa + lo);
                data.indexes.push_back(laa + lo + 1U);
                data.indexes.push_back(laa + cntLine2 + lo + 1U);

                data.indexes.push_back(laa + lo);
                data.indexes.push_back(laa + cntLine2 + lo + 1U);
                data.indexes.push_back(laa + cntLine2 + lo);
            }
        }
    }
    else
    {
        for (uint la = 0U; la < cntRing2 - 1U; ++la)
        {
            const uint laa = idx + la * cntLine2;
            for (uint lo = 0U; lo < cntLine2 - 1U; ++lo)
            {
                data.indexes.push_back(laa + lo);
                data.indexes.push_back(laa + cntLine2 + lo + 1U);
                data.indexes.push_back(laa + lo + 1U);

                data.indexes.push_back(laa + lo);
                data.indexes.push_back(laa + cntLine2 + lo);
                data.indexes.push_back(laa + cntLine2 + lo + 1U);
            }
        }
    }
}

Universe1::Video::DBItem3DTorusArcSlice::DBItem3DTorusArcSlice(const std::string &_footageName,
                                                               std::list<Item3D *> *_items)
    : DBItems3D("torusArcSlice", _footageName, _items)
{
}

Universe1::Video::Item3DTorusArcSlice *Universe1::Video::DBItem3DTorusArcSlice::add(const bool _inner,
                                                                                    const QVector3D &_center,
                                                                                    const QVector3D &_normal,
                                                                                    const QVector3D &_arm,
                                                                                    const float _angleArcStartDeg,
                                                                                    const float _angleArcEndDeg,
                                                                                    const float _angleSliceStartDeg,
                                                                                    const float _angleSliceEndDeg,
                                                                                    const float _radiusRing,
                                                                                    const float _radiusLine,
                                                                                    const uint _qualityRing,
                                                                                    const uint _qualityLine,
                                                                                    const bool _visible,
                                                                                    const Material &_material)
{
    Item3DTorusArcSlice *result = new Item3DTorusArcSlice(_inner,
                                                          _center,
                                                          _normal,
                                                          _arm,
                                                          _angleArcStartDeg,
                                                          _angleArcEndDeg,
                                                          _angleSliceStartDeg,
                                                          _angleSliceEndDeg,
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
