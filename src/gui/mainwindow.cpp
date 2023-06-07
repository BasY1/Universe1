#include "mainwindow.h"

Universe1::Video::View::View(QWidget *parent)
    : QWidget(parent)
{
}

void Universe1::Video::View::setImage(const QImage &_image)
{
    m_image = _image;
    update();
}

void Universe1::Video::View::setScale(qreal _value)
{
    m_scale = _value;
    update();
}

void Universe1::Video::View::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.scale(m_scale, m_scale);
    p.drawImage(QPoint(0, 0), m_image);
}

Universe1::Video::MainWindow::MainWindow(const std::list<Universe1::Video::Footage *> &_footages,
                                         const uint64_t _totalDuration,
                                         const uint64_t _totalFrames,
                                         QWidget *parent)
    : QMainWindow(parent)
    , m_cfg(Config::cfg())
    , m_footages(_footages)
    , m_totalDuration(_totalDuration)
    , m_totalFrames(_totalFrames)
{
    m_view = new View();
    m_view->setMinimumSize(qreal(m_cfg.widthScreen) * 0.5 / screen()->devicePixelRatio() + 0.01,
                           qreal(m_cfg.heightScreen) * 0.5 / screen()->devicePixelRatio() + 0.01);

    m_viewArea = new QScrollArea();
    m_viewArea->setWidget(m_view);
    m_viewArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_viewArea->setAlignment(Qt::AlignCenter);

    m_info = new QTreeWidget();
    m_info->setColumnCount(3);
    m_info->setHeaderLabels({tr("Name"), tr("Frames"), tr("Duration")});
    m_info->setColumnWidth(0, QSettings().value("MainWindow__m_info_0", 100).toInt());
    m_info->setColumnWidth(1, QSettings().value("MainWindow__m_info_1", 100).toInt());
    connect(m_info, &QTreeWidget::itemDoubleClicked, this, &MainWindow::itemDoubleClicked);

    m_splitter = new QSplitter(Qt::Horizontal);
    m_splitter->addWidget(m_viewArea);
    m_splitter->addWidget(m_info);
    m_splitter->restoreState(QSettings().value("MainWindow__m_splitter").toByteArray());

    m_curFrameSlider1 = new QSlider(Qt::Horizontal);
    m_curFrameSlider1->setRange(0, m_totalFrames - 1);
    m_curFrameSlider1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(m_curFrameSlider1, &QSlider::valueChanged, this, &MainWindow::changedFrame);

    QGridLayout *lay = new QGridLayout();
    lay->addWidget(m_splitter, 0, 0);
    lay->addWidget(m_curFrameSlider1, 0, 1);

    QWidget *widMain = new QWidget();
    widMain->setLayout(lay);
    setCentralWidget(widMain);

    //

    m_curFrameSlider2 = new QSlider(Qt::Horizontal);
    m_curFrameSlider2->setRange(0, m_totalFrames - 1);
    m_curFrameSlider2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    connect(m_curFrameSlider2, &QSlider::valueChanged, this, &MainWindow::changedFrame);

    m_curFrameBox = new QSpinBox();
    m_curFrameBox->setRange(0, m_totalFrames - 1);
    connect(m_curFrameBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changedFrame);

    m_zoomSlider = new QSlider(Qt::Horizontal);
    m_zoomSlider->setToolTip(tr("Zoom"));
    m_zoomSlider->setRange(1, 5);
    m_zoomSlider->setValue(QSettings().value("MainWindow__m_zoom", 3).toInt());
    m_zoomSlider->setTickPosition(QSlider::TicksAbove);
    m_zoomSlider->setTickInterval(1);
    m_zoomSlider->setMinimumWidth(100);
    m_zoomSlider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(m_zoomSlider, &QSlider::valueChanged, this, &MainWindow::changedZoom);

    m_createVideo = new QToolButton();
    m_createVideo->setCheckable(true);
    m_createVideo->setIcon(QIcon::fromTheme("document-save"));
    m_createVideo->setToolTip(tr("Create video"));

    m_expand = new QToolButton();
    m_expand->setCheckable(true);
    m_expand->setChecked(QSettings().value("MainWindow__m_expand").toBool());
    m_expand->setIcon(QIcon::fromTheme("dialog-information"));
    m_expand->setToolTip(tr("Expand info tree"));

    m_playBut = new QToolButton();
    m_playBut->setIcon(QIcon::fromTheme("media-playback-start"));
    m_playBut->setToolTip(tr("Play speech"));
    connect(m_playBut, &QToolButton::clicked, this, &MainWindow::playSubs);

    m_next1 = new QToolButton();
    m_next1->setIcon(QIcon::fromTheme("go-next"));
    m_next1->setToolTip(tr("Next frame"));
    connect(m_next1, &QToolButton::clicked, this, &MainWindow::jumpNext1);

    m_prev1 = new QToolButton();
    m_prev1->setIcon(QIcon::fromTheme("go-previous"));
    m_prev1->setToolTip(tr("Previous frame"));
    connect(m_prev1, &QToolButton::clicked, this, &MainWindow::jumpPrev1);

    m_next10 = new QToolButton();
    m_next10->setIcon(QIcon::fromTheme("object-rotate-left"));
    m_next10->setToolTip(tr("Next 10 frames"));
    connect(m_next10, &QToolButton::clicked, this, &MainWindow::jumpNext10);

    m_prev10 = new QToolButton();
    m_prev10->setIcon(QIcon::fromTheme("object-rotate-right"));
    m_prev10->setToolTip(tr("Previous 10 frames"));
    connect(m_prev10, &QToolButton::clicked, this, &MainWindow::jumpPrev10);

    m_nextSubs = new QToolButton();
    m_nextSubs->setIcon(QIcon::fromTheme("go-last"));
    m_nextSubs->setToolTip(tr("Next subtitle"));
    connect(m_nextSubs, &QToolButton::clicked, this, &MainWindow::jumpNextSubs);

    m_prevSubs = new QToolButton();
    m_prevSubs->setIcon(QIcon::fromTheme("go-first"));
    m_prevSubs->setToolTip(tr("Previous subtitle"));
    connect(m_prevSubs, &QToolButton::clicked, this, &MainWindow::jumpPrevSubs);

    m_nextFootage = new QToolButton();
    m_nextFootage->setIcon(QIcon::fromTheme("go-up"));
    m_nextFootage->setToolTip(tr("Next footage"));
    connect(m_nextFootage, &QToolButton::clicked, this, &MainWindow::jumpNextFootage);

    m_prevFootage = new QToolButton();
    m_prevFootage->setIcon(QIcon::fromTheme("go-down"));
    m_prevFootage->setToolTip(tr("Previous footage"));
    connect(m_prevFootage, &QToolButton::clicked, this, &MainWindow::jumpPrevFootage);

    m_first = new QToolButton();
    m_first->setIcon(QIcon::fromTheme("go-bottom"));
    m_first->setToolTip(tr("Next frame"));
    connect(m_first, &QToolButton::clicked, this, &MainWindow::jumpFirst);

    m_last = new QToolButton();
    m_last->setIcon(QIcon::fromTheme("go-top"));
    m_last->setToolTip(tr("Previous frame"));
    connect(m_last, &QToolButton::clicked, this, &MainWindow::jumpLast);

    QToolBar *toolBar = addToolBar("toolBar");
    toolBar->setFloatable(false);
    toolBar->setMovable(false);

    toolBar->addWidget(m_createVideo);
    toolBar->addWidget(m_expand);
    toolBar->addSeparator();
    toolBar->addWidget(m_playBut);
    toolBar->addSeparator();
    toolBar->addWidget(m_zoomSlider);
    toolBar->addSeparator();
    toolBar->addWidget(m_first);
    toolBar->addWidget(m_prevFootage);
    toolBar->addWidget(m_prevSubs);
    toolBar->addWidget(m_prev10);
    toolBar->addWidget(m_prev1);
    toolBar->addWidget(m_next1);
    toolBar->addWidget(m_next10);
    toolBar->addWidget(m_nextSubs);
    toolBar->addWidget(m_nextFootage);
    toolBar->addWidget(m_last);
    toolBar->addSeparator();
    toolBar->addWidget(m_curFrameSlider2);
    toolBar->addWidget(m_curFrameBox);

    changedZoom(m_zoomSlider->value());
    changedFrame(0);
}

