#include "item3dangledim.h"

Universe1::Video::Item3DAngleDim::Item3DAngleDim(const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_normalFrom,
                                                 const QVector3D &_normalTo,
                                                 const float _radius,
                                                 const float _lineRadius,
                                                 const float _arrowLength,
                                                 const float _arrowRadius,
                                                 const bool _showArrowFrom,
                                                 const bool _showArrowTo,
                                                 const bool _showText,
                                                 const QString &_text,
                                                 const Item3DLineArrow::TextPosition _textPosition,
                                                 const float _textSize,
                                                 const Qt::Alignment _textAlign,
                                                 const uint _qualityAngle,
                                                 const uint _qualityLine,
                                                 const bool _visible,
                                                 const Material &_material,
                                                 const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , normalFrom(_normalFrom, _name + ".normalFrom")
    , normalTo(_normalTo, _name + ".normalTo")
    , radius(_radius, _name + ".radius")
    , lineRadius(_lineRadius, _name + ".lineRadius")
    , arrowLength(_arrowLength, _name + ".arrowLength")
    , arrowRadius(_arrowRadius, _name + ".arrowRadius")
    , showArrowFrom(_showArrowFrom, _name + ".showArrowFrom")
    , showArrowTo(_showArrowTo, _name + ".showArrowTo")
    , showText(_showText, _name + ".showText")
    , textPosition(_textPosition, _name + ".textPosition")
    , text(_text, _textSize, _textAlign, _name, props)
    , qualityAngle(_qualityAngle, _name + ".qualityAngle")
    , qualityLine(_qualityLine, _name + ".qualityLine")
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&normalFrom);
    props.push_back(&normalTo);
    props.push_back(&radius);
    props.push_back(&lineRadius);
    props.push_back(&arrowLength);
    props.push_back(&arrowRadius);
    props.push_back(&showArrowFrom);
    props.push_back(&showArrowTo);
    props.push_back(&showText);
    props.push_back(&textPosition);
    props.push_back(&qualityAngle);
    props.push_back(&qualityLine);
}

