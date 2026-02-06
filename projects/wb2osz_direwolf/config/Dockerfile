ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build && rm -rf /var/lib/apt/lists/*

# Build only the geotranz static library from the project
WORKDIR /fuzz
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN cmake -S /fuzz/src/external/geotranz -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build -j

# Manually install static libs and headers needed for linking
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    if [ -f /fuzz/build/libgeotranz.a ]; then \
      cp /fuzz/build/libgeotranz.a /fuzz/install/lib/; \
    elif [ -f /fuzz/build/external/geotranz/libgeotranz.a ]; then \
      cp /fuzz/build/external/geotranz/libgeotranz.a /fuzz/install/lib/; \
    fi; \
    cp /fuzz/src/external/geotranz/*.h /fuzz/install/include/
