ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install libmpg123 (static-only)
ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /fuzz/src

# Install minimal build deps that may be missing (libtool runtime for libltdl if needed is avoided by disabling modules)
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    pkg-config \
    ca-certificates \
    bash \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static lib only
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    --with-cpu=generic_fpu \
    --disable-modules \
    --disable-network \
    --disable-ipv6 \
    --disable-buffer \
    --disable-messages || (cat config.log || true; exit 1)

RUN make -j"$(nproc)" && make install

# Show what we installed (for debugging)
RUN ls -al /fuzz/install && ls -al /fuzz/install/lib && ls -al /fuzz/install/include
