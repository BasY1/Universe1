#ifndef UNIVERSE1_VIDEO_ITEM2DIMAGE_H
#define UNIVERSE1_VIDEO_ITEM2DIMAGE_H

#include "item2d.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief 2D image item structure
 */
struct Item2DImage : public Item2D
{
    const QImage image;  //!< Image data

    DynamicBool visibleText;  //!< Show image label flag

    DynamicValue<uint> positionX;  //!< Image position X
    DynamicValue<uint> positionY;  //!< Image position Y
    DynamicValue<uint> sizeX;      //!< Image size X -> width;
    DynamicValue<uint> sizeY;      //!< Image size Y -> height;

    /*!
     * \brief Constructor
     * \param _visible Initial visible flag
     * \param _visibleText Initial visible flag for text label
     * \param _image Image data
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \param _name Item name
     */
    Item2DImage(const bool _visible,
                const bool _visibleText,
                const QImage &_image,
                const QString &_textHtml,
                const float _textSize,
                const Qt::Alignment _textAlign,
                const QColor _textColor,
                const std::string &_name);

    /*!
     * \brief Initialize 2D image item
     * \param _duration Total footage duration in ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Paint 2D image item
     * \param _painter Painter
     * \param _timeStep Time-step
     */
    void paint(QPainter *_painter, const uint64_t _timeStep) const;

    /*!
     * \brief Add maximized image prop. values at time-step
     * \param _timeStep Time-step
     */
    void addMaximized(const uint64_t _timeStep);

    /*!
     * \brief Add same value as last stored at time-step
     * \param _timeStep Time-step
     */
    inline void addSame(const uint64_t _timeStep)
    {
        positionX.addSame(_timeStep);
        positionY.addSame(_timeStep);
        sizeX.addSame(_timeStep);
        sizeY.addSame(_timeStep);
        text.addSame(_timeStep);
        textColor.addSame(_timeStep);
    }
};

/*! \brief Footage 2D image item database */
struct FootageItems2DImage
{
    const std::string &footageName;   //!< Footage name
    std::list<Item2DImage *> images;  //!< 2D image items list

    /*!
     * \brief Constructor
     * \param _footageName Footage name
     */
    FootageItems2DImage(const std::string &_footageName);
    virtual ~FootageItems2DImage();  //!< Destructor

    /*!
     * \brief Initialize 2D image items database
     * \param _duration Total footage duration in ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Paint image items at given time-step
     * \param _painter Painter
     * \param _timeStep Time-step
     */
    void paint(QPainter *_painter, const uint64_t _timeStep) const;

    /*!
     * \brief Add image into database
     * \param _visible Initial visible flag
     * \param _visibleText Initial visible flag for text label
     * \param _image Image data
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \return Created image item
     */
    Item2DImage *add(const bool _visible,
                     const bool _visibleText,
                     const QImage &_image,
                     const QString &_textHtml,
                     const float _textSize,
                     const Qt::Alignment _textAlign,
                     const QColor _textColor);

    /*!
     * \brief Add image into database
     * \param _visibleText Initial visible flag for text label
     * \param _image Image data
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \return Created image item
     */
    inline Item2DImage *add(const bool _visibleText,
                            const QImage &_image,
                            const QString &_textHtml,
                            const float _textSize,
                            const Qt::Alignment _textAlign,
                            const QColor _textColor)
    {
        return add(true, _visibleText, _image, _textHtml, _textSize, _textAlign, _textColor);
    }

    /*!
     * \brief Add image into database
     * \param _image Image data
     * \param _textHtml Initial HTML text
     * \return Created image item
     */
    inline Item2DImage *add(const QImage &_image, const QString &_textHtml = QString())
    {
        return add(true, _image, _textHtml, 1.0f, Qt::AlignHCenter, Config::cfg().colorSubs);
    }

    /*!
     * \brief Add image into database
     * \param _visibleText Initial visible flag for text label
     * \param _image Image data
     * \param _textHtml Initial HTML text
     * \param _textSize Initial text size multiplier
     * \param _textAlign Initial text align
     * \param _textColor Initial text color
     * \return Created image item
     */
    inline Item2DImage *addHidden(const bool _visibleText,
                                  const QImage &_image,
                                  const QString &_textHtml,
                                  const float _textSize,
                                  const Qt::Alignment _textAlign,
                                  const QColor _textColor)
    {
        return add(false, _visibleText, _image, _textHtml, _textSize, _textAlign, _textColor);
    }

    /*!
     * \brief Add image into database
     * \param _image Image data
     * \param _textHtml Initial HTML text
     * \return Created image item
     */
    inline Item2DImage *addHidden(const QImage &_image, const QString &_textHtml = QString())
    {
        return addHidden(true, _image, _textHtml, 1.0f, Qt::AlignHCenter, Config::cfg().colorSubs);
    }
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_ITEM2DIMAGE_H
