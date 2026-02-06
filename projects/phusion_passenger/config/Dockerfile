ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools if missing
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    binutils \
    && rm -rf /var/lib/apt/lists/*

# Build a minimal static library from the C++ supportlib (oxt)
# and install headers for inclusion
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN set -eux; \
    install -d /fuzz/install/include/passenger /fuzz/install/lib /tmp/build_oxt; \
    # Copy headers (keep tree under 'passenger')
    cp -a /fuzz/src/src/cxx_supportlib/. /fuzz/install/include/passenger/; \
    # Build lib from oxt sources (needs boost headers from vendor-modified)
    cd /tmp/build_oxt; \
    "$CXX" -fPIC -O2 -I/fuzz/install/include/passenger -I/fuzz/install/include/passenger/vendor-modified -c /fuzz/src/src/cxx_supportlib/oxt/implementation.cpp -o implementation.o; \
    "$CXX" -fPIC -O2 -I/fuzz/install/include/passenger -I/fuzz/install/include/passenger/vendor-modified -c /fuzz/src/src/cxx_supportlib/oxt/system_calls.cpp -o system_calls.o; \
    ar rcs /fuzz/install/lib/libpassenger_oxt.a implementation.o system_calls.o; \
    ranlib /fuzz/install/lib/libpassenger_oxt.a; \
    cd /; rm -rf /tmp/build_oxt
