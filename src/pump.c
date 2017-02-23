#include "pump.h"
#include <stdio.h>
#include "wiringPi.h"
#include "conf.h"

int init_pump(void)
{
#ifndef DEBUG
    if (wiringPiSetup() == -1) {
        printf("[ERROR][WIRINGPI] An error occured during Wiring Pi setup\n");
        return 1;
    }
    pinMode(PUMP_PIN, OUTPUT);
    return 0;
#endif
}

void start_pump(void)
{
#ifndef DEBUG
    printf("[INFO] Start Pump\n");
    digitalWrite(PUMP_PIN, 1);
#endif
}

void stop_pump(void)
{
#ifndef DEBUG
    printf("[INFO] Stop Pump\n");
    digitalWrite(PUMP_PIN, 0);
#endif
}
