#include "item.h"

Universe1::Video::Item::Item(const std::string &_name)
    : name(_name)
{
}

bool Universe1::Video::Item::initialize(const uint64_t _duration)
{
    bool result = true;
    for (DynamicProperty *p : props)
        if (!p->initialize(_duration))
            result = false;

    return result;
}
