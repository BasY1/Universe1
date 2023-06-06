#ifndef UNIVERSE1_VIDEO_ITEM2D_H
#define UNIVERSE1_VIDEO_ITEM2D_H

#include "subs.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief 2D text item structure
 */
struct Item2D : public Item
{
    DynamicBool visible;     //!< Visible flag
    DynamicTextGroup text;   //!< Text properties
    DynamicColor textColor;  //!< Text color

    static const std::set<Qt::Alignment> supportedAlignments;  //!< Supported alignments collection

    /*!
     * \brief Constructor
     * \param _visible Initial visible flag
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \param _name Item name
     */
    Item2D(const bool _visible,
           const QString &_textHtml,
           const float _textSize,
           const Qt::Alignment _textAlign,
           const QColor _textColor,
           const std::string &_name);

    /*!
     * \brief Initialize 2D text item
     * \param _duration Total footage duration in ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Paint 2D text item
     * \param _painter Painter
     * \param _timeStep Time-step
     * \return
     */
    virtual void paint(QPainter *_painter, const uint64_t _timeStep) const;

 protected:
    /*!
     * \brief Create QT text document
     * \param _timeStep Time-step
     * \return QT text document
     */
    virtual QTextDocument *createDocument(const uint64_t _timeStep) const;
};

/*! \brief Footage 2D text item database */
struct DBItem2D
{
    const std::string &footageName;                      //!< Footage name
    std::map<Qt::Alignment, std::list<Item2D *>> items;  //!< 2D items list

    /*!
     * \brief Constructor
     * \param _footageName Footage name
     */
    DBItem2D(const std::string &_footageName);

    virtual ~DBItem2D();  //!< Destructor

    /*!
     * \brief Initialize 2D items database
     * \param _duration Total footage duration in ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Paint text items at given time
     * \param _painter Painter
     * \param _timeStep Time-step
     */
    void paint(QPainter *_painter, const uint64_t _timeStep) const;

    /*!
     * \brief Add 2D item to database
     * \param _visible Initial visible flag
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \return Created item
     */
    Item2D *add(const bool _visible,
                const QString &_textHtml,
                const float _textSize,
                const Qt::Alignment _textAlign,
                const QColor _textColor);

    /*!
     * \brief Add visible 2D item to database
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \return Created item
     */
    inline Item2D *
    add(const QString &_textHtml, const float _textSize, const Qt::Alignment _textAlign, const QColor _textColor)
    {
        return add(true, _textHtml, _textSize, _textAlign, _textColor);
    }

    /*!
     * \brief Add visible 2D item to database
     * \param _textHtml Initial HTML text
     * \return Created item
     */
    inline Item2D *add(const QString &_textHtml)
    {
        return add(_textHtml, 1.0f, Qt::AlignTop | Qt::AlignLeft, Config::cfg().colorSubs);
    }

    /*!
     * \brief Add visible 2D item to database - (align right)
     * \param _textHtml Initial HTML text
     * \return Created item
     */
    inline Item2D *addR(const QString &_textHtml)
    {
        return add(_textHtml, 1.0f, Qt::AlignTop | Qt::AlignRight, Config::cfg().colorSubs);
    }

    /*!
     * \brief Add hidden 2D item to database
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \return Created item
     */
    inline Item2D *
    addHidden(const QString &_textHtml, const float _textSize, const Qt::Alignment _textAlign, const QColor _textColor)
    {
        return add(false, _textHtml, _textSize, _textAlign, _textColor);
    }

    /*!
     * \brief Add hidden 2D item to database
     * \param _textHtml Initial HTML text
     * \return Created item
     */
    inline Item2D *addHidden(const QString &_textHtml)
    {
        return addHidden(_textHtml, 1.0f, Qt::AlignTop | Qt::AlignLeft, Config::cfg().colorSubs);
    }

    /*!
     * \brief Add hidden 2D item to database - (align right)
     * \param _textHtml Initial HTML text
     * \return Created item
     */
    inline Item2D *addRHidden(const QString &_textHtml)
    {
        return addHidden(_textHtml, 1.0f, Qt::AlignTop | Qt::AlignRight, Config::cfg().colorSubs);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM2D_H
