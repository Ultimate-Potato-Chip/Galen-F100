# F100 Dashboard

Digital gauge cluster for a 1960-1966 Ford F100.
Integrates with a Holley Sniper 2 EFI system via CAN bus.

## Gauges
- RPM
- Coolant Temperature
- Battery Voltage
- Speed (CAN + VSS fallback)
- Oil Pressure (analog)
- Fuel Level (analog)
- AFR / MAP / MAT (diagnostic)

## Projects

### [`ST77916-Round-Display/`](ST77916-Round-Display/)
ESP32-S3 driver and LVGL UI for the 1.85" round ST77916 displays (QSPI).
Five displays driven individually for each gauge cluster position.

### [`NV3052CGRB-4inch-Square/`](NV3052CGRB-4inch-Square/)
Driver for the 4.0" 720×720 IPS square display (NV3052CGRB, 3SPI + 18-bit RGB).
Currently targeting ESP32-S3 with bounce-buffer rendering.
Migrating to STM32H750VBT6 + LTDC for final product.

## CAN Bus
Holley Sniper 2 extended 29-bit CAN at 1 Mbit/s.
Parsed message IDs documented in [`ST77916-Round-Display/holley_can_parser.c`](ST77916-Round-Display/holley_can_parser.c).

## Hardware
| Component | Part |
|-----------|------|
| MCU (prototype) | ESP32-S3 (8MB PSRAM) |
| MCU (product) | STM32H750VBT6 |
| CAN Transceiver | SN65HVD230 / TJA1051 |
| Round displays | 1.85" ST77916 QSPI ×5 |
| Square display | 4.0" 720×720 NV3052CGRB |
| Oil pressure | 0–5V analog sender |
| Speed | T56 VSS hall sensor |
| Fuel level | Ford resistive sender (10–73Ω) |
