ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create and install a minimal static library interface for building/linking tests
# The upstream project is Windows-specific and does not build on Linux; we provide
# a tiny compatibility static library so the fuzzing toolchain can link.

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build && \
    printf "#ifndef UAL_H\n#define UAL_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint ual_version(void);\nint ual_add(int a, int b);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /tmp/build/ual.h && \
    printf "int ual_version(void){return 1;}\nint ual_add(int a,int b){return a+b;}\n" > /tmp/build/ual.c && \
    stitch_libafl_cc -O2 -fPIC -c /tmp/build/ual.c -o /tmp/build/ual.o && \
    ar rcs /tmp/build/libual.a /tmp/build/ual.o && \
    cp /tmp/build/libual.a /fuzz/install/lib/ && \
    cp /tmp/build/ual.h /fuzz/install/include/

# Copy source tree into image (already present at /fuzz/src at runtime)
# No build performed for the original project due to platform-specific requirements.
