ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required libraries for building and linking
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    pkg-config \
    libgpg-error-dev libgcrypt20-dev \
    ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Build a minimal static library from GnuPG's common module for linking
WORKDIR /fuzz
RUN install -d /fuzz/install/lib /fuzz/install/include/gnupg /fuzz/build_miniconf
# Minimal config header to satisfy common/*.c includes
RUN printf '#ifndef GNUPG_MINI_CONFIG_H\n#define GNUPG_MINI_CONFIG_H\n\n#include <stdlib.h>\n\n/* Pretend we are on a POSIX system. */\n#define HAVE_PWD_H 1\n#define HAVE_GETPWUID 1\n#define HAVE_GETPWNAM 1\n/* Avoid redefining isascii which exists in ctype.h on this platform. */\n#define HAVE_ISASCII 1\n/* Do not enable any Windows specific code paths. */\n/* #undef HAVE_DOSISH_SYSTEM */\n\n/* Provide minimal estream compatibility types used by util.h */\ntypedef void* estream_t;\ntypedef int es_syshd_t;\n\n/* Provide a simple assert macro used in common code. */\n#ifndef log_assert\n#define log_assert(expr) do { if(!(expr)) abort(); } while(0)\n#endif\n\n#endif\n' > /fuzz/build_miniconf/config.h

# Provide tiny shims for a couple of utility symbols referenced by stringhelp
RUN printf '#include <unistd.h>\n#include <stdlib.h>\nchar *gnupg_getcwd(void){\n  long sz = 4096;\n  char *buf = (char*)malloc(sz);\n  if(!buf) return NULL;\n  if(getcwd(buf, sz)) return buf;\n  free(buf);\n  return NULL;\n}\n' > /fuzz/build_miniconf/mini_shims.c

# Compile a subset of the common module into a static library
RUN stitch_libafl_cc -O2 -I/fuzz/build_miniconf -I/fuzz/src/common -c /fuzz/src/common/stringhelp.c -o /tmp/stringhelp.o && \
    stitch_libafl_cc -O2 -I/fuzz/build_miniconf -I/fuzz/src/common -c /fuzz/src/common/percent.c -o /tmp/percent.o && \
    stitch_libafl_cc -O2 -I/fuzz/build_miniconf -c /fuzz/build_miniconf/mini_shims.c -o /tmp/mini_shims.o && \
    ar rcs /fuzz/install/lib/libcommon.a /tmp/stringhelp.o /tmp/percent.o /tmp/mini_shims.o && \
    install -m 0644 /fuzz/src/common/stringhelp.h /fuzz/src/common/types.h /fuzz/install/include/gnupg/
