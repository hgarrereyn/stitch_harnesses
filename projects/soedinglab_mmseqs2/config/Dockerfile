ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies: CMake, OpenMP for clang-17, zlib, bzip2, and rustup for Rust >=1.68
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates curl git pkg-config \
    cmake ninja-build \
    zlib1g-dev libbz2-dev \
    libomp-17-dev \
 && rm -rf /var/lib/apt/lists/*

# Install Rust (stable) for building block-aligner via Corrosion
ENV RUSTUP_HOME=/opt/rustup CARGO_HOME=/opt/cargo
ENV PATH="/opt/cargo/bin:${PATH}"
RUN curl -fsSL https://sh.rustup.rs | sh -s -- -y --profile minimal && \
    rustc --version && cargo --version

# Configure and build static framework only
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DFRAMEWORK_ONLY=1 \
    -DUSE_SYSTEM_ZSTD=0 \
    -DREQUIRE_OPENMP=1 \
    /fuzz/src && \
    ninja -v

# Install: manually copy the static library and headers as the project doesn't install them in FRAMEWORK_ONLY mode
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/commons && \
    cp -v /fuzz/build/src/libmmseqs-framework.a /fuzz/install/lib/ && \
    cp -v /fuzz/src/src/commons/*.h /fuzz/install/include/commons/
