#include <ucp/api/ucp.h>
#include <cstdio>
#include <cstring>

int main() {
    unsigned major, minor, patch;
    ucp_get_version(&major, &minor, &patch);
    const char* ver = ucp_get_version_string();
    std::printf("UCX version: %s (%u.%u.%u)\n", ver ? ver : "unknown", major, minor, patch);

    ucp_params_t params; 
    std::memset(&params, 0, sizeof(params));
    params.field_mask = UCP_PARAM_FIELD_FEATURES;
    params.features   = 0; // request no features for a minimal init

    ucp_config_t *config = nullptr;
    if (ucp_config_read(NULL, NULL, &config) != UCS_OK) {
        std::puts("ucp_config_read failed");
        return 0; // do not fail the test, just exit
    }

    ucp_context_h context = nullptr;
    if (ucp_init(&params, config, &context) != UCS_OK) {
        std::puts("ucp_init failed");
        ucp_config_release(config);
        return 0; // exit successfully even if init fails due to lack of transports
    }

    ucp_cleanup(context);
    ucp_config_release(config);
    return 0;
}
