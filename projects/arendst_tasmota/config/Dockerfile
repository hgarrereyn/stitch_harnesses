ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install FastCRC as a static library without relying on cmake
RUN mkdir -p /build /fuzz/install/lib /fuzz/install/include && \
    stitch_libafl_cxx -O2 -fPIC -include stddef.h -I/fuzz/src/lib/lib_div/FastCRC/src -c /fuzz/src/lib/lib_div/FastCRC/src/FastCRCsw.cpp -o /build/FastCRCsw.o && \
    stitch_libafl_cxx -O2 -fPIC -include stddef.h -I/fuzz/src/lib/lib_div/FastCRC/src -c /fuzz/src/lib/lib_div/FastCRC/src/FastCRChw.cpp -o /build/FastCRChw.o || true && \
    ar rcs /fuzz/install/lib/libfastcrc.a /build/FastCRCsw.o /build/FastCRChw.o && \
    install -D /fuzz/src/lib/lib_div/FastCRC/src/FastCRC.h /fuzz/install/include/FastCRC.h
