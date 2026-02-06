ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Build static libpg_query from the vendored sources
ENV SRC_DIR=/fuzz/src/ext/pg_query \
    PREFIX=/fuzz/install \
    CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx

RUN mkdir -p /build && \
    mkdir -p ${PREFIX}/lib ${PREFIX}/include && \
    cd /build && \
    INCLUDES="-I${SRC_DIR}/include -I${SRC_DIR}/include/postgres" && \
    # Compile C sources (exclude Ruby binding)
    for f in ${SRC_DIR}/*.c ${SRC_DIR}/src_*.c; do \
      bn=$(basename "$f"); \
      if [ "$bn" = "pg_query_ruby.c" ]; then continue; fi; \
      if [ "$bn" = "pg_query_outfuncs_protobuf_cpp.cc" ]; then continue; fi; \
      ${CC} -c -O2 -fPIC $INCLUDES "$f" -o "${bn%.c}.o"; \
    done && \
    # Create static library
    ar rcs libpg_query.a *.o && \
    ranlib libpg_query.a && \
    # Install library and public headers
    cp libpg_query.a ${PREFIX}/lib/ && \
    install -m 0644 ${SRC_DIR}/include/pg_query.h ${PREFIX}/include/
