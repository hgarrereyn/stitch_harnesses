#include <iostream>
#define ENABLE_CRYPTO_MBEDTLS 1
#include <openvpn-plugin.h>

int main() {
    std::cout << "OpenVPN plugin API version: " << OPENVPN_PLUGIN_VERSION << "\n";
    std::cout << "OPENVPN_PLUGIN_UP id: " << OPENVPN_PLUGIN_UP << "\n";
    std::cout << "Function success code: " << OPENVPN_PLUGIN_FUNC_SUCCESS << "\n";
    openvpn_x509_cert_t* cert_ptr = nullptr;
    (void)cert_ptr;
    openvpn_plugin_string_list list{}; list.next = nullptr; list.name = nullptr; list.value = nullptr;
    std::cout << "OK\n";
    return 0;
}
