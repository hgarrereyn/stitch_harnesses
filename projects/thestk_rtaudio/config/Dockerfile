ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        cmake \
        make \
        ninja-build \
        pkg-config \
        libasound2-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, and install RtAudio as a static library with ALSA only
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DBUILD_SHARED_LIBS=OFF \
    -DRTAUDIO_API_ALSA=ON \
    -DRTAUDIO_API_PULSE=OFF \
    -DRTAUDIO_API_JACK=OFF \
    -DRTAUDIO_API_OSS=OFF \
    -DRTAUDIO_API_WASAPI=OFF \
    -DRTAUDIO_API_DS=OFF \
    -DRTAUDIO_API_ASIO=OFF \
    -DRTAUDIO_BUILD_TESTING=OFF \
 && cmake --build /fuzz/build -j \
 && cmake --install /fuzz/build
