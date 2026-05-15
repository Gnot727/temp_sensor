#pragma once

#include <cstdint>

#include "common/Result.hpp"

namespace node::drivers{

//Defines abstract temperature sensor interface used by the monitoring app
//May read from fake data, ADC hardware etc...

class ITemperatureSensor{

public:
    virtual ~ITemperatureSensor() = default;

    //12 bit ADC value ranges from 0-4095, fits in std::uint16_t
    virtual common::Result<std::uint16_t> read_raw_adc() = 0;
};
} // namespace node::drivers
