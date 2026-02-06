ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and system libsodium
RUN apt-get update && apt-get install -y --no-install-recommends build-essential ca-certificates libsodium-dev && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc
ENV CXX=gf_libafl_cxx

# Build static lib and install
RUN set -eux; \
    SRC=/fuzz/src; \
    INST=/fuzz/install; \
    mkdir -p /fuzz/build "$INST/lib" "$INST/include"; \
    cd /fuzz/build; \
    CFLAGS="-O2 -fPIC"; \
    CXXFLAGS="-O2 -fPIC"; \
    INCLUDES="-I$SRC -I$SRC/include -I$SRC/serialize -I$SRC/netcode -I$SRC/reliable"; \
    # Build C deps (link to system libsodium at final link time)
    $CC $CFLAGS $INCLUDES -c $SRC/netcode/netcode.c -o netcode.o; \
    $CC $CFLAGS $INCLUDES -c $SRC/reliable/reliable.c -o reliable.o; \
    $CC $CFLAGS $INCLUDES -c $SRC/tlsf/tlsf.c -o tlsf.o; \
    # Build yojimbo sources
    for f in $SRC/source/*.cpp; do \
      base=$(basename "$f"); \
      out="${base%.cpp}.o"; \
      $CXX $CXXFLAGS $INCLUDES -c "$f" -o "$out"; \
    done; \
    # Archive static library
    ar rcs libyojimbo.a *.o; \
    install -m644 libyojimbo.a "$INST/lib/"; \
    # Install headers (public and required deps)
    cp -a $SRC/include/*.h "$INST/include/"; \
    cp -a $SRC/serialize/serialize.h "$INST/include/"; \
    :
