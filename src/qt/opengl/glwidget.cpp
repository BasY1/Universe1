/*!
 * \file qt/opengl/glwidget.cpp
 * \author Michal Steller
 * \brief Base QT Open GL widget class implementation
 */

#include "glwidget.h"

/*!
 * \brief Constructor
 * \param _parent Parent \c QWidget
 */
Universe1::OpenGL::GLWidget::GLWidget(QWidget *_parent)
    : QOpenGLWidget(_parent)
    , m_emitContextPainted(false)
    , m_antialiasing(false)
    , m_blending(false)
    , m_cullFaceCcw(false)
    , m_cullFaceMode(CullDisabled)
    , m_bgColorRed(0.0F)
    , m_bgColorGreen(0.0F)
    , m_bgColorBlue(0.0F)
    , m_bgColorAlpha(0.0F)
    , m_pointSize(1.0F)
    , m_lineWidth(1.0F)
    , m_camera(new Camera())
    , m_program(new ShaderProgram())
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);  // must be called before the widget or its parent window gets shown

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    connect(m_camera, &Camera::changed, this, static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));

    m_camera->setHandlingInput(true);
}

/*!
 * \brief Destructor
 */
Universe1::OpenGL::GLWidget::~GLWidget()
{
    makeCurrent();
    delete m_program;
    doneCurrent();

    disconnect(m_camera, &Camera::changed, this, static_cast<void (QOpenGLWidget::*)()>(&QOpenGLWidget::update));
    delete m_camera;
}

/*!
 * \brief Focus in event - starts handling input for camera dynamics
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::focusInEvent(QFocusEvent *_event)
{
    m_camera->setHandlingInput(true);
    QOpenGLWidget::focusInEvent(_event);
}

/*!
 * \brief Focus in event - disable handling input for camera dynamics
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::focusOutEvent(QFocusEvent *_event)
{
    m_camera->setHandlingInput(false);
    QOpenGLWidget::focusOutEvent(_event);
}

/*!
 * \brief Mouse press event handler
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::mousePressEvent(QMouseEvent *_event)
{
    m_camera->handleMousePress(_event);
    QOpenGLWidget::mousePressEvent(_event);
}

/*!
 * \brief Mouse move event handler
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::mouseMoveEvent(QMouseEvent *_event)
{
    m_camera->handleMouseMove(_event);
    QOpenGLWidget::mouseMoveEvent(_event);
}

/*!
 * \brief Wheel event handler
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::wheelEvent(QWheelEvent *_event)
{
    m_camera->handleWheel(_event);
    QOpenGLWidget::wheelEvent(_event);
}

/*!
 * \brief Key press event handler
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::keyPressEvent(QKeyEvent *_event)
{
    m_camera->handleKeyPress(_event);
    QOpenGLWidget::keyPressEvent(_event);
}

/*!
 * \brief Key release event handler
 * \param _event Event data
 */
void Universe1::OpenGL::GLWidget::keyReleaseEvent(QKeyEvent *_event)
{
    m_camera->handleKeyRelease(_event);
    QOpenGLWidget::keyReleaseEvent(_event);
}

/*!
 * \brief Open GL initialization
 */
void Universe1::OpenGL::GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    //m_camera->setLockedCenterOfView(QVector3D());

    if (m_program->initGL())
    {
        m_camera->resizeGL(width(), height());
        glEnable(GL_DEPTH_TEST);
        emit contextInitialized(context());

        initializeGLImpl();
    }
}

/*!
 * \brief Resize Open GL widget handler
 * \param _w New widget width
 * \param _h New widget height
 */
void Universe1::OpenGL::GLWidget::resizeGL(int _w, int _h)
{
    m_camera->resizeGL(_w, _h);
}

/*!
 * \brief Paint Open GL
 */
void Universe1::OpenGL::GLWidget::paintGL()
{
    glClearColor(m_bgColorRed, m_bgColorGreen, m_bgColorBlue, m_bgColorAlpha);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_blending)
    {
        glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
    }
    else
    {
        glDisable(GL_BLEND);
    }

    if (m_antialiasing)
    {
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_POINT_SMOOTH);
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_LINE_SMOOTH);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    }
    else
    {
        glDisable(GL_MULTISAMPLE);
        glDisable(GL_POINT_SMOOTH);
        glDisable(GL_LINE_SMOOTH);
    }

    switch (m_cullFaceMode)
    {
    case CullDisabled: glDisable(GL_CULL_FACE); break;

    case CullFront:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        glFrontFace(m_cullFaceCcw ? GL_CCW : GL_CW);
        break;

    case CullBack:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(m_cullFaceCcw ? GL_CCW : GL_CW);
        break;

    case CullFrontAndBack:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT_AND_BACK);
        glFrontFace(m_cullFaceCcw ? GL_CCW : GL_CW);
        break;
    }

    m_program->bind();
    m_program->setupCamera(m_camera);

    glPointSize(m_pointSize);
    glLineWidth(m_lineWidth);

    paintGLImpl();

    m_program->release();

    if (m_emitContextPainted)
        emit contextPainted(context());
}

/*!
 * \brief Setter for emitting context painted signal flag
 * \param _value New emitting context painted signal flag value
 */
void Universe1::OpenGL::GLWidget::setEmitContextPainted(const bool _value)
{
    if (m_emitContextPainted != _value)
    {
        m_emitContextPainted = _value;
        if (m_emitContextPainted)
            update();
    }
}

/*!
 * \brief Setter for antialiasing enabled flag
 * \param _value New antialiasing enabled flag value
 */
void Universe1::OpenGL::GLWidget::setAntialiasing(const bool _value)
{
    m_antialiasing = _value;
    update();
}

/*!
 * \brief Setter for blending enabled flag
 * \param _value New blending enabled flag value
 */
void Universe1::OpenGL::GLWidget::setBlending(const bool _value)
{
    m_blending = _value;
    update();
}

/*!
 * \brief Setter for counter clock wise flag
 * \param _value New counter clock wise flag value
 */
void Universe1::OpenGL::GLWidget::setCullFaceCcw(const bool _value)
{
    m_cullFaceCcw = _value;
    update();
}

/*!
 * \brief Setter for cull-face mode
 * \param _value New cull-face mode value
 */
void Universe1::OpenGL::GLWidget::setCullFaceMode(const CullFaceMode _value)
{
    m_cullFaceMode = _value;
    update();
}

/*!
 * \brief Setter for Open GL point size
 * \param _value New Open GL point size value
 */
void Universe1::OpenGL::GLWidget::setPointSize(const float _value)
{
    m_pointSize = _value;
    update();
}

/*!
 * \brief Setter for Open GL line width
 * \param _value New Open GL line width value
 */
void Universe1::OpenGL::GLWidget::setLineWidth(const float _value)
{
    m_lineWidth = _value;
    update();
}

/*!
 * \brief Setter for Open GL background color as \c QColor
 * \param _color new Open GL background color value
 */
void Universe1::OpenGL::GLWidget::setBGColor(const QColor &_color)
{
    m_bgColorRed = _color.redF();
    m_bgColorGreen = _color.greenF();
    m_bgColorBlue = _color.blueF();
    m_bgColorAlpha = _color.alphaF();
    update();
}
