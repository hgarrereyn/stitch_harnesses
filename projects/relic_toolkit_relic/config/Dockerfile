ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake is required) and keep image minimal
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake make ninja-build pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build RELIC as static library only (easy backend, no GMP)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src
RUN cmake -S . -B build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSHLIB=OFF -DSTLIB=ON \
    -DTESTS=0 -DBENCH=0 -DDOCUM=OFF \
    -DARITH=easy \
    -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build -j"$(nproc)" --target install
