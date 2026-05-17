#pragma once

#include "platform/ILogger.hpp"

namespace node::platform{

// Console logger used by desktop simulation writing telemetry to CSV and writes to stdout
class StdoutLogger final : public ILogger{

public:
    void log_temperature(
        std::uint32_t sequence,
        std::uint32_t timestamp_ms,
        std::int32_t raw_temperature_centi,
        std::int32_t filtered_temperature_centi,
        bool warning,
        std::uint32_t failure_count
    ) override;

private:
    static void print_temperature(std::int32_t temperature_centi);
};

} // namespace node::platform