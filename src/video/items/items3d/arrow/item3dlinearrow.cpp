#include "item3dlinearrow.h"

Universe1::Video::Item3DLineArrow::Item3DLineArrow(const QVector3D &_pointFrom,
                                                   const QVector3D &_pointTo,
                                                   const float _arrowLength,
                                                   const float _arrowRadius,
                                                   const float _lineRadius,
                                                   const uint _quality,
                                                   const QString &_text,
                                                   const TextPosition _textPosition,
                                                   const float _textSize,
                                                   const Qt::Alignment _textAlign,
                                                   const bool _showText,
                                                   const bool _visible,
                                                   const Material &_material,
                                                   const std::string &_name)
    : Item3DBase(_visible, _material, _name)
    , pointFrom(_pointFrom, _name + ".pointFrom")
    , pointTo(_pointTo, _name + ".pointTo")
    , arrowLength(_arrowLength, _name + ".arrowLength")
    , arrowRadius(_arrowRadius, _name + ".arrowRadius")
    , lineRadius(_lineRadius, _name + ".lineRadius")
    , quality(_quality, _name + ".quality")
    , text(_text, _textSize, _textAlign, _textPosition, _showText, _name, props)
{
    props.push_back(&pointFrom);
    props.push_back(&pointTo);
    props.push_back(&arrowLength);
    props.push_back(&arrowRadius);
    props.push_back(&lineRadius);
    props.push_back(&quality);
}

