ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN apt-get update && apt-get install -y --no-install-recommends build-essential ca-certificates && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
ENV PREFIX=/fuzz/install

WORKDIR /fuzz/src

# Create shim headers for Switch SDK bits used by this subset
RUN mkdir -p /fuzz/build/shim_includes/switch/services && \
    printf '%s\n' \
    '#ifndef SYS_DVR_SHIM_SWITCH_H' \
    '#define SYS_DVR_SHIM_SWITCH_H' \
    '#include <stdint.h>' \
    '#include <stdbool.h>' \
    '#include <stddef.h>' \
    'typedef uint32_t u32;' \
    'typedef uint8_t u8;' \
    'typedef int32_t s32;' \
    'typedef struct { int dummy; } Mutex;' \
    'static inline void mutexInit(Mutex* m) {(void)m;}' \
    'static inline void mutexLock(Mutex* m) {(void)m;}' \
    'static inline void mutexUnlock(Mutex* m) {(void)m;}' \
    'typedef void (*ThreadFunc)(void*);' \
    'typedef struct { int dummy; } Thread;' \
    'typedef uint32_t Result;' \
    'static inline void fatalThrow(Result r) {(void)r;}' \
    'static inline void svcSleepThread(uint64_t ns) {(void)ns;}' \
    'extern int g_bsdErrno;' \
    '#ifndef alignas' \
    '#define alignas(x) __attribute__((aligned(x)))' \
    '#endif' \
    '#endif' \
    > /fuzz/build/shim_includes/switch.h && \
    printf '%s\n' \
    '#ifndef SYS_DVR_SHIM_BSD_H' \
    '#define SYS_DVR_SHIM_BSD_H' \
    'extern int g_bsdErrno;' \
    '#endif' \
    > /fuzz/build/shim_includes/switch/services/bsd.h

# Build a minimal static library and install headers
RUN mkdir -p /fuzz/build/obj && mkdir -p ${PREFIX}/lib && \
    ${CC} -O2 -fPIC -I/fuzz/build/shim_includes -Isysmodule/source/third_party \
      -c sysmodule/source/third_party/nanoprintf.c -o /fuzz/build/obj/nanoprintf.o && \
    ar rcs ${PREFIX}/lib/libsysdvr_rtsp.a /fuzz/build/obj/nanoprintf.o && \
    mkdir -p ${PREFIX}/include/sysmodule/source && \
    find sysmodule/source -type d -exec mkdir -p ${PREFIX}/include/{} \; && \
    find sysmodule/source -name '*.h' -exec cp --parents {} ${PREFIX}/include \; && \
    mkdir -p ${PREFIX}/include && cp -r /fuzz/build/shim_includes/* ${PREFIX}/include/

# Finished
