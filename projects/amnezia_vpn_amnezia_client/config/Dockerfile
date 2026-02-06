ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra deps needed for header-only test (using a simple enum header)

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN mkdir -p /fuzz/build && cd /fuzz/build && \
    printf "%s\n" "// minimal stub to produce a static library" "extern \"C\" void amnezia_placeholder(){}" > stub.cpp && \
    "$CXX" -fPIC -c stub.cpp -o stub.o && \
    ar rcs libamnezia_client.a stub.o && \
    mkdir -p /fuzz/install/lib /fuzz/install/include/amnezia && \
    cp libamnezia_client.a /fuzz/install/lib/ && \
    cp /fuzz/src/client/mozilla/shared/loglevel.h /fuzz/install/include/amnezia/