Universe1::Video::MainWindow::~MainWindow()
{
    QSettings().setValue("MainWindow__m_splitter", m_splitter->saveState());
    QSettings().setValue("MainWindow__m_zoom", m_zoomSlider->value());
    QSettings().setValue("MainWindow__m_expand", m_expand->isChecked());
    QSettings().setValue("MainWindow__m_info_0", m_info->columnWidth(0));
    QSettings().setValue("MainWindow__m_info_1", m_info->columnWidth(1));
}

void Universe1::Video::MainWindow::changedZoom(int _value)
{
    static const qreal _delta = 0.01;
    qreal mult = 1.0;
    switch (_value)
    {
    case 1: mult = 0.5; break;
    case 2: mult = 0.75; break;
    case 4: mult = 1.5; break;
    case 5: mult = 2.0; break;
    default: break;
    }
    m_view->resize(qreal(m_cfg.widthScreen) * mult / screen()->devicePixelRatio() + _delta,
                   qreal(m_cfg.heightScreen) * mult / screen()->devicePixelRatio() + _delta);
    m_view->setScale(mult / screen()->devicePixelRatio());

    m_zoomSlider->setToolTip(tr("Zoom: x%1 ").arg(mult));
}

inline static QString mkTime(const int _durationMS)
{
    const QTime t = QTime::fromMSecsSinceStartOfDay(_durationMS);
    if (t.hour() > 0)
        return t.toString("h:mm:ss.zzz");
    return t.toString("mm:ss.zzz");
}

