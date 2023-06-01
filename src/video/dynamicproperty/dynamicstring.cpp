#include "dynamicstring.h"

Universe1::Video::DynamicString::DynamicString(const QString &_text, const std::string &_name)
    : DynamicProperty(_TEXT, _name)
{
    values.push_back({0UL, _text});
}

bool Universe1::Video::DynamicString::initialize(const uint64_t _duration)
{
    return initializeImpl<QString>(values, _duration);
}

QString Universe1::Video::DynamicString::getValue(const uint64_t _timeStep) const
{
    return getValueConstant<QString>(values, _timeStep);
}

QString Universe1::Video::DynamicString::getValueText(const uint64_t _timeStep) const
{
    return getValue(_timeStep);
}

void Universe1::Video::DynamicString::add(const uint64_t _timeStep, const QString &_value)
{
    const uint64_t timeStepFixed = Config::cfg().fixedTime(_timeStep);
    if (_timeStep != timeStepFixed)
        std::cerr << "Warning[" << name << "]: add(" << _timeStep << "ms, " << _value.toStdString()
                  << "): Using aligned time: " << timeStepFixed << "ms !" << std::endl;

    values.push_back({timeStepFixed, _value});
}
