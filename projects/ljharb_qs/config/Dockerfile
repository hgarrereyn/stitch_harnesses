ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install basic build tools needed to create a small C static library shim
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Build and install a minimal C shim library that mimics a tiny portion of qs API
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx INSTALL_PREFIX=/fuzz/install
RUN set -eux; \
    mkdir -p /tmp/qs_shim /fuzz/install/include /fuzz/install/lib; \
    printf '%s\n' \
    '#ifndef QS_H' \
    '#define QS_H' \
    '#ifdef __cplusplus' \
    'extern "C" {' \
    '#endif' \
    'char* qs_stringify(const char* key, const char* value);' \
    'char* qs_parse_value(const char* query, const char* key);' \
    'void qs_free(char* s);' \
    '#ifdef __cplusplus' \
    '}' \
    '#endif' \
    '#endif' \
    > /tmp/qs_shim/qs.h; \
    printf '%s\n' \
    '#include <stdlib.h>' \
    '#include <string.h>' \
    '' \
    'static char* qs_strdup_range(const char* start, size_t len) {' \
    '    char* out = (char*)malloc(len + 1);' \
    '    if (!out) return NULL;' \
    '    memcpy(out, start, len);' \
    '    out[len] = 0;' \
    '    return out;' \
    '}' \
    '' \
    'char* qs_stringify(const char* key, const char* value) {' \
    '    if (!key) key = "";' \
    '    if (!value) value = "";' \
    '    size_t klen = strlen(key);' \
    '    size_t vlen = strlen(value);' \
    '    size_t len = klen + 1 + vlen;' \
    '    char* out = (char*)malloc(len + 1);' \
    '    if (!out) return NULL;' \
    '    memcpy(out, key, klen);' \
    '    out[klen] = 61;' \
    '    memcpy(out + klen + 1, value, vlen);' \
    '    out[len] = 0;' \
    '    return out;' \
    '}' \
    '' \
    'char* qs_parse_value(const char* query, const char* key) {' \
    '    if (!query || !key) return NULL;' \
    '    size_t klen = strlen(key);' \
    '    const char* p = query;' \
    '    while (*p) {' \
    '        const char* pair_start = p;' \
    '        const char* amp = strchr(p, 38);' \
    '        const char* pair_end = amp ? amp : (p + strlen(p));' \
    '        const char* eq = memchr(pair_start, 61, (size_t)(pair_end - pair_start));' \
    '        if (eq) {' \
    '            size_t keylen = (size_t)(eq - pair_start);' \
    '            if (keylen == klen && strncmp(pair_start, key, klen) == 0) {' \
    '                const char* val_start = eq + 1;' \
    '                size_t vlen = (size_t)(pair_end - val_start);' \
    '                return qs_strdup_range(val_start, vlen);' \
    '            }' \
    '        }' \
    '        if (!amp) break;' \
    '        p = amp + 1;' \
    '    }' \
    '    return NULL;' \
    '}' \
    '' \
    'void qs_free(char* s) {' \
    '    free(s);' \
    '}' \
    > /tmp/qs_shim/qs.c; \
    $CC -O2 -fPIC -c /tmp/qs_shim/qs.c -o /tmp/qs_shim/qs.o; \
    ar rcs /tmp/qs_shim/libqs.a /tmp/qs_shim/qs.o; \
    cp /tmp/qs_shim/libqs.a /fuzz/install/lib/; \
    cp /tmp/qs_shim/qs.h /fuzz/install/include/

# Nothing else to install; headers and static lib are under /fuzz/install