inline static QString mkTime(const int _frames, const int _frameDuration)
{
    const QTime t = QTime::fromMSecsSinceStartOfDay(_frames * _frameDuration);
    if (t.hour() > 0)
        return t.toString("h:mm:ss.zzz");
    return t.toString("mm:ss.zzz");
}

void Universe1::Video::MainWindow::changedFrame(int _value)
{
    using namespace Universe1::Video;

    disconnect(m_curFrameSlider1, &QSlider::valueChanged, this, &MainWindow::changedFrame);
    disconnect(m_curFrameSlider2, &QSlider::valueChanged, this, &MainWindow::changedFrame);
    disconnect(m_curFrameBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changedFrame);

    m_curFrameSlider1->setValue(_value);
    m_curFrameSlider2->setValue(_value);
    m_curFrameBox->setValue(_value);

    connect(m_curFrameSlider1, &QSlider::valueChanged, this, &MainWindow::changedFrame);
    connect(m_curFrameSlider2, &QSlider::valueChanged, this, &MainWindow::changedFrame);
    connect(m_curFrameBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::changedFrame);

    m_curAudio.clear();

    int frameFirst = 0;
    std::list<Universe1::Video::Footage *>::const_iterator it1 = m_footages.cbegin();
    for (; it1 != m_footages.cend(); ++it1)
    {
        const Footage *footage = (*it1);
        const int frameFirstNext = frameFirst + static_cast<int>(footage->framesCount);
        if (frameFirstNext <= _value)
        {
            frameFirst = frameFirstNext;
            continue;
        }

        const int frameDur = m_cfg.frameDuration;
        const int frame = _value - frameFirst;
        const int timeStep = frame * m_cfg.frameDuration;
        const uint64_t ts = timeStep;

        QImage image;
        if (footage->getImage3D(image, ts))
        {
            QPainter painter(&image);
            footage->paint2D(&painter, ts);
            footage->paintSubs(&painter, ts);
            footage->paint2DPost(&painter, ts);
        }

        m_view->setImage(image);

        while (m_info->topLevelItemCount() >= 1)
            delete m_info->takeTopLevelItem(0);

        QTreeWidgetItem *tmp1 = nullptr;
        QTreeWidgetItem *root =
            new QTreeWidgetItem(m_info, {tr("Total"), QString::number(m_totalFrames), mkTime(m_totalFrames, frameDur)});
        root->setToolTip(2, QString::number(m_totalFrames * frameDur) + tr("ms"));
        root->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        root = new QTreeWidgetItem(m_info, {tr("Current"), QString::number(_value), mkTime(_value, frameDur)});
        root->setToolTip(2, QString::number(_value * frameDur) + tr("ms"));
        root->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        {
            const QVector3D camPos = footage->camera.pos.getValue(ts);
            const QVector3D camEye = footage->camera.lookAt.getValue(ts);
            root = new QTreeWidgetItem(m_info,
                                       {tr("Camera"),
                                        QString::number(camPos.x()) + " x " + QString::number(camPos.y()) + " x " +
                                            QString::number(camPos.z()),
                                        QString()});
            root->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            tmp1 = new QTreeWidgetItem(root,
                                       {tr("Look at"),
                                        QString::number(camEye.x()) + " x " + QString::number(camEye.y()) + " x " +
                                            QString::number(camEye.z()),
                                        QString()});
            tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
            if (ts == 0UL)
            {
                if (it1 != m_footages.cbegin())
                {
                    std::list<Universe1::Video::Footage *>::const_iterator it2 = it1;
                    it2--;
                    const Footage *footagePrev = (*it2);
                    const uint64_t tsPrev = footagePrev->duration - m_cfg.frameDuration;
                    const QVector3D camPosPrev = footagePrev->camera.pos.getValue(tsPrev);
                    const float distPrev = camPosPrev.distanceToPoint(camPos);

                    if (!qFuzzyIsNull(distPrev))
                    {
                        tmp1 = new QTreeWidgetItem(root,
                                                   {tr("Previous"),
                                                    QString::number(camPosPrev.x()) + " x " +
                                                        QString::number(camPosPrev.y()) + " x " +
                                                        QString::number(camPosPrev.z()),
                                                    QString::number(distPrev)});
                        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    }
                }

                {
                    const QVector3D camPosNext = footage->camera.pos.getValue(ts + m_cfg.frameDuration);
                    const float distNext = camPosNext.distanceToPoint(camPos);
                    if (!qFuzzyIsNull(distNext))
                    {
                        tmp1 = new QTreeWidgetItem(root,
                                                   {tr("Next"),
                                                    QString::number(camPosNext.x()) + " x " +
                                                        QString::number(camPosNext.y()) + " x " +
                                                        QString::number(camPosNext.z()),
                                                    QString::number(distNext)});
                        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    }
                }
            }
            else if (ts >= footage->duration - m_cfg.frameDuration)
            {
                const QVector3D camPosPrev = footage->camera.pos.getValue(ts - m_cfg.frameDuration);
                const float distPrev = camPosPrev.distanceToPoint(camPos);
                if (!qFuzzyIsNull(distPrev))
                {
                    tmp1 =
                        new QTreeWidgetItem(root,
                                            {tr("Previous"),
                                             QString::number(camPosPrev.x()) + " x " + QString::number(camPosPrev.y()) +
                                                 " x " + QString::number(camPosPrev.z()),
                                             QString::number(distPrev)});
                    tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }

                std::list<Universe1::Video::Footage *>::const_iterator it2 = it1;
                it2++;
                if (it2 != m_footages.cend())
                {
                    const QVector3D camPosNext = (*it2)->camera.pos.getValue(0);
                    const float distNext = camPosNext.distanceToPoint(camPos);
                    if (!qFuzzyIsNull(distNext))
                    {
                        tmp1 = new QTreeWidgetItem(root,
                                                   {tr("Next"),
                                                    QString::number(camPosNext.x()) + " x " +
                                                        QString::number(camPosNext.y()) + " x " +
                                                        QString::number(camPosNext.z()),
                                                    QString::number(distNext)});
                        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    }
                }
            }
            else
            {
                const QVector3D camPosPrev = footage->camera.pos.getValue(ts - m_cfg.frameDuration);
                const QVector3D camPosNext = footage->camera.pos.getValue(ts + m_cfg.frameDuration);
                const float distPrev = camPosPrev.distanceToPoint(camPos);
                const float distNext = camPosNext.distanceToPoint(camPos);
                if (!qFuzzyIsNull(distPrev))
                {
                    tmp1 =
                        new QTreeWidgetItem(root,
                                            {tr("Previous"),
                                             QString::number(camPosPrev.x()) + " x " + QString::number(camPosPrev.y()) +
                                                 " x " + QString::number(camPosPrev.z()),
                                             QString::number(distPrev)});
                    tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }

                if (!qFuzzyIsNull(distNext))
                {
                    tmp1 =
                        new QTreeWidgetItem(root,
                                            {tr("Next"),
                                             QString::number(camPosNext.x()) + " x " + QString::number(camPosNext.y()) +
                                                 " x " + QString::number(camPosNext.z()),
                                             QString::number(distNext)});
                    tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }
            }
        }

        root = new QTreeWidgetItem(m_info,
                                   {QString::fromStdString(footage->footageName),
                                    QString::number(footage->framesCount),
                                    mkTime(footage->framesCount, frameDur)});
        root->setToolTip(2, QString::number(footage->framesCount * frameDur) + tr("ms"));
        root->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        tmp1 = new QTreeWidgetItem(root, {tr("Current"), QString::number(frame), mkTime(frame, frameDur)});
        tmp1->setToolTip(2, QString::number(frame * frameDur) + tr("ms"));
        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        tmp1 = new QTreeWidgetItem(root, {tr("Subtitles"), QString::number(footage->subs.subs.size()), ""});
        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        for (const Subs *i : footage->subs.subs)
        {
            if (i->isCurrent(ts))
            {
                QTreeWidgetItem *tmp2 =
                    new QTreeWidgetItem(tmp1, {tr("Visible"), mkTime(i->showTime), mkTime(i->hideTime)});
                tmp2->setToolTip(1, QString::number(i->showTime) + tr("ms"));
                tmp2->setToolTip(2, QString::number(i->hideTime) + tr("ms"));
                tmp2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                tmp2 = new QTreeWidgetItem(tmp1,
                                           {tr("Duration"),
                                            mkTime(i->hideTime - i->showTime),
                                            QString::number(i->hideTime - i->showTime) + tr("ms")});
                tmp2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                tmp2 = new QTreeWidgetItem(
                    tmp1, {tr("Audio file"), QFileInfo(i->pathAudio).fileName(), mkTime(i->audioDuration)});
                tmp2->setToolTip(2, QString::number(i->audioDuration) + tr("ms"));
                tmp2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                tmp2->setData(0, Qt::UserRole, i->pathAudio);
                tmp1->setExpanded(true);
                m_curAudio = i->pathAudio;

                break;
            }
            if (i->showTime > ts)
                break;
        }

        tmp1 = new QTreeWidgetItem(root, {tr("Items 2D"), QString::number(footage->text2D.items.size()), ""});
        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        for (const std::pair<const Qt::Alignment, std::list<Item2D *>> &i2d : footage->text2D.items)
        {
            for (const Item2D *i : i2d.second)
            {
                if (i->visible.getValue(ts))
                {
                    QTreeWidgetItem *tmp2 =
                        new QTreeWidgetItem(tmp1, {QString::fromStdString(i->name), i->text.text.getValue(ts), ""});
                    tmp2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                    QTreeWidgetItem *tmp3 = new QTreeWidgetItem(
                        tmp2, {tr("Align"), QString::number(i2d.first), QString::number(i->text.align.getValue(ts))});
                    tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                    tmp3 = new QTreeWidgetItem(tmp2,
                                               {tr("Text size"), QString::number(i->text.sizeMult.getValue(ts)), ""});
                    tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                    const QColor col = i->textColor.getValue(ts);
                    tmp3 = new QTreeWidgetItem(tmp2, {tr("Color"), col.name(QColor::HexArgb), ""});
                    tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                    tmp3->setBackground(2, col);
                }
            }
        }

        for (const Item2DImage *ip : footage->image2D.images)
        {
            if (ip->visible.getValue(ts))
            {
                QTreeWidgetItem *tmp2 = new QTreeWidgetItem(tmp1, {QString::fromStdString(ip->name), "", ""});
                tmp2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                QTreeWidgetItem *tmp3 = new QTreeWidgetItem(tmp2, {tr("Text"), ip->text.text.getValue(ts), QString()});
                tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                tmp3 = new QTreeWidgetItem(
                    tmp2,
                    {tr("Size"),
                     QString::number(ip->sizeX.getValue(ts)) + " x " + QString::number(ip->sizeY.getValue(ts)),
                     QString()});
                tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                tmp3 = new QTreeWidgetItem(
                    tmp2,
                    {tr("Position"),
                     QString::number(ip->positionX.getValue(ts)) + " x " + QString::number(ip->positionY.getValue(ts)),
                     QString()});
                tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                tmp3 =
                    new QTreeWidgetItem(tmp2, {tr("Text size"), QString::number(ip->text.sizeMult.getValue(ts)), ""});
                tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                const QColor col = ip->textColor.getValue(ts);
                tmp3 = new QTreeWidgetItem(tmp2, {tr("Color"), col.name(QColor::HexArgb), ""});
                tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                tmp3->setBackground(2, col);
            }
        }

        tmp1->setExpanded(true);

        tmp1 = new QTreeWidgetItem(root, {tr("Items 3D"), QString::number(footage->items.size()), ""});
        tmp1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        for (const Item3D *i : footage->items)
        {
            if (i->visible.getValue(ts))
            {
                const size_t cutLen = i->name.length() + 1UL;
                QTreeWidgetItem *tmp2 = new QTreeWidgetItem(tmp1, {QString::fromStdString(i->name), "", ""});
                tmp2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

                for (const DynamicProperty *prop : i->props)
                {
                    QTreeWidgetItem *tmp3 = new QTreeWidgetItem(
                        tmp2, {QString::fromStdString(prop->name.substr(cutLen)), prop->getValueText(ts), ""});
                    switch (prop->type)
                    {
                    case DynamicProperty::_BOOL: tmp3->setText(2, tr("Boolean")); break;
                    case DynamicProperty::_VALUE: tmp3->setText(2, tr("Value")); break;
                    case DynamicProperty::_ENUM: tmp3->setText(2, tr("Enum")); break;
                    case DynamicProperty::_TEXT: tmp3->setText(2, tr("Text")); break;
                    case DynamicProperty::_VEC3: tmp3->setText(2, tr("Vector 3D")); break;
                    case DynamicProperty::_COLOR: tmp3->setText(2, tr("Color")); break;
                    }
                    tmp3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
                }
            }
        }

        tmp1->setExpanded(true);
        root->setExpanded(true);

        if (m_expand->isChecked())
            m_info->expandAll();

        return;
    }
}

