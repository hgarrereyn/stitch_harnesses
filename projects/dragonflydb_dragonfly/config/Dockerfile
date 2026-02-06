ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

WORKDIR /fuzz/src

RUN set -eux; \
    install -d /fuzz/install/lib /fuzz/install/include/dragonfly/redis /fuzz/install/include/redis; \
    SRC=/fuzz/src/src/redis; \
    SRCROOT=/fuzz/src/src; \
    INC1=/fuzz/install/include/dragonfly/redis; \
    INC2=/fuzz/install/include/redis; \
    # Install headers for public API into both include prefixes
    cp ${SRC}/*.h ${INC1}/; \
    cp ${SRC}/*.h ${INC2}/; \
    # Compile C sources into objects (provide include for both src/redis and src/)
    CFLAGS="-O2 -fPIC -I${SRC} -I${SRCROOT}"; \
    ${CC} $CFLAGS -c ${SRC}/crc16.c -o /tmp/crc16.o; \
    ${CC} $CFLAGS -c ${SRC}/crc64.c -o /tmp/crc64.o; \
    ${CC} $CFLAGS -c ${SRC}/crcspeed.c -o /tmp/crcspeed.o; \
    ${CC} $CFLAGS -c ${SRC}/debug.c -o /tmp/debug.o; \
    ${CC} $CFLAGS -c ${SRC}/intset.c -o /tmp/intset.o; \
    ${CC} $CFLAGS -c ${SRC}/geo.c -o /tmp/geo.o; \
    ${CC} $CFLAGS -c ${SRC}/geohash.c -o /tmp/geohash.o; \
    ${CC} $CFLAGS -c ${SRC}/geohash_helper.c -o /tmp/geohash_helper.o; \
    ${CC} $CFLAGS -c ${SRC}/hiredis.c -o /tmp/hiredis.o; \
    ${CC} $CFLAGS -c ${SRC}/read.c -o /tmp/read.o; \
    ${CC} $CFLAGS -c ${SRC}/listpack.c -o /tmp/listpack.o; \
    ${CC} $CFLAGS -c ${SRC}/lzf_c.c -o /tmp/lzf_c.o; \
    ${CC} $CFLAGS -c ${SRC}/lzf_d.c -o /tmp/lzf_d.o; \
    ${CC} $CFLAGS -c ${SRC}/sds.c -o /tmp/sds.o; \
    ${CC} $CFLAGS -c ${SRC}/quicklist.c -o /tmp/quicklist.o; \
    ${CC} $CFLAGS -c ${SRC}/rax.c -o /tmp/rax.o; \
    ${CC} $CFLAGS -c ${SRC}/redis_aux.c -o /tmp/redis_aux.o; \
    ${CC} $CFLAGS -c ${SRC}/t_stream.c -o /tmp/t_stream.o; \
    ${CC} $CFLAGS -c ${SRC}/util.c -o /tmp/util.o; \
    ${CC} $CFLAGS -c ${SRC}/ziplist.c -o /tmp/ziplist.o; \
    ${CC} $CFLAGS -c ${SRC}/hyperloglog.c -o /tmp/hyperloglog.o; \
    ${CC} $CFLAGS -c ${SRC}/siphash.c -o /tmp/siphash.o; \
    ar rcs /fuzz/install/lib/libdfredis.a \
      /tmp/crc16.o /tmp/crc64.o /tmp/crcspeed.o /tmp/debug.o /tmp/intset.o /tmp/geo.o \
      /tmp/geohash.o /tmp/geohash_helper.o /tmp/hiredis.o /tmp/read.o /tmp/listpack.o \
      /tmp/lzf_c.o /tmp/lzf_d.o /tmp/sds.o /tmp/quicklist.o /tmp/rax.o /tmp/redis_aux.o \
      /tmp/t_stream.o /tmp/util.o /tmp/ziplist.o /tmp/hyperloglog.o /tmp/siphash.o; \
    ranlib /fuzz/install/lib/libdfredis.a
