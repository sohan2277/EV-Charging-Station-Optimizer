#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <DHT.h>

extern DHT dht;

float mapFloat(long, long, long, float, float);
void sample_sensor(void);
void plug_status(void);
//void update_led_status(void);
float recentAvgCurrent();

#endif