ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Only need binutils to create a static archive; no heavy deps
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

# Install headers
RUN mkdir -p /fuzz/install/include/framework /fuzz/install/include/glm /fuzz/install/include/glutil /fuzz/install/include/glimg /fuzz/install/include/glload /fuzz/install/lib && \
    cp -v /fuzz/src/framework/*.h /fuzz/install/include/framework/ && \
    cp -v /fuzz/src/framework/rapidxml*.hpp /fuzz/install/include/framework/ && \
    cp -rv /fuzz/src/glsdk/glm/glm /fuzz/install/include/glm/ && \
    cp -rv /fuzz/src/glsdk/glutil/include/* /fuzz/install/include/glutil/ && \
    cp -rv /fuzz/src/glsdk/glimg/include/* /fuzz/install/include/glimg/ && \
    cp -rv /fuzz/src/glsdk/glload/include/* /fuzz/install/include/glload/ && \
    printf "#pragma once\n#include <glm/glm.hpp>\n" > /fuzz/install/include/framework/glm_shim.hpp

# Create an empty static library named libframework.a to link against
RUN printf "void __framework_placeholder(){}" > /tmp/fw.c && \
    gf_libafl_cc -c /tmp/fw.c -o /tmp/fw.o && \
    ar rcs /fuzz/install/lib/libframework.a /tmp/fw.o
