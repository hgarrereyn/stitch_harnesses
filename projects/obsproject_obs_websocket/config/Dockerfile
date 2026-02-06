ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install only what we need to compile against the API header: libobs-dev
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
      libobs-dev \
    && rm -rf /var/lib/apt/lists/*

# Prepare install prefix and install the public API header
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include

# Copy the public API header into the install include directory
# The source is already available in /fuzz/src at build time
RUN cp /fuzz/src/lib/obs-websocket-api.h ${PREFIX}/include/

# No build needed for header-only API. Ensure compilers are set for any potential builds.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
