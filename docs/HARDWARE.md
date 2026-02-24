# Hardware Setup

## nrf52840 DK (Development Kit)

### Pin Assignments

#### I2C (I2C0)
- SDA: P0.26
- SCL: P0.27

#### SPI (SPI1) - High-G Accelerometer
- MISO: P0.32
- MOSI: P0.3
- SCK: P0.31
- CS: P0.30

#### Interrupts
- BMI270 INT1: P0.29
- High-G INT: P0.28

#### ADC
- Channel 0: P0.4
- Channel 1: P0.5
- Channel 2: P0.6

#### GPIO
- General purpose: P0.7 - P0.27 (as available)

### Sensor I2C Addresses

| Sensor | I2C Address | Notes |
|--------|-------------|-------|
| BMI270 | 0x68 | 6-axis IMU |
| (Other I2C sensors) | 0x## | TBD |

## Custom Board Setup

When moving to a custom PCB:
1. Create board definition in `boards/custom_board/`
2. Update device tree overlay with actual pin assignments
3. Verify power supply (3.3V for all components)
4. Add decoupling capacitors near each sensor

