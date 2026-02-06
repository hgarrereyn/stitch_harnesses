ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (for ar) and any deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

# Use the required compilers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build a minimal static library from the Unix receiver sources (no external deps)
# and install headers and the archive into /fuzz/install
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cd /fuzz/src/Receivers/unix && \
    ${CC} -O2 -c network.c -o /tmp/network.o && \
    ${CC} -O2 -c shmem.c -o /tmp/shmem.o && \
    ${CC} -O2 -c raw.c -o /tmp/raw.o && \
    ar rcs /fuzz/install/lib/libscreamrecv.a /tmp/network.o /tmp/shmem.o /tmp/raw.o && \
    cp scream.h network.h shmem.h raw.h /fuzz/install/include/