void Universe1::Video::Item3DLineArrow::addData3D(std::list<Data3D> &_out,
                                                  const Shader *_shader,
                                                  const uint64_t _timeStep) const
{
    buildData(_out,
              _shader,
              pointFrom.getValue(_timeStep),
              pointTo.getValue(_timeStep),
              arrowLength.getValue(_timeStep),
              arrowRadius.getValue(_timeStep),
              lineRadius.getValue(_timeStep),
              quality.getValue(_timeStep),
              text.text.getValue(_timeStep),
              text.position.getValue(_timeStep),
              text.sizeMult.getValue(_timeStep),
              text.align.getValue(_timeStep),
              text.show.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineArrow::buildText(std::list<Data3D> &_out,
                                                  const Shader *_shader,
                                                  const QVector3D &_pointFrom,
                                                  const QVector3D &_pointTo,
                                                  const float _offsetUp,
                                                  const QString &_text,
                                                  const TextPosition _textPosition,
                                                  const float _textSize,
                                                  const Qt::Alignment _textAlign,
                                                  const bool _showText,
                                                  const Material &_material)
{
    if (_shader != nullptr && _showText && !_text.isEmpty())
    {
        switch (_textPosition)
        {
        case _TextAtPointFrom:
            Item3DText::buildData(_out, _shader, _text, _textSize, _textAlign, _pointFrom + nz * _offsetUp, _material);
            break;
        case _TextMiddle:
            Item3DText::buildData(_out,
                                  _shader,
                                  _text,
                                  _textSize,
                                  _textAlign,
                                  (_pointFrom + _pointTo) * 0.5f + nz * _offsetUp,
                                  _material);
            break;
        case _TextAtPointTo:
            Item3DText::buildData(_out, _shader, _text, _textSize, _textAlign, _pointTo + nz * _offsetUp, _material);
            break;
        }
    }
}

void Universe1::Video::Item3DLineArrow::buildData(std::list<Data3D> &_out,
                                                  const Shader *_shader,
                                                  const QVector3D &_pointFrom,
                                                  const QVector3D &_pointTo,
                                                  const QVector3D &_arm,
                                                  const float _arrowLength,
                                                  const float _arrowRadius,
                                                  const float _lineRadius,
                                                  const uint _quality,
                                                  const QString &_text,
                                                  const TextPosition _textPosition,
                                                  const float _textSize,
                                                  const Qt::Alignment _textAlign,
                                                  const bool _showText,
                                                  const Material &_material)
{
    const float len = _pointFrom.distanceToPoint(_pointTo);
    if (qFuzzyIsNull(len))
        return;

    buildText(_out,
              _shader,
              _pointFrom,
              _pointTo,
              _arrowLength,
              _text,
              _textPosition,
              _textSize,
              _textAlign,
              _showText,
              _material);

    if (qFuzzyIsNull(_arrowLength) || qFuzzyIsNull(_arrowRadius) || _arrowLength < 0.0f || _arrowRadius < 0.0f)
    {
        Item3DLineSegment::buildData(_out, _pointFrom, _pointTo, _arm, _lineRadius, _quality, _material);
        return;
    }

    const QVector3D n = (_pointTo - _pointFrom).normalized();
    if (qFuzzyCompare(len, _arrowLength))
    {
        Item3DCone::buildData(_out, _pointFrom, _pointTo, _arm, _arrowRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, _pointFrom, -n, _arm, _arrowRadius, _quality, _material);
        return;
    }

    if (len < _arrowLength)
    {
        const float ar = _arrowRadius * len / _arrowLength;
        Item3DCone::buildData(_out, _pointFrom, _pointTo, _arm, ar, _quality, _material);
        Item3DPlaneCircle::buildData(_out, _pointFrom, -n, _arm, ar, _quality, _material);
        return;
    }

    const QVector3D p = _pointFrom + n * (len - _arrowLength);
    Item3DLineSegment::buildData(_out, _pointFrom, p, _arm, _lineRadius, _quality, _material);
    Item3DCone::buildData(_out, p, _pointTo, _arm, _arrowRadius, _quality, _material);
    Item3DPlaneCircle::buildData(_out, p, -n, _arm, _arrowRadius, _quality, _material);
}

//

Universe1::Video::Item3DLineDim::Item3DLineDim(const QVector3D &_pointFrom,
                                               const QVector3D &_pointTo,
                                               const float _arrowLength,
                                               const float _arrowRadius,
                                               const float _lineRadius,
                                               const uint _quality,
                                               const QString &_text,
                                               const TextPosition _textPosition,
                                               const float _textSize,
                                               const Qt::Alignment _textAlign,
                                               const bool _showText,
                                               const bool _showArrowFrom,
                                               const bool _showArrowTo,
                                               const bool _visible,
                                               const Material &_material,
                                               const std::string &_name)
    : Item3DLineArrow(_pointFrom,
                      _pointTo,
                      _arrowLength,
                      _arrowRadius,
                      _lineRadius,
                      _quality,
                      _text,
                      _textPosition,
                      _textSize,
                      _textAlign,
                      _showText,
                      _visible,
                      _material,
                      _name)
    , showArrowFrom(_showArrowFrom, _name + ".showArrowFrom")
    , showArrowTo(_showArrowTo, _name + ".showArrowTo")
{
    props.push_back(&showArrowFrom);
    props.push_back(&showArrowTo);
}

void Universe1::Video::Item3DLineDim::addData3D(std::list<Data3D> &_out,
                                                const Shader *_shader,
                                                const uint64_t _timeStep) const
{
    buildData(_out,
              _shader,
              pointFrom.getValue(_timeStep),
              pointTo.getValue(_timeStep),
              arrowLength.getValue(_timeStep),
              arrowRadius.getValue(_timeStep),
              lineRadius.getValue(_timeStep),
              quality.getValue(_timeStep),
              text.text.getValue(_timeStep),
              text.position.getValue(_timeStep),
              text.sizeMult.getValue(_timeStep),
              text.align.getValue(_timeStep),
              text.show.getValue(_timeStep),
              showArrowFrom.getValue(_timeStep),
              showArrowTo.getValue(_timeStep),
              material.getValue(_timeStep));
}

void Universe1::Video::Item3DLineDim::buildData(std::list<Data3D> &_out,
                                                const Shader *_shader,
                                                const QVector3D &_pointFrom,
                                                const QVector3D &_pointTo,
                                                const QVector3D &_arm,
                                                const float _arrowLength,
                                                const float _arrowRadius,
                                                const float _lineRadius,
                                                const uint _quality,
                                                const QString &_text,
                                                const TextPosition _textPosition,
                                                const float _textSize,
                                                const Qt::Alignment _textAlign,
                                                const bool _showText,
                                                const bool _showArrowFrom,
                                                const bool _showArrowTo,
                                                const Material &_material)
{
    const float len = _pointFrom.distanceToPoint(_pointTo);
    if (qFuzzyIsNull(len))
        return;

    if ((!_showArrowFrom && !_showArrowTo) || qFuzzyIsNull(_arrowLength) || qFuzzyIsNull(_arrowRadius) ||
        _arrowLength < 0.0f || _arrowRadius < 0.0f)
    {
        Item3DLineSegment::buildData(_out, _pointFrom, _pointTo, _arm, _lineRadius, _quality, _material);
        buildText(_out,
                  _shader,
                  _pointFrom,
                  _pointTo,
                  _arrowLength,
                  _text,
                  _textPosition,
                  _textSize,
                  _textAlign,
                  _showText,
                  _material);
        return;
    }

    if (!_showArrowFrom && _showArrowTo)
    {
        Item3DLineArrow::buildData(_out,
                                   _shader,
                                   _pointFrom,
                                   _pointTo,
                                   _arm,
                                   _arrowLength,
                                   _arrowRadius,
                                   _lineRadius,
                                   _quality,
                                   _text,
                                   _textPosition,
                                   _textSize,
                                   _textAlign,
                                   _showText,
                                   _material);
        return;
    }

    if (_showArrowFrom && !_showArrowTo)
    {
        Item3DLineArrow::buildData(_out,
                                   _shader,
                                   _pointTo,
                                   _pointFrom,
                                   _arm,
                                   _arrowLength,
                                   _arrowRadius,
                                   _lineRadius,
                                   _quality,
                                   _text,
                                   _textPosition,
                                   _textSize,
                                   _textAlign,
                                   _showText,
                                   _material);
        return;
    }

    const QVector3D n = (_pointTo - _pointFrom).normalized();
    if (qFuzzyCompare(len, _arrowLength * 2.0f) || len < _arrowLength * 2.0f)
    {
        const QVector3D pf1 = _pointFrom - n * _arrowLength;
        const QVector3D pt1 = _pointFrom + n * (len + _arrowLength);
        const QVector3D pf2 = _pointFrom - n * (_arrowLength * 1.5f);
        const QVector3D pt2 = _pointFrom + n * (len + _arrowLength * 1.5f);

        Item3DLineSegment::buildData(_out, _pointFrom, _pointTo, _arm, _lineRadius, _quality, _material);
        Item3DLineSegment::buildData(_out, pf1, pf2, _arm, _lineRadius, _quality, _material);
        Item3DLineSegment::buildData(_out, pt1, pt2, _arm, _lineRadius, _quality, _material);
        Item3DCone::buildData(_out, pf1, _pointFrom, _arm, _arrowRadius, _quality, _material);
        Item3DCone::buildData(_out, pt1, _pointTo, _arm, _arrowRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, pf1, -n, _arm, _arrowRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, pf2, -n, _arm, _lineRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, pt1, n, _arm, _arrowRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, pt2, n, _arm, _lineRadius, _quality, _material);

        buildText(
            _out, _shader, pf2, pt2, _arrowLength, _text, _textPosition, _textSize, _textAlign, _showText, _material);
    }
    else
    {
        const QVector3D p1 = _pointFrom + n * _arrowLength;
        const QVector3D p2 = _pointFrom + n * (len - _arrowLength);

        Item3DLineSegment::buildData(_out, p1, p2, _arm, _lineRadius, _quality, _material);
        Item3DCone::buildData(_out, p1, _pointFrom, _arm, _arrowRadius, _quality, _material);
        Item3DCone::buildData(_out, p2, _pointTo, _arm, _arrowRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, p1, n, _arm, _arrowRadius, _quality, _material);
        Item3DPlaneCircle::buildData(_out, p2, -n, _arm, _arrowRadius, _quality, _material);

        buildText(_out,
                  _shader,
                  _pointFrom,
                  _pointTo,
                  _arrowLength,
                  _text,
                  _textPosition,
                  _textSize,
                  _textAlign,
                  _showText,
                  _material);
    }
}

//

Universe1::Video::DBItem3DLineArrow::DBItem3DLineArrow(const std::string &_footageName, std::list<Item3D *> *_items)
    : DBItems3D("lineArrow", _footageName, _items)
{
}

Universe1::Video::Item3DLineArrow *Universe1::Video::DBItem3DLineArrow::add(const QVector3D &_pointFrom,
                                                                            const QVector3D &_pointTo,
                                                                            const float _arrowLength,
                                                                            const float _arrowRadius,
                                                                            const float _lineRadius,
                                                                            const uint _quality,
                                                                            const QString &_text,
                                                                            const TextPosition _textPosition,
                                                                            const float _textSize,
                                                                            const Qt::Alignment _textAlign,
                                                                            const bool _showText,
                                                                            const bool _visible,
                                                                            const Material &_material)
{
    Item3DLineArrow *result = new Item3DLineArrow(_pointFrom,
                                                  _pointTo,
                                                  _arrowLength,
                                                  _arrowRadius,
                                                  _lineRadius,
                                                  _quality,
                                                  _text,
                                                  _textPosition,
                                                  _textSize,
                                                  _textAlign,
                                                  _showText,
                                                  _visible,
                                                  _material,
                                                  nextName());
    items->push_back(result);
    return result;
}

Universe1::Video::Item3DLineDim *Universe1::Video::DBItem3DLineArrow::addDim(const QVector3D &_pointFrom,
                                                                             const QVector3D &_pointTo,
                                                                             const float _arrowLength,
                                                                             const float _arrowRadius,
                                                                             const float _lineRadius,
                                                                             const uint _quality,
                                                                             const QString &_text,
                                                                             const TextPosition _textPosition,
                                                                             const float _textSize,
                                                                             const Qt::Alignment _textAlign,
                                                                             const bool _showText,
                                                                             const bool _showArrowFrom,
                                                                             const bool _showArrowTo,
                                                                             const bool _visible,
                                                                             const Material &_material)
{
    Item3DLineDim *result = new Item3DLineDim(_pointFrom,
                                              _pointTo,
                                              _arrowLength,
                                              _arrowRadius,
                                              _lineRadius,
                                              _quality,
                                              _text,
                                              _textPosition,
                                              _textSize,
                                              _textAlign,
                                              _showText,
                                              _showArrowFrom,
                                              _showArrowTo,
                                              _visible,
                                              _material,
                                              nextName());
    items->push_back(result);
    return result;
}
