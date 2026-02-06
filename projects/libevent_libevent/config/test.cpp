#include <event2/event.h>
#include <event2/util.h>
#include <event2/buffer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void on_timeout(evutil_socket_t, short, void *arg) {
    struct event_base *base = (struct event_base*)arg;
    // Break the loop after timeout fires once
    event_base_loopbreak(base);
}

int main() {
    struct event_base *base = event_base_new();
    if (!base) {
        fprintf(stderr, "Failed to create event_base\n");
        return 1;
    }

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1000; // 1ms

    struct event *timeout_event = evtimer_new(base, on_timeout, base);
    if (!timeout_event) {
        fprintf(stderr, "Failed to create timer event\n");
        event_base_free(base);
        return 1;
    }
    evtimer_add(timeout_event, &tv);

    // Run loop; timer will break it almost immediately
    event_base_dispatch(base);

    event_free(timeout_event);
    event_base_free(base);

    // Basic evbuffer sanity check
    struct evbuffer *buf = evbuffer_new();
    if (!buf) return 1;
    evbuffer_add_printf(buf, "hello %s", "libevent");
    size_t len = evbuffer_get_length(buf);
    unsigned char tmp[64];
    int n = evbuffer_remove(buf, tmp, sizeof(tmp)-1);
    if (n < 0) { evbuffer_free(buf); return 1; }
    tmp[n] = '\0';
    printf("buffer[%zu]: %s\n", len, tmp);
    evbuffer_free(buf);

    return 0;
}
