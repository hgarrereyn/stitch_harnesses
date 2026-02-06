ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    libfftw3-dev \
    libmbedtls-dev \
    libsctp-dev \
    libboost-program-options-dev \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure and build only the libraries, install to /fuzz/install
WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DBUILD_STATIC=ON \
    -DENABLE_SRSUE=OFF \
    -DENABLE_SRSENB=OFF \
    -DENABLE_SRSEPC=OFF \
    -DENABLE_GUI=OFF \
    -DENABLE_RF_PLUGINS=OFF \
    -DENABLE_ZEROMQ=OFF \
    -DENABLE_SOAPYSDR=OFF \
    -DENABLE_UHD=OFF \
    -DENABLE_BLADERF=OFF \
    -DENABLE_WERROR=OFF

RUN cmake --build /fuzz/build --target install -j$(nproc)

# Ensure static libraries are available under /fuzz/install/lib (best-effort)
RUN mkdir -p /fuzz/install/lib \
 && find /fuzz/build -name "lib*.a" -exec cp -n {} /fuzz/install/lib/ \;
