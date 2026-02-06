ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for generating configure and building the project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    flex bison \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Generate the configure script (repo build from git)
RUN ./build.sh

# Configure with fuzzing compilers and minimal plugins; install to /fuzz/install
RUN CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=/fuzz/install --disable-all-plugins

# Build and install
RUN make -j"$(nproc)" && make install
