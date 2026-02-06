ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install static libpffft.a
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include; \
    cd /fuzz/build; \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    stitch_libafl_cc -O2 -fPIC -I/fuzz/src -c /fuzz/src/pffft.c -o pffft.o; \
    stitch_libafl_cc -O2 -fPIC -I/fuzz/src -c /fuzz/src/fftpack.c -o fftpack.o; \
    ar rcs libpffft.a pffft.o fftpack.o; \
    install -m 0644 libpffft.a /fuzz/install/lib/; \
    install -m 0644 /fuzz/src/pffft.h /fuzz/install/include/; \
    # Also install fftpack.h for completeness (not required for public API)
    install -m 0644 /fuzz/src/fftpack.h /fuzz/install/include/
