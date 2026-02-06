ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config \
 && rm -rf /var/lib/apt/lists/*

# Configure, build, and "install" FreeRTOS-Kernel
ENV CC=stitch_libafl_cc CXX=stitch_libafl_cxx

# Configure with CMake
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_BUILD_TYPE=RelWithDebInfo \
    -DFREERTOS_HEAP=4 \
    -DFREERTOS_PORT=GCC_POSIX \
    -DFREERTOS_CONFIG_FILE_DIRECTORY=/fuzz/src/examples/template_configuration \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build static library
RUN cmake --build /fuzz/build -j

# Manual install since upstream has no install rules
RUN mkdir -p /fuzz/install/lib /fuzz/install/include && \
    cp /fuzz/build/libfreertos_kernel.a /fuzz/install/lib/ && \
    cp -r /fuzz/src/include/* /fuzz/install/include/ && \
    mkdir -p /fuzz/install/include/portable && \
    cp -r /fuzz/src/portable/* /fuzz/install/include/portable/ && \
    # Provide a default FreeRTOSConfig.h to consumers
    cp /fuzz/src/examples/template_configuration/FreeRTOSConfig.h /fuzz/install/include/
