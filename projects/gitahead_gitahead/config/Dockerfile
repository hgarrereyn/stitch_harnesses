ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed for building and linking against libgit2
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      pkg-config \
      libgit2-dev \
    && rm -rf /var/lib/apt/lists/*

# Create install prefix (no project build required; using system libgit2)
RUN mkdir -p /fuzz/install/include /fuzz/install/lib

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx
