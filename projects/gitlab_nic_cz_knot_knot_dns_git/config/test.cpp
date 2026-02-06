#include <cstdio>
#include <cstring>
extern "C" {
#include <libzscanner/scanner.h>
}

static void on_record(zs_scanner_t *s) {
    printf("record owner_len=%u type=%u\n", (unsigned)s->r_owner_length, (unsigned)s->r_type);
}

static void on_error(zs_scanner_t *s) {
    printf("error code=%d on line=%llu\n", s->error.code, (unsigned long long)s->line_counter);
}

int main() {
    zs_scanner_t s;
    if (zs_init(&s, ".", 1 /*IN*/, 3600) != 0) return 1;

    const char *zone = "example.com. 3600 IN A 1.2.3.4\n";
    if (zs_set_input_string(&s, zone, strlen(zone)) != 0) { zs_deinit(&s); return 1; }
    if (zs_set_processing(&s, on_record, on_error, nullptr) != 0) { zs_deinit(&s); return 1; }

    if (zs_parse_record(&s) != 0) { zs_deinit(&s); return 1; }
    if (s.state != ZS_STATE_DATA) { zs_deinit(&s); return 1; }

    zs_deinit(&s);
    return 0;
}
