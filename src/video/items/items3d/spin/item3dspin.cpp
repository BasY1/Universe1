#include "item3dspin.h"

Universe1::Video::Item3DSpin::Item3DSpin(const uint8_t _showFlags,
                                         const QVector3D &_center,
                                         const QVector3D &_normal,
                                         const QVector3D &_arm,
                                         const float _phaseDeg,
                                         const float _lengthVector,
                                         const float _radiusSphere,
                                         const float _radiusVector,
                                         const float _radiusLineAxis,
                                         const float _radiusLineSphere,
                                         const float _radiusDots,
                                         const float _twistStep,
                                         const float _arrowDirOffset,
                                         const float _arrowArmOffset,
                                         const float _arrowLength,
                                         const float _arrowRadius,
                                         const uint _arrowCount,
                                         const uint _dotsCount,
                                         const uint _multAxis,
                                         const uint _qualityLatLong,
                                         const uint _qualitySphere,
                                         const uint _qualityLine,
                                         const QString &_text,
                                         const TextPosition _textPosition,
                                         const float _textSize,
                                         const Qt::Alignment _textAlign,
                                         const bool _visible,
                                         const std::vector<Material> &_materials,
                                         const std::string &_name)
    : Item3D(_visible, _name)
    , showVector((_showFlags & _SPIN_VECTOR) != 0U, _name + ".showVector")
    , showAxis((_showFlags & _SPIN_AXIS) != 0U, _name + ".showAxis")
    , showArrows((_showFlags & _SPIN_ARROWS) != 0U, _name + ".showArrows")
    , showDots((_showFlags & _SPIN_DOTS) != 0U, _name + ".showDots")
    , showSphere((_showFlags & _SPIN_SPHERE) != 0U, _name + ".showSphere")
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")
    , phaseDeg(_phaseDeg, _name + ".phaseDeg")
    , lengthVector(_lengthVector, _name + ".lengthVector")
    , radiusSphere(_radiusSphere, _name + ".radiusSphere")
    , radiusVector(_radiusVector, _name + ".radiusVector")
    , radiusLineAxis(_radiusLineAxis, _name + ".radiusLineAxis")
    , radiusLineSphere(_radiusLineSphere, _name + ".radiusLineSphere")
    , radiusDots(_radiusDots, _name + ".radiusDots")
    , twistStep(_twistStep, _name + ".twistStep")
    , arrowDirOffset(_arrowDirOffset, _name + ".arrowDirOffset")
    , arrowArmOffset(_arrowArmOffset, _name + ".arrowArmOffset")
    , arrowLength(_arrowLength, _name + ".arrowLength")
    , arrowRadius(_arrowRadius, _name + ".arrowRadius")
    , arrowCount(_arrowCount, _name + ".arrowCount")
    , dotsCount(_dotsCount, _name + ".dotsCount")
    , multAxis(_multAxis, _name + ".multAxis")
    , qualityLatLong(_qualityLatLong, _name + ".qualityLatLong")
    , qualitySphere(_qualitySphere, _name + ".qualitySphere")
    , qualityLine(_qualityLine, _name + ".qualityLine")
    , text(_text, _textSize, _textAlign, _textPosition, (_showFlags & _SPIN_TEXT) != 0U, _name, props)
{
    props.push_back(&showVector);
    props.push_back(&showAxis);
    props.push_back(&showArrows);
    props.push_back(&showDots);
    props.push_back(&showSphere);
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&phaseDeg);
    props.push_back(&lengthVector);
    props.push_back(&radiusSphere);
    props.push_back(&radiusVector);
    props.push_back(&radiusLineAxis);
    props.push_back(&radiusLineSphere);
    props.push_back(&radiusDots);
    props.push_back(&twistStep);
    props.push_back(&arrowDirOffset);
    props.push_back(&arrowArmOffset);
    props.push_back(&arrowLength);
    props.push_back(&arrowRadius);
    props.push_back(&arrowCount);
    props.push_back(&dotsCount);
    props.push_back(&multAxis);
    props.push_back(&qualityLatLong);
    props.push_back(&qualitySphere);
    props.push_back(&qualityLine);

    if (_materials.empty())
        std::cerr << "Error[" << name << "]: Empty material collection !" << std::endl;

    spinMaterials.reserve(_materials.size());
    uint idx = 0U;
    for (const Material &mat : _materials)
        spinMaterials.push_back(
            DynamicMaterialGroup(mat, _name + ".material[" + std::to_string(idx) + "]", props, materials));
}

