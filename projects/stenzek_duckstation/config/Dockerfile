ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib; \
    cd /fuzz/build; \
    echo "// dummy" > dummy.cpp; \
    $CXX -O2 -c dummy.cpp -o dummy.o; \
    ar rcs /fuzz/install/lib/libduckstation_common.a dummy.o; \
    install -Dm644 /fuzz/src/src/common/types.h /fuzz/install/include/types.h; \
    install -Dm644 /fuzz/src/src/common/xorshift_prng.h /fuzz/install/include/xorshift_prng.h
