ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends \
    binutils \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc \
    CXX=gf_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p ${PREFIX}/include ${PREFIX}/lib

RUN cat > /tmp/oss_fuzz_dummy.h <<'EOF'
#ifndef OSS_FUZZ_DUMMY_H
#define OSS_FUZZ_DUMMY_H
#include <string>
namespace ossfuzz {
// Returns a string with a short description.
std::string version();
}
#endif
EOF

RUN cat > /tmp/oss_fuzz_dummy.cpp <<'EOF'
#include "oss_fuzz_dummy.h"
namespace ossfuzz {
std::string version() { return "oss-fuzz-repo-dummy-lib"; }
}
EOF

RUN set -eux; \
    "$CXX" -fPIC -O2 -c /tmp/oss_fuzz_dummy.cpp -o /tmp/oss_fuzz_dummy.o; \
    ar rcs ${PREFIX}/lib/libossfuzzdummy.a /tmp/oss_fuzz_dummy.o; \
    install -m 0644 /tmp/oss_fuzz_dummy.h ${PREFIX}/include/oss_fuzz_dummy.h; \
    rm -f /tmp/oss_fuzz_dummy.h /tmp/oss_fuzz_dummy.cpp /tmp/oss_fuzz_dummy.o

