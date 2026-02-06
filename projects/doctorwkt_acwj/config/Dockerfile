ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools
RUN apt-get update && apt-get install -y --no-install-recommends build-essential && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc
ENV CXX=stitch_libafl_cxx

# Build a static library from the 63_QBE chapter sources and install headers
RUN set -eux; \
    install -d /fuzz/install/lib /fuzz/install/include/acwj /fuzz/install/share/acwj/include; \
    cp -r /fuzz/src/63_QBE/include/. /fuzz/install/share/acwj/include/; \
    cd /fuzz/src/63_QBE; \
    echo "#define INCDIR \"/fuzz/install/share/acwj/include\"" > incdir.h; \
    srclist="cg.c decl.c expr.c gen.c misc.c opt.c scan.c stmt.c sym.c tree.c types.c main.c"; \
    for f in $srclist; do \
      if [ "$f" = "main.c" ]; then \
        ${CC} -g -O2 -Wall -I. -Dmain=acwj_main -c $f; \
      else \
        ${CC} -g -O2 -Wall -I. -c $f; \
      fi; \
    done; \
    ar rcs /fuzz/install/lib/libacwj.a cg.o decl.o expr.o gen.o misc.o opt.o scan.o stmt.o sym.o tree.o types.o main.o; \
    cp decl.h defs.h data.h incdir.h /fuzz/install/include/acwj/

