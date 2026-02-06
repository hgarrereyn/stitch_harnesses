ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install build and runtime dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake \
    ninja-build \
    make \
    pkg-config \
    libfreetype6-dev \
    libharfbuzz-dev \
    liblua5.4-dev \
 && rm -rf /var/lib/apt/lists/*

# Configure and build the project
RUN cmake -S /fuzz/src -B /build -G Ninja \
    -DCMAKE_C_COMPILER=stitch_libafl_cc \
    -DCMAKE_CXX_COMPILER=stitch_libafl_cxx \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_BUILD_TYPE=Release
RUN cmake --build /build --target vtm -j
RUN cmake --install /build || true

# Install headers for consumers and add a lightweight shim for standard headers
RUN mkdir -p /fuzz/install/include/netxs/desktopio && \
    mkdir -p /fuzz/install/include/netxs && \
    cp -a /fuzz/src/src/netxs/apps.hpp /fuzz/install/include/netxs/ && \
    cp -a /fuzz/src/src/netxs/desktopio/*.hpp /fuzz/install/include/netxs/desktopio/ && \
    cp -a /fuzz/src/src/vtm.hpp /fuzz/install/include/ && \
    printf "#pragma once\n#include <cstddef>\n#include <algorithm>\n#include <mutex>\n#include <condition_variable>\n#include <deque>\n#include <chrono>\n#include <memory>\n#include <functional>\n#include <tuple>\n#include <type_traits>\n#include <utility>\n#include <string>\n#include <string_view>\n#include <sstream>\n#include <vector>\n#include <unordered_map>\n#include <map>\n#include <thread>\n" > /fuzz/install/include/vtm_shim.hpp
