ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson \
    ninja-build \
    pkg-config \
    freerdp2-dev \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Build and install rdpapplist using meson
WORKDIR /fuzz/src/rdpapplist
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN meson setup build --prefix=/fuzz/install && \
    meson compile -C build && \
    meson install -C build
