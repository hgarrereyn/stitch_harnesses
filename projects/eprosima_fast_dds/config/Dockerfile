ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    build-essential \
    libfoonathan-memory-dev \
    libtinyxml2-dev \
    libssl-dev \
    libsqlite3-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure and build Fast-DDS
WORKDIR /fuzz/src

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DSECURITY=OFF \
    -DNO_TLS=ON \
    -DSQLITE3_SUPPORT=OFF \
    -DCOMPILE_EXAMPLES=OFF \
    -DCOMPILE_TOOLS=OFF \
    -DTHIRDPARTY_fastcdr=FORCE \
    -DTHIRDPARTY_Asio=FORCE \
    -DTHIRDPARTY_UPDATE=OFF

RUN cmake --build build --target install -- -v
