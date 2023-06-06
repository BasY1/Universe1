#ifndef UNIVERSE1_VIDEO_MAINWINDOW_H
#define UNIVERSE1_VIDEO_MAINWINDOW_H

#include "../video/footage.h"

#include <QFileInfo>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QScreen>
#include <QScrollArea>
#include <QSettings>
#include <QSlider>
#include <QSpinBox>
#include <QSplitter>
#include <QToolBar>
#include <QToolButton>
#include <QTreeWidget>

#include <QMediaPlayer>

namespace Universe1 {
namespace Video {

/*! \brief View for single frame image from video */
class View : public QWidget
{
    Q_OBJECT

    QImage m_image;       //!< Image data
    qreal m_scale = 0.5;  //!< Scale factor

 public:
    /*!
     * \brief Constructor
     * \param parent Parent widget
     */
    View(QWidget *parent = nullptr);

 public slots:
    /*!
     * \brief Setup new image
     * \param _image New image
     */
    void setImage(const QImage &_image);

    /*!
     * \brief Set new scale factor
     * \param _value New scale factor
     */
    void setScale(qreal _value);

 protected:
    /*!
     * \brief Paint event override
     * \param event Event data
     */
    void paintEvent(QPaintEvent *event) override;
};

/*! \brief Main window for video presentation GUI
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    const Config &m_cfg;                     //!< Video configuration data
    const std::list<Footage *> &m_footages;  //!< Video footage sequence
    const int m_totalDuration;               //!< Total video duration in ms
    const int m_totalFrames;                 //!< Total video frame count

    View *m_view;             //!< Main image view
    QScrollArea *m_viewArea;  //!< Main image view scroll area

    QTreeWidget *m_info;  //!< Current frame info tree widget

    QSplitter *m_splitter;  //!< Horizontal splitter

    QSlider *m_curFrameSlider1;  //!< Bottom long slider for current frame
    QSlider *m_curFrameSlider2;  //!< Top shorter slider for current frame
    QSpinBox *m_curFrameBox;     //!< Current frame spin box

    QSlider *m_zoomSlider;  //!< Slider for zoom image

    QToolButton *m_createVideo;  //!< Create video checker

    QToolButton *m_expand;  //!< Expand all info tree checker

    QToolButton *m_playBut;  //!< Play current audio

    QToolButton *m_next1;  //!< Next frame
    QToolButton *m_prev1;  //!< Previous frame

    QToolButton *m_next10;  //!< Next 10 frames
    QToolButton *m_prev10;  //!< Previous 10 frames

    QToolButton *m_nextSubs;  //!< Next subtitle frame
    QToolButton *m_prevSubs;  //!< Previous subtitle frame

    QToolButton *m_nextFootage;  //!< Next footage frame
    QToolButton *m_prevFootage;  //!< Previous footage frame

    QToolButton *m_first;  //!< First frame
    QToolButton *m_last;   //!< Last frame

    QMediaPlayer *m_player = nullptr;  //!< Current audio playing

    QString m_curAudio;  //!< Current audio file path

 public:
    /*!
     * \brief Constructor
     * \param _footages Video footage sequence
     * \param _totalDuration Total video duration in ms
     * \param _totalFrames Total video frame count
     * \param parent Parent widget
     */
    MainWindow(const std::list<Universe1::Video::Footage *> &_footages,
               const uint64_t _totalDuration,
               const uint64_t _totalFrames,
               QWidget *parent = nullptr);

    ~MainWindow();  //!< Destructor

    /*!
     * \brief Test for create video checked
     * \return create video checked state
     */
    inline bool createVideo() const
    {
        return m_createVideo->isChecked();
    }

 protected slots:
    /*!
     * \brief Zoom changed handler
     * \param _value New zoom scale index
     */
    void changedZoom(int _value);
    /*!
     * \brief Frame changed handler
     * \param _value New frame ID
     */
    void changedFrame(int _value);

    /*!
     * \brief Info tree item double clicked
     * \param _item Tree item
     * \param _column Tree item's column index
     */
    void itemDoubleClicked(QTreeWidgetItem *_item, int _column);

    /*!
     * \brief Audio play state changed handler
     * \param newState New audio player state
     */
    void audioChanged(QMediaPlayer::State newState);

    void playSubs();  //!< Play current subtitle file

    void jumpNext1();  //!< Jump to next frame handler
    void jumpPrev1();  //!< Jump to previous frame handler

    void jumpNext10();  //!< Jump to next 10 frames handler
    void jumpPrev10();  //!< Jump to previous 10 frames handler

    void jumpNextSubs();  //!< Jump to next subtitle frame handler
    void jumpPrevSubs();  //!< Jump to previous subtitle frame handler

    void jumpNextFootage();  //!< Jump to next footage frame handler
    void jumpPrevFootage();  //!< Jump to previous footage frame handler

    void jumpFirst();  //!< Jump to first frame
    void jumpLast();   //!< Jump to last frame
};

}  // namespace Video
}  // namespace Universe1

#endif  // UNIVERSE1_VIDEO_MAINWINDOW_H
