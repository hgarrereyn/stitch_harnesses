ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal setup: install headers and provide a stub static library for linking
WORKDIR /fuzz/src

# Create install prefix and copy headers
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    cp -r include/xrpl /fuzz/install/include/

# Create an empty static library archive to satisfy linker (-lxrpl)
RUN ${CC:-stitch_libafl_cc} -xc -c -o /tmp/empty.o /dev/null && \
    ar rcs /fuzz/install/lib/libxrpl.a /tmp/empty.o && \
    rm -f /tmp/empty.o
