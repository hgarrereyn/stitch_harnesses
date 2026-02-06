ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal dependencies to build aubio with waf
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3 \
    python-is-python3 \
    ca-certificates \
    pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Build and install aubio (static library preferred)
WORKDIR /fuzz/src
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Fetch waf, configure without external deps, build static only, install to /fuzz/install
RUN ./scripts/get_waf.sh \
 && python3 waf configure --prefix=/fuzz/install --disable-examples --disable-tests --nodeps \
 && LDFLAGS=--static python3 waf build \
 && python3 waf install
