ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No extra system dependencies are required for the shim build.

# Build and install a minimal static library shim to satisfy linking
# The actual ESP32 project depends on Arduino/ESP-IDF and cannot be built on this image.
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx PREFIX=/fuzz/install

RUN mkdir -p ${PREFIX}/include ${PREFIX}/lib /tmp/build && \
    printf '#ifndef PAXCOUNTER_SHIM_H\n#define PAXCOUNTER_SHIM_H\n#ifdef __cplusplus\nextern "C" {\n#endif\nconst char* paxcounter_version();\nint paxcounter_add(int a,int b);\n#ifdef __cplusplus\n}\n#endif\n#endif\n' > /tmp/build/paxcounter_shim.h && \
    printf '#include <stddef.h>\nextern "C" const char* paxcounter_version(){ return "ESP32-Paxcounter shim"; }\nextern "C" int paxcounter_add(int a,int b){ return a+b; }\n' > /tmp/build/paxcounter_shim.cpp && \
    stitch_libafl_cxx -O2 -fPIC -c /tmp/build/paxcounter_shim.cpp -o /tmp/build/paxcounter_shim.o && \
    ar rcs ${PREFIX}/lib/libpaxcounter.a /tmp/build/paxcounter_shim.o && \
    cp /tmp/build/paxcounter_shim.h ${PREFIX}/include/
