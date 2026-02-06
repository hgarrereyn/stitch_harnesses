ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates wget xz-utils ninja-build pkg-config cmake \
    zlib1g-dev \
 && rm -rf /var/lib/apt/lists/*

# Build and install TagLib 2.x (required by project)
ENV TAGLIB_VERSION=2.1.1
RUN mkdir -p /tmp/build && cd /tmp/build \
 && wget -q https://github.com/taglib/taglib/releases/download/v${TAGLIB_VERSION}/taglib-${TAGLIB_VERSION}.tar.gz \
 && tar -xzf taglib-${TAGLIB_VERSION}.tar.gz \
 && cd taglib-${TAGLIB_VERSION} \
 && cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_SHARED_LIBS=OFF \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
      . \
 && cmake --build . -j$(nproc) \
 && cmake --install . \
 && rm -rf /tmp/build

# Configure, build and install the project (builds the executable)
RUN cmake -G Ninja -S /fuzz/src -B /fuzz/build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=/fuzz/install \
      -DCMAKE_PREFIX_PATH=/fuzz/install \
      -DCMAKE_C_COMPILER=gf_libafl_cc \
      -DCMAKE_CXX_COMPILER=gf_libafl_cxx \
 && cmake --build /fuzz/build -j$(nproc) \
 && cmake --install /fuzz/build

# Create a static library for libncmdump from project sources (non-Windows build)
RUN mkdir -p /fuzz/install/lib /fuzz/install/include \
 && cp -r /fuzz/src/src/include/*.h /fuzz/install/include/ \
 && cp /fuzz/src/src/lib/libncmdump.h /fuzz/install/include/ \
 && gf_libafl_cxx -I/fuzz/src/src/include -I/fuzz/install/include -I/fuzz/install/include/taglib \
      -c /fuzz/src/src/utils/aes.cpp -o /tmp/aes.o \
 && gf_libafl_cxx -I/fuzz/src/src/include -I/fuzz/install/include -I/fuzz/install/include/taglib \
      -c /fuzz/src/src/utils/cJSON.cpp -o /tmp/cjson.o \
 && gf_libafl_cxx -I/fuzz/src/src/include -I/fuzz/install/include -I/fuzz/install/include/taglib \
      -c /fuzz/src/src/ncmcrypt.cpp -o /tmp/ncmcrypt.o \
 && gf_libafl_cxx -I/fuzz/src/src/include -I/fuzz/install/include -I/fuzz/install/include/taglib \
      -c /fuzz/src/src/lib/libncmdump.cpp -o /tmp/libapi.o \
 && ar rcs /fuzz/install/lib/libncmdump.a /tmp/aes.o /tmp/cjson.o /tmp/ncmcrypt.o /tmp/libapi.o \
 && rm -f /tmp/aes.o /tmp/cjson.o /tmp/ncmcrypt.o /tmp/libapi.o
