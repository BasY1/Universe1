#ifndef UNIVERSE1_VIDEO_ITEM3DTEXT_H
#define UNIVERSE1_VIDEO_ITEM3DTEXT_H

#include "../item3d.h"

namespace Universe1 {
namespace Video {

/*! \brief 3D Text item */
struct Item3DText : public Item3DBase
{
    DynamicTextGroup text;  //!< Text properties

    DynamicVec3 position;   //!< Text start position 3D
    DynamicVec3 normalRow;  //!< Normal in text row direction
    DynamicVec3 normalUp;   //!< Normal in text up direction

    DynamicBool followCamera;  //!< Turn text towards camera position flag

    /*!
     * \brief Constructor
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    Item3DText(const QString &_textHtml,
               const float _textSize,
               const Qt::Alignment _textAlign,
               const QVector3D &_position,
               const QVector3D &_normalRow,
               const QVector3D &_normalUp,
               const bool _followCamera,
               const bool _visible,
               const Material &_material,
               const std::string &_name);

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const;

    /*!
     * \brief Build 3D data
     * \param _out Output 3D data list
     * \param _textHtml Text to draw
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _position Text position
     * \param _normalRow Normal in text row direction
     * \param _normalUp Normal in text up direction
     * \param _material Material
     * \return
     */
    static void buildData(std::list<Data3D> &_out,
                          const QString &_textHtml,
                          const float _textSize,
                          const Qt::Alignment _textAlign,
                          const QVector3D &_position,
                          const QVector3D &_normalRow,
                          const QVector3D &_normalUp,
                          const Material &_material);

    /*!
     * \brief Build 3D data towards camera position
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _textHtml Text to draw
     * \param _textSize Text size multiplier
     * \param _textAlign Text align
     * \param _position Text position
     * \param _material Material
     * \return
     */
    inline static void buildData(std::list<Data3D> &_out,
                                 const Shader *_shader,
                                 const QString &_textHtml,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const QVector3D &_position,
                                 const Material &_material)
    {
        const QVector3D fw = (_shader->cam() - _position).normalized();
        const QVector3D nr = QVector3D::crossProduct(nz, fw).normalized();
        const QVector3D nu = QVector3D::crossProduct(fw, nr).normalized();
        buildData(_out, _textHtml, _textSize, _textAlign, _position, nr, nu, _material);
    }
};

/*! \brief 3D Text item with dynamic value */
template <typename T>
struct Item3DTextValue : public Item3DText
{
    DynamicValue<T> value;  //!< Property with value

    /*!
     * \brief Constructor
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \param _name Item name
     */
    template <typename = std::enable_if<std::is_floating_point<T>::value>>
    Item3DTextValue(const T _value,
                    const QString &_textHtml,
                    const float _textSize,
                    const Qt::Alignment _textAlign,
                    const QVector3D &_position,
                    const QVector3D &_normalRow,
                    const QVector3D &_normalUp,
                    const bool _followCamera,
                    const bool _visible,
                    const Material &_material,
                    const std::string &_name)
        : Item3DText(_textHtml,
                     _textSize,
                     _textAlign,
                     _position,
                     _normalRow,
                     _normalUp,
                     _followCamera,
                     _visible,
                     _material,
                     _name)
        , value(_value, _name + ".value")
    {
        props.push_back(&value);
    }

    /*!
     * \brief Create 3D data at given time-step
     * \param _out Output 3D data list
     * \param _shader Shader program
     * \param _timeStep Time-step
     */
    void addData3D(std::list<Data3D> &_out, const Shader *_shader, const uint64_t _timeStep) const
    {
        const QString txt = text.text.getValue(_timeStep).replace("$VAL$", value.getValueText(_timeStep));
        const float tps = text.sizeMult.getValue(_timeStep);
        const Qt::Alignment al = text.align.getValue(_timeStep);
        const QVector3D p = position.getValue(_timeStep);
        const Material m = material.getValue(_timeStep);
        if (followCamera.getValue(_timeStep))
            buildData(_out, _shader, txt, tps, al, p, m);
        else
            buildData(_out, txt, tps, al, p, normalRow.getValue(_timeStep), normalUp.getValue(_timeStep), m);
    }
};

/*!
 * \brief Footage database of 3D text items
 */
struct DBItem3DText : public DBItems3D
{
    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _items Pointer to all 3D items collection
     */
    DBItem3DText(const std::string &_footageName, std::list<Item3D *> *_items);

