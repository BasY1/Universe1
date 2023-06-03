#include "item3dsphere.h"

Universe1::Video::Item3DSphere::Item3DSphere(const bool _inner,
                                             const QVector3D &_center,
                                             const float _radius,
                                             const uint _quality,
                                             const bool _visible,
                                             const Material &_material,
                                             const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , inner(_inner)
    , center(_center, _name + ".center")
    , radius(_radius, _name + ".radius")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&center);
    props.push_back(&radius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DSphere::addData3D(std::list<Data3D> &_out,
                                               const Shader *,  // _shader,
                                               const uint64_t _timeStep) const
{
    buildData(_out,
              center.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              material.getValue(_timeStep),
              inner);
}

void Universe1::Video::Item3DSphere::buildData(std::list<Data3D> &_out,
                                               const QVector3D &_center,
                                               const QVector3D &_normal,
                                               const QVector3D &_arm,
                                               const float _radius,
                                               const uint _quality,
                                               const Material &_material,
                                               const bool _inner)
{
    if (qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;

    // const size_t cntLo = (_quality + 1U) * 4U;
    // const size_t cntLa = _quality * 2U + 1U;
    // const size_t cntPoint = cntLo * cntLa + 2UL;
    // const size_t cntIndex = cntLo * cntLa * 6UL;
    const std::pair<uint, uint> cnts = spherePointCount(_quality);
    uint idx = 0U;
    _out.push_back({_material, cnts.first, cnts.second});
    addSphere(_out.back(), idx, _center, _normal, _arm, _radius, _quality, _inner);
}

void Universe1::Video::Item3DSphere::addSphere(Data3D &_data,
                                               uint &_idx,
                                               const QVector3D &_center,
                                               const QVector3D &_normal,
                                               const QVector3D &_arm,
                                               const float _radius,
                                               const uint _quality,
                                               const bool _inner)
{
    if (qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;

    const QVector3D n = _normal.normalized();
    const QVector3D aa = _arm.normalized();
    const std::pair<uint, uint> lola = loLaPointCount(_quality);
    const uint cntLo = lola.first;
    const uint cntLa = lola.second;
    const QQuaternion rotLo = QQuaternion::fromAxisAndAngle(n, 360.0f / static_cast<float>(cntLo));
    const QQuaternion rotLa = QQuaternion::fromAxisAndAngle(aa, 180.0f / static_cast<float>(cntLa + 1U));
    const uint last = 1U + cntLa * cntLo;

    QVector3D a = rotLa.rotatedVector(n).normalized();

    _data.points.push_back(_center + n * _radius);
    if (_inner)
        _data.normals.push_back(-n);
    else
        _data.normals.push_back(n);

    for (uint la = 0U; la < cntLa; ++la, a = rotLa.rotatedVector(a).normalized())
    {
        QVector3D o = a;
        for (uint lo = 0U; lo < cntLo; ++lo, o = rotLo.rotatedVector(o).normalized())
        {
            _data.points.push_back(_center + o * _radius);
            if (_inner)
                _data.normals.push_back(-o);
            else
                _data.normals.push_back(o);
        }
    }

    _data.points.push_back(_center - n * _radius);
    if (_inner)
        _data.normals.push_back(n);
    else
        _data.normals.push_back(-n);

    uint prevIdx = 1U, idx = 1U;
    if (_inner)
    {
        for (uint i = 0U; i < cntLo - 1U; ++i)
        {
            _data.indexes.push_back(_idx + 0U);
            _data.indexes.push_back(_idx + idx);
            _data.indexes.push_back(_idx + idx + 1U);
            ++idx;
        }

        _data.indexes.push_back(_idx + 0U);
        _data.indexes.push_back(_idx + idx);
        _data.indexes.push_back(_idx + prevIdx);

        idx = 1U;
        for (uint r = 0U; r < cntLa - 1U; ++r)
        {
            prevIdx = idx;
            for (uint i = 0U; i < cntLo - 1U; ++i)
            {
                _data.indexes.push_back(_idx + idx);
                _data.indexes.push_back(_idx + idx + cntLo);
                _data.indexes.push_back(_idx + idx + cntLo + 1U);

                _data.indexes.push_back(_idx + idx);
                _data.indexes.push_back(_idx + idx + cntLo + 1U);
                _data.indexes.push_back(_idx + idx + 1U);

                ++idx;
            }

            _data.indexes.push_back(_idx + idx);
            _data.indexes.push_back(_idx + idx + cntLo);
            _data.indexes.push_back(_idx + prevIdx + cntLo);

            _data.indexes.push_back(_idx + idx);
            _data.indexes.push_back(_idx + prevIdx + cntLo);
            _data.indexes.push_back(_idx + prevIdx);

            ++idx;
        }

        prevIdx = idx;
        for (uint i = 0U; i < cntLo - 1U; ++i)
        {
            _data.indexes.push_back(_idx + last);
            _data.indexes.push_back(_idx + idx + 1U);
            _data.indexes.push_back(_idx + idx);

            ++idx;
        }

        _data.indexes.push_back(_idx + last);
        _data.indexes.push_back(_idx + prevIdx);
        _data.indexes.push_back(_idx + idx);
    }
    else
    {
        for (uint i = 0U; i < cntLo - 1U; ++i)
        {
            _data.indexes.push_back(_idx + 0U);
            _data.indexes.push_back(_idx + idx + 1U);
            _data.indexes.push_back(_idx + idx);
            ++idx;
        }

        _data.indexes.push_back(_idx + 0U);
        _data.indexes.push_back(_idx + prevIdx);
        _data.indexes.push_back(_idx + idx);

        idx = 1U;
        for (uint r = 0U; r < cntLa - 1U; ++r)
        {
            prevIdx = idx;
            for (uint i = 0U; i < cntLo - 1U; ++i)
            {
                _data.indexes.push_back(_idx + idx);
                _data.indexes.push_back(_idx + idx + cntLo + 1U);
                _data.indexes.push_back(_idx + idx + cntLo);

                _data.indexes.push_back(_idx + idx);
                _data.indexes.push_back(_idx + idx + 1U);
                _data.indexes.push_back(_idx + idx + cntLo + 1U);

                ++idx;
            }

            _data.indexes.push_back(_idx + idx);
            _data.indexes.push_back(_idx + prevIdx + cntLo);
            _data.indexes.push_back(_idx + idx + cntLo);

            _data.indexes.push_back(_idx + idx);
            _data.indexes.push_back(_idx + prevIdx);
            _data.indexes.push_back(_idx + prevIdx + cntLo);

            ++idx;
        }

        prevIdx = idx;
        for (uint i = 0U; i < cntLo - 1U; ++i)
        {
            _data.indexes.push_back(_idx + last);
            _data.indexes.push_back(_idx + idx);
            _data.indexes.push_back(_idx + idx + 1U);

            ++idx;
        }

        _data.indexes.push_back(_idx + last);
        _data.indexes.push_back(_idx + idx);
        _data.indexes.push_back(_idx + prevIdx);
    }
    _idx += cntLo * cntLa + 2UL;
}

Universe1::Video::DBItem3DSphere::DBItem3DSphere(const std::string &_footageName,

                                                 std::list<Item3D *> *_items)
    : DBItems3D("sphere", _footageName, _items)
{
}

Universe1::Video::Item3DSphere *Universe1::Video::DBItem3DSphere::add(const bool _inner,
                                                                      const QVector3D &_center,
                                                                      const float _radius,
                                                                      const uint _quality,
                                                                      const bool _visible,
                                                                      const Material &_material)
{
    Item3DSphere *result = new Item3DSphere(_inner, _center, _radius, _quality, _visible, _material, nextName());
    items->push_back(result);
    return result;
}
