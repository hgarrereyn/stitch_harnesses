ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Header-only library; install cmake (if missing) and boost headers for zip_longest
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        ninja-build \
        libboost-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and install the header-only library
WORKDIR /fuzz/src
RUN cmake -S . -B build \
      -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
  && cmake --build build --target install
