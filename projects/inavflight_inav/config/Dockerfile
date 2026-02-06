ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include && \
    set -eux; \
    cd /fuzz/build; \
    SRC_DIR=/fuzz/src/src/main; \
    TEST_DIR=/fuzz/src/src/test/unit; \
    INCDIR=$SRC_DIR/common; \
    for f in $SRC_DIR/common/maths.c $SRC_DIR/common/bitarray.c; do \
      echo "Compiling $f"; \
      $CC -O2 -fPIC -I$SRC_DIR -I$INCDIR -I$TEST_DIR -c "$f" -o "$(basename "$f" .c).o"; \
    done; \
    ar rcs libinav.a *.o; \
    mv libinav.a /fuzz/install/lib/; \
    cp -v $INCDIR/maths.h $INCDIR/bitarray.h /fuzz/install/include/

ENV CFLAGS="-I/fuzz/install/include" LDFLAGS="-L/fuzz/install/lib"