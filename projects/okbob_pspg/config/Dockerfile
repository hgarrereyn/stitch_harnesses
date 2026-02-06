ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libncurses-dev libreadline-dev pkg-config make && \
    rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

WORKDIR /fuzz/src

# Configure, build, and install
RUN ./configure --prefix=/fuzz/install && \
    make -j$(nproc) && \
    make install

# Create a static archive from built objects and install headers for external linking
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/pspg && \
    ar rcs /fuzz/install/lib/libpspg.a *.o || true && \
    cp -a src/*.h /fuzz/install/include/pspg/ || true && \
    cp -a config.h /fuzz/install/include/pspg/ || true
