ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
    pkg-config \
    ninja-build \
    meson \
    libbz2-dev \
    liblz4-dev \
    libssl-dev \
    libpq-dev \
    libxml2-dev \
    libyaml-dev \
    zlib1g-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build project with meson to generate configuration header and install binaries
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz/src
RUN meson setup build \
      --buildtype=release \
      -Dlibssh2=disabled \
      -Dlibzstd=disabled \
      --prefix=/fuzz/install
# Force-disable libbacktrace usage by editing generated config before building
RUN sed -i 's/^#define HAVE_LIBBACKTRACE.*/\/\/ HAVE_LIBBACKTRACE disabled/' build/src/build.auto.h || true
RUN ninja -C build install

# Create a minimal static library from common sources for linking
WORKDIR /fuzz/src/src
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/common obj && \
    cp /fuzz/src/build/src/build.auto.h ./build.auto.h && \
    cp /fuzz/src/build/src/build.auto.h /fuzz/install/include/ && \
    cp common/encode.h /fuzz/install/include/common/ && \
    for f in \
      common/debug.c \
      common/encode.c \
      common/error/error.c \
      common/io/filter/buffer.c \
      common/io/filter/filter.c \
      common/io/filter/group.c \
      common/io/filter/sink.c \
      common/io/bufferRead.c \
      common/io/bufferWrite.c \
      common/io/io.c \
      common/io/read.c \
      common/io/write.c \
      common/log.c \
      common/memContext.c \
      common/stackTrace.c \
      common/time.c \
      common/type/blob.c \
      common/type/buffer.c \
      common/type/convert.c \
      common/type/keyValue.c \
      common/type/list.c \
      common/type/object.c \
      common/type/pack.c \
      common/type/stringId.c \
      common/type/stringList.c \
      common/type/stringStatic.c \
      common/type/stringZ.c \
      common/type/variant.c \
      common/type/variantList.c \
      common/user.c \
      common/wait.c \
      config/common.c \
      storage/posix/read.c \
      storage/posix/storage.c \
      storage/posix/write.c \
      storage/iterator.c \
      storage/list.c \
      storage/read.c \
      storage/storage.c \
      storage/write.c; do \
        gf_libafl_cc -D_POSIX_C_SOURCE=200809L -I. -O2 -c $f -o obj/$(basename $f .c).o; \
      done && \
    ar rcs /fuzz/install/lib/libpgbackrestcore.a obj/*.o
