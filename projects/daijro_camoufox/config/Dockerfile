ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Minimal install: just install headers and a shim for mozilla Debug.h used by headers
RUN mkdir -p /fuzz/install/include/mozilla/glue

# Copy header-only public API from mounted source
RUN cp -a /fuzz/src/additions/camoucfg/MaskConfig.hpp /fuzz/install/include/ && \
    cp -a /fuzz/src/additions/camoufgx 2>/dev/null || true
RUN cp -a /fuzz/src/additions/camoucfg/MouseTrajectories.hpp /fuzz/install/include/ && \
    cp -a /fuzz/src/additions/camoucfg/json.hpp /fuzz/install/include/

# Provide a minimal shim for mozilla/glue/Debug.h expected by MaskConfig.hpp
RUN set -e; cat >/fuzz/install/include/mozilla/glue/Debug.h <<'EOF'
#ifndef MOZILLA_GLUE_DEBUG_H
#define MOZILLA_GLUE_DEBUG_H
#include <cstdarg>
#include <cstdio>
inline void printf_stderr(const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  vfprintf(stderr, fmt, args);
  va_end(args);
}
#endif
EOF

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Nothing to build; headers are header-only. Ensure presence
RUN test -f /fuzz/install/include/MouseTrajectories.hpp && test -f /fuzz/install/include/MaskConfig.hpp && test -f /fuzz/install/include/json.hpp
