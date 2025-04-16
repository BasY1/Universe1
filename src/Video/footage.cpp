/*!
 * \file src/Video/footage.cpp
 * \brief Video footage
 */

#include "footage.h"

#include "../Data3D/shaders.h"

#include "../Items/Items2D/item2dtext.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

#include <QOffscreenSurface>
#include <QOpenGLFramebufferObject>

namespace U1 {
namespace Video {

Footage::Footage(const std::string &_name)
    : Props::ItemPropertyGroup(_name)
    , Audio::FootageAudio()
    , cameraPosition("cameraPosition", {1, -4, 2})
    , cameraLookAt("cameraLookAt")
    , cameraUp("cameraUp", Math::Vec3F::unitZ())
    , cameraFieldOfView("cameraFieldOfView", 90.0f, 5.0, 175.0f)
    , cameraNearPlane("cameraNearPlane", 0.001f, 0.00001f, std::numeric_limits<float>::max())
    , cameraFarPlane("cameraFarPlane", 10000.0f, 0.1f, std::numeric_limits<float>::max())
    , bgColor("bgColor", QColor{0U, 0U, 0U, 255U})
    , lightColor("lightColor", QColor{255, 255, 255})
    , lightDirection("lightDirection", -Math::Vec3F::unitZ())
    , lightAmbient("lightAmbient", 0.75f, 0.0f, 1.0f)
{
    setupProperties({&cameraPosition,
                     &cameraLookAt,
                     &cameraUp,
                     &cameraFieldOfView,
                     &cameraNearPlane,
                     &cameraFarPlane,
                     &bgColor,
                     &lightColor,
                     &lightDirection,
                     &lightAmbient});
}

Footage::~Footage()
{
    for (Items::Item2D *i : m_items2D)
        delete i;
    for (Items::Item3D *i : m_items3D)
        delete i;
    for (Items::ItemCamera *i : m_cameras)
        delete i;
    for (Items::ClipPlane *i : m_clipPlanes)
        delete i;
}

size_t Footage::latestTimeStep() const
{
    return std::max(minimalFootageDuration,
                    std::max(Props::ItemPropertyGroup::latestTimeStep(), latestAudioTimeStep()));
}

Items::ClipPlane *Footage::addClipPlane(const Math::Vec3F &_center,
                                        const Math::Vec3F &_normal,
                                        const bool _enabled,
                                        const std::string &_name)
{
    if (m_clipPlanes.size() >= maxClipPlanes())
    {
        std::cerr << "Error: Footage::addClipPlane: Maximum " << maxClipPlanes() << " clip planes allowed!\n";
        return nullptr;
    }

    Items::ClipPlane *result = new Items::ClipPlane(_name, _center, _normal, _enabled);
    m_clipPlanes.push_back(result);
    addProperty(result);
    return result;
}

bool Footage::createVideo(const QString &_workDir,
                          const QString &_fileName,
                          const SettingsSubtitles &_settingsSubtitles,
                          const SettingsOpenGL &_settingsOpenGL,
                          const SettingsVideo &_settingsVideo,
                          const Audio::SettingsAudio &_settingsAudio) const
{
    const QDateTime tsStart = QDateTime::currentDateTime();

    if (!_settingsSubtitles.isValid() || !_settingsOpenGL.isValid() || !_settingsVideo.isValid() ||
        !_settingsAudio.isValid())
    {
        std::cout << "Footage[" << name << "]: Invalid settings!\n";
        return false;
    }

    const size_t duration = latestTimeStep();
    if (duration == 0UL)
    {
        std::cout << "Footage[" << name << "] empty !\n";
        return false;
    }

    if (QFile::exists(_fileName))
    {
        if (!QFile::remove(_fileName))
        {
            std::cerr << "Footage[" << name << "]: Can't overwrite/remove file:" << qPrintable(_fileName) << "!\n";
            return false;
        }
    }

    const QString wd = _workDir.endsWith(QDir::separator()) ? _workDir : (_workDir + QDir::separator());

    QDir(wd).removeRecursively();
    if (!QDir(wd).exists())
    {
        if (!QDir().mkpath(wd))
        {
            std::cerr << "Footage[" << name << "]: Can't create workDir:" << qPrintable(wd) << "!\n";
            return false;
        }
    }

    const QString audioFile = wd + "audio." + _settingsAudio.fileSuffix;
    if (!createAudio(_settingsAudio, wd + "audio" + QDir::separator(), audioFile, duration))
        return false;

    QStringList images;
    const size_t cntImages = 2UL + static_cast<size_t>(static_cast<float>(duration) / _settingsVideo.frameDuration);
    const QDateTime ts0 = QDateTime::currentDateTime();

    for (size_t frame = 0; frame < cntImages; ++frame)
    {
        const size_t ts = static_cast<size_t>(static_cast<float>(frame) * _settingsVideo.frameDuration);
        const QString fnImg = wd + "img_" + QString::number(frame) + "_." + _settingsVideo.imgSuffix;

        if (!createImageAt(fnImg, ts, _settingsSubtitles, _settingsOpenGL, _settingsVideo))
            return false;

        images.push_back(fnImg);

        const float doneMS = ts0.msecsTo(QDateTime::currentDateTime());
        const float totalMS = doneMS * float(cntImages) / float(frame + 1UL);
        const int waitMS = static_cast<int>(totalMS - doneMS);
        std::cout << "Footage[" << name << "] image: " << (frame + 1UL) << "/" << cntImages
                  << ", to wait: " << qPrintable(QTime::fromMSecsSinceStartOfDay(waitMS).toString()) << "\n";
        std::cout.flush();
    }

    const bool result = _settingsVideo.createVideo(_fileName, _settingsAudio, audioFile, images);
    const QDateTime tsEnd = QDateTime::currentDateTime();

    std::cout << "Footage[" << name << "] video in "
              << qPrintable(QTime::fromMSecsSinceStartOfDay(tsStart.msecsTo(tsEnd)).toString()) << "\n";
    std::cout.flush();

    return result;
}

// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Footage::createImageAt(const QString &_fileName,
                            const size_t _timeStep,
                            const SettingsSubtitles &_settingsSubtitles,
                            const SettingsOpenGL &_settingsOpenGL,
                            const SettingsVideo &_settingsVideo) const
{
    QSurfaceFormat surfaceFormat;
    surfaceFormat.setVersion(3, 3);
    if (_settingsOpenGL.useGlSamples > 0U)
        surfaceFormat.setSamples(_settingsOpenGL.useGlSamples);
    surfaceFormat.setDepthBufferSize(24);
    surfaceFormat.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);

