/*!
 * \file qt/opengl/glcamera.h
 * \author Michal Steller
 * \brief The QT Open GL camera class declarations
 */

#ifndef UNIVERSE1_OPENGL_GLCAMERA_H
#define UNIVERSE1_OPENGL_GLCAMERA_H

#include <QMatrix4x4>
#include <QObject>
#include <QPoint>
#include <QVector3D>

#include <QBasicTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimerEvent>
#include <QWheelEvent>

/*!
 * \brief The OpenGL camera
 */
class GLCamera : public QObject
{
    Q_OBJECT
 public:
    GLCamera(QObject *_parent = nullptr);

    inline const QVector3D &position() const;
    inline const QVector3D &centerOfView() const;
    inline const QVector3D &upVector() const;

    inline float verticalAngleDeg() const;
    inline float nearPlane() const;
    inline float farPlane() const;
    inline float moveSpeed() const;
    inline float spinSpeed() const;
    inline float modifierAccel() const;
    inline float mouseSensitivity() const;

    inline int viewWidth() const;
    inline int viewHeight() const;
    inline float aspectRatio() const;

    QMatrix4x4 perspectiveMatrix() const;
    QMatrix4x4 lookAtMatrix() const;
    QMatrix4x4 viewMatrix() const;

    bool isLockedCenterOfView() const;
    bool isHandlingInput() const;

    inline Qt::Key keyMoveForward() const;
    inline Qt::Key keyMoveBackward() const;
    inline Qt::Key keyMoveLeft() const;
    inline Qt::Key keyMoveRight() const;
    inline Qt::Key keyMoveUp() const;
    inline Qt::Key keyMoveDown() const;
    inline Qt::Key keyRollLeft() const;
    inline Qt::Key keyRollRight() const;
    inline Qt::Key keyResetZ() const;
    inline Qt::KeyboardModifier keyAccelerate() const;
    inline Qt::KeyboardModifier keyDecelerate() const;

 public slots:
    void setHandlingInput(const bool _enable);

    void setCamera(const QVector3D &_position,
                   const QVector3D &_centerOfView,
                   const QVector3D &_upVector = QVector3D(0.0F, 0.0F, 1.0F));

    void resetUpVector();

    void setVerticalAngleDeg(const float _verticalAngleDeg);
    void setNearPlane(const float _nearPlane);
    void setFarPlane(const float _farPlane);
    void setViewDistances(const float _nearPlane, const float _farPlane);
    void setMoveSpeed(const float _moveSpeed);
    void setSpinSpeed(const float _spinSpeed);
    void setModifierAccel(const float _modifierAccel);
    void setMouseSensitivity(const float _mouseSensitivity);

    void setLockedCenterOfView(const bool _lockedCenterOfView);
    void setLockedCenterOfView(const QVector3D &_centerOfView, const bool _lockedCenterOfView = true);

    void setLookAt(const std::pair<QVector3D, QVector3D> &_minMax, const bool _stayLocked = false);
    void setMaybeLookAt(const std::pair<QVector3D, QVector3D> &_minMax, const bool _stayLocked = false);

 public:
    void resizeGL(int _w, int _h);

    void handleMousePress(QMouseEvent *_event);
    void handleMouseMove(QMouseEvent *_event);

    void handleWheel(QWheelEvent *_event);

    void handleKeyPress(QKeyEvent *_event);
    void handleKeyRelease(QKeyEvent *_event);

 protected:
    float multModifier() const;
    void setupModifiers(QInputEvent *_event);
    void setupKey(const int _eventKey, const bool _value);

    void timerEvent(QTimerEvent *) override;

 public:
    void saveSettings(const bool _savePosition, const QString &_keyGroup = "GLCamera") const;
    void loadSettings(const bool _loadPosition, const QString &_keyGroup = "GLCamera");

 signals:
    void changed();          //!< Emits when camera change property and this change should be visible (repaint needed)
    void changedSetting();   //!< Emits when camera change settings property
    void changedLockView();  //!< Emits when locked view state changed
    void changedViewSize();  //!< Emits when bounded OpenGL widget change resolution
    void changedHandling();  //!< Emits when handling input state changed

 protected:
    QBasicTimer m_timer;  //!< Basic timer for dynamic behavior

    QVector3D m_position;      //!< Current camera position (position of "eye")
    QVector3D m_centerOfView;  //!< Current camera center of view, where camera is looking at
    QVector3D m_upVector;      //!< Current camera up vector

    int m_viewWidth;   //!< View width
    int m_viewHeight;  //!< View height

    float m_verticalAngleDeg;  //!< Vertical angle for view perspective Deg
    float m_nearPlane;         //!< View near plane
    float m_farPlane;          //!< View far plane

    float m_moveSpeed;         //!< Camera move speed
    float m_spinSpeed;         //!< Camera spin speed
    float m_modifierAccel;     //!< Camera acceleration/deceleration multiplier
    float m_mouseSensitivity;  //!< Camera mouse sensitivity

    QPoint m_lastMousePos;  //!< Last processed mouse position

    bool m_lockedCenterOfView;  //!< Flag for locked center of view
    bool m_isDownAccel;         //!< Flag for acceleration
    bool m_isDownDecel;         //!< Flag for deceleration
    bool m_isMoveForward;       //!< Flag for move forward
    bool m_isMoveBackward;      //!< Flag for move backward
    bool m_isMoveLeft;          //!< Flag for move left
    bool m_isMoveRight;         //!< Flag for move right
    bool m_isMoveUp;            //!< Flag for move up
    bool m_isMoveDown;          //!< Flag for move down
    bool m_isRollLeft;          //!< Flag for roll left
    bool m_isRollRight;         //!< Flag for roll right

