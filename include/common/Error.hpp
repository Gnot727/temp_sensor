#pragma once

#include <cstdint>

namespace node::common {

// Defines common error codes used across the temperature monitoring node.
enum class Error : std::uint8_t {
    Ok = 0,
    SensorReadFailed,
    InvalidRawValue,
    BufferTooSmall
};

constexpr const char* to_string(Error error){
    switch (error)
    {
    case Error::Ok: return "Ok";
    case Error::SensorReadFailed: return "SensorReadFailed";
    case Error::InvalidRawValue: return "InvalidRawValue";
    case Error::BufferTooSmall: return "BufferTooSmall";
     
    }

    return "Unknown";
}
} // namespace node::common
