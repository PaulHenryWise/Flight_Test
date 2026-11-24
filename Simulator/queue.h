
#ifndef QUEUE_H
#define QUEUE_H

#include "sensor.h"
#include <windows.h>

#define QUEUE_CAPACITY 100

typedef struct {
    Telemetry items[QUEUE_CAPACITY];

    int front;
    int rear;
    int count;

    CRITICAL_SECTION lock;
    CONDITION_VARIABLE not_empty;
    CONDITION_VARIABLE not_full;

} TelemetryQueue;

void queue_init(TelemetryQueue *queue);

void queue_push(TelemetryQueue *queue, Telemetry data);

Telemetry queue_pop(TelemetryQueue *queue);

void queue_destroy(TelemetryQueue *queue);

#endif
