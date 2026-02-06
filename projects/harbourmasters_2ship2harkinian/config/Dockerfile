ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools and create a dummy static library
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    binutils \
    && rm -rf /var/lib/apt/lists/*

# Environment: required compilers and install prefix
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# Prepare install directories and a minimal static library artifact
RUN mkdir -p ${PREFIX}/lib \
 && printf "void __2s2h_dummy(void){}" > /tmp/dummy.c \
 && ${CC} -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs ${PREFIX}/lib/lib2ship.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o

# No further build/install steps required
