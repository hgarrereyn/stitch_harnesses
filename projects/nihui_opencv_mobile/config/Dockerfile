ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install OpenCV development package and copy headers/libs into /fuzz/install
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libopencv-dev pkg-config && \
    rm -rf /var/lib/apt/lists/*

# Prepare install prefix and copy system-installed OpenCV into it
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -a /usr/include/opencv4 /fuzz/install/include/ && \
    cp -a /usr/lib/*/libopencv*.so* /fuzz/install/lib/ || true && \
    cp -a /usr/lib/*/libopencv*.a /fuzz/install/lib/ || true

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src
