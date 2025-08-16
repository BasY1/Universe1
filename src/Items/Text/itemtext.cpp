/*!
 * \file src/Items/Text/itemtext.cpp
 * \brief Dynamic 3D text video item
 */

#include "itemtext.h"

#include "../../Math/multithread.h"

#include "../../Data3D/data3dmaterialbase.h"

#include "../../ItemProps/itempropertyvec2.h"
#include "../../ItemProps/itempropertyvec3.h"

#include <QImage>
#include <QPainter>

namespace U1 {
namespace Items {

ItemText::ItemText(const std::string &_name,
                   const Math::Vec3F &_center,
                   const Math::Vec3F &_normal,
                   const Math::Vec3F &_arm,
                   const QString &_text,
                   const Math::ColorRGB &_color,
                   const QString &_fontFamily,
                   const uint32_t _fontHeight,
                   const uint32_t _borderOffset,
                   const float _pixelSize,
                   const Math::AlignType _textAlign,
                   const Text::TextVisibleType _visibleFrom,
                   const uint8_t _alpha,
                   const bool _visible)
    : Item3DExt(_name, _center, _normal, _arm, _alpha, _visible)
    , text("text", _text)
    , color("color", _color)
    , fontFamily("fontFamily", _fontFamily)
    , fontHeight("fontHeight", _fontHeight)
    , borderOffset("borderOffset", _borderOffset)
    , pixelSize("pixelSize", _pixelSize, 0, std::numeric_limits<float>::max())
    , textAlign("textAlign", QMetaEnum::fromType<Math::AlignType>(), _textAlign)
    , visibleFrom("visibleFrom", QMetaEnum::fromType<Text::TextVisibleType>(), _visibleFrom)
{
    addProperty(&text);
    addProperty(&color);
    addProperty(&fontFamily);
    addProperty(&fontHeight);
    addProperty(&borderOffset);
    addProperty(&pixelSize);
    addProperty(&textAlign);
    addProperty(&visibleFrom);
}

ItemTextCamera::ItemTextCamera(const std::string &_name,
                               const Math::Vec3F &_center,
                               const float _spin,
                               const QString &_text,
                               const Math::ColorRGB &_color,
                               const QString &_fontFamily,
                               const uint32_t _fontHeight,
                               const uint32_t _borderOffset,
                               const float _pixelSize,
                               const Math::AlignType _textAlign,
                               const uint8_t _alpha,
                               const bool _visible)
    : Item3D(_name, _alpha, _visible)
    , center("center", _center)
    , spin("spin", _spin)
    , text("text", _text)
    , color("color", _color)
    , fontFamily("fontFamily", _fontFamily)
    , fontHeight("fontHeight", _fontHeight)
    , borderOffset("borderOffset", _borderOffset)
    , pixelSize("pixelSize", _pixelSize, 0, std::numeric_limits<float>::max())
    , textAlign("textAlign", QMetaEnum::fromType<Math::AlignType>(), _textAlign)
{
    addProperty(&center);
    addProperty(&spin);
    addProperty(&text);
    addProperty(&color);
    addProperty(&fontFamily);
    addProperty(&fontHeight);
    addProperty(&borderOffset);
    addProperty(&pixelSize);
    addProperty(&textAlign);
}

void ItemText::addTextProp(const QString &_key, const Props::ItemProperty *_property)
{
    for (const std::pair<QString, const Props::ItemProperty *> &tp : m_textProps)
    {
        if (_key == tp.first)
            std::cerr << "Error: ItemText::addTextProp(" << _key.toStdString() << ", ...) Key already registered!\n";
        return;
    }
    m_textProps.push_back({_key, _property});
}

void ItemTextCamera::addTextProp(const QString &_key, const Props::ItemProperty *_property)
{
    for (const std::pair<QString, const Props::ItemProperty *> &tp : m_textProps)
    {
        if (_key == tp.first)
            std::cerr << "Error: ItemTextCamera::addTextProp(" << _key.toStdString()
                      << ", ...) Key already registered!\n";
        return;
    }
    m_textProps.push_back({_key, _property});
}

/*!
 * \brief Tool function - replace text with value
 * \param txt Text
 * \param _prop Property
 * \param _timeStep Time-step of property value
 * \param _textPos Text position to replace
 * \param _textLen Text length to replace
 * \param _decimals Number of decimals for a property value
 * \return
 */
static void replaceTextDecimals(QString &txt,
                                const Props::ItemProperty *_prop,
                                const size_t _timeStep,
                                const qsizetype _textPos,
                                const qsizetype _textLen,
                                const int _decimals)
{
    if (_prop->type() == Props::ItemProperty::_PropertyFloat)
        txt.replace(_textPos,
                    _textLen,
                    QString::number(
                        reinterpret_cast<const Props::ItemPropertyFloat *>(_prop)->value(_timeStep), 'f', _decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyDouble)
        txt.replace(_textPos,
                    _textLen,
                    QString::number(
                        reinterpret_cast<const Props::ItemPropertyDouble *>(_prop)->value(_timeStep), 'f', _decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyLongDouble)
        txt.replace(
            _textPos,
            _textLen,
            QString::number((double)reinterpret_cast<const Props::ItemPropertyLongDouble *>(_prop)->value(_timeStep),
                            'f',
                            _decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyVec2F)
        txt.replace(_textPos,
                    _textLen,
                    reinterpret_cast<const Props::ItemPropertyVec2F *>(_prop)->value(_timeStep).toQString(_decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyVec2D)
        txt.replace(_textPos,
                    _textLen,
                    reinterpret_cast<const Props::ItemPropertyVec2D *>(_prop)->value(_timeStep).toQString(_decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyVec2L)
        txt.replace(_textPos,
                    _textLen,
                    reinterpret_cast<const Props::ItemPropertyVec2L *>(_prop)->value(_timeStep).toQString(_decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyVec3F)
        txt.replace(_textPos,
                    _textLen,
                    reinterpret_cast<const Props::ItemPropertyVec3F *>(_prop)->value(_timeStep).toQString(_decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyVec3D)
        txt.replace(_textPos,
                    _textLen,
                    reinterpret_cast<const Props::ItemPropertyVec3D *>(_prop)->value(_timeStep).toQString(_decimals));
    else if (_prop->type() == Props::ItemProperty::_PropertyVec3L)
        txt.replace(_textPos,
                    _textLen,
                    reinterpret_cast<const Props::ItemPropertyVec3L *>(_prop)->value(_timeStep).toQString(_decimals));
    else
        txt.replace(_textPos, _textLen, _prop->textValue(_timeStep));
}

void ItemText::replaceTextValues(QString &txt,
                                 const std::vector<std::pair<QString, const Props::ItemProperty *>> &_textProps,
                                 const size_t _timeStep)
{
    if (_textProps.empty() || txt.isEmpty())
        return;

    qsizetype idxStart = 0;
    while (true)
    {
        const qsizetype idxBeg = txt.indexOf("$$$", idxStart);
        if (idxBeg < 0)
            return;

        const qsizetype idxEnd = txt.indexOf("$", idxBeg + 3);
        if (idxEnd < 0)
        {
            std::cerr << "Error: ItemText::replaceTextValues(): Missing key end [$$$]!\n";
            return;
        }

        const QString key = txt.mid(idxBeg + 3, idxEnd - idxBeg - 3);

        bool ok = false;

        for (const std::pair<QString, const Props::ItemProperty *> &tp : _textProps)
            if (key == tp.first)
            {
                const QString keyEnd = txt.mid(idxEnd, 3);
                const qsizetype keyLen = idxEnd + 3 - idxBeg;

                if (keyEnd == "$$$")
                    txt.replace(idxBeg, keyLen, tp.second->textValue(_timeStep));
                else if (keyEnd == "$0$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 0);
                else if (keyEnd == "$1$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 1);
                else if (keyEnd == "$2$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 2);
                else if (keyEnd == "$3$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 3);
                else if (keyEnd == "$4$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 4);
                else if (keyEnd == "$5$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 5);
                else if (keyEnd == "$6$")
                    replaceTextDecimals(txt, tp.second, _timeStep, idxBeg, keyLen, 6);
                else
                {
                    std::cerr << "Error: ItemText::replaceTextValues(): Unknown key end $$$" << key.toStdString()
                              << keyEnd.toStdString() << "!\n";
                    return;
                }

                ok = true;
                break;
            }

        if (!ok)
        {
            std::cerr << "Error: ItemText::replaceTextValues(): Unknown key $$$" << key.toStdString() << "$!\n";
            idxStart = idxEnd + 3;
        }
        else
        {
            idxStart = idxBeg;
        }
    }
}

void ItemText::createDataImpl(std::list<OpenGL::Data3D *> &_data, const size_t _timeStep) const
{
    QString txt = text.value(_timeStep);
    if (txt.isEmpty())
        return;

    const uint32_t fh = fontHeight.value(_timeStep);
    if (fh == 0U)
        return;

    const float ps = pixelSize.value(_timeStep);
    if (!Math::isPositive(ps))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    replaceTextValues(txt, m_textProps, _timeStep);

    const Math::OrientF o = valueOrientation(_timeStep);
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = color.value(_timeStep);
    const Math::AlignType at = textAlign.valueEnum<Math::AlignType>(_timeStep);

    switch (visibleFrom.valueEnum<Text::TextVisibleType>(_timeStep))
    {
    case Text::TextFrontBack:
        createText(_data, o, txt, c, a, ff, fh, bo, ps, at, true);
        createText(_data, o, txt, c, a, ff, fh, bo, ps, at, false);
        break;
    case Text::TextFront: createText(_data, o, txt, c, a, ff, fh, bo, ps, at, true); break;
    case Text::TextBack: createText(_data, o, txt, c, a, ff, fh, bo, ps, at, false); break;
    }
}

void ItemTextCamera::createDataImpl(std::list<OpenGL::Data3D *> &_data,
                                    const Math::CamF &_camera,
                                    const size_t _timeStep) const
{
    QString txt = text.value(_timeStep);
    if (txt.isEmpty())
        return;

    const uint32_t fh = fontHeight.value(_timeStep);
    if (fh == 0U)
        return;

    const float ps = pixelSize.value(_timeStep);
    if (!Math::isPositive(ps))
        return;

    const uint8_t a = alpha.value(_timeStep);
    if (a == 0U)
        return;

    ItemText::replaceTextValues(txt, m_textProps, _timeStep);

    const Math::OrientF o = Math::OrientF(_camera, center.value(_timeStep), spin.value(_timeStep));
    const QString ff = fontFamily.value(_timeStep);
    const uint32_t bo = borderOffset.value(_timeStep);
    const Math::ColorRGB c = color.value(_timeStep);
    const Math::AlignType at = textAlign.valueEnum<Math::AlignType>(_timeStep);
    ItemText::createText(_data, o, txt, c, a, ff, fh, bo, ps, at, true);
}

/*! \brief Tool structure for text 2D pixels */
struct TextPixels
{
    uint32_t width;                                                     //!< 2D text image width
    uint32_t height;                                                    //!< 2D text image height
    std::vector<Math::ColorRGB> color;                                  //!< Used colors
    std::vector<std::pair<std::array<Math::Vec2F, 4>, size_t>> pixels;  //!< Text pixels - border vertices and color

    /*!
     * \brief Constructor
     * \param _text Text
     * \param _color Text base color
     * \param _fontFamily Text font name
     * \param _fontHeight Font height
     * \param _borderOffset Font height
     */
    TextPixels(const QString &_text,
               const Math::ColorRGB &_color,
               const QString &_fontFamily,
               const uint32_t _fontHeight,
               const uint32_t _borderOffset);

    static std::map<size_t, TextPixels> pixCache;  //!< 2D text pixels cache
};

std::map<size_t, TextPixels> TextPixels::pixCache = {};

/*!
 * \brief Tool function - find color in the collection
 * \param _colors Color collection
 * \param _color Color
 * \return Color index or collection size incremented by 1
 */
inline static size_t findColor(const std::vector<Math::ColorRGB> &_colors, const Math::ColorRGB &_color)
{
    for (size_t i = 0UL; i < _colors.size(); ++i)
        if (_colors[i] == _color)
            return i;
    return _colors.size() + 1UL;
}

/*!
 * \brief Tool function search for visible pixels in the image column
 * \param _out Output pixel collection
 * \param _image Image
 * \param _x Column within the image
 * \param _height Image height
 * \param _colors Used colors
 * \return
 */
static void addColumnPixels(std::list<std::tuple<uint, uint, uint, size_t>> &_out,
                            const QImage &_image,
                            const uint _x,
                            const uint _height,
                            const std::vector<Math::ColorRGB> &_colors)
{
    static const int minAlpha = 32;

    for (uint y = 0; y < _height; ++y)
    {
        const uint yy = _height - y - 1U;
        const QColor col = _image.pixelColor(_x, yy);
        if (col.alpha() > minAlpha)
        {
            size_t cId = findColor(_colors, Math::ColorRGB(col));
            uint y2 = y + 1U;
            for (; y2 < _height; ++y2)
            {
                const uint yy2 = _height - y2 - 1U;
                const QColor col2 = _image.pixelColor(_x, yy2);
                if (col2.alpha() > minAlpha)
                {
                    if (cId > _colors.size())
                        cId = findColor(_colors, Math::ColorRGB(col2));
                }
                else
                {
                    break;
                }
            }

            if (cId > _colors.size())
                cId = 0UL;

            const uint cnt = y2 - y;
            _out.push_back({_x, y, cnt, cId});
            y += (cnt - 1U);
        }
    }
}

TextPixels::TextPixels(const QString &_text,
                       const Math::ColorRGB &_color,
                       const QString &_fontFamily,
                       const uint32_t _fontHeight,
                       const uint32_t _borderOffset)
{
    color = {_color};
    qsizetype i = _text.indexOf("<font color=\"");
    while (i > 0)
    {
        const qsizetype ib = i + 13;
        const qsizetype ie = _text.indexOf("\"", ib);
        const QString colName = _text.mid(ib, ie - ib);
        const QColor qCol = QColor::fromString(colName);
        if (qCol.isValid())
        {
            const Math::ColorRGB col = Math::ColorRGB(qCol);
            if (std::find(color.cbegin(), color.cend(), col) == color.cend())
                color.push_back(col);
        }
        else
        {
            std::cerr << "Invalid <font color=\"" << qPrintable(colName) << "\">!\n";
        }

        i = _text.indexOf("<font color=\"", ie + 1);
    }

    QTextDocument *doc = Item::createTextDocument(_text, _fontFamily, _fontHeight, _color.toQColor());
    const QSize imgSize = doc->size().toSize();
    const uint w = imgSize.width();
    const uint h = imgSize.height();

    QImage img(imgSize.width(), imgSize.height(), QImage::Format_ARGB32_Premultiplied);
    img.fill(QColor(0, 0, 0, 0));
    QPainter painter(&img);
    doc->drawContents(&painter);
    delete doc;

    std::vector<std::pair<uint, uint>> pool = Math::createPool(w);
    std::list<std::tuple<uint, uint, uint, size_t>> data;

    if (pool.empty())
    {
        for (uint x = 0; x < w; ++x)
            addColumnPixels(data, img, x, h, color);
    }
    else
    {
        uint tt = 0;
        std::vector<std::list<std::tuple<uint, uint, uint, size_t>>> tData(pool.size());
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        for (const std::pair<uint, uint> &t : std::as_const(pool))
            threads.push_back(std::thread(
                [t, img, h, this](std::list<std::tuple<uint, uint, uint, size_t>> &__out) {
                    const uint end = t.first + t.second;
                    for (uint i = t.first; i < end; ++i)
                        addColumnPixels(__out, img, i, h, color);
                },
                std::ref(tData[tt++])));

        for (std::thread &t : threads)
            t.join();

        for (std::list<std::tuple<uint, uint, uint, size_t>> &l : tData)
            data.splice(data.end(), l);
    }

    uint minX = std::numeric_limits<uint>::max(), minY = std::numeric_limits<uint>::max(), maxX = 0U, maxY = 0U;
    for (const std::tuple<uint, uint, uint, size_t> &t : std::as_const(data))
    {
        if (minX > std::get<0>(t))
            minX = std::get<0>(t);
        if (minY > std::get<1>(t))
            minY = std::get<1>(t);
        if (maxX < std::get<0>(t))
            maxX = std::get<0>(t);
        if (maxY < std::get<1>(t))
            maxY = std::get<1>(t);
    }

    width = maxX - minX + 1 + _borderOffset * 2;
    height = maxY - minY + 1 + _borderOffset * 2;

    pool = Math::createPool(uint(data.size()));
    if (pool.empty())
    {
        pixels.reserve(data.size());
        for (const std::tuple<uint, uint, uint, size_t> &t : std::as_const(data))
        {
            const Math::Vec2F p0 =
                Math::Vec2F(std::get<0>(t) - minX + _borderOffset, std::get<1>(t) - minY + _borderOffset);
            const Math::Vec2F p1 = {p0.x + 1.0f, p0.y};
            const Math::Vec2F p2 = {p1.x, p1.y + float(std::get<2>(t))};
            const Math::Vec2F p3 = {p0.x, p0.y + float(std::get<2>(t))};
            pixels.push_back({{{p0, p1, p2, p3}}, std::get<3>(t)});
        }
    }
    else
    {
        std::list<std::tuple<uint, uint, uint, size_t>>::const_iterator it = data.cbegin();
        std::vector<std::thread> threads;
        threads.reserve(pool.size());
        pixels.resize(data.size());
        for (const std::pair<uint, uint> &t : std::as_const(pool))
        {
            threads.push_back(std::thread(
                [t, minX, minY, _borderOffset](std::pair<std::array<Math::Vec2F, 4>, size_t> *__out,
                                               std::list<std::tuple<uint, uint, uint, size_t>>::const_iterator _it) {
                    std::list<std::tuple<uint, uint, uint, size_t>>::const_iterator it2 = _it;
                    const uint end = t.first + t.second;
                    for (uint i = t.first; i < end; ++i, ++it2)
                    {
                        const Math::Vec2F p0 = {float(std::get<0>(*it2) - minX + _borderOffset),
                                                float(std::get<1>(*it2) - minY + _borderOffset)};
                        const Math::Vec2F p1 = {p0.x + 1.0f, p0.y};
                        const Math::Vec2F p2 = {p1.x, p1.y + float(std::get<2>(*it2))};
                        const Math::Vec2F p3 = {p0.x, p0.y + float(std::get<2>(*it2))};
                        __out[i] = {{{p0, p1, p2, p3}}, std::get<3>(*it2)};
                    }
                },
                pixels.data(),
                it));
            std::advance(it, t.second);
        }
        for (std::thread &t : threads)
            t.join();
    }
}

void ItemText::createText(std::list<OpenGL::Data3D *> &_data,
                          const Math::OrientF &_orientation,
                          const QString &_text,
                          const Math::ColorRGB &_color,
                          const uint8_t _alpha,
                          const QString &_fontFamily,
                          const uint32_t _fontHeight,
                          const uint32_t _borderOffset,
                          const float _pixelSize,
                          const Math::AlignType _textAlign,
                          const bool _visibleFromFront)
{
    const size_t hash = Math::mixHash(Math::mixTextHash(_text),
                                      _color.toHash(),
                                      Math::mixTextHash(_fontFamily),
                                      std::hash<uint32_t>{}(_fontHeight),
                                      std::hash<uint32_t>{}(_borderOffset));

    std::map<size_t, TextPixels>::const_iterator it = TextPixels::pixCache.find(hash);
    if (it == TextPixels::pixCache.cend())
    {
        TextPixels::pixCache.insert({hash, TextPixels(_text, _color, _fontFamily, _fontHeight, _borderOffset)});
        it = TextPixels::pixCache.find(hash);
    }

    if (it == TextPixels::pixCache.cend())
        return;

    const TextPixels &tp = (*it).second;

    const float w = float(tp.width) * _pixelSize;
    const float h = float(tp.height) * _pixelSize;
    Math::Vec2F o = {};
    switch (_textAlign)
    {
    case Math::_AlignTopLeft: o = {0.0f, -h}; break;
    case Math::_AlignTopCenter: o = {-w * 0.5f, -h}; break;
    case Math::_AlignTopRight: o = {-w, -h}; break;
    case Math::_AlignCenterLeft: o = {0.0f, -h * 0.5f}; break;
    case Math::_AlignCenterCenter: o = {-w * 0.5f, -h * 0.5f}; break;
    case Math::_AlignCenterRight: o = {-w, -h * 0.5f}; break;
    case Math::_AlignBottomLeft: o = {0.0f, 0.0f}; break;
    case Math::_AlignBottomCenter: o = {-w * 0.5f, 0.0f}; break;
    case Math::_AlignBottomRight: o = {-w, 0.0f}; break;
    }

    const Math::Vec3F c = _orientation.center + _orientation.normal2 * o.x + _orientation.normal3 * o.y;
    const std::vector<std::pair<size_t, size_t>> pool = Math::createPool(tp.pixels.size());

    if (_visibleFromFront)
    {
        if (pool.empty())
        {
            for (size_t i = 0; i < tp.pixels.size(); ++i)
            {
                const std::array<Math::Vec2F, 4> &p = tp.pixels.at(i).first;
                _data.push_back(OpenGL::Data3DMaterialBase::rectangle(
                    c + _orientation.normal2 * (p[0].x * _pixelSize) + _orientation.normal3 * (p[0].y * _pixelSize),
                    c + _orientation.normal2 * (p[1].x * _pixelSize) + _orientation.normal3 * (p[1].y * _pixelSize),
                    c + _orientation.normal2 * (p[2].x * _pixelSize) + _orientation.normal3 * (p[2].y * _pixelSize),
                    c + _orientation.normal2 * (p[3].x * _pixelSize) + _orientation.normal3 * (p[3].y * _pixelSize),
                    Math::MaterialRGB(tp.color[tp.pixels.at(i).second]),
                    _alpha));
            }
        }
        else
        {
            uint tt = 0U;
            std::vector<std::list<OpenGL::Data3D *>> tData(pool.size());
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, c, _orientation, _pixelSize, _alpha, tp](
                        std::list<OpenGL::Data3D *> &__data, const std::pair<std::array<Math::Vec2F, 4>, size_t> *_p) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const std::array<Math::Vec2F, 4> &p = _p[i].first;
                            __data.push_back(OpenGL::Data3DMaterialBase::rectangleData(
                                c + _orientation.normal2 * (p[0].x * _pixelSize) +
                                    _orientation.normal3 * (p[0].y * _pixelSize),
                                c + _orientation.normal2 * (p[1].x * _pixelSize) +
                                    _orientation.normal3 * (p[1].y * _pixelSize),
                                c + _orientation.normal2 * (p[2].x * _pixelSize) +
                                    _orientation.normal3 * (p[2].y * _pixelSize),
                                c + _orientation.normal2 * (p[3].x * _pixelSize) +
                                    _orientation.normal3 * (p[3].y * _pixelSize),
                                Math::MaterialRGB(tp.color[_p[i].second]),
                                _alpha));
                        }
                    },
                    std::ref(tData[tt++]),
                    tp.pixels.data()));

            for (std::thread &t : threads)
                t.join();

            for (std::list<OpenGL::Data3D *> &l : tData)
                _data.splice(_data.end(), l);
        }
    }
    else
    {
        if (pool.empty())
        {

            for (size_t i = 0; i < tp.pixels.size(); ++i)
            {
                const std::array<Math::Vec2F, 4> &p = tp.pixels.at(i).first;
                _data.push_back(OpenGL::Data3DMaterialBase::rectangle(
                    c + _orientation.normal2 * (p[0].x * _pixelSize) + _orientation.normal3 * (p[0].y * _pixelSize),
                    c + _orientation.normal2 * (p[3].x * _pixelSize) + _orientation.normal3 * (p[3].y * _pixelSize),
                    c + _orientation.normal2 * (p[2].x * _pixelSize) + _orientation.normal3 * (p[2].y * _pixelSize),
                    c + _orientation.normal2 * (p[1].x * _pixelSize) + _orientation.normal3 * (p[1].y * _pixelSize),
                    Math::MaterialRGB(tp.color[tp.pixels.at(i).second]),
                    _alpha));
            }
        }
        else
        {
            uint tt = 0U;
            std::vector<std::list<OpenGL::Data3D *>> tData(pool.size());
            std::vector<std::thread> threads;
            threads.reserve(pool.size());
            for (const std::pair<size_t, size_t> &t : std::as_const(pool))
                threads.push_back(std::thread(
                    [t, c, _orientation, _pixelSize, _alpha, tp](
                        std::list<OpenGL::Data3D *> &__data, const std::pair<std::array<Math::Vec2F, 4>, size_t> *_p) {
                        const size_t end = t.first + t.second;
                        for (size_t i = t.first; i < end; ++i)
                        {
                            const std::array<Math::Vec2F, 4> &p = _p[i].first;
                            __data.push_back(OpenGL::Data3DMaterialBase::rectangleData(
                                c + _orientation.normal2 * (p[0].x * _pixelSize) +
                                    _orientation.normal3 * (p[0].y * _pixelSize),
                                c + _orientation.normal2 * (p[3].x * _pixelSize) +
                                    _orientation.normal3 * (p[3].y * _pixelSize),
                                c + _orientation.normal2 * (p[2].x * _pixelSize) +
                                    _orientation.normal3 * (p[2].y * _pixelSize),
                                c + _orientation.normal2 * (p[1].x * _pixelSize) +
                                    _orientation.normal3 * (p[1].y * _pixelSize),
                                Math::MaterialRGB(tp.color[_p[i].second]),
                                _alpha));
                        }
                    },
                    std::ref(tData[tt++]),
                    tp.pixels.data()));

            for (std::thread &t : threads)
                t.join();

            for (std::list<OpenGL::Data3D *> &l : tData)
                _data.splice(_data.end(), l);
        }
    }
}

}  // namespace Items
}  // namespace U1
