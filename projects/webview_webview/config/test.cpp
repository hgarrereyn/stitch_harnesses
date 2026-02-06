#include <iostream>
#include "webview/webview.h"
#include "webview/version.h"

int main() {
  // Simple smoke test that references a couple of API tokens without creating a GUI.
  std::cout << "Webview version: "
            << WEBVIEW_VERSION_MAJOR << "." << WEBVIEW_VERSION_MINOR << "." << WEBVIEW_VERSION_PATCH
            << "\n";

  // Use a tiny piece of the C API type surface to ensure headers are consistent.
  webview_t w = nullptr; // just declare the type; do not create a window
  (void)w;

  return 0;
}
