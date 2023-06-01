#include "dynamicbool.h"

Universe1::Video::DynamicBool::DynamicBool(const bool _value, const std::string &_name)
    : DynamicProperty(_BOOL, _name)
{
    values.push_back({0UL, _value});
}

bool Universe1::Video::DynamicBool::initialize(const uint64_t _duration)
{
    return initializeImpl<bool>(values, _duration);
}

bool Universe1::Video::DynamicBool::getValue(const uint64_t _timeStep) const
{
    return getValueConstant<bool>(values, _timeStep);
}

QString Universe1::Video::DynamicBool::getValueText(const uint64_t _timeStep) const
{
    return getValue(_timeStep) ? "On" : "Off";
}

void Universe1::Video::DynamicBool::add(const uint64_t _timeStep, const bool _value)
{
    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: add(" << _timeStep << "ms, " << (_value ? "On" : "Off")
                  << "): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

    values.push_back({timeStepFixed, _value});
}

void Universe1::Video::DynamicBool::addLoop(const uint64_t _timeStepStart,
                                            const uint64_t _timeStepEnd,
                                            const uint64_t _durationOn,
                                            const uint64_t _durationOff)
{
    const uint64_t timeOn = Config::cfg().fixedTime(_timeStepStart);
    const uint64_t timeOff = Config::cfg().fixedTime(_timeStepEnd);
    const uint64_t durOn = Config::cfg().fixedTime(_durationOn);
    const uint64_t durOff = Config::cfg().fixedTime(_durationOff);

    if (_timeStepStart != timeOn)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned time start: " << timeOn << "ms !" << std::endl;
    if (_timeStepEnd != timeOff)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned time end: " << timeOff << "ms !" << std::endl;
    if (_durationOn != durOn)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned duration on: " << durOn << "ms !" << std::endl;
    if (_durationOff != durOff)
        std::cerr << "Warning[" << name << "]: addLoop(): Using aligned duration off: " << durOff << "ms !"
                  << std::endl;

    uint64_t tt = timeOn;
    while (tt + durOn < timeOff)
    {
        values.push_back({tt, true});
        values.push_back({tt + durOn, false});
        tt += (durOn + durOff);
    }
}