    /*!
     * \brief Add 3D text item
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    Item3DText *add(const QString &_textHtml,
                    const float _textSize,
                    const Qt::Alignment _textAlign,
                    const QVector3D &_position,
                    const QVector3D &_normalRow,
                    const QVector3D &_normalUp,
                    const bool _followCamera,
                    const bool _visible,
                    const Material &_material);

    /*!
     * \brief Add 3D text item
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *add(const QString &_textHtml,
                           const float _textSize,
                           const Qt::Alignment _textAlign,
                           const QVector3D &_position,
                           const QVector3D &_normalRow,
                           const QVector3D &_normalUp,
                           const bool _followCamera,
                           const Material &_material)
    {
        return add(_textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, _followCamera, true, _material);
    }

    /*!
     * \brief Add 3D text item - not following camera
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *add(const QString &_textHtml,
                           const float _textSize,
                           const Qt::Alignment _textAlign,
                           const QVector3D &_position,
                           const QVector3D &_normalRow,
                           const QVector3D &_normalUp,
                           const Material &_material)
    {
        return add(_textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, false, _material);
    }

    /*!
     * \brief Add 3D text item - not following camera
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *add(const QString &_textHtml,
                           const QVector3D &_position,
                           const QVector3D &_normalRow,
                           const QVector3D &_normalUp,
                           const Material &_material)
    {
        return add(_textHtml, 1.0f, Qt::AlignCenter, _position, _normalRow, _normalUp, _material);
    }

    /*!
     * \brief Add 3D text item - following camera
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *add(const QString &_textHtml,
                           const float _textSize,
                           const Qt::Alignment _textAlign,
                           const QVector3D &_position,
                           const Material &_material)
    {
        return add(_textHtml, _textSize, _textAlign, _position, {}, {}, true, _material);
    }

    /*!
     * \brief Add 3D text item - following camera
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *add(const QString &_textHtml, const QVector3D &_position, const Material &_material)
    {
        return add(_textHtml, 1.0f, Qt::AlignCenter, _position, _material);
    }

    /*!
     * \brief Add hidden 3D text item
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *addHidden(const QString &_textHtml,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const QVector3D &_position,
                                 const QVector3D &_normalRow,
                                 const QVector3D &_normalUp,
                                 const bool _followCamera,
                                 const Material &_material)
    {
        return add(_textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, _followCamera, false, _material);
    }

    /*!
     * \brief Add hidden 3D text item - not following camera
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *addHidden(const QString &_textHtml,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const QVector3D &_position,
                                 const QVector3D &_normalRow,
                                 const QVector3D &_normalUp,
                                 const Material &_material)
    {
        return addHidden(_textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, false, _material);
    }

    /*!
     * \brief Add hidden 3D text item - not following camera
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *addHidden(const QString &_textHtml,
                                 const QVector3D &_position,
                                 const QVector3D &_normalRow,
                                 const QVector3D &_normalUp,
                                 const Material &_material)
    {
        return addHidden(_textHtml, 1.0f, Qt::AlignCenter, _position, _normalRow, _normalUp, _material);
    }

    /*!
     * \brief Add hidden 3D text item - following camera
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *addHidden(const QString &_textHtml,
                                 const float _textSize,
                                 const Qt::Alignment _textAlign,
                                 const QVector3D &_position,
                                 const Material &_material)
    {
        return addHidden(_textHtml, _textSize, _textAlign, _position, {}, {}, true, _material);
    }

    /*!
     * \brief Add hidden 3D text item - following camera
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    inline Item3DText *addHidden(const QString &_textHtml, const QVector3D &_position, const Material &_material)
    {
        return addHidden(_textHtml, 1.0f, Qt::AlignCenter, _position, _material);
    }

    /*!
     * \brief Add 3D text with value item
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _visible Initial visible flag
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    Item3DTextValue<T> *addT(const T _value,
                             const QString &_textHtml,
                             const float _textSize,
                             const Qt::Alignment _textAlign,
                             const QVector3D &_position,
                             const QVector3D &_normalRow,
                             const QVector3D &_normalUp,
                             const bool _followCamera,
                             const bool _visible,
                             const Material &_material)
    {
        Item3DTextValue<T> *result = new Item3DTextValue<T>(_value,
                                                            _textHtml,
                                                            _textSize,
                                                            _textAlign,
                                                            _position,
                                                            _normalRow,
                                                            _normalUp,
                                                            _followCamera,
                                                            _visible,
                                                            _material,
                                                            nextName() + "[" + typeid(T).name() + "]");
        items->push_back(result);
        return result;
    }

    /*!
     * \brief Add visible 3D text with value item
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addT(const T _value,
                                    const QString &_textHtml,
                                    const float _textSize,
                                    const Qt::Alignment _textAlign,
                                    const QVector3D &_position,
                                    const QVector3D &_normalRow,
                                    const QVector3D &_normalUp,
                                    const bool _followCamera,
                                    const Material &_material)
    {
        return addT(
            _value, _textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, _followCamera, true, _material);
    }

    /*!
     * \brief Add visible 3D text with value item - following camera
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addT(const T _value,
                                    const QString &_textHtml,
                                    const float _textSize,
                                    const Qt::Alignment _textAlign,
                                    const QVector3D &_position,
                                    const Material &_material)
    {
        return addT(_value, _textHtml, _textSize, _textAlign, _position, {}, {}, true, _material);
    }

    /*!
     * \brief Add visible 3D text with value item - following camera
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *
    addT(const T _value, const QString &_textHtml, const QVector3D &_position, const Material &_material)
    {
        return addT(_value, _textHtml, 1.0f, Qt::AlignCenter, _position, _material);
    }

    /*!
     * \brief Add visible 3D text with value item - frozen position
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addT(const T _value,
                                    const QString &_textHtml,
                                    const float _textSize,
                                    const Qt::Alignment _textAlign,
                                    const QVector3D &_position,
                                    const QVector3D &_normalRow,
                                    const QVector3D &_normalUp,
                                    const Material &_material)
    {
        return addT(_value, _textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, false, _material);
    }

    /*!
     * \brief Add visible 3D text with value item - frozen position
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addT(const T _value,
                                    const QString &_textHtml,
                                    const QVector3D &_position,
                                    const QVector3D &_normalRow,
                                    const QVector3D &_normalUp,
                                    const Material &_material)
    {
        return addT(_value, _textHtml, 1.0f, Qt::AlignCenter, _position, _normalRow, _normalUp, _material);
    }

    /*!
     * \brief Add hidden 3D text with value item
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _followCamera Initial follow camera flag
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addTHidden(const T _value,
                                          const QString &_textHtml,
                                          const float _textSize,
                                          const Qt::Alignment _textAlign,
                                          const QVector3D &_position,
                                          const QVector3D &_normalRow,
                                          const QVector3D &_normalUp,
                                          const bool _followCamera,
                                          const Material &_material)
    {
        return addT(_value,
                    _textHtml,
                    _textSize,
                    _textAlign,
                    _position,
                    _normalRow,
                    _normalUp,
                    _followCamera,
                    false,
                    _material);
    }

    /*!
     * \brief Add hidden 3D text with value item - following camera
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addTHidden(const T _value,
                                          const QString &_textHtml,
                                          const float _textSize,
                                          const Qt::Alignment _textAlign,
                                          const QVector3D &_position,
                                          const Material &_material)
    {
        return addTHidden(_value, _textHtml, _textSize, _textAlign, _position, {}, {}, true, _material);
    }

    /*!
     * \brief Add hidden 3D text with value item - following camera
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *
    addTHidden(const T _value, const QString &_textHtml, const QVector3D &_position, const Material &_material)
    {
        return addTHidden(_value, _textHtml, 1.0f, Qt::AlignCenter, _position, _material);
    }

    /*!
     * \brief Add hidden 3D text with value item - frozen position
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addTHidden(const T _value,
                                          const QString &_textHtml,
                                          const float _textSize,
                                          const Qt::Alignment _textAlign,
                                          const QVector3D &_position,
                                          const QVector3D &_normalRow,
                                          const QVector3D &_normalUp,
                                          const Material &_material)
    {
        return addT(_value, _textHtml, _textSize, _textAlign, _position, _normalRow, _normalUp, false, _material);
    }

    /*!
     * \brief Add hidden 3D text with value item - frozen position
     * \param _value Initial value
     * \param _textHtml Initial HTML text
     * \param _position Initial text start position 3D
     * \param _normalRow Initial normal in text row direction
     * \param _normalUp Initial normal in text up direction
     * \param _material Initial material
     * \return Created item
     */
    template <typename T, typename = std::enable_if<std::is_floating_point<T>::value>>
    inline Item3DTextValue<T> *addTHidden(const T _value,
                                          const QString &_textHtml,
                                          const QVector3D &_position,
                                          const QVector3D &_normalRow,
                                          const QVector3D &_normalUp,
                                          const Material &_material)
    {
        return addT(_value, _textHtml, 1.0f, Qt::AlignCenter, _position, _normalRow, _normalUp, _material);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM3DTEXT_H
