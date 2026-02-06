ARG BASE_IMAGE
FROM ${BASE_IMAGE}

# Install minimal tools and Qt headers for QString
RUN apt-get update && apt-get install -y --no-install-recommends ninja-build cmake qtbase5-dev && rm -rf /var/lib/apt/lists/*

# Prepare install prefix and install header from source tree
RUN mkdir -p /fuzz/install/include /fuzz/install/lib && \
    install -Dm644 /fuzz/src/global.h /fuzz/install/include/global.h

# Build and install a tiny static library stub to satisfy linking
RUN mkdir -p /fuzz/minlib && \
    cd /fuzz/minlib && \
    printf "%s\n" "cmake_minimum_required(VERSION 3.13)" \
                  "project(xelfviewer_dummy LANGUAGES C CXX)" \
                  "set(CMAKE_C_STANDARD 11)" \
                  "set(CMAKE_CXX_STANDARD 17)" \
                  "add_library(xelfviewer_dummy STATIC dummy.cpp)" \
                  "target_include_directories(xelfviewer_dummy PUBLIC /fuzz/install/include)" \
                  "install(TARGETS xelfviewer_dummy ARCHIVE DESTINATION lib)" \
                  "install(FILES /fuzz/install/include/global.h DESTINATION include)" \
        > CMakeLists.txt && \
    printf "%s\n" "#include <stddef.h>" "extern \"C\" int xelfviewer_dummy_anchor;" "int xelfviewer_dummy_anchor = 0;" > dummy.cpp && \
    cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/fuzz/install \
          -DCMAKE_C_COMPILER=gf_libafl_cc -DCMAKE_CXX_COMPILER=gf_libafl_cxx . && \
    ninja -j$(nproc) && ninja install
