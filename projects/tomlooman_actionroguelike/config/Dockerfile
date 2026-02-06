ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Provide a minimal shim static library to allow building/linking in this environment.

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/rogue_shim; \
    cat > /tmp/rogue_shim/rogue_shim.h <<'EOF'
#pragma once
#ifdef __cplusplus
extern "C" {
#endif
// Returns a constant version string for the ActionRoguelike shim
const char* rogue_shim_version();
// Simple adder to exercise a code path
int rogue_shim_add(int a, int b);
#ifdef __cplusplus
}
#endif
EOF

RUN set -eux; \
    cat > /tmp/rogue_shim/rogue_shim.cpp <<'EOF'
#include "rogue_shim.h"

const char* rogue_shim_version() {
    return "ActionRoguelike shim 1.0";
}

int rogue_shim_add(int a, int b) {
    return a + b;
}
EOF

RUN set -eux; \
    stitch_libafl_cxx -fPIC -O2 -c /tmp/rogue_shim/rogue_shim.cpp -o /tmp/rogue_shim/rogue_shim.o; \
    ar rcs /fuzz/install/lib/librogue_shim.a /tmp/rogue_shim/rogue_shim.o; \
    cp /tmp/rogue_shim/rogue_shim.h /fuzz/install/include/

# Note: The project sources are at /fuzz/src but Unreal cannot be built here.
