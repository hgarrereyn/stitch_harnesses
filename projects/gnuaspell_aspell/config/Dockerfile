ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for autoconf/automake/libtool based project
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool gettext autopoint texinfo perl pkg-config \
    ca-certificates file \
 && rm -rf /var/lib/apt/lists/*

# Build and install aspell statically to /fuzz/install
WORKDIR /fuzz/src

# Generate configure scripts
RUN ./autogen || ./autogen.sh

# Configure with fuzzing compilers and static libs only
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN ./configure \
    --prefix=/fuzz/install \
    --disable-shared \
    --enable-static \
    --disable-curses \
    --disable-wide-curses

# Build and install
RUN make -j"$(nproc)" && make install
