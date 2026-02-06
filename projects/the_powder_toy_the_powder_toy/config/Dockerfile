ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config meson ninja-build python3 ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Configure and perform a no-op build/install to set up prefix
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src
RUN meson setup build \
      --prefix /fuzz/install \
      -Ddefault_library=static \
      -Dbuild_powder=false -Dbuild_render=false -Dbuild_font=false \
      -Dhttp=false -Dlua=none \
      -Dbuildtype=release -Db_lto=false && \
    meson compile -C build && \
    meson install -C build || true

# Build a small static library for common string utilities used by headers
RUN mkdir -p /fuzz/install/lib && \
    $CXX -O2 -fPIC -Isrc -c src/common/String.cpp -o /tmp/String.o && \
    ar rcs /fuzz/install/lib/libtptcommon.a /tmp/String.o

# Install public headers for fuzz harnesses
RUN mkdir -p /fuzz/install/include/common && \
    cp -v src/common/*.h /fuzz/install/include/common/