    Qt::Key m_keyMoveForward;              //!< Move forward key
    Qt::Key m_keyMoveBackward;             //!< Move backward key
    Qt::Key m_keyMoveLeft;                 //!< Move left key
    Qt::Key m_keyMoveRight;                //!< Move right key
    Qt::Key m_keyMoveUp;                   //!< Move up key
    Qt::Key m_keyMoveDown;                 //!< Move down key
    Qt::Key m_keyRollLeft;                 //!< Roll left key
    Qt::Key m_keyRollRight;                //!< Roll right key
    Qt::Key m_keyResetZ;                   //!< Reset up vector key
    Qt::KeyboardModifier m_keyAccelerate;  //!< Acceleration modifier
    Qt::KeyboardModifier m_keyDecelerate;  //!< Deceleration modifier
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for camera position
 * \returns Camera position
 */
inline const QVector3D &GLCamera::position() const
{
    return m_position;
}

/*!
 * \brief Getter for camera center of view
 * \returns Camera center of view
 */
inline const QVector3D &GLCamera::centerOfView() const
{
    return m_centerOfView;
}

/*!
 * \brief Getter for camera up vector
 * \returns Camera up vector
 */
inline const QVector3D &GLCamera::upVector() const
{
    return m_upVector;
}

/*!
 * \brief Getter for vertical angle [degrees]
 * \returns Camera vertical angle [degrees]
 */
inline float GLCamera::verticalAngleDeg() const
{
    return m_verticalAngleDeg;
}

/*!
 * \brief Getter for camera near plane
 * \returns Camera near plane
 */
inline float GLCamera::nearPlane() const
{
    return m_nearPlane;
}

/*!
 * \brief Getter for camera far plane
 * \returns Camera far plane
 */
inline float GLCamera::farPlane() const
{
    return m_farPlane;
}

/*!
 * \brief Getter for camera move speed
 * \returns Camera move speed
 */
float GLCamera::moveSpeed() const
{
    return m_moveSpeed;
}

/*!
 * \brief Getter for camera spin speed
 * \returns Camera spin speed
 */
inline float GLCamera::spinSpeed() const
{
    return m_spinSpeed;
}

/*!
 * \brief Getter for camera acceleration/deceleration multiplier
 * \returns Camera acceleration/deceleration multiplier
 */
inline float GLCamera::modifierAccel() const
{
    return m_modifierAccel;
}

/*!
 * \brief Getter for camera mouse sensitivity
 * \returns Camera mouse sensitivity
 */
inline float GLCamera::mouseSensitivity() const
{
    return m_mouseSensitivity;
}

/*!
 * \brief Getter for view width
 * \returns View width
 */
inline int GLCamera::viewWidth() const
{
    return m_viewWidth;
}

/*!
 * \brief Getter for view height
 * \returns View height
 */
inline int GLCamera::viewHeight() const
{
    return m_viewHeight;
}

/*!
 * \brief Getter for view aspect ratio \f$\frac{width}{height}\f$
 * \returns View aspect ratio
 */
inline float GLCamera::aspectRatio() const
{
    return static_cast<float>(m_viewWidth) / static_cast<float>(m_viewHeight);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Getter for key mapping action: move forward
 * \returns Move forward key
 */
inline Qt::Key GLCamera::keyMoveForward() const
{
    return m_keyMoveForward;
}

/*!
 * \brief Getter for key mapping action: move backward
 * \returns Move backward key
 */
inline Qt::Key GLCamera::keyMoveBackward() const
{
    return m_keyMoveBackward;
}

/*!
 * \brief Getter for key mapping action: move left
 * \returns Move left key
 */
inline Qt::Key GLCamera::keyMoveLeft() const
{
    return m_keyMoveLeft;
}

/*!
 * \brief Getter for key mapping action: move right
 * \returns Move right key
 */
inline Qt::Key GLCamera::keyMoveRight() const
{
    return m_keyMoveRight;
}

/*!
 * \brief Getter for key mapping action: move up
 * \returns Move up key
 */
inline Qt::Key GLCamera::keyMoveUp() const
{
    return m_keyMoveUp;
}

/*!
 * \brief Getter for key mapping action: move down
 * \returns Move down key
 */
inline Qt::Key GLCamera::keyMoveDown() const
{
    return m_keyMoveDown;
}

/*!
 * \brief Getter for key mapping action: roll left
 * \returns Roll left key
 */
inline Qt::Key GLCamera::keyRollLeft() const
{
    return m_keyRollLeft;
}

/*!
 * \brief Getter for key mapping action: roll right
 * \returns Roll right key
 */
inline Qt::Key GLCamera::keyRollRight() const
{
    return m_keyRollRight;
}

/*!
 * \brief Getter for key mapping action: reset up vector
 * \returns Reset up vector key
 */
inline Qt::Key GLCamera::keyResetZ() const
{
    return m_keyResetZ;
}

/*!
 * \brief Getter for acceleration modifier
 * \returns Acceleration modifier
 */
inline Qt::KeyboardModifier GLCamera::keyAccelerate() const
{
    return m_keyAccelerate;
}

/*!
 * \brief Getter for deceleration modifier
 * \returns Deceleration modifier
 */
inline Qt::KeyboardModifier GLCamera::keyDecelerate() const
{
    return m_keyDecelerate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif  // UNIVERSE1_OPENGL_GLCAMERA_H
