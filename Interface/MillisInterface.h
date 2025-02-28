#pragma once

#include <cstdint>

class MillisInterface {
public:
    virtual ~MillisInterface() = default;

    virtual void init() = 0;
    virtual bool check() = 0;
    virtual void set_delay(uint32_t delay) = 0;

};