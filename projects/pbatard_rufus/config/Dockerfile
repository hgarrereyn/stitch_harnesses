ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a minimal static library from the Rufus cregex component
# Using the required compilers and installing into /fuzz/install
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install/lib /fuzz/install/include; \
    cd /fuzz/src/src; \
    CC=stitch_libafl_cc CFLAGS="-O2 -fPIC" \
      stitch_libafl_cc -O2 -fPIC -c cregex_compile.c -o /fuzz/build/cregex_compile.o; \
    CC=stitch_libafl_cc CFLAGS="-O2 -fPIC" \
      stitch_libafl_cc -O2 -fPIC -c cregex_parse.c -o /fuzz/build/cregex_parse.o; \
    CC=stitch_libafl_cc CFLAGS="-O2 -fPIC" \
      stitch_libafl_cc -O2 -fPIC -c cregex_vm.c -o /fuzz/build/cregex_vm.o; \
    ar rcs /fuzz/install/lib/libcregex.a /fuzz/build/cregex_compile.o /fuzz/build/cregex_parse.o /fuzz/build/cregex_vm.o; \
    cp -v cregex.h /fuzz/install/include/
