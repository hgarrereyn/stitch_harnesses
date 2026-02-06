ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and OpenGL dev libraries
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    git \
    python3 \
    python-is-python3 \
    perl \
    pkg-config \
    libgl1-mesa-dev \
    libx11-dev \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate headers and sources, build and install library and headers
# Use stitch_libafl_cc/stitch_libafl_cxx as compilers
ENV PREFIX=/fuzz/install

# Generate the headers/sources first (avoids building utils and extra deps)
RUN make -C auto

# Build only the library (shared+static as per upstream makefile) and install
RUN make glew.lib SYSTEM=linux-clang CC=stitch_libafl_cc CXX=stitch_libafl_cxx LD=stitch_libafl_cc GLEW_DEST=${PREFIX} && \
    make install.lib install.include install.pkgconfig SYSTEM=linux-clang CC=stitch_libafl_cc CXX=stitch_libafl_cxx LD=stitch_libafl_cc GLEW_DEST=${PREFIX}
