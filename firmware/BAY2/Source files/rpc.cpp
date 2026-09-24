#include <ArduinoJson.h>
#include "rpc.h"
#include "network.h"
#include "state.h"
#include "config.h"

void handleRpc(String requestId, char *payload)
{
    StaticJsonDocument<300> doc;

    if (deserializeJson(doc, payload))
        return;

    String method = doc["method"] | "";
    JsonObject params = doc["params"];

    StaticJsonDocument<400> response;

    if (method == "setRelayState")
    {
        bool state = params["state"] | false;

        manualOverrideActive = true;
        manualRelayControlActive = true;
        manualRelayState = state;

        throttleLevel = state ? 100 : 0;
        loadDecision = state ? "MANUAL_ON" : "MANUAL_OFF";

        response["success"] = true;
        response["throttleLevel"] = throttleLevel;

        Serial.print(">> RPC setRelayState(");
        Serial.print(state);
        Serial.println(") - manual relay override engaged.");
    }

    else if (method == "setThrottle")
    {
        int level = params["level"] | 100;
        level = constrain(level, 0, 100);

        manualOverrideActive = true;
        manualRelayControlActive = false;
        throttleLevel = level;

        loadDecision = "MANUAL_THROTTLE";

        response["success"] = true;
        response["throttleLevel"] = throttleLevel;

        Serial.print(">> RPC setThrottle(");
        Serial.print(level);
        Serial.println(") - manual override engaged.");
    }

    else if (method == "getStatus")
    {
        response["success"] = true;
        response["bayStatus"] = bayStatus;
        response["voltage"] = voltage;
        response["current"] = current;
        response["power"] = power;
        response["energyWh"] = energyWh;
        response["temperature"] = temperature;
        response["throttleLevel"] = throttleLevel;
        response["loadDecision"] = loadDecision;

        Serial.println(">> RPC getStatus() - status sent.");
    }
    else if (method == "setAutoMode")
    {
        manualOverrideActive = false;
        manualRelayControlActive = false;
        manualRelayState = false;

        loadDecision = "AUTO";

        response["success"] = true;
        response["mode"] = "AUTO";

        Serial.println(
            ">> RPC setAutoMode() - automatic optimization restored.");
    }

    else
    {
        response["success"] = false;
        response["error"] = "unknown method";
    }

    char buffer[450];

    serializeJson(response, buffer);

    mqtt.publish(
        ("v1/devices/me/rpc/response/" + requestId).c_str(),
        buffer);
}