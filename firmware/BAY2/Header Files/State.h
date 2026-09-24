#ifndef STATE_H
#define STATE_H

#include <Arduino.h>
// ---------------------------------------------------------------------
// Live bay state
// ---------------------------------------------------------------------
extern String bayStatus;
extern float voltage, current, power, energyWh, temperature,raw_voltage, raw_current, t;
extern unsigned long sessionStartMs;

extern float predictedArrivalProb;
extern int predictedDurationMin;
extern int lastHourOfDay;

extern String loadDecision;
extern int throttleLevel;
extern float predictionThreshold;
extern int peakTariffStartHr;
extern int peakTariffEndHr;
extern bool overloadActive;
extern float overloadCurrentA;
extern float maxStationLoadW;
extern unsigned long  DUTY_CYCLE_WINDOW_MS;

extern bool manualOverrideActive;
extern bool manualRelayControlActive;
extern bool manualRelayState;

#endif