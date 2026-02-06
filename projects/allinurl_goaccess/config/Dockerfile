ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gettext autopoint m4 \
    libncurses-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install goaccess
WORKDIR /fuzz/src

# Regenerate build system and configure with fuzz compilers
RUN autoreconf -fiv
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx ./configure --prefix=/fuzz/install

# Build
RUN make -j$(nproc)

# Install binaries and configs
RUN make install

# Install headers (including generated) and build a minimal static library for linking
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -a src/*.h /fuzz/install/include/ \
 && [ -d src/win ] && cp -a src/win/*.h /fuzz/install/include/ || true \
 && [ -f src/config.h ] && cp -a src/config.h /fuzz/install/include/config.h || true \
 && printf '#include <stdarg.h>\n#include "settings.h"\nGConf conf;\nvoid dbg_fprintf (const char *fmt, ...) { (void)fmt; }\n' > /tmp/stubs.c \
 && stitch_libafl_cc -I./src -I/fuzz/install/include -DHAVE_CONFIG_H -c /tmp/stubs.c -o /tmp/stubs.o \
 && stitch_libafl_cc -I./src -I/fuzz/install/include -DHAVE_CONFIG_H -c src/base64.c -o /tmp/base64.o \
 && stitch_libafl_cc -I./src -I/fuzz/install/include -DHAVE_CONFIG_H -c src/bitmap.c -o /tmp/bitmap.o \
 && stitch_libafl_cc -I./src -I/fuzz/install/include -DHAVE_CONFIG_H -c src/xmalloc.c -o /tmp/xmalloc.o \
 && ar rcs /fuzz/install/lib/libgoaccess.a /tmp/base64.o /tmp/bitmap.o /tmp/xmalloc.o /tmp/stubs.o
