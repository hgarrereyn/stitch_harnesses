ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    mkdir -p /build && cd /build; \
    echo '#define CGLTF_IMPLEMENTATION' > cgltf_all.c; \
    echo '#define CGLTF_WRITE_IMPLEMENTATION' >> cgltf_all.c; \
    echo '#include "/fuzz/src/cgltf_write.h"' >> cgltf_all.c; \
    stitch_libafl_cc -O2 -fPIC -c cgltf_all.c -o cgltf.o; \
    ar rcs libcgltf.a cgltf.o; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    cp /fuzz/src/cgltf.h /fuzz/install/include/; \
    cp /fuzz/src/cgltf_write.h /fuzz/install/include/; \
    cp libcgltf.a /fuzz/install/lib/
