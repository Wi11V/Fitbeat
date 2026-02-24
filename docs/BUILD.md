# Build and Development Guide

## Prerequisites

```bash
# Install Zephyr SDK
# https://docs.zephyrproject.org/latest/develop/getting_started/index.html

# Clone and initialize
git clone https://github.com/yourusername/fitbeat.git
cd fitbeat

# Initialize west workspace
west init -l .

# Update dependencies
west update
```

## Building

```bash
# Build for nrf52840dk_nrf52840
west build -b nrf52840dk_nrf52840 -t menuconfig

# Or with compile commands
west build -b nrf52840dk_nrf52840
```

## Flashing

```bash
# Flash via JLink (default on DK)
west flash

# Or with nrfjprog
nrfjprog -f nrf52 --eraseall
nrfjprog -f nrf52 --program build/zephyr/zephyr.hex
nrfjprog -f nrf52 -r
```

## Debugging

```bash
# Start GDB server
west debug

# In another terminal, connect with arm-none-eabi-gdb
arm-none-eabi-gdb build/zephyr/zephyr.elf
(gdb) target remote :3333
(gdb) break main
(gdb) continue
```

## Serial Console

```bash
# Monitor UART output
screen /dev/ttyUSB0 115200

# Or use miniterm (Python)
python -m serial.tools.miniterm /dev/ttyUSB0 115200
```

## Common Commands

```bash
# Clean build
west build -t clean

# Pristine build
rm -rf build
west build -b nrf52840dk_nrf52840

# List available targets
west --help

# View device configuration
west kconfig
```

## Testing

```bash
# Run any Zephyr tests
west test

# If tests are added later
cd tests/unit
west build -b native_posix
west test
```

