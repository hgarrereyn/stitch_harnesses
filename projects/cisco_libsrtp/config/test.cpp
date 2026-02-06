#include <cstdio>
#include <cstring>
#include <cstdint>

extern "C" {
#include <srtp.h>
}

int main() {
    if (srtp_init() != srtp_err_status_ok) {
        printf("srtp_init failed\n");
        return 1;
    }

    srtp_policy_t policy;
    std::memset(&policy, 0, sizeof(policy));

    policy.ssrc.type = ssrc_any_outbound;

    srtp_crypto_policy_set_rtp_default(&policy.rtp);
    srtp_crypto_policy_set_rtcp_default(&policy.rtcp);

    uint8_t key[SRTP_MASTER_KEY_LEN] = {0};
    for (size_t i = 0; i < sizeof(key); ++i) key[i] = static_cast<uint8_t>(i);
    policy.key = key;

    srtp_t session = nullptr;
    if (srtp_create(&session, &policy) != srtp_err_status_ok) {
        printf("srtp_create failed\n");
        srtp_shutdown();
        return 1;
    }

    // Construct a tiny fake RTP packet (12-byte header + payload)
    uint8_t rtp[64] = {0};
    size_t rtp_len = 20; // small payload
    rtp[0] = 0x80; // V=2
    rtp[1] = 96;   // PT=96
    rtp[2] = 0x00; rtp[3] = 0x01; // sequence number

    uint8_t srtp_buf[128] = {0};
    size_t srtp_len = sizeof(srtp_buf);

    srtp_err_status_t st = srtp_protect(session, rtp, rtp_len, srtp_buf, &srtp_len, 0);
    if (st != srtp_err_status_ok) {
        printf("srtp_protect failed: %d\n", (int)st);
        srtp_dealloc(session);
        srtp_shutdown();
        return 1;
    }

    printf("libsrtp protect OK (srtp_len=%zu)\n", srtp_len);

    srtp_dealloc(session);
    srtp_shutdown();
    return 0;
}
