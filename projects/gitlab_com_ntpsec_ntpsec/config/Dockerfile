ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    python3 \
    python-is-python3 \
    pkg-config \
    libssl-dev \
    libbsd-dev \
    bison \
    m4 \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Use required compilers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Configure and build with waf (minimal features)
RUN ./waf configure --prefix=/fuzz/install --disable-nts --enable-pylib=none \
 && ./waf build -j"$(nproc)"

# Install minimal artifacts for linking: headers and libntp.a and config.h
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r include/* /fuzz/install/include/ \
 && cp build/config.h /fuzz/install/include/ \
 && LIB_PATH=$(find build -name "libntp.a" | head -n1) \
 && cp "$LIB_PATH" /fuzz/install/lib/
