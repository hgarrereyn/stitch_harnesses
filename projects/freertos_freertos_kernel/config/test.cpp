#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

// Provide required hook when stack overflow checking is enabled in config
extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    (void)xTask; (void)pcTaskName;
    // For test, just print and return
    printf("Stack overflow hook called for task: %s\n", pcTaskName ? pcTaskName : "<null>");
}

int main() {
    // Create a queue of 5 ints
    QueueHandle_t q = xQueueCreate(5, sizeof(int));
    if (q == NULL) {
        printf("Queue creation failed\n");
        return 1;
    }

    int v = 42;
    if (xQueueSend(q, &v, 0) != pdPASS) {
        printf("Send failed\n");
        return 1;
    }

    int r = 0;
    if (xQueueReceive(q, &r, 0) != pdPASS) {
        printf("Receive failed\n");
        return 1;
    }

    printf("Received: %d\n", r);
    vQueueDelete(q);
    return 0;
}
