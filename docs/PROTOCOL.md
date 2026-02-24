# Fitbeat Embedded - BLE Communication Protocol

## Overview

Data is streamed from the nrf52840 to GUI clients over BLE. All multi-byte values are little-endian.

## Data Packet Format

### Sensor Data Packet (20 bytes)
Sent at 10 Hz (100ms intervals)

```
Byte 0:     Packet type (0x01 = sensor data)
Byte 1:     Sequence number (0-255)
Bytes 2-3:  Timestamp (uint16, ms)
Bytes 4-5:  Accel X (int16, mg)
Bytes 6-7:  Accel Y (int16, mg)
Bytes 8-9:  Accel Z (int16, mg)
Bytes 10-11: Gyro X (int16, °/s × 100)
Bytes 12-13: Gyro Y (int16, °/s × 100)
Bytes 14-15: Gyro Z (int16, °/s × 100)
Bytes 16-17: High-G Accel (magnitude, mg)
Bytes 18-19: Cap sensor + ADC data
```

### Status Packet
Sent on events or requested

```
Byte 0:     Packet type (0x02 = status)
Byte 1:     Battery level (0-100%)
Byte 2:     Device status flags
Byte 3:     Temperature (°C)
```

### Command Format (from GUI to device)

```
Byte 0:     Command type
Byte 1:     Parameter byte (varies by command)
```

**Supported Commands:**
- `0x10`: Set sampling rate
- `0x20`: Start recording
- `0x21`: Stop recording
- `0x30`: Query status
- `0x40`: Reset device

## GATT Services

### Sensor Data Service (UUID: TBD)
- **Sensor Data Characteristic**: Notifications, sensor streaming
- **Control Characteristic**: Writable, commands to device
- **Status Characteristic**: Read/notify, device status

## Connection Parameters

- Max connections: 1
- Connection interval: 20-100 ms
- MTU: 20 bytes (standard)
- PHY: 1M (LE 1M)

## Timing

- Sensor sampling: 10 Hz
- BLE update rate: 10 Hz
- Startup time: < 5 seconds

