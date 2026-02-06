ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install any extra dependencies (none required beyond build essentials already present)
# But ensure standard utilities and minimal deps are available
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build and install SQLite as a static library
WORKDIR /fuzz/src

# Configure with required compilers and install prefix. Disable shared libs, enable static.
# Use minimal options to avoid tcl and extras.
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
 && make -j$(nproc) \
 && make install
