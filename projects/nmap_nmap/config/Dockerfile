ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential \
    python3-minimal \
    flex bison \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src

# Configure with fuzzing compilers and a minimal feature set; install prefix is /fuzz/install
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx
RUN ./configure --prefix=/fuzz/install \
    --without-zenmap \
    --without-ndiff \
    --without-nping \
    --without-openssl

# Build everything (static libs are produced by subdirs like nsock/nbase/libpcap)
RUN make -j$(nproc)

# Install the binary data (not strictly necessary for the library usage)
RUN make install

# Manually install the libraries/headers we want to link against (nsock + nbase + pcap)
RUN mkdir -p /fuzz/install/include/nsock /fuzz/install/lib \
 && cp -v nsock/include/nsock.h nsock/include/nsock_config.h /fuzz/install/include/nsock/ \
 && cp -v nsock/src/libnsock.a /fuzz/install/lib/ \
 && cp -v nbase/libnbase.a /fuzz/install/lib/ \
 && cp -v libpcap/libpcap.a /fuzz/install/lib/
