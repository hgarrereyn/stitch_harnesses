#include <OpenImageDenoise/oidn.h>
#include <iostream>

int main() {
  // Simple API smoke test: create a device, query a few properties, create a buffer
  OIDNDevice device = oidnNewDevice(OIDN_DEVICE_TYPE_CPU);
  if (!device) {
    const char* msg = nullptr;
    oidnGetDeviceError(nullptr, &msg);
    std::cerr << "Failed to create device: " << (msg ? msg : "unknown") << std::endl;
    return 1;
  }

  // Disable thread affinity to avoid loading TBB bind plugin (sanitizer-incompatible)
  oidnSetDeviceBool(device, "setAffinity", false);
  oidnCommitDevice(device);

  int version = oidnGetDeviceInt(device, "version");
  int major = oidnGetDeviceInt(device, "versionMajor");
  int minor = oidnGetDeviceInt(device, "versionMinor");
  int patch = oidnGetDeviceInt(device, "versionPatch");
  std::cout << "OIDN version: " << major << "." << minor << "." << patch
            << " (" << version << ")" << std::endl;

  // Create a tiny buffer and access it
  const size_t byteSize = 16;
  OIDNBuffer buf = oidnNewBuffer(device, byteSize);
  if (!buf) {
    std::cerr << "Failed to allocate buffer" << std::endl;
    oidnReleaseDevice(device);
    return 1;
  }
  void* data = oidnGetBufferData(buf);
  if (data) {
    unsigned char* p = static_cast<unsigned char*>(data);
    for (size_t i = 0; i < byteSize; ++i) p[i] = static_cast<unsigned char>(i);
    std::cout << "Buffer[0]=" << (int)p[0] << std::endl;
  }

  oidnReleaseBuffer(buf);
  oidnReleaseDevice(device);
  return 0;
}
