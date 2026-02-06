ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install system msgpack and copy headers/libs into /fuzz/install since the source tree is empty here
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libmsgpack-dev \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix and copy headers and libraries
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /fuzz/install/share \
 && cp -a /usr/include/msgpack* /fuzz/install/include/ || true \
 && cp -a /usr/lib/x86_64-linux-gnu/libmsgpackc.* /fuzz/install/lib/ || true

# No build is required because the C++ API is header-only and C lib is provided by the system package
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
