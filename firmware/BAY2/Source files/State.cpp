#include "State.h"


String bayStatus = "FREE";
float voltage = 0.0, current = 0.0, power = 0.0, energyWh = 0.0, temperature = 0.0, raw_current = 0.0, raw_voltage = 0.0, t = 0.0;
unsigned long sessionStartMs = 0;

//Edge AI Variables
float predictedArrivalProb = 0.0;
int predictedDurationMin = 0;
int lastHourOfDay = 0;

String loadDecision = "ALLOW";
int throttleLevel = 100;
float predictionThreshold = 0.5; //
int peakTariffStartHr = 18; //
int peakTariffEndHr = 21; //
bool overloadActive = false;
float overloadCurrentA = 16.0; //
float maxStationLoadW = 6000.0; //
unsigned long DUTY_CYCLE_WINDOW_MS = 2000;

bool manualOverrideActive = false;
bool manualRelayControlActive = false;
bool manualRelayState = false;