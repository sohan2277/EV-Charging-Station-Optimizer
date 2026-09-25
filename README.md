# ⚡ Edge AI Based Smart EV Charging Station Optimizer

<p align="center">
  <img src="https://img.shields.io/badge/ESP32-Embedded%20Controller-blue?style=for-the-badge&logo=espressif" alt="ESP32">
  <img src="https://img.shields.io/badge/ThingsBoard-Cloud-orange?style=for-the-badge" alt="ThingsBoard">
  <img src="https://img.shields.io/badge/MQTT-IoT-green?style=for-the-badge&logo=mqtt" alt="MQTT">
  <img src="https://img.shields.io/badge/C%2B%2B-Arduino-red?style=for-the-badge&logo=cplusplus" alt="C++">
</p>

<p align="center">
  <b>Three-Bay Intelligent EV Charging Station with Cloud Monitoring, Load Optimization, Remote Control & Edge AI</b>
</p>

---

## 📌 Overview

This project implements a **3-bay smart EV charging station** using ESP32-based controllers and ThingsBoard Cloud.

Each charging bay independently monitors electrical parameters and charging state while the station provides centralized monitoring and load management.

### Core capabilities

- 🔌 Three independent charging bays
- ⚡ Voltage, current and power monitoring
- 🔋 Session energy tracking
- 🌡️ Temperature monitoring
- 🧠 Edge-AI prediction/inference
- 📊 Charging-load optimization
- 🎚️ Dynamic throttle control
- 🔁 Relay duty-cycle control
- ☁️ ThingsBoard Cloud telemetry
- 🎛️ Remote RPC controls
- 🚨 Overcurrent / fault indication
- 📈 Individual BAY dashboards
- 🖥️ Master Station dashboard
- 📡 MQTT communication

---

## 🏗️ System Architecture

```text
                         ┌─────────────────────────┐
                         │     ThingsBoard Cloud   │
                         │                         │
                         │  BAY 1 Dashboard        │
                         │  BAY 2 Dashboard        │
                         │  BAY 3 Dashboard        │
                         │  Master Dashboard       │
                         └────────────┬────────────┘
                                      │
                                    MQTT
                                      │
              ┌───────────────────────┼───────────────────────┐
              │                       │                       │
        ┌─────▼─────┐           ┌─────▼─────┐           ┌─────▼─────┐
        │   BAY 1   │           │   BAY 2   │           │   BAY 3   │
        │   ESP32   │           │   ESP32   │           │   ESP32   │
        └─────┬─────┘           └─────┬─────┘           └─────┬─────┘
              │                       │                       │
        Sensors / Relay         Sensors / Relay         Sensors / Relay
```

---

## ⚙️ Main Features

### 1. Real-Time Monitoring

Each bay monitors:

| Parameter | Unit |
|---|---|
| Voltage | V |
| Current | A |
| Power | W |
| Temperature | °C |
| Bay Status | FREE / CHARGING / FAULT |
| Throttle | % |
| Load Decision | Text |

### 2. Station Power Management

The configured **maximum total station load is 6000 W**.

```text
Total Station Power =
BAY 1 Power + BAY 2 Power + BAY 3 Power
```

The 6000 W limit applies to the **complete station**, not to each individual bay.

### 3. Charging Throttle

```text
0%    → Relay OFF
50%   → Approximately 50% duty cycle
70%   → Approximately 70% duty cycle
100%  → Relay continuously ON
```

### 4. Overcurrent Protection

When an overcurrent condition is detected, the optimization logic can reduce the charging throttle and activate the local overload indication.

### 5. Plug-In / Plug-Out Detection

```text
FREE
  │ Plug-in
  ▼
CHARGING
  │ Plug-out
  ▼
FREE
```

---

## 🎛️ Remote RPC Controls

### `setRelayState`

ON:

```json
{"state": true}
```

OFF:

```json
{"state": false}
```

### `setThrottle`

Example:

```json
{"level": 60}
```

Range:

```text
0–100%
```

### `getStatus`

Requests the current device status.

### AUTO Mode

Returns control to automatic optimization through the configured AUTO RPC/dashboard control.

