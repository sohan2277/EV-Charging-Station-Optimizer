# ⚡ Edge AI Based Smart EV Charging Station Optimizer

<p align="center">
  <img src="https://img.shields.io/badge/ESP32-Embedded%20Controller-blue?style=for-the-badge&logo=espressif" alt="ESP32">
  <img src="https://img.shields.io/badge/ThingsBoard-Cloud-orange?style=for-the-badge" alt="ThingsBoard">
  <img src="https://img.shields.io/badge/MQTT-IoT-green?style=for-the-badge&logo=mqtt" alt="MQTT">
  <img src="https://img.shields.io/badge/C%2B%2B-Arduino-red?style=for-the-badge&logo=cplusplus" alt="C++">
  <img src="https://img.shields.io/badge/Wokwi-Simulation-purple?style=for-the-badge" alt="Wokwi">
</p>

<p align="center">
  <b>Three-Bay Intelligent EV Charging Station with Real-Time Monitoring, Load Optimization, Remote Control & Edge AI</b>
</p>

---

## 📑 Table of Contents

1. [Overview](#1-overview)
2. [Objectives](#2-objectives)
3. [Key Features](#3-key-features)
4. [System Architecture](#4-system-architecture)
5. [Charging Bay Monitoring](#5-charging-bay-monitoring)
6. [Load Management & Optimization](#6-load-management--optimization)
7. [Edge AI](#7-edge-ai)
8. [Charging Control](#8-charging-control)
9. [Overcurrent & Fault Handling](#9-overcurrent--fault-handling)
10. [ThingsBoard Cloud](#10-thingsboard-cloud)
11. [Remote RPC Control](#11-remote-rpc-control)
12. [Wokwi Simulation](#12-wokwi-simulation)
13. [Technologies Used](#13-technologies-used)
14. [Repository Structure](#14-repository-structure)
15. [Getting Started](#15-getting-started)
16. [Station Configuration](#16-station-configuration)
17. [Testing](#17-testing)
18. [Security](#18-security)
19. [Documentation](#19-documentation)

---

# 1. Overview

The **Edge AI Based Smart EV Charging Station Optimizer** is a simulated smart charging management system built using **three independent ESP32-controlled charging bays**.

Each bay independently monitors its charging parameters and communicates with **ThingsBoard Cloud** through MQTT. A centralized master dashboard provides a station-level view of all three bays and their combined power consumption.

The system combines:

- Real-time charging telemetry
- Dynamic load management
- Charging throttle control
- Relay control
- Overcurrent handling
- Remote device control
- Edge AI-based prediction/inference
- Cloud-based monitoring

The complete system can be developed and tested using **Wokwi simulation**, without requiring physical charging hardware.

---

# 2. Objectives

The main objectives of the project are:

- Develop a multi-bay EV charging management system.
- Monitor charging parameters in real time.
- Collect charging data for prediction and analysis.
- Manage the total station power demand.
- Dynamically control charging throttle.
- Provide remote charging control through ThingsBoard.
- Detect overcurrent and fault conditions.
- Provide individual and centralized dashboards.
- Demonstrate Edge AI-based charging optimization.

---

# 3. Key Features

| Feature | Description |
|---|---|
| 🔌 3 Charging Bays | Three independent ESP32-controlled charging bays |
| ⚡ Parameter Monitoring | Voltage, current, power and temperature monitoring |
| 🔋 Energy Tracking | Charging session energy monitoring |
| 📡 MQTT | Communication between ESP32 devices and ThingsBoard |
| ☁️ Cloud Monitoring | Real-time ThingsBoard telemetry and dashboards |
| 🧠 Edge AI | Charging-data prediction/inference |
| 📊 Load Optimization | Dynamic management of station charging demand |
| 🎚️ Throttle Control | Adjustable charging output from 0–100% |
| 🔁 Relay Control | Charging ON/OFF control |
| 🚨 Overcurrent Detection | Detection and response to abnormal current |
| 🔌 Plug Detection | EV plug-in / plug-out state handling |
| 🎛️ Remote RPC | Remote relay, throttle and status control |
| 🖥️ Master Dashboard | Centralized monitoring of the complete station |
| 🧪 Wokwi | Hardware-free simulation and testing |

---

# 4. System Architecture

The system consists of three independent charging bays connected to ThingsBoard Cloud.

```text
                         ┌──────────────────────────┐
                         │     ThingsBoard Cloud    │
                         │                          │
                         │  BAY 1 Dashboard         │
                         │  BAY 2 Dashboard         │
                         │  BAY 3 Dashboard         │
                         │  Master Dashboard        │
                         └────────────┬─────────────┘
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
        ┌─────▼─────┐           ┌─────▼─────┐           ┌─────▼─────┐
        │  Sensors  │           │  Sensors  │           │  Sensors  │
        │  Relay    │           │  Relay    │           │  Relay    │
        └───────────┘           └───────────┘           └───────────┘
```

### System Flow

```text
Sensors
   │
   ▼
ESP32 Charging Bay
   │
   ├── Local Monitoring
   ├── Charging Control
   ├── Throttle Control
   └── Optimization Logic
   │
   ▼
MQTT
   │
   ▼
ThingsBoard Cloud
   │
   ├── BAY Dashboards
   └── Master Dashboard
```

Each bay operates independently while the master dashboard provides a combined view of the complete charging station.

---

# 5. Charging Bay Monitoring

Each charging bay monitors its own operating parameters.

| Parameter | Unit | Purpose |
|---|---:|---|
| Voltage | V | Monitor charging voltage |
| Current | A | Monitor charging current |
| Power | W | Calculate charging power |
| Temperature | °C | Monitor simulated temperature |
| Energy | Wh | Track charging energy |
| Bay Status | — | FREE / CHARGING / FAULT |
| Throttle | % | Control charging level |
| Load Decision | — | Display optimization decision |

### Plug-In / Plug-Out State

```text
             Plug-in
FREE ───────────────────► CHARGING
 ▲                            │
 │                            │ Plug-out
 └────────────────────────────┘
```

The current bay state is reflected on the corresponding ThingsBoard dashboard.

---

# 6. Load Management & Optimization

The charging station has a configured maximum total power limit of:

```text
6000 W
```

The total station power is calculated as:

```text
Total Station Power =
BAY 1 Power + BAY 2 Power + BAY 3 Power
```

The optimization logic evaluates the charging demand of the three bays and adjusts charging throttle when required.

### Load Management Flow

```text
       BAY 1 Power ─┐
       BAY 2 Power ─┼──► Total Station Load
       BAY 3 Power ─┘
                         │
                         ▼
                  Compare with
                   6000 W Limit
                         │
                 ┌───────┴───────┐
                 │               │
              Within          Exceeds
               Limit            Limit
                 │               │
                 ▼               ▼
             Continue       Optimize Load
                             / Reduce Throttle
```

The **6000 W limit applies to the complete station**, not to each individual bay.

---

# 7. Edge AI

Charging data from the individual bays can be used for **Edge AI-based prediction/inference** and charging-load management.

The project uses charging parameters to support:

- Charging demand analysis
- Load prediction
- Charging optimization
- Dynamic throttle decisions
- Station-level load management

The Edge AI component works together with the charging-control logic to make the charging system more responsive to changing load conditions.

---

# 8. Charging Control

The charging throttle controls the simulated relay duty cycle.

| Throttle | Relay Behaviour |
|---:|---|
| 0% | Relay OFF |
| 50% | Approximately 50% duty cycle |
| 70% | Approximately 70% duty cycle |
| 100% | Relay continuously ON |

This allows the charging output to be dynamically adjusted according to the station's load-management requirements.

---

# 9. Overcurrent & Fault Handling

The system monitors charging current for abnormal conditions.

When an overcurrent condition is detected, the control logic can:

1. Detect the abnormal current.
2. Reduce the charging throttle.
3. Activate the overload indication.
4. Update the bay status.
5. Report the condition to ThingsBoard.

```text
Current Monitoring
        │
        ▼
   Overcurrent?
     /       \
   No         Yes
   │           │
   ▼           ▼
Continue    Reduce Throttle
Charging        │
                ▼
          Overload Indication
                │
                ▼
          Update Dashboard
```

---

# 10. ThingsBoard Cloud

**ThingsBoard Cloud** is used as the monitoring and remote-control layer of the system.

### Cloud Functions

| Function | Purpose |
|---|---|
| MQTT Telemetry | Receive charging data from ESP32 |
| Dashboards | Visualize real-time station data |
| RPC | Remotely control charging bays |
| Alarms | Display fault/overload conditions |
| Historical Data | Monitor charging trends |
| Master Dashboard | Monitor the complete charging station |

### Dashboards

| Dashboard | Purpose |
|---|---|
| BAY 1 | Monitor and control Bay 1 |
| BAY 2 | Monitor and control Bay 2 |
| BAY 3 | Monitor and control Bay 3 |
| Master Station | Monitor the complete charging station |

---

# 11. Remote RPC Control

ThingsBoard RPC is used to remotely control the charging bays.

## `setRelayState`

### Turn ON

```json
{
  "state": true
}
```

### Turn OFF

```json
{
  "state": false
}
```

## `setThrottle`

Example:

```json
{
  "level": 60
}
```

Supported range:

```text
0–100%
```

## `getStatus`

Requests the current charging-bay status.

## AUTO Mode

Returns control to the automatic charging optimization logic.

---

# 12. Wokwi Simulation

The project includes **Wokwi simulation files** for testing the charging-bay controllers without physical hardware.

### Simulation Includes

| Component | Purpose |
|---|---|
| ESP32 | Charging-bay controller |
| Voltage Sensor | Simulated voltage measurement |
| Current Sensor | Simulated current measurement |
| Temperature Sensor | Simulated temperature monitoring |
| Relay | Charging control |
| Plug Button | EV plug-in / plug-out simulation |
| LEDs | Status and overload indication |
| MQTT | Cloud communication |
| Optimization Logic | Charging-load management |

Simulation files are available in:

```text
/wokwi/
```

---

# 13. Technologies Used

| Technology | Role in Project |
|---|---|
| **ESP32** | Embedded controller for each charging bay |
| **C++ / Arduino** | Firmware development |
| **MQTT** | Device-to-cloud communication |
| **ThingsBoard Cloud** | Monitoring, dashboards and remote control |
| **Wokwi** | Embedded system simulation |
| **Edge AI** | Charging-data prediction/inference |
| **Git / GitHub** | Source-code management |

---

# 14. Repository Structure

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
│   ├── BAY1/
│   ├── BAY2/
│   └── BAY3/
│
└── ThingsBoard/
    ├── BAY_01_Dashboard.json
    ├── BAY_02_Dashboard.json
    ├── BAY_03_Dashboard.json
    ├── Master_Station_Dashboard.json
    └── README.md
```

---

# 15. Getting Started

## 15.1 Clone the Repository

```bash
git clone https://github.com/sohan2277/EV-Charging-Station-Optimizer.git
cd EV-Charging-Station-Optimizer
```

## 15.2 Configure ESP32

Configure the required:

- Wi-Fi credentials
- ThingsBoard server
- Device credentials
- MQTT configuration

> Do not commit passwords, access tokens, API keys, or other sensitive credentials.

## 15.3 Configure the Charging Bays

The system uses three independent ESP32 controllers:

```text
BAY 1 → ESP32
BAY 2 → ESP32
BAY 3 → ESP32
```

Configure the corresponding firmware for each bay.

## 15.4 Configure ThingsBoard

Create/register the following devices:

```text
BAY 1
BAY 2
BAY 3
```

Configure the corresponding device credentials in the firmware.

## 15.5 Import Dashboards

Dashboard JSON files are available in:

```text
ThingsBoard/
```

Refer to the ThingsBoard documentation included in the repository for the import procedure.

---

# 16. Station Configuration

| Parameter | Configuration |
|---|---:|
| Number of Charging Bays | 3 |
| Maximum Station Load | 6000 W |
| Maximum Simulated Bay Voltage | 250 V |
| Maximum Simulated Bay Current | 32 A |
| Communication Protocol | MQTT |
| Controller | ESP32 |
| Cloud Platform | ThingsBoard |
| Simulation Platform | Wokwi |

### Power Reference

The theoretical electrical power corresponding to the simulated maximum voltage and current is:

```text
250 V × 32 A = 8000 W
```

This represents the theoretical electrical range of an individual simulated bay.

The configured **total station power limit is 6000 W**.

```text
Configured Station Limit = 6000 W
```

---

# 17. Testing

The system can be tested using the following checklist.

### Connectivity

- [ ] ESP32 connects to Wi-Fi
- [ ] MQTT connection succeeds
- [ ] Telemetry reaches ThingsBoard

### Charging Operation

- [ ] Plug-in changes bay status
- [ ] Plug-out returns bay to FREE
- [ ] Relay responds correctly
- [ ] Throttle changes relay duty cycle
- [ ] AUTO mode works

### Remote Control

- [ ] RPC relay control works
- [ ] RPC throttle control works
- [ ] `getStatus` returns the current state

### Monitoring

- [ ] Voltage updates
- [ ] Current updates
- [ ] Power updates
- [ ] Temperature updates
- [ ] Energy tracking works
- [ ] Individual dashboards update
- [ ] Master dashboard updates

### Protection & Optimization

- [ ] Overcurrent detection works
- [ ] Overload indication works
- [ ] Load optimization responds correctly
- [ ] Station power remains within the configured limit

---

# 18. Security

Sensitive credentials should never be committed to the repository.

Do not upload:

```text
Wi-Fi passwords
ThingsBoard access tokens
MQTT credentials
API keys
Private certificates
```

Use local configuration files or environment variables for development credentials.

---

# 19. Documentation

Additional project documentation is available in:

```text
wokwi/README.md
ThingsBoard/README.md
```

These documents contain simulation-specific and dashboard-specific information.

---

## 📌 Project Summary

| Category | Details |
|---|---|
| Project Type | Smart EV Charging Management System |
| Controllers | 3 × ESP32 |
| Charging Bays | 3 Independent Bays |
| Communication | MQTT |
| Cloud Platform | ThingsBoard |
| Simulation | Wokwi |
| AI Component | Edge AI Prediction / Inference |
| Station Power Limit | 6000 W |
| Remote Control | ThingsBoard RPC |
| Monitoring | Individual + Master Dashboards |

---

<p align="center">
  <b>⚡ Smart Charging • Load Optimization • Cloud Monitoring • Edge AI</b>
</p>
