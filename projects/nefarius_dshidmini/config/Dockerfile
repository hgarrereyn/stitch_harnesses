ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Prepare install dirs
RUN mkdir -p /fuzz/install/include/DsHidMini /fuzz/install/lib

# Copy public headers from mounted source tree
RUN cp -r /fuzz/src/include/DsHidMini /fuzz/install/include/

# Provide minimal Windows shim headers so the public headers compile on Linux/Clang
RUN bash -lc 'echo "#ifndef DSHIDMINI_WIN_SHIM_H" > /fuzz/install/include/win_shim.h && \
    echo "#define DSHIDMINI_WIN_SHIM_H" >> /fuzz/install/include/win_shim.h && \
    echo "#include <stdint.h>" >> /fuzz/install/include/win_shim.h && \
    echo "#ifdef __cplusplus" >> /fuzz/install/include/win_shim.h && \
    echo "extern \"C\" {" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "typedef uint8_t UCHAR;" >> /fuzz/install/include/win_shim.h && \
    echo "typedef uint16_t USHORT;" >> /fuzz/install/include/win_shim.h && \
    echo "typedef uint32_t ULONG;" >> /fuzz/install/include/win_shim.h && \
    echo "typedef int32_t LONG;" >> /fuzz/install/include/win_shim.h && \
    echo "typedef float FLOAT;" >> /fuzz/install/include/win_shim.h && \
    echo "typedef uint8_t BOOLEAN;" >> /fuzz/install/include/win_shim.h && \
    echo "#ifndef TRUE" >> /fuzz/install/include/win_shim.h && \
    echo "#define TRUE 1" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "#ifndef FALSE" >> /fuzz/install/include/win_shim.h && \
    echo "#define FALSE 0" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "#ifndef FORCEINLINE" >> /fuzz/install/include/win_shim.h && \
    echo "#define FORCEINLINE inline __attribute__((always_inline))" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "#ifndef __declspec" >> /fuzz/install/include/win_shim.h && \
    echo "#define __declspec(x)" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "#ifndef _In_" >> /fuzz/install/include/win_shim.h && \
    echo "#define _In_" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "typedef struct _GUID { uint32_t Data1; uint16_t Data2; uint16_t Data3; uint8_t Data4[8]; } GUID;" >> /fuzz/install/include/win_shim.h && \
    echo "#define DEFINE_GUID(name, l, w1, w2, b1,b2,b3,b4,b5,b6,b7,b8) const GUID name = { (uint32_t)(l), (uint16_t)(w1), (uint16_t)(w2), { (uint8_t)(b1), (uint8_t)(b2), (uint8_t)(b3), (uint8_t)(b4), (uint8_t)(b5), (uint8_t)(b6), (uint8_t)(b7), (uint8_t)(b8) } };" >> /fuzz/install/include/win_shim.h && \
    echo "typedef struct _DEVPROPKEY { GUID fmtid; uint32_t pid; } DEVPROPKEY;" >> /fuzz/install/include/win_shim.h && \
    echo "#define DEFINE_DEVPROPKEY(name, l, w1, w2, b1,b2,b3,b4,b5,b6,b7,b8, pid) const DEVPROPKEY name = { { (uint32_t)(l), (uint16_t)(w1), (uint16_t)(w2), { (uint8_t)(b1), (uint8_t)(b2), (uint8_t)(b3), (uint8_t)(b4), (uint8_t)(b5), (uint8_t)(b6), (uint8_t)(b7), (uint8_t)(b8) } }, (uint32_t)(pid) };" >> /fuzz/install/include/win_shim.h && \
    echo "#ifdef __cplusplus" >> /fuzz/install/include/win_shim.h && \
    echo "}" >> /fuzz/install/include/win_shim.h && \
    echo "#endif" >> /fuzz/install/include/win_shim.h && \
    echo "#endif /* DSHIDMINI_WIN_SHIM_H */" >> /fuzz/install/include/win_shim.h'

# Provide packing pragma shims
RUN bash -lc 'echo "#pragma pack(push, 1)" > /fuzz/install/include/pshpack1.h && echo "#pragma pack(pop)" > /fuzz/install/include/poppack.h'

# Create a tiny static library to satisfy linker (-ldshidmini)
RUN bash -lc 'printf "int dshidmini_placeholder(void){return 0;}\n" > /tmp/placeholder.c && \
    stitch_libafl_cc -c /tmp/placeholder.c -o /tmp/placeholder.o && \
    ar rcs /fuzz/install/lib/libdshidmini.a /tmp/placeholder.o'
