#include "dynamicvec3.h"

Universe1::Video::DynamicVec3::DynamicVec3(const QVector3D &_value, const std::string &_name)
    : DynamicProperty(_VEC3, _name)
{
    values.push_back({0UL, _value});
}

bool Universe1::Video::DynamicVec3::initialize(const uint64_t _duration)
{
    return initializeImpl<QVector3D>(values, _duration);
}

QVector3D Universe1::Video::DynamicVec3::getValue(const uint64_t _timeStep) const
{
    if (values.empty())
        return QVector3D();

    if (values.front().first >= _timeStep)
        return values.front().second;

    std::list<std::pair<uint64_t, QVector3D>>::const_iterator itPrev = values.cbegin();
    std::list<std::pair<uint64_t, QVector3D>>::const_iterator itNext = itPrev;
    itNext++;

    for (; itNext != values.cend(); ++itPrev, ++itNext)
    {
        const std::pair<uint64_t, QVector3D> &prev = *itPrev;
        if (prev.first == _timeStep)
            return prev.second;

        const std::pair<uint64_t, QVector3D> &next = *itNext;
        if (next.first == _timeStep)
            return next.second;

        if (next.first > _timeStep)
            return prev.second +
                (next.second - prev.second) *
                (static_cast<float>(_timeStep - prev.first) / static_cast<float>(next.first - prev.first));
    }

    return (*itPrev).second;
}

QString Universe1::Video::DynamicVec3::getValueText(const uint64_t _timeStep) const
{
    const QVector3D tmp = getValue(_timeStep);
    return QString::number(tmp.x()) + " x " + QString::number(tmp.y()) + " x " + QString::number(tmp.z());
}

QVector3D Universe1::Video::DynamicVec3::addSame(const uint64_t _timeStep)
{
    if (values.empty())
    {
        std::cerr << "Error[" << name << "]: addSame(): Empty values !" << std::endl;
        return QVector3D();
    }

    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: addSame(" << _timeStep << "ms): Using aligned time: " << timeStepFixed
                  << "ms !" << std::endl;

    const QVector3D result = values.back().second;
    values.push_back({timeStepFixed, result});
    return result;
}

