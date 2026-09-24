#include <ArduinoJson.h>
#include "telemetry.h"
#include "network.h"
#include "state.h"
#include "config.h"

void publishTelemetry()
{
  if (!mqtt.connected())
    return;

  // send values in key value pair
  JsonDocument doc;
  doc["bayId"] = BAY_ID;
  doc["voltage"] = round(voltage * 10) / 10.0;
  doc["current"] = round(current * 10) / 10.0;
  doc["power"] = round(power * 10) / 10.0;
  doc["temperature"] = round(temperature * 10) / 10.0;
  doc["bayStatus"] = bayStatus;
  doc["predictedArrivalProb"] = round(predictedArrivalProb * 100) / 100.0;
  doc["predictedDurationMin"] = predictedDurationMin;
  doc["throttleLevel"] = throttleLevel;
  doc["loadDecision"] = loadDecision;
  doc["overloadActive"] = overloadActive;

  char buffer[350];
  serializeJson(doc, buffer, sizeof(buffer));
  
  //pust the data to the cloud
  mqtt.publish("v1/devices/me/telemetry", buffer);
  Serial.print("[MQTT >>] ");
  Serial.println(buffer);
}
