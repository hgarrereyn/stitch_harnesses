ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for meson build
RUN apt-get update && apt-get install -y --no-install-recommends \
    meson \
    pkg-config \
    python3 \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure, ensure libraries go to /fuzz/install/lib, build static lib, and install
RUN meson setup build \
      --prefix=/fuzz/install \
      --libdir=lib \
      -Ddefault_library=static \
      -Ddocs=false -Dbin=false -Dtests=false \
    && meson compile -C build \
    && meson install -C build
