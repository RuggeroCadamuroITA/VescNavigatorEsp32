# VescNavigator ESP32 🧠⚡

Firmware for ESP32 S3 acting as the hardware hub of the VescNavigator system.

This controller receives navigation packets via BLE from the Android app and merges them with live VESC motor telemetry.

---

## 📌 Overview

The ESP32 firmware is designed for embedded HUD dashboards in electric vehicles.

It handles:

- BLE communication with Android
- Navigation packet decoding
- VESC UART telemetry
- Real-time electrical calculations

The goal is to drive a compact display showing both navigation and vehicle data.

---

## ✨ Features

- BLE GATT server
- Secure Android pairing
- Navigation packet parsing
- VESC UART communication (19200 baud)
- Voltage / Current monitoring
- Wattage calculation
- Battery percentage estimation
- ERPM-based speed calculation

---

## ⚡ Telemetry Logic

The firmware calculates:

- Voltage
- Current
- Power (W)
- Battery %
- Vehicle speed

Optimized for VESC controller data streams.

---

## 🚀 Getting Started

1. Open project in PlatformIO
2. Configure ESP32 S3 board in `platformio.ini`
3. Flash firmware
4. Open Serial Monitor (115200 baud)

Incoming BLE packets will appear in the console.

---

## 📈 Roadmap

- Display hardware integration
- TFT graphics engine
- Unified HUD rendering
- Handlebar mounting system
- Haptic feedback support

---

## 🔗 Companion App

Works with:

👉 **VescNavigator Android App**

(Separate repository)

---

## 👨‍💻 Author

Ruggero Cadamuro  
Innovative EV Solutions
