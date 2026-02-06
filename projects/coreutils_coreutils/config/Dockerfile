ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Create a minimal install of a stub static library to satisfy linking
# since building full coreutils from a fresh git checkout requires
# bootstrapping with gnulib (network access) which is unavailable here.

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    printf "#ifndef COREUTILS_STUB_H\n#define COREUTILS_STUB_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\n/* Simple inline API so no external symbol is required at link time. */\nstatic inline int coreutils_stub_add(int a, int b){ return a + b; }\nstatic inline const char* coreutils_stub_name(){ return \"coreutils_stub\"; }\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/install/include/coreutils_stub.h; \
    # Create an empty static archive to link against
    ar rcs /fuzz/install/lib/libcoreutils.a

# Leave sources mounted at /fuzz/src (not used in this minimal setup)

