ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal tools and headers
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    binutils \
    libboost-dev \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Build a small self-contained static library from the project's IANA protocol API
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include \
 && "$CXX" -O2 -fPIC -c /fuzz/src/src/iana_ip_protocols.cpp -o /fuzz/build/iana_ip_protocols.o -I/fuzz/src/src \
 && ar rcs /fuzz/install/lib/libfastnetmon_iana.a /fuzz/build/iana_ip_protocols.o \
 && install -m 0644 /fuzz/src/src/iana_ip_protocols.hpp /fuzz/install/include/
