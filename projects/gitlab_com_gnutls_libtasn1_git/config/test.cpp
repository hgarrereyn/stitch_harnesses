#include <cstdio>
#include <libtasn1.h>

int main() {
    const char* ver = asn1_check_version(nullptr);
    if (!ver) return 1;
    std::printf("libtasn1 version: %s\n", ver);

    const char* ok = asn1_strerror(ASN1_SUCCESS);
    std::printf("ASN1_SUCCESS string: %s\n", ok ? ok : "(null)");

    // Simple DER snippet: INTEGER 5 -> 0x02 0x01 0x05
    unsigned char der[] = {0x02, 0x01, 0x05};
    int value_len = 0;
    long used = asn1_get_length_der(der + 1, 2, &value_len);
    std::printf("Length bytes used: %ld, value length: %d\n", used, value_len);

    return 0;
}
