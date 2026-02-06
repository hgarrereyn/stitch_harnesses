ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal C API shim to enable linking in tests
RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build; \
    printf "#ifndef KYANOS_C_H\n#define KYANOS_C_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nint kyanos_add(int a, int b);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/install/include/kyanos_c.h; \
    printf "int kyanos_add(int a, int b){ return a + b; }\n" > /tmp/build/kyanos_c.c; \
    gf_libafl_cc -O2 -fPIC -c /tmp/build/kyanos_c.c -o /tmp/build/kyanos_c.o; \
    ar rcs /fuzz/install/lib/libkyanos_c.a /tmp/build/kyanos_c.o; \
    ranlib /fuzz/install/lib/libkyanos_c.a
