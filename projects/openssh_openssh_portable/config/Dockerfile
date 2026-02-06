ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config make \
    libssl-dev zlib1g-dev libedit-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and install prefix
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# Generate configure (if building from git), configure, build and install
RUN autoreconf -fi || true && \
    ./configure --prefix=${PREFIX} && \
    make -j"$(nproc)" && \
    make install && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/openbsd-compat && \
    cp -a libssh.a ${PREFIX}/lib/ && \
    cp -a openbsd-compat/libopenbsd-compat.a ${PREFIX}/lib/ && \
    cp -a ssh-pkcs11.o ssh-sk.o ${PREFIX}/lib/ || true && \
    cp -a *.h ${PREFIX}/include/ && \
    cp -a openbsd-compat/*.h ${PREFIX}/include/openbsd-compat/