    QOpenGLContext openGLContext;
    openGLContext.setFormat(surfaceFormat);
    openGLContext.create();
    if (!openGLContext.isValid())
    {
        std::cerr << "Footage[" << name << "]: Can't create OpenGL context!\n";
        return false;
    }

    QOffscreenSurface surface;
    surface.setFormat(surfaceFormat);
    surface.create();
    if (!surface.isValid())
    {
        std::cerr << "Footage[" << name << "]: Can't create OpenGL off-screen surface!\n";
        return false;
    }

    if (!openGLContext.makeCurrent(&surface))
    {
        std::cerr << "Footage[" << name << "]: Can't make OpenGL context current!\n";
        return false;
    }

    QOpenGLFramebufferObjectFormat fboFormat;
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    if (_settingsOpenGL.useGlSamples > 0U)
        fboFormat.setSamples(_settingsOpenGL.useGlSamples);

    QOpenGLFunctions *fun = openGLContext.functions();
    _settingsOpenGL.setupGL(fun);

    OpenGL::Shaders shaders;
    if (!shaders.init())
        return false;

    const Math::Vec3F bg = bgColor.value(_timeStep).toVec3F();
    const Math::CamF cam = {cameraPosition.value(_timeStep),
                            cameraLookAt.value(_timeStep),
                            cameraUp.value(_timeStep),
                            static_cast<uint>(_settingsVideo.resolution.width()),
                            static_cast<uint>(_settingsVideo.resolution.height()),
                            cameraFieldOfView.value(_timeStep),
                            cameraNearPlane.value(_timeStep),
                            cameraFarPlane.value(_timeStep)};

    shaders.setupLight(
        lightColor.value(_timeStep).toVec3F(), lightDirection.value(_timeStep), lightAmbient.value(_timeStep));

    std::vector<QVector4D> planes;
    for (const Items::ClipPlane *const &cp : std::as_const(m_clipPlanes))
        if (cp->enabled.value(_timeStep))
            planes.push_back(cp->equation(_timeStep));

    std::list<OpenGL::Data3D *> data;
    std::vector<std::pair<Math::CamF, std::list<OpenGL::Data3D *>>> camData;
    std::vector<Items::ItemCamera *> camObj;

    camData.push_back({cam, {}});
    camObj.push_back(nullptr);

    for (Items::ItemCamera *const &ic : std::as_const(m_cameras))
        if (ic->visible.value(_timeStep) && ic->showImage.value(_timeStep))
        {
            camData.push_back({ic->getCamera(_timeStep), {}});
            camObj.push_back(ic);
        }

    for (Items::Item3D *const &i : std::as_const(m_items3D))
        i->createData(data, camData, planes, _timeStep);

