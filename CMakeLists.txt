cmake_minimum_required(VERSION 3.20)

project(temp_sensor_node LANGUAGES CXX)

add_executable(temp_sensor_node
    src/main.cpp
    src/app/TemperatureMonitor.cpp
    src/drivers/FakeTemperatureSensor.cpp
    src/platform/StdoutLogger.cpp
)

target_include_directories(temp_sensor_node
    PRIVATE
        include
)

target_compile_features(temp_sensor_node
    PRIVATE 
        cxx_std_17

)   

if(MSVC)
    target_compile_options(temp_sensor_node
        PRIVATE 
            /W4
    )
else()
    target_compile_options(temp_sensor_node
        PRIVATE 
            -Wall
            -Wextra
            -Wpedantic
    )
endif()