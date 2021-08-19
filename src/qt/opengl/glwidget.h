/*!
 * \file qt/opengl/glwidget.h
 * \author Michal Steller
 * \brief Base QT Open GL widget class declaration
 */

#ifndef UNIVERSE1_OPENGL_GLWIDGET_H
#define UNIVERSE1_OPENGL_GLWIDGET_H

#include "shaderprogram.h"

#include <QOpenGLWidget>
#include <QSettings>

namespace Universe1 {
namespace OpenGL {

/*!
 * \brief Base QT Open GL widget
 */
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
 public:
    /*!
     * \brief Open GL cull-face mode
     */
    enum CullFaceMode
    {
        CullDisabled,      //!< Cull-face disabled
        CullFront,         //!< Cull-face cull front
        CullBack,          //!< Cull-face cull back
        CullFrontAndBack,  //!< Cull-face cull front and back
    };
    Q_ENUM(CullFaceMode)

    GLWidget(const QString &_settingsKey, const bool _storePosition, QWidget *_parent = nullptr);
    inline GLWidget(QWidget *_parent = nullptr);

    ~GLWidget();

    inline Camera *camera();

    inline bool emitContextPainted() const;
    inline bool blending() const;
    inline bool blendFunc() const;
    inline bool antialiasing() const;
    inline bool cullFaceCcw() const;
    inline CullFaceMode cullFaceMode() const;
    inline float pointSize() const;
    inline float lineWidth() const;

    inline QColor bgColor() const;

    /*!
     * \brief Memory usage: returns size of allocated memory within OpenGL context
     * \returns Size of allocated memory within OpenGL context
     */
    virtual size_t memoryUsage() const = 0;

 protected:
    void focusInEvent(QFocusEvent *_event) override;
    void focusOutEvent(QFocusEvent *_event) override;
    // void mouseDoubleClickEvent(QMouseEvent *_event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseMoveEvent(QMouseEvent *_event) override;
    void wheelEvent(QWheelEvent *_event) override;
    void keyPressEvent(QKeyEvent *_event) override;
    void keyReleaseEvent(QKeyEvent *_event) override;

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;

    /*!
     * \brief Initialize scene within Open GL
     * \returns Void
     */
    virtual void initializeGLImpl() = 0;

    /*!
     * \brief Paint scene within Open GL
     * \returns Void
     */
    virtual void paintGLImpl() = 0;

 public slots:
    void setEmitContextPainted(const bool _value);
    void setAntialiasing(const bool _value);
    void setBlending(const bool _value);
    void setBlendFunc(const bool _value);
    void setCullFaceCcw(const bool _value);
    void setCullFaceMode(const CullFaceMode _value);
    void setPointSize(const float _value);
    void setLineWidth(const float _value);

    void setBGColor(const QColor &_color);
    void setBGColorRed(const float _value);
    void setBGColorGreen(const float _value);
    void setBGColorBlue(const float _value);
    void setBGColorAlpha(const float _value);

 signals:
    /*!
     * \brief Open GL context initialized
     * \param _context Open GL object
     */
    void contextInitialized(QOpenGLContext *_context);

    /*!
     * \brief Open GL context painted
     * \param _context Open GL object
     * \note Emitted only when \a m_emitContextPainted flag value is \c true
     */
    void contextPainted(QOpenGLContext *_context);

 protected:
    const QString m_settingsKey;  //!< Key for storing within \c QSettings

    bool m_emitContextPainted;  //!< Enable flag for emitting context painted signal

    bool m_antialiasing;  //!< Antialiasing enabled flag

    bool m_blending;  //!< Blending enabled flag

    /*!
     * \brief Blending function flag
     * \details
     * | Value    | \c glBlendFunc(ARGS)                          |
     * | :------- | :-------------------------------------------- |
     * | \c true  | <tt>GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA</tt> |
     * | \c false | <tt>GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA</tt> |
     */
    bool m_blendFunc;

    bool m_cullFaceCcw;           //!< Counter clock wise flag for front face definition
    CullFaceMode m_cullFaceMode;  //!< Cull-face mode

    GLclampf m_bgColorRed;    //!< Background color \b red property
    GLclampf m_bgColorGreen;  //!< Background color \b green property
    GLclampf m_bgColorBlue;   //!< Background color \b blue property
    GLclampf m_bgColorAlpha;  //!< Background color \b alpha property

    GLfloat m_pointSize;  //!< Open GL point size
    GLfloat m_lineWidth;  //!< Open GL line width

    Camera *m_camera;  //!< Camera

    ShaderProgram *m_program;  //!< Shader program
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Constructor
 * \param _parent Parent \c QWidget
 */
inline GLWidget::GLWidget(QWidget *_parent)
    : GLWidget(QString(), false, _parent)
{
}

/*!
 * \brief Getter for camera object
 * \returns Camera object
 */
inline Camera *Universe1::OpenGL::GLWidget::camera()
{
    return m_camera;
}

/*!
 * \brief Getter for emitting context painted signal flag
 * \returns Emitting context painted signal flag
 */
inline bool GLWidget::emitContextPainted() const
{
    return m_emitContextPainted;
}

/*!
 * \brief Getter for antialiasing enabled flag
 * \returns Antialiasing enabled flag
 */
inline bool GLWidget::antialiasing() const
{
    return m_antialiasing;
}

/*!
 * \brief Getter for counter clock wise flag
 * \returns Counter clock wise flag
 */
inline bool GLWidget::cullFaceCcw() const
{
    return m_cullFaceCcw;
}

/*!
 * \brief Getter for cull-face mode
 * \returns Cull-face mode
 */
inline GLWidget::CullFaceMode GLWidget::cullFaceMode() const
{
    return m_cullFaceMode;
}

/*!
 * \brief Getter for blending enabled flag
 * \returns Blending enabled flag
 */
inline bool GLWidget::blending() const
{
    return m_blending;
}

/*!
 * \brief Getter for blending function flag
 * \returns Blending function flag
 * \details
 * | Value    | \c glBlendFunc(ARGS)                          |
 * | :------- | :-------------------------------------------- |
 * | \c true  | <tt>GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA</tt> |
 * | \c false | <tt>GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA</tt> |
 */
inline bool GLWidget::blendFunc() const
{
    return m_blendFunc;
}

/*!
 * \brief Getter for Open GL point size
 * \returns Open GL point size
 */
inline float GLWidget::pointSize() const
{
    return m_pointSize;
}

/*!
 * \brief Getter for Open GL line width
 * \returns Open GL line width
 */
inline float GLWidget::lineWidth() const
{
    return m_lineWidth;
}

/*!
 * \brief Getter for Open GL background color as \c QColor
 * \returns Open GL background color
 */
inline QColor GLWidget::bgColor() const
{
    return QColor(m_bgColorRed * 255.0F, m_bgColorGreen * 255.0F, m_bgColorBlue * 255.0F, m_bgColorAlpha * 255.0F);
}

}  // namespace OpenGL
}  // namespace Universe1

#endif  // UNIVERSE1_OPENGL_GLWIDGET_H
