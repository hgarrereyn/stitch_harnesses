ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    libsqlite3-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with required compilers and install prefix. Disable optional image output to avoid extra deps.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install --disable-image-output

# Build installed binaries (not used for linking but ensures project builds correctly)
RUN make -j"$(nproc)" && make install

# Build our own static library from the core sources and install headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include /tmp/vnobj \
 && for f in src/*.c; do \
      bn=$(basename "$f"); \
      case "$bn" in vnstat.c|vnstatd.c|vnstati.c) ;; \
      *) ${CC} -I./src -I. -c "$f" -o "/tmp/vnobj/${bn%.c}.o" ;; \
      esac; \
    done \
 && ar rcs /fuzz/install/lib/libvnstat.a /tmp/vnobj/*.o \
 && ranlib /fuzz/install/lib/libvnstat.a \
 && cp -v src/*.h src/config.h /fuzz/install/include/
