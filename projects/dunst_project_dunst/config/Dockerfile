ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies (X11 + GLib stack) and helpers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    perl \
    libglib2.0-dev \
    libgdk-pixbuf-2.0-dev \
    libpango1.0-dev \
    libcairo2-dev \
    libx11-dev \
    libxinerama-dev \
    libxext-dev \
    libxrandr-dev \
    libxss-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Build with the fuzzing compilers, disable optional components we don't need
# (wayland, dunstify, systemd units, completions) to keep deps minimal
RUN make -j"$(nproc)" \
    CC=stitch_libafl_cc \
    WAYLAND=0 \
    DUNSTIFY=0 \
    SYSTEMD=0 \
    COMPLETIONS=0 \
    PREFIX=${PREFIX}

# Install binaries and manpages (not used by fuzzing but harmless)
RUN make install \
    CC=stitch_libafl_cc \
    WAYLAND=0 \
    DUNSTIFY=0 \
    SYSTEMD=0 \
    COMPLETIONS=0 \
    PREFIX=${PREFIX}

# Create a static archive from built objects and install headers for development
RUN mkdir -p ${PREFIX}/lib ${PREFIX}/include/dunst && \
    find src -name '*.o' -print0 | xargs -0 ar rcs ${PREFIX}/lib/libdunst.a && \
    cp -a src/*.h ${PREFIX}/include/dunst/ && \
    mkdir -p ${PREFIX}/include/dunst/x11 && \
    cp -a src/x11/*.h ${PREFIX}/include/dunst/x11/ || true
