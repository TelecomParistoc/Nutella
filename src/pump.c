#include "pump.h"
#include <stdio.h>
#ifndef DEBUG
#include <wiringPi.h>
#endif
#include "conf.h"

int init_pump(void)
{
#ifndef DEBUG
    if(wiringPiSetup() == -1) {
        printf("[ERROR][WIRINGPI] An error occured during Wiring Pi setup\n");
        return 1;
    }
    pinMode(PUMP_PIN, OUTPUT);
#endif
    return 0;
}

void start_pump(void)
{
    printf("[INFO] Start Pump\n");
#ifndef DEBUG
    digitalWrite(PUMP_PIN, 1);
#endif
}

void stop_pump(void)
{
    printf("[INFO] Stop Pump\n");
#ifndef DEBUG
    digitalWrite(PUMP_PIN, 0);
#endif
}
