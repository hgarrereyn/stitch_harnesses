ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson pkg-config ninja-build \
    libglib2.0-dev libnss3-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build and install libcacard using Meson
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN meson setup builddir \
    --prefix=/fuzz/install \
    -Ddefault_library=static \
    -Dpcsc=disabled \
    -Ddisable_tests=true && \
    meson compile -C builddir -j$(nproc) && \
    meson install -C builddir
