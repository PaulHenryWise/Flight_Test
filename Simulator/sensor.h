#ifndef SENSOR_H
#define SENSOR_H

typedef struct {
    long long timestamp;
    double altitude;
    double airspeed; // speed in knots
    double heading; // Direction the aircraft is traveling
    double engine_temp;
    double fuel_level;
    double vertical_speed; // Rate of climbing or descending
} Telemetry;

Telemetry generate_telemetry(double elapsed_seconds);

#endif