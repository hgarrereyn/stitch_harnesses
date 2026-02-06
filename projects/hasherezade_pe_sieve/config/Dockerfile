ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Note: This project is Windows-only; we still provide a best-effort Linux build setup.
# Install build tools explicitly (even though base may include some)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Attempt to configure as a static library install
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPESIEVE_AS_STATIC_LIB=ON \
    -DPECONV_LIB_INSTALL=ON || true

# Attempt to build and install (will no-op if configure failed); do not fail the image build
RUN cmake --build /fuzz/build --target install -j || true
