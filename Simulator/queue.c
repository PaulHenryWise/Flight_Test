
#include "queue.h"

void queue_init(TelemetryQueue *queue) {

    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;

    InitializeCriticalSection(&queue->lock);

    InitializeConditionVariable(&queue->not_empty);
    InitializeConditionVariable(&queue->not_full);
}

void queue_push(TelemetryQueue *queue, Telemetry data) {

    EnterCriticalSection(&queue->lock); // protect the queue data

    // Wait while the queue is full.
    while (queue->count == QUEUE_CAPACITY) {
        SleepConditionVariableCS(
            &queue->not_full,
            &queue->lock,
            INFINITE
        );
    }

    // Insert telemetry into the queue.
    queue->items[queue->rear] = data;

    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;

    queue->count++;

    // Notify waiting consumer threads.
    WakeConditionVariable(&queue->not_empty);

    LeaveCriticalSection(&queue->lock);
}

Telemetry queue_pop(TelemetryQueue *queue) {

    EnterCriticalSection(&queue->lock);

    // Wait while the queue is empty.
    while (queue->count == 0) {
        SleepConditionVariableCS(
            &queue->not_empty,
            &queue->lock,
            INFINITE
        );
    }

    // Retrieve telemetry from the queue.
    Telemetry data = queue->items[queue->front];

    queue->front = (queue->front + 1) % QUEUE_CAPACITY;

    queue->count--;

    // Notify waiting producer threads.
    WakeConditionVariable(&queue->not_full);

    LeaveCriticalSection(&queue->lock);

    return data;
}

void queue_destroy(TelemetryQueue *queue) {
    DeleteCriticalSection(&queue->lock);
}
