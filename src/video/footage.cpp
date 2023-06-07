#include "footage.h"

const QVector3D Universe1::Video::Footage::nx(1, 0, 0);
const QVector3D Universe1::Video::Footage::ny(0, 1, 0);
const QVector3D Universe1::Video::Footage::nz(0, 0, 1);

const QString Universe1::Video::Footage::tR1("<b>ℝ</b><sub>1</sub>");
const QString Universe1::Video::Footage::tC1("<b>ℂ</b><sub>1</sub>");
const QString Universe1::Video::Footage::tV1("<b>V</b><sub>1</sub>");
const QString Universe1::Video::Footage::tO1("<b>Ω</b><sub>1</sub>");
const QString Universe1::Video::Footage::tOI("<b>Ω</b><sub>I</sub>");
const QString Universe1::Video::Footage::tOJ("<b>Ω</b><sub>J</sub>");
const QString Universe1::Video::Footage::tOK("<b>Ω</b><sub>K</sub>");
const QString Universe1::Video::Footage::tOM("<b>Ω</b><sub>M</sub>");
const QString Universe1::Video::Footage::tOT("<b>Ω</b><sub>T</sub>");
const QString Universe1::Video::Footage::tOG("<b>ω</b><sub>G</sub>");
const QString Universe1::Video::Footage::tOG1("<b>ω</b><sub>G1</sub>");
const QString Universe1::Video::Footage::tOG2("<b>ω</b><sub>G2</sub>");
const QString Universe1::Video::Footage::tOG3("<b>ω</b><sub>G3</sub>");

const QString Universe1::Video::Footage::tVOL("<b>Ⓥ</b><sub>1</sub>");
const QString Universe1::Video::Footage::tLEN("<b>Ⓛ</b><sub>1</sub>");
const QString Universe1::Video::Footage::tPER("<b>Ⓣ</b><sub>1</sub>");

const QString Universe1::Video::Footage::tM("[<i>m</i>]");
const QString Universe1::Video::Footage::tM_2("[<i>m</i><sup>2</sup>]");
const QString Universe1::Video::Footage::tM_3("[<i>m</i><sup>3</sup>]");

const QString Universe1::Video::Footage::tRad("[<i>rad</i>]");
const QString Universe1::Video::Footage::tS("[<i>s</i>]");

const QString Universe1::Video::Footage::tM_S("[<i>m s</i><sup>-1</sup>]");
const QString Universe1::Video::Footage::tR_S("[<i>rad s</i><sup>-1</sup>]");
const QString Universe1::Video::Footage::tENG("[<i>m</i><sup>2</sup> <i>rad</i><sup>2</sup> <i>s</i><sup>-2</sup>]");

const std::array<QString, 5> Universe1::Video::Footage::tabR1 = {QObject::tr("Particle radius"), tR1, "=", "1", tM};
const std::array<QString, 5> Universe1::Video::Footage::tabC1 = {QObject::tr("Particle velocity"), tC1, "=", "1", tM_S};
const std::array<QString, 5> Universe1::Video::Footage::tabO1 = {QObject::tr("Particle spin"), tO1, "=", "1", tR_S};
const std::array<QString, 5> Universe1::Video::Footage::tabVOL = {
    QObject::tr("Particle volume"), tVOL, "=", "4/3π " + tR1, tM_3};
const std::array<QString, 5> Universe1::Video::Footage::tabLEN = {
    QObject::tr("Period length"), tLEN, "=", "2π " + tR1, tM};
const std::array<QString, 5> Universe1::Video::Footage::tabPER = {QObject::tr("Period duration"), tPER, "=", "2π", tS};

const QString Universe1::Video::Footage::tab_R1_C1_O1 =
    Universe1::Video::Footage::mkTab({{QObject::tr("Universe constants"), "-C-", "", "", ""}, tabR1, tabC1, tabO1});
const QString Universe1::Video::Footage::tab_CONSTANTS = Universe1::Video::Footage::mkTab(
    {{QObject::tr("Universe constants"), "-C-", "", "", ""}, tabR1, tabC1, tabO1, tabVOL, tabLEN, tabPER});

