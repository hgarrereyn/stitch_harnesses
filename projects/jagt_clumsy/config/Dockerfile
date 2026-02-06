ARG BASE_IMAGE
FROM ${BASE_IMAGE}

ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install SRC=/fuzz/src

RUN mkdir -p /fuzz/stubs/include /fuzz/build ${PREFIX}/include ${PREFIX}/lib && \
    printf "#ifndef WINDOWS_H_STUB\n#define WINDOWS_H_STUB\n#include <stdint.h>\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n static inline void OutputDebugString(const char*){}\n static inline void DebugBreak(void){}\n static inline unsigned int timeBeginPeriod(unsigned int u){return 0;}\n static inline unsigned int timeEndPeriod(unsigned int u){return 0;}\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/stubs/include/Windows.h && \
    printf "#ifndef IUP_H_STUB\n#define IUP_H_STUB\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n typedef struct Ihandle Ihandle;\n typedef int (*Icallback)(Ihandle*);\n enum { IUP_DEFAULT = 0 };\n static inline float IupGetFloat(Ihandle* ih, const char* a){return 0.0f;}\n static inline int IupGetInt(Ihandle* ih, const char* a){return 0;}\n static inline char* IupGetAttribute(Ihandle* ih, const char* a){return (char*)0;}\n static inline void IupSetAttribute(Ihandle* ih, const char* a, const char* b){}\n static inline void IupStoreAttribute(Ihandle* ih, const char* a, const char* b){}\n static inline void IupStoreGlobal(const char* a, const char* b){}\n static inline char* IupGetGlobal(const char* a){return (char*)0;}\n static inline Icallback IupGetCallback(Ihandle* ih, const char* a){return (Icallback)0;}\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/stubs/include/iup.h && \
    printf "#ifndef WINDIVERT_H_STUB\n#define WINDIVERT_H_STUB\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n typedef int BOOL; typedef void* HWND; typedef unsigned int UINT; typedef unsigned long DWORD; typedef long LONG;\n typedef struct { unsigned long dummy0; unsigned long dummy1; } WINDIVERT_ADDRESS;\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/stubs/include/windivert.h && \
    printf "#include <stdint.h>\n#include <stddef.h>\nlong __clumsy_atomic_xchg_long(volatile long* p, long v){ __atomic_exchange(p, &v, (long*)(&(long){0}), __ATOMIC_SEQ_CST); return v; }\nshort __clumsy_atomic_xchg_short(volatile short* p, short v){ __atomic_exchange(p, &v, (short*)(&(short){0}), __ATOMIC_SEQ_CST); return v; }\n" > /fuzz/stubs/stub.c && \
    cp ${SRC}/src/common.h ${PREFIX}/include/common.h && \
    cp /fuzz/stubs/include/iup.h ${PREFIX}/include/iup.h && \
    cp /fuzz/stubs/include/windivert.h ${PREFIX}/include/windivert.h && \
    cp /fuzz/stubs/include/Windows.h ${PREFIX}/include/Windows.h

RUN ${CC} -O2 -I/fuzz/stubs/include -I${SRC}/src \
    -D'InterlockedExchange(x,y)=__atomic_exchange_n((long*)(x),(y),__ATOMIC_SEQ_CST)' \
    -D'InterlockedExchange16(x,y)=__atomic_exchange_n((short*)(x),(y),__ATOMIC_SEQ_CST)' \
    -c ${SRC}/src/utils.c -o /fuzz/build/utils.o && \
    ${CC} -O2 -I/fuzz/stubs/include -I${SRC}/src -include stdlib.h -include string.h -c ${SRC}/src/packet.c -o /fuzz/build/packet.o && \
    ${CC} -O2 -I/fuzz/stubs/include -c /fuzz/stubs/stub.c -o /fuzz/build/stub.o && \
    ar rcs ${PREFIX}/lib/libclumsy.a /fuzz/build/utils.o /fuzz/build/packet.o /fuzz/build/stub.o
