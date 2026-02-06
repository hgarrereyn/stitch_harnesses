ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

# Build a minimal static library from common C utilities and frozen JSON
RUN set -eux; \
    mkdir -p ${INSTALL_PREFIX}/lib ${INSTALL_PREFIX}/include; \
    OBJDIR=/tmp/objs; mkdir -p "$OBJDIR"; \
    INCDIR=/fuzz/src/include; FROZENDIR=/fuzz/src/src/frozen; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/cs_crc32.c -o $OBJDIR/cs_crc32.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/cs_file.c   -o $OBJDIR/cs_file.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/cs_frbuf.c  -o $OBJDIR/cs_frbuf.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/cs_hex.c    -o $OBJDIR/cs_hex.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/cs_rbuf.c   -o $OBJDIR/cs_rbuf.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/cs_varint.c -o $OBJDIR/cs_varint.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/common/json_utils.c -o $OBJDIR/json_utils.o; \
    $CC -O2 -fPIC -I"$INCDIR" -I"$FROZENDIR" -c /fuzz/src/src/frozen/frozen.c     -o $OBJDIR/frozen.o; \
    ar rcs ${INSTALL_PREFIX}/lib/libmgos.a $OBJDIR/*.o; \
    # Install headers (public API)
    cp -a /fuzz/src/include/* ${INSTALL_PREFIX}/include/; \
    cp /fuzz/src/src/frozen/frozen.h ${INSTALL_PREFIX}/include/
