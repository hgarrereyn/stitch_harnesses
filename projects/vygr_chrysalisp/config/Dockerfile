ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include
WORKDIR /fuzz/src

# Create minimal Linux stubs for a subset of PII functions to avoid SDL and platform-specific build issues
RUN printf '%s\n' \
'#include <stdint.h>' \
'#include <sys/time.h>' \
'#include <sys/types.h>' \
'#include <sys/stat.h>' \
'#include <fcntl.h>' \
'#include <unistd.h>' \
'extern "C++" int64_t pii_gettime(){ struct timeval tv; gettimeofday(&tv, 0); return (int64_t)tv.tv_sec*1000000 + tv.tv_usec; }' \
'extern "C++" int64_t pii_open(const char *path, uint64_t mode){ int flags=O_RDONLY; if(mode==1) flags=O_CREAT|O_RDWR|O_TRUNC; else if(mode==2) flags=O_CREAT|O_RDWR; int fd=open(path, flags, 0644); if(mode==2 && fd>=0) lseek(fd,0,SEEK_END); return fd; }' \
'extern "C++" uint64_t pii_close(uint64_t fd){ return close((int)fd); }' \
> /fuzz/build/stubs.cpp

# Build static library: vp64 core + minimal stubs
RUN $CXX -I/fuzz/src/src/host -O2 -fno-exceptions -c src/host/vp64.cpp -o /fuzz/build/vp64.o && \
    $CXX -O2 -fno-exceptions -c /fuzz/build/stubs.cpp -o /fuzz/build/stubs.o && \
    ar rcs /fuzz/install/lib/libchrysalisp.a /fuzz/build/vp64.o /fuzz/build/stubs.o && \
    cp src/host/pii.h src/host/sdl_dummy.h /fuzz/install/include/
