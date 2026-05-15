#pragma once

#include "common/Error.hpp"


namespace node::common{

//Stores either a successful value or an error code
// Intended for embedded-style code where exceptions are avoided
template<typename T>
class Result{
public:
    static constexpr Result success(const T& value){
        return Result(value, Error::Ok);
    }

    static constexpr Result failure(Error error){
        return Result(T{}, error);
    }

    constexpr bool ok() const{
        return error_ == Error::Ok;
    }

    constexpr const T& value() const{
        return value_;
    }

    constexpr Error error() const {
        return error_;
    }

private:
    Result(const T& value, Error error): value_(value), error_(error) {}

    T value_{};
    Error error_{Error::Ok};
};

} //namespace node::common
