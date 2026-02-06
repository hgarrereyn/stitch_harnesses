ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools needed to build a static library (ar)
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Environment
ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

# Build and install a tiny static library from the project's kconfig utilities
# - Build libkconfigutil.a from scripts/config/util.c
# - Install public headers needed by that util API
RUN set -eux; \
    mkdir -p "$PREFIX/include" "$PREFIX/lib" /tmp/build; \
    cd /fuzz/src/scripts/config; \
    # Install headers required by util.c's public API
    install -m644 list.h expr.h lkc_proto.h lkc.h "$PREFIX/include/"; \
    # Build the static library
    "$CC" -O2 -fPIC -I/fuzz/src/scripts/config -c util.c -o /tmp/build/util.o; \
    ar rcs "$PREFIX/lib/libkconfigutil.a" /tmp/build/util.o; \
    ranlib "$PREFIX/lib/libkconfigutil.a"

