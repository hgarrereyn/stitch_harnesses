#include <iostream>
#include "mediapipe/framework/port.h"
#include "mediapipe/framework/camera_intrinsics.h"
#include "mediapipe/framework/demangle.h"

int main() {
  // Use a simple header-only class from MediaPipe
  CameraIntrinsics cam(500.0f, 500.0f, 320.0f, 240.0f, 640.0f, 480.0f);
  std::cout << "fx=" << cam.fx() << ", fy=" << cam.fy() << "\n";
  std::cout << "cx=" << cam.cx() << ", cy=" << cam.cy() << "\n";
  std::cout << "width=" << cam.width() << ", height=" << cam.height() << "\n";

  // Demonstrate usage of Demangle utility
  std::string demangled = mediapipe::Demangle(typeid(cam).name());
  std::cout << "Type: " << demangled << "\n";

  // Read a compile-time macro from port.h
#if defined(MEDIAPIPE_OPENGL_ES_VERSION)
  std::cout << "GLES version macro: " << MEDIAPIPE_OPENGL_ES_VERSION << "\n";
#else
  std::cout << "GLES version macro not defined" << "\n";
#endif

  return 0;
}
