ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build tools and minimal deps
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config python3 \
 && rm -rf /var/lib/apt/lists/*

# Configure Granite (we'll only build the util target to keep it light)
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN mkdir -p /fuzz/build && \
    cmake -S /fuzz/src -B /fuzz/build -G Ninja \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DGRANITE_SHARED=OFF \
      -DGRANITE_TOOLS=OFF \
      -DGRANITE_AUDIO=OFF \
      -DGRANITE_BULLET=OFF \
      -DGRANITE_FFMPEG=OFF \
      -DGRANITE_PLATFORM=null \
      -DGRANITE_VULKAN_PROFILES=OFF \
      -DGRANITE_INSTALL_TARGETS=ON && \
    cmake --build /fuzz/build --target granite-util -j$(nproc)

# Manually install static libs and headers
RUN mkdir -p /fuzz/install/lib && \
    find /fuzz/build -name "*granite-util*.a" -exec cp -v {} /fuzz/install/lib/ \; && \
    mkdir -p /fuzz/install/include && \
    cp -r /fuzz/src/util /fuzz/install/include/util
