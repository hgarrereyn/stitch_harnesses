ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal static libgif from the vendored gif sources (no Android NDK needed)
RUN set -eux; \
    apt-get update; apt-get install -y --no-install-recommends ca-certificates build-essential; \
    rm -rf /var/lib/apt/lists/*; \
    mkdir -p /work/obj /fuzz/install/include /fuzz/install/lib; \
    cd /work; \
    SRC=/fuzz/src/app/src/main/cpp/gif; \
    # Install public header
    cp "$SRC/gif_lib.h" /fuzz/install/include/; \
    # Compile sources into a static library
    stitch_libafl_cc -fPIC -O2 -I"$SRC" -c "$SRC/dgif_lib.c" -o obj/dgif_lib.o; \
    stitch_libafl_cc -fPIC -O2 -I"$SRC" -c "$SRC/egif_lib.c" -o obj/egif_lib.o; \
    stitch_libafl_cc -fPIC -O2 -I"$SRC" -c "$SRC/gif_err.c" -o obj/gif_err.o; \
    stitch_libafl_cc -fPIC -O2 -I"$SRC" -c "$SRC/gif_hash.c" -o obj/gif_hash.o; \
    stitch_libafl_cc -fPIC -O2 -I"$SRC" -c "$SRC/gifalloc.c" -o obj/gifalloc.o; \
    stitch_libafl_cc -fPIC -O2 -I"$SRC" -c "$SRC/quantize.c" -o obj/quantize.o; \
    ar rcs /fuzz/install/lib/libgif.a obj/*.o; \
    ranlib /fuzz/install/lib/libgif.a