---

## ☁️ ThingsBoard

ThingsBoard Cloud is used for:

- MQTT telemetry
- Dashboard visualization
- Remote RPC
- Alarm monitoring
- Historical charts
- Station-level monitoring

Dashboards:

- BAY 1
- BAY 2
- BAY 3
- Master Station

See the separate **ThingsBoard README** for dashboard JSON import instructions.

---
## 🧪 Wokwi Simulation

The project includes Wokwi simulation files for the charging-bay controllers.

The simulations allow the project to be tested without physical hardware.

Simulation includes:

- ESP32 controller
- Voltage sensing
- Current sensing
- Temperature sensing
- Relay control
- EV plug-in / plug-out buttons
- Status LEDs
- MQTT connectivity
- Charging optimization logic

The Wokwi simulation files are available in:

`/wokwi/`

Refer to the Wokwi README for simulation-specific instructions.

---

## 📂 Suggested Project Structure

```text
EV-Charging-Station-Optimizer/
│
├── README.md
│
├── firmware/
│   ├── BAY1/
│   ├── BAY2/
│   └── BAY3/
│
├── wokwi/
│   └── BAY1, BAY2, BAY3/ 
│       ├── diagram.json
│       ├── wokwi.toml
│       └── README.md
│
└── ThingsBoard/
    ├── BAY_01_Dashboard.json
    ├── BAY_02_Dashboard.json
    ├── BAY_03_Dashboard.json
    ├── Master_Station_Dashboard.json
    └── README.md

```

> Adjust the structure to match your final repository.

---

## 🚀 Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/sohan2277/EV-Charging-Station-Optimizer.git
cd EV-Charging-Station-Optimizer
```

### 2. Configure the ESP32

Configure your local Wi-Fi and ThingsBoard/MQTT credentials.

Do **not** commit real credentials or device tokens.

### 3. Upload the firmware

Compile and upload the firmware to the ESP32 using your configured Arduino/PlatformIO environment.

### 4. Configure ThingsBoard

Create/register devices for:

```text
BAY 1
BAY 2
BAY 3
```

Use the corresponding device credentials/tokens in the firmware configuration.

### 5. Import dashboards

Download the dashboard JSON files and follow `README.md`.

---

## 🔐 Security Notes

Never commit:

- Wi-Fi passwords
- ThingsBoard access tokens
- MQTT credentials
- API keys
- Private certificates

Use local/private configuration for credentials.

---

## 📊 Dashboard Structure

### BAY Dashboards

Each BAY dashboard focuses on its own charger:

- Status
- Voltage
- Current
- Power
- Temperature
- Throttle
- Load decision
- Remote controls

### Master Station Dashboard

The Master dashboard focuses on the complete station:

- Total station power
- 6000 W station limit
- BAY 1/2/3 status
- Charging/free bay count
- Station energy
- Power comparison
- Power history
- Station alarms

---

## 🧪 Testing Checklist

- [ ] ESP32 connects to Wi-Fi
- [ ] MQTT connection succeeds
- [ ] Telemetry reaches ThingsBoard
- [ ] Plug-in changes BAY status
- [ ] Plug-out returns BAY to FREE
- [ ] Voltage/current/power update
- [ ] Relay responds correctly
- [ ] Throttle changes relay duty cycle
- [ ] Overcurrent protection works
- [ ] Red overload indication works
- [ ] RPC relay control works
- [ ] RPC throttle control works
- [ ] AUTO mode works
- [ ] BAY dashboards update
- [ ] Master dashboard updates
- [ ] ThingsBoard alarms update correctly

---

## ⚠️ Important Configuration

```text
Maximum station load = 6000 W
Maximum simulated bay voltage = 250 V
Maximum simulated bay current = 32 A
```

Although:

```text
250 V × 32 A = 8000 W
```

the **8000 W value is the theoretical individual-bay electrical range**, not the configured station limit.

The configured total station limit is:

```text
6000 W
```

---

<p align="center">
  ⚡ <b>Smart Charging • Intelligent Load Management • Cloud Monitoring</b> ⚡
</p>
