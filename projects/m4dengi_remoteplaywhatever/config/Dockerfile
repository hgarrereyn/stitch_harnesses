ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        make \
        ninja-build \
        pkg-config \
        libwxgtk3.0-gtk3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
# Build OpenSteamAPI static library (the CMake PRE_BUILD only works on MSVC)
RUN make -C open-steamworks/OpenSteamAPI/src

# Configure, build, install
RUN cmake -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release
RUN cmake --build build --target install