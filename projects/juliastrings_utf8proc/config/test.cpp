#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include <utf8proc.h>
}

int main() {
    // Print version
    printf("utf8proc version: %s\n", utf8proc_version());

    // Example: casefold "\xC3\x9F" (ß) -> "ss"
    const utf8proc_uint8_t input_str[] = "\xC3\x9F"; // ß in UTF-8
    utf8proc_uint8_t *folded = nullptr;
    utf8proc_ssize_t r = utf8proc_map(input_str, 0, &folded, (utf8proc_option_t)(UTF8PROC_NULLTERM | UTF8PROC_CASEFOLD));
    if (r < 0) {
        printf("utf8proc_map error: %s\n", utf8proc_errmsg(r));
        return 1;
    }
    printf("casefold(ß) = %s\n", folded);

    // Decode first codepoint and encode it back
    utf8proc_int32_t cp = 0;
    utf8proc_ssize_t len = utf8proc_iterate(folded, -1, &cp);
    if (len > 0) {
        utf8proc_uint8_t out[8] = {0};
        utf8proc_encode_char(cp, out);
        printf("first codepoint after fold encoded back: %s\n", out);
    }

    free(folded);
    return 0;
}
