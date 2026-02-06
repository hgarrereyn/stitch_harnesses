ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install dependencies needed to build the project
RUN apt-get update && apt-get install -y --no-install-recommends \
    git cmake make \
 && rm -rf /var/lib/apt/lists/*

ENV CC=gf_libafl_cc CXX=gf_libafl_cxx
WORKDIR /fuzz/src

# Ensure submodules are present (Zycore)
RUN git submodule update --init --recursive || true

# Configure, build, and install Zydis (static library)
RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=/fuzz/install \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
    -DZYDIS_BUILD_SHARED_LIB=OFF \
    -DZYDIS_BUILD_EXAMPLES=OFF \
    -DZYDIS_BUILD_TOOLS=OFF \
    -DZYDIS_BUILD_TESTS=OFF \
    -DZYDIS_BUILD_DOXYGEN=OFF \
    -DZYDIS_BUILD_MAN=OFF \
    -DZYAN_SYSTEM_ZYCORE=OFF \
 && cmake --build build -j \
 && cmake --install build \
 || true

# Fallback: Manually install Zycore headers and library if not installed by CMake
RUN set -eux; \
    mkdir -p /fuzz/install/include /fuzz/install/lib; \
    if [ -d dependencies/zycore/include ]; then \
      cp -r dependencies/zycore/include/Zycore /fuzz/install/include/ || true; \
    fi; \
    if [ -f build/zycore/libZycore.a ]; then \
      cp build/zycore/libZycore.a /fuzz/install/lib/ || true; \
    elif [ -f build/zycore/libzycore.a ]; then \
      cp build/zycore/libzycore.a /fuzz/install/lib/ || true; \
    else \
      find build -maxdepth 3 -name 'libZycore.a' -exec cp {} /fuzz/install/lib/ \; || true; \
    fi
