ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git ca-certificates unzip python3 cmake ninja-build make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build the project (static libs where applicable)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -S /fuzz/src \
    -B /fuzz/build \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DFUZZTEST_BUILD_TESTING=OFF \
    -DFUZZTEST_BUILD_FLATBUFFERS=OFF \
 && ninja -j$(nproc)

# Install third-party dependencies that provide install() rules (e.g., Abseil)
RUN cmake --install /fuzz/build --prefix /fuzz/install || true

# Expose headers for consumers. Copy needed source trees into include prefix.
RUN mkdir -p /fuzz/install/include \
 && cp -r /fuzz/src/fuzztest /fuzz/install/include/ \
 && cp -r /fuzz/src/common /fuzz/install/include/
