ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (include cmake just in case)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    pkg-config \
    libjudy-dev \
    libgmp-dev \
    libpcap-dev \
    libjson-c-dev \
    libunistring-dev \
    flex \
    byacc \
    gengetopt \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=${CC} \
    -DCMAKE_CXX_COMPILER=${CXX} \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build --target install -j$(nproc)

# Manually install the static library and headers (project does not install them)
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && if [ -f /fuzz/build/lib/libzmaplib.a ]; then cp /fuzz/build/lib/libzmaplib.a /fuzz/install/lib/; fi \
 && if [ -f /fuzz/build/libzmaplib.a ]; then cp /fuzz/build/libzmaplib.a /fuzz/install/lib/; fi \
 && cp /fuzz/src/lib/*.h /fuzz/install/include/
