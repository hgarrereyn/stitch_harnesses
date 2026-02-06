#include <cstdio>
#include <cstdlib>
#include <cstring>
extern "C" {
#include "readstat.h"
}

int metadata_handler(readstat_metadata_t *metadata, void *ctx) {
    int *count = static_cast<int*>(ctx);
    *count = readstat_get_var_count(metadata);
    return READSTAT_HANDLER_OK;
}

int main() {
    // Basic sanity checks of API usage
    const char *msg = readstat_error_message(READSTAT_ERROR_READ);
    if (!msg) return 1;

    int var_count = 0;
    readstat_parser_t *parser = readstat_parser_init();
    if (!parser) return 1;
    readstat_set_metadata_handler(parser, metadata_handler);

    // We won't actually parse a file here; just ensure we can create/free objects
    readstat_parser_free(parser);

    // Exercise writer API minimally
    readstat_writer_t *writer = readstat_writer_init();
    if (!writer) return 1;
    readstat_writer_free(writer);

    // Print something deterministic so the test runner knows it executed
    std::printf("ReadStat OK: %s, vars=%d\n", msg, var_count);
    return 0;
}
