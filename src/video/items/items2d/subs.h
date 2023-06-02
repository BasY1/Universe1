#ifndef UNIVERSE1_VIDEO_SUBS_H
#define UNIVERSE1_VIDEO_SUBS_H

#include "../item.h"

namespace Universe1 {
namespace Video {

/*!
 * \brief Subtitle structure
 */
struct Subs : public Item
{
    uint64_t showTime;  //!< Show time in ms
    uint64_t hideTime;  //!< Hide time in ms

    QString textHtml;        //!< Subtitle text
    QString textRead;        //!< Speech text for TTS engine
    QString pathAudio = "";  //!< Audio file for this speech

    uint64_t audioDuration = 0UL;  //!< Audio duration in ms

    /*!
     * \brief Constructor
     * \param _textHtml Subtitle text
     * \param _textRead Speech text for TTS engine
     * \param _name Item name
     * \param _showTime Show time in ms
     * \param _hideTime Hide time in ms
     */
    Subs(const QString &_textHtml,
         const QString &_textRead,
         const std::string &_name,
         const uint64_t _showTime,
         const uint64_t _hideTime);

    /*!
     * \brief Initialize subtitle item
     * \param _duration Total footage duration in ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Paint subtitles
     * \param _painter Painter
     */
    void paint(QPainter *_painter) const;

    /*!
     * \brief Audio duration aligned to frames and frame duration
     * \return Aligned audio duration
     */
    inline uint64_t audioDurationAligned() const
    {
        const uint64_t fd = Config::cfg().frameDuration;
        const uint64_t tmod = audioDuration % fd;
        return audioDuration + (tmod == 0UL ? 0UL : (fd - tmod));
    }

    /*!
     * \brief Return fixed hide time
     * \param _add Silence time addition in ms
     * \return Aligned total duration with addition
     */
    inline uint64_t fixTime(const uint64_t _add = 0UL) const
    {
        return showTime + audioDurationAligned() + _add;
    }

    /*!
     * \brief Test if subtitle is visible
     * \param _timeStep Time-step
     * \return \c true if subtitle is visible at given time
     */
    inline bool isCurrent(const uint64_t _timeStep) const
    {
        return showTime <= _timeStep && (hideTime == 0UL || hideTime > _timeStep);
    }

 private:
    /*!
     * \brief Create QT text document
     * \return QT text document
     */
    QTextDocument *createDocument() const;
};

/*!
 * \brief Footage subtitle database
 */
struct FootageSubs
{
    const std::string &footageName;  //!< Footage name
    const uint64_t &footageId;       //!< Footage ID

    std::list<Subs *> subs;  //!< Subtitle items list

    QString pathAudioFile;  //!< Audio file for current footage

    /*!
     * \brief Constructor
     * \param _footageName Footage name
     * \param _footageId Footage ID
     */
    FootageSubs(const std::string &_footageName, const uint64_t &_footageId);

    virtual ~FootageSubs();  //!< Destructor

    /*!
     * \brief Add subtitle
     * \param _showTime Show time in ms
     * \param _hideTime Hide time in ms
     * \param _textHtml Subtitle text
     * \param _textRead Speech text for TTS engine
     * \return Created item
     */
    Subs *add(const uint64_t _showTime, const uint64_t _hideTime, const QString &_textHtml, const QString &_textRead);

    /*!
     * \brief Add subtitle
     * \param _showTime Show time in ms
     * \param _textHtml Subtitle text
     * \param _textRead Speech text for TTS engine
     * \return Created item
     */
    inline Subs *add(const uint64_t _showTime, const QString &_textHtml, const QString &_textRead)
    {
        return add(_showTime, 0UL, _textHtml, _textRead);
    }

    /*!
     * \brief Add subtitle
     * \param _showTime Show time in ms
     * \param _hideTime Hide time in ms
     * \param _textHtml Subtitle and speech text
     * \return Created item
     */
    inline Subs *add(const uint64_t _showTime, const uint64_t _hideTime, const QString &_textHtml)
    {
        return add(_showTime, _hideTime, _textHtml, _textHtml);
    }

    /*!
     * \brief Add subtitle
     * \param _showTime Show time in ms
     * \param _textHtml Subtitle and speech text
     * \return Created item
     */
    inline Subs *add(const uint64_t _showTime, const QString &_textHtml)
    {
        return add(_showTime, 0UL, _textHtml, _textHtml);
    }

    /*!
     * \brief Initialize subtitle database
     * \param _duration Total footage duration in ms
     * \return Success flag
     */
    bool initialize(const uint64_t _duration);

    /*!
     * \brief Paint subtitles at given time
     * \param _painter Painter
     * \param _timeStep Time-step
     */
    void paint(QPainter *_painter, const uint64_t _timeStep) const;

    /*!
     * \brief Create HTML text
     * \return HTML text
     */
    QString toHtml() const;
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_SUBS_H