void Universe1::Video::Item3DAngleDim::addData3D(std::list<Data3D> &_out,
                                                 const Shader *_shader,
                                                 const uint64_t _timeStep) const
{
    buildData(_out,
              _shader,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              normalFrom.getValue(_timeStep),
              normalTo.getValue(_timeStep),
              radius.getValue(_timeStep),
              lineRadius.getValue(_timeStep),
              arrowLength.getValue(_timeStep),
              arrowRadius.getValue(_timeStep),
              showArrowFrom.getValue(_timeStep),
              showArrowTo.getValue(_timeStep),
              showText.getValue(_timeStep),
              text.text.getValue(_timeStep),
              textPosition.getValue(_timeStep),
              text.sizeMult.getValue(_timeStep),
              text.align.getValue(_timeStep),
              qualityAngle.getValue(_timeStep),
              qualityLine.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DAngleDim::buildData(std::list<Data3D> &_out,
                                                 const Shader *_shader,
                                                 const QVector3D &_center,
                                                 const QVector3D &_normal,
                                                 const QVector3D &_normalFrom,
                                                 const QVector3D &_normalTo,
                                                 const float _radius,
                                                 const float _lineRadius,
                                                 const float _arrowLength,
                                                 const float _arrowRadius,
                                                 const bool _showArrowFrom,
                                                 const bool _showArrowTo,
                                                 const bool _showText,
                                                 const QString &_text,
                                                 const Item3DLineArrow::TextPosition _textPosition,
                                                 const float _textSize,
                                                 const Qt::Alignment _textAlign,
                                                 const uint _qualityAngle,
                                                 const uint _qualityLine,
                                                 const Material &_material)
{
    using namespace Math;
    const QVector3D n = _normal.normalized();
    const QVector3D n1 = _normalFrom.normalized();
    const QVector3D n2 = _normalTo.normalized();
    const float angleDeg = Vec3F(n1).angleNormDeg(Vec3F(n2), Vec3F(n));
    if (qFuzzyIsNull(angleDeg) || qFuzzyIsNull(_radius) || qFuzzyIsNull(_arrowLength) || qFuzzyIsNull(_arrowRadius) ||
        qFuzzyIsNull(_lineRadius) || _radius < 0.0f || _arrowLength < 0.0f || _arrowRadius < 0.0f || _lineRadius < 0.0f)
        return;

    const float arrowAngleDeg = toDeg<float>(_arrowLength / _radius);
    bool isOuter = false;
    if (_showArrowFrom && _showArrowTo)
    {
        if (arrowAngleDeg * 2.0f > 360)
            return;

        isOuter = arrowAngleDeg * 3.0f > angleDeg;
    }
    else if (_showArrowFrom || _showArrowTo)
    {
        if (arrowAngleDeg > 360)
            return;
        isOuter = arrowAngleDeg * 2.0f > angleDeg;
    }

    QVector3D ar = n1;
    float ad = angleDeg;
    if (!isOuter && _showArrowFrom)
    {
        ad -= arrowAngleDeg;
        ar = QQuaternion::fromAxisAndAngle(n, arrowAngleDeg).rotatedVector(n1).normalized();
    }
    if (!isOuter && _showArrowFrom)
        ad -= arrowAngleDeg;

    Item3DTorusArc::buildData(_out, _center, n, ar, ad, _radius, _lineRadius, _qualityAngle, _qualityLine, _material);

    if (_showArrowFrom)
    {
        if (isOuter)
        {
            const QVector3D nn = QQuaternion::fromAxisAndAngle(n, -arrowAngleDeg).rotatedVector(n1).normalized();
            Item3DArcArrow::buildData(
                _out, _center, n, nn, _radius, _arrowLength, _arrowRadius, _qualityLine, _material);
            Item3DTorusArc::buildData(
                _out, _center, -n, nn, arrowAngleDeg, _radius, _lineRadius, _qualityAngle, _qualityLine, _material);
        }
        else
        {
            Item3DArcArrow::buildData(_out,
                                      _center,
                                      -n,
                                      QQuaternion::fromAxisAndAngle(n, arrowAngleDeg).rotatedVector(n1).normalized(),
                                      _radius,
                                      _arrowLength,
                                      _arrowRadius,
                                      _qualityLine,
                                      _material);
        }
    }
    else
    {
        Item3DPlaneCircle::buildData(_out,
                                     _center + n1 * _radius,
                                     QVector3D::crossProduct(n1, n).normalized(),
                                     n,
                                     _lineRadius,
                                     _qualityLine,
                                     _material);
    }

    if (_showArrowTo)
    {
        if (isOuter)
        {
            const QVector3D nn = QQuaternion::fromAxisAndAngle(n, arrowAngleDeg).rotatedVector(n2).normalized();
            Item3DArcArrow::buildData(
                _out, _center, -n, nn, _radius, _arrowLength, _arrowRadius, _qualityLine, _material);
            Item3DTorusArc::buildData(
                _out, _center, n, nn, arrowAngleDeg, _radius, _lineRadius, _qualityAngle, _qualityLine, _material);
        }
        else
        {
            Item3DArcArrow::buildData(_out,
                                      _center,
                                      n,
                                      QQuaternion::fromAxisAndAngle(n, -arrowAngleDeg).rotatedVector(n2).normalized(),
                                      _radius,
                                      _arrowLength,
                                      _arrowRadius,
                                      _qualityLine,
                                      _material);
        }
    }
    else
    {
        Item3DPlaneCircle::buildData(_out,
                                     _center + n2 * _radius,
                                     QVector3D::crossProduct(n, n2).normalized(),
                                     n,
                                     _lineRadius,
                                     _qualityLine,
                                     _material);
    }

    if (!_showText || _shader == nullptr)
        return;

    const QString txt = _text.isEmpty() ? QString("%1°").arg(angleDeg, 0, 'f', 3) : _text;
    switch (_textPosition)
    {
    case Item3DLineArrow::_TextAtPointFrom:
        Item3DText::buildData(
            _out, _shader, txt, _textSize, _textAlign, _center + n1 * _radius + nz * _arrowLength, _material);
        break;
    case Item3DLineArrow::_TextMiddle:
        Item3DText::buildData(
            _out,
            _shader,
            txt,
            _textSize,
            _textAlign,
            _center + QQuaternion::fromAxisAndAngle(n, angleDeg * 0.5).rotatedVector(n1).normalized() * _radius +
                QVector3D(0, 0, 1) * _arrowLength,
            _material);
        break;
    case Item3DLineArrow::_TextAtPointTo:
        Item3DText::buildData(
            _out, _shader, txt, _textSize, _textAlign, _center + n2 * _radius + nz * _arrowLength, _material);
        break;
    }
}

Universe1::Video::DBItem3DAngleDim::DBItem3DAngleDim(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("angleDim", _footageName, _items)
{
}

Universe1::Video::Item3DAngleDim *
Universe1::Video::DBItem3DAngleDim::add(const QVector3D &_center,
                                        const QVector3D &_normal,
                                        const QVector3D &_normalFrom,
                                        const QVector3D &_normalTo,
                                        const float _radius,
                                        const float _lineRadius,
                                        const float _arrowLength,
                                        const float _arrowRadius,
                                        const bool _showArrowFrom,
                                        const bool _showArrowTo,
                                        const bool _showText,
                                        const QString &_text,
                                        const Item3DLineArrow::TextPosition _textPosition,
                                        const float _textSize,
                                        const Qt::Alignment _textAlign,
                                        const uint _qualityAngle,
                                        const uint _qualityLine,
                                        const bool _visible,
                                        const Material &_material)
{
    Item3DAngleDim *result = new Item3DAngleDim(_center,
                                                _normal,
                                                _normalFrom,
                                                _normalTo,
                                                _radius,
                                                _lineRadius,
                                                _arrowLength,
                                                _arrowRadius,
                                                _showArrowFrom,
                                                _showArrowTo,
                                                _showText,
                                                _text,
                                                _textPosition,
                                                _textSize,
                                                _textAlign,
                                                _qualityAngle,
                                                _qualityLine,
                                                _visible,
                                                _material,
                                                nextName());
    items->push_back(result);
    return result;
}
