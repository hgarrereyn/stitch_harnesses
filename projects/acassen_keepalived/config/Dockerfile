ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tooling
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends build-essential && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Create a minimal generated config and build a tiny static lib from project sources
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include/keepalived && \
    # Generate minimal config headers expected by the project
    printf "#ifndef _CONFIG_H\n#define _CONFIG_H\n#define PACKAGE_NAME \"keepalived\"\n#define PACKAGE_VERSION \"dev\"\n#define GIT_DATE \"01/01,1970\"\n#define GIT_YEAR \"1970\"\n#ifndef _GNU_SOURCE\n#define _GNU_SOURCE\n#endif\n#define KA_TMP_DIR \"/tmp\"\n#define RUNSTATEDIR \"/run\"\n#define PRI_tv_sec \"ld\"\n#define PRI_tv_usec \"ld\"\n#include \"config_warnings.h\"\n#endif\n" > lib/config.h && \
    cp lib/config_warnings.h.in lib/config_warnings.h && \
    # Build a small static library exposing some utility symbols
    stitch_libafl_cc -Ilib -I. -c lib/utils.c -o /fuzz/build/utils.o && \
    stitch_libafl_cc -Ilib -I. -c lib/memory.c -o /fuzz/build/memory.o && \
    stitch_libafl_cc -Ilib -I. -c lib/logger.c -o /fuzz/build/logger.o && \
    # Provide minimal stubs for a few parser utilities referenced by utils.c
    /bin/sh -c 'printf "#include \"config.h\"\n#include <stdarg.h>\n#include <stdbool.h>\n#include <stdint.h>\n#include \"parser.h\"\nvoid report_config_error(config_err_t t, const char *fmt, ...) { (void)t; (void)fmt; }\nbool read_unsigned(const char *s, unsigned *out, unsigned min, unsigned max, bool base10) { (void)s; (void)min; (void)max; (void)base10; if (out) *out = 0; return false; }\n" > /fuzz/build/stubs.c' && \
    stitch_libafl_cc -Ilib -I. -c /fuzz/build/stubs.c -o /fuzz/build/stubs.o && \
    ar rcs /fuzz/install/lib/libkeepalived.a /fuzz/build/utils.o /fuzz/build/memory.o /fuzz/build/logger.o /fuzz/build/stubs.o && \
    # Install headers for consumers
    cp -a lib/*.h /fuzz/install/include/ && \
    cp -a keepalived/include/*.h /fuzz/install/include/keepalived/ && \
    # Patch a C-only designated initializer to be C++ friendly in installed header
    sed -i 's/timeval_t b = { \.tv_sec = diff_hz \/ TIMER_HZ, \.tv_usec = diff_hz % TIMER_HZ };/timeval_t b; b.tv_sec = diff_hz \/ TIMER_HZ; b.tv_usec = diff_hz % TIMER_HZ;/' /fuzz/install/include/timer.h
