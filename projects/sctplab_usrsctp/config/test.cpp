#include <cstdio>
#include <cstdint>
#include "usrsctplib/usrsctp.h"

static int dummy_output(void* addr, void* buffer, size_t length, uint8_t tos, uint8_t set_df) {
    (void)addr; (void)buffer; (void)length; (void)tos; (void)set_df;
    // Drop all outgoing packets in this simple test.
    return 0; // success
}

static void dummy_logger(const char* fmt, ...) {
    (void)fmt;
}

int main() {
    // Initialize the usrsctp stack with no UDP encapsulation and dummy callbacks.
    usrsctp_init(0, dummy_output, dummy_logger);

    // Exercise a simple API: get and print a tunable value.
    uint32_t sendspace = usrsctp_sysctl_get_sctp_sendspace();
    uint32_t recvspace = usrsctp_sysctl_get_sctp_recvspace();
    std::printf("usrsctp sendspace=%u recvspace=%u\n", sendspace, recvspace);

    // Finish and cleanup.
    usrsctp_finish();
    return 0;
}
