ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    perl pkg-config libicu-dev ca-certificates cmake ninja-build && \
    rm -rf /var/lib/apt/lists/*

# Configure, build and install libical (static only)
WORKDIR /fuzz/src

# Configure with CMake
RUN cmake -S . -B build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DSTATIC_ONLY=True \
    -DLIBICAL_CXX_BINDINGS=False \
    -DLIBICAL_GLIB=False \
    -DLIBICAL_GOBJECT_INTROSPECTION=False \
    -DLIBICAL_GLIB_BUILD_DOCS=False \
    -DLIBICAL_GLIB_VAPI=False \
    -DLIBICAL_BUILD_DOCS=False \
    -DLIBICAL_JAVA_BINDINGS=False \
    -DCMAKE_DISABLE_FIND_PACKAGE_BDB=True

# Build and install
RUN cmake --build build --target install -j$(nproc)
