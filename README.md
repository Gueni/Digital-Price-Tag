
# 📦 Digital Price Tag – ANNA-B112 + E-Ink + CR Battery

A low-power, wireless **digital price tag** using:

- **ANNA-B112-01B** Bluetooth LE module  
- **E-Ink Display** (e.g., 2.13” GDEH0213B72)
- **CR2032 Battery**
- Designed for **supermarket shelf labeling**, with OTA updates via BLE

---
<p align="center">
  <img  src="/2d.png">
</p>

<p align="center">
  <img  src="/3d.png">
</p>


## 📘 Features

- BLE-enabled wireless updates via central device (app/gateway)
- Ultra-low-power mode suitable for coin cell operation
- Bistable E-Ink display – no power needed to retain the image
- Custom GATT service for remote pricing updates
- Sleep current < 2 µA (target)
- Display refreshes triggered by BLE or timer

---

## 📦 Hardware Components

| Component           | Description                          |
|--------------------|--------------------------------------|
| ANNA-B112-01B      | BLE module (nRF52832)                |
| E-Ink Display       | 2.13” SPI EPD (GDEH0213B72 or similar) |
| CR2032 Battery     | 3V coin cell                          |
| LDO Regulator      | 3.3V LDO for stable display voltage   |
| Level shifter      | Optional, for voltage compatibility  |
| Passive components | Pull-ups, caps, resistors            |

---

## 🧠 Firmware Architecture

- **Nordic SDK** or **nRF Connect SDK (Zephyr RTOS)**
- **BLE Custom GATT Service**
  - `UUID 0x180C` – Price Tag Service
  - Characteristics:
    - `UUID 0x2A56` – Text/Price (UTF-8 string)
    - `UUID 0x2A57` – Display Refresh Trigger
- E-Ink driver via SPI (Waveshare compatible)
- Deep Sleep using `sd_power_system_off()` until BLE wake or RTC interrupt

---

## 🔧 Setup Instructions

1. **Hardware Wiring**
   - Connect E-Ink SPI lines (CLK, MOSI, CS, DC, RST, BUSY) to ANNA-B112
   - Power via CR2032 with 3.3V LDO regulator
   - Add pull-ups for I2C (if used), and decoupling capacitors

2. **Build and Flash**
   - Clone project and configure for your SDK
   - Compile using SEGGER Embedded Studio or `west` (if using Zephyr)
   - Flash via SWD or set up BLE DFU for OTA firmware upgrades

3. **BLE Test**
   - Install **nRF Connect** mobile app
   - Scan, connect, and write pricing string to `0x2A56`
   - Write any value to `0x2A57` to trigger refresh

---

## 📉 Power Considerations

| Mode            | Power Consumption |
|-----------------|-------------------|
| Sleep (RTC)     | ~1.5 µA           |
| BLE Advertising | ~10–20 µA average |
| Display Refresh | ~15–20 mA (spike) |

- Target average: **<10 µA** with infrequent updates
- Battery Life Estimate: **~1 year** on CR2032

---

## 📁 Directory Structure

```
project/
├── src/
│   ├── main.c
│   ├── ble_price_service.c
│   └── eink_driver.c
├── include/
│   └── eink_driver.h
├── sdk_config.h
├── Makefile / CMakeLists.txt
└── README.md
```

---

## 📡 OTA and Gateway

Optional BLE gateway (e.g., ESP32, Raspberry Pi) can:

- Push price updates over BLE
- Schedule updates via MQTT / HTTP
- Manage multiple shelf labels in bulk

---

## 🔄 Future Enhancements

- NFC tap-to-update fallback
- QR code on E-Ink
- Temp/humidity sensors for smart shelves
- Battery voltage and signal strength reporting

---

## 📚 References

- [ANNA-B112 Datasheet](https://www.u-blox.com/en/product/anna-b1-series)
- [Nordic nRF52 SDK](https://www.nordicsemi.com/Products/Development-software/nRF5-SDK)
- [Waveshare E-Ink Displays](https://www.waveshare.com/wiki/Main_Page)
- [BLE GATT Specifications](https://www.bluetooth.com/specifications/gatt/)

---


