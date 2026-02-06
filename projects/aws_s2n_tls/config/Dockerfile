ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building s2n-tls
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        build-essential pkg-config cmake libssl-dev ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build s2n-tls as a static library and install it
RUN cmake . -B build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DUNSAFE_TREAT_WARNINGS_AS_ERRORS=OFF \
      -DBUILD_TESTING=OFF \
      -DS2N_INSTALL_S2NC_S2ND=OFF && \
    cmake --build build -j$(nproc) && \
    cmake --install build
