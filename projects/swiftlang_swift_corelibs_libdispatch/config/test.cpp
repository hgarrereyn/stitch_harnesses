#include <dispatch/dispatch.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    dispatch_queue_t q = dispatch_queue_create("com.example.test", DISPATCH_QUEUE_SERIAL);
    if (!q) {
        fprintf(stderr, "failed to create queue\n");
        return 1;
    }

    __block int value = 0;
    dispatch_semaphore_t sema = dispatch_semaphore_create(0);
    if (!sema) {
        fprintf(stderr, "failed to create semaphore\n");
        return 1;
    }

    dispatch_async(q, ^{
        value = 42;
        dispatch_semaphore_signal(sema);
    });

    // Wait for the async block to complete
    dispatch_semaphore_wait(sema, DISPATCH_TIME_FOREVER);

    // Basic sanity check
    printf("value=%d\n", value);

    // Clean up (only needed for non-Objective-C platforms)
#if !OS_OBJECT_HAVE_OBJC_SUPPORT
    dispatch_release(sema);
    dispatch_release(q);
#endif

    return value == 42 ? 0 : 2;
}
