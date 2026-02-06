ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    pkg-config \
    libboost-dev \
    cmake \
    ninja-build \
  && rm -rf /var/lib/apt/lists/*

# Configure and build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DBUILD_STATIC_LIBS=ON \
    -DBUILD_SERVER=ON \
    -DBUILD_CLIENT=OFF \
    -DBUILD_WITH_SSL=OFF \
    -DBUILD_WITH_ALSA=OFF \
    -DBUILD_WITH_FLAC=OFF \
    -DBUILD_WITH_VORBIS=OFF \
    -DBUILD_WITH_OPUS=OFF \
    -DBUILD_WITH_AVAHI=OFF \
    -DBUILD_WITH_EXPAT=OFF \
    -DBUILD_WITH_PULSE=OFF \
    -DBUILD_WITH_JACK=OFF \
    -DBUILD_WITH_PIPEWIRE=OFF \
    -DBUILD_WITH_SDL2=OFF

RUN cmake --build /fuzz/build --verbose

# Install artifacts manually: libcommon.a and public headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/snapcast && \
    cp -v /fuzz/src/bin/libcommon.a /fuzz/install/lib/ && \
    cp -rv /fuzz/src/common /fuzz/install/include/snapcast/
