ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system deps required for the minimal static library we build
# We use the provided clang wrappers to build a tiny static library from the project's sources

# Build a minimal static library from a standalone component
RUN mkdir -p /fuzz/build-mini /fuzz/install/lib /fuzz/install/include/imgbrd && \
    cp /fuzz/src/src/lib/src/exponential-moving-average.h /fuzz/install/include/imgbrd/ && \
    /opt/gf_bin/bin/gf_libafl_cxx -c -O2 -fPIC /fuzz/src/src/lib/src/exponential-moving-average.cpp -o /fuzz/build-mini/ema.o && \
    ar rcs /fuzz/install/lib/libimgbrd-mini.a /fuzz/build-mini/ema.o
