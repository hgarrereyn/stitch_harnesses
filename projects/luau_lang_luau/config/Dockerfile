ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    build-essential cmake make \
 && rm -rf /var/lib/apt/lists/*

# Configure and build static libraries only (CLI/tests off)
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

WORKDIR /fuzz
RUN cmake -S /fuzz/src -B /fuzz/build \
    -G "Unix Makefiles" \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DLUAU_BUILD_CLI=OFF \
    -DLUAU_BUILD_TESTS=OFF \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install
RUN cmake --build /fuzz/build -- -j$(nproc)

# Install: copy headers and libraries to /fuzz/install
RUN mkdir -p /fuzz/install/include /fuzz/install/lib \
 && cp -r /fuzz/src/VM/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/Compiler/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/Ast/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/Config/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/Analysis/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/Require/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/CodeGen/include/* /fuzz/install/include/ \
 && cp -r /fuzz/src/Common/include/* /fuzz/install/include/ \
 && cp /fuzz/build/libLuau*.a /fuzz/install/lib/
