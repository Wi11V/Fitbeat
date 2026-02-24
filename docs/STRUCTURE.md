# Fitbeat Embedded Project Structure

```
fitbeat/
├── src/                    # Main application source code
│   ├── main.c             # Entry point
│   ├── ble_handler.c      # BLE communication
│   └── sensor_manager.c   # Sensor data aggregation
│
├── drivers/               # Custom sensor drivers
│   ├── bmi270/           # 6-axis IMU driver
│   │   ├── bmi270.h
│   │   └── bmi270.c
│   ├── accel_highg/      # High-G accelerometer driver
│   │   ├── accel_highg.h
│   │   └── accel_highg.c
│   ├── cap_sensor/       # Capacitive sensor driver
│   │   ├── cap_sensor.h
│   │   └── cap_sensor.c
│   └── adc_gpio/         # ADC and GPIO handlers
│       ├── adc_gpio.h
│       └── adc_gpio.c
│
├── include/              # Header files
│   ├── sensor_manager.h
│   └── ble_handler.h
│
├── boards/              # Board definitions
│   └── nrf52840dk_nrf52840/
│
├── dts/                # Device tree overlays
│   └── fitbeat.overlay
│
├── app/                # Application configuration
│
├── tests/              # Unit tests
│
├── docs/               # Documentation
│   ├── PROTOCOL.md    # BLE communication protocol
│   ├── HARDWARE.md    # Hardware setup and pinouts
│   └── BUILD.md       # Build and development guide
│
├── CMakeLists.txt     # CMake build configuration
├── prj.conf          # Zephyr project configuration
├── west.yml          # West workspace manifest
├── README.md         # Project overview
├── .gitignore        # Git ignore rules
└── .git/             # Git repository
```

## Next Steps

1. **Implement Drivers**: Complete the sensor driver implementations
2. **BLE GATT**: Define and implement GATT services and characteristics
3. **Testing**: Create unit tests for drivers and main logic
4. **Custom Board**: Once validated, port to custom PCB board definition
5. **GUI Integration**: Coordinate with GUI repo on protocol implementation

