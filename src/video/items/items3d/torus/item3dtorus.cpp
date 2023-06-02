#include "item3dtorus.h"

Universe1::Video::Item3DTorus::Item3DTorus(const bool _inner,
                                           const QVector3D &_center,
                                           const QVector3D &_normal,
                                           const float _radiusRing,
                                           const float _radiusLine,
                                           const uint _qualityRing,
                                           const uint _qualityLine,
                                           const bool _visible,
                                           const Material &_material,
                                           const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , inner(_inner)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , radiusRing(_radiusRing, _name + ".radiusRing")
    , radiusLine(_radiusLine, _name + ".radiusLine")
    , qualityRing(_qualityRing, _name + ".qualityRing")
    , qualityLine(_qualityLine, _name + ".qualityLine")

{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&radiusRing);
    props.push_back(&radiusLine);
    props.push_back(&qualityRing);
    props.push_back(&qualityLine);
}

void Universe1::Video::Item3DTorus::addData3D(std::list<Data3D> &_out,
                                              const Shader *,  // _shader,
                                              const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              radiusRing.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              qualityRing.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DTorus::buildData(std::list<Data3D> &_out,
                                              const QVector3D &_center,
                                              const QVector3D &_normal,
                                              const QVector3D &_arm,
                                              const float _radiusRing,
                                              const float _radiusLine,
                                              const uint _qualityRing,
                                              const uint _qualityLine,
                                              const Material &_material,
                                              const bool _inner)
{
    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const uint cntPoint = cntRing * cntLine;
    uint idx = 0U;
    _out.push_back({_material, cntPoint, cntPoint * 6UL});
    addTorus(_out.back(), idx, _center, _normal, _arm, _radiusRing, _radiusLine, _qualityRing, _qualityLine, _inner);
}

void Universe1::Video::Item3DTorus::addTorus(Data3D &_data,
                                             uint &_idx,
                                             const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _radiusRing,
                                             const float _radiusLine,
                                             const uint _qualityRing,
                                             const uint _qualityLine,
                                             const bool _inner)
{
    const uint cntRing = circlePointCount(_qualityRing);
    const uint cntLine = circlePointCount(_qualityLine);
    const QVector3D n = _normal.normalized();

    const QQuaternion rotRing = QQuaternion::fromAxisAndAngle(n, 360.0 / static_cast<float>(cntRing));
    QVector3D ar = _arm.normalized();
    for (uint r = 0U; r < cntRing; ++r)
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

    if (_inner)
    {
        for (uint r = 0U; r < cntRing - 1U; ++r)
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

        for (uint l = 0U; l < cntLine - 1U; ++l)
        {
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine + l);
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine + l + 1U);
            _data.indexes.push_back(_idx + l + 1U);

            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine + l);
            _data.indexes.push_back(_idx + l + 1U);
            _data.indexes.push_back(_idx + l);
        }

        _data.indexes.push_back(_idx + cntRing * cntLine - 1U);
        _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine);
        _data.indexes.push_back(_idx);

        _data.indexes.push_back(_idx + cntRing * cntLine - 1U);
        _data.indexes.push_back(_idx);
        _data.indexes.push_back(_idx + cntLine - 1U);
    }
    else
    {
        for (uint r = 0U; r < cntRing - 1U; ++r)
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

        for (uint l = 0U; l < cntLine - 1U; ++l)
        {
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine + l);
            _data.indexes.push_back(_idx + l + 1U);
            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine + l + 1U);

            _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine + l);
            _data.indexes.push_back(_idx + l);
            _data.indexes.push_back(_idx + l + 1U);
        }

        _data.indexes.push_back(_idx + cntRing * cntLine - 1U);
        _data.indexes.push_back(_idx);
        _data.indexes.push_back(_idx + (cntRing - 1U) * cntLine);

        _data.indexes.push_back(_idx + cntRing * cntLine - 1U);
        _data.indexes.push_back(_idx + cntLine - 1U);
        _data.indexes.push_back(_idx);
    }

    _idx += cntRing * cntLine;
}

Universe1::Video::DBItem3DTorus::DBItem3DTorus(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("torus", _footageName, _items)
{
}

Universe1::Video::Item3DTorus *Universe1::Video::DBItem3DTorus::add(const bool _inner,
                                                                    const QVector3D &_center,
                                                                    const QVector3D &_normal,
                                                                    const float _radiusRing,
                                                                    const float _radiusLine,
                                                                    const uint _qualityRing,
                                                                    const uint _qualityLine,
                                                                    const bool _visible,
                                                                    const Material &_material)
{
    Item3DTorus *result = new Item3DTorus(_inner,
                                          _center,
                                          _normal,
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
