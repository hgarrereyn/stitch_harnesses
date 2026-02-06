ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git ca-certificates pkg-config meson ninja-build \
    libwayland-dev libxkbcommon-dev libpixman-1-dev libjansson-dev \
    libdrm-dev libgbm-dev libpam0g-dev libgnutls28-dev \
    libturbojpeg0-dev libavfilter-dev libavcodec-dev libavutil-dev \
    && rm -rf /var/lib/apt/lists/*

# Prepare subprojects for neatvnc and aml
WORKDIR /fuzz/src
RUN mkdir -p subprojects && \
    git clone --depth=1 https://github.com/any1/neatvnc.git /tmp/neatvnc && \
    git clone --depth=1 https://github.com/any1/aml.git /tmp/aml && \
    ln -s /tmp/neatvnc subprojects/neatvnc && \
    mkdir -p /tmp/neatvnc/subprojects && \
    ln -s /tmp/aml /tmp/neatvnc/subprojects/aml

# Configure, build, and install
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN meson setup build \
    --prefix=/fuzz/install \
    -Dman-pages=disabled \
    -Dtests=false \
    && ninja -C build -j$(nproc) && ninja -C build install

# Install headers for downstream use
RUN mkdir -p /fuzz/install/include && \
    cp -r include/* /fuzz/install/include/ && \
    if compgen -G "build/*.h" > /dev/null; then cp build/*.h /fuzz/install/include/; fi && \
    if compgen -G "build/protocols/*.h" > /dev/null; then cp build/protocols/*.h /fuzz/install/include/; fi && \
    if [ -f build/config.h ]; then cp build/config.h /fuzz/install/include/; fi
