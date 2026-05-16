#pragma once

#include <cstdint>

namespace node::platform{


//Defines telemetry output interface used by monitoring app

class ILogger{
public:
    virtual ~ILogger() = default;

    virtual void log_temperature(
        std::uint32_t sequence,
        std::uint32_t timestamp_ms,
        std::int32_t raw_temperature_centi,
        std::int32_t filtered_temperature_centi,
        bool warning,
        std::uint32_t failure_count
    ) = 0;
};

} // namespace node::platform