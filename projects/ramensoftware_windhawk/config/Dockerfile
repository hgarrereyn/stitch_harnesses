ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# The project is Windows-specific and not buildable on Linux. To enable fuzzing of
# any available C/C++ surface, we expose a minimal header-only API (version.h)
# and provide a tiny static library for linking.

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# Install headers and create a minimal static library archive.
RUN mkdir -p ${PREFIX}/include/windhawk ${PREFIX}/lib \
 && install -m 0644 /fuzz/src/src/windhawk/shared/version.h ${PREFIX}/include/windhawk/version.h

# Create a tiny dummy object and archive so linking works
RUN echo 'void windhawk_dummy(){}' > /tmp/dummy.c \
 && ${CC} -c /tmp/dummy.c -o /tmp/dummy.o \
 && ar rcs ${PREFIX}/lib/libwindhawk.a /tmp/dummy.o \
 && rm -f /tmp/dummy.c /tmp/dummy.o
