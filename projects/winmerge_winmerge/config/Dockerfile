ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install libxdiff (vendored in Externals/xdiff)
RUN set -eux; \
    export DEBIAN_FRONTEND=noninteractive; \
    apt-get update; apt-get install -y --no-install-recommends ca-certificates; \
    rm -rf /var/lib/apt/lists/*;

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

# Build static library and install headers
RUN set -eux; \
    mkdir -p /fuzz/build/xdiff /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/src/Externals/xdiff; \
    for f in *.c; do \
      ${CC} -O2 -fPIC -I. -c "$f" -o "/fuzz/build/xdiff/${f%.c}.o"; \
    done; \
    ar rcs /fuzz/build/xdiff/libxdiff.a /fuzz/build/xdiff/*.o; \
    ranlib /fuzz/build/xdiff/libxdiff.a; \
    install -m 0644 xdiff.h /fuzz/install/include/; \
    install -m 0644 /fuzz/build/xdiff/libxdiff.a /fuzz/install/lib/
