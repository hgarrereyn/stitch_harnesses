ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends cmake make pkg-config && rm -rf /var/lib/apt/lists/*

# Configure, build, and install zlib-ng as a static library
WORKDIR /fuzz/src
RUN cmake -S . -B build -G "Unix Makefiles" \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_TESTING=OFF \
    -DWITH_GTEST=OFF \
    -DINSTALL_UTILS=OFF \
    && cmake --build build -j"$(nproc)" \
    && cmake --install build
