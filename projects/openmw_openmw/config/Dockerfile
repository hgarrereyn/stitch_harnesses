ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV DEBIAN_FRONTEND=noninteractive

# Use the required fuzzing compiler wrappers
ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# No heavy deps are needed for the minimal headers-only API test.
RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

# Install headers and build a tiny static stub library to link against
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/components /fuzz/install/include/components \
 && printf 'void openmw_components_stub(void){}' > /tmp/stub.c \
 && ${CC} -c /tmp/stub.c -o /tmp/stub.o \
 && ar rcs /fuzz/install/lib/libopenmw_components_stub.a /tmp/stub.o
