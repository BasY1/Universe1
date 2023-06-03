#include "item3dsphereslice.h"

Universe1::Video::Item3DSphereSlice::Item3DSphereSlice(const bool _inner,
                                                       const QVector3D &_center,
                                                       const QVector3D &_normal,
                                                       const QVector3D &_arm,
                                                       const float _angleLatBeginDeg,
                                                       const float _angleLatEndDeg,
                                                       const float _angleLonBeginDeg,
                                                       const float _angleLonEndDeg,
                                                       const float _radius,
                                                       const uint _quality,
                                                       const bool _visible,
                                                       const Material &_material,
                                                       const std::string &_name)
    : Item3DSphere(_inner, _center, _radius, _quality, _visible, _material, _name)
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")
    , angleLatBeginDeg(_angleLatBeginDeg, _name + ".angleLatBeginDeg")
    , angleLatEndDeg(_angleLatEndDeg, _name + ".angleLatEndDeg")
    , angleLonBeginDeg(_angleLonBeginDeg, _name + ".angleLonBeginDeg")
    , angleLonEndDeg(_angleLonEndDeg, _name + ".angleLonEndDeg")
{
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&angleLatBeginDeg);
    props.push_back(&angleLatEndDeg);
    props.push_back(&angleLonBeginDeg);
    props.push_back(&angleLonEndDeg);
}

