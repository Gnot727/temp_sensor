#include "platform/StdoutLogger.hpp"

#include <cstdlib>
#include <iomanip>
#include <iostream>

namespace node::platform{
    
void StdoutLogger::log_temperature(
    std::uint32_t sequence,
    std::uint32_t timestamp_ms,
    std::int32_t raw_temperature_centi,
    std::int32_t filtered_temperature_centi,
    bool warning,
    std::uint32_t failure_count
){
    std::cout << "TEMP," << sequence << "," << timestamp_ms << ",";
    print_temperature(raw_temperature_centi);

    std::cout << ",";

    print_temperature(filtered_temperature_centi);

    std::cout << "," << (warning ? "WARN" : "OK") << "," << failure_count << '\n';
}

void StdoutLogger::print_temperature(std::int32_t temperature_centi){
    const std::int32_t whole = temperature_centi / 100;
    const std::int32_t fractional = std::abs(temperature_centi % 100);

    std::cout << whole << '.' << std::setw(2) <<std::setfill('0') << fractional << std::setfill(' ');
}
} // namespace node::platform