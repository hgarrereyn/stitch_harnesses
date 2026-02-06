ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/lib /fuzz/install/include /tmp/kconfig; \
    cd /tmp/kconfig; \
    for f in confdata.c expr.c images.c menu.c preprocess.c symbol.c util.c lexer.lex.c parser.tab.c; do \
      ${CC} -O2 -fPIC -I/fuzz/src/scripts/config -c /fuzz/src/scripts/config/$f; \
    done; \
    ar rcs libkconfig.a *.o; \
    ranlib libkconfig.a || true; \
    install -m644 libkconfig.a /fuzz/install/lib/; \
    cp /fuzz/src/scripts/config/list.h /fuzz/src/scripts/config/expr.h /fuzz/src/scripts/config/images.h /fuzz/src/scripts/config/lkc.h /fuzz/src/scripts/config/lkc_proto.h /fuzz/install/include/