void Universe1::Video::Item3DSphereSlice::addData3D(std::list<Data3D> &_out,
                                                    const Shader *,  // _shader,
                                                    const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              angleLatBeginDeg.getValue(_timeStep),
              angleLatEndDeg.getValue(_timeStep),
              angleLonBeginDeg.getValue(_timeStep),
              angleLonEndDeg.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DSphereSlice::buildData(std::list<Data3D> &_out,
                                                    const QVector3D &_center,
                                                    const QVector3D &_normal,
                                                    const QVector3D &_arm,
                                                    const float _angleLatBeginDeg,
                                                    const float _angleLatEndDeg,
                                                    const float _angleLonBeginDeg,
                                                    const float _angleLonEndDeg,
                                                    const float _radius,
                                                    const uint _quality,
                                                    const Material &_material,
                                                    const bool _inner)
{
    float lab = std::max(0.0f, _angleLatBeginDeg);
    float lae = std::min(180.0f, _angleLatEndDeg);
    float lob = std::max(0.0f, _angleLonBeginDeg);
    float loe = std::min(360.0f, _angleLonEndDeg);

    if (qFuzzyCompare(lab, lae) || qFuzzyCompare(lob, loe))
        return;

    if (lab > lae)
        std::swap(lab, lae);
    if (lob > loe)
        std::swap(lob, loe);

    uint anglesLo = 0U, anglesLa = 0U;

    const std::pair<uint, uint> lola = loLaPointCount(_quality);
    const float stepAngleLoDeg = 360.0f / static_cast<float>(lola.first);
    uint s = 1U + static_cast<uint>(lob / stepAngleLoDeg);
    float as = static_cast<float>(s) * stepAngleLoDeg;

    anglesLo++;
    while (!qFuzzyCompare(as, loe) && as < loe)
    {
        anglesLo++;
        as += stepAngleLoDeg;
    }
    anglesLo++;

    const float stepAngleLaDeg = 180.0f / static_cast<float>(lola.second + 1U);
    s = 1U + static_cast<uint>(lab / stepAngleLaDeg);
    as = static_cast<float>(s) * stepAngleLaDeg;

    anglesLa++;
    while (!qFuzzyCompare(as, lae) && as < lae)
    {
        anglesLa++;
        as += stepAngleLaDeg;
    }
    anglesLa++;

    uint idx = 0U;
    _out.push_back({_material, anglesLo * anglesLa, (anglesLo - 1UL) * (anglesLa - 1UL) * 6UL});
    addSphereSlice(_out.back(),
                   idx,
                   _center,
                   _normal,
                   _arm,
                   _angleLatBeginDeg,
                   _angleLatEndDeg,
                   _angleLonBeginDeg,
                   _angleLonEndDeg,
                   _radius,
                   _quality,
                   _inner);
}

void Universe1::Video::Item3DSphereSlice::addSphereSlice(Data3D &_data,
                                                         uint &_idx,
                                                         const QVector3D &_center,
                                                         const QVector3D &_normal,
                                                         const QVector3D &_arm,
                                                         const float _angleLatBeginDeg,
                                                         const float _angleLatEndDeg,
                                                         const float _angleLonBeginDeg,
                                                         const float _angleLonEndDeg,
                                                         const float _radius,
                                                         const uint _quality,
                                                         const bool _inner)
{
    float lab = std::max(0.0f, _angleLatBeginDeg);
    float lae = std::min(180.0f, _angleLatEndDeg);
    float lob = std::max(0.0f, _angleLonBeginDeg);
    float loe = std::min(360.0f, _angleLonEndDeg);

    if (qFuzzyCompare(lab, lae) || qFuzzyCompare(lob, loe))
        return;

    if (lab > lae)
        std::swap(lab, lae);
    if (lob > loe)
        std::swap(lob, loe);

    std::list<float> anglesLo, anglesLa;

    const std::pair<uint, uint> lola = loLaPointCount(_quality);
    const float stepAngleLoDeg = 360.0f / static_cast<float>(lola.first);
    uint s = 1U + static_cast<uint>(lob / stepAngleLoDeg);
    float as = static_cast<float>(s) * stepAngleLoDeg;

    anglesLo.push_back(lob);
    while (!qFuzzyCompare(as, loe) && as < loe)
    {
        anglesLo.push_back(as);
        as += stepAngleLoDeg;
    }
    anglesLo.push_back(loe);

    const float stepAngleLaDeg = 180.0f / static_cast<float>(lola.second + 1U);
    s = 1U + static_cast<uint>(lab / stepAngleLaDeg);
    as = static_cast<float>(s) * stepAngleLaDeg;

    anglesLa.push_back(lab);
    while (!qFuzzyCompare(as, lae) && as < lae)
    {
        anglesLa.push_back(as);
        as += stepAngleLaDeg;
    }
    anglesLa.push_back(lae);

    const QVector3D nn = _normal.normalized();
    const QVector3D aa = _arm.normalized();
    const QVector3D ss = QVector3D::crossProduct(nn, aa).normalized();
    for (const float la : anglesLa)
    {
        const QVector3D a = QQuaternion::fromAxisAndAngle(ss, la).rotatedVector(nn).normalized();
        for (const float lo : anglesLo)
        {
            const QVector3D n = QQuaternion::fromAxisAndAngle(nn, lo).rotatedVector(a).normalized();
            _data.points.push_back(_center + n * _radius);
            if (_inner)
                _data.normals.push_back(-n);
            else
                _data.normals.push_back(n);
        }
    }

    if (!_inner)
    {
        for (uint la = 0U; la < anglesLa.size() - 1U; ++la)
        {
            const uint laa = _idx + la * anglesLo.size();
            for (uint lo = 0U; lo < anglesLo.size() - 1U; ++lo)
            {
                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + lo + 1U);
                _data.indexes.push_back(laa + anglesLo.size() + lo + 1U);

                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + anglesLo.size() + lo + 1U);
                _data.indexes.push_back(laa + anglesLo.size() + lo);
            }
        }
    }
    else
    {
        for (uint la = 0U; la < anglesLa.size() - 1U; ++la)
        {
            const uint laa = _idx + la * anglesLo.size();
            for (uint lo = 0U; lo < anglesLo.size() - 1U; ++lo)
            {
                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + anglesLo.size() + lo + 1U);
                _data.indexes.push_back(laa + lo + 1U);

                _data.indexes.push_back(laa + lo);
                _data.indexes.push_back(laa + anglesLo.size() + lo);
                _data.indexes.push_back(laa + anglesLo.size() + lo + 1U);
            }
        }
    }

    _idx += anglesLo.size() * anglesLa.size();
}

Universe1::Video::DBItem3DSphereSlice::DBItem3DSphereSlice(const std::string &_footageName,

                                                           std::list<Item3D *> *_items)
    : DBItems3D("sphereSlice", _footageName, _items)
{
}

Universe1::Video::Item3DSphereSlice *Universe1::Video::DBItem3DSphereSlice::add(const bool _inner,
                                                                                const QVector3D &_center,
                                                                                const QVector3D &_normal,
                                                                                const QVector3D &_arm,
                                                                                const float _angleLatBeginDeg,
                                                                                const float _angleLatEndDeg,
                                                                                const float _angleLonBeginDeg,
                                                                                const float _angleLonEndDeg,
                                                                                const float _radius,
                                                                                const uint _quality,
                                                                                const bool _visible,
                                                                                const Material &_material)
{
    Item3DSphereSlice *result = new Item3DSphereSlice(_inner,
                                                      _center,
                                                      _normal,
                                                      _arm,
                                                      _angleLatBeginDeg,
                                                      _angleLatEndDeg,
                                                      _angleLonBeginDeg,
                                                      _angleLonEndDeg,
                                                      _radius,
                                                      _quality,
                                                      _visible,
                                                      _material,
                                                      nextName());
    items->push_back(result);
    return result;
}
