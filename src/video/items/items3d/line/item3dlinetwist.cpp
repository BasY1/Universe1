#include "item3dlinetwist.h"

Universe1::Video::Item3DLineTwist::Item3DLineTwist(const QVector3D &_point,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
                                                   const float _length,
                                                   const float _twistStep,
                                                   const float _radius,
                                                   const uint _quality,
                                                   const bool _visible,
                                                   const std::vector<Material> &_materials,
                                                   const std::string &_name)
    : Item3D(_visible, _name)
    , point(_point, _name + ".point")
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")
    , length(_length, _name + ".length")
    , twistStep(_twistStep, _name + ".twistStep")
    , radius(_radius, _name + ".radius")
    , quality(_quality, _name + ".quality")
{
    props.push_back(&point);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&length);
    props.push_back(&twistStep);
    props.push_back(&radius);
    props.push_back(&quality);

    if (_materials.empty())
        std::cerr << "[" << name << "]: Empty material collection !" << std::endl;

    materialProps.reserve(_materials.size());
    uint idx = 0U;
    for (const Material &mat : _materials)
        materialProps.push_back(
            DynamicMaterialGroup(mat, _name + ".material[" + std::to_string(idx) + "]", props, materials));
}

void Universe1::Video::Item3DLineTwist::addData3D(std::list<Data3D> &_out,
                                                  const Shader *,  // _shader,
                                                  const uint64_t _timeStep) const
{

    std::vector<Material> curMat;
    curMat.reserve(materials.size());
    for (const DynamicMaterialGroup &mat : materialProps)
        curMat.push_back(mat.getValue(_timeStep));
    buildData(_out,
              point.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              length.getValue(_timeStep),
              twistStep.getValue(_timeStep),
              radius.getValue(_timeStep),
              quality.getValue(_timeStep),
              curMat);
}

void Universe1::Video::Item3DLineTwist::buildData(std::list<Data3D> &_out,
                                                  const QVector3D &_point,
                                                  const QVector3D &_normal,
                                                  const QVector3D &_arm,
                                                  const float _length,
                                                  const float _twistStep,
                                                  const float _radius,
                                                  const uint _quality,
                                                  const std::vector<Material> &_materials)
{
    if (qFuzzyIsNull(_length))
        return;

    if (_materials.empty())
        return;

    if (_materials.size() == 1U)
    {
        Item3DLine::buildData(_out, _point, _normal, _length, _radius, _quality, _materials.front());
        return;
    }

    const uint cntCircle = circlePointCount(_quality);
    uint usedCnt = _materials.size();
    while (usedCnt < cntCircle)
        usedCnt *= 2U;

    const uint usedCntSingle = 1U + usedCnt / _materials.size();
    const float twistStep = std::min(_length, _twistStep);
    const float twistStepSingle = twistStep / static_cast<float>(usedCnt);

    const uint cntPathSteps = static_cast<uint>(_length / twistStepSingle);
    const bool isAdd = !qFuzzyCompare(twistStepSingle * static_cast<float>(cntPathSteps), _length);
    const float lastAngle =
        isAdd ? (360.0f * ((_length - (static_cast<float>(usedCnt) * twistStep)) / twistStep)) : 0.0f;

    const uint usedPathSteps = cntPathSteps + (isAdd ? 1U : 0U);
    const uint cntPoints = (usedPathSteps + 1U) * usedCntSingle;
    const uint cntIndexes = usedPathSteps * (usedCntSingle - 1U) * 6U;

    // const QVector3D n = (_point2 - _point1) / len;
    const QVector3D n = _normal.normalized();
    const QVector3D a = QVector3D::crossProduct(QVector3D::crossProduct(n, _arm).normalized(), n).normalized();

    const float angleMat = 360.0f / static_cast<float>(_materials.size());
    const float angleStep = 360.0f / static_cast<float>(usedCnt);

    float angleStart = 0.0f;
    for (const Material &mat : _materials)
    {
        Item3DPlaneCircleSlice::buildData(_out,
                                          _point,
                                          -n,
                                          QQuaternion::fromAxisAndAngle(n, angleStart).rotatedVector(a).normalized(),
                                          _radius,
                                          -angleMat,
                                          _quality,
                                          mat);

        Item3DPlaneCircleSlice::buildData(
            _out,
            _point + n * _length,
            n,
            QQuaternion::fromAxisAndAngle(n, angleStart + lastAngle).rotatedVector(a).normalized(),
            _radius,
            angleMat,
            _quality,
            mat);

        _out.push_back({mat, cntPoints, cntIndexes});
        Data3D &data = _out.back();

        for (uint i = 0U; i <= cntPathSteps; i++)
        {
            const float angleStartStep = angleStart + (static_cast<float>(i) * angleStep);
            const QVector3D p = _point + n * (static_cast<float>(i) * twistStepSingle);
            for (uint j = 0U; j < usedCntSingle; j++)
            {
                const float angle = angleStartStep + (static_cast<float>(j) * angleStep);
                const QVector3D aa = QQuaternion::fromAxisAndAngle(n, angle).rotatedVector(a).normalized();
                data.points.push_back(p + aa * _radius);
                data.normals.push_back(aa);
            }
        }

        if (isAdd)
        {
            const float angleStartStep = angleStart + lastAngle;
            const QVector3D p = _point + n * _length;
            for (uint j = 0U; j < usedCntSingle; j++)
            {
                const float angle = angleStartStep + (static_cast<float>(j) * angleStep);
                const QVector3D aa = QQuaternion::fromAxisAndAngle(n, angle).rotatedVector(a).normalized();
                data.points.push_back(p + aa * _radius);
                data.normals.push_back(aa);
            }
        }

        uint idx = 0U;
        for (uint la = 0U; la < usedPathSteps; ++la)
        {
            const uint laa = idx + la * usedCntSingle;
            for (uint lo = 0U; lo < usedCntSingle - 1U; ++lo)
            {
                data.indexes.push_back(laa + lo);
                data.indexes.push_back(laa + usedCntSingle + lo + 1U);
                data.indexes.push_back(laa + lo + 1U);

                data.indexes.push_back(laa + lo);
                data.indexes.push_back(laa + usedCntSingle + lo);
                data.indexes.push_back(laa + usedCntSingle + lo + 1U);
            }
        }

        angleStart += angleMat;
    }
}

Universe1::Video::DBItem3DLineTwist::DBItem3DLineTwist(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineTwist", _footageName, _items)
{
}

Universe1::Video::Item3DLineTwist *Universe1::Video::DBItem3DLineTwist::add(const QVector3D &_point,
                                                                            const QVector3D &_normal,
                                                                            const QVector3D &_arm,
                                                                            const float _length,
                                                                            const float _twistStep,
                                                                            const float _radius,
                                                                            const uint _quality,
                                                                            const bool _visible,
                                                                            const std::vector<Material> &_materials)
{
    Item3DLineTwist *result = new Item3DLineTwist(
        _point, _normal, _arm, _length, _twistStep, _radius, _quality, _visible, _materials, nextName());
    items->push_back(result);
    return result;
}
