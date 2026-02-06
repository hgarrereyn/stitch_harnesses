ARG BASE_IMAGE
FROM ${BASE_IMAGE}

RUN set -eux; \
    install -d /fuzz/install/include /fuzz/install/lib /tmp/build; \
    # Provide a tiny portable wrapper API for testing/linking
    printf "#pragma once\nextern \"C\" int tgit_sum(int a, int b);\n" > /fuzz/install/include/tgit_portable.h; \
    printf "extern \"C\" int tgit_sum(int a, int b){ return a + b; }\n" > /tmp/build/tgit_portable.cpp; \
    stitch_libafl_cxx -c /tmp/build/tgit_portable.cpp -o /tmp/build/tgit_portable.o; \
    ar rcs /fuzz/install/lib/libtgitutils.a /tmp/build/tgit_portable.o; \
    rm -rf /tmp/build
