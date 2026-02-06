ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    autoconf automake libtool pkg-config \
    make \
    libssl-dev zlib1g-dev libseccomp-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

ENV PREFIX=/fuzz/install
WORKDIR /fuzz/src

# Prepare, configure and build only the static libraries; then install headers/libs manually
RUN autoreconf -f -i && \
    CC=stitch_libafl_cc CXX=stitch_libafl_cxx \
    ./configure --prefix=${PREFIX} && \
    make -j"$(nproc)" libssh.a && \
    make -j"$(nproc)" -C openbsd-compat libopenbsd-compat.a && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include/openbsd-compat && \
    cp -a libssh.a ${PREFIX}/lib/ && \
    cp -a openbsd-compat/libopenbsd-compat.a ${PREFIX}/lib/ && \
    # Build a small extra archive for pkcs11 and security key stubs used by libssh
    stitch_libafl_cc -I. -Iopenbsd-compat -c ssh-pkcs11.c -o ssh-pkcs11.o && \
    stitch_libafl_cc -I. -Iopenbsd-compat -c ssh-sk.c -o ssh-sk.o && \
    ar rcs ${PREFIX}/lib/libssh_extra.a ssh-pkcs11.o ssh-sk.o && \
    # Install headers (API + dependencies)
    cp -a ./*.h ${PREFIX}/include/ && \
    cp -a openbsd-compat/*.h ${PREFIX}/include/openbsd-compat/
