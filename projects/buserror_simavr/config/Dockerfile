ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies for simavr
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    make pkg-config libelf-dev libdwarf-dev gcc-avr binutils-avr avr-libc \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV CFLAGS=-Wno-error\ -fPIC
ENV EXTRA_LDFLAGS=-Wl,-z,notext

# Build and install only the simavr library and headers
RUN make -C /fuzz/src/simavr RELEASE=1 CC=${CC} CFLAGS="${CFLAGS}" EXTRA_LDFLAGS="${EXTRA_LDFLAGS}" -j"$(nproc)" \
 && make -C /fuzz/src/simavr RELEASE=1 CC=${CC} CFLAGS="${CFLAGS}" EXTRA_LDFLAGS="${EXTRA_LDFLAGS}" DESTDIR=/fuzz/install PREFIX=/fuzz/install install
