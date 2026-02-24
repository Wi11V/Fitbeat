cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(fitbeat)

# Add source files
target_sources(app PRIVATE
    src/main.c
    src/ble_handler.c
    src/sensor_manager.c
)

# Add include directories
target_include_directories(app PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add driver sources
target_sources(app PRIVATE
    drivers/bmi270/bmi270.c
    drivers/accel_highg/accel_highg.c
    drivers/cap_sensor/cap_sensor.c
    drivers/adc_gpio/adc_gpio.c
)
