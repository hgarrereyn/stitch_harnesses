ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      meson pkg-config python3 \
      libsdl2-dev libavformat-dev libavcodec-dev libavutil-dev libswresample-dev libavdevice-dev \
      libusb-1.0-0-dev && \
    rm -rf /var/lib/apt/lists/*

# Configure environment compilers for fuzzing wrappers
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build and install scrcpy (client only)
WORKDIR /fuzz/src
RUN meson setup build \
      -Dcompile_server=false \
      -Dprefix=/fuzz/install && \
    meson compile -C build && \
    meson install -C build

# Install headers for external consumers (copy source headers layout) and generated config.h
RUN mkdir -p /fuzz/install/include/scrcpy && \
    cp -r app/src/* /fuzz/install/include/scrcpy/ && \
    cp build/app/config.h /fuzz/install/include/scrcpy/