void Universe1::Video::MainWindow::itemDoubleClicked(QTreeWidgetItem *_item, int)
{
    if (m_player != nullptr)
        return;

    if (_item->data(0, Qt::UserRole).isValid())
    {
        m_player = new QMediaPlayer();
        m_player->setMedia(QUrl::fromLocalFile(_item->data(0, Qt::UserRole).toString()));
        m_player->setVolume(50);
        m_player->play();
        connect(m_player, &QMediaPlayer::stateChanged, this, &MainWindow::audioChanged);
    }
}

void Universe1::Video::MainWindow::audioChanged(QMediaPlayer::State _state)
{
    switch (_state)
    {
    case QMediaPlayer::StoppedState:
        disconnect(m_player, &QMediaPlayer::stateChanged, this, &MainWindow::audioChanged);
        m_player->deleteLater();
        m_player = nullptr;
        break;
    case QMediaPlayer::PlayingState: break;
    case QMediaPlayer::PausedState: break;
    }
}

void Universe1::Video::MainWindow::playSubs()
{
    if (m_player != nullptr || m_curAudio.isEmpty())
        return;

    m_player = new QMediaPlayer();
    m_player->setMedia(QUrl::fromLocalFile(m_curAudio));
    m_player->setVolume(50);
    m_player->play();
    connect(m_player, &QMediaPlayer::stateChanged, this, &MainWindow::audioChanged);
}

