ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies: protobuf, abseil, build essentials, git for fetching boringssl headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    ca-certificates \
    git \
    pkg-config \
    libprotobuf-dev \
    protobuf-compiler \
    libabsl-dev \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Fetch BoringSSL headers only (no need to build libraries for header parsing)
WORKDIR /tmp
RUN git clone --depth=1 https://github.com/google/boringssl.git && \
    mkdir -p /fuzz/install/include && \
    cp -r boringssl/include/* /fuzz/install/include/

# Build jwt_verify_lib as a static library and install headers
WORKDIR /fuzz/src
RUN mkdir -p /fuzz/install/include/jwt_verify_lib /fuzz/install/lib && \
    for f in src/*.cc; do \
      gf_libafl_cxx -I/fuzz/src -I/fuzz/src/jwt_verify_lib -I/fuzz/install/include -fPIC -c "$f" -o "/tmp/$(basename "$f").o" ; \
    done && \
    ar rcs /fuzz/install/lib/libjwt_verify.a /tmp/*.o && \
    cp -r /fuzz/src/jwt_verify_lib/*.h /fuzz/install/include/jwt_verify_lib/
