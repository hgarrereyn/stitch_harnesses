ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools required for configuration
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

# Configure and install NumCpp (header-only). Avoid Boost to keep image small.
WORKDIR /fuzz/src
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DNUMCPP_NO_USE_BOOST=ON \
    -DBUILD_DOCS=OFF -DBUILD_TESTS=OFF -DBUILD_EXAMPLE_ALL=OFF
RUN cmake --build build --target install
