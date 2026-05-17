#include "app/TemperatureMonitor.hpp"

namespace node::app {
    TemperatureMonitor::TemperatureMonitor(
        drivers::ITemperatureSensor& sensor,
        platform::ILogger& logger,
        std::int32_t warning_threshold_centi
    ): sensor_(sensor), logger_(logger), warning_threshold_centi_(warning_threshold_centi){}

    void TemperatureMonitor::tick(std::uint32_t timestamp_ms){
        const auto reading = sensor_.read_raw_adc();

        if(!reading.ok()){
            ++failure_count_;
            return;
        }
        const std::int32_t raw_temperature_centi = convert_adc_to_centi_celcius(reading.value());

        const std::int32_t filtered_temperature_centi = filter_.push(raw_temperature_centi);

        const bool warning = filtered_temperature_centi > warning_threshold_centi_;
        logger_.log_temperature(
            sequence_,
            timestamp_ms,
            raw_temperature_centi,
            filtered_temperature_centi,
            warning,
            failure_count_
        );

        ++sequence_;
    }

    std::uint32_t TemperatureMonitor::sequence() const{
        return sequence_;
    }

    std::uint32_t TemperatureMonitor::failure_count() const{
        return failure_count_;
    }

    std::int32_t TemperatureMonitor::convert_adc_to_centi_celcius(std::uint16_t raw_adc){
        const std::uint32_t millivolts =
            (static_cast<std::uint32_t>(raw_adc) * reference_millivolts_) / adc_max;

        return static_cast<std::int32_t>(millivolts * 10U);
    }
}
