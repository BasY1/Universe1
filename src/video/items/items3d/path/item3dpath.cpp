#include "item3dpath.h"

Universe1::Video::Item3DPath::Item3DPath(const std::vector<QVector3D> &_path,
                                         const float _lineRadius,
                                         const float _pointRadius,
                                         const uint _quality,
                                         const bool _showLine,
                                         const bool _showPoint,
                                         const bool _visible,
                                         const Material &_materialLine,
                                         const Material &_materialPoint,
                                         const std::string &_name)
    : Item3D(_visible, _name)
    , lineRadius(_lineRadius, _name + ".lineRadius")
    , pointRadius(_pointRadius, _name + ".pointRadius")
    , materialLine(_materialLine, _name + ".materialLine", props, materials)
    , materialPoint(_materialPoint, _name + ".materialPoint", props, materials)
    , quality(_quality, _name + ".quality")
    , showLine(_showLine, _name + ".showLine")
    , showPoint(_showPoint, _name + ".showPoint")
{
    props.push_back(&lineRadius);
    props.push_back(&pointRadius);
    props.push_back(&quality);
    props.push_back(&showLine);
    props.push_back(&showPoint);

    if (_path.empty())
        std::cerr << "Error[" << name << "]: Empty path collection !" << std::endl;

    points.reserve(_path.size());
    for (size_t i = 0UL; i < _path.size(); ++i)
        points.push_back(DynamicVec3(_path[i], _name + ".point[" + std::to_string(i) + "]"));
}

void Universe1::Video::Item3DPath::addData3D(std::list<Data3D> &_out,
                                             const Shader *,  // _shader,
                                             const uint64_t _timeStep) const
{
    const bool sl = showLine.getValue(_timeStep);
    const bool sp = showPoint.getValue(_timeStep);
    const float lr = lineRadius.getValue(_timeStep);

    if (points.size() < 2U || (!sl && !sp) || qFuzzyIsNull(lr) || lr < 0.0f)
        return;

    std::vector<QVector3D> path;
    path.reserve(points.size());
    for (const DynamicVec3 &p : points)
        path.push_back(p.getValue(_timeStep));

    const uint q = quality.getValue(_timeStep);

    if (sp)
        buildDataPoints(_out, path, lr, pointRadius.getValue(_timeStep), q, materialPoint.getValue(_timeStep));

    if (sl)
        buildDataPath(_out, path, lr, q, materialLine.getValue(_timeStep));
}

void Universe1::Video::Item3DPath::buildDataPath(std::list<Data3D> &_out,
                                                 const std::vector<QVector3D> &_path,
                                                 const float _radius,
                                                 const uint _quality,
                                                 const Material &_material)
{
    if (_path.size() < 2U || qFuzzyIsNull(_radius) || _radius < 0.0f)
        return;

    const uint last = _path.size() - 1UL;
    const uint cntCircle = circlePointCount(_quality);
    const uint cntPoint = cntCircle * _path.size();
    const uint cntIndex = cntCircle * last * 6U;

    _out.push_back({_material, cntPoint, cntIndex});
    Data3D &data = _out.back();

    for (uint i = 0U; i < _path.size(); ++i)
    {
        QVector3D n;
        if (i == 0U)
            n = (_path[1] - _path[0]).normalized();
        else if (i == last)
            n = (_path[i] - _path[i - 1U]).normalized();
        else
            n = ((_path[i] - _path[i - 1U]).normalized() + (_path[i + 1U] - _path[i]).normalized()).normalized();

        const QQuaternion rot = QQuaternion::fromAxisAndAngle(n, 360.0f / static_cast<float>(cntCircle));
        QVector3D a = perpendicularNormal(n);
        for (uint j = 0U; j < cntCircle; ++j, a = rot.rotatedVector(a).normalized())
        {
            data.points.push_back(_path[i] + a * _radius);
            data.normals.push_back(a);
        }
    }

    uint idx = 0U;
    for (size_t i = 0UL; i < last; ++i)
    {
        for (size_t j = 0UL; j < cntCircle - 1UL; ++j)
        {
            data.indexes.push_back(idx + j);
            data.indexes.push_back(idx + j + cntCircle);
            data.indexes.push_back(idx + j + cntCircle + 1U);

            data.indexes.push_back(idx + j);
            data.indexes.push_back(idx + j + cntCircle + 1U);
            data.indexes.push_back(idx + j + 1UL);
        }

        data.indexes.push_back(idx + cntCircle - 1UL);
        data.indexes.push_back(idx + 2UL * cntCircle - 1UL);
        data.indexes.push_back(idx + cntCircle);

        data.indexes.push_back(idx + cntCircle - 1UL);
        data.indexes.push_back(idx + cntCircle);
        data.indexes.push_back(idx);
        idx += cntCircle;
    }
}

void Universe1::Video::Item3DPath::buildDataPoints(std::list<Data3D> &_out,
                                                   const std::vector<QVector3D> &_path,
                                                   const float _lineRadius,
                                                   const float _pointRadius,
                                                   const uint _quality,
                                                   const Material &_material)
{
    if (_path.size() < 2U || qFuzzyIsNull(_lineRadius) || qFuzzyIsNull(_pointRadius) || _lineRadius < 0.0f ||
        _pointRadius < 0.0f)
        return;

    const uint last = _path.size() - 1U;
    for (uint i = 0U; i < _path.size(); ++i)
    {
        QVector3D n;
        if (i == 0U)
            n = (_path[1] - _path[0]).normalized();
        else if (i == last)
            n = (_path[i] - _path[i - 1U]).normalized();
        else
            n = ((_path[i] - _path[i - 1U]).normalized() + (_path[i + 1U] - _path[i]).normalized()).normalized();

        QVector3D a = perpendicularNormal(n);
        QVector3D b = QVector3D::crossProduct(n, a).normalized();
        a *= _pointRadius;
        b *= _pointRadius;
        Item3DLineSegment::buildData(_out, _path[i] - a, _path[i] + a, _lineRadius, _quality, _material);
        Item3DLineSegment::buildData(_out, _path[i] - b, _path[i] + b, _lineRadius, _quality, _material);
    }
}

void Universe1::Video::Item3DPath::buildData(std::list<Data3D> &_out,
                                             const std::vector<QVector3D> &_path,
                                             const float _lineRadius,
                                             const float _pointRadius,
                                             const uint _quality,
                                             const bool _showLine,
                                             const bool _showPoint,
                                             const Material &_materialLine,
                                             const Material &_materialPoint)
{
    if (_path.size() < 2U || (!_showLine && !_showPoint))
        return;

    if (_showPoint)
        buildDataPoints(_out, _path, _lineRadius, _pointRadius, _quality, _materialPoint);

    if (_showLine)
        buildDataPath(_out, _path, _lineRadius, _quality, _materialLine);
}

Universe1::Video::DBItem3DPath::DBItem3DPath(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("path", _footageName, _items)
{
}

Universe1::Video::Item3DPath *Universe1::Video::DBItem3DPath::add(const std::vector<QVector3D> &_path,
                                                                  const float _lineRadius,
                                                                  const float _pointRadius,
                                                                  const uint _quality,
                                                                  const bool _showLine,
                                                                  const bool _showPoint,
                                                                  const bool _visible,
                                                                  const Material &_materialLine,
                                                                  const Material &_materialPoint)
{
    Item3DPath *result = new Item3DPath(_path,
                                        _lineRadius,
                                        _pointRadius,
                                        _quality,
                                        _showLine,
                                        _showPoint,
                                        _visible,
                                        _materialLine,
                                        _materialPoint,
                                        nextName());
    items->push_back(result);
    return result;
}
