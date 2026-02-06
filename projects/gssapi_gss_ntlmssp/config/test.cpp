#include <iostream>
#include <gssapi/gssapi.h>
#include <gssapi/gssapi_ext.h>
#include <gssapi/gssapi_ntlmssp.h>

int main() {
    // Print known OID string length from the header to verify inclusion
    std::cout << "GSS-NTLMSSP OID length: " << GSS_NTLMSSP_OID_LENGTH << "\n";
    // Also print known constant strings to ensure header parses
    std::cout << "Base OID length: " << GSS_NTLMSSP_BASE_OID_LENGTH << "\n";
    return 0;
}
