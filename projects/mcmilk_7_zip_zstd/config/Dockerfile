ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build static libzstd from vendored sources (no external deps)
RUN mkdir -p /fuzz/install/include /fuzz/install/lib /fuzz/build/zstd && \
    cd /fuzz/src/C/zstd && \
    for f in *.c; do \
      stitch_libafl_cc -O2 -fPIC -DZSTD_DISABLE_ASM=1 -I. -I/fuzz/src/C/hashes -c "$f" -o "/fuzz/build/zstd/$(basename "$f" .c).o"; \
    done && \
    stitch_libafl_cc -O2 -fPIC -I/fuzz/src/C/hashes -c /fuzz/src/C/hashes/xxhash.c -o /fuzz/build/zstd/xxhash.o && \
    stitch_libafl_cc -O2 -fPIC -I/fuzz/src/C/hashes -c /fuzz/src/C/hashes/xxh_x86dispatch.c -o /fuzz/build/zstd/xxh_x86dispatch.o && \
    ar rcs /fuzz/install/lib/libzstd.a /fuzz/build/zstd/*.o && \
    cp /fuzz/src/C/zstd/zstd.h /fuzz/src/C/zstd/zstd_errors.h /fuzz/install/include/
