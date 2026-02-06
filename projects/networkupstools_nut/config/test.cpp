#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
extern "C" {
#include <upsclient.h>
}

int main() {
    // Test token helpers
    const char* status = "OL DISCHRG"
;   int has_ol = upscli_str_contains_token(status, "OL");
    int has_ob = upscli_str_contains_token(status, "OB");

    // Test split address helper (no network activity)
    char *host = nullptr; uint16_t port = 0;
    int rc = upscli_splitaddr("localhost:3493", &host, &port);

    printf("has_ol=%d has_ob=%d split_rc=%d host=%s port=%u\n",
           has_ol, has_ob, rc, host ? host : "(null)", (unsigned)port);

    free(host); // upsclient.c uses malloc for host copy
    return 0;
}
