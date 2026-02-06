ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed to build the project with scons and compilers
RUN apt-get update && apt-get install -y --no-install-recommends \
    scons \
    python3 \
    pkg-config \
    clang-17 \
 && rm -rf /var/lib/apt/lists/*

# Provide expected compiler wrapper names as symlinks to clang-17
RUN ln -sf /usr/bin/clang-17 /usr/local/bin/gf_libafl_cc && \
    ln -sf /usr/bin/clang++-17 /usr/local/bin/gf_libafl_cxx

WORKDIR /fuzz/src

# Build and install using scons
RUN scons \
    CXX=gf_libafl_cxx \
    optimize=1 \
    DESTDIR=/fuzz/install \
    prefix=/ \
    install && \
    mkdir -p /fuzz/install/include/double-conversion && \
    cp -a double-conversion/*.h /fuzz/install/include/double-conversion/
