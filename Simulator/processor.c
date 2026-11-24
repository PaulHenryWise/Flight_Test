
#include <stdio.h>
#include "processor.h"

// Simulations limits not real limits in an actual aircraft
int validate_telemetry(Telemetry data) {

    if (data.altitude < 0 || data.altitude > 60000) {
        return 0;
    }

    if (data.airspeed < 0 || data.airspeed > 600) {
        return 0;
    }

    if (data.heading < 0 || data.heading >= 360) {
        return 0;
    }

    if (data.engine_temp < 0 || data.engine_temp > 1200) {
        return 0;
    }

    if (data.fuel_level < 0 || data.fuel_level > 100) {
        return 0;
    }

    if (data.vertical_speed < -10000 ||
        data.vertical_speed > 10000) {
        return 0;
    }

    return 1;
}

void detect_anomalies(Telemetry data) {

    if (data.engine_temp > 750) {
        printf("[WARNING] High engine temperature: %.2f C\n",
               data.engine_temp);
    }

    if (data.airspeed > 400) {
        printf("[WARNING] High airspeed: %.2f knots\n",
               data.airspeed);
    }

    if (data.fuel_level < 20) {
        printf("[WARNING] Low fuel: %.2f%%\n",
               data.fuel_level);
    }

    if (data.vertical_speed > 3000 ||
        data.vertical_speed < -3000) {
        printf("[WARNING] Unusual vertical speed: %.2f ft/min\n",
               data.vertical_speed);
    }
}
