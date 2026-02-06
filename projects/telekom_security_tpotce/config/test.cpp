#include <iostream>
#include <cstring>
extern "C" const char* p0f_shim_version();
#include <api.h>
#include <types.h>
int main() {
    p0f_api_query q{};
    q.magic = P0F_QUERY_MAGIC;
    q.addr_type = P0F_ADDR_IPV4;
    std::cout << "p0f_shim_version: " << p0f_shim_version() << "\n";
    std::cout << "Query magic: 0x" << std::hex << q.magic << std::dec << ", addr_type=" << (int)q.addr_type << "\n";
    return 0;
}
