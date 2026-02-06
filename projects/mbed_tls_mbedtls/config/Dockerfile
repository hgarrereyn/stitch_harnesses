ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake ninja-build make python3 python3-pip perl ca-certificates pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Install Python packages needed to generate sources
RUN python3 -m pip install --no-cache-dir -r /fuzz/src/scripts/basic.requirements.txt

# Configure, build, install static libraries only
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release \
    -DENABLE_TESTING=Off \
    -DENABLE_PROGRAMS=Off \
    -DMBEDTLS_FATAL_WARNINGS=Off \
    -DUSE_STATIC_MBEDTLS_LIBRARY=On \
    -DUSE_SHARED_MBEDTLS_LIBRARY=Off \
    /fuzz/src && \
    cmake --build . --target install
