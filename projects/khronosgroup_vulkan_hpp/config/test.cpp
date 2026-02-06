#include <vulkan/vulkan.hpp>
#include <iostream>

int main() {
  uint32_t api = vk::makeApiVersion(1, 3, 0, 0);
  auto major = VK_API_VERSION_MAJOR(api);
  auto minor = VK_API_VERSION_MINOR(api);

  vk::Format fmt = vk::Format::eR8G8B8A8Unorm;
  std::cout << "Vulkan API version: " << major << "." << minor << "\n";
  std::cout << "Sample format: " << vk::to_string(fmt) << "\n";

  vk::ApplicationInfo appInfo("TestApp", 1, "NoEngine", 1, api);
  (void)appInfo;
  return 0;
}
