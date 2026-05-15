#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "drivers/ITemperatureSensor.hpp"

namespace node::drivers{

//Fake temp sensor used for desktop simulation
//Simulates read failures and returns deterministic ADC samples
class FakeTemperatureSensor final : public ITemperatureSensor{
public:
    FakeTemperatureSensor() = default;

    common::Result<std::uint16_t> read_raw_adc() override;

private:

    struct Sample{
        bool should_fail;
        std::uint16_t raw_adc;
    };

    //array of raw ADC test values, fixed array to avoid dynamic allocation.
    static constexpr std::array<Sample,12> samples_{{
        {false, 290}, 
        {false, 295}, 
        {false, 299}, 
        {false, 387}, 
        {true,  0},
        {false, 397}, 
        {false, 402}, 
        {false, 310}, 
        {true,  0},
        {false, 300}, 
        {false, 410}, 
        {false, 415}, 
    }};

    std::size_t index_{0};
};
}// namespace node::drivers