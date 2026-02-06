ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal build tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    cmake ninja-build make pkg-config ca-certificates \
 && rm -rf /var/lib/apt/lists/*

# Provide a default LVGL configuration header
RUN set -eux; \
    mkdir -p /fuzz/build /fuzz/install; \
    sed -e '0,/#if 0/s//#if 1/' /fuzz/src/lv_conf_template.h > /fuzz/src/lv_conf.h

# Configure, build static lib, and install
RUN set -eux; \
    cmake -S /fuzz/src -B /fuzz/build -G Ninja \
      -DCMAKE_C_COMPILER=stitch_libafl_cc \
      -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DBUILD_SHARED_LIBS=OFF \
      -DLV_BUILD_LVGL_H_SIMPLE_INCLUDE=ON; \
    cmake --build /fuzz/build --target install --parallel
