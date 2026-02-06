ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/w2lshim; \
    echo '#ifndef W2L_SHIM_H' > /tmp/w2lshim/w2l_shim.h; \
    echo '#define W2L_SHIM_H' >> /tmp/w2lshim/w2l_shim.h; \
    echo '' >> /tmp/w2lshim/w2l_shim.h; \
    echo '#ifdef __cplusplus' >> /tmp/w2lshim/w2l_shim.h; \
    echo 'extern "C" {' >> /tmp/w2lshim/w2l_shim.h; \
    echo '#endif' >> /tmp/w2lshim/w2l_shim.h; \
    echo '' >> /tmp/w2lshim/w2l_shim.h; \
    echo '// Returns a constant string describing the shim/library.' >> /tmp/w2lshim/w2l_shim.h; \
    echo 'const char* w2l_shim_version();' >> /tmp/w2lshim/w2l_shim.h; \
    echo '' >> /tmp/w2lshim/w2l_shim.h; \
    echo '#ifdef __cplusplus' >> /tmp/w2lshim/w2l_shim.h; \
    echo '}' >> /tmp/w2lshim/w2l_shim.h; \
    echo '#endif' >> /tmp/w2lshim/w2l_shim.h; \
    echo '' >> /tmp/w2lshim/w2l_shim.h; \
    echo '#endif // W2L_SHIM_H' >> /tmp/w2lshim/w2l_shim.h; \
    echo '#include "w2l_shim.h"' > /tmp/w2lshim/w2l_shim.cpp; \
    echo '' >> /tmp/w2lshim/w2l_shim.cpp; \
    echo 'const char* w2l_shim_version() {' >> /tmp/w2lshim/w2l_shim.cpp; \
    echo '    return "wav2letter shim 0.1";' >> /tmp/w2lshim/w2l_shim.cpp; \
    echo '}' >> /tmp/w2lshim/w2l_shim.cpp; \
    stitch_libafl_cxx -fPIC -O2 -c /tmp/w2lshim/w2l_shim.cpp -o /tmp/w2lshim/w2l_shim.o; \
    ar rcs /tmp/w2lshim/libw2lshim.a /tmp/w2lshim/w2l_shim.o; \
    install -m 0644 /tmp/w2lshim/libw2lshim.a /fuzz/install/lib/; \
    install -m 0644 /tmp/w2lshim/w2l_shim.h /fuzz/install/include/; \
    rm -rf /tmp/w2lshim
