#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace node::filters{


// Fixed-size moving average filter.
// Stores last WindowSize samples and returns integer average
template <std::size_t WindowSize>
class MovingAverage{
public:
    static_assert(WindowSize > 0U, "WindowSize must be greater than zero");

    std::int32_t push(std::int32_t sample){
        if(count_ < buffer_.size()){
            buffer_[index_] = sample;
            sum_ += sample;
            ++count_;
        } else{
            sum_ -= buffer_[index_];
            buffer_[index_] = sample;
            sum_ += sample;
        }

        index_ = (index_ + 1U) % buffer_.size();

        return average();
    }

    std::int32_t average() const{
        if(count_ == 0U){
            return 0;
        }

        return static_cast<std::int32_t>(sum_ / static_cast<std::int64_t>(count_));
    }
private:
    std::array<std::int32_t,WindowSize> buffer_{};
    std::size_t count_{0};
    std::size_t index_{0};
    std::int64_t sum_{0};
};
} // namespace node::filters