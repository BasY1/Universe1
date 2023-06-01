#include "dynamiccolor.h"

Universe1::Video::DynamicColor::DynamicColor(const QColor &_color, const std::string &_name)
    : DynamicProperty(_COLOR, _name)
{
    values.push_back({0UL, _color});
}

bool Universe1::Video::DynamicColor::initialize(const uint64_t _duration)
{
    return initializeImpl<QColor>(values, _duration);
}

QColor Universe1::Video::DynamicColor::getValue(const uint64_t _timeStep) const
{
    if (values.empty())
        return QColor();

    if (values.front().first >= _timeStep)
        return values.front().second;

    std::list<std::pair<uint64_t, QColor>>::const_iterator itPrev = values.cbegin();
    std::list<std::pair<uint64_t, QColor>>::const_iterator itNext = itPrev;
    itNext++;

    for (; itNext != values.cend(); ++itPrev, ++itNext)
    {
        const std::pair<uint64_t, QColor> &prev = *itPrev;
        if (prev.first == _timeStep)
            return prev.second;

        const std::pair<uint64_t, QColor> &next = *itNext;
        if (next.first == _timeStep)
            return next.second;

        if (next.first > _timeStep)
        {
            const float r = static_cast<float>(_timeStep - prev.first) / static_cast<float>(next.first - prev.first);
            return QColor(
                prev.second.red() + static_cast<int>(static_cast<float>(next.second.red() - prev.second.red()) * r),
                prev.second.green() +
                    static_cast<int>(static_cast<float>(next.second.green() - prev.second.green()) * r),
                prev.second.blue() + static_cast<int>(static_cast<float>(next.second.blue() - prev.second.blue()) * r),
                prev.second.alpha() +
                    static_cast<int>(static_cast<float>(next.second.alpha() - prev.second.alpha()) * r));
        }
    }

    return (*itPrev).second;
}

QString Universe1::Video::DynamicColor::getValueText(const uint64_t _timeStep) const
{
    return getValue(_timeStep).name(QColor::HexArgb);
}

QColor Universe1::Video::DynamicColor::addSame(const uint64_t _timeStep)
{
    if (values.empty())
    {
        std::cerr << "Error[" << name << "]: addSame(): Empty values !" << std::endl;
        return QColor();
    }

    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: addSame(" << _timeStep << "ms): Using aligned time: " << timeStepFixed
                  << "ms !" << std::endl;

    const QColor result = values.back().second;
    values.push_back({timeStepFixed, result});
    return result;
}

void Universe1::Video::DynamicColor::add(const uint64_t _timeStep, const QColor &_value)
{
    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: add(" << _timeStep << "ms, [" << _value.name().toStdString()
                  << "]): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

    values.push_back({timeStepFixed, _value});
}

void Universe1::Video::DynamicColor::addJump(const uint64_t _timeStepStart,
                                             const uint64_t _timeStepEnd,
                                             const QColor &_value)
{
    const uint64_t timeStepStartFixed = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeStepEndFixed = Config::cfg().fixedTime(_timeStepEnd);
    if (_timeStepStart != timeStepStartFixed || _timeStepEnd != timeStepEndFixed)
        std::cerr << "Warning[" << name << "]: addJump(" << _timeStepStart << "ms, " << _timeStepEnd << "ms, ["
                  << _value.name().toStdString() << "]): Using aligned times: " << timeStepStartFixed << "ms, "
                  << timeStepEndFixed << " !" << std::endl;
    addSame(timeStepStartFixed);
    add(timeStepEndFixed, _value);
}

void Universe1::Video::DynamicColor::addLoop(const uint64_t _timeStepStart,
                                             const uint64_t _timeStepEnd,
                                             const QColor &_value1,
                                             const QColor &_value2,
                                             const uint64_t _durationValue1toValue2,
                                             const uint64_t _durationValue2toValue1)
{
    const uint64_t timeOn = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeOff = Config::cfg().fixedTime(_timeStepEnd);
    const uint64_t dur12 = Config::cfg().fixedTime(_durationValue1toValue2);
    const uint64_t dur21 = Config::cfg().fixedTime(_durationValue1toValue2);

    if (_timeStepStart != timeOn)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned time start: " << timeOn << "ms !" << std::endl;
    if (_timeStepEnd != timeOff)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned time end: " << timeOff << "ms !" << std::endl;
    if (_durationValue1toValue2 != dur12)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned duration 1->2: " << dur12 << "ms !"
                  << std::endl;
    if (_durationValue2toValue1 != dur21)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned duration 2->1: " << dur21 << "ms !"
                  << std::endl;

    const uint64_t loopTime = dur12 + dur21;
    uint64_t tt = timeOn;
    while (tt + loopTime < timeOff)
    {
        values.push_back({tt + dur12, _value2});
        tt += loopTime;
        values.push_back({tt, _value1});
    }
}

void Universe1::Video::DynamicColor::addLoop(const uint64_t _timeStepStart,
                                             const uint64_t _timeStepEnd,
                                             const QColor &_value,
                                             const uint64_t _durationValue1toValue2,
                                             const uint64_t _durationValue2toValue1)
{
    if (values.empty())
        std::cerr << "Error[" << name << "]: addLoop(): Empty values !" << std::endl;
    else
        addLoop(_timeStepStart,
                _timeStepEnd,
                values.back().second,
                _value,
                _durationValue1toValue2,
                _durationValue2toValue1);
}
