ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build a minimal C static library shim that satisfies linking
RUN apt-get update && apt-get install -y --no-install-recommends binutils && rm -rf /var/lib/apt/lists/*

WORKDIR /tmp/shim
RUN printf "#ifndef NUM_BIGINT_H\n#define NUM_BIGINT_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint num_bigint_version(void);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > num_bigint.h \
 && printf "int num_bigint_version(void){return 46;}\n" > num_bigint.c \
 && stitch_libafl_cc -fPIC -O2 -c num_bigint.c -o num_bigint.o \
 && ar rcs libnum_bigint.a num_bigint.o \
 && mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp libnum_bigint.a /fuzz/install/lib/ \
 && cp num_bigint.h /fuzz/install/include/

WORKDIR /fuzz/src
