ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools to create a static archive
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Create install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include/Common/json \
    && mkdir -p ${PREFIX}/include/Common/CppCodec \
    && mkdir -p ${PREFIX}/lib

# Copy header-only libraries that are platform-independent from the mounted source tree
RUN cp -r /fuzz/src/Src/Common/json ${PREFIX}/include/Common/ \
    && cp -r /fuzz/src/Src/Common/CppCodec ${PREFIX}/include/Common/

# Build a tiny static library to satisfy linking (-lc3)
RUN echo "void c3_dummy(){}" > /tmp/dummy.c \
    && stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o \
    && ar rcs ${PREFIX}/lib/libc3.a /tmp/dummy.o \
    && rm -f /tmp/dummy.c /tmp/dummy.o
