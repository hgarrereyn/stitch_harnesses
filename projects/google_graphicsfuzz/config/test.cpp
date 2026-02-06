#include <iostream>
#include <vkcheck.h>
#include <vulkan_worker.h>

int main() {
  // Simple runtime smoke test that does not require a Vulkan ICD.
  const char* s = getVkResultString(VK_SUCCESS);
  std::cout << "vk result string: " << s << std::endl;
  return 0;
}
