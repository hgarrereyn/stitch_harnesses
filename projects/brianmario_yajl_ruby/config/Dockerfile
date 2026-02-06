ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install YAJL (C library bundled in this repo) as a static lib
RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    cd /fuzz/src/ext/yajl; \
    export CC=gf_libafl_cc; \
    CFLAGS="-O2 -fPIC -I."; \
    $CC $CFLAGS -c yajl_alloc.c -o yajl_alloc.o; \
    $CC $CFLAGS -c yajl_buf.c -o yajl_buf.o; \
    $CC $CFLAGS -c yajl_encode.c -o yajl_encode.o; \
    $CC $CFLAGS -c yajl_gen.c -o yajl_gen.o; \
    $CC $CFLAGS -c yajl_lex.c -o yajl_lex.o; \
    $CC $CFLAGS -c yajl_parser.c -o yajl_parser.o; \
    $CC $CFLAGS -c yajl.c -o yajl.o; \
    $CC $CFLAGS -c yajl_version.c -o yajl_version.o; \
    ar rcs /fuzz/install/lib/libyajl.a \
      yajl_alloc.o yajl_buf.o yajl_encode.o yajl_gen.o yajl_lex.o yajl_parser.o yajl.o yajl_version.o; \
    mkdir -p /fuzz/install/include/api; \
    cp -a api/*.h /fuzz/install/include/api/

