ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake \
    make \
    pkg-config \
    libssl-dev \
    libplist-dev \
    libavahi-compat-libdnssd-dev \
    libgstreamer1.0-dev \
    libgstreamer-plugins-base1.0-dev \
    && rm -rf /var/lib/apt/lists/*

# Configure, build, install
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S . -B build -DNO_MARCH_NATIVE=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    && cmake --build build -j

# Install executable (provided by cmake) and also copy static libraries and headers for linking
RUN cmake --install build \
    && mkdir -p /fuzz/install/lib /fuzz/install/include \
    && cp build/lib/libairplay.a /fuzz/install/lib/ \
    && cp -n build/renderers/librenderers.a /fuzz/install/lib/ || true \
    && cp lib/*.h /fuzz/install/include/ \
    && cp renderers/*.h /fuzz/install/include/ || true
