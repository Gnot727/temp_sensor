# Temperature Sensor Node

Small C++17 desktop simulation of an embedded temperature monitoring node

The program reads raw scripted ADC samples from a fake temperature sensor,
converts them to fixed-point Celsius values, filters them with a moving average,
and prints CSV telemetry to output.

## Features
- Fake sensor driver with deterministic ADC samples
- Simulated sensor read failures
- Raw ADC to Celsius conversion
- Fixed-point temperature representation using centi-degrees Celsius
- Moving average over last 5 successful samples
- Failure counter for sensor and read errors
- Interfaces for replacing fake drivers with real hardware later

## Telemetry Format
```text
TEMP, sequence, timestamp_ms, raw_temperature_c, filtered_temperature_c, status, failures
```

Example:
```text
TEMP,0,0,23.30,23.30,OK,0
TEMP,1,500,23.70,23.50,OK,0
TEMP,2,1000,24.00,23.66,OK,0
TEMP,3,1500,31.10,25.52,OK,0
TEMP,4,2500,31.90,26.80,OK,1
```

Failed sensor reads increment failure counter and still consume simulated time, does 
not update moving average or increment successful sequence number

## Project Structure
```text
include/
    app/        Application-level monitoring logic
    common/     Result and error types
    drivers/    Sensor interfaces and fake sensor driver
    filters/    Moving average filter
    platform/   Logging interface and stdout logger
src/
    app/
    drivers/
    platform/
    main.cpp
```

## Design Notes

The app stores temperatures as fixed-point centi-degrees Celsius:

```text
23.30 C -> 2330
30.00 C -> 3000
```

This avoids floating-point math in monitoring logic while still allowing logger 
to print human-readable decimal temps.

Sensor interface returns:

```cpp
node::common::Result<std::uint16_t>
```
Which keeps sensor failures explicit without using exceptions

## Build

From repository root:

```powershell
cmake -S . -B build
cmake --build build
```

## Run

With the default Visual Studio generator on Windows:

```powershell
.\build\Debug\temp_sensor_node.exe
```
