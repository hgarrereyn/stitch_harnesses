ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build dependencies and system libraries (prefer system for most, but use bundled Abseil for building; use system Abseil headers/libs for consumers)
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
    git \
    build-essential \
    pkg-config \
    cmake \
    ninja-build \
    libprotobuf-dev libprotoc-dev protobuf-compiler \
    libcapstone-dev \
    libre2-dev \
    zlib1g-dev \
    libzstd-dev \
    libabsl-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build
ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
RUN cmake -S /fuzz/src -B /fuzz/build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_C_COMPILER=${CC} -DCMAKE_CXX_COMPILER=${CXX} \
    -DBLOATY_PREFER_SYSTEM_ABSL=OFF
RUN cmake --build /fuzz/build --parallel
# Install and prepare dev artifacts
RUN cmake --install /fuzz/build || true \
 && rm -rf /fuzz/install/include/absl \
 && mkdir -p /fuzz/install/lib /fuzz/install/include/dwarf \
 && cp -v /fuzz/build/liblibbloaty.a /fuzz/install/lib/ || true \
 && cp -v /fuzz/src/src/bloaty.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/range_map.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/re.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/source_map.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/util.h /fuzz/install/include/ \
 && cp -v /fuzz/src/src/dwarf/*.h /fuzz/install/include/dwarf/ \
 && cp -v /fuzz/src/src/dwarf_constants.h /fuzz/install/include/ \
 && cp -v /fuzz/src/third_party/lief_pe/pe_structures.h /fuzz/install/include/ || true \
 && cp -v /fuzz/build/src/bloaty.pb.h /fuzz/install/include/
