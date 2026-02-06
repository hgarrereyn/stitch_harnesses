ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# This project is an Unreal Engine plugin and cannot be built without the Unreal toolchain.
# To enable linking during fuzzing setup, we install a minimal stub static library
# that satisfies the linker and provides a trivial symbol.

# Environment
ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    PREFIX=/fuzz/install

RUN set -eux; \
    mkdir -p "$PREFIX/lib" "$PREFIX/include" /tmp/build; \
    echo 'void rmc_stub(void){}' > /tmp/build/stub.c; \
    "$CC" -c -O2 /tmp/build/stub.c -o /tmp/build/stub.o; \
    ar rcs "$PREFIX/lib/libRealtimeMeshComponent.a" /tmp/build/stub.o; \
    echo '#ifndef RMC_STUB_H\n#define RMC_STUB_H\n#ifdef __cplusplus\nextern "C" {\n#endif\nvoid rmc_stub(void);\n#ifdef __cplusplus\n}\n#endif\n#endif' > "$PREFIX/include/RealtimeMeshComponentStub.h"; \
    rm -rf /tmp/build

# No further build steps possible without Unreal Engine. The stub library is installed in /fuzz/install.