void Universe1::Video::DynamicVec3::add(const uint64_t _timeStep, const QVector3D &_value)
{
    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: add(" << _timeStep << "ms, [" << _value.x() << "x" << _value.y() << "x"
                  << _value.z() << "]): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

    values.push_back({timeStepFixed, _value});
}

void Universe1::Video::DynamicVec3::addJump(const uint64_t _timeStepStart,
                                            const uint64_t _timeStepEnd,
                                            const QVector3D &_value)
{
    const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addJump(" << _timeStepStart << "ms, " << _timeStepEnd << "ms, ["
                  << _value.x() << "x" << _value.y() << "x" << _value.z()
                  << "]): Using aligned times: " << timeStepStartFixed << "ms, " << timeStepEndFixed << " !"
                  << std::endl;
    addSame(timeStepStartFixed);
    add(timeStepEndFixed, _value);
}

bool Universe1::Video::DynamicVec3::initAccel(
    Accel &_out, const uint64_t _duration, const float _length, const float _acceleration, const float _deceleration)

{
    const uint64_t fd = Config::cfg().frameDuration;

    _out.dur1 = static_cast<uint64_t>(static_cast<float>(_duration) * _acceleration);
    uint64_t tmod = _out.dur1 % fd;
    uint64_t usedTimeStep = _out.dur1 + (tmod == 0UL ? 0UL : (fd - tmod));
    _out.dur1 = usedTimeStep;

    _out.dur3 = static_cast<uint64_t>(static_cast<float>(_duration) * _deceleration);
    tmod = _out.dur3 % fd;
    usedTimeStep = _out.dur3 + (tmod == 0UL ? 0UL : (fd - tmod));
    _out.dur3 = usedTimeStep;

    if (_out.dur1 + _out.dur3 > _duration)
        return false;

    _out.dur2 = _duration - _out.dur1 - _out.dur3;
    tmod = _out.dur2 % fd;
    usedTimeStep = _out.dur2 + (tmod == 0UL ? 0UL : (fd - tmod));
    _out.dur2 = usedTimeStep;

    _out.v0 = _length /
        (static_cast<float>(_out.dur1 / 2UL) + static_cast<float>(_out.dur2) + static_cast<float>(_out.dur3 / 2UL));
    _out.a1 = _out.v0 / static_cast<float>(_out.dur1);
    _out.a3 = _out.v0 / static_cast<float>(_out.dur3);
    _out.l1 = 0.5f * _out.a1 * static_cast<float>(_out.dur1 * _out.dur1);
    _out.l3 = 0.5f * _out.a3 * static_cast<float>(_out.dur3 * _out.dur3);
    return true;
}

void Universe1::Video::DynamicVec3::addAccel(const uint64_t _timeStepStart,
                                             const uint64_t _timeStepEnd,
                                             const QVector3D &_value,
                                             const float _acceleration,
                                             const float _deceleration)
{
    const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addAccel(" << _timeStepStart << "ms, " << _timeStepEnd << "ms, ["
                  << _value.x() << "x" << _value.y() << "x" << _value.z()
                  << "]): Using aligned times: " << timeStepStartFixed << "ms, " << timeStepEndFixed << " !"
                  << std::endl;

    addSame(timeStepStartFixed);
    addAccel(timeStepEndFixed, _value, _acceleration, _deceleration);
}

void Universe1::Video::DynamicVec3::addAccel(const uint64_t _timeStepEnd,
                                             const QVector3D &_value,
                                             const float _acceleration,
                                             const float _deceleration)
{
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addAccel(): Using aligned end time: " << timeStepEndFixed << "ms !"
                  << std::endl;

    const uint64_t startTime = values.back().first;
    if (startTime >= timeStepEndFixed)
    {
        std::cerr << "Error[" << name << "]: addAccel(): Start time is not before last stored time !" << std::endl;
        return;
    }

    const uint64_t step = Config::cfg().frameDuration;
    const uint64_t duration = timeStepEndFixed - startTime;
    if (step > duration)
    {
        values.push_back({timeStepEndFixed, _value});
        return;
    }

    const QVector3D &beginPos = values.back().second;
    QVector3D dir = (_value - beginPos);
    const float length = dir.length();
    if (qFuzzyIsNull(length))
    {
        values.push_back({timeStepEndFixed, _value});
        return;
    }
    dir /= length;

    Accel acc;
    if (!initAccel(acc, duration, length, _acceleration, _deceleration))
    {
        std::cerr << "Error[" << name << "]: addAccel(): Invalid acceleration / deceleration !" << std::endl;
        return;
    }

    const QVector3D p1 = beginPos + dir * acc.l1;
    const QVector3D p2 = _value - dir * acc.l3;

    uint64_t s = step;
    for (; s < acc.dur1; s += step)
        values.push_back({startTime + s, beginPos + dir * (0.5f * acc.a1 * static_cast<float>(s * s))});

    const uint64_t o3 = startTime + acc.dur1 + acc.dur2;
    values.push_back({startTime + acc.dur1, p1});
    values.push_back({o3, p2});

    s = step;
    for (; s < acc.dur3; s += step)
        values.push_back({o3 + s, p2 + dir * ((acc.v0 * s) - (0.5f * acc.a3 * static_cast<float>(s * s)))});

    if (values.back().first < timeStepEndFixed)
        values.push_back({timeStepEndFixed, _value});
}

//

void Universe1::Video::DynamicVec3::addArc(const uint64_t _timeStepStart,
                                           const uint64_t _timeStepEnd,
                                           const QVector3D &_rotationCenter,
                                           const QVector3D &_rotationNormal,
                                           const float _angleDeg)
{
    const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addArc(" << _timeStepStart << "ms, " << _timeStepEnd
                  << "ms): Using aligned times: " << timeStepStartFixed << "ms, " << timeStepEndFixed << " !"
                  << std::endl;

    addSame(timeStepStartFixed);
    addArc(timeStepEndFixed, _rotationCenter, _rotationNormal, _angleDeg);
}

void Universe1::Video::DynamicVec3::addArc(const uint64_t _timeStepEnd,
                                           const QVector3D &_rotationCenter,
                                           const QVector3D &_rotationNormal,
                                           const float _angleDeg)
{
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addArc(): Using aligned end time: " << timeStepEndFixed << "ms !"
                  << std::endl;

    const uint64_t startTime = values.back().first;
    if (startTime >= timeStepEndFixed)
    {
        std::cerr << "Error[" << name << "]: addArc(): Start time is not before last stored time !" << std::endl;
        return;
    }

    const QVector3D &beginPos = values.back().second;
    if (qFuzzyIsNull(_angleDeg))
    {
        values.push_back({timeStepEndFixed, beginPos});
        return;
    }

    if (qFuzzyCompare(_rotationCenter, beginPos))
    {
        std::cerr << "Warning[" << name << "]: addArc(): Distance to center too small !" << std::endl;
        values.push_back({timeStepEndFixed, beginPos});
        return;
    }

    const uint64_t step = Config::cfg().frameDuration;
    const uint64_t duration = timeStepEndFixed - startTime;
    if (step > duration)
    {
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(_rotationNormal, _angleDeg);
        values.push_back({timeStepEndFixed, _rotationCenter + rot.rotatedVector(beginPos - _rotationCenter)});
        return;
    }

    const uint64_t stepCount = duration / step;
    const QQuaternion rot = QQuaternion::fromAxisAndAngle(_rotationNormal, _angleDeg / static_cast<float>(stepCount));
    uint64_t i = startTime + step;
    QVector3D arm = rot.rotatedVector(beginPos - _rotationCenter);
    for (uint64_t s = 0UL; s < stepCount; ++s, i += step, arm = rot.rotatedVector(arm))
        values.push_back({i, _rotationCenter + arm});

    if (values.back().first < timeStepEndFixed)
    {
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(_rotationNormal, _angleDeg);
        values.push_back({timeStepEndFixed, _rotationCenter + rot.rotatedVector(beginPos - _rotationCenter)});
    }
}

void Universe1::Video::DynamicVec3::addArcAccel(const uint64_t _timeStepStart,
                                                const uint64_t _timeStepEnd,
                                                const QVector3D &_rotationCenter,
                                                const QVector3D &_rotationNormal,
                                                const float _angleDeg,
                                                const float _acceleration,
                                                const float _deceleration)
{
    const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addArcAccel(" << _timeStepStart << "ms, " << _timeStepEnd
                  << "ms): Using aligned times: " << timeStepStartFixed << "ms, " << timeStepEndFixed << " !"
                  << std::endl;

    addSame(timeStepStartFixed);
    addArcAccel(timeStepEndFixed, _rotationCenter, _rotationNormal, _angleDeg, _acceleration, _deceleration);
}

void Universe1::Video::DynamicVec3::addArcAccel(const uint64_t _timeStepEnd,
                                                const QVector3D &_rotationCenter,
                                                const QVector3D &_rotationNormal,
                                                const float _angleDeg,
                                                const float _acceleration,
                                                const float _deceleration)
{
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addArcAccel(): Using aligned end time: " << timeStepEndFixed << "ms !"
                  << std::endl;

    const uint64_t startTime = values.back().first;
    if (startTime >= timeStepEndFixed)
    {
        std::cerr << "Error[" << name << "]: addArcAccel(): Start time is not before last stored time !" << std::endl;
        return;
    }

    const QVector3D &beginPos = values.back().second;
    if (qFuzzyIsNull(_angleDeg))
    {
        values.push_back({timeStepEndFixed, beginPos});
        return;
    }

    if (qFuzzyCompare(_rotationCenter, beginPos))
    {
        std::cerr << "Warning[" << name << "]: addArcAccel(): Distance to center too small !" << std::endl;
        values.push_back({timeStepEndFixed, beginPos});
        return;
    }

    const uint64_t step = Config::cfg().frameDuration;
    const uint64_t duration = timeStepEndFixed - startTime;
    if (step > duration)
    {
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(_rotationNormal, _angleDeg);
        values.push_back({timeStepEndFixed, _rotationCenter + rot.rotatedVector(beginPos - _rotationCenter)});
        return;
    }

    Accel acc;
    if (!initAccel(acc, duration, _angleDeg, _acceleration, _deceleration))
    {
        std::cerr << "Error[" << name << "]: addArcAccel(): Invalid acceleration / deceleration !" << std::endl;
        return;
    }

    const QVector3D arm = beginPos - _rotationCenter;

    uint64_t s = step;
    for (; s < acc.dur1; s += step)
    {
        const QQuaternion rot =
            QQuaternion::fromAxisAndAngle(_rotationNormal, 0.5f * acc.a1 * static_cast<float>(s * s));
        values.push_back({startTime + s, _rotationCenter + rot.rotatedVector(arm)});
    }

    const uint64_t d2 = (acc.dur1 + acc.dur2);
    for (; s < d2; s += step)
    {
        const QQuaternion rot =
            QQuaternion::fromAxisAndAngle(_rotationNormal, acc.l1 + acc.v0 * static_cast<float>(s - acc.dur1));
        values.push_back({startTime + s, _rotationCenter + rot.rotatedVector(arm)});
    }

    const float l2 = _angleDeg - acc.l3;
    for (; s < duration; s += step)
    {
        const uint64_t ss = s - d2;
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(
            _rotationNormal, l2 + acc.v0 * static_cast<float>(ss) - 0.5f * acc.a3 * static_cast<float>(ss * ss));
        values.push_back({startTime + s, _rotationCenter + rot.rotatedVector(arm)});
    }

    if (values.back().first < timeStepEndFixed)
    {
        const QQuaternion rot = QQuaternion::fromAxisAndAngle(_rotationNormal, _angleDeg);
        values.push_back({timeStepEndFixed, _rotationCenter + rot.rotatedVector(beginPos - _rotationCenter)});
    }
}

void Universe1::Video::DynamicVec3::addBezier(const uint64_t _timeStepStart,
                                              const uint64_t _timeStepEnd,
                                              const QVector3D &_endPos,
                                              const QVector3D &_beginDir,
                                              const QVector3D &_endDir)
{
    const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addBezier(" << _timeStepStart << "ms, " << _timeStepEnd
                  << "ms): Using aligned times: " << timeStepStartFixed << "ms, " << timeStepEndFixed << " !"
                  << std::endl;

    addSame(timeStepStartFixed);
    addBezier(timeStepEndFixed, _endPos, _beginDir, _endDir);
}

inline QVector3D
bezier(const QVector3D &_p1, const QVector3D &_p2, const QVector3D &_p3, const QVector3D &_p4, const float _t)
{
    const float tt = (1.0f - _t);
    return (_p1 * tt * tt * tt) + (_p2 * 3.0f * tt * tt * _t) + (_p3 * 3.0f * tt * _t * _t) + (_p4 * _t * _t * _t);
}

void Universe1::Video::DynamicVec3::addBezier(const uint64_t _timeStepEnd,
                                              const QVector3D &_endPos,
                                              const QVector3D &_beginDir,
                                              const QVector3D &_endDir)
{
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addBezier(): Using aligned end time: " << timeStepEndFixed << "ms !"
                  << std::endl;

    const uint64_t startTime = values.back().first;
    if (startTime >= timeStepEndFixed)
    {
        std::cerr << "Error[" << name << "]: addBezier(): Start time is not before last stored time !" << std::endl;
        return;
    }

    const QVector3D &beginPos = values.back().second;
    if (qFuzzyCompare(_endPos, beginPos))
    {
        values.push_back({timeStepEndFixed, _endPos});
        return;
    }

    const uint64_t step = Config::cfg().frameDuration;
    const uint64_t duration = timeStepEndFixed - startTime;
    if (step > duration)
    {
        values.push_back({timeStepEndFixed, _endPos});
        return;
    }

    const uint64_t stepCount = duration / step;
    const float stepT = 1.0f / static_cast<float>(stepCount);
    const QVector3D &bezierP1 = values.back().second;
    const QVector3D bezierP2 = bezierP1 + _beginDir;
    const QVector3D bezierP3 = _endPos - _endDir;
    const QVector3D &bezierP4 = _endPos;
    uint64_t i = startTime + step;

    float t = stepT;
    for (uint64_t s = 0UL; s < stepCount; ++s, t += stepT, i += step)
        values.push_back({i, bezier(bezierP1, bezierP2, bezierP3, bezierP4, t)});
}