void Universe1::Video::Item3DSpin::addData3D(std::list<Data3D> &_out,
                                             const Shader *_shader,
                                             const uint64_t _timeStep) const
{
    std::vector<Material> curMat;
    curMat.reserve(materials.size());
    for (const DynamicMaterialGroup &mat : spinMaterials)
        curMat.push_back(mat.getValue(_timeStep));
    buildData(_out,
              _shader,
              showVector.getValue(_timeStep),
              showAxis.getValue(_timeStep),
              showArrows.getValue(_timeStep),
              showDots.getValue(_timeStep),
              showSphere.getValue(_timeStep),
              text.show.getValue(_timeStep),
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              phaseDeg.getValue(_timeStep),
              lengthVector.getValue(_timeStep),
              radiusSphere.getValue(_timeStep),
              radiusVector.getValue(_timeStep),
              radiusLineAxis.getValue(_timeStep),
              radiusLineSphere.getValue(_timeStep),
              radiusDots.getValue(_timeStep),
              twistStep.getValue(_timeStep),
              arrowDirOffset.getValue(_timeStep),
              arrowArmOffset.getValue(_timeStep),
              arrowLength.getValue(_timeStep),
              arrowRadius.getValue(_timeStep),
              arrowCount.getValue(_timeStep),
              dotsCount.getValue(_timeStep),
              multAxis.getValue(_timeStep),
              qualityLatLong.getValue(_timeStep),
              qualitySphere.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              text.text.getValue(_timeStep),
              text.position.getValue(_timeStep),
              text.sizeMult.getValue(_timeStep),
              text.align.getValue(_timeStep),
              curMat);
}

void Universe1::Video::Item3DSpin::buildData(std::list<Data3D> &_out,
                                             const Shader *_shader,
                                             const bool _showVector,
                                             const bool _showAxis,
                                             const bool _showArrows,
                                             const bool _showDots,
                                             const bool _showSphere,
                                             const bool _showText,
                                             const QVector3D &_center,
                                             const QVector3D &_normal,
                                             const QVector3D &_arm,
                                             const float _phaseDeg,
                                             const float _lengthVector,
                                             const float _radiusSphere,
                                             const float _radiusVector,
                                             const float _radiusLineAxis,
                                             const float _radiusLineSphere,
                                             const float _radiusDots,
                                             const float _twistStep,
                                             const float _arrowDirOffset,
                                             const float _arrowArmOffset,
                                             const float _arrowLength,
                                             const float _arrowRadius,
                                             const uint _arrowCount,
                                             const uint _dotsCount,
                                             const uint _multAxis,
                                             const uint _qualityLatLong,
                                             const uint _qualitySphere,
                                             const uint _qualityLine,
                                             const QString &_text,
                                             const TextPosition _textPosition,
                                             const float _textSize,
                                             const Qt::Alignment _textAlign,
                                             const std::vector<Material> &_materials)
{
    if (_materials.empty())
        return;

    const QVector3D n = _normal.normalized();
    const QVector3D a =
        QQuaternion::fromAxisAndAngle(n, _phaseDeg).rotatedVector(perpendicularArm(_arm, n)).normalized();

    if (_showSphere)
    {
        Item3DWireSphereSlice::buildMultiColor(_out,
                                               _center,
                                               n,
                                               a,
                                               _radiusSphere,
                                               _radiusLineSphere,
                                               _qualityLatLong,
                                               _qualitySphere,
                                               _qualityLine,
                                               _materials);
    }

    if (_showDots && _dotsCount > 0U && !qFuzzyIsNull(_radiusSphere) && !qFuzzyIsNull(_radiusDots) &&
        _radiusSphere > 0.0f && _radiusDots > 0.0f)
    {
        const uint steps = _dotsCount * _materials.size();
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(n, 360.0f / static_cast<float>(steps));
        QVector3D aa = a;
        for (uint i = 0U; i < steps; ++i, aa = rot.rotatedVector(aa).normalized())
            Item3DSphere::buildData(
                _out, _center + aa * _radiusSphere, _radiusDots, _qualitySphere, _materials[i % _materials.size()]);
    }

    if (_showArrows && _arrowCount > 0U && !qFuzzyIsNull(_radiusSphere) && !qFuzzyIsNull(_arrowArmOffset) &&
        !qFuzzyIsNull(_arrowLength) && !qFuzzyIsNull(_arrowRadius) && _radiusSphere > 0.0f && _arrowArmOffset > 0.0f &&
        _arrowLength > 0.0f && _arrowRadius > 0.0f)
    {
        const uint steps = _arrowCount * _materials.size();
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(n, 360.0f / static_cast<float>(steps));
        QVector3D aa = a;
        for (uint i = 0U; i < steps; ++i, aa = rot.rotatedVector(aa).normalized())
            Item3DArcArrow::buildData(_out,
                                      _center + n * (_lengthVector + _arrowDirOffset),
                                      n,
                                      aa,
                                      _arrowArmOffset,
                                      _arrowLength,
                                      _arrowRadius,
                                      _qualitySphere,
                                      _materials[i % _materials.size()]);
    }

    if (_showAxis && !qFuzzyIsNull(_radiusLineAxis) && _radiusLineAxis > 0.0f)
    {
        const QVector3D p2 = _center - n * (_radiusSphere * 1.1f);
        QVector3D p1 = _center;
        if (!_showVector)
            p1 += n * (_radiusSphere * 1.1f);
        Item3DLineDashSegment::buildMultiColor(
            _out, p1, p2, _radiusLineAxis, _multAxis, _multAxis, 1U, _qualityLine, _materials);
    }

    if (_showVector && !qFuzzyIsNull(_radiusVector) && !qFuzzyIsNull(_lengthVector) && _radiusVector > 0.0f &&
        _lengthVector > 0.0f)
        Item3DLineTwist::buildData(
            _out, _center, n, a, _lengthVector, _twistStep, _radiusVector, _qualityLine, _materials);

    if (_shader != nullptr && _showText && !_text.isEmpty())
    {
        switch (_textPosition)
        {
        case _TextAtPointFrom:
            Item3DText::buildData(_out,
                                  _shader,
                                  _text,
                                  _textSize,
                                  _textAlign,
                                  _center + QVector3D(0, 0, 1) * _arrowLength,
                                  _materials[0]);
            break;
        case _TextMiddle:
            Item3DText::buildData(_out,
                                  _shader,
                                  _text,
                                  _textSize,
                                  _textAlign,
                                  _center + n * _lengthVector * 0.5f + QVector3D(0, 0, 1) * _arrowLength,
                                  _materials[0]);
            break;
        case _TextAtPointTo:
            Item3DText::buildData(_out,
                                  _shader,
                                  _text,
                                  _textSize,
                                  _textAlign,
                                  _center + n * _lengthVector + QVector3D(0, 0, 1) * _arrowLength,
                                  _materials[0]);
            break;
        }
    }
}

