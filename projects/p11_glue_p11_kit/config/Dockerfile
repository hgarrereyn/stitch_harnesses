ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    meson \
    pkg-config \
    python3 \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install p11-kit
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

RUN meson setup build \
      --prefix=/fuzz/install \
      --buildtype=release \
      -Dtrust_module=disabled \
      -Dsystemd=disabled \
      -Dbash_completion=disabled \
      -Dzsh_completion=disabled \
      -Dgtk_doc=false \
      -Dman=false \
      -Dnls=false \
      -Dtest=false \
      -Dlibffi=disabled \
    && meson compile -C build \
    && meson install -C build
