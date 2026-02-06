#include <iostream>
#include "quiche/common/simple_buffer_allocator.h"
#include "quiche/common/quiche_buffer_allocator.h"

int main() {
    quiche::SimpleBufferAllocator* alloc = quiche::SimpleBufferAllocator::Get();
    const char* msg = "hello quiche";
    size_t len = 12;
    char* buf = alloc->New(len);
    for (size_t i = 0; i < len; ++i) buf[i] = msg[i];
    std::cout << std::string(buf, len) << "\n";
    alloc->Delete(buf);
    return 0;
}
