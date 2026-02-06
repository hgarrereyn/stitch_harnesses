#include <stdio.h>
#include <obs-websocket-api.h>

int main() {
    // Call a function that does not require an initialized OBS context.
    // This ensures we can link and run without starting OBS.
    obs_websocket_request_response_free(NULL);
    printf("obs-websocket API header is usable.\n");
    return 0;
}