void Universe1::Video::MainWindow::jumpNextSubs()
{
    using namespace Universe1::Video;

    const int curValue = m_curFrameBox->value();
    int frameFirst = 0;

    std::list<Universe1::Video::Footage *>::const_iterator it1 = m_footages.cbegin();
    for (; it1 != m_footages.cend(); ++it1)
    {
        int frameFirstNext = frameFirst + static_cast<int>((*it1)->framesCount);
        if (frameFirstNext <= curValue)
        {
            frameFirst = frameFirstNext;
            continue;
        }

        const int frame = curValue - frameFirst;
        const int timeStep = frame * m_cfg.frameDuration;
        const uint64_t ts = timeStep;

        std::list<Subs *>::const_iterator it2 = (*it1)->subs.subs.cbegin();
        for (; it2 != (*it1)->subs.subs.cend(); ++it2)
        {
            if ((*it2)->showTime > ts)
            {
                changedFrame(frameFirst + (*it2)->showTime / m_cfg.frameDuration);
                return;
            }

            if ((*it2)->isCurrent(ts))
            {
                ++it2;
                if (it2 != (*it1)->subs.subs.cend())
                {
                    changedFrame(frameFirst + (*it2)->showTime / m_cfg.frameDuration);
                }
                else
                {
                    ++it1;
                    frameFirst = frameFirstNext;
                    while (it1 != m_footages.cend() && (*it1)->subs.subs.empty())
                    {
                        frameFirst += static_cast<int>((*it1)->framesCount);
                        ++it1;
                    }
                    if (it1 != m_footages.cend() && !(*it1)->subs.subs.empty())
                        changedFrame(frameFirst + (*it1)->subs.subs.front()->showTime / m_cfg.frameDuration);
                }
                return;
            }
        }
    }
}

