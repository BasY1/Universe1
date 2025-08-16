/*!
 * \file src/Items/Items2D/item2dtext.cpp
 * \brief Dynamic 2D text item
 */

#include "item2dtext.h"

#include "../Text/itemtext.h"

#include <QTextDocument>

namespace U1 {
namespace Items {

Item2DText::Item2DText(const std::string &_name,
                       const QString &_text,
                       const Math::AlignType _screenPosition,
                       const uint32_t _screenOffset,
                       const QString &_fontFamily,
                       const uint32_t _fontHeight,
                       const Math::ColorRGB &_fontColor,
                       const uint8_t _alpha,
                       const bool _visible)
    : Item2D(_name, _visible, _alpha)
    , text("text", _text)
    , fontFamily("fontFamily", _fontFamily)
    , fontHeight("fontHeight", _fontHeight)
    , fontColor("fontColor", _fontColor)
    , screenPosition("screenPosition", QMetaEnum::fromType<Math::AlignType>(), _screenPosition)
    , screenOffset("screenOffset", _screenOffset)
{
    setupProperties({&text, &fontFamily, &fontHeight, &screenPosition, &screenOffset, &fontColor, &alpha, &visible});
}

void Item2DText::addTextProp(const QString &_key, const Props::ItemProperty *_property)
{
    for (const std::pair<QString, const Props::ItemProperty *> &tp : m_textProps)
    {
        if (_key == tp.first)
            std::cerr << "Error: Item2DText::addTextProp(" << _key.toStdString() << ", ...) Key already registered!\n";
        return;
    }
    m_textProps.push_back({_key, _property});
}

void Item2DText::paintItem(QPainter &_painter, const QSize &_screenSize, const size_t _timeStep) const
{
    const Math::ColorRGB colRGB = fontColor.value(_timeStep);
    QString txt = text.value(_timeStep);
    ItemText::replaceTextValues(txt, m_textProps, _timeStep);
    paintItem2D(_painter,
                _screenSize,
                txt,
                fontFamily.value(_timeStep),
                fontHeight.value(_timeStep),
                QColor(colRGB.red, colRGB.green, colRGB.blue, alpha.value(_timeStep)),
                screenPosition.valueEnum<Math::AlignType>(_timeStep),
                screenOffset.value(_timeStep));
}

void Item2DText::paintItem2D(QPainter &_painter,
                             const QSize &_screenSize,
                             const QString &_text,
                             const QString &_fontFamily,
                             const uint32_t _fontHeight,
                             const QColor _usedColor,
                             const Math::AlignType _screenPosition,
                             const uint32_t _screenOffset)
{
    int offsetX = 0;
    int offsetY = 0;

    QTextDocument *doc = createTextDocument(_text, _fontFamily, _fontHeight, _usedColor);
    const QSize docSize = doc->size().toSize();

    switch (_screenPosition)
    {
    case Math::_AlignTopLeft:
        offsetX = _screenOffset;
        offsetY = _screenOffset;
        break;
    case Math::_AlignTopCenter:
        offsetX = (_screenSize.width() - docSize.width()) / 2;
        offsetY = _screenOffset;
        break;
    case Math::_AlignTopRight:
        offsetX = _screenSize.width() - _screenOffset - docSize.width();
        offsetY = _screenOffset;
        break;
    case Math::_AlignCenterLeft:
        offsetX = _screenOffset;
        offsetY = (_screenSize.height() - docSize.height()) / 2;
        break;
    case Math::_AlignCenterCenter:
        offsetX = (_screenSize.width() - docSize.width()) / 2;
        offsetY = (_screenSize.height() - docSize.height()) / 2;
        break;
    case Math::_AlignCenterRight:
        offsetX = _screenSize.width() - _screenOffset - docSize.width();
        offsetY = (_screenSize.height() - docSize.height()) / 2;
        break;
    case Math::_AlignBottomLeft:
        offsetX = _screenOffset;
        offsetY = _screenSize.height() - _screenOffset - docSize.height();
        break;
    case Math::_AlignBottomCenter:
        offsetX = (_screenSize.width() - docSize.width()) / 2;
        offsetY = _screenSize.height() - _screenOffset - docSize.height();
        break;
    case Math::_AlignBottomRight:
        offsetX = _screenSize.width() - _screenOffset - docSize.width();
        offsetY = _screenSize.height() - _screenOffset - docSize.height();
        break;
    }

    _painter.save();
    _painter.setTransform(QTransform::fromTranslate(offsetX, offsetY));
    doc->drawContents(&_painter);
    _painter.restore();

    delete doc;
}

}  // namespace Items
}  // namespace U1
