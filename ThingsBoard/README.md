# ☁️ ThingsBoard Dashboard Package

<p align="center">
  <img src="https://img.shields.io/badge/ThingsBoard-Cloud-orange?style=for-the-badge" alt="ThingsBoard">
  <img src="https://img.shields.io/badge/MQTT-IoT-green?style=for-the-badge&logo=mqtt" alt="MQTT">
  <img src="https://img.shields.io/badge/EV-Charging-blue?style=for-the-badge" alt="EV Charging">
  <img src="https://img.shields.io/badge/Dashboard-JSON-purple?style=for-the-badge" alt="Dashboard JSON">
</p>

<p align="center">
  <b>ThingsBoard Cloud dashboards for Smart EV Charging Station</b>
</p>

---

## 📌 About

This folder contains the **ThingsBoard Cloud dashboard JSON exports** for the Smart EV Charging Station.

### Included dashboards

```text
BAY 1
BAY 2
BAY 3
MASTER STATION
```

Each BAY dashboard provides detailed monitoring/control for one charging bay.

The Master Station dashboard provides an overview of the complete station.

---

## 📦 Dashboard Files

Recommended structure:

```text
ThingsBoard/
│
├── BAY1-dashboard.json
├── BAY2-dashboard.json
├── BAY3-dashboard.json
├── Master-dashboard.json
└── README.md
```

---

# 🔌 BAY Dashboards

Each BAY dashboard can contain:

- Bay Status
- Voltage
- Current
- Power
- Temperature
- Throttle Level
- Load Decision
- Relay control
- Throttle control
- AUTO control
- Status/RPC controls

### Device mapping

```text
BAY 1 Dashboard → BAY 1 Device
BAY 2 Dashboard → BAY 2 Device
BAY 3 Dashboard → BAY 3 Device
```

---

# 🏭 Master Station Dashboard

The Master dashboard provides station-level information:

- ⚡ Total Station Power
- 🔋 Total Station Energy
- 🚦 BAY 1 status
- 🚦 BAY 2 status
- 🚦 BAY 3 status
- 📊 BAY power comparison
- 📈 Station power history
- 🚨 Station alarms
- 🔢 Charging/free bay count
- ⚠️ 6000 W station-load monitoring

### Total Station Power

```text
BAY 1 Power
     +
BAY 2 Power
     +
BAY 3 Power
     =
Total Station Power
```

Configured station limit:

```text
6000 W
```

This is the **combined station limit**, not an individual BAY limit.

---

# 🚀 How to Import the Dashboard JSON Files

## Step 1 — Open ThingsBoard Cloud

Log in to your ThingsBoard Cloud account.

Open the **Dashboards** section.

## Step 2 — Import a Dashboard

Use the dashboard **Import** option available in your ThingsBoard Cloud interface.

Select the required `.json` file.

For example:

```text
BAY1-dashboard.json
```

Confirm the import.

Repeat for:

```text
BAY2-dashboard.json
BAY3-dashboard.json
Master-dashboard.json
```

> The exact menu wording can vary between ThingsBoard versions.

---

# 🔗 Step 3 — Configure Entity Aliases

After importing a dashboard, verify that its entity/device alias points to the correct ThingsBoard device.

For example:

```text
BAY 1 Dashboard
        ↓
BAY 1 ESP32 Device
```

```text
BAY 2 Dashboard
        ↓
BAY 2 ESP32 Device
```

```text
BAY 3 Dashboard
        ↓
BAY 3 ESP32 Device
```

If a dashboard is imported successfully but widgets show no data, **check Entity Aliases first**.

---

# 📡 Step 4 — Verify Telemetry

Make sure the corresponding ESP32 is connected and publishing telemetry.

Typical project telemetry includes:

```text
voltage
current
power
energyWh
temperature
bayStatus
throttleLevel
loadDecision
```

Use the **actual telemetry keys implemented by the firmware**.

If a widget is empty, compare its configured key with the telemetry keys visible in the ThingsBoard device.

---

# 🎛️ Step 5 — Verify RPC Controls

The BAY dashboards may use RPC controls such as:

### Relay

Method:

```text
setRelayState
```

ON:

```json
{"state": true}
```

OFF:

```json
{"state": false}
```

### Throttle

Method:

```text
setThrottle
```

Example:

```json
{"level": 60}
```

### Status

Method:

```text
getStatus
```

### AUTO

Use the exact AUTO RPC method configured in the final firmware/dashboard.

---

# 🚨 Step 6 — Verify Alarms

An alarm widget only displays alarms that actually exist in ThingsBoard.

If the alarm table is empty:

1. Confirm the device is connected.
2. Confirm telemetry is arriving.
3. Confirm the alarm rule/rule chain is configured.
4. Trigger a test condition.
5. Check the ThingsBoard alarm section.
6. Verify the dashboard alarm widget's entity scope.

---

# 🏭 Master Dashboard Data

The Master dashboard combines information from all three bays.

Conceptually:

```text
              ┌── BAY 1 ──┐
              │           │
              ├── BAY 2 ──┼──→ MASTER DASHBOARD
              │           │
              └── BAY 3 ──┘
```

### Total Station Power

```text
Total Station Power =
BAY 1 Power +
BAY 2 Power +
BAY 3 Power
```

Station limit:

```text
6000 W
```

---

# 🛠️ Troubleshooting

## Dashboard imported but widgets are empty

Check:

```text
Dashboard
   ↓
Entity Alias
   ↓
Correct Device
   ↓
Telemetry Key
```

## Wrong BAY data is displayed

For example, if the BAY 1 dashboard shows BAY 2 data:

1. Open the dashboard.
2. Check its Entity Alias.
3. Select the BAY 1 device.
4. Save the dashboard.


## Alarm table is empty

Check:

- Alarm rules
- Alarm originator
- Device/entity scope
- Alarm status
- Dashboard alarm widget configuration

## RPC button does nothing

Verify:

```text
ESP32 connected
      ↓
MQTT connected
      ↓
RPC method name
      ↓
RPC payload
      ↓
ESP32 RPC handler
```

---

# 🔐 Security

Never publish:

- ThingsBoard device access tokens
- Wi-Fi passwords
- MQTT credentials
- API keys
- Private certificates

Dashboard JSON files should not contain real credentials.

---

# ✅ Final Import Checklist

- [ ] BAY 1 dashboard imported
- [ ] BAY 2 dashboard imported
- [ ] BAY 3 dashboard imported
- [ ] Master dashboard imported
- [ ] BAY 1 entity alias verified
- [ ] BAY 2 entity alias verified
- [ ] BAY 3 entity alias verified
- [ ] Telemetry is updating
- [ ] Historical charts work
- [ ] RPC controls work
- [ ] Alarms are visible
- [ ] Master total power is correct
- [ ] 6000 W station limit is configured
- [ ] Master dashboard receives data from all three bays

---

<p align="center">
  ⚡ <b>ThingsBoard Cloud • 3-Bay EV Charging Station</b> ⚡
</p>
