ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      cmake \
      ninja-build \
      make \
      libimath-dev \
      pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Provide lightweight shim headers to map legacy Imath includes to v3 layout
RUN mkdir -p /fuzz/shim/imath_compat && \
    printf "#pragma once\n#include <Imath/ImathBox.h>\n" > /fuzz/shim/imath_compat/ImathBox.h && \
    printf "#pragma once\n#include <Imath/ImathVec.h>\n" > /fuzz/shim/imath_compat/ImathVec.h && \
    printf "#pragma once\n#include <Imath/ImathMatrix.h>\n" > /fuzz/shim/imath_compat/ImathMatrix.h && \
    printf "#pragma once\n#include <Imath/ImathColor.h>\n" > /fuzz/shim/imath_compat/ImathColor.h && \
    printf "#pragma once\n#include <Imath/ImathMath.h>\n" > /fuzz/shim/imath_compat/ImathMath.h && \
    printf "#pragma once\n#include <Imath/half.h>\n" > /fuzz/shim/imath_compat/half.h && \
    printf "#pragma once\n#include <Imath/ImathConfig.h>\n" > /fuzz/shim/imath_compat/ImathConfig.h

# Configure and build OpenEXR statically
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_SHARED_LIBS=OFF \
    -DOPENEXR_BUILD_TOOLS=OFF \
    -DOPENEXR_INSTALL_TOOLS=OFF \
    -DOPENEXR_BUILD_EXAMPLES=OFF \
    -DOPENEXR_BUILD_PYTHON=OFF \
    -DOPENEXR_TEST_LIBRARIES=OFF \
    -DOPENEXR_TEST_TOOLS=OFF \
    -DOPENEXR_INSTALL_DOCS=OFF
RUN cmake --build /fuzz/build --target install --parallel