void Universe1::Video::MainWindow::jumpPrevSubs()
{
    using namespace Universe1::Video;

    const int curValue = m_curFrameBox->value();
    int frameFirst = 0;

    std::list<Universe1::Video::Footage *>::const_iterator it1 = m_footages.cbegin();
    for (; it1 != m_footages.cend(); ++it1)
    {
        const int frameFirstNext = frameFirst + static_cast<int>((*it1)->framesCount);
        if (frameFirstNext <= curValue)
        {
            frameFirst = frameFirstNext;
            continue;
        }

        const int frame = curValue - frameFirst;
        const int timeStep = frame * m_cfg.frameDuration;
        const uint64_t ts = timeStep;

        std::list<Subs *>::const_iterator it2 = (*it1)->subs.subs.cbegin();
        for (; it2 != (*it1)->subs.subs.cend(); ++it2)
        {
            if ((*it2)->isCurrent(ts))
            {
                if (it2 != (*it1)->subs.subs.cbegin())
                {
                    --it2;
                    changedFrame(frameFirst + (*it2)->showTime / m_cfg.frameDuration);
                }
                else if (it1 != m_footages.cbegin())
                {
                    --it1;
                    frameFirst -= static_cast<int>((*it1)->framesCount);

                    while (it1 != m_footages.cbegin() && (*it1)->subs.subs.empty())
                    {
                        --it1;
                        frameFirst -= static_cast<int>((*it1)->framesCount);
                    }

                    if (!(*it1)->subs.subs.empty())
                        changedFrame(frameFirst + (*it1)->subs.subs.back()->showTime / m_cfg.frameDuration);
                }
                return;
            }
        }
    }
}

