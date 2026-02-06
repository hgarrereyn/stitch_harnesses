ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install tools needed for building a static library manually
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    INSTALL_PREFIX=/fuzz/install

# Build a static lib from the kconfig sources in scripts/config
RUN set -eux; \
    mkdir -p /build /fuzz/install/lib /fuzz/install/include/kconfig; \
    cd /build; \
    inc=/fuzz/src/scripts/config; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/confdata.c" -o confdata.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/expr.c" -o expr.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/images.c" -o images.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/lexer.lex.c" -o lexer.lex.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/menu.c" -o menu.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/parser.tab.c" -o parser.tab.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/preprocess.c" -o preprocess.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/symbol.c" -o symbol.o; \
    $CC -fPIC -O2 -I"$inc" -c "$inc/util.c" -o util.o; \
    ar rcs libkconfig.a confdata.o expr.o images.o lexer.lex.o menu.o parser.tab.o preprocess.o symbol.o util.o; \
    ranlib libkconfig.a || true; \
    cp libkconfig.a /fuzz/install/lib/; \
    # Install public headers
    cp "$inc/expr.h" "$inc/images.h" "$inc/lkc.h" "$inc/lkc_proto.h" "$inc/list.h" /fuzz/install/include/kconfig/
