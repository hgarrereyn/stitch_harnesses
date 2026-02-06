ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed
RUN apt-get update && apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

# Environment
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# Install headers and create a tiny static library to link against
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib \
 && cp -r /fuzz/src/WinDiskWriter/libs/wimlib/include/*.h ${PREFIX}/include/ \
 # Build a dummy archive providing no symbols (sufficient for link when unused)
 && echo "void __wimlib_dummy(void){}" > /tmp/dummy.c \
 && ${CC} -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs ${PREFIX}/lib/libwim.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o
