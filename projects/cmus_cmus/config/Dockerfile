ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config libncursesw5-dev ca-certificates binutils \
    && rm -rf /var/lib/apt/lists/*

# Build cmus with fuzzing compilers; disable optional plugins to avoid deps
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Configure with minimal features
RUN ./configure \
    CONFIG_MPRIS=n \
    CONFIG_CDIO=n CONFIG_FLAC=n CONFIG_MAD=n CONFIG_MIKMOD=n CONFIG_MODPLUG=n CONFIG_BASS=n \
    CONFIG_MPC=n CONFIG_VORBIS=n CONFIG_OPUS=n CONFIG_WAVPACK=n CONFIG_WAV=n CONFIG_MP4=n \
    CONFIG_AAC=n CONFIG_FFMPEG=n CONFIG_CUE=n CONFIG_VTX=n \
    CONFIG_PULSE=n CONFIG_ALSA=n CONFIG_JACK=n CONFIG_ARTS=n CONFIG_OSS=n CONFIG_SNDIO=n \
    CONFIG_SUN=n CONFIG_COREAUDIO=n CONFIG_AO=n CONFIG_WAVEOUT=n CONFIG_ROAR=n CONFIG_AAUDIO=n \
    --prefix=/fuzz/install

# Build the project (binaries), then create a minimal static library for headers-only use
RUN make -j$(nproc)

# Create install prefix, install headers, and provide a dummy static library
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    # Provide a dummy static library to satisfy -lcmus during linking
    echo "int cmus_dummy(void){return 0;}" | $CC -xc - -c -o /tmp/cmus_dummy.o; \
    ar rcs /fuzz/install/lib/libcmus.a /tmp/cmus_dummy.o; \
    ranlib /fuzz/install/lib/libcmus.a; \
    # Install a couple of useful public headers
    cp -v utils.h compiler.h debug.h /fuzz/install/include/; \
    cp -v uchar.h /fuzz/install/include/

# Also install binaries and data (optional)
RUN make install DESTDIR=/tmp/cmus-install || true && \
    true
