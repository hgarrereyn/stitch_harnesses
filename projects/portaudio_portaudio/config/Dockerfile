ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for build and Linux host APIs (ALSA, JACK, PulseAudio)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libasound2-dev \
    libjack-jackd2-dev \
    libpulse-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure, build static library, and install to /fuzz/install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Use an out-of-tree build
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DPA_BUILD_SHARED_LIBS=OFF \
    -DPA_BUILD_TESTS=OFF \
    -DPA_BUILD_EXAMPLES=OFF \
    -DPA_USE_ALSA=ON \
    -DPA_USE_PULSEAUDIO=ON \
    -DPA_USE_JACK=ON
RUN cmake --build build --config Release --target install
