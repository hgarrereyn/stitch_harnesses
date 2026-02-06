ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

WORKDIR /fuzz/src

# Build only the static library using required compilers
RUN make clean || true \
 && make -j$(nproc) my_api.a CXX=gf_libafl_cxx CC=gf_libafl_cc

# Install headers and library to /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -v my_api.h /fuzz/install/include/ \
 && cp -v my_api.a /fuzz/install/lib/