Universe1::Video::Footage::Footage(const std::string &_footageName,
                                   const uint64_t _footageId,
                                   const uint64_t _footageStartTime,
                                   const std::pair<QVector3D, QVector3D> &_lastCamera)
    : QObject(nullptr)
    , footageName(_footageName)
    , footageId(_footageId)
    , footageStartTime(_footageStartTime)
    , duration(0UL)
    , framesCount(0UL)
    , camera(footageName, _lastCamera.first, _lastCamera.second)
    , subs(footageName, footageId)
    , text2D(footageName)
    , image2D(footageName)
    , text3D(footageName, &items)
    , plane(footageName, &items)
    , planeCircle(footageName, &items)
    , planeCircleSlice(footageName, &items)
    , cone(footageName, &items)
    , coneSlice(footageName, &items)
    , cylinder(footageName, &items)
    , cylinderSlice(footageName, &items)
    , sphere(footageName, &items)
    , sphereCup(footageName, &items)
    , sphereSlice(footageName, &items)
    , wireSphere(footageName, &items)
    , wireSphereCup(footageName, &items)
    , wireSphereSlice(footageName, &items)
    , torus(footageName, &items)
    , torusArc(footageName, &items)
    , torusCup(footageName, &items)
    , torusArcCup(footageName, &items)
    , torusSlice(footageName, &items)
    , torusArcSlice(footageName, &items)
    , line(footageName, &items)
    , lineDots(footageName, &items)
    , lineDash(footageName, &items)
    , lineTwist(footageName, &items)
    , lineCircle(footageName, &items)
    , lineArc(footageName, &items)
    , lineArcDots(footageName, &items)
    , lineArcDash(footageName, &items)
    , cross(footageName, &items)
    , path(footageName, &items)
    , arrow(footageName, &items)
    , arcArrow(footageName, &items)
    , angleDim(footageName, &items)
    , space(footageName, &items)
    , hand(footageName, &items)
    , spin(footageName, &items)
    , constellation(footageName, &items)
    , cfg(Config::cfg())
{
    if (cfg.verbose)
        std::cout << "---------------- " << footageName << "[" << footageId << "] ----------------" << std::endl;
}

Universe1::Video::Footage::~Footage()
{
    for (Item3D *ii : items)
        delete ii;
}

bool Universe1::Video::Footage::initialize()
{
    if (cfg.verbose)
        std::cout << "---------------- " << footageName << "[" << footageId << "] ----------------" << std::endl;

    if (duration == 0UL)
    {
        std::cerr << "Error[" << footageName << "[" << footageId << "]]: Footage duration not set !" << std::endl;
        return false;
    }

    if (duration < cfg.frameDuration)
    {
        std::cerr << "Error[" << footageName << "[" << footageId << "]]: Footage duration too short [" << duration
                  << "ms], frame time [" << cfg.frameDuration << "ms]" << std::endl;
        return false;
    }

    framesCount = duration / cfg.frameDuration;
    const uint64_t realDuration = framesCount * cfg.frameDuration;
    if (realDuration != duration)
    {
        std::cerr << "Warning[" << footageName << "[" << footageId << "]]: using aligned duration [" << realDuration
                  << "ms], frame time [" << cfg.frameDuration << "ms], frame count [x" << framesCount
                  << "], invalid duration [" << duration << "ms]" << std::endl;
        duration = realDuration;
    }

    bool result = true;
    if (!subs.initialize(duration))
        result = false;
    if (!text2D.initialize(duration))
        result = false;

    if (!items.empty())
    {
        if (!camera.initialize(duration))
            result = false;
        for (Item3D *i : items)
            if (!i->initialize(duration))
                result = false;
    }

    return result;
}

bool Universe1::Video::Footage::saveImages() const
{
    const std::vector<std::pair<uint64_t, uint64_t>> pool = cfg.createPool(framesCount);
    if (cfg.verbose)
    {
        std::cout << "Building images: " << footageName << "[" << footageId << "]"
                  << " frame count [" << framesCount << "], duration [" << duration << "ms, "
                  << QTime::fromMSecsSinceStartOfDay(duration).toString("HH:mm:ss.zzz").toStdString() << "]";

        if (!pool.empty())
            std::cout << ", thread pool [" << pool.size() << " x " << pool.front().second << "]";
        std::cout << std::endl;
    }

    const QDateTime bt = QDateTime::currentDateTime();
    if (pool.empty())
    {
        for (uint64_t f = 0UL; f < framesCount; ++f)
            if (!saveImage(this, f))
                return false;

        if (cfg.verbose)
        {
            const QTime tt = QTime::fromMSecsSinceStartOfDay(bt.msecsTo(QDateTime::currentDateTime()));
            std::cout << "Building images: " << footageName << "[" << footageId
                      << "]: " << tt.toString("h:m:ss.zzz").toStdString() << std::endl;
        }
        return true;
    }

    std::vector<int> tData(pool.size(), 0);
    std::vector<std::thread> threads;
    threads.reserve(pool.size());
    uint tt = 0U;

    for (const std::pair<uint64_t, uint64_t> &t : pool)
    {
        threads.push_back(std::thread(
            [this, t](int &_out) {
                const uint64_t end = t.first + t.second;
                for (uint64_t f = t.first; f < end; ++f)
                {
                    if (!Footage::saveImage(this, f))
                    {
                        _out = 1;
                        return;
                    }
                }
            },
            std::ref(tData[tt++])));
    }

    for (std::thread &t : threads)
        t.join();

    for (const int &t : tData)
        if (t == 1)
            return false;

    if (cfg.verbose)
    {
        const QTime tt = QTime::fromMSecsSinceStartOfDay(bt.msecsTo(QDateTime::currentDateTime()));
        std::cout << "Building images: " << footageName << "[" << footageId
                  << "]: " << tt.toString("h:m:ss.zzz").toStdString() << std::endl;
    }

    return true;
}


