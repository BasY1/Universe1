#include "item3dspherecup.h"

Universe1::Video::Item3DSphereCup::Item3DSphereCup(const bool _inner,
                                                   const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const float _angleDeg,
                                                   const float _radius,
                                                   const uint _quality,
                                                   const bool _visible,
                                                   const Material &_material,
                                                   const std::string &_name)
    : Item3DSphere(_inner, _center, _radius, _quality, _visible, _material, _name)
    , normal(_normal, _name + ".normal")
    , angleDeg(_angleDeg, _name + ".angleDeg")
{
    props.push_back(&normal);
    props.push_back(&angleDeg);
}

void Universe1::Video::Item3DSphereCup::addData3D(std::list<Data3D> &_out,
                                                  const Shader *,  // _shader,
                                                  const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              angleDeg.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DSphereCup::buildData(std::list<Data3D> &_out,
                                                  const QVector3D &_center,
                                                  const QVector3D &_normal,
                                                  const QVector3D &_arm,
                                                  const float _angleDeg,
                                                  const float _radius,
                                                  const uint _quality,
                                                  const Material &_material,
                                                  const bool _inner)
{
    if (qFuzzyIsNull(_angleDeg) || _angleDeg < 0.0f)
        return;

    if (qFuzzyCompare(_angleDeg, 180.0f) || _angleDeg > 180.0f)
    {
        Item3DSphere::buildData(_out, _center, _radius, _quality, _material, _inner);
        return;
    }

    const std::pair<uint, uint> lola = loLaPointCount(_quality);
    const float stepAngleDeg = 180.0f / static_cast<float>(lola.second + 1U);
    uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    if (!qFuzzyCompare(angleDegFromSteps, _angleDeg))
        ++steps;

    const size_t cntPoint = lola.first * steps + 1UL;
    const size_t cntIndex = lola.first * steps * 6UL + lola.first * 3U;

    uint idx = 0U;
    _out.push_back({_material, cntPoint, cntIndex});
    addSphereCup(_out.back(), idx, _center, _normal, _arm, _angleDeg, _radius, _quality, _inner);
}

void Universe1::Video::Item3DSphereCup::addSphereCup(Data3D &_data,
                                                     uint &_idx,
                                                     const QVector3D &_center,
                                                     const QVector3D &_normal,
                                                     const QVector3D &_arm,
                                                     const float _angleDeg,
                                                     const float _radius,
                                                     const uint _quality,
                                                     const bool _inner)
{
    if (qFuzzyIsNull(_angleDeg) || _angleDeg < 0.0f)
        return;

    if (qFuzzyCompare(_angleDeg, 180.0f) || _angleDeg > 180.0f)
    {
        Item3DSphere::addSphere(_data, _idx, _center, _radius, _quality, _inner);
        return;
    }

    const std::pair<uint, uint> lola = loLaPointCount(_quality);
    const float stepAngleDeg = 180.0f / static_cast<float>(lola.second + 1U);
    uint steps = _angleDeg / stepAngleDeg;
    const float angleDegFromSteps = stepAngleDeg * static_cast<float>(steps);
    const bool addRest = !qFuzzyCompare(angleDegFromSteps, _angleDeg);

    const QVector3D nn = _normal.normalized();
    const QVector3D aa = _arm.normalized();
    const QQuaternion rotLo = QQuaternion::fromAxisAndAngle(nn, 360.0f / static_cast<float>(lola.first));
    const QQuaternion rotLa = QQuaternion::fromAxisAndAngle(aa, stepAngleDeg);

    _data.points.push_back(_center + nn * _radius);
    if (_inner)
        _data.normals.push_back(-nn);
    else
        _data.normals.push_back(nn);

    QVector3D a = rotLa.rotatedVector(nn).normalized();
    for (uint la = 1U; la <= steps; ++la)
    {
        QVector3D o = a;
        for (uint lo = 0U; lo < lola.first; ++lo, o = rotLo.rotatedVector(o).normalized())
        {
            _data.points.push_back(_center + o * _radius);
            if (_inner)
                _data.normals.push_back(-o);
            else
                _data.normals.push_back(o);
        }
        a = rotLa.rotatedVector(a).normalized();
    }

    if (addRest)
    {
        const QQuaternion rotLa2 = QQuaternion::fromAxisAndAngle(aa, _angleDeg);
        QVector3D o = rotLa2.rotatedVector(nn).normalized();
        for (uint lo = 0U; lo < lola.first; ++lo, o = rotLo.rotatedVector(o).normalized())
        {
            _data.points.push_back(_center + o * _radius);
            if (_inner)
                _data.normals.push_back(-o);
            else
                _data.normals.push_back(o);
        }

        steps++;
    }

    if (_inner)
    {
        for (uint lo = 0U; lo < lola.first - 1U; ++lo)
        {
            _data.indexes.push_back(_idx + 0U);
            _data.indexes.push_back(_idx + lo + 1U);
            _data.indexes.push_back(_idx + lo + 2U);
        }

        _data.indexes.push_back(_idx + 0U);
        _data.indexes.push_back(_idx + lola.first);
        _data.indexes.push_back(_idx + 1U);

        for (uint la = 0U; la < steps - 1U; ++la)
        {
            for (uint lo = 0U; lo < lola.first - 1U; ++lo)
            {
                _data.indexes.push_back(_idx + la * lola.first + lo + 1U);
                _data.indexes.push_back(_idx + (la + 1U) * lola.first + lo + 2U);
                _data.indexes.push_back(_idx + la * lola.first + lo + 2U);

                _data.indexes.push_back(_idx + la * lola.first + lo + 1U);
                _data.indexes.push_back(_idx + (la + 1U) * lola.first + lo + 1U);
                _data.indexes.push_back(_idx + (la + 1U) * lola.first + lo + 2U);
            }

            _data.indexes.push_back(_idx + (la + 1U) * lola.first);
            _data.indexes.push_back(_idx + (la + 1U) * lola.first + 1U);
            _data.indexes.push_back(_idx + la * lola.first + 1U);

            _data.indexes.push_back(_idx + (la + 1U) * lola.first);
            _data.indexes.push_back(_idx + (la + 2U) * lola.first);
            _data.indexes.push_back(_idx + (la + 1U) * lola.first + 1U);
        }
    }
    else
    {
        for (uint lo = 0U; lo < lola.first - 1U; ++lo)
        {
            _data.indexes.push_back(_idx + 0U);
            _data.indexes.push_back(_idx + lo + 2U);
            _data.indexes.push_back(_idx + lo + 1U);
        }

        _data.indexes.push_back(_idx + 0U);
        _data.indexes.push_back(_idx + 1U);
        _data.indexes.push_back(_idx + lola.first);

        for (uint la = 0U; la < steps - 1U; ++la)
        {
            for (uint lo = 0U; lo < lola.first - 1U; ++lo)
            {
                _data.indexes.push_back(_idx + la * lola.first + lo + 1U);
                _data.indexes.push_back(_idx + la * lola.first + lo + 2U);
                _data.indexes.push_back(_idx + (la + 1U) * lola.first + lo + 2U);

                _data.indexes.push_back(_idx + la * lola.first + lo + 1U);
                _data.indexes.push_back(_idx + (la + 1U) * lola.first + lo + 2U);
                _data.indexes.push_back(_idx + (la + 1U) * lola.first + lo + 1U);
            }

            _data.indexes.push_back(_idx + (la + 1U) * lola.first);
            _data.indexes.push_back(_idx + la * lola.first + 1U);
            _data.indexes.push_back(_idx + (la + 1U) * lola.first + 1U);

            _data.indexes.push_back(_idx + (la + 1U) * lola.first);
            _data.indexes.push_back(_idx + (la + 1U) * lola.first + 1U);
            _data.indexes.push_back(_idx + (la + 2U) * lola.first);
        }
    }

    _idx += lola.first * steps + 1U;
}

Universe1::Video::DBItem3DSphereCup::DBItem3DSphereCup(const std::string &_footageName,

                                                       std::list<Item3D *> *_items)
    : DBItems3D("sphereCup", _footageName, _items)
{
}

Universe1::Video::Item3DSphereCup *Universe1::Video::DBItem3DSphereCup::add(const bool _inner,
                                                                            const QVector3D &_center,
                                                                            const QVector3D &_normal,
                                                                            const float _angleDeg,
                                                                            const float _radius,
                                                                            const uint _quality,
                                                                            const bool _visible,
                                                                            const Material &_material)
{
    Item3DSphereCup *result =
        new Item3DSphereCup(_inner, _center, _normal, _angleDeg, _radius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
