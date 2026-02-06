#include <iostream>
#include <s2n.h>

int main() {
    if (s2n_init() != S2N_SUCCESS) {
        std::cerr << "s2n_init failed: " << s2n_strerror_name(*s2n_errno_location()) << "\n";
        return 1;
    }

    unsigned long openssl_ver = s2n_get_openssl_version();
    std::cout << "OpenSSL version (compiled with): " << openssl_ver << "\n";

    // Basic sanity: create and free a config object
    struct s2n_config *config = s2n_config_new();
    if (!config) {
        std::cerr << "s2n_config_new failed: " << s2n_strerror_name(*s2n_errno_location()) << "\n";
        s2n_cleanup();
        return 1;
    }

    // Set default cipher preferences (may fail depending on libcrypto, ignore result in simple test)
    s2n_config_set_cipher_preferences(config, "default");

    s2n_config_free(config);

    if (s2n_cleanup() != S2N_SUCCESS) {
        std::cerr << "s2n_cleanup failed: " << s2n_strerror_name(*s2n_errno_location()) << "\n";
        return 1;
    }
    return 0;
}
