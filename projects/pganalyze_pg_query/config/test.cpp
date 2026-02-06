#include <cstdio>
#include <cstring>
#include "pg_query.h"

int main() {
    const char* sql = "SELECT 1";
    PgQueryParseResult res = pg_query_parse(sql);
    if (res.error) {
        printf("Error: %s\n", res.error->message ? res.error->message : "unknown");
        pg_query_free_parse_result(res);
        return 1;
    }
    if (res.parse_tree) {
        size_t n = strlen(res.parse_tree);
        printf("Parsed OK (%zu bytes)\n", n);
    } else {
        printf("Parsed but no tree returned\n");
    }
    pg_query_free_parse_result(res);
    PgQueryFingerprintResult f = pg_query_fingerprint(sql);
    if (f.error == NULL && f.fingerprint_str) {
        printf("Fingerprint: %s\n", f.fingerprint_str);
    }
    pg_query_free_fingerprint_result(f);
    return 0;
}
