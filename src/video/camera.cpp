#include "camera.h"

Universe1::Video::Camera::Camera(const std::string &_footageName,
                                 const QVector3D &_pos,
                                 const QVector3D &_lookAt,
                                 const QVector3D &_up)
    : pos(_pos, _footageName + ".camera.pos")
    , lookAt(_lookAt, _footageName + ".camera.lookAt")
    , up(_up, _footageName + ".camera.up")
{
}

QMatrix4x4 Universe1::Video::Camera::makeMvp(const QVector3D &_pos, const QVector3D &_lookAt, const QVector3D &_up)
{
    const QVector3D tmpUp = _up.normalized();
    const QVector3D camFw = (_pos - _lookAt).normalized();
    const QVector3D camLeft = QVector3D::crossProduct(tmpUp, camFw).normalized();
    const QVector3D camUp = QVector3D::crossProduct(camFw, camLeft).normalized();

    QMatrix4x4 result;
    result.setToIdentity();
    result.data()[0] = camLeft.x();
    result.data()[4] = camLeft.y();
    result.data()[8] = camLeft.z();
    result.data()[1] = camUp.x();
    result.data()[5] = camUp.y();
    result.data()[9] = camUp.z();
    result.data()[2] = camFw.x();
    result.data()[6] = camFw.y();
    result.data()[10] = camFw.z();
    result.data()[12] = (-camLeft.x() * _pos.x() - camLeft.y() * _pos.y() - camLeft.z() * _pos.z());
    result.data()[13] = (-camUp.x() * _pos.x() - camUp.y() * _pos.y() - camUp.z() * _pos.z());
    result.data()[14] = (-camFw.x() * _pos.x() - camFw.y() * _pos.y() - camFw.z() * _pos.z());
    return result;
}

bool Universe1::Video::Camera::initialize(const uint64_t _duration)
{
    bool result = pos.initialize(_duration);
    result = lookAt.initialize(_duration) && result;
    result = up.initialize(_duration) && result;
    return result;
}
