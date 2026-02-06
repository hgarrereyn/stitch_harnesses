#include <cstdio>
#include <cstring>
#define PCRE2_CODE_UNIT_WIDTH 8
extern "C" {
#include <pcre2.h>
}

int main() {
    const char *pattern = "a+";
    const char *subject = "baaac";

    int error_number = 0;
    PCRE2_SIZE error_offset = 0;
    pcre2_code *re = pcre2_compile(
        (PCRE2_SPTR)pattern,
        PCRE2_ZERO_TERMINATED,
        0,
        &error_number,
        &error_offset,
        NULL);
    if (!re) {
        std::printf("compile error %d at offset %zu\n", error_number, (size_t)error_offset);
        return 1;
    }

    pcre2_match_data *md = pcre2_match_data_create_from_pattern(re, NULL);
    int rc = pcre2_match(
        re,
        (PCRE2_SPTR)subject,
        std::strlen(subject),
        0,
        0,
        md,
        NULL);

    if (rc >= 0) {
        PCRE2_SIZE *ov = pcre2_get_ovector_pointer(md);
        std::printf("Matched: '%.*s'\n", (int)(ov[1]-ov[0]), subject + ov[0]);
    } else if (rc == PCRE2_ERROR_NOMATCH) {
        std::printf("No match\n");
    } else {
        std::printf("Match error %d\n", rc);
    }

    pcre2_match_data_free(md);
    pcre2_code_free(re);
    return 0;
}
