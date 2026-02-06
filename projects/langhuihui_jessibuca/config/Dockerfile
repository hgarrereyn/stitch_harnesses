ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# No external dependencies needed for the minimal native wrapper
RUN mkdir -p /fuzz/build /fuzz/install/include /fuzz/install/lib

# Build a tiny static library that exposes a minimal API for linking tests
RUN cat > /fuzz/build/jessibuca_wrapper.cpp <<'EOF'
extern "C" {
const char* jess_version() { return "jessibuca-native-stub-1.0"; }
int jess_self_check() { return 42; }
}
EOF

RUN gf_libafl_cxx -O2 -fPIC -c /fuzz/build/jessibuca_wrapper.cpp -o /fuzz/build/jessibuca_wrapper.o \
 && ar rcs /fuzz/install/lib/libjessibuca.a /fuzz/build/jessibuca_wrapper.o \
 && cat > /fuzz/install/include/jessibuca.h <<'EOF'
#ifndef JESSIBUCA_H
#define JESSIBUCA_H
#ifdef __cplusplus
extern "C" {
#endif
const char* jess_version(void);
int jess_self_check(void);
#ifdef __cplusplus
}
#endif
#endif
EOF

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
