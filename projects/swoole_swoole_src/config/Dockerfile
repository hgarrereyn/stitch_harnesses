ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

# Install headers and write a minimal shim source implementing version APIs
RUN set -eux; \
    mkdir -p "$PREFIX/lib" "$PREFIX/include/swoole" "$PREFIX/include/swoole/wrapper" /tmp/build; \
    cd /fuzz/src; \
    cp -a include/*.h "$PREFIX/include/swoole/"; \
    if [ -d include/wrapper ]; then cp -a include/wrapper/*.hpp "$PREFIX/include/swoole/wrapper/" || true; fi; \
    cat > /tmp/build/version_shim.cc <<'EOF'
#include <stddef.h>
extern "C" {
#include "swoole/swoole_version.h"
}
extern "C" {
const char *swoole_version(void) { return SWOOLE_VERSION; }
int swoole_version_id(void) { return SWOOLE_VERSION_ID; }
int swoole_api_version_id(void) { return SWOOLE_API_VERSION_ID; }
}
EOF

# Build the minimal static library
RUN set -eux; \
    $CXX -O2 -g -fPIC -I"$PREFIX/include" -std=c++14 -c /tmp/build/version_shim.cc -o /tmp/build/version_shim.o; \
    ar rcs "$PREFIX/lib/libswoole.a" /tmp/build/version_shim.o

# Done. The fuzz harnesses and tests will link against /fuzz/install
