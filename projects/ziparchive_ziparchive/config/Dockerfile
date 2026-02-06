ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build static minizip-ng (vendored) from SSZipArchive/minizip on Linux
# and install into /fuzz/install

ENV DEBIAN_FRONTEND=noninteractive

# 1) Dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# 2) Configure compilers and install prefix
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx PREFIX=/fuzz/install

# 3) Build only a static library and install headers
RUN set -eux; \
    builddir=/tmp/build && mkdir -p "$builddir" "$PREFIX/lib" "$PREFIX/include/minizip"; \
    cd /fuzz/src/SSZipArchive/minizip; \
    INCS="-I/fuzz/src/SSZipArchive/minizip"; \
    DEFS="-DHAVE_ZLIB -DHAVE_STDINT_H -DHAVE_INTTYPES_H -DZLIB_COMPAT -DMZ_ZIP_NO_CRYPTO"; \
    SRCS="mz_crypt.c mz_os.c mz_os_posix.c mz_strm.c mz_strm_buf.c mz_strm_mem.c mz_strm_os_posix.c mz_strm_split.c mz_strm_zlib.c mz_zip.c mz_zip_rw.c"; \
    for f in $SRCS; do \
      $CC -c -O2 -fPIC $INCS $DEFS "$f" -o "$builddir/${f%.c}.o"; \
    done; \
    ar rcs "$PREFIX/lib/libminizip.a" $builddir/*.o; \
    # Install headers
    cp -a *.h "$PREFIX/include/minizip/";

# Done