void Universe1::Video::MainWindow::jumpNextFootage()
{
    using namespace Universe1::Video;

    const int curValue = m_curFrameBox->value();
    int frameFirst = 0;

    std::list<Universe1::Video::Footage *>::const_iterator it1 = m_footages.cbegin();
    for (; it1 != m_footages.cend(); ++it1)
    {
        int frameFirstNext = frameFirst + static_cast<int>((*it1)->framesCount);
        if (frameFirstNext <= curValue)
        {
            frameFirst = frameFirstNext;
            continue;
        }

        ++it1;
        if (it1 != m_footages.cend())
            changedFrame(frameFirstNext);
        return;
    }
}

void Universe1::Video::MainWindow::jumpPrevFootage()
{
    using namespace Universe1::Video;

    const int curValue = m_curFrameBox->value();
    int frameFirst = 0;

    std::list<Universe1::Video::Footage *>::const_iterator it1 = m_footages.cbegin();
    for (; it1 != m_footages.cend(); ++it1)
    {
        int frameFirstNext = frameFirst + static_cast<int>((*it1)->framesCount);
        if (frameFirstNext <= curValue)
        {
            frameFirst = frameFirstNext;
            continue;
        }

        if (it1 != m_footages.cbegin())
        {
            --it1;
            changedFrame(frameFirst - static_cast<int>((*it1)->framesCount));
        }
        else
            changedFrame(0);
        return;
    }
}

void Universe1::Video::MainWindow::jumpFirst()
{
    changedFrame(0);
}
void Universe1::Video::MainWindow::jumpLast()
{
    changedFrame(m_totalFrames - 1);
}

void Universe1::Video::MainWindow::jumpNext1()
{
    const int curValue = m_curFrameBox->value() + 1;
    if (curValue < m_totalFrames)
        changedFrame(curValue);
}

void Universe1::Video::MainWindow::jumpPrev1()
{
    const int curValue = m_curFrameBox->value() - 1;
    if (curValue >= 0)
        changedFrame(curValue);
}

void Universe1::Video::MainWindow::jumpNext10()
{
    const int curValue = m_curFrameBox->value() + 10;
    if (curValue < m_totalFrames)
        changedFrame(curValue);
    else
        changedFrame(m_totalFrames - 1);
}

void Universe1::Video::MainWindow::jumpPrev10()
{
    const int curValue = m_curFrameBox->value() - 10;
    if (curValue >= 0)
        changedFrame(curValue);
    else
        changedFrame(0);
}
