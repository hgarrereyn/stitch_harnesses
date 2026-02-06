ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install CPython as a static library with embedding support
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libssl-dev zlib1g-dev libbz2-dev libreadline-dev libsqlite3-dev \
    libffi-dev libncursesw5-dev libgdbm-dev libnsl-dev uuid-dev libexpat1-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and install prefix. Build static libpython only.
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure --prefix=/fuzz/install --disable-shared --without-ensurepip
RUN make -j"$(nproc)"
RUN make install

# Ensure libraries are discoverable at link time
ENV LIBRARY_PATH=/fuzz/install/lib:$LIBRARY_PATH
ENV CPATH=/fuzz/install/include:$CPATH