    for (Items::ItemCamera *const &ic : std::as_const(m_cameras))
        ic->createData(data, camData, planes, _timeStep);

    std::vector<QImage> camImages;
    camImages.reserve(camObj.size());
    for (size_t i = 1UL; i < camObj.size(); ++i)
    {
        const Math::CamF &iCam = camData.at(i).first;
        QOpenGLFramebufferObject fbo(QSize(iCam.screenWidth, iCam.screenHeight), fboFormat);
        fbo.bind();
        fun->glViewport(0, 0, iCam.screenWidth, iCam.screenHeight);
        fun->glClearColor(bg.x, bg.y, bg.z, 1.0f);
        fun->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaders.setupCamera(iCam);

        std::list<std::pair<float, OpenGL::Data3D *>> alphaData;
        for (OpenGL::Data3D *const &d : std::as_const(data))
            if (d->isTransparent())
                alphaData.push_back({d->centralPoint().distanceToPoint(iCam.position), d});
            else
                d->draw(fun, shaders.getShader(d));

        for (OpenGL::Data3D *const &d : std::as_const(camData.at(i).second))
            if (d->isTransparent())
                alphaData.push_back({d->centralPoint().distanceToPoint(iCam.position), d});
            else
                d->draw(fun, shaders.getShader(d));

        alphaData.sort([](const std::pair<float, OpenGL::Data3D *> &_1, const std::pair<float, OpenGL::Data3D *> &_2) {
            return _1.first > _2.first;
        });

        for (const std::pair<float, OpenGL::Data3D *> &d : std::as_const(alphaData))
            d.second->draw(fun, shaders.getShader(d.second));

        alphaData.clear();

        camImages.push_back(fbo.toImage());
        fbo.release();

        while (!camData.at(i).second.empty())
        {
            delete camData.at(i).second.front();
            camData.at(i).second.pop_front();
        }
    }

    QOpenGLFramebufferObject fbo(QSize(cam.screenWidth, cam.screenHeight), fboFormat);
    fbo.bind();
    fun->glViewport(0, 0, cam.screenWidth, cam.screenHeight);
    fun->glClearColor(bg.x, bg.y, bg.z, 1.0f);
    fun->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaders.setupCamera(cam);

    for (size_t i = 1UL; i < camObj.size(); ++i)
        camObj.at(i)->createTexture(data, new QOpenGLTexture(camImages.at(i - 1UL)), cam, _timeStep);

    std::list<std::pair<float, OpenGL::Data3D *>> alphaData;
    for (OpenGL::Data3D *const &d : std::as_const(data))
        if (d->isTransparent())
            alphaData.push_back({d->centralPoint().distanceToPoint(cam.position), d});
        else
        {
            d->draw(fun, shaders.getShader(d));
            delete d;
        }

    for (OpenGL::Data3D *const &d : std::as_const(camData.at(0).second))
        if (d->isTransparent())
            alphaData.push_back({d->centralPoint().distanceToPoint(cam.position), d});
        else
        {
            d->draw(fun, shaders.getShader(d));
            delete d;
        }

    alphaData.sort([](const std::pair<float, OpenGL::Data3D *> &_1, const std::pair<float, OpenGL::Data3D *> &_2) {
        return _1.first > _2.first;
    });

    for (const std::pair<float, OpenGL::Data3D *> &d : std::as_const(alphaData))
    {
        d.second->draw(fun, shaders.getShader(d.second));
        delete d.second;
    }

    QImage curImg = fbo.toImage();
    fbo.release();
    openGLContext.doneCurrent();

    QString curSubs = _settingsSubtitles.useSubtitles ? subs(_timeStep) : QString();

    if (!curSubs.isEmpty() || !m_items2D.empty())
    {
        if (_settingsSubtitles.removeLastDot && !curSubs.isEmpty())
        {
            if (curSubs.endsWith("."))
                curSubs.chop(1);
            else if (curSubs.endsWith(". "))
                curSubs.chop(2);
        }

        QPainter painter(&curImg);
        for (Items::Item2D *const &i : std::as_const(m_items2D))
            i->paintItem(painter, _settingsVideo.resolution, _timeStep);

        if (!curSubs.isEmpty())
            Items::Item2DText::paintItem2D(painter,
                                           _settingsVideo.resolution,
                                           _settingsSubtitles.upperCase ? curSubs.toUpper() : curSubs,
                                           _settingsSubtitles.fontFamily,
                                           _settingsSubtitles.fontHeight,
                                           _settingsSubtitles.fontColor,
                                           Math::_AlignBottomCenter,
                                           _settingsSubtitles.bottomOffset);
    }

    return curImg.save(_fileName);
}

}  // namespace Video
}  // namespace U1