Universe1::Video::DBItem3DSpin::DBItem3DSpin(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("spin", _footageName, _items)
{
}

Universe1::Video::Item3DSpin *Universe1::Video::DBItem3DSpin::add(const uint8_t _showFlags,
                                                                  const QVector3D &_center,
                                                                  const QVector3D &_normal,
                                                                  const QVector3D &_arm,
                                                                  const float _phaseDeg,
                                                                  const float _lengthVector,
                                                                  const float _radiusSphere,
                                                                  const float _radiusVector,
                                                                  const float _radiusLineAxis,
                                                                  const float _radiusLineSphere,
                                                                  const float _radiusDots,
                                                                  const float _twistStep,
                                                                  const float _arrowDirOffset,
                                                                  const float _arrowArmOffset,
                                                                  const float _arrowLength,
                                                                  const float _arrowRadius,
                                                                  const uint _arrowCount,
                                                                  const uint _dotsCount,
                                                                  const uint _multAxis,
                                                                  const uint _qualityLatLong,
                                                                  const uint _qualitySphere,
                                                                  const uint _qualityLine,
                                                                  const QString &_text,
                                                                  const TextPosition _textPosition,
                                                                  const float _textSize,
                                                                  const Qt::Alignment _textAlign,
                                                                  const bool _visible,
                                                                  const std::vector<Material> &_materials)
{
    Item3DSpin *result = new Item3DSpin(_showFlags,
                                        _center,
                                        _normal,
                                        _arm,
                                        _phaseDeg,
                                        _lengthVector,
                                        _radiusSphere,
                                        _radiusVector,
                                        _radiusLineAxis,
                                        _radiusLineSphere,
                                        _radiusDots,
                                        _twistStep,
                                        _arrowDirOffset,
                                        _arrowArmOffset,
                                        _arrowLength,
                                        _arrowRadius,
                                        _arrowCount,
                                        _dotsCount,
                                        _multAxis,
                                        _qualityLatLong,
                                        _qualitySphere,
                                        _qualityLine,
                                        _text,
                                        _textPosition,
                                        _textSize,
                                        _textAlign,
                                        _visible,
                                        _materials,
                                        nextName());
    items->push_back(result);
    return result;
}

