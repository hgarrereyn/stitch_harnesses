ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autoconf-based build
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config gawk ca-certificates file \
    libssl-dev zlib1g-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and install prefix. Disable optional features to simplify build.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install \
    --disable-md2man --disable-roll-simd \
    --disable-xxhash --disable-zstd --disable-lz4 \
    --with-included-popt --with-included-zlib

# Build and install
RUN make -j"$(nproc)" && make install

# Create static archives and install headers for external use
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/rsync/lib && \
    OBJ_ALL=$(find . -type f -name '*.o' | grep -vE '/(testrun|getgroups|getfsdev|t_stub|t_unsafe|trimslash|wildtest|tls|main)\.o$' || true) && \
    ar rcs /fuzz/install/lib/librsync.a $OBJ_ALL && \
    ar rcs /fuzz/install/lib/librsyncmini.a lib/wildmatch.o && \
    cp -f rsync.h errcode.h byteorder.h ifuncs.h itypes.h inums.h proto.h config.h /fuzz/install/include/rsync/ && \
    cp -f lib/*.h /fuzz/install/include/rsync/lib/ && \
    true
