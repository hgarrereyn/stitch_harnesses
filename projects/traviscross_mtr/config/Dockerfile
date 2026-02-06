ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    libcap-dev \
    libncursesw5-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Bootstrap autotools and configure
RUN ./bootstrap.sh && \
    ./configure --prefix=/fuzz/install \
      --without-gtk \
      --without-jansson \
      --disable-bash-completion

# Build and install
RUN make -j$(nproc) && make install

# Package a static library from the packet objects and install headers
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include /fuzz/install/include/portability; \
    objs=""; \
    for f in \
      packet/packet.o \
      packet/cmdparse.o \
      packet/command.o \
      packet/construct_unix.o \
      packet/deconstruct_unix.o \
      packet/probe.o \
      packet/timeval.o \
      packet/wait_unix.o \
      packet/probe_unix.o \
      packet/sockaddr.o; do \
        if [ -f "$f" ]; then objs="$objs $f"; fi; \
    done; \
    # Optional portability objects
    for f in portability/error.o portability/getopt.o portability/getopt1.o; do \
        if [ -f "$f" ]; then objs="$objs $f"; fi; \
    done; \
    test -n "$objs"; \
    ar rcs /fuzz/install/lib/libmtrpacket.a $objs; \
    # Install headers (flattened for packet, and keep portability in subdir)
    cp -a packet/*.h /fuzz/install/include/; \
    cp -a portability/*.h /fuzz/install/include/portability/ || true
