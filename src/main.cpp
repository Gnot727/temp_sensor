#include <cstdint>

#include "app/TemperatureMonitor.hpp"
#include "drivers/FakeTemperatureSensor.hpp"
#include "platform/StdoutLogger.hpp"

int main(){
    constexpr std::uint32_t sample_period_ms = 500;
    constexpr std::uint32_t tick_count = 20;
    constexpr std::int32_t warning_threshold_centi = 3000;

    node::drivers::FakeTemperatureSensor sensor;
    node::platform::StdoutLogger logger;

    node::app::TemperatureMonitor monitor(
        sensor,
        logger,
        warning_threshold_centi
    );

    for(std::uint32_t tick = 0; tick < tick_count; ++tick){
        const std::uint32_t timestamp_ms = tick * sample_period_ms;
        monitor.tick(timestamp_ms);
    }

    return 0;
}