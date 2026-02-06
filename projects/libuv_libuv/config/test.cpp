#include <uv.h>
#include <stdio.h>

static void timer_cb(uv_timer_t* handle) {
  printf("timer fired\n");
  uv_timer_stop(handle);
}

int main() {
  uv_loop_t loop;
  if (uv_loop_init(&loop) != 0) {
    fprintf(stderr, "failed to init loop\n");
    return 1;
  }

  uv_timer_t timer;
  if (uv_timer_init(&loop, &timer) != 0) {
    fprintf(stderr, "failed to init timer\n");
    uv_loop_close(&loop);
    return 1;
  }
  if (uv_timer_start(&timer, timer_cb, 1, 0) != 0) {
    fprintf(stderr, "failed to start timer\n");
    uv_loop_close(&loop);
    return 1;
  }

  uv_run(&loop, UV_RUN_DEFAULT);

  uv_close((uv_handle_t*)&timer, NULL);
  uv_run(&loop, UV_RUN_DEFAULT); // drain close callbacks
  uv_loop_close(&loop);
  return 0;
}
