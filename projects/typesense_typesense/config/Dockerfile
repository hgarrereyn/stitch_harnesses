ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install needed build tools and ICU headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    libicu-dev \
 && rm -rf /var/lib/apt/lists/*

# Create install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Install headers
COPY . /fuzz/src
RUN cp -r /fuzz/src/include/* ${PREFIX}/include/

# Build a minimal static library to link against
RUN echo "void __ts_dummy(void){}" > /tmp/dummy.c \
 && stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs ${PREFIX}/lib/libtypesense.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o
