ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libglib2.0-dev \
    libfreetype6-dev \
    libxml2-dev \
    zlib1g-dev \
    gettext \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Configure and build static libfontforge without GUI or optional features
WORKDIR /fuzz/build
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_GUI=OFF \
    -DENABLE_DOCS=OFF \
    -DENABLE_PYTHON_SCRIPTING=OFF \
    -DENABLE_PYTHON_EXTENSION=OFF \
    -DENABLE_LIBSPIRO=OFF \
    -DENABLE_LIBGIF=OFF \
    -DENABLE_LIBJPEG=OFF \
    -DENABLE_LIBPNG=OFF \
    -DENABLE_LIBREADLINE=OFF \
    -DENABLE_LIBTIFF=OFF \
    -DENABLE_WOFF2=OFF \
    -DENABLE_HARFBUZZ=OFF \
    /fuzz/src && \
    ninja -v

# Manual install: library and headers (static build doesn't install by default)
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include /fuzz/install/include/fontforge; \
    cp /fuzz/build/lib/libfontforge.a /fuzz/install/lib/; \
    # Common headers (including generated ones)
    cp -a /fuzz/src/inc/*.h /fuzz/install/include/; \
    if [ -f /fuzz/build/inc/fontforge-config.h ]; then cp /fuzz/build/inc/fontforge-config.h /fuzz/install/include/; fi; \
    if [ -f /fuzz/build/inc/fontforge-version-extras.h ]; then cp /fuzz/build/inc/fontforge-version-extras.h /fuzz/install/include/; fi; \
    # FontForge public headers
    cp -a /fuzz/src/fontforge/*.h /fuzz/install/include/fontforge/; \
    if [ -f /fuzz/src/fontforge/std_maps.hpp ]; then cp /fuzz/src/fontforge/std_maps.hpp /fuzz/install/include/fontforge/; fi; \
    # Also install C++ tag header
    if [ -f /fuzz/src/inc/tag.hpp ]; then cp /fuzz/src/inc/tag.hpp /fuzz/install/include/; fi
