ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools (cmake may not be present in the base image used by the tester)
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
 && rm -rf /var/lib/apt/lists/*

ENV CC=stitch_libafl_cc \
    CXX=stitch_libafl_cxx \
    AR=llvm-ar-17 \
    RANLIB=llvm-ranlib-17

# Configure, build static libs, and install artifacts to /fuzz/install
RUN mkdir -p /fuzz/build /fuzz/install && \
    cd /fuzz/build && \
    cmake -G "Ninja" \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=${CC} \
      -DCMAKE_CXX_COMPILER=${CXX} \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      /fuzz/src && \
    ninja -j"$(nproc)" libxaacdec libxaacenc && \
    mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp -v ./libxaacdec.a ./libxaacenc.a /fuzz/install/lib/ && \
    cp -v /fuzz/src/common/ixheaac_type_def.h /fuzz/install/include/ && \
    cp -v /fuzz/src/decoder/ixheaacd_apicmd_standards.h /fuzz/install/include/ && \
    cp -v /fuzz/src/decoder/ixheaacd_api_defs.h /fuzz/install/include/ && \
    cp -v /fuzz/src/decoder/ixheaacd_error_codes.h /fuzz/install/include/ && \
    cp -v /fuzz/src/decoder/ixheaacd_memory_standards.h /fuzz/install/include/ && \
    cp -v /fuzz/src/encoder/ixheaace_api.h /fuzz/install/include/
