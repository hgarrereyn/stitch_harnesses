#include <vulkan/vulkan.h>
#include <cstdio>

int main() {
    uint32_t apiVersion = 0;
    VkResult res = vkEnumerateInstanceVersion(&apiVersion);
    if (res != VK_SUCCESS) {
        std::printf("vkEnumerateInstanceVersion failed: %d\n", res);
    } else {
        std::printf("Vulkan API version: %u.%u.%u\n", VK_VERSION_MAJOR(apiVersion), VK_VERSION_MINOR(apiVersion), VK_VERSION_PATCH(apiVersion));
    }

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "test";
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    VkInstance instance = VK_NULL_HANDLE;
    res = vkCreateInstance(&createInfo, nullptr, &instance);
    std::printf("vkCreateInstance returned: %d\n", res);
    if (res == VK_SUCCESS && instance != VK_NULL_HANDLE) {
        vkDestroyInstance(instance, nullptr);
        std::printf("Destroyed instance.\n");
    }
    return 0;
}
