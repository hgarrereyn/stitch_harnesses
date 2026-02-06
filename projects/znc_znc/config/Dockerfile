ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build \
    ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Configure and build ZNC with most optional deps disabled to keep build lean
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DWANT_OPENSSL=NO \
    -DWANT_ZLIB=NO \
    -DWANT_PERL=OFF \
    -DWANT_PYTHON=OFF \
    -DWANT_TCL=OFF \
    -DWANT_I18N=NO \
    -DWANT_ICU=NO \
    -DWANT_CYRUS=NO \
    -DWANT_ARGON=NO \
 && cmake --build /fuzz/build --target install -j$(nproc) \
 && mkdir -p /fuzz/install/lib \
 && if [ -f /fuzz/build/src/libznc.a ]; then cp /fuzz/build/src/libznc.a /fuzz/install/lib/; fi
