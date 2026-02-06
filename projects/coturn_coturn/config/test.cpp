#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <turn/client/ns_turn_msg.h>
#include <turn/client/ns_turn_msg_defs.h>

int main() {
    uint8_t buf[1024];
    size_t len = 0;
    // Initialize a STUN binding request
    stun_init_buffer_str(buf, &len);
    stun_init_request_str(STUN_METHOD_BINDING, buf, &len);

    bool is_req = stun_is_request_str(buf, len);
    uint16_t method = stun_get_method_str(buf, len);

    std::printf("is_request=%d method=0x%04x\n", (int)is_req, (unsigned)method);
    return (is_req && method == STUN_METHOD_BINDING) ? 0 : 1;
}
