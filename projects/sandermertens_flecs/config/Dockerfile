ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Install minimal build tooling
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build pkg-config \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure and build static-only
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DFLECS_STATIC=ON -DFLECS_SHARED=OFF \
 && cmake --build build --target install --config Release
