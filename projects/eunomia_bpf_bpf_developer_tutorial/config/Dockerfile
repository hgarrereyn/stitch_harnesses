ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools if needed
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Environment
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

# "Build" and install a minimal static library interface from the tutorial
# We package a tiny static library and install a public header from the repo
RUN mkdir -p ${INSTALL_PREFIX}/include ${INSTALL_PREFIX}/lib && \
    cp /fuzz/src/src/11-bootstrap/bootstrap.h ${INSTALL_PREFIX}/include/ && \
    echo "int bpfdt_dummy(void){return 0;}" > /tmp/dummy.c && \
    ${CC} -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs ${INSTALL_PREFIX}/lib/libbpfdevtutorial.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o

# Display installed files (debug)
RUN ls -R ${INSTALL_PREFIX}
