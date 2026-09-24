#include <Arduino.h>
#include "optimization.h"
#include "config.h"
#include "state.h"

// ---------------------------------------------------------------------
// SRS 8.7 optimization - skipped entirely while manualOverrideActive
// (an RPC call is in effect).
// ---------------------------------------------------------------------
void runOptimization()
{
  float totalStationPower = power;

  // Default: no overload
  overloadActive = false;

  // --------------------------------------------------
  // BAY NOT CHARGING
  // --------------------------------------------------
  if (bayStatus != "CHARGING")
  {
    bool peakHour =
        (lastHourOfDay >= peakTariffStartHr &&
         lastHourOfDay <= peakTariffEndHr);

    if (peakHour && predictedArrivalProb >= predictionThreshold)
    {
      loadDecision = "STANDBY_EXPECTING";
    }
    else if (peakHour)
    {
      loadDecision = "LOW_DEMAND";
    }
    else
    {
      loadDecision = "ALLOW";
    }

    return;
  }

  // --------------------------------------------------
  // SAFETY: OVERCURRENT
  // --------------------------------------------------
  if (current > overloadCurrentA)
  {
    loadDecision = "THROTTLE";
    throttleLevel = 50;
    overloadActive = true;

    Serial.print("!! OVERCURRENT: ");
    Serial.print(current);
    Serial.print(" A > ");
    Serial.print(overloadCurrentA);
    Serial.println(" A");

    return;
  }

  // --------------------------------------------------
  // STATION POWER LIMIT
  // --------------------------------------------------
  if (totalStationPower > maxStationLoadW)
  {
    if (predictedDurationMin > 10)
    {
      loadDecision = "THROTTLE";
      throttleLevel = 70;

      Serial.println(
          "!! Station power cap exceeded -> THROTTLE @ 70%.");
    }
    else
    {
      loadDecision = "ALLOW";
      throttleLevel = 100;
    }

    return;
  }

  // --------------------------------------------------
  // NORMAL OPERATION
  // --------------------------------------------------
  loadDecision = "ALLOW";
  throttleLevel = 100;
}
// ---------------------------------------------------------------------
// FR-6: apply throttleLevel to the relay via duty-cycling.
// ---------------------------------------------------------------------
// optimization.cpp
void applyRelayDutyCycle()
{
  // --------------------------------------------------
  // BAY NOT CHARGING
  // --------------------------------------------------
  if (bayStatus != "CHARGING")
  {
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  // --------------------------------------------------
  // SAFETY: OVERCURRENT HAS HIGHEST PRIORITY
  // --------------------------------------------------
  if (overloadActive)
  {
    // Safety throttling
    throttleLevel = 50;

    unsigned long phase =
        millis() % DUTY_CYCLE_WINDOW_MS;

    unsigned long onTime =
        (DUTY_CYCLE_WINDOW_MS * throttleLevel) / 100;

    digitalWrite(
        RELAY_PIN,
        phase < onTime ? HIGH : LOW);

    return;
  }

  // --------------------------------------------------
  // MANUAL RELAY OVERRIDE
  // --------------------------------------------------
  if (manualOverrideActive && manualRelayControlActive)
  {
    digitalWrite(
        RELAY_PIN,
        manualRelayState ? HIGH : LOW);

    return;
  }

  // --------------------------------------------------
  // MANUAL THROTTLE
  // --------------------------------------------------
  if (manualOverrideActive && !manualRelayControlActive)
  {
    if (throttleLevel >= 100)
    {
      digitalWrite(RELAY_PIN, HIGH);
      return;
    }

    if (throttleLevel <= 0)
    {
      digitalWrite(RELAY_PIN, LOW);
      return;
    }

    unsigned long phase =
        millis() % DUTY_CYCLE_WINDOW_MS;

    unsigned long onTime =
        (DUTY_CYCLE_WINDOW_MS * throttleLevel) / 100;

    digitalWrite(
        RELAY_PIN,
        phase < onTime ? HIGH : LOW);

    return;
  }

  // --------------------------------------------------
  // AUTOMATIC MODE
  // --------------------------------------------------
  if (throttleLevel >= 100)
  {
    digitalWrite(RELAY_PIN, HIGH);
    return;
  }

  if (throttleLevel <= 0)
  {
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  unsigned long phase =
      millis() % DUTY_CYCLE_WINDOW_MS;

  unsigned long onTime =
      (DUTY_CYCLE_WINDOW_MS * throttleLevel) / 100;

  digitalWrite(
      RELAY_PIN,
      phase < onTime ? HIGH : LOW);
}
void updateLeds()
{
  digitalWrite(
      LED_RED,
      overloadActive ? HIGH : LOW);

  digitalWrite(
      LED_GREEN,
      (bayStatus == "FREE" && !overloadActive)
          ? HIGH
          : LOW);

  digitalWrite(
      LED_YELLOW,
      (bayStatus == "CHARGING" && !overloadActive)
          ? HIGH
          : LOW);
}
