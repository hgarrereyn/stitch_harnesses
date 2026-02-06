#include <stdio.h>
extern "C" {
#include "tjs.h"
}

int main() {
    TJSRunOptions opts;
    TJS_DefaultOptions(&opts);
    TJSRuntime *rt = TJS_NewRuntimeOptions(&opts);
    if (!rt) {
        printf("Failed to create runtime\n");
        return 1;
    }
    // Initialize the runtime (no args)
    TJS_Initialize(0, NULL);

    // Run the event loop once and then stop
    (void)TJS_Run(rt);
    TJS_Stop(rt);

    TJS_FreeRuntime(rt);
    printf("txiki.js runtime init/stop OK\n");
    return 0;
}
