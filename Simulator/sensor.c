
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "sensor.h"

// Generates random variation in sensor readings.
static double random_noise(double magnitude) {
    return (((double)rand() / RAND_MAX) * 2.0 - 1.0) * magnitude;
}

// Generates one set of aircraft telemetry.
Telemetry generate_telemetry(double elapsed_seconds) {

    Telemetry data;

    data.timestamp = (long long)time(NULL);

    data.altitude =
        25000 + 1000 * sin(elapsed_seconds / 20.0)
        + random_noise(20);

    data.airspeed =
        320 + 15 * sin(elapsed_seconds / 10.0)
        + random_noise(2);

    data.heading = fmod(180 + elapsed_seconds * 0.5, 360);

    data.engine_temp =
        650 + 10 * sin(elapsed_seconds / 15.0)
        + random_noise(3);

    data.fuel_level = 85 - elapsed_seconds * 0.002;

    data.vertical_speed =
        500 * cos(elapsed_seconds / 20.0)
        + random_noise(10);

    return data;
}
