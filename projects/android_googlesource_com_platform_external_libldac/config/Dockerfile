ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build static libldacBT_enc.a and libldacBT_abr.a and install headers
RUN set -eux; \
    apt-get update; \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends ca-certificates pkg-config; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include; \
    cd /fuzz/src; \
    stitch_libafl_cc -O2 -fPIC -Wall -Wextra -Iinc -Isrc -c src/ldaclib.c -o /fuzz/build/ldaclib.o; \
    stitch_libafl_cc -O2 -fPIC -Wall -Wextra -Iinc -Isrc -c src/ldacBT.c -o /fuzz/build/ldacBT.o; \
    ar rcs /fuzz/install/lib/libldacBT_enc.a /fuzz/build/ldaclib.o /fuzz/build/ldacBT.o; \
    stitch_libafl_cc -O2 -fPIC -Wall -Wextra -Iinc -Iabr/inc -Isrc -c abr/src/ldacBT_abr.c -o /fuzz/build/ldacBT_abr.o; \
    ar rcs /fuzz/install/lib/libldacBT_abr.a /fuzz/build/ldacBT_abr.o; \
    install -m 0644 inc/ldacBT.h /fuzz/install/include/; \
    install -m 0644 abr/inc/ldacBT_abr.h /fuzz/install/include/
