#include <iostream>
#include <xls.h>

int main() {
    const char* ver = xls::xls_getVersion();
    const char* ok = xls::xls_getError(xls::LIBXLS_OK);
    std::cout << "libxls version: " << (ver ? ver : "(null)") << "\n";
    std::cout << "error string for OK: " << (ok ? ok : "(null)") << "\n";
    return 0;
}
