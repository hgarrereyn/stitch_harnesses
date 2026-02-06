ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx
ENV AR=ar
ENV INSTALL_PREFIX=/fuzz/install

RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

RUN set -eux; \
    mkdir -p /fuzz/build "$INSTALL_PREFIX/lib" "$INSTALL_PREFIX/include/commonlib/bsd"; \
    cd /fuzz/build; \
    CFLAGS="-O2 -fPIC -D__packed=__attribute__((packed)) -D__aligned(x)=__attribute__((aligned(x))) -I/fuzz/src/src/commonlib/bsd/include -I/fuzz/src/src/commonlib/bsd/zstd -I/fuzz/src/src/commonlib/bsd/zstd/common -I/fuzz/src/src/commonlib/bsd/zstd/decompress"; \
    SRCS="\
      /fuzz/src/src/commonlib/bsd/gcd.c \
      /fuzz/src/src/commonlib/bsd/ipchksum.c \
      /fuzz/src/src/commonlib/bsd/elog.c \
      /fuzz/src/src/commonlib/bsd/lz4_wrapper.c \
      /fuzz/src/src/commonlib/bsd/xxhash.c \
      /fuzz/src/src/commonlib/bsd/string.c \
      /fuzz/src/src/commonlib/bsd/zstd_wrapper.c \
      /fuzz/src/src/commonlib/bsd/zstd/common/debug.c \
      /fuzz/src/src/commonlib/bsd/zstd/common/entropy_common.c \
      /fuzz/src/src/commonlib/bsd/zstd/common/error_private.c \
      /fuzz/src/src/commonlib/bsd/zstd/common/fse_decompress.c \
      /fuzz/src/src/commonlib/bsd/zstd/common/zstd_common.c \
      /fuzz/src/src/commonlib/bsd/zstd/decompress/zstd_decompress.c \
      /fuzz/src/src/commonlib/bsd/zstd/decompress/zstd_decompress_block.c \
      /fuzz/src/src/commonlib/bsd/zstd/decompress/huf_decompress.c \
      /fuzz/src/src/commonlib/bsd/zstd/decompress/zstd_ddict.c \
    "; \
    for f in $SRCS; do "$CC" $CFLAGS -c "$f" -o "$(basename "$f").o"; done; \
    $AR rcs "$INSTALL_PREFIX/lib/libcommonlib_bsd.a" *.o; \
    for h in \
      bcd.h cb_err.h elog.h gcd.h ipchksum.h compression.h xxhash.h string.h; do \
      cp -a "/fuzz/src/src/commonlib/bsd/include/commonlib/bsd/$h" "$INSTALL_PREFIX/include/commonlib/bsd/"; \
    done
