#include <cstdio>
#include <cstring>
#include "mbedtls/version.h"
#include "mbedtls/x509_crt.h"

int main() {
    const char* ver_full = mbedtls_version_get_string_full();
    if (ver_full) {
        std::printf("Mbed TLS version: %s\n", ver_full);
    }
    mbedtls_x509_crt crt; 
    mbedtls_x509_crt_init(&crt);
    // Load a minimal invalid cert from memory to exercise a call path
    const unsigned char dummy[] = "-----BEGIN CERTIFICATE-----\nMIIB\n-----END CERTIFICATE-----\n";
    int ret = mbedtls_x509_crt_parse(&crt, dummy, sizeof(dummy));
    std::printf("Parse returned: %d (expected failure)\n", ret);
    mbedtls_x509_crt_free(&crt);
    return 0;
}