bool Universe1::Video::Footage::saveImage(const Footage *_footage, const uint64_t _frameId)
{
    const uint64_t timeStep = _frameId * Config::cfg().frameDuration;

    QImage image;
    if (!_footage->getImage3D(image, timeStep))
        return false;

    QPainter painter(&image);
    _footage->paint2D(&painter, timeStep);
    _footage->paintSubs(&painter, timeStep);
    _footage->paint2DPost(&painter, timeStep);

    const QString fileName = Config::cfg().pathImage(_footage->footageId, _frameId);
    if (!image.save(fileName))
    {
        std::cerr << "Error[" << _footage->footageName << "[" << _footage->footageId
                  << "]]: Can't save image: " << fileName.toStdString() << " !" << std::endl;
        return false;
    }

    return true;
}

void Universe1::Video::Footage::paintSubs(QPainter *_painter, const uint64_t _timeStep) const
{
    subs.paint(_painter, _timeStep);
}

void Universe1::Video::Footage::paint2D(QPainter *_painter, const uint64_t _timeStep) const
{
    text2D.paint(_painter, _timeStep);
}

void Universe1::Video::Footage::paint2DPost(QPainter *, const uint64_t) const {}

bool Universe1::Video::Footage::getImage3D(QImage &_out, const uint64_t _timeStep) const
{
    if (items.empty())
    {
        _out = QImage(cfg.widthScreen, cfg.heightScreen, QImage::Format_ARGB32);
        _out.fill(cfg.colorBG);
        return true;
    }

    const QSize imgSize = QSize(cfg.widthScreen, cfg.heightScreen);

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setVersion(3, 3);
    if (cfg.glSamples > 0U)
        surfaceFormat.setSamples(cfg.glSamples);
    surfaceFormat.setDepthBufferSize(24);
    surfaceFormat.setProfile(QSurfaceFormat::OpenGLContextProfile::CompatibilityProfile);

    QOpenGLContext openGLContext;
    openGLContext.setFormat(surfaceFormat);
    openGLContext.create();
    if (!openGLContext.isValid())
    {
        std::cerr << "Can't create OpenGL context" << std::endl;
        return false;
    }

    QOffscreenSurface surface;
    surface.setFormat(surfaceFormat);
    surface.create();
    if (!surface.isValid())
    {
        std::cerr << "Can't create off-screen surface" << std::endl;
        return false;
    }

    if (!openGLContext.makeCurrent(&surface))
    {
        std::cerr << "Can't make OpenGL context current" << std::endl;
        return false;
    }

    QOpenGLFunctions *f = openGLContext.functions();

    QOpenGLFramebufferObjectFormat fboFormat;
    // fboFormat.setAttachment(QOpenGLFramebufferObject::Depth);
    fboFormat.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    if (cfg.glSamples > 0U)
        fboFormat.setSamples(cfg.glSamples);
    QOpenGLFramebufferObject fbo(imgSize, fboFormat);
    f->glViewport(0, 0, imgSize.width(), imgSize.height());
    fbo.bind();

    Shader program(f, camera.getStats(_timeStep), cfg.perspectiveMatrix());
    if (!program.initialize())
        return false;

    program.bind();

    f->glClearColor(cfg.colorBG.redF(), cfg.colorBG.greenF(), cfg.colorBG.blueF(), cfg.colorBG.alphaF());
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    f->glEnable(GL_DEPTH_TEST);

    if (cfg.glBlend)
    {
        f->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        f->glBlendEquation(GL_FUNC_ADD);
        f->glEnable(GL_BLEND);
    }

    if (cfg.glSamples > 0U)
        f->glEnable(GL_MULTISAMPLE);

    if (cfg.glCullFront)
    {
        f->glEnable(GL_CULL_FACE);
        f->glCullFace(GL_FRONT);
    }

    std::list<Data3D> data3D;
    for (const Item3D *i : items)
        if (i->visible.getValue(_timeStep))
            i->addData3D(data3D, &program, _timeStep);

    program.draw(data3D);

    program.release();
    _out = fbo.toImage();
    fbo.release();
    openGLContext.doneCurrent();

    return true;
}

std::list<Universe1::Video::FootageFactoryInterface *> Universe1::Video::Footages::sequence = {};

uint64_t Universe1::Video::Footages::init(std::list<Footage *> &_footages)
{
    std::pair<QVector3D, QVector3D> camera = {QVector3D(1, -8, 3), QVector3D(0, 0, 0)};

    uint64_t id = 1UL, tt = 0UL;
    for (const FootageFactoryInterface *fi : sequence)
    {
        Footage *next = fi->create(id, tt, camera);
        camera = next->camera.getLastState();
        id++;
        tt += next->duration;
        _footages.push_back(next);
    }
    return tt;
}

