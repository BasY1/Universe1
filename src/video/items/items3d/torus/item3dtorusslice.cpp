#include "item3dtorusslice.h"

Universe1::Video::Item3DTorusSlice::Item3DTorusSlice(const bool _inner,
                                                     const QVector3D &_center,
                                                     const QVector3D &_normal,
                                                     const float _angleSliceStartDeg,
                                                     const float _angleSliceEndDeg,
                                                     const float _radiusRing,
                                                     const float _radiusLine,
                                                     const uint _qualityRing,
                                                     const uint _qualityLine,
                                                     const bool _visible,
                                                     const Material &_material,
                                                     const std::string &_name)
    : Item3DTorus(
          _inner, _center, _normal, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _visible, _material, _name)
    , angleSliceStartDeg(_angleSliceStartDeg, _name + ".angleSliceStartDeg")
    , angleSliceEndDeg(_angleSliceEndDeg, _name + ".angleSliceEndDeg")
{
    props.push_back(&angleSliceStartDeg);
    props.push_back(&angleSliceEndDeg);
}

void Universe1::Video::Item3DTorusSlice::addData3D(std::list<Data3D> &_out,
                                                   const Shader *,  // _shader,
                                                   const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              angleSliceStartDeg.getValue(_timeStep),
              angleSliceEndDeg.getValue(_timeStep),
              radiusRing.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityRing.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DTorusSlice::buildData(std::list<Data3D> &_out,
                                                   const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
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

    float as = std::max(0.0f, _angleSliceStartDeg);
    float ae = std::min(360.0f, _angleSliceEndDeg);
    if (qFuzzyCompare(as, ae))
        return;
    if (as > ae)
        std::swap(as, ae);

    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const float stepAngleLine = 360.0f / static_cast<float>(cntLine);
    float ang = static_cast<float>(1U + static_cast<uint>(as / stepAngleLine)) * stepAngleLine;
    std::list<float> anglesLine;
    anglesLine.push_back(as);
    while (!qFuzzyCompare(ang, ae) && ang < ae)
    {
        anglesLine.push_back(ang);
        ang += stepAngleLine;
    }
    anglesLine.push_back(ae);
    const uint cntLine2 = anglesLine.size();
    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);
    const QQuaternion rotRing = QQuaternion::fromAxisAndAngle(n, 360.0 / static_cast<float>(cntRing));

    _out.push_back({_material, cntLine2 * cntRing, (cntLine2 - 1U) * cntRing * 6U});
    Data3D &data = _out.back();
    QVector3D aa = a;
    for (uint r = 0U; r < cntRing; ++r, aa = rotRing.rotatedVector(aa).normalized())
    {
        const QVector3D nLine = QVector3D::crossProduct(n, aa).normalized();
        const QVector3D cr = _center + aa * _radiusRing;
        for (const float &curAngle : anglesLine)
        {
            const QVector3D a0 = QQuaternion::fromAxisAndAngle(nLine, curAngle).rotatedVector(aa).normalized();
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
        for (uint r = 0U; r < cntRing - 1U; ++r)
        {
            for (uint l = 0U; l < cntLine2 - 1U; ++l)
            {
                data.indexes.push_back(idx + r * cntLine2 + l);
                data.indexes.push_back(idx + r * cntLine2 + l + 1U);
                data.indexes.push_back(idx + (r + 1U) * cntLine2 + l + 1U);

                data.indexes.push_back(idx + r * cntLine2 + l);
                data.indexes.push_back(idx + (r + 1U) * cntLine2 + l + 1U);
                data.indexes.push_back(idx + (r + 1U) * cntLine2 + l);
            }
        }

        for (uint l = 0U; l < cntLine2 - 1U; ++l)
        {
            data.indexes.push_back(idx + (cntRing - 1U) * cntLine2 + l);
            data.indexes.push_back(idx + (cntRing - 1U) * cntLine2 + l + 1U);
            data.indexes.push_back(idx + l + 1U);

            data.indexes.push_back(idx + (cntRing - 1U) * cntLine2 + l);
            data.indexes.push_back(idx + l + 1U);
            data.indexes.push_back(idx + l);
        }
    }
    else
    {
        for (uint r = 0U; r < cntRing - 1U; ++r)
        {
            for (uint l = 0U; l < cntLine2 - 1U; ++l)
            {
                data.indexes.push_back(idx + r * cntLine2 + l);
                data.indexes.push_back(idx + (r + 1U) * cntLine2 + l + 1U);
                data.indexes.push_back(idx + r * cntLine2 + l + 1U);

                data.indexes.push_back(idx + r * cntLine2 + l);
                data.indexes.push_back(idx + (r + 1U) * cntLine2 + l);
                data.indexes.push_back(idx + (r + 1U) * cntLine2 + l + 1U);
            }
        }

        for (uint l = 0U; l < cntLine2 - 1U; ++l)
        {
            data.indexes.push_back(idx + (cntRing - 1U) * cntLine2 + l);
            data.indexes.push_back(idx + l + 1U);
            data.indexes.push_back(idx + (cntRing - 1U) * cntLine2 + l + 1U);

            data.indexes.push_back(idx + (cntRing - 1U) * cntLine2 + l);
            data.indexes.push_back(idx + l);
            data.indexes.push_back(idx + l + 1U);
        }
    }
}

Universe1::Video::DBItem3DTorusSlice::DBItem3DTorusSlice(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("torusSlice", _footageName, _items)
{
}

Universe1::Video::Item3DTorusSlice *Universe1::Video::DBItem3DTorusSlice::add(const bool _inner,
                                                                              const QVector3D &_center,
                                                                              const QVector3D &_normal,
                                                                              const float _angleSliceStartDeg,
                                                                              const float _angleSliceEndDeg,
                                                                              const float _radiusRing,
                                                                              const float _radiusLine,
                                                                              const uint _qualityRing,
                                                                              const uint _qualityLine,
                                                                              const bool _visible,
                                                                              const Material &_material)
{
    Item3DTorusSlice *result = new Item3DTorusSlice(_inner,
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
                                                    nextName());
    items->push_back(result);
    return result;
}
