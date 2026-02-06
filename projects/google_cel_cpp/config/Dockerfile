ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies (Abseil headers for public API includes)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    libabsl-dev \
 && rm -rf /var/lib/apt/lists/*

# Prepare install prefix
ENV PREFIX=/fuzz/install
RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib

# Install headers (public API subset under base/)
# Copy the base headers which contain lightweight public enums/APIs.
RUN cp -r /fuzz/src/base ${PREFIX}/include/base

# Build a minimal static library to link against (dummy, for linking stage)
# Use the required compilers (clang-17 wrappers)
RUN echo "void cel_dummy_library_symbol(){}" > /tmp/dummy.c && \
    stitch_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o && \
    ar rcs ${PREFIX}/lib/libcel.a /tmp/dummy.o && \
    rm -f /tmp/dummy.c /tmp/dummy.o

ENV CPATH=${PREFIX}/include
ENV LIBRARY_PATH=${PREFIX}/lib
ENV LD_LIBRARY_PATH=${PREFIX}/lib