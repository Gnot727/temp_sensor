#pragma once

#include <cstdint>

#include "drivers/ITemperatureSensor.hpp"
#include "filters/MovingAverage.hpp"
#include "platform/ILogger.hpp"

namespace node::app{

// handles sensor reading, conversion, filtering, warning detection
// produces telemetry output for temp monitoring node

class TemperatureMonitor{

public:
    TemperatureMonitor(
        drivers::ITemperatureSensor& sensor,
        platform::ILogger& logger,
        std::int32_t warning_threshold_centi
    );

    void tick(std::uint32_t timestamp_ms);

    std::uint32_t sequence() const;
    std::uint32_t failure_count() const;

private:
    static constexpr std::uint16_t adc_max{4095};
    static constexpr std::uint32_t reference_millivolts_{3300};

    static std::int32_t convert_adc_to_centi_celcius(std::uint16_t raw_adc);

    drivers::ITemperatureSensor& sensor_;
    platform:: ILogger& logger_;

    std::int32_t warning_threshold_centi_;
    std::uint32_t sequence_{0};
    std::uint32_t failure_count_{0};
    filters::MovingAverage<5> filter_;
};

} //namespace node::app

