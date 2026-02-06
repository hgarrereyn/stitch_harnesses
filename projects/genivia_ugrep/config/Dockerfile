ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal toolchain
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build a static libreflex.a manually (without AVX-specific sources)
RUN mkdir -p /fuzz/build && \
    cd /fuzz/build && \
    SRCS="/fuzz/src/lib/convert.cpp /fuzz/src/lib/debug.cpp /fuzz/src/lib/error.cpp /fuzz/src/lib/input.cpp /fuzz/src/lib/matcher.cpp /fuzz/src/lib/pattern.cpp /fuzz/src/lib/posix.cpp /fuzz/src/lib/simd.cpp /fuzz/src/lib/unicode.cpp /fuzz/src/lib/utf8.cpp /fuzz/src/lib/block_scripts.cpp /fuzz/src/lib/language_scripts.cpp /fuzz/src/lib/letter_scripts.cpp /fuzz/src/lib/letter_case.cpp /fuzz/src/lib/composer.cpp" && \
    for f in $SRCS; do \
      gf_libafl_cxx -O2 -fPIC -I/fuzz/src/include -c "$f"; \
    done && \
    ar rcs libreflex.a *.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp libreflex.a /fuzz/install/lib/ && \
    cp -a /fuzz/src/include/* /fuzz/install/include/
