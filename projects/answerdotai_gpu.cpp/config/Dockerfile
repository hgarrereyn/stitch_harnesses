ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies and set compilers
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 ca-certificates \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src

# Fetch the prebuilt Dawn library (downloads headers and lib into third_party)
RUN python3 setup.py

# Install headers and library to /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp gpu.hpp /fuzz/install/include/ && \
    cp -r numeric_types utils /fuzz/install/include/ && \
    cp -r third_party/headers/* /fuzz/install/include/ && \
    if [ -f third_party/lib/libwebgpu_dawn.so ]; then \
      cp third_party/lib/libwebgpu_dawn.so /fuzz/install/lib/; \
    elif [ -f third_party/lib/libwebgpu_dawn.dylib ]; then \
      cp third_party/lib/libwebgpu_dawn.dylib /fuzz/install/lib/; \
    fi
