ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    build-essential \
    libglib2.0-dev libjansson-dev libconfig-dev libnice-dev \
    libssl-dev libsrtp2-dev zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate configure script and build with fuzzing compilers
RUN sh autogen.sh && \
    CC=gf_libafl_cc CXX=gf_libafl_cxx \
    ./configure --prefix=/fuzz/install \
      --disable-websockets --disable-data-channels --disable-rabbitmq --disable-mqtt \
    && make -j$(nproc) \
    && make install \
    # Build a minimal static archive exposing some public helpers for linking tests
    && mkdir -p /fuzz/install/lib \
    && gf_libafl_cc -I/fuzz/src/src -I/fuzz/install/include/janus -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -c src/utils.c -o /fuzz/install/lib/utils.o \
    && gf_libafl_cc -I/fuzz/src/src -I/fuzz/install/include/janus -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -c src/log.c -o /fuzz/install/lib/log.o \
    && printf '%s\n' '#include <glib.h>' 'int janus_log_level = 4;' 'gboolean janus_log_timestamps = 0;' 'gboolean janus_log_colors = 0;' 'char *janus_log_global_prefix = 0;' 'int lock_debug = 0;' > /tmp/jlog_stubs.c \
    && gf_libafl_cc -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -c /tmp/jlog_stubs.c -o /fuzz/install/lib/jlog_stubs.o \
    && ar rcs /fuzz/install/lib/libjanuscore.a /fuzz/install/lib/utils.o /fuzz/install/lib/log.o /fuzz/install/lib/jlog_stubs.o

ENV PKG_CONFIG_PATH=/fuzz/install/lib/pkgconfig:/usr/lib/x86_64-linux-gnu/pkgconfig
