ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install libfdt (from scripts/dtc/libfdt) as a static library
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    AR=ar

WORKDIR /fuzz/src

RUN set -eux; \
    mkdir -p /fuzz/build/libfdt /fuzz/install/include/libfdt /fuzz/install/lib; \
    cd scripts/dtc/libfdt; \
    SRCs="fdt.c fdt_addresses.c fdt_empty_tree.c fdt_overlay.c fdt_ro.c fdt_rw.c fdt_strerror.c fdt_sw.c fdt_wip.c"; \
    for f in $SRCs; do \
      "$CC" -O2 -fPIC -I . -c "$f" -o "/fuzz/build/libfdt/$(basename "$f" .c).o"; \
    done; \
    "$AR" rcs /fuzz/install/lib/libfdt.a /fuzz/build/libfdt/*.o; \
    cp libfdt.h libfdt_env.h fdt.h /fuzz/install/include/libfdt/
