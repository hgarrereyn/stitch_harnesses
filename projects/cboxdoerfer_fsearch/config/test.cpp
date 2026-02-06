#include <stdio.h>
extern "C" {
#include "fsearch_string_utils.h"
}

int main() {
    const char *wc = "data-*.log";
    char *re = fsearch_string_convert_wildcard_to_regex_expression(wc);
    if (re) {
        printf("Wildcard: %s\nRegex: %s\n", wc, re);
    } else {
        printf("Conversion failed\n");
    }
    printf("Has wildcards: %d\n", fsearch_string_has_wildcards(wc));
    printf("Is empty: %d\n", fsearch_string_is_empty("   \t\n"));
    printf("Ext: %s\n", fsearch_string_get_extension("file.txt"));
    return 0;
}
