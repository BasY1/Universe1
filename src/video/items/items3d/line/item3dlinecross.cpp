#include "item3dlinecross.h"

Universe1::Video::Item3DLineCross::Item3DLineCross(const QVector3D &_center,
                                                   const QVector3D &_normal,
                                                   const QVector3D &_arm,
                                                   const CrossType _type,
                                                   const float _radius,
                                                   const float _radiusLine,
                                                   const uint _quality,
                                                   const bool _showText,
                                                   const QString &_text,
                                                   const float _textSize,
                                                   const Qt::Alignment _textAlign,
                                                   const bool _visible,
                                                   const Material &_material,
                                                   const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , center(_center, _name + ".center")
    , normal(_normal, _name + ".normal")
    , arm(_arm, _name + ".arm")
    , type(_type, _name + ".type")
    , radius(_radius, _name + ".radius")
    , radiusLine(_radiusLine, _name + ".radiusLine")
    , quality(_quality, _name + ".quality")
    , showText(_showText, _name + ".showText")
    , text(_text, _textSize, _textAlign, _name, props)
{
    props.push_back(&center);
    props.push_back(&normal);
    props.push_back(&arm);
    props.push_back(&type);
    props.push_back(&radius);
    props.push_back(&radiusLine);
    props.push_back(&quality);
    props.push_back(&showText);
}

void Universe1::Video::Item3DLineCross::addData3D(std::list<Data3D> &_out,
                                                  const Shader *_shader,
                                                  const uint64_t _timeStep) const
{
    buildData(_out,
              _shader,
              center.getValue(_timeStep),
              normal.getValue(_timeStep),
              arm.getValue(_timeStep),
              type.getValue(_timeStep),
              radius.getValue(_timeStep),
              radiusLine.getValue(_timeStep),
              quality.getValue(_timeStep),
              showText.getValue(_timeStep),
              text.text.getValue(_timeStep),
              text.sizeMult.getValue(_timeStep),
              text.align.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineCross::buildData(std::list<Data3D> &_out,
                                                  const Shader *_shader,
                                                  const QVector3D &_center,
                                                  const QVector3D &_normal,
                                                  const QVector3D &_arm,
                                                  const CrossType _type,
                                                  const float _radius,
                                                  const float _radiusLine,
                                                  const uint _quality,
                                                  const bool _showText,
                                                  const QString &_text,
                                                  const float _textSize,
                                                  const Qt::Alignment _textAlign,
                                                  const Material &_material)
{
    const QVector3D n = _normal.normalized();
    const QVector3D a = perpendicularArm(_arm, n);
    const QVector3D b = QVector3D::crossProduct(n, a).normalized();

    QVector3D t;
    switch (_type)
    {
    case _Axis:
        Item3DLineSegment::buildData(
            _out, _center - n * _radius, _center + n * _radius, _radiusLine, _quality, _material);
        Item3DLineSegment::buildData(
            _out, _center - a * _radius, _center + a * _radius, _radiusLine, _quality, _material);
        Item3DLineSegment::buildData(
            _out, _center - b * _radius, _center + b * _radius, _radiusLine, _quality, _material);
        break;

    case _Planes:
        t = (n + a).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (n - a).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (n + b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (n - b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (a + b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (a - b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        break;

    case _Diagonals:
        t = (n + a + b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (n + a - b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (n - a + b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        t = (n - a - b).normalized() * _radius;
        Item3DLineSegment::buildData(_out, _center - t, _center + t, _radiusLine, _quality, _material);
        break;
    }

    if (_showText)
    {
        if (_text.contains("$CENTER$"))
        {
            QString tmp = _text;
            tmp.replace("$CENTER$", QString("%1 x %2 x %3").arg(_center.x(), 0, 'f', 3));
            Item3DText::buildData(
                _out, _shader, tmp, _textSize, _textAlign, _center + QVector3D(0, 0, _radius * 2.0), _material);
        }
        else
        {
            Item3DText::buildData(
                _out, _shader, _text, _textSize, _textAlign, _center + QVector3D(0, 0, _radius * 2.0), _material);
        }
    }
}

Universe1::Video::DBItem3DLineCross::DBItem3DLineCross(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineCross", _footageName, _items)
{
}

Universe1::Video::Item3DLineCross *Universe1::Video::DBItem3DLineCross::add(const QVector3D &_center,
                                                                            const QVector3D &_normal,
                                                                            const QVector3D &_arm,
                                                                            const Item3DLineCross::CrossType _type,
                                                                            const float _radius,
                                                                            const float _radiusLine,
                                                                            const uint _quality,
                                                                            const bool _showText,
                                                                            const QString &_text,
                                                                            const float _textSize,
                                                                            const Qt::Alignment _textAlign,
                                                                            const bool _visible,
                                                                            const Material &_material)
{
    Item3DLineCross *result = new Item3DLineCross(_center,
                                                  _normal,
                                                  _arm,
                                                  _type,
                                                  _radius,
                                                  _radiusLine,
                                                  _quality,
                                                  _showText,
                                                  _text,
                                                  _textSize,
                                                  _textAlign,
                                                  _visible,
                                                  _material,
                                                  nextName());
    items->push_back(result);
    return result;
}
