#include "glcamera.h"

#include <QSettings>

/*!
 * \brief Tool function returns value from flag setup
 * \param _valueNoFlag Value to return if both flags have same value
 * \param _valueFlag1 Value to return if \b first flag \a _flag1 is set
 * \param _valueFlag2 Value to return if \b second flag \a _flag2 is set
 * \param _flag1 First flag
 * \param _flag2 Second flag
 * \returns Value from flag setup
 */
static float valueByFlags(
    const float _valueNoFlag, const float _valueFlag1, const float _valueFlag2, const bool _flag1, const bool _flag2)
{
    if (_flag1 && !_flag2)
        return _valueFlag1;
    else if (!_flag1 && _flag2)
        return _valueFlag2;
    return _valueNoFlag;
}

/*!
 * \brief Tool function prepare spin properties
 * \param _forward Camera forward normal
 * \param _sideRight Camera side normal
 * \param _up Camera up normal
 * \param _angleYawDeg Yaw angle in degrees
 * \param _anglePitchDeg Pitch angle in degrees
 * \return Pair of new direction normal and side normal
 */
static std::pair<QVector3D, QVector3D> spinByYawPitch(const QVector3D &_forward,
                                                      const QVector3D &_sideRight,
                                                      const QVector3D &_up,
                                                      const float _angleYawDeg,
                                                      const float _anglePitchDeg)
{
    const QVector3D dir =
        QQuaternion::fromAxisAndAngle(_up, _angleYawDeg)
            .rotatedVector(
                QQuaternion::fromAxisAndAngle(_sideRight, _anglePitchDeg).rotatedVector(_forward).normalized())
            .normalized();
    return {dir, QVector3D::crossProduct(QVector3D::crossProduct(dir, _up).normalized(), dir).normalized()};
}

/*!
 * \brief Constructor
 * \param _parent Parent \c QObject
 */
GLCamera::GLCamera(QObject *_parent)
    : QObject(_parent)
    , m_position(0.0F, -1.0F, -5.0F)
    , m_centerOfView()
    , m_upVector(0.0F, 0.0F, 1.0F)
    , m_viewWidth(0)
    , m_viewHeight(1)
    , m_verticalAngleDeg(90.0F)
    , m_nearPlane(0.001F)
    , m_farPlane(1000.0F)
    , m_moveSpeed(0.1F)
    , m_spinSpeed(10.0F)
    , m_modifierAccel(10.0F)
    , m_mouseSensitivity(10.0F)
    , m_lastMousePos()
    , m_lockedCenterOfView(false)
    , m_isDownAccel(false)
    , m_isDownDecel(false)
    , m_isMoveForward(false)
    , m_isMoveBackward(false)
    , m_isMoveLeft(false)
    , m_isMoveRight(false)
    , m_isMoveUp(false)
    , m_isMoveDown(false)
    , m_isRollLeft(false)
    , m_isRollRight(false)
    , m_keyMoveForward(Qt::Key_Up)
    , m_keyMoveBackward(Qt::Key_Down)
    , m_keyMoveLeft(Qt::Key_Left)
    , m_keyMoveRight(Qt::Key_Right)
    , m_keyMoveUp(Qt::Key_PageUp)
    , m_keyMoveDown(Qt::Key_PageDown)
    , m_keyRollLeft(Qt::Key_Insert)
    , m_keyRollRight(Qt::Key_Home)
    , m_keyResetZ(Qt::Key_End)
    , m_keyAccelerate(Qt::ShiftModifier)
    , m_keyDecelerate(Qt::ControlModifier)
{
}

/*!
 * \brief Getter for camera perspective matrix
 * \returns Perspective matrix
 */
QMatrix4x4 GLCamera::perspectiveMatrix() const
{
    QMatrix4x4 result;
    result.setToIdentity();
    result.perspective(m_verticalAngleDeg, aspectRatio(), m_nearPlane, m_farPlane);
    return result;
}

/*!
 * \brief Getter for camera look at matrix
 * \returns Look at matrix
 */
QMatrix4x4 GLCamera::lookAtMatrix() const
{
    QMatrix4x4 result;
    result.setToIdentity();
    result.lookAt(m_position, m_centerOfView, m_upVector);
    return result;
}

/*!
 * \brief Getter for camera view matrix (\f$perspective \times lookAt\f$)
 * \returns View matrix
 */
QMatrix4x4 GLCamera::viewMatrix() const
{
    return perspectiveMatrix() * lookAtMatrix();
}

