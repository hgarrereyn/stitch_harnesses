ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: build essentials, Rust (via rustup), bindgen, and libclang for bindgen
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates curl git pkg-config python3 \
    libclang-17-dev clang-17 llvm-17-dev \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

# Install Rust toolchain (stable, which is >=1.84 at time of writing) and bindgen
ENV RUSTUP_HOME=/opt/rustup \
    CARGO_HOME=/opt/cargo \
    PATH=/opt/cargo/bin:$PATH
RUN curl -fsSL https://sh.rustup.rs | sh -s -- -y --default-toolchain stable \
    && cargo install bindgen-cli --locked --version ">=0.60"

# Build dbus-broker with meson using LibAFL compiler wrappers and disable optional deps
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx

WORKDIR /fuzz/src
RUN meson setup build \
    --prefix=/fuzz/install \
    --buildtype=release \
    -Dlauncher=false -Dtests=false -Ddocs=false -Ddoctest=false -Dapparmor=false -Daudit=false -Dselinux=false \
    && meson compile -C build \
    && meson install -C build || true

# Install headers for external builds (copy project headers)
RUN mkdir -p /fuzz/install/include \
    && for d in dbus util bus broker launch session; do \
         mkdir -p /fuzz/install/include/$d; \
         [ -d src/$d ] && cp -a src/$d/*.h /fuzz/install/include/$d/ 2>/dev/null || true; \
       done \
    && mkdir -p /fuzz/install/lib \
    && cp -a build/src/*.a /fuzz/install/lib/ 2>/dev/null || true
