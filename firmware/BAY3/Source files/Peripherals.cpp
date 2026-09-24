#include <Arduino.h>
#include <DHT.h>
#include "State.h"
#include "Peripherals.h"
#include "config.h"

DHT dht(DHT_PIN, DHT_TYPE);

float mapFloat(long x, long inMin, long inMax, float outMin, float outMax)
{
   return (x - inMin) * (outMax - outMin) / (float)(inMax - inMin) + outMin;
}
void sample_sensor(void)
{
   raw_current = analogRead(CURRENT_PIN); // 0 to 4095 //0 to 32A
   raw_voltage = analogRead(VOLTAGE_PIN); // 0 to 4095 //0 to 250V

   voltage = mapFloat(raw_voltage, 0, 4095, 0, 250); // convert raw voltage to 0 - 250 V
   if (bayStatus == "CHARGING")
   {
      current = mapFloat(raw_current, 0, 4095, 0, 32); // convert raw current to 0 - 32 A
   }
   else
   {
      current = 0.0;
   }

   //read current and 5 values array

   // calculate Power
   power = voltage * current;

   // temprature
   t = dht.readTemperature();
   if (!isnan(t))
   {
      temperature = t;
   }
}

float recentAvgCurrent()
{
   float sum = 0;
   for(int i = 0; i < 5; i++)
   {
      sum += current;
   }
   return sum / 5.0;
}





bool plugin_flag = 1;
bool plugout_flag = 1;

void plug_status(void)
{
   bool pluginReading = digitalRead(BTN_PLUGIN);
   // detect the sw is pressed
   if (pluginReading == LOW && plugin_flag == 1)
   {
      //session time
      sessionStartMs = millis();
      plugin_flag = 0;
      if (bayStatus == "FREE")
      {
         bayStatus = "CHARGING";
         Serial.println("Bay 1 Plugin detected and Bay is Charging");
      } // update leds
   }
   if (pluginReading == HIGH)
   {
      plugin_flag = 1;
   }
   // plug out switch is pressed
   bool plugoutReading = digitalRead(BTN_PLUGOUT); // return LOW when button is pressed
   // detect the sw is pressed
   if (plugoutReading == LOW && plugout_flag == 1)
   {
      plugout_flag = 0;
      if (bayStatus == "CHARGING")
      {
         bayStatus = "FREE";
         Serial.println("Bay 1 Plugout detected and Bay is FREE");
         //digitalWrite(RELAY_PIN, LOW);
      } // update leds
   }
   if (plugoutReading == HIGH)
   {
      plugout_flag = 1;
   }
}

/*void update_led_status(void)
{
   if (bayStatus == "FREE")
   {
      digitalWrite(LED_GREEN, HIGH);
      digitalWrite(LED_YELLOW, LOW);
   }
   else
   {
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_YELLOW, HIGH);
   }
}*/