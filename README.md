# Fitbeat Embedded Firmware

Nrf52840-based drumstick motion tracking device with Zephyr RTOS and BLE connectivity.

## Overview

This firmware runs on the nrf52840 microcontroller and provides:
- **BMI270 IMU**: 9-axis motion tracking (accel, gyro, mag)
- **High-G Accelerometer**: High acceleration range for impact detection
- **Capacitive Sensor**: Touch/grip detection
- **ADC/GPIO**: Additional analog and digital inputs
- **BLE**: Wireless data streaming to GUI applications

## Project Structure

```
.
├── src/                    # Main application source files
├── drivers/               # Custom driver implementations
│   ├── bmi270/           # BMI270 IMU driver
│   ├── accel_highg/      # High-G accelerometer driver
│   ├── cap_sensor/       # Capacitive sensor driver
│   └── adc_gpio/         # ADC and GPIO handler
├── include/              # Header files
├── boards/               # Board-specific configurations
├── dts/                  # Device tree overlays
├── app/                  # Application configuration
├── tests/                # Unit tests
├── docs/                 # Documentation
├── CMakeLists.txt        # Build configuration
├── prj.conf              # Zephyr project configuration
└── west.yml              # Workspace manifest
```

## Requirements

- Zephyr SDK (v3.2+)
- nrf-command-line-tools
- arm-none-eabi toolchain
- Python 3.8+

## Building

```bash
# Set up Zephyr environment
source zephyr-env.sh

# Build for nrf52840dk
west build -b nrf52840dk_nrf52840

# Flash to device
west flash
```

## Drivers

### BMI270 (I2C)
6-axis IMU with accelerometer and gyroscope
- Address: 0x68
- Interrupt: GPIO P0.29

### High-G Accelerometer
For measuring high acceleration impacts during drumming

### Capacitive Sensor
For grip/touch detection

### ADC/GPIO
General purpose analog and digital IO

## BLE Communication

Device advertises as "Fitbeat" and provides GATT services for:
- Sensor data streaming
- Configuration
- Battery monitoring

## Debugging

```bash
west debug
```

## Documentation

See [docs/](docs/) for detailed driver documentation and protocol specifications.

## License

[Add your license here]
