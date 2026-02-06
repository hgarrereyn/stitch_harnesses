ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies for building libdispatch on Linux
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3-pip \
    ninja-build \
    pkg-config \
    libbsd-dev \
    systemtap-sdt-dev \
    linux-libc-dev \
    ca-certificates \
  && rm -rf /var/lib/apt/lists/* \
  && pip3 install --no-cache-dir cmake==3.27.9

# Configure, build, and install libdispatch statically
WORKDIR /fuzz/src

# Use Ninja and install to /fuzz/install, build static libs only
RUN cmake -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_INSTALL_LIBDIR=lib \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_SWIFT=OFF \
    . \
 && ninja -v \
 && ninja install
