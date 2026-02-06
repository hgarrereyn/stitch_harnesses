ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and library dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    git \
    autoconf \
    automake \
    libtool \
    pkg-config \
    libc++-17-dev \
    libc++abi-17-dev \
 && rm -rf /var/lib/apt/lists/*

# Build and install a modern Asio (header-only)
RUN git clone https://github.com/chriskohlhoff/asio --branch asio-1-34-2 --single-branch /tmp/asio \
 && cd /tmp/asio/asio \
 && ./autogen.sh \
 && ./configure \
 && make install \
 && rm -rf /tmp/asio

# Configure, build, and install restbed
WORKDIR /fuzz/src

# Configure with static library only, no SSL, no tests, install to /fuzz/install
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_CXX_FLAGS="-stdlib=libc++" \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_TESTS=OFF \
    -DBUILD_SSL=OFF \
    -DBUILD_SHARED_LIBRARY=OFF \
    -DBUILD_STATIC_LIBRARY=ON \
    -DCMAKE_INSTALL_LIBDIR=library

RUN cmake --build build -j
RUN cmake --install build
