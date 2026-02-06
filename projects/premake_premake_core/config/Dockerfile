ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (Lua 5.3 headers/libs, libuuid)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    liblua5.3-dev uuid-dev \
 && rm -rf /var/lib/apt/lists/*

# Build a static library from the Premake host sources and install to /fuzz/install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /build && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cd /build && \
    SRCS=$(cd /fuzz/src && find src/host -name '*.c' ! -name 'premake_main.c') && \
    for f in $SRCS; do \
      out=o/$(basename "$f").o; \
      mkdir -p $(dirname "$out"); \
      ${CC} -O2 -fPIC -DPREMAKE_NO_BUILTIN_SCRIPTS -I/fuzz/src/src/host -c /fuzz/src/$f -o $out; \
    done && \
    ar rcs /fuzz/install/lib/libpremakecore.a o/*.o && ranlib /fuzz/install/lib/libpremakecore.a && \
    cp /fuzz/src/src/host/premake.h /fuzz/install/include/
