ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install required build tools
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make python3 pkg-config \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /fuzz/build /fuzz/install

# Configure for host platform with provided clang wrappers
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_C_COMPILER=gf_libafl_cc \
    -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
    -DCMAKE_BUILD_TYPE=Release \
    -DPICO_PLATFORM=host \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install

# Build (host libs are mostly INTERFACE; this validates configuration)
RUN cmake --build /fuzz/build

# Install headers into /fuzz/install/include, including generated headers
RUN mkdir -p /fuzz/install/include && \
    if [ -d /fuzz/src/src/common ]; then find /fuzz/src/src/common -type d -name include -exec bash -lc 'd="{}"; cp -r "$d"/* /fuzz/install/include/ 2>/dev/null || true' \; ; fi && \
    if [ -d /fuzz/src/src/host ]; then find /fuzz/src/src/host -type d -name include -exec bash -lc 'd="{}"; cp -r "$d"/* /fuzz/install/include/ 2>/dev/null || true' \; ; fi && \
    if [ -d /fuzz/build/generated/pico_base ]; then cp -r /fuzz/build/generated/pico_base/* /fuzz/install/include/ ; fi && \
    if [ -d /fuzz/src/src/boards/include/boards ]; then mkdir -p /fuzz/install/include/boards && cp -r /fuzz/src/src/boards/include/boards/* /fuzz/install/include/boards/ ; fi
