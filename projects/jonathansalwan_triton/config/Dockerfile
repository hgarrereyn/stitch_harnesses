ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and build Capstone 5 statically
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git ca-certificates ninja-build pkg-config build-essential python3 cmake && \
    rm -rf /var/lib/apt/lists/*

# Build and install Capstone v5 as static lib into /fuzz/install
RUN git clone --depth=1 --branch 5.0.1 https://github.com/capstone-engine/capstone /tmp/capstone && \
    cmake -S /tmp/capstone -B /tmp/capstone/build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DCAPSTONE_BUILD_STATIC=ON && \
    cmake --build /tmp/capstone/build -j && \
    cmake --install /tmp/capstone/build && \
    rm -rf /tmp/capstone

# Build Triton as a static library without optional heavy deps
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DPYTHON_BINDINGS=OFF \
      -DZ3_INTERFACE=OFF \
      -DBITWUZLA_INTERFACE=OFF \
      -DLLVM_INTERFACE=OFF \
      -DCMAKE_PREFIX_PATH=/fuzz/install && \
    cmake --build build -j && \
    cmake --install build
