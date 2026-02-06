ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Build and install a host-side static library from pico-sdk/tools/elf2uf2
# along with its public headers.

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates \
    cmake \
    ninja-build \
    build-essential \
    binutils \
 && rm -rf /var/lib/apt/lists/*

# Build the elf2uf2 tool (host executable) to validate sources compile with the given toolchain
RUN cmake -S /fuzz/src/pico-sdk/tools/elf2uf2 -B /tmp/build-elf2uf2 -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc -DCMAKE_CXX_COMPILER=gf_libafl_cxx -DCMAKE_BUILD_TYPE=Release \
 && cmake --build /tmp/build-elf2uf2

# Install: create a static library from elf2uf2 sources and copy headers
RUN mkdir -p /fuzz/install/lib /fuzz/install/include/elf2uf2 /fuzz/install/include/boot /fuzz/install/bin \
 && gf_libafl_cxx -std=c++17 -I/fuzz/src/pico-sdk/tools/elf2uf2 -I/fuzz/src/pico-sdk/src/common/boot_uf2/include \
    -Dmain=elf2uf2_tool_main \
    -c /fuzz/src/pico-sdk/tools/elf2uf2/main.cpp -o /tmp/elf2uf2.o \
 && ar rcs /fuzz/install/lib/libelf2uf2.a /tmp/elf2uf2.o \
 && cp /fuzz/src/pico-sdk/tools/elf2uf2/elf.h /fuzz/install/include/elf2uf2/ \
 && cp /fuzz/src/pico-sdk/src/common/boot_uf2/include/boot/uf2.h /fuzz/install/include/boot/ \
 && cp /tmp/build-elf2uf2/elf2uf2 /fuzz/install/bin/
