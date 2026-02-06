#include <pw_status/status.h>
#include <pw_status/status_with_size.h>
#include <cstdio>

int main() {
  // Simple sanity checks using the pw_status API
  pw::Status ok = pw::OkStatus();
  pw::Status not_found = pw::Status::NotFound();

  if (!ok.ok()) {
    return 1;
  }
  if (not_found.ok()) {
    return 2;
  }

  // Use StatusWithSize utility
  pw::StatusWithSize s(5);
  if (!s.ok() || s.size() != 5u) {
    return 3;
  }

  // Exercise basic status retrieval
  if (!s.status().ok()) {
    return 4;
  }

  std::printf("pw_status test passed: size=%zu\n", static_cast<size_t>(s.size()));
  return 0;
}
