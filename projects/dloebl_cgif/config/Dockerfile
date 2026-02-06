ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson \
    pkg-config \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Build and install libcgif statically to /fuzz/install
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src
RUN meson setup builddir \
        --prefix /fuzz/install \
        --libdir lib \
        -Ddefault_library=static \
        -Dbuildtype=release \
        -Dexamples=false \
        -Dtests=false \
    && meson compile -C builddir \
    && meson install -C builddir \
    # Ensure all public headers are installed
    && mkdir -p /fuzz/install/include \
    && cp -v inc/cgif_raw.h /fuzz/install/include/
