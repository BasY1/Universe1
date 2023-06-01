#include "dynamicalign.h"

Universe1::Video::DynamicAlign::DynamicAlign(const Qt::Alignment _value, const std::string &_name)
    : DynamicProperty(_ENUM, _name)
{
    values.push_back({0UL, _value});
}

bool Universe1::Video::DynamicAlign::initialize(const uint64_t _duration)
{
    return initializeImpl<Qt::Alignment>(values, _duration);
}

QString Universe1::Video::DynamicAlign::getValueText(const uint64_t _timeStep) const
{
    return QString::number((int)getValue(_timeStep));
}

void Universe1::Video::DynamicAlign::add(const uint64_t _timeStep, const Qt::Alignment _value)
{
    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: add(" << _timeStep << "ms, " << _value
                  << "): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

    values.push_back({timeStepFixed, _value});
}
