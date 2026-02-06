ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends make libssl-dev && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

WORKDIR /fuzz/src/src

# Build the static library
RUN make libsmartdns.a

# Install headers and library
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/smartdns/lib /fuzz/install/include/smartdns \
    && cp -v libsmartdns.a /fuzz/install/lib/ \
    && cp -v include/smartdns/*.h /fuzz/install/include/smartdns/ \
    && cp -v include/smartdns/lib/*.h /fuzz/install/include/smartdns/lib/
