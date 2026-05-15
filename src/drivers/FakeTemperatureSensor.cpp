#include "drivers/FakeTemperatureSensor.hpp"
#include "common/Error.hpp"

namespace node::drivers{

// Returns the next scripted ADC sample or a simulated failure
common::Result<std::uint16_t> FakeTemperatureSensor::read_raw_adc(){
    const Sample& sample = samples_[index_];

    //wraps back to beginning when reaches end
    index_ = (index_ + 1U) % samples_.size();

    if(sample.should_fail){
        return common::Result<std::uint16_t>::failure(
            common::Error::SensorReadFailed
        );
    }
    return common::Result<std::uint16_t>::success(sample.raw_adc);
}

} // namespace node::drivers