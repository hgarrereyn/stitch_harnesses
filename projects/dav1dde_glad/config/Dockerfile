ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: Python for the generator
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
 && rm -rf /var/lib/apt/lists/*

# Generate a header-only glad for OpenGL core 3.3 and install headers
# Use the in-tree glad module
RUN python3 -m glad \
    --out-path /tmp/glad-out \
    --api gl:core=3.3 \
    c \
    --header-only

# Install headers to /fuzz/install
RUN mkdir -p /fuzz/install/include && \
    cp -r /tmp/glad-out/include/* /fuzz/install/include/

# Environment
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
