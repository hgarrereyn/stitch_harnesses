ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    pkg-config \
    libxerces-c-dev \
    zlib1g-dev \
    libproj-dev \
    libeigen3-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build only the libraries we need
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S . -B build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DISOLATED_BUILD=ON \
    -DCHECK_OPTIONAL_LIBS=OFF \
    -DENABLE_PYTHON_BINDINGS=OFF \
    -DENABLE_JAVA_BINDINGS=OFF \
    -DENABLE_CS_BINDINGS=OFF \
    -DFMI=OFF \
    -DNETEDIT=OFF

# Build shared libsumo C++ library (pulls in required static utils libs)
RUN cmake --build build -j$(nproc) --target libsumocpp

# Manually install just the shared library to keep image small
RUN bash -lc 'set -eux; mkdir -p /fuzz/install/lib; f=$(find build -type f -name "*sumocpp*.so*" | head -n1); cp -v "$f" /fuzz/install/lib/'
