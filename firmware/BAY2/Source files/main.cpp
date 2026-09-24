#include <Arduino.h>
#include "State.h"
#include "config.h"
#include "Peripherals.h"
#include "network.h"
#include "telemetry.h"
#include "model.h"
#include "edge_ai.h"
#include "optimization.h"

void setup()
{

    Serial.begin(115200); // initialise serial monitor
    dht.begin();          // initialise sesnor

    // config esp32 with real time
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    // Config Pins
    pinMode(BTN_PLUGIN, INPUT_PULLUP);
    pinMode(BTN_PLUGOUT, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_YELLOW, OUTPUT);
    pinMode(LED_RED, OUTPUT);

    // Connect to Wifi
    connectWiFi();

    // configure MQTT server
    mqtt.setServer(MQTT_SERVER, MQTT_PORT);
    mqtt.setCallback(mqttCallback);
    mqtt.setBufferSize(512);

    // Connect MQTT
    connectMQTT();
}

unsigned long now;
unsigned long last_print;
static bool lastMqttState = false;

// main.cpp - replace loop()
void loop()
{
    mqtt.loop();

    // Detect plug-in / plug-out
    plug_status();

    now = millis();

    if ((now - last_print) > 5000)
    {
        last_print = now;

        // Read sensors
        sample_sensor();

        // Run AI prediction
        runEdgeAIInference();

        // --------------------------------------------------
        // SAFETY CHECK - ALWAYS RUN
        // --------------------------------------------------
        if (bayStatus == "CHARGING" &&
            current > overloadCurrentA)
        {
            overloadActive = true;
            loadDecision = "THROTTLE";
            throttleLevel = 50;

            Serial.print("!! OVERCURRENT: ");
            Serial.print(current);
            Serial.print(" A > ");
            Serial.print(overloadCurrentA);
            Serial.println(" A");
        }
        else
        {
            overloadActive = false;

            // --------------------------------------------------
            // AUTOMATIC OPTIMIZATION
            // --------------------------------------------------
            if (!manualOverrideActive)
            {
                runOptimization();
            }
        }

        publishTelemetry();
    }

    // Relay control runs continuously
    applyRelayDutyCycle();

    // LEDs run continuously
    updateLeds();
}
