
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "sensor.h"

int main(void) {

    srand((unsigned int)time(NULL));

    printf("Starting Flight Telemetry Simulator...\n");

    double elapsed_seconds = 0.0;

    while (1) {

        Telemetry data = generate_telemetry(elapsed_seconds);

        printf(
            "{\"timestamp\":%lld,"
            "\"altitude\":%.2f,"
            "\"airspeed\":%.2f,"
            "\"heading\":%.2f,"
            "\"engine_temp\":%.2f,"
            "\"fuel_level\":%.2f,"
            "\"vertical_speed\":%.2f}\n",

            data.timestamp,
            data.altitude,
            data.airspeed,
            data.heading,
            data.engine_temp,
            data.fuel_level,
            data.vertical_speed
        );

        fflush(stdout);

        Sleep(100); // every 100 ms between readings

        elapsed_seconds += 0.1;
    }

    return 0;
}
