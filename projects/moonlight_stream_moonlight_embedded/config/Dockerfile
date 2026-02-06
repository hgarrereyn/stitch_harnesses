ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git ca-certificates pkg-config ninja-build cmake \
    libavahi-client-dev uuid-dev libcurl4-openssl-dev libssl-dev libexpat1-dev \
    libopus-dev libevdev-dev libudev-dev libasound2-dev \
    libsdl2-dev libavcodec-dev libavutil-dev libegl1-mesa-dev libgles2-mesa-dev libx11-dev \
    && rm -rf /var/lib/apt/lists/*

# Prepare source and fetch submodules
WORKDIR /fuzz/src
RUN git submodule update --init --recursive

# Configure, build, and install the whole project
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_MODULE_PATH=/fuzz/src/cmake \
    -DENABLE_FFMPEG=ON -DENABLE_SDL=ON -DENABLE_X11=ON \
    && cmake --build build -j \
    && cmake --install build

# Install public headers for consumers (library doesn't install headers by default)
RUN mkdir -p /fuzz/install/include && \
    cp -v libgamestream/*.h /fuzz/install/include/ && \
    if [ -d third_party/moonlight-common-c/src ]; then cp -v third_party/moonlight-common-c/src/*.h /fuzz/install/include/ || true; fi
