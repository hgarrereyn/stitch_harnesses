ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    binutils \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Build only what we need for the public API and create a static library
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build required objects into /fuzz/build using the project's Makefile rules
RUN make -j"$(nproc)" \
      BUILDDIR=/fuzz/build \
      CXX=gf_libafl_cxx CC=gf_libafl_cc \
      /fuzz/build/.objs/mergerfs_api.cpp.o \
      /fuzz/build/.objs/fs_xattr.cpp.o \
      /fuzz/build/.objs/str.cpp.o

# Install headers and create static library
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -v src/mergerfs_api.hpp src/fs_path.hpp /fuzz/install/include/ \
 && ar rcs /fuzz/install/lib/libmergerfs_api.a \
      /fuzz/build/.objs/mergerfs_api.cpp.o \
      /fuzz/build/.objs/fs_xattr.cpp.o \
      /fuzz/build/.objs/str.cpp.o