/*!
 * \brief Getter for locked center of view flag
 * \returns Locked center of view flag
 */
bool GLCamera::isLockedCenterOfView() const
{
    return m_lockedCenterOfView;
}

/*!
 * \brief Getter for handling input flag
 * \returns Handling input flag
 */
bool GLCamera::isHandlingInput() const
{
    return m_timer.isActive();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Start or stop handling input process
 * \param _enable Start/stop flag
 * \note  Starts/stops \a m_timer
 */
void GLCamera::setHandlingInput(const bool _enable)
{
    if (_enable)
    {
        if (!m_timer.isActive())
            m_timer.start(50, this);
    }
    else
    {
        if (m_timer.isActive())
            m_timer.stop();
    }

    m_isDownAccel = false;
    m_isDownDecel = false;
    m_isMoveForward = false;
    m_isMoveBackward = false;
    m_isMoveLeft = false;
    m_isMoveRight = false;
    m_isMoveUp = false;
    m_isMoveDown = false;
    m_isRollLeft = false;
    m_isRollRight = false;
    emit changedHandling();
}

/*!
 * \brief Replace camera in space
 * \param _position New camera position
 * \param _centerOfView New camera center of view
 * \param _upVector New camera up vector
 */
void GLCamera::setCamera(const QVector3D &_position, const QVector3D &_centerOfView, const QVector3D &_upVector)
{
    m_position = _position;
    m_centerOfView = _centerOfView;
    m_upVector = qFuzzyCompare(m_upVector, QVector3D()) ? QVector3D(0.0F, 0.0F, 1.0F) : _upVector.normalized();

    if (qFuzzyCompare(m_position, m_centerOfView))
        m_position += QVector3D(0.0F, 0.0F, 1.0F);

    const QVector3D forward = (m_centerOfView - m_position).normalized();
    if (!qFuzzyIsNull(QVector3D::dotProduct(forward, m_upVector)))
        m_upVector = QVector3D::crossProduct(QVector3D::crossProduct(forward, m_upVector), forward).normalized();

    emit changed();
}

/*!
 * \brief Reset up vector to best fit \b Z axis
 */
void GLCamera::resetUpVector()
{
    setCamera(m_position, m_centerOfView);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*!
 * \brief Setter for vertical angle [degrees]
 * \param _verticalAngleDeg New vertical angle
 */
void GLCamera::setVerticalAngleDeg(const float _verticalAngleDeg)
{
    m_verticalAngleDeg = _verticalAngleDeg;
    emit changedSetting();
    emit changed();
}

/*!
 * \brief Setter for camera near plane
 * \param _nearPlane New near plane value
 */
void GLCamera::setNearPlane(const float _nearPlane)
{
    m_nearPlane = _nearPlane;
    emit changedSetting();
    emit changed();
}

/*!
 * \brief Setter for camera far plane
 * \param _farPlane New far plane value
 */
void GLCamera::setFarPlane(const float _farPlane)
{
    m_farPlane = _farPlane;
    emit changedSetting();
    emit changed();
}

/*!
 * \brief Setter for camera plane
 * \param _nearPlane New near plane value
 * \param _farPlane New far plane value
 */
void GLCamera::setViewDistances(const float _nearPlane, const float _farPlane)
{
    m_nearPlane = _nearPlane;
    m_farPlane = _farPlane;
    emit changedSetting();
    emit changed();
}

/*!
 * \brief Setter for camera move speed
 * \param _moveSpeed New move speed value
 */
void GLCamera::setMoveSpeed(const float _moveSpeed)
{
    m_moveSpeed = _moveSpeed;
    emit changedSetting();
}

/*!
 * \brief Setter for camera spin speed
 * \param _spinSpeed New spin speed value
 */
void GLCamera::setSpinSpeed(const float _spinSpeed)
{
    m_spinSpeed = _spinSpeed;
    emit changedSetting();
}

/*!
 * \brief Setter for camera acceleration/deceleration multiplier
 * \param _modifierAccel New acceleration/deceleration multiplier
 */
void GLCamera::setModifierAccel(const float _modifierAccel)
{
    m_modifierAccel = _modifierAccel;
    emit changedSetting();
}

/*!
 * \brief Setter for camera mouse sensitivity
 * \param _mouseSensitivity New mouse sensitivity value
 */
void GLCamera::setMouseSensitivity(const float _mouseSensitivity)
{
    m_mouseSensitivity = _mouseSensitivity;
    emit changedSetting();
}

/*!
 * \brief Setter for locked center of view flag
 * \param _lockedCenterOfView New locked center of view flag value
 */
void GLCamera::setLockedCenterOfView(const bool _lockedCenterOfView)
{
    if (m_lockedCenterOfView != _lockedCenterOfView)
    {
        m_lockedCenterOfView = _lockedCenterOfView;
        emit changedLockView();
    }
}

/*!
 * \brief Setup locked view
 * \param _centerOfView New camera center of view
 * \param _lockedCenterOfView New locked center of view flag value
 */
void GLCamera::setLockedCenterOfView(const QVector3D &_centerOfView, const bool _lockedCenterOfView)
{
    if (m_lockedCenterOfView != _lockedCenterOfView)
    {
        m_lockedCenterOfView = _lockedCenterOfView;
        if (m_lockedCenterOfView && !qFuzzyCompare(_centerOfView, m_centerOfView))
            setCamera(m_position, _centerOfView);
        emit changedLockView();
    }
    else
    {
        if (m_lockedCenterOfView && !qFuzzyCompare(_centerOfView, m_centerOfView))
            setCamera(m_position, _centerOfView);
    }
}

/*!
 * \brief Setup view sizes
 * \param _w New width value
 * \param _h New height value
 */
void GLCamera::resizeGL(int _w, int _h)
{
    m_viewWidth = std::max(1, _w);
    m_viewHeight = std::max(1, _h);
    emit changedViewSize();
}

/*!
 * \brief Mouse press handler
 * \param _event Mouse event data
 */
void GLCamera::handleMousePress(QMouseEvent *_event)
{
    if (!isHandlingInput())
        return;

    if (_event->buttons().testFlag(Qt::LeftButton))
    {
        setupModifiers(_event);
        m_lastMousePos = _event->pos();
    }
}

/*!
 * \brief Mouse move handler
 * \param _event Mouse event data
 */
void GLCamera::handleMouseMove(QMouseEvent *_event)
{
    if (!isHandlingInput())
        return;

    if (_event->buttons().testFlag(Qt::LeftButton))
    {
        setupModifiers(_event);

        const QPoint moveDist = _event->pos() - m_lastMousePos;
        const float angleYaw = static_cast<float>(moveDist.x()) / m_mouseSensitivity;
        const float anglePitch = static_cast<float>(moveDist.y()) / m_mouseSensitivity;
        const float forwardLength = m_position.distanceToPoint(m_centerOfView);
        const QVector3D forward = (m_centerOfView - m_position).normalized();
        const QVector3D sideRight = QVector3D::crossProduct(forward, m_upVector).normalized();
        const QVector3D up = QVector3D::crossProduct(sideRight, forward).normalized();
        const std::pair<QVector3D, QVector3D> spin = spinByYawPitch(forward, sideRight, up, angleYaw, anglePitch);

        if (m_lockedCenterOfView)
            setCamera(m_centerOfView - spin.first * forwardLength, m_centerOfView);  //, spin.second);
        else
            setCamera(m_position, m_position + spin.first * forwardLength);  //, spin.second);

        m_lastMousePos = _event->pos();
    }
}

/*!
 * \brief Mouse wheel handler
 * \param _event Wheel event data
 */
void GLCamera::handleWheel(QWheelEvent *_event)
{
    if (!isHandlingInput())
        return;

    setupModifiers(_event);

    int angleDelta = _event->angleDelta().y();
    if (angleDelta == 0)
        _event->angleDelta().x();

    if (angleDelta == 0)
        return;

    if (m_lockedCenterOfView)
    {
        QVector3D move = (m_centerOfView - m_position).normalized() * (m_moveSpeed * multModifier());
        if (angleDelta > 0)
        {
            const float maxMoveDist = m_centerOfView.distanceToPoint(m_position) - m_nearPlane;
            if (qFuzzyIsNull(maxMoveDist))
                return;

            if (move.length() > maxMoveDist)
                move = move.normalized() * maxMoveDist;

            setCamera(m_position + move, m_centerOfView, m_upVector);
        }
        else
        {
            setCamera(m_position - move, m_centerOfView, m_upVector);
        }
    }
    else
    {
        const QVector3D move =
            (angleDelta > 0 ? (m_centerOfView - m_position).normalized() : (m_position - m_centerOfView).normalized()) *
            (m_moveSpeed * multModifier());

        setCamera(m_position + move, m_centerOfView + move, m_upVector);
    }
}

/*!
 * \brief Setup dynamic flag by pressed / released key
 * \param _eventKey Key index
 * \param _value New flag value
 */
void GLCamera::setupKey(const int _eventKey, const bool _value)
{
    if (_eventKey == m_keyMoveForward)
        m_isMoveForward = _value;
    else if (_eventKey == m_keyMoveBackward)
        m_isMoveBackward = _value;
    else if (_eventKey == m_keyMoveLeft)
        m_isMoveLeft = _value;
    else if (_eventKey == m_keyMoveRight)
        m_isMoveRight = _value;
    else if (_eventKey == m_keyMoveUp)
        m_isMoveUp = _value;
    else if (_eventKey == m_keyMoveDown)
        m_isMoveDown = _value;
    else if (_eventKey == m_keyRollLeft)
        m_isRollLeft = _value;
    else if (_eventKey == m_keyRollRight)
        m_isRollRight = _value;
}

/*!
 * \brief Key press handler
 * \param _event Key event data
 */
void GLCamera::handleKeyPress(QKeyEvent *_event)
{
    if (!isHandlingInput())
        return;

    setupModifiers(_event);
    setupKey(_event->key(), true);

    if (_event->key() == m_keyResetZ)
        resetUpVector();
}

/*!
 * \brief Key release handler
 * \param _event Key event data
 */
void GLCamera::handleKeyRelease(QKeyEvent *_event)
{
    if (!isHandlingInput())
        return;

    setupModifiers(_event);
    setupKey(_event->key(), false);
}

/*!
 * \brief Returns acceleration/deceleration multiplier value
 * \returns Acceleration/deceleration multiplier value
 */
float GLCamera::multModifier() const
{
    return valueByFlags(1.0F, m_modifierAccel, 1.0F / m_modifierAccel, m_isDownAccel, m_isDownDecel);
}

/*!
 * \brief Modifiers handler
 * \param _event Event data
 */
void GLCamera::setupModifiers(QInputEvent *_event)
{
    m_isDownAccel = _event->modifiers().testFlag(Qt::ShiftModifier);
    m_isDownDecel = _event->modifiers().testFlag(Qt::ControlModifier);
}

/*!
 * \brief Next step from camera dynamics
 */
void GLCamera::timerEvent(QTimerEvent *)
{
    if (!m_isMoveForward && !m_isMoveBackward && !m_isMoveLeft && !m_isMoveRight && !m_isMoveUp && !m_isMoveDown &&
        !m_isRollLeft && !m_isRollRight)
        return;

    const float multRoll = valueByFlags(0.0F, m_spinSpeed, -m_spinSpeed, m_isRollLeft, m_isRollRight);
    const float multModif = multModifier();

    const QVector3D forward = (m_centerOfView - m_position).normalized();
    const QVector3D sideRight = QVector3D::crossProduct(forward, m_upVector).normalized();
    QVector3D up = QVector3D::crossProduct(sideRight, forward).normalized();
    if (!qFuzzyIsNull(multRoll))
        up = QQuaternion::fromAxisAndAngle(forward, multRoll * multModif).rotatedVector(up);

    if (m_lockedCenterOfView)
    {
        const float multSide = valueByFlags(0.0F, -m_spinSpeed, m_spinSpeed, m_isMoveLeft, m_isMoveRight);
        const float multUpDown = valueByFlags(0.0F, -m_spinSpeed, m_spinSpeed, m_isMoveUp, m_isMoveDown);
        const float angleYaw = static_cast<float>(multSide * multModif);
        const float anglePitch = static_cast<float>(multUpDown * multModif);
        const float forwardLength = m_position.distanceToPoint(m_centerOfView);
        const std::pair<QVector3D, QVector3D> spin = spinByYawPitch(forward, sideRight, up, angleYaw, anglePitch);

        QVector3D move;
        if (m_isMoveBackward)
        {
            move = -spin.first * (m_moveSpeed * multModif);
        }
        else if (m_isMoveForward)
        {
            const float maxMoveDist = forwardLength - m_nearPlane;
            const float curMove = m_moveSpeed * multModif;
            if (!qFuzzyIsNull(maxMoveDist))
                move = spin.first * (curMove > maxMoveDist ? maxMoveDist : curMove);
        }

        setCamera(m_centerOfView - spin.first * forwardLength + move, m_centerOfView, spin.second);
    }
    else
    {
        const float multMove = m_moveSpeed * multModif;
        const float multFront = valueByFlags(0.0F, 1.0F, -1.0F, m_isMoveForward, m_isMoveBackward);
        const float multSide = valueByFlags(0.0F, 1.0F, -1.0F, m_isMoveRight, m_isMoveLeft);
        const float multUpDown = valueByFlags(0.0F, 1.0F, -1.0F, m_isMoveUp, m_isMoveDown);

        const QVector3D move = (forward * multFront + sideRight * multSide + up * multUpDown).normalized() * multMove;

        setCamera(m_position + move, m_centerOfView + move, up);
    }
}

/*!
 * \brief Setup camera position by given range
 * \param _minMax Scene range (\a first is minimum, \a second maximum)
 * \param _stayLocked Stay locked flag (if already locked)
 */
void GLCamera::setLookAt(const std::pair<QVector3D, QVector3D> &_minMax, const bool _stayLocked)
{
    const QVector3D &min = _minMax.first;
    const QVector3D &max = _minMax.second;
    const QVector3D range = max - min;
    const QVector3D center = (min + max) * 0.5F;

    setCamera(QVector3D(center.x() + range.x() * 0.25f,
                        min.y() - range.y() * 0.5f,
                        center.z() + 0.25f * std::max(std::max(range.x(), range.y()), range.z())),
              center);

    if (!m_lockedCenterOfView && _stayLocked)
    {
        m_lockedCenterOfView = true;
        emit changedLockView();
    }
}

/*!
 * \brief Setup camera position by given range only if current position is outside given range
 * \param _minMax Scene range (\a first is minimum, \a second maximum)
 * \param _stayLocked Stay locked flag (if already locked)
 */
void GLCamera::setMaybeLookAt(const std::pair<QVector3D, QVector3D> &_minMax, const bool _stayLocked)
{
    if (position().x() > _minMax.first.x() && position().x() < _minMax.second.x() &&
        position().y() > _minMax.first.y() && position().y() < _minMax.second.y() &&
        position().z() > _minMax.first.z() && position().z() < _minMax.second.z())
        return;
    setLookAt(_minMax, _stayLocked);
}

/*!
 * \brief Save camera into \c QSettings
 * \param _savePosition Save with position
 * \param _keyGroup \c QSettings group name
 */
void GLCamera::saveSettings(const bool _savePosition, const QString &_keyGroup) const
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    QSettings settings;

    settings.setValue(key + "verticalAngleDeg", m_verticalAngleDeg);
    settings.setValue(key + "nearPlane", m_nearPlane);
    settings.setValue(key + "farPlane", m_farPlane);
    settings.setValue(key + "moveSpeed", m_moveSpeed);
    settings.setValue(key + "spinSpeed", m_spinSpeed);
    settings.setValue(key + "modifierAccel", m_modifierAccel);
    settings.setValue(key + "mouseSensitivity", m_mouseSensitivity);
    if (_savePosition)
    {
        settings.setValue(key + "position", m_position);
        settings.setValue(key + "centerOfView", m_centerOfView);
        settings.setValue(key + "upVector", m_upVector);
    }
}

/*!
 * \brief Load camera properties from \c QSettings
 * \param _loadPosition Load with position
 * \param _keyGroup \c QSettings group name
 */
void GLCamera::loadSettings(const bool _loadPosition, const QString &_keyGroup)
{
    const QString key = _keyGroup.isEmpty() ? QString() : (_keyGroup.endsWith('/') ? _keyGroup : (_keyGroup + "/"));
    const QSettings settings;
    m_verticalAngleDeg = settings.value(key + "verticalAngleDeg", m_verticalAngleDeg).toFloat();
    m_nearPlane = settings.value(key + "nearPlane", m_nearPlane).toFloat();
    m_farPlane = settings.value(key + "farPlane", m_farPlane).toFloat();
    m_moveSpeed = settings.value(key + "moveSpeed", m_moveSpeed).toFloat();
    m_spinSpeed = settings.value(key + "spinSpeed", m_spinSpeed).toFloat();
    m_modifierAccel = settings.value(key + "modifierAccel", m_modifierAccel).toFloat();
    m_mouseSensitivity = settings.value(key + "mouseSensitivity", m_mouseSensitivity).toFloat();
    if (_loadPosition)
    {
        m_position = settings.value(key + "position", m_position).value<QVector3D>();
        m_centerOfView = settings.value(key + "centerOfView", m_centerOfView).value<QVector3D>();
        m_upVector = settings.value(key + "upVector", m_upVector).value<QVector3D>();
    }
}
