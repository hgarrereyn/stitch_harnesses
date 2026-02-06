#include <iostream>
#include <cstring>
#include <rime_api.h>

int main() {
    RimeApi* api = rime_get_api();
    if (!api) {
        std::cout << "Failed to get Rime API" << std::endl;
        return 1;
    }

    RimeTraits traits;
    RIME_STRUCT_INIT(RimeTraits, traits);
    traits.app_name = "rime.test";
    traits.log_dir = ""; // only stderr

    if (RIME_API_AVAILABLE(api, setup)) {
        api->setup(&traits);
    }
    if (RIME_API_AVAILABLE(api, initialize)) {
        api->initialize(&traits);
    }

    const char* ver = nullptr;
    if (RIME_API_AVAILABLE(api, get_version)) {
        ver = api->get_version();
    }

    if (RIME_API_AVAILABLE(api, finalize)) {
        api->finalize();
    }

    std::cout << "librime version: " << (ver ? ver : "unknown") << std::endl;
    return 0;
}
