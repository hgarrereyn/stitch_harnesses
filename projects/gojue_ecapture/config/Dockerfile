ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && apt-get install -y --no-install-recommends make ca-certificates && rm -rf /var/lib/apt/lists/*

# Build and install a tiny static C library that exposes a trivial API for linking tests
# This repo is primarily Go + eBPF sources and does not ship a C/C++ userland library,
# so we provide a small C API wrapper for testing/linking purposes.
RUN mkdir -p /tmp/build && cd /tmp/build \
    && printf "#ifndef ECAPTURE_UTILS_H\n#define ECAPTURE_UTILS_H\n#ifdef __cplusplus\nextern \"C\" {\n#endif\nconst char* ecapture_project_name();\nint ecapture_answer();\n#ifdef __cplusplus\n}\n#endif\n#endif\n" > ecapture_utils.h \
    && printf "#include \"ecapture_utils.h\"\nconst char* ecapture_project_name(){return \"ecapture\";}\nint ecapture_answer(){return 42;}\n" > ecapture_utils.c \
    && mkdir -p /fuzz/install/include /fuzz/install/lib \
    && gf_libafl_cc -O2 -fPIC -c ecapture_utils.c -o ecapture_utils.o \
    && ar rcs libecapture_utils.a ecapture_utils.o \
    && cp libecapture_utils.a /fuzz/install/lib/ \
    && cp ecapture_utils.h /fuzz/install/include/

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx

# No further build needed; headers and static lib are installed under /fuzz/install
