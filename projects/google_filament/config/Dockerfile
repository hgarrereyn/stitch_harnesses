ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/build

# Configure math subproject with required compilers and install prefix
RUN cmake -G Ninja \
    -S /fuzz/src/libs/math \
    -B /fuzz/build/math \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build the static library target
RUN cmake --build /fuzz/build/math --target math -- -v

# Install headers and copy the static archive into /fuzz/install/lib
RUN cmake --install /fuzz/build/math && \
    mkdir -p /fuzz/install/lib && \
    cp /fuzz/build/math/libmath.a /fuzz/install/lib/
