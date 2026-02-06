ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Use fuzzing compiler wrappers
ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Create install prefix and install header-only public API we will target
RUN mkdir -p /fuzz/install/include/qbittorrent /fuzz/install/lib \
 && cp /fuzz/src/src/base/3rdparty/expected.hpp /fuzz/install/include/qbittorrent/expected.hpp

# Build and install a tiny static stub library to satisfy linker usage
RUN echo "int qbittorrent_stub_version(){return 1;}" > /tmp/stub.cpp \
 && $CXX -c -O2 -fPIC -o /tmp/stub.o /tmp/stub.cpp \
 && ar rcs /fuzz/install/lib/libqbittorrent_stub.a /tmp/stub.o

# No further build needed; headers and a static lib are installed at /fuzz/install
