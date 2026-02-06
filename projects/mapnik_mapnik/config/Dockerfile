ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal build: create a tiny static libmapnik.a from src/mapnik.cpp and install public headers
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include
WORKDIR /fuzz/build
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
# Build a minimal static library containing mapnik::setup()
RUN $CXX -std=c++17 -O2 -fPIC -I/fuzz/src/include -c /fuzz/src/src/mapnik.cpp -o mapnik.o \
 && ar rcs libmapnik.a mapnik.o \
 && cp libmapnik.a /fuzz/install/lib/
# Install headers (public API)
RUN mkdir -p /fuzz/install/include/mapnik \
 && cp -r /fuzz/src/include/mapnik/* /fuzz/install/include/mapnik/
