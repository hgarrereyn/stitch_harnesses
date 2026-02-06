ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends binutils ca-certificates && rm -rf /var/lib/apt/lists/*

WORKDIR /fuzz/src
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# Build minimal static library and a C shim that wraps a few functions and provides missing globals
RUN set -eux; \
    printf "%s\n" '#include <sys/select.h>' '#include <stdint.h>' '#include "hydra-mod.h"' '' 'int32_t conwait = 1;' 'int32_t my_select(int32_t fd, fd_set *r, fd_set *w, fd_set *e, long sec, long usec){' '  struct timeval tv; tv.tv_sec=sec; tv.tv_usec=usec; return select(fd, r, w, e, &tv); }' '' 'void thcf_make_to_lower(char* s){ make_to_lower(s); }' 'void thcf_base64(unsigned char* buf, unsigned int buflen, unsigned int bufsize){ hydra_tobase64(buf, buflen, bufsize); }' 'int thcf_memsearch(char* h,int hl,char* n,int nl){ return hydra_memsearch(h,hl,n,nl); }' > shim.c; \
    $CC -I. -O2 -fcommon -c hydra-mod.c crc32.c d3des.c bfg.c ntlm.c sasl.c hmacmd5.c hydra-time.c shim.c; \
    mkdir -p /fuzz/install/lib /fuzz/install/include; \
    ar rcs /fuzz/install/lib/libhydra.a hydra-mod.o crc32.o d3des.o bfg.o ntlm.o sasl.o hmacmd5.o hydra-time.o shim.o; \
    cp -f hydra.h hydra-mod.h hydra-http.h d3des.h crc32.h bfg.h hmacmd5.h performance.h /fuzz/install/include/
