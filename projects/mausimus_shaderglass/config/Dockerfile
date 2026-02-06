ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cp -v /fuzz/src/ShaderGC/framework.h /fuzz/install/include/; \
    cp -v /fuzz/src/ShaderGC/SourceDefs.h /fuzz/install/include/; \
    cp -v /fuzz/src/ShaderGC/ShaderDef.h /fuzz/install/include/; \
    cp -v /fuzz/src/ShaderGC/TextureDef.h /fuzz/install/include/; \
    cp -v /fuzz/src/ShaderGC/PresetDef.h /fuzz/install/include/; \
    cp -v /fuzz/src/ShaderGC/ShaderCache.h /fuzz/install/include/; \
    cp -v /fuzz/src/ShaderGC/ShaderGC.h /fuzz/install/include/; \
    printf "void __shadergc_dummy(void){}\n" > /tmp/dummy.c; \
    gf_libafl_cc -c /tmp/dummy.c -o /tmp/dummy.o; \
    ar rcs /fuzz/install/lib/libshadergc.a /tmp/dummy.o; \
    rm -f /tmp/dummy.c /tmp/dummy.o
