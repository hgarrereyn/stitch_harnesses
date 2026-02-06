#include <cstdio>
#include <xnnpack.h>

int main() {
  enum xnn_status s = xnn_initialize(nullptr);
  if (s != xnn_status_success && s != xnn_status_unsupported_hardware) {
    std::printf("xnn_initialize failed: %d\n", (int)s);
    return 1;
  }
  // Create and delete an empty subgraph to exercise basic API surface.
  xnn_subgraph_t sg = nullptr;
  if (xnn_create_subgraph(0, 0, &sg) == xnn_status_success && sg != nullptr) {
    xnn_delete_subgraph(sg);
  }
  xnn_deinitialize();
  std::puts("XNNPACK basic init/deinit OK");
  return 0;
}
