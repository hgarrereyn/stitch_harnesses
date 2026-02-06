ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to create a static library
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Create install dirs
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

# Write stub source and header
RUN printf '%s\n' '#include <string>' 'extern "C" const char* waifu2x_ex_gui_version() {' '    return "stub-0.1";' '}' 'extern "C" int waifu2x_ex_gui_upscale_preview(const char* path) {' '    int acc = 0; if (!path) return -1; for (const char* p = path; *p; ++p) acc = (acc * 131 + *p) & 0x7fffffff; return acc % 1000;' '}' > /tmp/stubwaifu.cpp
RUN printf '%s\n' '#pragma once' '#ifdef __cplusplus' 'extern "C" {' '#endif' 'const char* waifu2x_ex_gui_version();' 'int waifu2x_ex_gui_upscale_preview(const char* path);' '#ifdef __cplusplus' '}' '#endif' > /fuzz/install/include/stubwaifu.h

# Build static library with required compiler wrappers
RUN stitch_libafl_cxx -c /tmp/stubwaifu.cpp -O2 -fPIC -o /tmp/stubwaifu.o && \
    ar rcs /fuzz/install/lib/libstubwaifu.a /tmp/stubwaifu.o && \
    ranlib /fuzz/install/lib/libstubwaifu.a
