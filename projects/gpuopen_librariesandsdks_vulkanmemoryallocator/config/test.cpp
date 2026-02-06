#include <cstdio>

// Compile VMA implementation into this TU so we can link without separate library
#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

int main() {
    VmaVirtualBlockCreateInfo blockInfo{};
    blockInfo.size = 1024 * 1024; // 1 MB

    VmaVirtualBlock block = VK_NULL_HANDLE;
    VkResult res = vmaCreateVirtualBlock(&blockInfo, &block);
    if (res != VK_SUCCESS || block == VK_NULL_HANDLE) {
        std::printf("Failed to create virtual block\n");
        return 1;
    }

    VmaVirtualAllocationCreateInfo allocInfo{};
    allocInfo.size = 4096; // 4 KB

    VmaVirtualAllocation allocation = VK_NULL_HANDLE;
    VkDeviceSize offset = 0;
    res = vmaVirtualAllocate(block, &allocInfo, &allocation, &offset);
    if (res != VK_SUCCESS) {
        std::printf("Allocation failed\n");
        vmaDestroyVirtualBlock(block);
        return 1;
    }

    VmaVirtualAllocationInfo outInfo{};
    vmaGetVirtualAllocationInfo(block, allocation, &outInfo);
    std::printf("Allocated size: %llu at offset: %llu\n", (unsigned long long)outInfo.size, (unsigned long long)outInfo.offset);

    vmaVirtualFree(block, allocation);
    vmaDestroyVirtualBlock(block);
    std::printf("Done.\n");
    return 0;
}
