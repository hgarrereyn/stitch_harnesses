ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a tiny static library from Asterisk sources (MD5)
# using the required compilers and install prefix.

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

RUN set -eux; \
    mkdir -p /fuzz/build/stub/include/asterisk "$PREFIX"/lib "$PREFIX"/include/asterisk; \
    # Minimal stub for generated header expected by asterisk.h
    printf "/* stub autoconfig for fuzzing build */\n" > /fuzz/build/stub/include/asterisk/autoconfig.h; \
    # Compile just the standalone MD5 implementation. Define AST_NOT_MODULE to avoid module symbol requirement
    # and HAVE_STRTOQ to avoid conflicting prototype from compat.h.
    "$CC" -O2 -fPIC -DAST_NOT_MODULE -DHAVE_STRTOQ -I/fuzz/build/stub/include -I"$SRC"/include \
        -c "$SRC"/main/md5.c -o /fuzz/build/md5.o; \
    ar rcs /fuzz/build/libasteriskmd5.a /fuzz/build/md5.o; \
    cp /fuzz/build/libasteriskmd5.a "$PREFIX"/lib/; \
    # Install the public headers needed to consume the MD5 API
    cp "$SRC"/include/asterisk/md5.h "$PREFIX"/include/asterisk/; \
    cp "$SRC"/include/asterisk/endian.h "$PREFIX"/include/asterisk/
