#include <cstdio>
#include <cstring>
#include <htp/htp.h>

int main() {
    htp_cfg_t *cfg = htp_config_create();
    if (!cfg) {
        std::printf("Failed to create config\n");
        return 1;
    }

    // Optionally register multipart parser
    htp_config_register_multipart_parser(cfg);

    htp_connp_t *connp = htp_connp_create(cfg);
    if (!connp) {
        std::printf("Failed to create connection parser\n");
        htp_config_destroy(cfg);
        return 1;
    }

    htp_connp_open(connp, "127.0.0.1", 12345, "127.0.0.1", 80, nullptr);

    const char *req = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    int rc = htp_connp_req_data(connp, nullptr, req, std::strlen(req));
    std::printf("req rc=%d consumed=%zu\n", rc, htp_connp_req_data_consumed(connp));

    htp_connp_close(connp, nullptr);
    htp_connp_destroy_all(connp);
    htp_config_destroy(cfg);

    std::printf("LibHTP basic test OK\n");
    return 0;
}
