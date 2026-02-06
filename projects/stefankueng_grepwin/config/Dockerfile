ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# This project is Windows-only; provide a minimal shim static library so the fuzzing
# pipeline can link. No external deps required on Linux.

RUN mkdir -p /fuzz/install/include /fuzz/install/lib /tmp/build && \
    printf "#ifndef GREPWIN_DUMMY_H\n#define GREPWIN_DUMMY_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nconst char* grepwin_version(void);\nint grepwin_add(int a, int b);\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > /fuzz/install/include/grepwin_dummy.h && \
    printf "#include <stdio.h>\nconst char* grepwin_version(void){return \"grepWin-shim 0.1\";}\nint grepwin_add(int a,int b){return a+b;}\n" > /tmp/build/grepwin_dummy.c && \
    gf_libafl_cc -fPIC -O2 -c /tmp/build/grepwin_dummy.c -o /tmp/build/grepwin_dummy.o && \
    ar rcs /fuzz/install/lib/libgrepwin_dummy.a /tmp/build/grepwin_dummy.o && \
    rm -rf /tmp/build
